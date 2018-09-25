# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.

ECHO ?= @

MV_SOC_REV ?= ma2150

APPDIR=$(CURDIR)
ifndef APPNAME
APPNAME := $(basename $(notdir $(CURDIR)))
endif

MDK_BASE ?= ../..
MV_COMMON_BASE   ?= $(MDK_BASE)/common
MV_PACKAGES_BASE ?= $(MDK_BASE)/packages/movidius

SRV_IP ?=

TEST_TYPE=AUTO
TEST_SOC_PLATFORM="myriad2"
TEST_HW_PLATFORM="MV0182_MA2150,MV0182_MA2450,MOVISIM_MA2150,MOVISIM_MA2450,MOVISIM_MA2480,MV0212_MA2150,MV0212_MA2450"
TEST_TAGS:="MA2150,MA2450,MA2480"

# Platform detection
FULL_PLATFORM := $(shell uname -a)
ifndef UNAME
UNAME := $(shell uname -o)
endif
ifeq ($(UNAME),GNU/Linux)
  ifeq ($(findstring x86_64,$(FULL_PLATFORM)),x86_64)
    DETECTED_PLATFORM =linux64
  else
    $(error Linux32 platform is no longer supported.)
  endif
else
  DETECTED_PLATFORM =win32
endif

include $(MV_COMMON_BASE)/generalsettings.mk
include $(MV_COMMON_BASE)/toolssettings.mk

#toolssettings.mk will tenatively set CC, CXX and AR to sparc-elf-gcc
#sparc-elf-g++ and sparc-elf-ar respectively. However this file is only trying
#to build PC side applications and such we define PC tools instead of these
CC = gcc
CXX = g++
AR = ar

MDK_PROJ_STRING = "MDK_FALSE"

MV_TOOLS_BASE = $(MV_TOOLS_DIR)/$(MV_TOOLS_VERSION)

-include $(MV_COMMON_BASE)/inhousetargets.mk

UNIT_TEST_DIR ?= $(MDK_BASE)/regression/unittest
GTEST_DIR = $(UNIT_TEST_DIR)/g_test/gtest-1.6.0
# Where to find user code.
USER_DIR = $(GTEST_DIR)/samples

MYRIAD_DIR = $(MV_COMMON_BASE)/swCommon/shave_code/$(MV_SOC_PLATFORM)
MYRIAD_MODEL_DIR = $(MV_COMMON_BASE)/swCommon/pcModel/dmaModel
SHAVE_COMMON_DIR = $(MV_COMMON_BASE)/swCommon/shave_code
SHAVE_COMMON_INCLUDE = $(SHAVE_COMMON_DIR)/include
MDK_SHARED_INCLUDE_DIR = $(MV_COMMON_BASE)/shared/include
MYRIAD_INCLUDE_DIR = $(MYRIAD_DIR)/include

TESTRUNNER_DIR = $(UNIT_TEST_DIR)/testrunner

