MV_SOC_PLATFORM ?= myriad2
MV_SOC_REV       ?= ma2450

SHAVE_COMPONENTS = no
MV_COMMON_BASE  ?= ../../../../../../common
ComponentList_LOS   := UnitTestVcs VcsHooks PipePrint
DirAppRoot = ../..
DirAppOutput = ./output

#########################################################################################
# Include SIPP specifics
include $(MV_COMMON_BASE)/components/sipp/arch/$(MV_SOC_REV)/build/myriad2/sippMyriad2Elf.mk
#########################################################################################

#CCOPT   += -DSIPP_NO_PRINTF
#The binary elf for Shave:
CCOPT   += -DSIPP_SCRT_ENABLE_OPIPE
svuSippImg = $(DirAppOutput)/svuSippImg
RAWDATAOBJECTFILES += $(svuSippImg)_sym.o $(svuSippImg)Map.o

#########################################################################################
# Include the top makefile
PROJECTCLEAN += $(SippSvuObj)
include $(MV_COMMON_BASE)/generic.mk
#########################################################################################

$(svuSippImg).mvlib : $(SippSvuObj)
	@mkdir -p $(dir $@)
	$(ECHO) $(LD) $(MVLIBOPT) $(SippSvuObj) $(CompilerANSILibs) -o $@

$(svuSippImg)_sym.o : $(svuSippImg).shvdcomplete
	$(ECHO) $(OBJCOPY) --prefix-symbols=SS_ --extract-symbol $< $@

$(svuSippImg)Map.o : $(svuSippImg).shvdlib
		@mkdir -p $(dir $@)
			$(OBJCOPY) -I binary $(REVERSE_BYTES) --rename-section .data=.ddr.data \
					--redefine-sym  _binary_$(subst -,_,$(subst /,_,$(subst .,_,$<)))_start=mbinImgSipp \
						-O elf32-littlesparc -B sparc $< $@
#########################################################################################
# Test specifics
#########################################################################################
TEST_HW_PLATFORM := "MV0182_MA2150, MV0212_MA2450"
TEST_TYPE := "AUTO"
#Mark test as running long
TEST_TAGS := "MA2150, MA2450, SIPP, LONG_RUN_TEST, MOVISIM_LONG_RUN_TEST_MA2450, MOVISIM_LONGER_RUN_TEST_MA2150"
