#include <gmi_mesh.h>
#include <gmi_sim.h>
#include <ma.h>
#include <maShape.h>
#include <apfMDS.h>
#include <PCU.h>
#include <SimUtil.h>
#include <SimModel.h>

#include "MeshAdaptPUMI.h"

MeshAdaptPUMIDrvr::MeshAdaptPUMIDrvr(double Hmax, double Hmin, int NumIter,
    const char* sfConfig, const char* maType)
{
  m = 0;
  PCU_Comm_Init();
  PCU_Protect();
  Sim_readLicenseFile(0);
  SimModel_start();
  numVar=0;
  hmin=Hmin; hmax=Hmax;
  numIter=NumIter;
  nAdapt=0;
  if(PCU_Comm_Self()==0)
     printf("MeshAdapt: Setting hmax=%lf, hmin=%lf, numIters(meshadapt)=%d\n",
       hmax, hmin, numIter);
  global[0] = global[1] = global[2] = global[3] = 0;
  local[0] = local[1] = local[2] = local[3] = 0;
  solution = 0;
  size_iso = 0;
  size_scale = 0;
  size_frame = 0;
  err_reg = 0;
  gmi_register_mesh();
  gmi_register_sim();
  approximation_order = 2;
  integration_order = 3;//approximation_order * 2;
  casenum = 2;
  exteriorGlobaltoLocalElementBoundariesArray = NULL;
  size_field_config = sfConfig;
  geomFileName = NULL; 
  modelFileName = NULL; 
  meshFileName = NULL; 
  adapt_type_config = maType;
}

MeshAdaptPUMIDrvr::~MeshAdaptPUMIDrvr()
{
  freeField(solution);
  freeField(size_iso);
  freeField(size_scale);
  freeField(size_frame);
  SimModel_stop();
  Sim_unregisterAllKeys();
}

int MeshAdaptPUMIDrvr::loadModelAndMesh(const char* modelFile, const char* meshFile)
{
  m = apf::loadMdsMesh(modelFile, meshFile);
  m->verify();
  comm_size = PCU_Comm_Peers();
  comm_rank = PCU_Comm_Self();
  return 0;
}