ifeq ($(USES_OPENCV), yes)
HELPERS_DIR = $(UNIT_TEST_DIR)/helpers
HELPERS_SRC_DIR = $(HELPERS_DIR)/src
HELPERS_INCLUDE_DIR = $(HELPERS_DIR)/include
HELPERS_SOURCES = $(wildcard $(HELPERS_SRC_DIR)/*.cpp)
HELPERS_HEADERS = $(wildcard $(HELPERS_INCLUDE_DIR)/*.h)
endif
RANDGEN_DIR = $(UNIT_TEST_DIR)/datagenerator
RANDGEN_SRC_DIR = $(RANDGEN_DIR)/src
RANDGEN_INCLUDE_DIR = $(RANDGEN_DIR)/include
RANDGEN_SOURCES = $(wildcard $(RANDGEN_SRC_DIR)/*.cpp)
RANDGEN_HEADERS = $(wildcard $(RANDGEN_INCLUDE_DIR)/*.h)
UNIT_TEST_SRC_DIR = $(TESTRUNNER_DIR)/src
UNIT_TEST_INCLUDE_DIR = $(TESTRUNNER_DIR)/include
UNIT_TEST_SOURCES = $(wildcard $(UNIT_TEST_SRC_DIR)/*.cpp)
UNIT_TEST_HEADERS += $(wildcard $(UNIT_TEST_INCLUDE_DIR)/*.h)
UNIT_TEST_HEADERS += $(RANDGEN_HEADERS)
UNIT_TEST_OUT_DIR = $(APPDIR)/out

ASM_FUNC_DIR = $(APPDIR)
ASM_FUNC_INCLUDE_DIR = $(ASM_FUNC_DIR)
ASM_FUNC_OUT_DIR = $(APPDIR)/out/asm_functions

EXTRA_LIBS += $(ASM_FUNC_OBJ) $(DATA_GEN_OBJ)
ifeq ($(USES_OPENCV), yes)
EXTRA_LIBS += $(HELPERS_GEN_OBJ)
endif
# switch between movidebug1/movidebug2

CPPFLAGS += -DMV_MVDBG_GEN2


# Debug Interface: DLL_DBGI_JTAG for JTAG interface and DLL_DBGI_MSIM for simulator interface
DI ?= DLL_DBGI_MSIM
ifdef SRV_PORT
srvPort = $(SRV_PORT)
endif
srvPort ?= 30000
ifeq ($(DBGI), jtag)
DI = DLL_DBGI_JTAG
srvPort = 30001
else ifeq ($(DBGI), sim)
DI = DLL_DBGI_MSIM
endif

# Flags passed to the preprocessor.
CPPFLAGS += -DDBG_INTERFACE=$(DI)
# shave prefix used to create shave symbol names
CPPFLAGS += -D"TARGET_PREFIX=\"$(TARGET_PREFIX)\""
CPPFLAGS += -D"KERNEL_APP_NAME=\"$(KERNEL_APP_NAME)\""
CPPFLAGS += -D"APP_PATH=\"$(KERNEL_APP_PATH)\""
CPPFLAGS += -D"KERNEL_ASM_LABEL=\"$(KERNEL_ASM_LABEL)\""
ifeq "y" "$(MVCV_UNITTEST_BUILD_WITH_NEXTGEN)"
CPPFLAGS += -D"APP_ELFPATH=\"$(KERNEL_APP_PATH)/mvbuild/$(MV_SOC_REV)/$(KERNEL_APP_NAME).elf\""
else
CPPFLAGS += -D"APP_ELFPATH=\"$(KERNEL_APP_PATH)/output/$(KERNEL_APP_NAME).elf\""
endif
CPPFLAGS += -I$(GTEST_DIR)/include
CPPFLAGS += -I$(MDK_SHARED_INCLUDE_DIR)
CPPFLAGS += -I$(MYRIAD_MODEL_DIR)
CPPFLAGS += -I$(MYRIAD_INCLUDE_DIR)
CPPFLAGS += -I$(SHAVE_COMMON_INCLUDE)
CPPFLAGS += -I$(UNIT_TEST_INCLUDE_DIR)
ifeq ($(USES_OPENCV), yes)
CPPFLAGS += -I$(HELPERS_INCLUDE_DIR)
endif
CPPFLAGS += -I$(ASM_FUNC_INCLUDE_DIR)
CPPFLAGS += -I$(RANDGEN_INCLUDE_DIR)
CPPFLAGS += -I$(MV_PACKAGES_BASE)/pcModel/moviCompile/compilerIntrinsics/include
CPPFLAGS += -I$(MV_PACKAGES_BASE)/pcModel/moviCompile/compilerVectorFunctions/include
CPPFLAGS += -I$(MDK_BASE)/common/swCommon/pcModel/half
CPPFLAGS += -L$(TEST_LIB_DIR)

CPPFLAGS += -Wno-multichar -fpermissive

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra
CXXFLAGS += -D__PC__
# We need the following option to downgrade some errors that appear on some Linux platforms to warnings
#CXXFLAGS += -fpermissive
ifeq ($(MV_SOC_PLATFORM),myriad2)
CXXFLAGS += -DMYRIAD2
endif
ifeq ($(MV_SOC_REV),ma2150)
CXXFLAGS += -U"TARGET_MYRIAD2"
CXXFLAGS += -D"TARGET_MYRIAD2=MOVIDEBUG_TARGETS_MYRIAD_2V2_FLAG"
CPPFLAGS += -DCVMA2150
endif
ifeq ($(MV_SOC_REV),ma2450)
CXXFLAGS += -U"TARGET_MYRIAD2"
CXXFLAGS += -D"TARGET_MYRIAD2=MOVIDEBUG_TARGETS_MYRIAD_2V2_FLAG"
CPPFLAGS += -DCVMA2450
endif
ifeq ($(MV_SOC_REV),ma2480)
CXXFLAGS += -U"TARGET_MYRIAD2"
CXXFLAGS += -D"TARGET_MYRIAD2=MOVIDEBUG_TARGETS_MYRIAD_2V2_FLAG"
CPPFLAGS += -DCVMA2480
endif

GTEST_PROJ_STRING ?= "GTEST_TRUE"

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = $(UNIT_TEST_LIST)

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	@echo Generating: $@
	$(ECHO) $(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	@echo Generating: $@
	$(ECHO) $(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	@echo Generating: $@
	$(ECHO) $(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	@echo Generating: $@
	$(ECHO) $(AR) $(ARFLAGS) $@ $^

TEST_OUT_DIR = $(APPDIR)/out
TEST_RUN_DIR = $(APPDIR)/run


TEST_LIB_DIR = $(MV_TOOLS_DIR)/$(MV_TOOLS_VERSION)/$(DETECTED_PLATFORM)/lib



ifeq ($(UNAME),GNU/Linux)
  EXTRA_GCC_DLL = libgcc_s.so.1
  EXTRA_STD_DLL = libstdc++.so.6
  MV_DBG_DLL2 = moviDebug2.so
  USE_PTHREAD = -pthread
else
  MV_DBG_DLL2 = moviDebug2.dll
  USE_PTHREAD = -lpthread
endif

TEST_INCLUDE_DIR = ./include
CPPFLAGS += -I$(TEST_INCLUDE_DIR)

UNIT_TEST_OBJ = $(patsubst %, $(UNIT_TEST_OUT_DIR)/%, $(notdir $(patsubst %.cpp, %.o, $(wildcard $(UNIT_TEST_SRC_DIR)/*.cpp))))

$(UNIT_TEST_OBJ) : $(UNIT_TEST_OUT_DIR)/%.o : $(UNIT_TEST_SRC_DIR)/%.cpp $(UNIT_TEST_HEADERS)
	@echo Generating: $@
	$(ECHO) @mkdir -p $(dir $@)
	$(ECHO) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

DATA_GEN_OBJ = $(patsubst %, $(TEST_OUT_DIR)/%, $(notdir $(patsubst %.cpp, %.o, $(RANDGEN_SOURCES))))

$(DATA_GEN_OBJ) : $(UNIT_TEST_OUT_DIR)/%.o : $(RANDGEN_SRC_DIR)/%.cpp $(RANDGEN_INCLUDE_DIR)/*.h
	@echo Generating: $@
	$(ECHO) @mkdir -p $(dir $@)
	$(ECHO) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

ifeq ($(USES_OPENCV), yes)
HELPERS_GEN_OBJ = $(patsubst %, $(TEST_OUT_DIR)/%, $(notdir $(patsubst %.cpp, %.o, $(HELPERS_SOURCES))))

$(HELPERS_GEN_OBJ) : $(UNIT_TEST_OUT_DIR)/%.o : $(HELPERS_SRC_DIR)/%.cpp $(HELPERS_INCLUDE_DIR)/*.h
	@echo Generating: $@
	$(ECHO) @mkdir -p $(dir $@)
	$(ECHO) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
endif

KERNEL_NAME = $(patsubst %_unittest,%,$(TEST_NAME))

ASM_FUNC_OBJ = $(patsubst %, $(ASM_FUNC_OUT_DIR)/%, $(notdir $(patsubst %.cpp, %.o, $(wildcard $(ASM_FUNC_DIR)/*$(KERNEL_NAME)_asm_test*.cpp))))
$(ASM_FUNC_OBJ) : $(ASM_FUNC_OUT_DIR)/%.o : $(ASM_FUNC_DIR)/%.cpp $(ASM_FUNC_INCLUDE_DIR)/*.h
	@echo Generating: $@
	$(ECHO) @mkdir -p $(dir $@)
	$(ECHO) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

UNIT_TEST_MODULES = $(wildcard $(APPDIR)/*_unittest.cpp)
UNIT_TEST_OBJECTS = $(patsubst %, $(TEST_OUT_DIR)/%, $(notdir $(patsubst %.cpp, %.o, $(UNIT_TEST_MODULES))))
UNIT_TEST_LIST = $(patsubst %, $(TEST_RUN_DIR)/%, $(notdir $(subst .cpp,, $(UNIT_TEST_MODULES))))

# libinintrinsics contains half library also
LBITS := $(shell getconf LONG_BIT)
ifeq ($(UNAME),GNU/Linux)
LIB_INTRINSICS = $(MV_PACKAGES_BASE)/pcModel/moviCompile/compilerIntrinsics/lib/linux$(LBITS)/libintrinsics.a
LIB_VECTFUNC   = $(MV_PACKAGES_BASE)/pcModel/moviCompile/compilerVectorFunctions/lib/linux$(LBITS)/libvectorfunctions.a
else
LIB_INTRINSICS = $(MV_PACKAGES_BASE)/pcModel/moviCompile/compilerIntrinsics/lib/win$(LBITS)/libintrinsics.a
LIB_VECTFUNC   = $(MV_PACKAGES_BASE)/pcModel/moviCompile/compilerVectorFunctions/lib/win$(LBITS)/libvectorfunctions.a
endif

ifeq ($(UNAME),GNU/Linux)
$(UNIT_TEST_LIST) : $(TEST_RUN_DIR)/%_unittest : $(TEST_OUT_DIR)/%_unittest.o \
	$(EXTRA_LIBS) $(UNIT_TEST_OBJ) gtest.a $(TEST_LIB_DIR)/$(MV_DBG_DLL2) $(TEST_LIB_DIR)/$(EXTRA_GCC_DLL) $(TEST_LIB_DIR)/$(EXTRA_STD_DLL) $(LIB_INTRINSICS) $(LIB_VECTFUNC)
	@echo Generating: $@
	$(ECHO) @mkdir -p $(dir $@)
	$(ECHO) $(CXX) $(CXXFLAGS) $(USE_PTHREAD) $^ $(CPPFLAGS) -o $@
else
$(UNIT_TEST_LIST) : $(TEST_RUN_DIR)/%_unittest : $(TEST_OUT_DIR)/%_unittest.o \
	$(EXTRA_LIBS) $(UNIT_TEST_OBJ) gtest.a $(TEST_LIB_DIR)/$(MV_DBG_DLL2) $(LIB_INTRINSICS) $(LIB_VECTFUNC)
	@echo Generating: $@
	$(ECHO) @mkdir -p $(dir $@)
	$(ECHO) $(CXX) $(CXXFLAGS) $(USE_PTHREAD) $^ $(CPPFLAGS) -o $@
endif
ifeq ($(UNAME),GNU/Linux)
Test_Executable = $(TEST_RUN_DIR)/$(TEST_NAME)
else
Test_Executable = $(TEST_RUN_DIR)/$(TEST_NAME).exe
endif

PATH:=$(PATH):$(TEST_LIB_DIR)
export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(TEST_LIB_DIR)

DUMMY_MAKEFILE_NAME=$(if $(MVCV_UNITTEST_BUILD_WITH_NEXTGEN),newMakefile.mk,Makefile)

# House-keeping build targets.

all : $(UNIT_TEST_LIST) Makefile
	@if [ "$(VCS_TEST_BUILD)" = "true" ]; then \
		$(MAKE) -C $(KERNEL_APP_PATH) -f $(DUMMY_MAKEFILE_NAME) all VCS_TEST_BUILD=true; \
	else \
		$(MAKE) -C $(KERNEL_APP_PATH) -f $(DUMMY_MAKEFILE_NAME) all; \
	fi

run_test:
	@echo LD_LIBRARY_PATH=$(LD_LIBARY_PATH)
	$(Test_Executable) $(SRV_IP) $(srvPort)

dummy2:
	echo $(Test_Executable) $(SRV_IP) $(SRV_PORT)

run_test_auto:
	@if [ "$(srvIP)" = "" -o "$(srvPort)" = "" ]; then \
		echo "Error: srvIP and srvPort variables must be not empty when running with run_test_auto target"; \
		exit 1; \
	fi; \
	$(Test_Executable) -srvIP: $(srvIP) -srvPort: $(srvPort)

sim:
	( \
		MOVISIM_PORT=$$($(MV_COMMON_BASE)/scripts/movisim/get_movisim_port.sh) ; \
		echo "Got free port $$MOVISIM_PORT" ; \
		MOVISIM_LAUNCH_RETRY_COUNT=0 ; \
		until [ $$MOVISIM_LAUNCH_RETRY_COUNT -ge $(MOVISIM_INIT_RETRY_COUNT) ] ; \
		do \
			$(MVSIM) $(MVSIMOPT) $(otherMovisimOptions) $(debugOptions) -ca -tcpip:$$MOVISIM_PORT -darw -v:4 > leonos_movisim.lst & \
			MOVISIM_PID=$! ; \
			jobs %% && break ; \
			MOVISIM_LAUNCH_RETRY_COUNT=$$[$$MOVISIM_LAUNCH_RETRY_COUNT+1] ; \
		done ; \
		while [ -z "$$(ss -ln | grep $$MOVISIM_PORT)" ] ; do sleep 0.1 ; done ; \
		$(Test_Executable) -srvIP: 127.0.0.1 -srvPort: $$MOVISIM_PORT ; \
		$(MV_COMMON_BASE)/scripts/movisim/release_movisim_port.sh $$MOVISIM_PORT \
	)

run_seed:
	@if [ "$(SEED_VAL)" = "" ]; then \
		echo "Error: SEED_VAL variable must be not empty when running with run_seed"; \
		exit 1; \
	fi; \
	$(Test_Executable) -useSeed: $(SEED_VAL)


isGTestProject:
	@echo $(GTEST_PROJ_STRING)

clean :
	@echo "Cleaning ..."
	$(ECHO) rm -f gtest.a gtest_main.a *.o
	$(ECHO) rm -fr $(TEST_OUT_DIR)
	$(ECHO) rm -fr $(TEST_RUN_DIR)
	$(ECHO) @cd $(KERNEL_APP_PATH); $(MAKE) -f $(DUMMY_MAKEFILE_NAME) clean
	@echo "Done"

help:
	@echo "'make help'                      : show this message"
	@echo "'make all'                       : build everything"
	@echo "'make clean'                     : Clean all built files: Google Test, unit test,"
	@echo "                                   and dummy app files"
	@echo "'make clean_lib'                 : Clean the MvCv/MvISP library"
	@echo "'make run_test'                  : build everything and run the unit test"
	@echo "                                   executable"
	@echo "'make run_test_auto'             : build everything and run the unit test"
	@echo "                                   executable on a remote PC"
	@echo "'make start_server'              : starts moviDebug server"
	@echo "'make start_simulator'           : starts moviSim in quiet mode"
	@echo "'make start_simulator_full'      : starts moviSim in verbose full mode"
	@echo "Optional Parameters:"
	@echo "srvIP=192.168.1.100              : Connect to moviDebugserver on a different PC"
	@echo "srvPort=30001                    : Connect to moviDebugserver on a different PC"
	@echo "DBGI=jtag                        : Change the debug interface (moviSim by default)"
	@echo "VCS_TEST_BUILD=true              : Creates .elf file for each test"
	@echo "VERBOSE=yes                      : Echo full build commands during make"
	@echo
