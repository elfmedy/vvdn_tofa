//convolution11x11s3hhhh kernel test
//Asm function prototype:
//     void Convolution11x11s3hhhh_asm(half** in, half** out, half conv[][11], u32 inWidth);
//
//Asm test function prototype:
//     void Convolution11x11s3hhhh_asm(half** in, half** out, half conv[][11], unsigned int inWidth);
//
//C function prototype:
//     void Convolution11x11s3hhhh(half** in, half** out, half conv[][11], u32 inWidth);
//
//Parameter description:
// in         - array of pointers to input lines
// out        - array of pointers to output lines
// conv       - array of values from convolution
// inWidth    - width of input line
//
// each line needs a padding o kernel_size - 1 values at the end; the value of the padding is equal
// with the last value of line without padding

#include "gtest/gtest.h"
///
#include "convolution11x11s3hhhh.h"
#include "convolution11x11s3hhhh_asm_test.h"
#include "RandomGenerator.h"
#include "InputGenerator.h"
#include "UniformGenerator.h"
#include "TestEventListener.h"
#include "ArrayChecker.h"
#include <ctime>
#include "half.h"

using ::testing::TestWithParam;
using ::testing::Values;


#define PADDING 16
half delta=3.0;
//#define DELTA 3.0 //accepted tolerance between C and ASM results
#define SIZE 11

class Convolution11x11s3hhhhKernelTest : public ::testing::TestWithParam< unsigned int > {
protected:

	virtual void SetUp()
	{
		randGen.reset(new RandomGenerator);
		uniGen.reset(new UniformGenerator);
		inputGen.AddGenerator(std::string("random"), randGen.get());
		inputGen.AddGenerator(std::string("uniform"), uniGen.get());
	}

	half convMat[121];
		
	half **inLines;
	half **outLinesC;
	half **outLinesAsm;
	unsigned int width;
	InputGenerator inputGen;
	std::auto_ptr<RandomGenerator>  randGen;
	std::auto_ptr<UniformGenerator>  uniGen;
	ArrayChecker outputChecker;

	virtual void TearDown() {} 
};

TEST_F(Convolution11x11s3hhhhKernelTest, TestUniformInputLinesMinimumWidth)
{

	width = 24;
	inputGen.SelectGenerator("random");
	inLines = inputGen.GetLinesFloat16(width + PADDING, 11,4, 500);
	outLinesC = inputGen.GetEmptyLinesFp16(width, 1);
	outLinesAsm = inputGen.GetEmptyLinesFp16(width, 1);

	inputGen.FillLine(convMat, 121, 0.003,0.0082644);
	

	Convolution11x11s3hhhh_asm_test(inLines, outLinesAsm, convMat, width);
	RecordProperty("CyclePerPixel", convolution11x11s3hhhhCycleCount / width);

        
	inLines = inputGen.GetOffsettedLines(inLines, SIZE, PADDING / 2);
	mvcvConvolution11x11s3hhhh(inLines, outLinesC, convMat, width);
	
    

	outputChecker.CompareArrays(outLinesC, outLinesAsm, width/3, 1, delta);
}

 TEST_F(Convolution11x11s3hhhhKernelTest, TestUniformInputLinesAll0)
 {
	 width = 640;
	 inputGen.SelectGenerator("uniform");
	 inLines = inputGen.GetLinesFloat16(width + PADDING, 11, 0);
	 outLinesC = inputGen.GetEmptyLinesFp16(width, 1);
	 outLinesAsm = inputGen.GetEmptyLinesFp16(width, 1);

	
	 inputGen.FillLine(convMat, 121, 0.0082644);

	 Convolution11x11s3hhhh_asm_test(inLines, outLinesAsm, convMat, width);
         RecordProperty("CyclePerPixel", convolution11x11s3hhhhCycleCount / width);

	 inLines = inputGen.GetOffsettedLines(inLines, SIZE, PADDING / 2);
	 mvcvConvolution11x11s3hhhh(inLines, outLinesC, convMat, width);
	

	 outputChecker.CompareArrays(outLinesC[0], outLinesAsm[0], width/3);
 }


 TEST_F(Convolution11x11s3hhhhKernelTest, TestUniformInputLinesAll255)
 {
	 width = 640;
	 inputGen.SelectGenerator("uniform");
	 inLines = inputGen.GetLinesFloat16(width + PADDING, 11, 255);
	 outLinesC = inputGen.GetEmptyLinesFp16(width, 1);
	 outLinesAsm = inputGen.GetEmptyLinesFp16(width, 1);


         inputGen.FillLine(convMat, 121, 0.0082644);

	 Convolution11x11s3hhhh_asm_test(inLines, outLinesAsm, convMat, width);
	 RecordProperty("CyclePerPixel", convolution11x11s3hhhhCycleCount / width);

	 inLines = inputGen.GetOffsettedLines(inLines, SIZE, PADDING / 2);
	 mvcvConvolution11x11s3hhhh(inLines, outLinesC, convMat, width);
	
	outputChecker.CompareArrays(outLinesC[0], outLinesAsm[0], width/3, delta);
 }

