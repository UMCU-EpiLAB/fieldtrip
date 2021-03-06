#include "mex.h"
#include "matrix.h"
#include "math.h"
#include "stdlib.h"

/*  Copyright (C) 2009 Cesare Magri                                        */

/*
 * -------
 * LICENSE
 * -------
 * This software is distributed free under the condition that:
 *
 * 1. it shall not be incorporated in software that is subsequently sold;
 *
 * 2. the authorship of the software shall be acknowledged and the following
 *    article shall be properly cited in any publication that uses results
 *    generated by the software:

 *      Magri C, Whittingstall K, Singh V, Logothetis NK, Panzeri S: A
 *      toolbox for the fast information analysis of multiple-site LFP, EEG
 *      and spike train recordings. BMC Neuroscience 2009 10(1):81;
 * 3.  this notice shall remain in place in each source file.
 */

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    /* Input:                                                            */
    double *R;
    double *nt;
    
    /* Dimensions or R:                                                  */
    mwSize Nc, Nt, Ns;
    
    /* Indexes:                                                          */
    mwIndex c, t, s;
    mwIndex r;
    mwIndex xyz_current;
    mwIndex xyz_random;
    
    /* Output:                                                           */
    double *Rsh;
    
    /*
     * --------------------------------------------------------------------
     * The routine is based on the following simple algorithm for permuting
     * an array (i.e., any ordering of the array is equally probable or any
     * element has equal chance of being in any position):
     *
     *      For i=1 to n-1:
     *      - Let j=r(i+1)
     *      - Swap a[i] and a[j]
     *
     * where r[n] is a rand number generated between 0 and n-1.
     * --------------------------------------------------------------------
     */
    
    R  = mxGetPr(prhs[0]);
    nt = mxGetPr(prhs[1]);
    
    /* Get dimensions of R:                                              */
    Nc = mxGetDimensions(prhs[0])[0];
    Nt = mxGetDimensions(prhs[0])[1];
    Ns = mxGetDimensions(prhs[0])[2];
    
    plhs[0] = mxCreateNumericArray(3, mxGetDimensions(prhs[0]), mxDOUBLE_CLASS, 0);
    Rsh = mxGetPr(plhs[0]);
    
    for(s=0;s<Ns;s++)
    {      
        /* For t = 1 to nt[s]-1                                          */
        for(t=0;t<nt[s];t++)
        {
            for(c=0;c<Nc;c++)
            {
                /* Generating random number between 0 and t              */
                r = rand() % (t+1);
                
                /* Swapping Rsh[c, t, s] and Rsh[c, r, s]:               */
                xyz_current = c + t*Nc + s*Nc*Nt;
                xyz_random  = c + r*Nc + s*Nc*Nt;
                
                Rsh[xyz_current] = Rsh[xyz_random];
                Rsh[xyz_random]  = R[xyz_current];
            }
        }
    }
}