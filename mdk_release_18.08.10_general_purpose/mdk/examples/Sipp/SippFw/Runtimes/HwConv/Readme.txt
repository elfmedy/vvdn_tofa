testHWConv

Overview
====================
This is a simple SIPP pipeline to test the convolution hardware accelerator
running in direct streaming runtime.

Hardware needed
==================
Myriad2 - This example works on Myriad2: ma2150, ma2450 silicon

Build
====================
Change directory to the required build platform.

build/myriad2 (mv0212 or mv0182 board): To build the project please type:
     - "make clean"
     - "make all MV_SOC_REV={Myriad_version}"

Where {Myriad_version} may be ma2150 or ma2450.
The default Myriad revision in this project is ma2150 so it is not necessary
to specify the MV_SOC_REV in the terminal.

Setup
====================
MV0182 or MV0212
    - open terminal and type "make start_server"
    - open another terminal and type "make run MV_SOC_REV={Myriad_version}"

Where {Myriad_version} may be ma2150 or ma2450.
The default Myriad revision in this project is ma2150 so it is not necessary
to specify the MV_SOC_REV in the terminal.

Notes
====================
This is a LeonRT demonstration example. It can not be run from within Eclipse and will not work if flashed
into EEPROM unless example is changed to run on LeonOS and interrupts are re-routed to LeonOS.

Expected output
====================
1. Expected displayed message: "moviUnitTest:PASSED"
2. Expected output file: An output image will be generated after run finishes
with the following characteristics:
- Name:            output.raw
- Location:        build/myriad2
- Format:          .raw
- Size(WxH):       1296x972
- Bits per sample: 8
- No. of planes:   1
- Open with tools: movImageCompare, Irfanview or pyuv
