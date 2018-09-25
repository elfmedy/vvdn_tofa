///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief apply a convolution 3x3 filter, in the case of symmetric kernel.
///

.type mvcvConvSeparable9x9_asm,@function
.version 00.51.04

.code .text.convSeparable9x9

//void convSeparable9x9_asm(u8** out(i18), u8** in(i17), fp32 conv[5](i16), u32 inWidth(i15))

mvcvConvSeparable9x9_asm: 
     IAU.SUB i19 i19 8
	 LSU0.ST.64.L v24  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v24  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.L v25  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v25  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.L v26  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v26  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.L v27  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v27  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.L v28  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v28  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.L v29  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v29  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.L v30  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v30  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.L v31  i19  || IAU.SUB i19 i19 8
	 LSU0.ST.64.H v31  i19  

	 lsu0.ldil i11 convSeparable9x9_loop  ||  lsu1.ldih i11 convSeparable9x9_loop
	 nop 6
	 LSU0.LDi.64 i0 i17
	 LSU0.LDi.64 i2 i17
	 LSU0.LDi.64 i4 i17  
	 LSU0.LDi.64 i6 i17 
	 LSU0.LDi.32 i8 i17 || LSU1.LD.32  i18  i18
	 
	 LSU0.LDO.64.L v20 i16 0x00	|| LSU1.LDO.64.H v20 i16 0x08
	 nop 6
	
	 cmu.cpvv.f32.f16 v20, v20 || iau.shr.u32 i10, i15, 3
	 cmu.cpvi.x16 i9.l v20.0    || iau.sub i0 i0 8
	 cmu.cpivr.x16 v21 i9 	    || iau.sub i1 i1 8  //conv[0]
	 cmu.cpvi.x16 i9.l v20.1    || iau.sub i2 i2 8
	 cmu.cpivr.x16 v22 i9 	    || iau.sub i3 i3 8  //conv[1]
	 cmu.cpvi.x16 i9.l v20.2    || iau.sub i4 i4 8
	 cmu.cpivr.x16 v23 i9 	    || iau.sub i5 i5 8  //conv[2]
	 cmu.cpvi.x16 i9.l v20.3    || iau.sub i6 i6 8
	 cmu.cpivr.x16 v24 i9 	    || iau.sub i7 i7 8  //conv[3]
	 LSU0.LDO.64.L v20 i16 0x10 || iau.sub i8 i8 8
	 nop 6
	 cmu.cpvv.f32.f16 v20, v20
	 cmu.cpvi.x16 i9.l v20.0 
	 cmu.cpivr.x16 v25 i9   //conv[4]
	 
	//-----------------------------------------------------------------
	
	 lsu0.ldi.128.u8f.f16 v0, i0 || lsu1.ldi.128.u8f.f16 v8, i8  
	 lsu0.ldi.128.u8f.f16 v1, i1 || lsu1.ldi.128.u8f.f16 v7, i7
	 lsu0.ldi.128.u8f.f16 v2, i2 || lsu1.ldi.128.u8f.f16 v6, i6 
	 lsu0.ldi.128.u8f.f16 v3, i3 || lsu1.ldi.128.u8f.f16 v5, i5 
	 lsu0.ldi.128.u8f.f16 v4, i4 
	 nop 2
		
	 vau.add.f16 v0 v0 v8  || lsu0.ldi.128.u8f.f16 v9, i0  || lsu1.ldi.128.u8f.f16 v17, i8 
	 vau.add.f16 v1 v1 v7  || lsu0.ldi.128.u8f.f16 v10, i1 || lsu1.ldi.128.u8f.f16 v16, i7
	 vau.add.f16 v2 v2 v6  || lsu0.ldi.128.u8f.f16 v11, i2 || lsu1.ldi.128.u8f.f16 v15, i6 
	 vau.add.f16 v3 v3 v5  || lsu0.ldi.128.u8f.f16 v12, i3 || lsu1.ldi.128.u8f.f16 v14, i5 
	 vau.mul.f16 v8 v0 v21 || lsu0.ldi.128.u8f.f16 v13, i4 
	 vau.mul.f16 v7 v1 v22 
	 vau.mul.f16 v6 v2 v23 
	 vau.mul.f16 v5 v3 v24 
	 vau.mul.f16 v4 v4 v25 
	 vau.add.f16 v0 v8 v7  
	 vau.add.f16 v1 v6 v5  
	 vau.add.f16 v9 v9 v17    || lsu0.ldi.128.u8f.f16 v0, i0 || lsu1.ldi.128.u8f.f16 v8, i8 //nop
	 vau.add.f16 v4 v4 v0 
	// nop 2
	 vau.add.f16 v10 v10 v16  || lsu0.ldi.128.u8f.f16 v1, i1 || lsu1.ldi.128.u8f.f16 v7, i7
	 vau.add.f16 v11 v11 v15  || lsu0.ldi.128.u8f.f16 v2, i2 || lsu1.ldi.128.u8f.f16 v6, i6 
	 
	 vau.add.f16 v26 v4 v1 
	vau.add.f16 v12 v12 v14  || lsu0.ldi.128.u8f.f16 v3, i3 || lsu1.ldi.128.u8f.f16 v5, i5 
	vau.mul.f16 v17 v9 v21   || lsu0.ldi.128.u8f.f16 v4, i4 
	vau.mul.f16 v16 v10 v22  
	vau.mul.f16 v15 v11 v23
	vau.mul.f16 v14 v12 v24
	vau.mul.f16 v13 v13 v25
	vau.add.f16 v9 v17 v16 
	vau.add.f16 v10 v15 v14 
	vau.add.f16 v0 v0 v8  //nop 
    vau.add.f16 v13 v13 v9
    //nop 2
	vau.add.f16 v1 v1 v7  
	vau.add.f16 v2 v2 v6 
	
	vau.add.f16 v27 v13 v10// 22222 

	vau.add.f16 v3 v3 v5                                            
	vau.mul.f16 v11 v0 v21                                  || lsu0.ldi.128.u8f.f16 v0, i0 || lsu1.ldi.128.u8f.f16 v8, i8       
	vau.mul.f16 v7 v1 v22                                   || lsu0.ldi.128.u8f.f16 v1, i1 || lsu1.ldi.128.u8f.f16 v7, i7      
	vau.mul.f16 v30 v2 v23                                  || lsu0.ldi.128.u8f.f16 v2, i2 || lsu1.ldi.128.u8f.f16 v6, i6       
	vau.mul.f16 v10 v3 v24  || cmu.alignvec v12 v26 v27 8   || lsu0.ldi.128.u8f.f16 v3, i3 || lsu1.ldi.128.u8f.f16 v5, i5       
	vau.mul.f16 v31 v4 v25  || cmu.alignvec v13 v26 v27 10  || lsu0.ldi.128.u8f.f16 v4, i4 
	vau.add.f16 v9 v11 v7  || cmu.alignvec v14 v26 v27 12
	vau.add.f16 v29 v30 v10   || cmu.alignvec v15 v26 v27 14
	nop
    vau.add.f16 v31 v31 v9
    nop 2
    vau.add.f16 v28 v31 v29// 333333
	nop 2
	
		
		vau.add.f16 v0 v0 v8 
		vau.add.f16 v1 v1 v7  
		vau.add.f16 v2 v2 v6  
		vau.add.f16 v3 v3 v5  
		vau.mul.f16 v8 v0 v21 
	 	vau.mul.f16 v7 v1 v22 
		vau.mul.f16 v6 v2 v23 || bru.rpl i11 i10
		vau.mul.f16 v5 v3 v24 
		vau.mul.f16 v4 v4 v25
		vau.add.f16 v7 v8 v7 
		vau.add.f16 v1 v6 v5
	vau.mul.f16 v9 v27 v25  || cmu.alignvec v16 v27 v28 8
	vau.add.f16 v10 v12 v16	|| cmu.alignvec v17 v27 v28 6
	vau.add.f16 v11 v13 v17 || cmu.alignvec v18 v27 v28 4
	vau.add.f16 v29 v14 v18 || cmu.alignvec v19 v27 v28 2 || lsu0.ldi.128.u8f.f16 v0, i0 || lsu1.ldi.128.u8f.f16 v8, i8 
	vau.add.f16 v30 v15 v19 || cmu.cpvv v26 v27           || lsu0.ldi.128.u8f.f16 v2, i2 || lsu1.ldi.128.u8f.f16 v6, i6         
		vau.add.f16 v4 v4 v7	
	vau.mul.f16 v10 v10 v21 || cmu.cpvv v27 v28			  || lsu0.ldi.128.u8f.f16 v3, i3 || lsu1.ldi.128.u8f.f16 v5, i5
	vau.mul.f16 v11 v11 v22 || cmu.alignvec v12 v26 v27 8 || lsu0.ldi.128.u8f.f16 v1, i1 || lsu1.ldi.128.u8f.f16 v7, i7
		vau.add.f16 v28 v4 v1
	vau.mul.f16 v29 v29 v23 || cmu.alignvec v13 v26 v27 10
	vau.mul.f16 v30 v30 v24 || cmu.alignvec v14 v26 v27 12 || lsu0.ldi.128.u8f.f16 v4, i4 
	vau.add.f16 v10 v10 v11 || cmu.alignvec v15 v26 v27 14
		vau.add.f16 v0 v0 v8 //nop 
	vau.add.f16 v9 v9 v29
 convSeparable9x9_loop:
	vau.add.f16 v30 v30 v10
		vau.add.f16 v1 v1 v7  
		vau.add.f16 v2 v2 v6
	vau.add.f16 v9 v30 v9
		vau.add.f16 v3 v3 v5 
		vau.mul.f16 v8 v0 v21
		vau.mul.f16 v7 v1 v22 || lsu0.sti.128.f16.u8f v9, i18

	
		
	 LSU0.LD.64.H  v31  i19 || IAU.ADD i19 i19 8    
	 LSU0.LD.64.L  v31  i19 || IAU.ADD i19 i19 8
	 LSU0.LD.64.H  v30  i19 || IAU.ADD i19 i19 8    
	 LSU0.LD.64.L  v30  i19 || IAU.ADD i19 i19 8
	 LSU0.LD.64.H  v29  i19 || IAU.ADD i19 i19 8    
	 LSU0.LD.64.L  v29  i19 || IAU.ADD i19 i19 8
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
	

	BRU.jmp i30
	nop 6

.size mvcvConvSeparable9x9_asm,.-mvcvConvSeparable9x9_asm
.end
 
 
