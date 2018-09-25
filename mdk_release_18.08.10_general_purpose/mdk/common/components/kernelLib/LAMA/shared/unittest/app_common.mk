# ------------------------------[ App ]--------------------------------------------#
# Default application name is the same as the folder it is in.
# This can be overridden here if something different is required
#APPNAME ?= $(notdir $(shell pwd))

DirAppRoot           = ../../../../shared/unittest
DirAppOutput         = ./output

MV_SOC_PLATFORM ?= myriad2
MV_SOC_REV      ?= ma2150

ifeq ($(MV_SOC_REV),$(filter $(MV_SOC_REV),ma2150 ma2155 ma2450 ma2455))
    MV_SOC_REV_DIR:=ma2x5x
else
    ifeq ($(MV_SOC_REV),$(filter $(MV_SOC_REV),ma2480))
	    CCOPT += -DCVMA2480 
        MV_SOC_REV_DIR:=ma2x8x
    else
        $(error "$(MV_SOC_REV) variant not supported by unittesting")
    endif
endif

# ------------------------------[ Build overrides ]--------------------------------#
# overrides that need to be set before including generic.mk
ifeq ($(MV_SOC_PLATFORM), myriad2)
ifeq ($(INT_DDR), yes)
ifeq ($(MV_SOC_REV),$(filter $(MV_SOC_REV),ma2480))
LinkerScript ?= $(DirAppRoot)/config/custom_ma2480_ddr.ldscript
CCOPT += -DINT_DDR
else
LinkerScript ?= $(DirAppRoot)/config/custom_ddr.ldscript
CCOPT += -DINT_DDR
endif
else
ifeq ($(MV_SOC_REV),$(filter $(MV_SOC_REV),ma2480))
LinkerScript ?= $(DirAppRoot)/config/custom_ma2480_cmx.ldscript
else
LinkerScript ?= $(DirAppRoot)/config/custom_cmx.ldscript
endif
endif
endif

MVASMOPT += -showWarnings:1

# Set MV_COMMON_BASE relative to mdk directory location (but allow user to override in environment)
MV_COMMON_BASE  ?= ../../../../../../../../common

LAMA_PATH                = $(MV_COMMON_BASE)/components/kernelLib/LAMA
LAMA_OUTPUT_PATH         = shared/unittest/$(DirAppOutput)

# ------------------------------[ Components used ]--------------------------------#
# Extra app related options
ifeq ($(MV_SOC_PLATFORM), myriad2)
ComponentList_LOS  += UnitTestVcs VcsHooks
ComponentList_LRT  += UnitTestVcs VcsHooks
ComponentList_SVE += UnitTestVcs VcsHooks
endif

LEON_COMPONENT_PATHS 			+= ./leon
LEON_COMPONENT_HEADERS_PATHS 	+= ./leon
LEON_COMPONENT_HEADERS_PATHS 	+= ./shared

#-------------------------------[ Local shave applications sources ]--------------------#
#Choosing if this project has shave components or not
SHAVE_COMPONENTS = yes

DirLAMAOutput   = $(LAMA_PATH)/$(LAMA_OUTPUT_PATH)
DirLAMAObj      = $(DirLAMAOutput)/objects/
DirLAMAInclude  = $(LAMA_PATH)/include
DirLAMAKernels  = $(LAMA_PATH)/kernels

