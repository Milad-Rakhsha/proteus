from proteus import *
from proteus.default_p import *
from proteus import ADR

LevelModelType = ADR.LevelModel

"""
Linear advection-diffusion-reaction at equilibrium in 2D.
"""

## \page Tests Test Problems 
# \ref ladr_ss_2d_p.py "Linear advection-diffusion-reaction at steady state"
#

##\ingroup test
#\file ladr_ss_2d_p.py
#
#\brief Linear advection-diffusion-reaction at equilibrium in 1D.
#\todo finish ladr_ss_2d_p.py doc

nd = 2
L=(1.0,1.0,1.0)

a0=0.01
b0=1.0
A0_1c={0:numpy.array([[a0,0],[0,a0]])}
B0_1c={0:numpy.array([0.0,b0])}
C0_1c={0:0.0}
M0_1c={0:0.0}

ans = AnalyticalSolutions.LinearAD_SteadyState(b=B0_1c[0][1],a=A0_1c[0][0,0])
analyticalSolution = {0:ans}
initialConditions = None

def a(x):
    return numpy.array([[a0,0.0],[0.0,a0]])
def f(x):
    return 0.0

aOfX = {0:a}; fOfX = {0:f}

coefficients = ADR.Coefficients(aOfX=aOfX,fOfX=fOfX,velocity=B0_1c[0],nc=1,nd=nd,forceStrongDirichlet=False)

def getDBC(x,flag):
    if x[0] <= 1.0e-8 or x[1] <= 1.0e-8:
        return lambda x,t: 1.0 
    if x[0] >= 1.0 - 1.0e-8 or x[1] >= 1.0-1.0e-8:
        return lambda x,t: 0.0

dirichletConditions = {0:getDBC}

fluxBoundaryConditions = {0:'noFlow'}

def getFlux(x,flag):
    pass

advectiveFluxBoundaryConditions =  {0:getFlux}

diffusiveFluxBoundaryConditions = {0:{0:getFlux}}
