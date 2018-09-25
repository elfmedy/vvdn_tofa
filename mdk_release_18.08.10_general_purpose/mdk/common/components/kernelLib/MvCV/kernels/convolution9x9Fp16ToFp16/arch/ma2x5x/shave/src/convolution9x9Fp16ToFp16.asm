///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief
///

.type mvcvConvolution9x9Fp16ToFp16_asm,@function
.version 00.51.05

.data .data.convolution9x9Fp16ToFp16
.align 16

.code .text.convolution9x9Fp16ToFp16

//void Convolution9x9Fp16ToFp16_asm(u8** in(i18), u8** out(i17), half conv[49](i16), u32 inWidth(i15))
mvcvConvolution9x9Fp16ToFp16_asm:
	
	IAU.SUB i19 i19 8		|| LSU0.LDIL i10 convolution9x9Fp16ToFp16_loop	|| LSU1.LDIH i10 convolution9x9Fp16ToFp16_loop
	LSU0.ST.64.L v24  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDi.64 i0 i18	
	LSU0.ST.64.H v24  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDi.64 i2 i18	
	LSU0.ST.64.L v25  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDi.64 i4 i18		
	LSU0.ST.64.H v25  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDi.64 i6 i18
	LSU0.ST.64.L v26  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDi.32 i8 i18	
	LSU0.ST.64.H v26  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDo.64.l v10 i16 0x00
	LSU0.ST.64.L v27  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDo.64.h v10 i16 0x08
	LSU0.ST.64.H v27  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDo.64.l v11 i16 0x10
	LSU0.ST.64.L v28  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDo.64.h v11 i16 0x18		|| SAU.SUB.i32 i12 i12 i12
	LSU0.ST.64.H v28  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDo.64.l v12 i16 0x20		|| SAU.SUB.i32 i11 i11 i11
	LSU0.ST.64.L v30  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDo.64.h v12 i16 0x28		|| SAU.SHR.i32 i15 i15 3
	LSU0.ST.64.H v30  i19  	|| IAU.SUB i19 i19 8		|| LSU1.LDo.64.l v13 i16 0x30		|| SAU.SUB.i32 i0 i0 16
	LSU0.ST.64.L v29  i19								|| LSU1.LDo.64.h v13 i16 0x38		|| IAU.SUB i1 i1 16
	
	
	
	LSU0.LDo.64.l v14 i16 0x40							|| LSU1.LDo.64.h v14 i16 0x48		|| IAU.SUB i2 i2 16	 									
	LSU0.LDo.64.l v15 i16 0x50							|| LSU1.LDo.64.h v15 i16 0x58 		|| IAU.SUB i3 i3 16
	LSU0.LDo.64.l v16 i16 0x60							|| LSU1.LDo.64.h v16 i16 0x68		|| IAU.SUB i4 i4 16
	LSU0.LDo.64.l v17 i16 0x70							|| LSU1.LDo.64.h v17 i16 0x78		|| IAU.SUB i5 i5 16
	LSU0.LDo.64.l v18 i16 0x80							|| LSU1.LDo.64.h v18 i16 0x88		|| IAU.SUB i6 i6 16
	LSU0.LDo.64.l v19 i16 0x90							|| LSU1.LDo.64.h v19 i16 0x98		|| IAU.SUB i7 i7 16	 
	LSU0.LDo.64.l v29 i16 0xA0							|| LSU1.LD.32 i17 i17				|| IAU.SUB i8 i8 16

				
	LSU0.LD.64.L  v0  i0	|| LSU1.LDO.64.H v0 i0 0x08	|| IAU.ADD i0 i0 16	
	LSU0.LD.64.L  v1  i1	|| LSU1.LDO.64.H v1 i1 0x08 || IAU.ADD i1 i1 16
	LSU0.LD.64.L  v2  i2	|| LSU1.LDO.64.H v2 i2 0x08 || IAU.ADD i2 i2 16
	LSU0.LD.64.L  v3  i3	|| LSU1.LDO.64.H v3 i3 0x08 || IAU.ADD i3 i3 16
	LSU0.LD.64.L  v4  i4	|| LSU1.LDO.64.H v4 i4 0x08 || IAU.ADD i4 i4 16
	LSU0.LD.64.L  v5  i5	|| LSU1.LDO.64.H v5 i5 0x08 || IAU.ADD i5 i5 16
	LSU0.LD.64.L  v6  i6	|| LSU1.LDO.64.H v6 i6 0x08 || IAU.ADD i6 i6 16
	LSU0.LD.64.L  v7  i7	|| LSU1.LDO.64.H v7 i7 0x08 || IAU.ADD i7 i7 16
	LSU0.LD.64.L  v8  i8	|| LSU1.LDO.64.H v8 i8 0x08 || IAU.ADD i8 i8 16
	
	LSU0.LD.64.L  v20 i0	|| LSU1.LDO.64.H v20 i0 0x08	|| IAU.ADD i0 i0 16 
	LSU0.LD.64.L  v21 i1	|| LSU1.LDO.64.H v21 i1 0x08 	|| IAU.ADD i1 i1 16
	LSU0.LD.64.L  v22 i2	|| LSU1.LDO.64.H v22 i2 0x08	|| IAU.ADD i2 i2 16
	LSU0.LD.64.L  v23 i3	|| LSU1.LDO.64.H v23 i3 0x08	|| IAU.ADD i3 i3 16
	LSU0.LD.64.L  v24 i4	|| LSU1.LDO.64.H v24 i4 0x08	|| IAU.ADD i4 i4 16
	LSU0.LD.64.L  v25 i5	|| LSU1.LDO.64.H v25 i5 0x08	|| IAU.ADD i5 i5 16
	LSU0.LD.64.L  v26 i6	|| LSU1.LDO.64.H v26 i6 0x08	|| IAU.ADD i6 i6 16
	LSU0.LD.64.L  v27 i7	|| LSU1.LDO.64.H v27 i7 0x08 	|| IAU.ADD i7 i7 16
	LSU0.LD.64.L  v20 i0    || LSU1.LDO.64.H v20 i0 0x08	|| IAU.ADD i0 i0 16 	//!!!!!!!!!!!!!!!
	LSU0.LD.64.L  v28 i8	|| LSU1.LDO.64.H v28 i8 0x08	|| IAU.ADD i8 i8 16

	CMU.ALIGNVEC v9 v0 v20 8
	
	VAU.MACPZ.f16 v10 v9	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v0 v20 10	|| BRU.RPL i10 i15
	VAU.MACP.f16  v10 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v0 v20 12
	VAU.MACP.f16  v10 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v0 v20 14
	VAU.MACP.f16  v10 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.CPVV v0 v20
	VAU.MACP.f16  v10 v0 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v0 v20  2    
	VAU.MACP.f16  v10 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v0 v20  4    
	VAU.MACP.f16  v10 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v0 v20  6	|| LSU1.LDXV v21  i1 || iau.add i1 i1 16
	VAU.MACP.f16  v10 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v0 v20  8

	VAU.MACP.f16  v11 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v1 v21 8
	VAU.MACP.f16  v11 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v1 v21 10
	VAU.MACP.f16  v11 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v1 v21 12
	VAU.MACP.f16  v11 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v1 v21 14
	VAU.MACP.f16  v11 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.CPVV v1 v21
	VAU.MACP.f16  v11 v1 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v1 v21 2
	VAU.MACP.f16  v11 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v1 v21 4		
	VAU.MACP.f16  v11 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v1 v21 6		|| LSU1.LDXV v22  i2 || iau.add i2 i2 16	
	
	VAU.MACP.f16  v12 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v1 v21 8
	VAU.MACP.f16  v12 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v2 v22 8
	VAU.MACP.f16  v12 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v2 v22 10
	VAU.MACP.f16  v12 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v2 v22 12
	VAU.MACP.f16  v12 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v2 v22 14
	VAU.MACP.f16  v12 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.CPVV v2 v22
	VAU.MACP.f16  v12 v2 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v2 v22 2
	VAU.MACP.f16  v12 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v2 v22 4
	
	VAU.MACP.f16  v13 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v2 v22 6		|| LSU1.LDXV v23  i3 || iau.add i3 i3 16	
	VAU.MACP.f16  v13 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v2 v22 8
	VAU.MACP.f16  v13 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v3 v23 8
	VAU.MACP.f16  v13 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v3 v23 10
	VAU.MACP.f16  v13 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v3 v23 12
	VAU.MACP.f16  v13 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v3 v23 14
	VAU.MACP.f16  v13 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.CPVV v3 v23
	VAU.MACP.f16  v13 v3 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v3 v23 2
	
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v3 v23 4
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v3 v23 6	 	|| LSU1.LDXV v24  i4 || iau.add i4 i4 16	
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v3 v23 8
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v4 v24 8
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v4 v24 10
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v4 v24 12
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v4 v24 14
	VAU.MACP.f16  v14 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.CPVV v4 v24
	
	VAU.MACP.f16  v15 v4 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v4 v24 2
	VAU.MACP.f16  v15 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v4 v24 4
	VAU.MACP.f16  v15 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v4 v24 6		|| LSU1.LDXV v25  i5 || iau.add i5 i5 16		
	VAU.MACP.f16  v15 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v4 v24 8
	VAU.MACP.f16  v15 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v5 v25 8
	VAU.MACP.f16  v15 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v5 v25 10
	VAU.MACP.f16  v15 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v5 v25 12
	VAU.MACP.f16  v15 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v5 v25 14
	
	VAU.MACP.f16  v16 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.CPVV v5 v25
	VAU.MACP.f16  v16 v5 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v5 v25 2
	VAU.MACP.f16  v16 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v5 v25 4
	VAU.MACP.f16  v16 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v5 v25 6		|| LSU1.LDXV v26  i6 || iau.add i6 i6 16		
	VAU.MACP.f16  v16 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v5 v25 8
	VAU.MACP.f16  v16 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v6 v26 8
	VAU.MACP.f16  v16 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v6 v26 10
	VAU.MACP.f16  v16 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v6 v26 12	
	
	VAU.MACP.f16  v17 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v6 v26 14
	VAU.MACP.f16  v17 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.CPVV v6 v26
	VAU.MACP.f16  v17 v6 	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v6 v26 2
	VAU.MACP.f16  v17 v9 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v6 v26 4
	VAU.MACP.f16  v17 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v6 v26 6		|| LSU1.LDXV v27  i7 || iau.add i7 i7 16
	VAU.MACP.f16  v17 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v6 v26 8
	VAU.MACP.f16  v17 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v7 v27 8
	VAU.MACP.f16  v17 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v7 v27 10		
															
	VAU.MACP.f16  v18 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v7 v27 12
	VAU.MACP.f16  v18 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v7 v27 14
	VAU.MACP.f16  v18 v9 	|| LSU0.SWZV8 [22222222]	|| CMU.CPVV v7 v27
	VAU.MACP.f16  v18 v7 	|| LSU0.SWZV8 [33333333]	|| CMU.ALIGNVEC v9 v7 v27 2
	VAU.MACP.f16  v18 v9 	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v7 v27 4
	VAU.MACP.f16  v18 v9 	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v7 v27 6		 || LSU1.LDXV v28  i8 || iau.add i8 i8 16	
	VAU.MACP.f16  v18 v9 	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v7 v27 8
	VAU.MACP.f16  v18 v9 	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v8 v28 8
	
	VAU.MACP.f16  v19 v9 	|| LSU0.SWZV8 [00000000]	|| CMU.ALIGNVEC v9 v8 v28 10
	VAU.MACP.f16  v19 v9 	|| LSU0.SWZV8 [11111111]	|| CMU.ALIGNVEC v9 v8 v28 12	
	VAU.MACP.f16  v19 v9	|| LSU0.SWZV8 [22222222]	|| CMU.ALIGNVEC v9 v8 v28 14
	VAU.MACP.f16  v19 v9	|| LSU0.SWZV8 [33333333]	|| CMU.CPVV v8 v28
	VAU.MACP.f16  v19 v8	|| LSU0.SWZV8 [44444444]	|| CMU.ALIGNVEC v9 v8 v28 2
	VAU.MACP.f16  v19 v9	|| LSU0.SWZV8 [55555555]	|| CMU.ALIGNVEC v9 v8 v28 4
	VAU.MACP.f16  v19 v9	|| LSU0.SWZV8 [66666666]	|| CMU.ALIGNVEC v9 v8 v28 6
	VAU.MACP.f16  v19 v9	|| LSU0.SWZV8 [77777777]	|| CMU.ALIGNVEC v9 v8 v28 8
	
	VAU.MACPW.f16 v30 v29 v9 || LSU0.SWZV8 [00000000]		
	NOP 2
	