SH_LAMA_HEADERS_PATH += $(wildcard $(DirLAMAKernels)/*/shave/include)

#Add LAMA include directories to Components include
SHAVE_COMPONENT_INCLUDE_PATHS += $(DirLAMAInclude)
SHAVE_COMPONENT_INCLUDE_PATHS += ./shared
SHAVE_COMPONENT_INCLUDE_PATHS += $(SH_LAMA_HEADERS_PATH)

# Get all kernels
ALL_KERNELS = $(notdir $(wildcard $(DirLAMAKernels)/*))

# Exclude unwanted kernels
EXCLUDED_KERNELS =
KERNELS = $(filter-out $(EXCLUDED_KERNELS), $(ALL_KERNELS))

# Directory path for CPP code
SH_LAMA_PATHS_CPP		+=  $(patsubst %,%/shave/src/cpp,$(KERNELS))
# Directory path for chip agnostic asm code
SH_LAMA_PATHS_ASM		+=  $(patsubst %,%/shave/src,$(KERNELS))
# Directory path for chip specific asm code
SH_LAMA_PATHS_ARCH_ASM	+=  $(patsubst %,%/arch/$(MV_SOC_REV_DIR)/shave/src,$(KERNELS))

SHAVE_LAMA_HEADERS			= $(sort $(wildcard $(patsubst %,%/*.h,$(SH_LAMA_HEADERS_PATH))))
SHAVE_LAMA_CPP_SOURCES		= $(sort $(wildcard $(patsubst %,$(DirLAMAKernels)/%/*.cpp,$(SH_LAMA_PATHS_CPP))))
SHAVE_LAMA_ASM_SOURCES		= $(sort $(wildcard $(patsubst %,$(DirLAMAKernels)/%/*.asm,$(SH_LAMA_PATHS_ASM))))
SHAVE_LAMA_ARCH_ASM_SOURCES	= $(sort $(wildcard $(patsubst %,$(DirLAMAKernels)/%/*.asm,$(SH_LAMA_PATHS_ARCH_ASM))))
SHAVE_LAMA_GENASMS			= $(patsubst $(DirLAMAKernels)/%,$(DirLAMAObj)%, $(patsubst %.cpp,%.asmgen, $(SHAVE_LAMA_CPP_SOURCES)))

SHAVE_LAMA_OBJS  = $(patsubst $(DirLAMAKernels)/%,$(DirLAMAObj)%,$(patsubst %.asm, %_asm.o,$(SHAVE_LAMA_ASM_SOURCES)))
SHAVE_LAMA_OBJS += $(patsubst $(DirLAMAKernels)/%,$(DirLAMAObj)%,$(patsubst %.asm, %_asm_$(MV_SOC_REV).o,$(SHAVE_LAMA_ARCH_ASM_SOURCES)))
SHAVE_LAMA_OBJS += $(patsubst %.asmgen,%_shave.o, $(SHAVE_LAMA_GENASMS))

include $(MV_COMMON_BASE)/resolvetargetpath.mk

.SECONDEXPANSION:
$(DirLAMAObj)%_asm.o : $(DirLAMAKernels)/%.asm $(DirLAMAKernels)/$$(word 1, $$(subst /, , %))/shave/include/*.h
	@echo "Shave ASM : $*_asm.o"
	@test -d $(dir $(DirLAMAObj)$*) || mkdir -p $(dir $(DirLAMAObj)$*)
	$(MVASM) $(MVASMOPT)  $(call RESOLVE_TARGET_PATH,$<) -o:$(call RESOLVE_TARGET_PATH,$@) $(DUMP_NULL)

$(DirLAMAObj)%_asm_$(MV_SOC_REV).o : $(DirLAMAKernels)/%.asm $(DirLAMAKernels)/$$(word 1, $$(subst /, , %))/shave/include/*.h
	@echo "Shave ASM : $*_asm.o"
	@test -d $(dir $(DirLAMAObj)$*) || mkdir -p $(dir $(DirLAMAObj)$*)
	$(MVASM) $(MVASMOPT)  $(call RESOLVE_TARGET_PATH,$<) -o:$(call RESOLVE_TARGET_PATH,$@) $(DUMP_NULL)

$(DirLAMAObj)%_shave.o: $(DirLAMAObj)%.asmgen
	@echo "Shave ASM : $<"
	$(ECHO) $(MVASM) $(MVASMOPT)  $(call RESOLVE_TARGET_PATH,$<) -o:$(call RESOLVE_TARGET_PATH,$@) $(DUMP_NULL)

$(DirLAMAObj)%.asmgen: $(DirLAMAKernels)/%.cpp $(DirLAMAKernels)/$$(word 1, $$(subst /, , %))/shave/include/*.h
	@echo "Shave CPP : $<"
	@test -d $(dir $(DirLAMAObj)$*) || mkdir -p $(dir $(DirLAMAObj)$*)
	$(ECHO) $(MVCC) $(MVCCOPT) -I $(DirLAMAKernels)/$*/shave/include $(call RESOLVE_TARGET_PATH,$<) -o $(call RESOLVE_TARGET_PATH,$@) $(DUMP_NULL)


#-------------------------------[ Local shave applications sources ]--------------------#

# mvcv_macro header
MVCV_DIR = $(MV_COMMON_BASE)/components/kernelLib/MvCV
MVCCOPT += -I$(MVCV_DIR)/include

#Choosing C sources the dummy application on shave
DummyApp = shave/dummy
SHAVE_CPP_SOURCES_dummy = $(wildcard $ ./shave/*.cpp)

VCS_CPP = $(wildcard $ ./../../../../shared/unittest/shave/*.cpp)
VCS_GENASMS = $(patsubst %.cpp,$(DirAppObjBase)%.asmgen,$(VCS_CPP))
VCS_OBJ = $(patsubst %.asmgen,%_shave.o,$(VCS_GENASMS))

#Choosing ASM sources for the shave dummy app on shave
#no asm files
#SHAVE_ASM_SOURCES_dummy =

#Generating list of required generated assembly files for the dummy app on shave
SHAVE_GENASMS_dummy = $(patsubst %.cpp,$(DirAppObjBase)%.asmgen,$(SHAVE_CPP_SOURCES_dummy))
#Generating required objects list from sources
SHAVE_dummy_OBJ = $(patsubst %.asmgen,%_shave.o,$(SHAVE_GENASMS_dummy))
#update clean rules with our generated files
PROJECTCLEAN += $(SHAVE_GENASMS_dummy) $(SHAVE_dummy_OBJ)
#Uncomment below to reject generated shave as intermediary files (consider them secondary)
PROJECTINTERM += $(SHAVE_GENASMS_dummy) $(SHAVE_LAMA_GENASMS)

#--------------------------[ Shave applications section ]--------------------------#
SHAVE_APP_LIBS = $(DummyApp).mvlib
SHAVE0_APPS = $(DummyApp).shv0lib
ifeq ($(VCS_TEST_BUILD), true)
	SHAVE8_APPS = vcstest.shv8lib
endif

# ------------------------------[ Tools overrides ]--------------------------------#
# Hardcode tool version here if needed, otherwise defaults to latest stable release
#MV_TOOLS_VERSION =00.50.23.0

# Verbose or not, uncomment for more verbosity
#ECHO=

# Include the generic Makefile
include $(MV_COMMON_BASE)/generic.mk

LAMALib = $(DirLAMAOutput)/lama.a
LAMALibRev = $(DirLAMAOutput)/$(MV_SOC_REV)

$(LAMALib) : $(SHAVE_LAMA_HEADERS) $(SHAVE_LAMA_CPP_SOURCES) $(SHAVE_LAMA_ASM_SOURCES) $(SHAVE_LAMA_OBJS)
	@echo "Shave LAMA LIB   : $@"
	@mkdir -p $(dir $@)
	@touch $(LAMALibRev)
	$(ECHO) $(AR) rs $@ $(SHAVE_LAMA_OBJS)

$(LAMALibRev) : FORCE
	@mkdir -p $(dir $@)
	$(ECHO) if [ ! -f $(LAMALibRev) ]; then if [ -d $(DirLAMAOutput) ]; then rm -rf $(DirLAMAOutput)/*; touch $(LAMALibRev); else true; fi; fi
	@make $(LAMALib)

FORCE:

ENTRYPOINTS = -e _EP_start -u main -u StartAddrPcBoardLength -u savedElf -u nrOfCheckVariable -u pcExpectedOutput -u pcExpectedOutputPointer --gc-sections

PROJECTCLEAN += $(SHAVE_COMPONENT_GENASMS)

#-------------------------------[ Local shave applications build rules ]------------------#
#Describe the rule for building the dummy application. Simple rule specifying
#which objects build up the said application. The application will be built into a library
$(DummyApp).mvlib : $(SHAVE_dummy_OBJ) $(PROJECT_SHAVE_LIBS) $(LAMALibRev)
	$(ECHO) $(LD) $(MVLIBOPT) $(ENTRYPOINTS) $(SHAVE_dummy_OBJ) $(LAMALib) $(PROJECT_SHAVE_LIBS) $(CompilerANSILibs) -o $@

vcstest.mvlib : $(VCS_OBJ)
	$(ECHO) $(LD) $(MVLIBOPT) $(ENTRYPOINTS) $(VCS_OBJ) -o $@

# -------------------------------- [ Build Options ] ------------------------------ #
# App related build options

# Extra app related options
#CCOPT			+= -DDEBUG

# The following is used to specify which platforms a given unit test is expected to build on
# The default expectation is that they work for both myriad2
# In these cases the variable is overidden locally
BUILD_PLATFORMS ?= "myriad2"
MDK_PROJ_STRING  = "MDK_FALSE"

getBuildPlatforms:
	@echo BUILD_PLATFORMS=$(BUILD_PLATFORMS)

UNIT_TEST_USE_C_VERSION =
ifeq ($(UNIT_TEST_USE_C_VERSION), true)
MVCCOPT        += -DUNIT_TEST_USE_C_VERSION
endif

ifeq ($(VCS_TEST_BUILD), true)
MVCCOPT        += -DVCS_TESTING_DUMP_ELF
CCOPT          += -DVCS_TESTING_DUMP_ELF
endif

clean_lib :
	@echo "Cleaning LAMA lib"
	$(call SAFE_RM,$(DirLAMAOutput))

