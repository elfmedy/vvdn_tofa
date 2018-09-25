#include "mv_types.h"
#include "TestRunner.h"
#include "FunctionInfo.h"
#include "moviDebugDll.h"
#include <cstdio>

TestRunner sgemmtrsm_l4x4TestRunner(APP_PATH, APP_ELFPATH, KERNEL_ASM_LABEL, DBG_INTERFACE);
unsigned int sgemmtrsm_l4x4CycleCount;

void sgemmtrsm_l4x4_asm_test(s32 k, float *alpha, float *a10, float *a11, float *b01, float *b11, float *c11, s32 rs_c, s32 cs_c)
{
	//FunctionInfo& functionInfo = FunctionInfo::Instance();

	sgemmtrsm_l4x4TestRunner.Init();
	sgemmtrsm_l4x4TestRunner.SetInput("k",          k,        SHAVE0);
	sgemmtrsm_l4x4TestRunner.SetInput("alpha", *alpha,        SHAVE0);
	sgemmtrsm_l4x4TestRunner.SetInput("A10",      a10, 4 * k, SHAVE0);
        sgemmtrsm_l4x4TestRunner.SetInput("A11",      a11, 4 * 4, SHAVE0);
        sgemmtrsm_l4x4TestRunner.SetInput("B01",      b01, 4 * k, SHAVE0);
        sgemmtrsm_l4x4TestRunner.SetInput("B11",      b11, 4 * 4, SHAVE0);
	sgemmtrsm_l4x4TestRunner.SetInput("rs_c",    rs_c,        SHAVE0);
	sgemmtrsm_l4x4TestRunner.SetInput("cs_c",    cs_c,        SHAVE0);

	sgemmtrsm_l4x4TestRunner.GuardInsert("B11", SHAVE0, 4 * 4 * sizeof(float), (unsigned char*)b11);
	sgemmtrsm_l4x4TestRunner.GuardInsert("C11", SHAVE0, 4 * 4 * sizeof(float), (unsigned char*)c11);
	sgemmtrsm_l4x4TestRunner.Run(SHAVE0);
    //sgemmtrsm_l4x4CycleCount = sgemmtrsm_l4x4TestRunner.GetVariableValue("cycleCount");
        sgemmtrsm_l4x4TestRunner.GetOutput("B11", SHAVE0, 4 * 4 * sizeof(float), (unsigned char*)b11);
        sgemmtrsm_l4x4TestRunner.GuardCheck("B11", SHAVE0, 4 * 4 * sizeof(float), (unsigned char*)b11);
	sgemmtrsm_l4x4TestRunner.GetOutput("C11", SHAVE0, 4 * 4 * sizeof(float), (unsigned char*)c11);
	sgemmtrsm_l4x4TestRunner.GuardCheck("C11", SHAVE0, 4 * 4 * sizeof(float), (unsigned char*)c11);
}
