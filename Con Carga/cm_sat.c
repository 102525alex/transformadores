/*
 * cm_sat.c Singe Coil Magnetic Circuit with core saturation  
 * Author: Alberto Sanchez
 * 28/01/2021
 *
 * ver 1.0
 *
 * Modify by Alex Andrade 2022
 * ver 2.0 20/01/2021
 * Model Description in this version. 
 * States:  x = [Psi]
 * Inputs:  u = [v DeltaPsim]
 * Outputs: y = [i e Psi Psimsat]
 *
 * PAR = [wb r xl xm]
 *
 * 
 *
 */

#define S_FUNCTION_NAME cm_sat

#include "simstruc.h"
#include <math.h>

#define XINIT   ssGetArg(S,0)
#define PAR	ssGetArg(S,1)

/*
 * mdlInitializeSizes - initialize the sizes array
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumContStates(S, 2);       /* number of continuous states           */
    ssSetNumDiscStates(S, 0);       /* number of discrete states             */
    ssSetNumInputs(S, 3);           /* number of inputs                      */
    ssSetNumOutputs(S, 7);          /* number of outputs                     */
    ssSetDirectFeedThrough(S, 1);   /* direct feedthrough flag               */
    ssSetNumSampleTimes(S, 1);      /* number of sample times                */
    ssSetNumSFcnParams(S, 2);       /* number of input arguments             */
    ssSetNumRWork(S, 0);            /* number of real work vector elements   */
    ssSetNumIWork(S, 0);            /* number of integer work vector elements*/
    ssSetNumPWork(S, 0);            /* number of pointer work vector elements*/
}

/*
 * mdlInitializeSampleTimes - initialize the sample times array
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}


/*
 * mdlInitializeConditions - initialize the states
 */
static void mdlInitializeConditions(double *x0, SimStruct *S)
{
x0[0] = mxGetPr(XINIT)[0];
}

/*
 * mdlOutputs - compute the outputs
 */

static void mdlOutputs(double *y, double *x, double *u, SimStruct *S, int tid)
{
double wb,r1,rp2,xl1,xlp2,xm;
double XM_n,XM_d;
double XM,i1,ip2,Psimsat;

wb = mxGetPr(PAR)[0];
r1 = mxGetPr(PAR)[1];
rp2 = mxGetPr(PAR)[2];
xl1 = mxGetPr(PAR)[3];
xlp2 = mxGetPr(PAR)[4];
xm = mxGetPr(PAR)[5];

XM_n = xm*xlp2*xl1;
XM_d = xlp2*xl1+xm*xl1+xm*xlp2;
XM = XM_n/XM_d;

Psimsat = XM*(x[0]/xl1+x[1]/xlp2-u[2]/xm);

i1 = (x[0]-Psimsat)/xl1;
ip2 = (x[1]-Psimsat)/xlp2;

//Outputs: y = [i1 ip2 fem1 fem2 psi1 psi2 Psimsat]
y[0] = i1;
y[1] = ip2;
y[2] = u[0]-r1*((x[0]-Psimsat)/xl1); //fem 1
y[3] = u[1]-rp2*((x[1]-Psimsat)/xlp2); //fem 2
y[4] = x[0];
y[5] = x[1];
y[6] = Psimsat;
}

/*
 * mdlUpdate - perform action at major integration time step
 */

static void mdlUpdate(double *x, double *u, SimStruct *S, int tid)
{
}

/*
 * mdlDerivatives - compute the derivatives
 */
static void mdlDerivatives(double *dx, double *x, double *u, SimStruct *S, int tid)
{
double wb,r1,rp2,xl1,xlp2,xm;
double XM_n,XM_d;
double XM,i1,ip2,Psimsat;

wb = mxGetPr(PAR)[0];
r1 = mxGetPr(PAR)[1];
rp2 = mxGetPr(PAR)[2];
xl1 = mxGetPr(PAR)[3];
xlp2 = mxGetPr(PAR)[4];
xm = mxGetPr(PAR)[5];

XM_n = xm*xlp2*xl1;
XM_d = xlp2*xl1+xm*xl1+xm*xlp2;
XM = XM_n/XM_d;

Psimsat = XM*(x[0]/xl1+x[1]/xlp2-u[2]/xm);

dx[0] = wb*(u[0]-r1*((x[0]-Psimsat)/xl1));
dx[1] = wb*(u[1]-rp2*((x[1]-Psimsat)/xlp2));
}


/*
 * mdlTerminate - called when the simulation is terminated.
 */
static void mdlTerminate(SimStruct *S)
{
}

#ifdef	MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
