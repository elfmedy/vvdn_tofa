///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief
///

.type mvcvConvolution11x11s2xxhx_asm,@function
.version 00.51.05

.code .text.convolution11x11s2xxhx

//void Convolution11x11s2xxhx_asm(u8** in(i18), u8** out(i17), u8 conv[121](i16), u32 inWidth(i15))
mvcvConvolution11x11s2xxhx_asm:

	IAU.SUB i19 i19 8
	LSU0.ST.64.l v24  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v24  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.l v25  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v25  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.l v26  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v26  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.l v27  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v27  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.l v28  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v28  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.l v29  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v29  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.l v30  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v30  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.l v31  i19  || IAU.SUB i19 i19 8
	LSU0.ST.64.h v31  i19  

        LSU1.LD.32 i17 i17
	LSU1.LDi.64  i0   i18
	LSU1.LDi.64  i2   i18
	LSU1.LDi.64  i4   i18
	LSU1.LDi.64  i6   i18
	LSU1.LDi.64  i8   i18
	LSU1.LDi.64  i10  i18
	LSU1.LDi.128.u8.f16 v24 i16
	LSU1.LDi.128.u8.f16 v25 i16
        LSU1.LDi.128.u8.f16 v26 i16
        LSU1.LDi.128.u8.f16 v27 i16
	LSU1.LDi.128.u8.f16 v28 i16
	LSU1.LDi.128.u8.f16 v29 i16
	LSU1.LDi.128.u8.f16 v30 i16
	LSU1.LDi.128.u8.f16 v31 i16
       
        LSU0.ST.64.H v31  i19	
	IAU.SUB i0  i0  8									
	IAU.SUB i1  i1  8		
	IAU.SUB i2  i2  8	|| LSU0.LDi.128.u8f.f16 v0  i0 
	IAU.SUB i3  i3  8	|| LSU0.LDi.128.u8f.f16 v1  i1
	IAU.SUB i4  i4  8	|| LSU0.LDi.128.u8f.f16 v2  i2
	IAU.SUB i5  i5  8	|| LSU0.LDi.128.u8f.f16 v3  i3
	IAU.SUB i6  i6  8	|| LSU0.LDi.128.u8f.f16 v4  i4
	IAU.SUB i7  i7  8       || LSU0.LDi.128.u8f.f16 v5  i5
	IAU.SUB i8  i8  8       || LSU0.LDi.128.u8f.f16 v6  i6
	IAU.SUB i9  i9  8       || LSU0.LDi.128.u8f.f16 v7  i7
	IAU.SUB i10 i10 8       || LSU0.LDi.128.u8f.f16 v8  i8
	IAU.SHR.i32 i12 i15 3	|| LSU0.LDi.128.u8f.f16 v9  i9
							   LSU0.LDi.128.u8f.f16 v10 i10	
							   LSU0.LDi.128.u8f.f16 v11 i0	
							   LSU0.LDi.128.u8f.f16 v12 i1	
							   LSU0.LDi.128.u8f.f16 v13 i2	
							   LSU0.LDi.128.u8f.f16 v14 i3	
							   LSU0.LDi.128.u8f.f16 v15 i4	
							   LSU0.LDi.128.u8f.f16 v16 i5	
							   LSU0.LDi.128.u8f.f16 v17 i6	
							   LSU0.LDi.128.u8f.f16 v18 i7	
							   LSU0.LDi.128.u8f.f16 v19 i8	
							   LSU0.LDi.128.u8f.f16 v20 i9	|| LSU1.LDi.128.u8f.f16 v11 i0
							   LSU0.LDi.128.u8f.f16 v21 i10	|| CMU.ALIGNVEC v22 v0 v11 6
	
	
 convolution11x11s2xxhx_loop:
 .nowarn 10
        
	VAU.MACPZ.f16 v24 v22	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v0 v11 8	
 .nowarnend
	VAU.MACP.f16  v24 v22	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v0 v11 10
	VAU.MACP.f16  v24 v22	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v0 v11 12
	VAU.MACP.f16  v24 v22	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v0 v11 14
	VAU.MACP.f16  v24 v22	|| LSU0.SWZV8 [44444444]	|| CMU.CPVV v0 v11
	VAU.MACP.f16  v24 v0 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v0 v11 2
	VAU.MACP.f16  v24 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v0 v11 4
	VAU.MACP.f16  v24 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v0 v11 6
	
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v0 v11 8
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v0 v11 10	|| LSU1.LDi.128.u8f.f16 v12 i1
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v1 v12 6
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v1 v12 8
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v1 v12 10
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v1 v12 12
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v1 v12 14
	VAU.MACP.f16  v25 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.CPVV v1 v12
	
	VAU.MACP.f16  v26 v1 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v1 v12 2
	VAU.MACP.f16  v26 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v1 v12 4
	VAU.MACP.f16  v26 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v1 v12 6
	VAU.MACP.f16  v26 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v1 v12 8
	VAU.MACP.f16  v26 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v1 v12 10	|| LSU1.LDi.128.u8f.f16 v13 i2
	VAU.MACP.f16  v26 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v2 v13 6
	VAU.MACP.f16  v26 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v2 v13 8
	VAU.MACP.f16  v26 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v2 v13 10
	
	VAU.MACP.f16  v27 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v2 v13 12
	VAU.MACP.f16  v27 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v2 v13 14
	VAU.MACP.f16  v27 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.CPVV v2 v13
	VAU.MACP.f16  v27 v2 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v2 v13 2
	VAU.MACP.f16  v27 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v2 v13 4
	VAU.MACP.f16  v27 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v2 v13 4
	VAU.MACP.f16  v27 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v2 v13 8
	VAU.MACP.f16  v27 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v2 v13 10	|| LSU1.LDi.128.u8f.f16 v14 i3
	
	VAU.MACP.f16  v28 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v3 v14 6
	VAU.MACP.f16  v28 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v3 v14 8
	VAU.MACP.f16  v28 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v3 v14 10
	VAU.MACP.f16  v28 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v3 v14 12
	VAU.MACP.f16  v28 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v3 v14 14
	VAU.MACP.f16  v28 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.CPVV v3 v14
	VAU.MACP.f16  v28 v3 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v3 v14 2
	VAU.MACP.f16  v28 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v3 v14 4
	
	VAU.MACP.f16  v29 v22	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v3 v14 6
	VAU.MACP.f16  v29 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v3 v14 8
	VAU.MACP.f16  v29 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v3 v14 10	|| LSU1.LDi.128.u8f.f16 v15 i4
	VAU.MACP.f16  v29 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v4 v15 6
	VAU.MACP.f16  v29 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v4 v15 8
	VAU.MACP.f16  v29 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v4 v15 10
	VAU.MACP.f16  v29 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v4 v15 12
	VAU.MACP.f16  v29 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v4 v15 14
	
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.CPVV v4 v15
	VAU.MACP.f16  v30 v4 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v4 v15 2 
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v4 v15 4 
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v4 v15 6 
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v4 v15 8 
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v4 v15 10 	|| LSU1.LDi.128.u8f.f16 v16 i5
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v5 v16 6 
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v5 v16 8 
	
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v5 v16 10	|| LSU1.LDi.128.u8.f16 v30 i16	
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v5 v16 12   
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v5 v16 14 
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.CPVV v5 v16
	VAU.MACP.f16  v31 v5 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v5 v16 2
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v5 v16 4
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v5 v16 6	|| LSU1.LDi.128.u8.f16 v31 i16
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v5 v16 8

	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v5 v16 10	|| LSU1.LDi.128.u8.f16 v17 i6
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v6 v17 6    
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v6 v17 8
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v6 v17 10
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v6 v17 12
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v6 v17 14
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.CPVV v6 v17
	VAU.MACP.f16  v30 v6 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v6 v17 2
	
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v6 v17 4	||LSU1.LDi.128.u8.f16 v30 i16
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v6 v17 6 
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v6 v17 8
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v6 v17 10	|| LSU1.LDi.128.u8.f16 v18 i7
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v7 v18 6
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v7 v18 8
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v7 v18 10
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v7 v18 12
	
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v7 v18 14	||LSU1.LDi.128.u8.f16 v31 i16
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.CPVV v7 v18
	VAU.MACP.f16  v30 v7 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v7 v18 2
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v7 v18 4
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v7 v18 6
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v7 v18 8
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v7 v18 10	|| LSU1.LDi.128.u8.f16 v19 i8
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v8 v19 6
	
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v8 v19 8	|| LSU1.LDi.128.u8.f16 v30 i16
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v8 v19 10   
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v8 v19 12
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v8 v19 14
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.CPVV v8 v19
	VAU.MACP.f16  v31 v8 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v8 v19 2
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v8 v19 4
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v8 v19 6	|| LSU1.LDi.128.u8.f16 v31 i16
                                                                                        
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v8 v19 8	
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v8 v19 10	|| LSU1.LDi.128.u8.f16 v20 i9
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v9 v20 6
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v9 v20 8
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v9 v20 10
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v9 v20 12
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v9 v20 14
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.CPVV v9 v20
	
	VAU.MACP.f16  v31 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v9  v20 2	|| LSU1.LDi.128.u8.f16 v30 i16
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v9  v20 4
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v22 v9  v20 6
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v9  v20 8
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v9  v20 10	|| LSU1.LDi.128.u8.f16 v21 i10
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v10 v21 6
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v10 v21 8
	VAU.MACP.f16  v31 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v10 v21 10
	
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v22 v10 v21 12	|| LSU1.LDi.128.u8.f16 v31 i16
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v22 v10 v21 14
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [22222222]	|| CMU.CPVV v10 v21
	VAU.MACP.f16  v30 v10 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v22 v10 v21 2
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v22 v10 v21 4
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v22 v10 v21 6
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v22 v10 v21 8
	VAU.MACP.f16  v30 v22 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v22 v10 v21 10
        VAU.MACPW.f16 v23 v31 v22 	|| LSU0.SWZV8 [00000000]
        nop 13
        CMU.VDILV.x16 v30 v23 v23 v23
        CMU.CPVV.f16.u8fs V30 V30
        nop
 	cmu.cpvi.x32 i11 v30.0
        LSU0.STi.32 i11 i17	|| IAU.SUB i15 i15 8
	
	PEU.PC1I NEQ || BRU.BRA convolution11x11s2xxhx_loop
        iau.incs i16 -64
        LSU1.LDi.128.u8.f16 v30 i16
	LSU1.LDi.128.u8.f16 v31 i16
        
        LSU0.LDi.128.u8f.f16 v11 i0
	CMU.ALIGNVEC v22 v0 v11 6
        nop 6
	
        LSU0.LD.64.h  v31  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v31  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.h  v30  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v30  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.h  v29  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v29  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.h  v28  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v28  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.h  v27  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v27  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.h  v26  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v26  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.h  v25  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v25  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.h  v24  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.l  v24  i19 || IAU.ADD i19 i19 8	

	
        nop 6
        BRU.jmp i30
	NOP 6



.size mvcvConvolution11x11s2xxhx_asm,.-mvcvConvolution11x11s2xxhx_asm
.end