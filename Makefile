OBJ_DIR := objs
LIB_DIR := libs
BIN_DIR := bins
DEP_DIR := deps
SRC_DIR := srcs

OBJ_SUFFIX := .o
DEP_SUFFIX := .d

LIB_STATIC_PREFIX := lib
LIB_SHARED_PREFIX := lib
LIB_STATIC_SUFFIX := .a

ifndef HOME
  $(error "Not compatible OS")
endif

OSTYPE := $(shell uname -s)
ifneq (,$(or $(filter CYGWIN,$(OSTYPE)),$(filter MSYS,$(OSTYPE))),$(filter MINGW,$(OSTYPE)))
  EXE_SUFFIX := .exe
  LIB_SHARED_SUFFIX := .dll
endif
ifeq ($(OSTYPE),Linux)
  EXE_SUFFIX := 
  LIB_SHARED_SUFFIX := .so
  CFLAGS += -fPIC
  CXXFLAGS += -fPIC
endif

CC := gcc
CXX:= g++
AR := ar
LD := ld
RM := rm -rf
MKDIR := mkdir -p
CFLAGS   += -O3 -Wall
CXXFLAGS += -O3 -Wall
ARCMDS   := rcs

LIB_MC_SRCS := myclass.cpp
LIB_PR_SRCS := print_num.c print_str.cpp
LIB_UT_SRCS := conv.c
LIB_MA_SRCS := power.c
LIB_STR_SRCS := strng.c

APP_SRCS := main.cpp
APP_OBJS := $(patsubst %,$(OBJ_DIR)/%$(OBJ_SUFFIX),$(basename $(APP_SRCS)))

# define GetObjNames =
# 	$(eval para := $(strip $(1)))
# 	$(eval srcs := $(LIB_$(para)_SRCS))
# 	$(eval srcc := $(filter %.c, $(srcs)))
# 	$(eval objs := $(srcc:.c=$(OBJ_SUFFIX)))
# 	$(eval srcx := $(filter %.cpp, $(srcs)))
# 	$(eval objs += $(srcx:.cpp=$(OBJ_SUFFIX)))
# 	$(eval LIB_$(para)_OBJS := $(addprefix $(OBJ_DIR)/,$(objs)))
# endef

define GetObjNames =
	$(eval para := $(strip $(1)))
	$(eval srcs := $(LIB_$(para)_SRCS))
	$(eval LIB_$(para)_OBJS := $(patsubst %,$(OBJ_DIR)/%$(OBJ_SUFFIX),$(basename $(srcs))))
endef

# # A macro for converting a string to uppercase
# uppercase_TABLE:=a,A b,B c,C d,D e,E f,F g,G h,H i,I j,J k,K l,L m,M n,N o,O p,P q,Q r,R s,S t,T u,U v,V w,W x,X y,Y z,Z

# define uppercase_internal
# $(if $1,$$(subst $(firstword $1),$(call uppercase_internal,$(wordlist 2,$(words $1),$1),$2)),$2)
# endef

# define uppercase
# $(eval uppercase_RESULT:=$(call uppercase_internal,$(uppercase_TABLE),$1))$(uppercase_RESULT)
# endef

# # A macro for converting a string to lowercase
# lowercase_TABLE:=A,a B,b C,c D,d E,e F,f G,g H,h I,i J,j K,k L,l M,m N,n O,o P,p Q,q R,r S,s T,t U,u V,v W,w X,x Y,y Z,z

# define lowercase_internal
# $(if $1,$$(subst $(firstword $1),$(call lowercase_internal,$(wordlist 2,$(words $1),$1),$2)),$2)
# endef

# define lowercase
# $(eval lowercase_RESULT:=$(call lowercase_internal,$(lowercase_TABLE),$1))$(lowercase_RESULT)
# endef

lowercase = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,\
$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,\
$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,\
$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,\
$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

LIB_NAMES := MC PR UT MA STR

$(foreach n, $(LIB_NAMES), $(eval $(call GetObjNames, $(n))))
#$(foreach n, $(LIB_NAMES), $(info LIB_$(n)_OBJS:$(LIB_$(n)_OBJS)))

$(foreach n, $(LIB_NAMES) ONE, $(eval LIB_$(n)_NAME := $(call lowercase,$(n))))
#$(foreach n, $(LIB_NAMES) ONE, $(info LIB_$(n)_NAME:$(LIB_$(n)_NAME)))

