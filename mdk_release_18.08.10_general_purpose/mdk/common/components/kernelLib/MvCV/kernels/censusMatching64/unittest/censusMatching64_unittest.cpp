
//Parameter description:
// mvcvCensusMatching 
// @param[in] in1            - pointer to input lines of the left image
// @param[in] in2            - pointer to input lines of the right image
// @param[out] out           - array of disparity cost
// @param[in] width          - width of the input lines
// @return    Nothing




#include "gtest/gtest.h"
#include <censusMatching64.h>
#include "censusMatching64_asm_test.h"
#include "RandomGenerator.h"
#include "InputGenerator.h"
#include "UniformGenerator.h"
#include "TestEventListener.h"
#include "ArrayChecker.h"
#include <ctime>

using ::testing::TestWithParam;
using ::testing::Values;

#define PADDING 64

class mvcvCensusMatching64KernelTest : public ::testing::TestWithParam< unsigned int > {
protected:

    virtual void SetUp()
    {
        randGen.reset(new RandomGenerator);
        uniGen.reset(new UniformGenerator);
        inputGen.AddGenerator(std::string("random"), randGen.get());
        inputGen.AddGenerator(std::string("uniform"), uniGen.get());
    }

    unsigned int *inLine1;
    unsigned int *inLine2;
    unsigned char *outLineC;
    unsigned char *outLineAsm;
    unsigned int width;
    unsigned int flag;
    unsigned int disparities;

    InputGenerator inputGen;
    std::auto_ptr<RandomGenerator>  randGen;
    std::auto_ptr<UniformGenerator>  uniGen;
    ArrayChecker outputChecker;

    virtual void TearDown() {}
};

TEST_F(mvcvCensusMatching64KernelTest, TestWidth16All0)
{
    disparities = 64;
    width = 16;
    flag = 0;
    
    inputGen.SelectGenerator("uniform");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0);
    

    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1 + PADDING, inLine2 + PADDING, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

TEST_F(mvcvCensusMatching64KernelTest, TestWidth16AllMAX)
{
    disparities = 64;
    width = 16;
    flag = 0;
    
    inputGen.SelectGenerator("uniform");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 255);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 255);
    

    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1 + PADDING, inLine2 + PADDING, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

TEST_F(mvcvCensusMatching64KernelTest, TestRandomDATARandomWidth)
{
    disparities = 64;
    width = randGen->GenerateUInt(8, 1280, 8);
    flag = 0;
    
    inputGen.SelectGenerator("random");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    
    inputGen.SelectGenerator("uniform");
    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1 + PADDING, inLine2 + PADDING, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

TEST_F(mvcvCensusMatching64KernelTest, TestRandomDATARandom2Width)
{
    disparities = 64;
    width = randGen->GenerateUInt(960, 1280, 8);
    flag = 0;
    
    inputGen.SelectGenerator("random");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    
    inputGen.SelectGenerator("uniform");
    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1 + PADDING, inLine2 + PADDING, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

TEST_F(mvcvCensusMatching64KernelTest, TestWidth16All0_flag)
{
    disparities = 64;
    width = 16;
    flag = 1;
    
    inputGen.SelectGenerator("uniform");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0);
    

    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1, inLine2, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

TEST_F(mvcvCensusMatching64KernelTest, TestWidth16AllMAX_flag)
{
    disparities = 64;
    width = 16;
    flag = 1;
    
    inputGen.SelectGenerator("uniform");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 255);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 255);
    

    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1, inLine2, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

TEST_F(mvcvCensusMatching64KernelTest, TestRandomDATARandomWidth_flag)
{
    disparities = 64;
    width = randGen->GenerateUInt(8, 1280, 8);
    flag = 1;
    
    inputGen.SelectGenerator("random");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    
    inputGen.SelectGenerator("uniform");
    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1, inLine2, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

TEST_F(mvcvCensusMatching64KernelTest, TestRandomDATARandom2Width_flag)
{
    disparities = 64;
    width = randGen->GenerateUInt(960, 1280, 8);
    flag = 1;
    
    inputGen.SelectGenerator("random");
    inLine1 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    inLine2 = (unsigned int *)inputGen.GetLine((width + PADDING)*4, 0, 255);
    
    inputGen.SelectGenerator("uniform");
    outLineC   = inputGen.GetEmptyLine(width * disparities + PADDING);
    outLineAsm = inputGen.GetEmptyLine(width * disparities + PADDING);
    inputGen.FillLine(outLineC,  width * disparities + PADDING , 5);
    inputGen.FillLine(outLineAsm,width * disparities + PADDING , 5);
    

    mvcvCensusMatching64(inLine1, inLine2, outLineC + PADDING/2, width, flag);
    mvcvCensusMatching64_asm_test(inLine1 , inLine2 , outLineAsm , width, flag);
    
    RecordProperty("CyclePerPixel", mvcvCensusMatching64CycleCount / (width * disparities));

    //outputChecker.DumpArrays("refInput1", "refInput1.c", inLine1, width + PADDING);
    //outputChecker.DumpArrays("refInput2", "refInput2.c", inLine2, width + PADDING);
    //outputChecker.DumpArrays("outC", "outC.c", outLineC, width * disparities + PADDING);
    //outputChecker.DumpArrays("outAsm", "outAsm.c", outLineAsm, width * disparities + PADDING);
    
    
    outputChecker.CompareArrays(outLineC, outLineAsm, width * disparities + PADDING);
}

