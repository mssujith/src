/* Chebyshev polynomial coefficients */
/*
  Copyright (C) 2022 University of Texas at Austin
   
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

#include "chebyshev.h"

int main (int argc, char* argv[])
{
    int nc;
    float *data;
    sf_file inp, out;

    sf_init(argc,argv);
    inp = sf_input("in");
    out = sf_output("out");

    if (SF_FLOAT != sf_gettype(inp)) sf_error("Need float input");
    if (!sf_histint(inp,"n1",&nc)) sf_error("No n1= in input");

    data = sf_floatalloc(nc);

    chebyshev_init(nc,-1.0,1.0);

    sf_floatread(data,nc,inp);
    chebyshev_set(data);
    chebyshev_poly(data);
    sf_floatwrite(data,nc,out);

    exit(0);
}