$(foreach n, $(LIB_NAMES), $(eval LIB_$(n)_FILE := $(LIB_DIR)/$(LIB_STATIC_PREFIX)$(LIB_$(n)_NAME)$(LIB_STATIC_SUFFIX)))
#$(foreach n, $(LIB_NAMES), $(info LIB_$(n)_NAME:$(LIB_$(n)_FILE)))
LIB_FILES := $(foreach n, $(LIB_NAMES), $(LIB_$(n)_FILE))

DEP_FILES := $(foreach n, $(LIB_NAMES),$(patsubst %,$(DEP_DIR)/%$(DEP_SUFFIX),$(basename $(LIB_$(n)_SRCS))))
DEP_FILES += $(patsubst %,$(DEP_DIR)/%$(DEP_SUFFIX),$(basename $(APP_SRCS)))
#$(error $(DEP_FILES))

# define multiple targets with same actions
# libs/libxx.a: xxx.o...
# 	$(AR) $(ARCMDS) $@ $^
define make-libs
$(1): $(2)
	$(AR) $(ARCMDS) $$@ $$^
endef

.PHONY: all
all: dirs $(BIN_DIR)/app_s$(EXE_SUFFIX) $(BIN_DIR)/app_d$(EXE_SUFFIX)

$(foreach n, $(LIB_NAMES), $(eval $(call make-libs,$(LIB_$(n)_FILE),$(LIB_$(n)_OBJS))))

.PHONY: dirs
dirs: $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(DEP_DIR)
$(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(DEP_DIR): 
	$(MKDIR) $@

$(OBJ_DIR)/%$(OBJ_SUFFIX): $(SRC_DIR)/%.c
$(OBJ_DIR)/%$(OBJ_SUFFIX): $(SRC_DIR)/%.c $(DEP_DIR)/%$(DEP_SUFFIX)
	$(CC) $(CFLAGS) -MT $@ -MMD -MP -MF $(DEP_DIR)/$(*F)$(DEP_SUFFIX) -o $@ -c $<

$(OBJ_DIR)/%$(OBJ_SUFFIX): $(SRC_DIR)/%.cpp
$(OBJ_DIR)/%$(OBJ_SUFFIX): $(SRC_DIR)/%.cpp $(DEP_DIR)/%$(DEP_SUFFIX)
	$(CXX) $(CXXFLAGS) -MT $@ -MMD -MP -MF $(DEP_DIR)/$(*F)$(DEP_SUFFIX) -o $@ -c $<

LIB_ONE_STA=$(LIB_DIR)/$(LIB_STATIC_PREFIX)$(LIB_ONE_NAME)$(LIB_STATIC_SUFFIX)
LIB_ONE_DYN=$(BIN_DIR)/$(LIB_SHARED_PREFIX)$(LIB_ONE_NAME)$(LIB_SHARED_SUFFIX)

$(LIB_ONE_STA): $(LIB_FILES)
	-$(RM) $@
	$(AR) rsT $@ $^

$(LIB_ONE_DYN): $(LIB_ONE_STA)
	$(CXX) -shared -Wl,-soname,$(LIB_ONE_DYN) -o $(LIB_ONE_DYN) -Wl,-whole-archive $^ -Wl,-no-whole-archive
#	$(CXX) -shared -Wl,-soname,$(LIB_ONE_DYN) -Wl,--export-all-symbols -o $(LIB_ONE_DYN) -Wl,-whole-archive $^ -Wl,-no-whole-archive

$(BIN_DIR)/app_s$(EXE_SUFFIX): $(APP_OBJS) $(LIB_ONE_STA)
	$(CXX) -o $@ $(APP_OBJS) -L$(LIB_DIR) -Wl,-Bstatic -l$(LIB_ONE_NAME) -Wl,-Bdynamic

# in cygwin, if there're same basenamed in one directory 
# for static library and dynamic library, like libfoo.a and libfoo.dll,
# and expect to link the dynamic library, I have to use "-Wl,-Bdynamic -llibfoo"
$(BIN_DIR)/app_d$(EXE_SUFFIX): $(APP_OBJS) $(LIB_ONE_DYN)
	$(CXX) -o $@ $(APP_OBJS) -L$(BIN_DIR) -Wl,-Bdynamic -l$(LIB_ONE_NAME)

.PRECIOUS = $(DEP_DIR)/%.d
$(DEP_DIR)/%.d: ;
-include $(DEP_FILES)

.PHONY:clean
clean:
	$(RM) $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(DEP_DIR)