#include <MeshSim.h>
#include <SimMeshTools.h>
#include <SimParasolidKrnl.h>
#define FACE 2
pAManager SModel_attManager(pModel model);
/*
Temporary function used to read in BC from Simmetrix Model
*/
int MeshAdaptPUMIDrvr::getSimmetrixBC(const char* geomFile, const char* modelFile)
{
  if(geomFileName == NULL)
  {
    geomFileName=(char *) malloc(sizeof(char) * strlen(geomFile));
    modelFileName=(char *) malloc(sizeof(char) * strlen(modelFile));
    strcpy(geomFileName,geomFile);
    strcpy(modelFileName,modelFile);
std::cout<<"Does it come here after adapt?\n";
  }
  pNativeModel nmodel = 0;
  pGModel model = 0;
  SimParasolid_start(1);

  nmodel = ParasolidNM_createFromFile(geomFile, 0);

  pProgress prog;
  prog = Progress_new();
  model=GM_load(modelFile,nmodel,prog);

  pAManager attmngr = SModel_attManager(model);
  pACase acase = AMAN_findCase(attmngr, "geom");
  if (acase){
     std::cout<<"Found case, setting the model"<<std::endl;
     AttCase_setModel(acase,model);
  } else {
      std::cout<<"Case not found, rename case to geom\n"<<std::endl;
      exit(1);
  }
  AttCase_associate(acase,prog);

  pGFace gFace;
  GFIter gfIter = GM_faceIter(model);
  pAttribute Att[GM_numFaces(model)];
  int attMap[GM_numFaces(model)];
  int nF=0;
  
  char strAtt[2][25] = {"traction vector","comp3"};
  int modelEntTag;

  while(gFace = GFIter_next(gfIter))
  {
    if(GEN_attrib((pGEntity)gFace,strAtt[0]))
    { 
      modelEntTag=GEN_tag((pGEntity)gFace);
      Att[nF]=GEN_attrib((pGEntity)gFace,strAtt[0]);
      attMap[nF] = modelEntTag;
      nF++;
    }
  }
  GFIter_delete(gfIter);
  
  apf::MeshIterator* fIter = m->begin(FACE);
  apf::MeshEntity* fEnt;
  apf::Vector3 evalPt;
  int numqpt=0;
  const int nsd = 3;
  int bcFlag[nsd+1] = {0,1,1,1};

  //assign a label to the BC type tag
  char label[4][9],labelflux[6],type_flag;
  for(int idx=0;idx<4;idx++)
  {
    if(idx == 0) sprintf(&type_flag,"p");
    else if(idx == 1) sprintf(&type_flag,"u");
    else if(idx == 2) sprintf(&type_flag,"v");
    else if(idx == 3) sprintf(&type_flag,"w");
    sprintf(label[idx],"BCtype_%c",type_flag);
    BCtag[idx] = m->createIntTag(label[idx],1);
std::cout<<"Boundary label "<<label[idx]<<std::endl;
    if(idx>0) sprintf(labelflux,"%c_flux",type_flag);
  }

  while(fEnt = m->iterate(fIter))
  {
    apf::ModelEntity* me=m->toModel(fEnt);
    modelEntTag = m->getModelTag(me);
    apf::ModelEntity* boundary_face = m->findModelEntity(FACE,modelEntTag);
    if(me==boundary_face)
    {
      for(int i=0;i<nF;i++)
      {
        if(attMap[i]==modelEntTag)
        {
          apf::MeshElement* testElem = apf::createMeshElement(m,fEnt);
          if(numqpt==0)
          {
            numqpt = apf::countIntPoints(testElem,integration_order);
            for(int idx=1;idx<nsd+1;idx++)
              fluxtag[idx]= m->createDoubleTag(labelflux,numqpt);
          }
            double data[nsd+1][numqpt];
          for(int k=0; k<numqpt;k++)
          {
            apf::getIntPoint(testElem,integration_order,k,evalPt);
            apf::Vector3 evalPtGlobal;
            apf::mapLocalToGlobal(testElem,evalPt,evalPtGlobal);
            double evalPtSim[nsd];
            evalPtGlobal.toArray(evalPtSim);
            for(int j=0;j<nsd;j++)
              data[j+1][k]=AttributeTensor1_evalDS((pAttributeTensor1)Att[i], j,evalPtSim);
          }
          for(int idx=1;idx<nsd+1;idx++)
          {
            m->setIntTag(fEnt,BCtag[idx],&bcFlag[idx]);
            m->setDoubleTag(fEnt,fluxtag[idx],data[idx]); //set the quadrature points
          }
          apf::destroyMeshElement(testElem);
        } //end if on model
        else
        {
          for(int idx=1;idx<nsd+1;idx++)
          {
            int dummy = 0;
            m->setIntTag(fEnt,BCtag[idx],&dummy);
          }
        }
      }//end loop over attributes
    } 
  }//end while
  m->end(fIter);
  NM_release(nmodel);
  AMAN_release( attmngr );
  //GM_release(model);
  SimParasolid_stop(1);
  std::cout<<"Finished reading and storing diffusive flux BCs\n"; 
  return 0;
} 

int MeshAdaptPUMIDrvr::adaptPUMIMesh()
{
  if (size_field_config == "farhad")
    calculateAnisoSizeField();
  else if (size_field_config == "alvin")
    get_local_error();
    //std::cout<<"Skip error field calculation and adapt "<<std::endl;
  else {
    std::cerr << "unknown size field config " << size_field_config << '\n';
    abort();
  }
  //m->destroyTag(fluxtag[1]); m->destroyTag(fluxtag[2]); m->destroyTag(fluxtag[3]);
  delete [] exteriorGlobaltoLocalElementBoundariesArray;
  exteriorGlobaltoLocalElementBoundariesArray = NULL;
  assert(size_iso == 0);
  for (int d = 0; d <= m->getDimension(); ++d)
    freeNumbering(local[d]);
  /// Adapt the mesh
    ma::Input* in = ma::configure(m, size_scale, size_frame);
    ma::validateInput(in);
    in->shouldRunPreParma = true;
    in->shouldRunMidParma = true;
    in->shouldRunPostParma = true;
    in->maximumIterations = numIter;
    in->shouldSnap = false;
    //in->shouldFixShape = true;
    std::cout<<"Starting adapt (numIter "<<numIter<<")"<<std::endl;
    ma::adapt(in);
    std::cout<<"Finished adapt"<<std::endl;
    freeField(size_frame);
    freeField(size_scale);
    m->verify();
    getSimmetrixBC(geomFileName,modelFileName);
    nAdapt++; //counter for number of adapt steps
  return 0;
}

double MeshAdaptPUMIDrvr::getMinimumQuality()
{
  ma::SizeField* isf = new ma::IdentitySizeField(m);
  apf::MeshIterator* it = m->begin(m->getDimension());
  apf::MeshEntity* e;
  double minq = 1;
  while ((e = m->iterate(it)))
    minq = std::min(minq, ma::measureElementQuality(m, isf, e));
  m->end(it);
  delete isf;
  return PCU_Min_Double(minq);
}