TEST_F(Convolution11x11s3hhhhKernelTest, TestUniformInputLinesRandomConvMatrix)
{
	width = 64;
	 inputGen.SelectGenerator("uniform");
	 inLines = inputGen.GetLinesFloat16(width + PADDING, 11, 3);
	 outLinesC = inputGen.GetEmptyLinesFp16(width, 1);
	 outLinesAsm = inputGen.GetEmptyLinesFp16(width, 1);

	
	 inputGen.SelectGenerator("random");
	 half *convMat = inputGen.GetLineFloat16(121, 0.0f, 0.01f);
	
	 Convolution11x11s3hhhh_asm_test(inLines, outLinesAsm, convMat, width);
	 RecordProperty("CyclePerPixel", convolution11x11s3hhhhCycleCount / width);

	 inLines = inputGen.GetOffsettedLines(inLines, SIZE, PADDING / 2);
	 mvcvConvolution11x11s3hhhh(inLines, outLinesC, convMat, width);
	
	 outputChecker.CompareArrays(outLinesC[0], outLinesAsm[0], width/3, delta);
}


 TEST_F(Convolution11x11s3hhhhKernelTest, TestRandomInputLinesRandomConvMatrix)
 {   
	 width = 240;
	 inputGen.SelectGenerator("random");
	 inLines = inputGen.GetLinesFloat16(width + PADDING, 11, 0, 255);
	 outLinesC = inputGen.GetEmptyLinesFp16(width, 1);
	 outLinesAsm = inputGen.GetEmptyLinesFp16(width, 1);

	 half convMat[121];
	 inputGen.FillLine(convMat, 121, 0.0f, 0.008f);
	

	 Convolution11x11s3hhhh_asm_test(inLines, outLinesAsm, convMat, width);
	 RecordProperty("CyclePerPixel", convolution11x11s3hhhhCycleCount / width);

	 inLines = inputGen.GetOffsettedLines(inLines, SIZE, PADDING / 2);
	 mvcvConvolution11x11s3hhhh(inLines, outLinesC, convMat, width);
	
        
	 outputChecker.CompareArrays(outLinesC[0], outLinesAsm[0], width/3, delta);
 }


///------------ parameterized tests ----------------------------------------

INSTANTIATE_TEST_CASE_P(UniformInputs, Convolution11x11s3hhhhKernelTest,
		 Values((unsigned int)24, (unsigned int)48, (unsigned int)240, (unsigned int)512, (unsigned int)320, (unsigned int)400, (unsigned int)1920);
 );

TEST_P(Convolution11x11s3hhhhKernelTest, TestRandomInputLinesBlurFilter)
 {
	
	 half convMat[121];

	 inputGen.SelectGenerator("uniform");

	 inputGen.FillLine(convMat, 121, 1.0f / 121);

	 unsigned int width = GetParam();

	 inputGen.SelectGenerator("random");
	 inLines = inputGen.GetLinesFloat16(width + PADDING, 11, 0, 255);
	 outLinesC = inputGen.GetEmptyLinesFp16(width, 1);
	 outLinesAsm = inputGen.GetEmptyLinesFp16(width, 1);

	 Convolution11x11s3hhhh_asm_test(inLines, outLinesAsm, convMat, width);
	 RecordProperty("CyclePerPixel", convolution11x11s3hhhhCycleCount / width);
	
	 inLines = inputGen.GetOffsettedLines(inLines, SIZE, PADDING / 2);
	 mvcvConvolution11x11s3hhhh(inLines, outLinesC, convMat, width);

	 outputChecker.CompareArrays(outLinesC[0], outLinesAsm[0], width/3, delta);
 }
