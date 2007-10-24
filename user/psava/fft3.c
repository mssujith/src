/* 3-D FFT encapsulated */
/*
  Copyright (C) 2004 University of Texas at Austin
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <rsf.h>
/*^*/

#include "fft3.h"

static kiss_fft_cfg forw1, invs1;
static kiss_fft_cfg forw2, invs2;
static kiss_fft_cfg forw3, invs3;
static int n1, n2, n3;
static float fftscale;
static kiss_fft_cpx *trace2, *trace3;

#define LOOP1(a) for(i1=0;i1<n1;i1++){ {a} }
#define LOOP2(a) for(i2=0;i2<n2;i2++){ {a} }
#define LOOP3(a) for(i3=0;i3<n3;i3++){ {a} }

void fft3_init(int n1_, int n2_, int n3_)
/*< initialize >*/
{
    n1 = n1_; 
    n2 = n2_;
    n3 = n3_;

    forw1 = kiss_fft_alloc(n1,0,NULL,NULL);
    invs1 = kiss_fft_alloc(n1,1,NULL,NULL);

    forw2 = kiss_fft_alloc(n2,0,NULL,NULL);
    invs2 = kiss_fft_alloc(n2,1,NULL,NULL);

    forw3 = kiss_fft_alloc(n3,0,NULL,NULL);
    invs3 = kiss_fft_alloc(n3,1,NULL,NULL);
    
    if (NULL == forw1 || NULL == invs1 || 
	NULL == forw2 || NULL == invs2 ||
	NULL == forw3 || NULL == invs3) 
	sf_error("%s: KISS FFT allocation error",__FILE__);

    trace2 = (kiss_fft_cpx*) sf_complexalloc(n2);
    trace3 = (kiss_fft_cpx*) sf_complexalloc(n3);

    fftscale = 1./(n1*n2*n3);
}

void fft3_close(void)
/*< Free allocated storage >*/
{
    free (trace2);
    free (trace3);

    free (forw1);
    free (invs1);
    free (forw2);
    free (invs2);
    free (forw3);
    free (invs3);
}

void fft3(bool inv           /* inverse/forward flag */, 
	  kiss_fft_cpx ***pp /* [n1][n2][n3] */) 
/*< Apply 3-D FFT >*/
{
    int i1, i2, i3;
    
    if (inv) {

	/* IFT 1 */
	for (i3=0; i3 < n3; i3++) {
	    for (i2=0; i2 < n2; i2++) {
		kiss_fft(invs1,pp[i3][i2],pp[i3][i2]);
	    }
	}

	/* IFT 2 */
	for (i3=0; i3 < n3; i3++) {
	    for (i1=0; i1 < n1; i1++) {
		kiss_fft_stride(invs2,pp[i3][0]+i1,trace2,n1);
		for (i2=0; i2 < n2; i2++) {
		    pp[i3][i2][i1] = trace2[i2];
		}
	    }
	}
	
	/* IFT 3 */
	for (i2=0; i2 < n2; i2++) {
	    for (i1=0; i1 < n1; i1++) {
		kiss_fft_stride(invs3,pp[0][i2]+i1,trace3,n1);
		for (i3=0; i3 < n3; i3++) {
		    pp[i3][i2][i1] = trace3[i3];
		}
	    }
	}

	/* scaling */
	for (i3=0; i3 < n3; i3++) {
	    for (i2=0; i2 < n2; i2++) {
		for (i1=0; i1 < n1; i1++) {
		    pp[i3][i2][i1] = sf_crmul(pp[i3][i2][i1],fftscale);
		}
	    }
	}
	
    } else {
	/* FFT 3 */
	for (i2=0; i2 < n2; i2++) {
	    for (i1=0; i1 < n1; i1++) {
		kiss_fft_stride(forw3,pp[0][i2]+i1,trace3,n1);
		for (i3=0; i3 < n3; i3++) {
		    pp[i3][i2][i1] = trace3[i3];
		}
	    }
	}

	/* FFT 2 */
	for (i3=0; i3 < n3; i3++) {
	    for (i1=0; i1 < n1; i1++) {
		kiss_fft_stride(forw2,pp[i3][0]+i1,trace2,n1);
		for (i2=0; i2 < n2; i2++) {
		    pp[i3][i2][i1] = trace2[i2];
		}
	    }
	}

	/* FFT 1 */
	for (i3=0; i3 < n3; i3++) {
	    for (i2=0; i2 < n2; i2++) {
		kiss_fft(forw1,pp[i3][i2],pp[i3][i2]);
	    }
	}
    }
}