convolution9x9Fp16ToFp16_loop:
.nowarn 10
	CMU.CMII.i32 i11 i12
.nowarnend
	PEU.PC1C NEQ 			|| LSU0.ST.64.L v30 i17 	|| LSU1.STO.64.H v30 i17 0x08	|| IAU.ADD i17 i17 16
	IAU.ADD  i11 i11 1
	NOP 
	LSU0.LD.64.L v20 i0      || LSU1.LDO.64.H v20 i0 0x08	||	IAU.ADD i0 i0 16
	CMU.ALIGNVEC v9 v0 v20 8
	NOP
	
	
	LSU0.ST.64.L v30 i17 	|| LSU1.STO.64.H v30 i17 0x08	|| IAU.ADD i17 i17 16


	LSU0.LD.64.L  v29  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.H  v30  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.L  v30  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.H  v28  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.L  v28  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.H  v27  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.L  v27  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.H  v26  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.L  v26  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.H  v25  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.L  v25  i19 || IAU.ADD i19 i19 8
	LSU0.LD.64.H  v24  i19 || IAU.ADD i19 i19 8    
	LSU0.LD.64.L  v24  i19 || IAU.ADD i19 i19 8

	BRU.JMP i30	
	NOP 6
	
.size mvcvConvolution9x9Fp16ToFp16_asm,.-mvcvConvolution9x9Fp16ToFp16_asm
.end
