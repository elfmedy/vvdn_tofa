/*

   BLIS    
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2014, The University of Texas

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name of The University of Texas nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"
#include "mv_types.h"


#undef  GENTFUNC
#define GENTFUNC( ctype, ch, varname, kername ) \
\
void PASTEMAC(ch,varname)( \
                           ctype* restrict a, \
                           ctype* restrict b, \
                           ctype* restrict c, inc_t rs_c, inc_t cs_c, \
                           auxinfo_t*      data  \
                         ) \
{ \
    UNUSED(data); \
	const dim_t     m     = PASTEMAC(ch,mr); \
	const dim_t     n     = PASTEMAC(ch,nr); \
\
	const inc_t     rs_a  = 1; \
	const inc_t     cs_a  = PASTEMAC(ch,packmr); \
\
	const inc_t     rs_b  = PASTEMAC(ch,packnr); \
	const inc_t     cs_b  = 1; \
\
	dim_t           iter, i, j, l; \
	dim_t           n_behind; \
\
	ctype* restrict alpha11; \
	ctype* restrict a10t; \
	ctype* restrict alpha10; \
	ctype* restrict X0; \
	ctype* restrict x1; \
	ctype* restrict x01; \
	ctype* restrict chi01; \
	ctype* restrict chi11; \
	ctype* restrict gamma11; \
	ctype           rho11; \
\
	for ( iter = 0; iter < m; ++iter ) \
	{ \
		i        = iter; \
		n_behind = i; \
		alpha11  = a + (i  )*rs_a + (i  )*cs_a; \
		a10t     = a + (i  )*rs_a + (0  )*cs_a; \
		X0       = b + (0  )*rs_b + (0  )*cs_b; \
		x1       = b + (i  )*rs_b + (0  )*cs_b; \
\
		/* x1 = x1 - a10t * X0; */ \
		/* x1 = x1 / alpha11; */ \
		for ( j = 0; j < n; ++j ) \
		{ \
			x01     = X0 + (0  )*rs_b + (j  )*cs_b; \
			chi11   = x1 + (0  )*rs_b + (j  )*cs_b; \
			gamma11 = c  + (i  )*rs_c + (j  )*cs_c; \
\
			/* chi11 = chi11 - a10t * x01; */ \
			PASTEMAC(ch,set0s)( rho11 ); \
			for ( l = 0; l < n_behind; ++l ) \
			{ \
				alpha10 = a10t + (l  )*cs_a; \
				chi01   = x01  + (l  )*rs_b; \
\
				PASTEMAC(ch,axpys)( *alpha10, *chi01, rho11 ); \
			} \
			PASTEMAC(ch,subs)( rho11, *chi11 ); \
\
			/* chi11 = chi11 / alpha11; */ \
			/* NOTE: The INVERSE of alpha11 (1.0/alpha11) is stored instead
			   of alpha11, so we can multiply rather than divide. We store 
			   the inverse of alpha11 intentionally to avoid expensive
			   division instructions within the micro-kernel. */ \
			PASTEMAC(ch,scals)( *alpha11, *chi11 ); \
\
			/* Output final result to matrix C. */ \
			PASTEMAC(ch,copys)( *chi11, *gamma11 ); \
		} \
	} \
}

INSERT_GENTFUNC_BASIC( trsm_l_ref_mxn, trsm_l_ref_mxn )

