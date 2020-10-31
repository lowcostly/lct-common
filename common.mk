######################################################################
 # @copyright    Copyright (C), 2017
 # @file         common.mk
 # @version      1.0
 # @date         Jun 8, 2017 5:18:16 PM
 # @author       wayfarerly@yahoo.com
 # @brief        TODO
 #####################################################################

ifeq ($(AARCH64) , true)
	CXX = aarch64-himix100-linux-c++
else
	CXX = g++
endif

GCC_VERSION = $(shell $(CXX) --version | grep ^$(CXX) | sed 's/^.* //g' | awk '{print substr($$1,1,1)}')

ifeq "$(GCC_VERSION)" "8"
    CPP_STD = c++17
else
    CPP_STD = c++14
endif

CPP_FLAGS_DEFAULT   = -g -O2 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function --std=$(CPP_STD) -fno-strict-aliasing
CPP_FLAGS_LOOSE     = -g -O1 -Wall -Wextra -Werror -Wredundant-decls -Wno-unused-parameter -Wno-unused-function -Wno-shadow --std=$(CPP_STD)
CPP_FLAGS_STRICT    = -g -O3 -Wall -Wextra -Werror -Wcast-qual -Wredundant-decls -Wno-unused-parameter -Wno-unused-function -Wno-shadow --std=$(CPP_STD)
CPP_FLAGS_DEBUG     = -g -O0 -Wall -Wextra -Werror -Wcast-qual -Wredundant-decls -Wno-unused-parameter -Wno-unused-function -Wno-shadow --std=$(CPP_STD)
CPP_FLAGS_RELEASE   = -O2 -Wall -Wextra -Werror -Wredundant-decls -Wno-unused-parameter -Wno-unused-function -Wno-shadow ---std=$(CPP_STD)
CPP_FLAGS_3rd       = -O3 --std=$(CPP_STD)

ifndef SYSTEM
	export OS_NAME         := $(shell uname -s)
	export PROCESSOR_NAME  := $(shell uname -p)
	export SYSTEM          := ${OS_NAME}-$(PROCESSOR_NAME)
endif

ifeq ($(AARCH64) , false)
	CPP_FLAGS_DEFAULT   += -DNVIDIA_GPU_CODEC
endif

ifdef CPP_FLAG
	CPP_FLAG_FINAL := $(CPP_FLAG)
else
	CPP_FLAG_FINAL := $(CPP_FLAGS_DEFAULT)
endif

ifndef SRC_DIR
	SRC_DIR := ./
endif

VERSION := v1.0.0
BUILD   := `git rev-parse --short HEAD`

VPATH           := $(SRC_DIR)
CPPS            := $(foreach dir, $(VPATH), $(wildcard $(dir)/*.$(SRC_SUFFIX)))
OBJS            := $(patsubst %.$(SRC_SUFFIX), %.o, $(notdir $(CPPS)))
DEPS            := $(patsubst %.$(SRC_SUFFIX), %.d, $(notdir $(CPPS)))

ifeq ($(SRC_POST_PATH), )
CURR_BASE_DIR   := $(notdir $(CURR_DIR_PATH))
else
CURR_BASE_DIR   := $(SRC_POST_PATH)
endif

BUILD_OUT_ROOT  := $(LCT_SVC_PRJ_ROOT)/build
BUILD_OBJ_ROOT  := $(BUILD_OUT_ROOT)/obj
BUILD_OBJ_DIR   := $(BUILD_OBJ_ROOT)/$(CURR_BASE_DIR)
LIB_DIR         := $(BUILD_OUT_ROOT)/lib



ifeq ($(TARGET_TYPE), app)
	FIXED_TARGET_DIR    := $(BUILD_OUT_ROOT)/bin
else ifeq ($(TARGET_TYPE), lib)
	FIXED_TARGET_DIR    := $(BUILD_OUT_ROOT)/lib
else
	FIXED_TARGET_DIR    := $(BUILD_OBJ_DIR)
endif

FIXED_TARGET    := $(addprefix $(FIXED_TARGET_DIR)/, $(TARGET))
FIXED_OBJS      := $(addprefix $(BUILD_OBJ_DIR)/, $(OBJS))
FIXED_DEPS      := $(addprefix $(BUILD_OBJ_DIR)/, $(DEPS))

all debug release build:$(FIXED_OBJS)
ifneq ($(BUILD_OUT_ROOT), $(wildcard $(BUILD_OUT_ROOT)))
	@mkdir -p $(BUILD_OUT_ROOT)
endif

ifneq ($(FIXED_TARGET_DIR), $(wildcard $(FIXED_TARGET_DIR)))
	@mkdir -p $(FIXED_TARGET_DIR)
endif

	@echo 'Building target: $@'
ifeq ($(TARGET_TYPE), app)
	$(CXX) $^ $(DEP_OBJ) $(SYS_LIB_DIR) $(SYS_LIB) -o $(FIXED_TARGET) 
else ifeq ($(TARGET_TYPE), lib)
	ar -r $(FIXED_TARGET) $(FIXED_OBJS)
else 
.PHONY: $(TARGET)
endif
	@echo 'Finished building target: $@'
	@echo ' '

-include $(FIXED_DEPS)

$(BUILD_OBJ_DIR)/%.o:%.$(SRC_SUFFIX)
ifneq ($(BUILD_OBJ_DIR), $(wildcard $(BUILD_OBJ_DIR)))
	@mkdir -p $(BUILD_OBJ_DIR)
endif

	@echo "Start building $@"
	$(CXX) $(CPP_FLAG_FINAL) $(INC_DIR) -o $@ -c $< -MMD -MF"$(@:%.o=%.d)"
	@echo "Finished building $@"
	@echo " "

clean: cleanObj
	rm -fr $(FIXED_TARGET_DIR)
	rm -fr $(BUILD_OBJ_DIR)
	rm -fr $(BUILD_OBJ_ROOT)
	@echo " "

cleanObj:
	rm -fr $(BUILD_OBJ_DIR)/*
	rm -f $(FIXED_OBJS)
	rm -f $(FIXED_DEPS)
	rm -f $(FIXED_TARGET)
	@echo " "

rebuild:cleanObj all

.PHONY:clean cleanObj rebuild image


