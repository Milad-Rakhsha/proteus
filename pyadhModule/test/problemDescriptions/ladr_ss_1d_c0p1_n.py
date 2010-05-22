from pyadh import *
from pyadh.default_n import *
from ladr_ss_1d_p import *

timeIntegration = NoIntegration
timeIntegrator = ForwardIntegrator
runCFL = 0.9
DT=1.0
#femSpaces = {0:C0_AffineLinearOnSimplexWithNodalBasis}
femSpaces = {0:C0_AffineQuadraticOnSimplexWithNodalBasis}
#femSpaces = {0:DG_AffineP0_OnSimplexWithMonomialBasis}
#femSpaces = {0:DG_AffineP1_OnSimplexWithMonomialBasis}
#femSpaces = {0:DG_AffineP5_OnSimplexWithMonomialBasis}
#femSpaces = {0:DG_Constants}
#femSpaces = {0:DG_AffineLinearOnSimplexWithNodalBasis}
#femSpaces = {0:DG_AffineQuadraticOnSimplexWithNodalBasis}

# femSpaces = {0:DG_AffineP0_OnSimplexWithMonomialBasis}
# elementQuadrature = SimplexGaussQuadrature(nd,1)
# elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,1)

#femSpaces = {0:DG_AffineP1_OnSimplexWithMonomialBasis}
#femSpaces = {0:DG_AffineLinearOnSimplexWithNodalBasis}
elementQuadrature = SimplexGaussQuadrature(nd,5)
elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,5)

# femSpaces = {0:DG_AffineP2_OnSimplexWithMonomialBasis}
# femSpaces = {0:DG_AffineQuadraticOnSimplexWithNodalBasis}
# elementQuadrature = SimplexGaussQuadrature(nd,3)
# elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,3)

# femSpaces = {0:DG_AffineP3_OnSimplexWithMonomialBasis}
# elementQuadrature = SimplexGaussQuadrature(nd,4)
# elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,4)

# femSpaces = {0:DG_AffineP4_OnSimplexWithMonomialBasis}
# elementQuadrature = SimplexGaussQuadrature(nd,5)
# elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,5)

#femSpaces = {0:DG_AffineP5_OnSimplexWithMonomialBasis}
#elementQuadrature = SimplexGaussQuadrature(nd,6)
#elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,6)

nn=11
nLevels = 1

subgridError = None
subgridError = AdvectionDiffusionReaction_ASGS(coefficients,nd,lag=False,stabFlag='p')

massLumping = False

shockCapturing = None

numericalFluxType = None
#numericalFluxType = Advection_DiagonalUpwind_Diffusion_IIPG_exterior
#numericalFluxType = Advection_DiagonalUpwind_Diffusion_IIPG
#numericalFluxType = Advection_DiagonalUpwind_Diffusion_LDG
#numericalFluxType = Advection_DiagonalUpwind

# femSpaces = {0:C0_AffineLinearOnSimplexWithNodalBasis}
# elementQuadrature = SimplexGaussQuadrature(nd,2)
# elementBoundaryQuadrature = SimplexGaussQuadrature(nd-1,2)
# numericalFluxType = None


#multilevelNonlinearSolver  = NLNI
multilevelNonlinearSolver  = Newton
#multilevelNonlinearSolver  = NLStarILU
#multilevelNonlinearSolver  = NLJacobi
#multilevelNonlinearSolver  = NLGaussSeidel

levelNonlinearSolver = Newton
#levelNonlinearSolver  = NLStarILU

nonlinearSmoother = NLGaussSeidel

fullNewtonFlag = True
#fullNewtonFlag = False

tolFac = 0.0#1.0e-8

nl_atol_res = 1.0e-8

maxNonlinearIts =10001

matrix = SparseMatrix
#matrix = Numeric.array

multilevelLinearSolver = NI
#multilevelLinearSolver = StarILU
#multilevelLinearSolver = GaussSeidel
#multilevelLinearSolver = Jacobi
multilevelLinearSolver = LU

levelLinearSolver = LU
#levelLinearSolver = GaussSeidel
#levelLinearSolver = StarILU
#levelLinearSolver = MGM
#computeEigenvalues=True

linearSmoother = StarILU#GaussSeidel

linTolFac = 0.001

conservativeFlux = None
