from pyadh import *
from pyadh.default_n import *
from navier_stokes_cylinder_fib_3d_p import *

#timeIntegration = FLCBDF
#stepController  = FLCBDF_controller
#systemStepControllerType = SplitOperator.Sequential_MinFLCBDFModelStep
#timeIntegration = BackwardEuler
#stepController  = FixedStep
#systemStepControllerType = SplitOperator.Sequential_FixedStep
timeIntegration = NoIntegration
#stepController  = Newton_controller
rtol_u[1] = 1.0e-3
rtol_u[2] = 1.0e-3
rtol_u[3] = 1.0e-3
atol_u[1] = 1.0e-2
atol_u[2] = 1.0e-2
atol_u[3] = 1.0e-2



runCFL = 0.1#None
#DT=1.0e-1
DT=0.0000001
if timeIntegration == NoIntegration:
    nDTout = 1
else:
    nDTout = 100#100#2000#int(T/DT)

DT = T/float(nDTout)
tnList = [i*DT for i in range(nDTout+1)]
femSpaces = {0:C0_AffineLinearOnSimplexWithNodalBasis,
             1:C0_AffineLinearOnSimplexWithNodalBasis,
             2:C0_AffineLinearOnSimplexWithNodalBasis,
             3:C0_AffineLinearOnSimplexWithNodalBasis}

elementQuadrature = SimplexGaussQuadrature(nd,3)

elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,3)

# elementQuadrature = SimplexLobattoQuadrature(nd,1)

# elementBoundaryQuadrature = SimplexLobattoQuadrature(nd-1,1)

nn=3
nLevels = 1
triangleOptions="VpAq1.25ena%f" % (((0.15*inflow_height)**3)/6.0,)


subgridError = NavierStokesASGS_velocity_pressure(coefficients,nd,lag=True)
#subgridError = NavierStokesWithBodyForceASGS_velocity_pressure(coefficients,nd,lag=True)
#subgridError = StokesASGS_velocity_pressure(coefficients,nd,lag=False)

#numericalFluxType = None
#numericalFluxType = NavierStokes_Advection_DiagonalUpwind_Diffusion_IIPG_exterior #need weak for parallel and global conservation
#numericalFluxType = Stokes_Advection_DiagonalUpwind_Diffusion_IIPG_exterior #need weak for parallel and global conservation

massLumping = False

shockCapturing = None

multilevelNonlinearSolver  = NLNI

levelNonlinearSolver = Newton

maxNonlinearIts = 10
maxLineSearches = 10
nonlinearSmoother = NLGaussSeidel

fullNewtonFlag = True

tolFac = 0.0#1.0e-6

nl_atol_res = 1.0e-8

matrix = SparseMatrix

multilevelLinearSolver = LU
levelLinearSolver = LU
#multilevelLinearSolver = PETSc
#levelLinearSolver = PETSc

linearSmoother = GaussSeidel

linTolFac = 0.001

#conservativeFlux = {0:'pwl',1:'pwl',2:'pwl'}
#conservativeFlux = {0:'pwl',1:'pwl',2:'pwl'}

# auxiliaryVariables=[BoundaryForce(D=2.0*cylinder_radius,Ubar=Ubar,rho=rho),
#                     PressureProfile(flag=5,center=cylinder_center,radius=cylinder_radius),
#                     RecirculationLength(cylinder_center[0]+cylinder_radius)]
#auxiliaryVariables=[BoundaryForce(D=2.0*cylinder_radius,Ubar=Ubar,rho=rho),PressureProfile(flag=5,center=cylinder_center,radius=cylinder_radius),RecirculationLength()]
#auxiliaryVariables=[BoundaryForce(D=2.0*cylinder_radius,Ubar=Ubar,rho=rho)]
#auxiliaryVariables=[]
