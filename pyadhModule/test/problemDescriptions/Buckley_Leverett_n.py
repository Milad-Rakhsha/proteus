from pyadh import *
from pyadh.default_n import *
from Buckley_Leverett_p import *
#John Chrispell, Summer 07
#type of time integration formula
timeIntegration = BackwardEuler_cfl
#timeIntegration = ForwardEuler_A
#general type of integration (Forward or to SteadyState)
timeIntegrator = ForwardIntegrator
stepController = Min_dt_controller 
runCFL = 1.1
#runCFL=None

DT=None
#DT=1.0e-3
#nDTout = int(T/DT)
nDTout=100
print "nDTout",nDTout
femSpaces = {0:C0_AffineLinearOnSimplexWithNodalBasis}

elementQuadrature = SimplexGaussQuadrature(nd,3)

elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,3)

#elementQuadrature = SimplexLobattoQuadrature(nd,1)
#elementBoundaryQuadrature = SimplexLobattoQuadrature(nd-1,1)

#nn=3
#nLevels = 7
nn = 51
nLevels = 1
#subgridError = AdvectionDiffusionReaction_ASGS(coefficients,nd,stabFlag='1',lag=True)
subgridError = AdvectionDiffusionReactionTransientSubscales_ASGS(coefficients,nd,stabFlag='1',lag=True,trackSubScales=True,useHarariDirectly=False)
#subgridError = None

massLumping=False

shockCapturing = ResGrad_SC(coefficients,nd,shockCapturingFactor=0.2,lag=True)
#shockCapturing = ScalarAdvection_SC(coefficients,nd,shockCapturingFactor=0.99,lag=True)
#shockCapturing = None

multilevelNonlinearSolver  = NLNI
#multilevelNonlinearSolver  = Newton

levelNonlinearSolver = Newton
#levelNonlinearSolver = NLStarILU

fullNewtonFlag = True

tolFac = 0.001

nl_atol_res = 1.0e-8

matrix = SparseMatrix

multilevelLinearSolver = LU

levelLinearSolver = LU

linTolFac = 0.0001

conservativeFlux = None
