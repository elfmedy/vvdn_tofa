#include "half.h"
#include "TestRunner.h"
#include "FunctionInfo.h"
#include "moviDebugDll.h"
#include <cstdio>

#define EXPECTED_CC  (38.07)

TestRunner convolution5x5s8hhhhTestRunner(APP_PATH, APP_ELFPATH, KERNEL_ASM_LABEL, DBG_INTERFACE);
unsigned int convolution5x5s8hhhhCycleCount;

void Convolution5x5s8hhhh_asm_test(half** in, half** out, half conv[25], unsigned int width)
{
	FunctionInfo& functionInfo = FunctionInfo::Instance();
	// for calculation of the last values on the line a padding of kenrnel_size - 1 is needed
	const unsigned int padding = 16;
	// maxWidth - the maximum image width for which was allocated space in the board application;
	// it is needed to permit proper memory initialization for line sizes lower than it
	unsigned int maxWidth = 1920 + padding;

	convolution5x5s8hhhhTestRunner.Init();
	//add padding values at the end of each line
	convolution5x5s8hhhhTestRunner.SetInput("input", in, width + padding, maxWidth, 5, SHAVE0);
	convolution5x5s8hhhhTestRunner.SetInput("conv", (half*)&conv[0], 25, SHAVE0);
	convolution5x5s8hhhhTestRunner.SetInput("width", (unsigned int)width, SHAVE0);
	convolution5x5s8hhhhTestRunner.GuardInsert(string("output"), SHAVE0, width/8, maxWidth, 1, out);
	convolution5x5s8hhhhTestRunner.Run(SHAVE0);
	if(width >= 1280)
	{
		convolution5x5s8hhhhCycleCount = convolution5x5s8hhhhTestRunner.GetVariableValue("cycleCount");
		functionInfo.AddCyclePerPixelInfo((float)(convolution5x5s8hhhhCycleCount - 65)/ (float)(width/8));
		functionInfo.setExpectedCycles((float)EXPECTED_CC);
	}
	convolution5x5s8hhhhTestRunner.GetOutput(string("output"), SHAVE0, width/8, maxWidth, 1, out);
	convolution5x5s8hhhhTestRunner.GuardCheck(string("output"), SHAVE0, width/8, maxWidth, 1, out);
}
