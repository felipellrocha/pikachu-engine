OUT_FILE := game

ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
OUT_DIR := out
INC_DIR := src
SRC_DIR := src
OBJ_DIR := obj/native

C := gcc
CXX := g++
LINKER := g++
INC_DIRS := -I$(INC_DIR)
C_FLAGS = \
	-Wall \
	-D NATIVE \
  -D DRAW_COLLISION \
	-pedantic \
	-g

CXX_FLAGS = \
	-std=c++11 \
	-std=c++14 \
	-Wall \
  -Wno-missing-braces \
	-D NATIVE \
  -D DRAW_COLLISION \
	-pedantic \
	-g
  #-D DRAW_FPS \

	#-Wextra \
	#-Wshadow \

EXEC_FLAGS = 
LIBS := -I /Library/Frameworks/SDL2.framework/Headers \
  -I /Library/Frameworks/SDL2_image.framework/Headers \
  -I /Library/Frameworks/SDL2_ttf.framework/Headers \
  -I /usr/local/Cellar/glew/2.1.0/include \
	-lglew \
  -framework SDL2 \
  -framework SDL2_image \
  -framework SDL2_ttf \
  -framework OpenGL

SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp' -o -name '*.c')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,   $(OBJ_DIR)/%.o, $(OBJ_FILES))
DEPFILES := $(patsubst  $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.d, $(SRC_FILES))
DEPFILES := $(patsubst  $(SRC_DIR)/%.c,   $(OBJ_DIR)/%.d, $(DEPFILES))

$(OUT_FILE): $(OBJ_FILES)
	$(LINKER) $(CXX_FLAGS) $(EXEC_FLAGS) $^ $(LIBS) -o $@

clean:
	rm -rf $(OBJ_DIR) $(OUT_FILE)

list:
	@echo "$(SRC_FILES)"
	@echo "$(OBJ_FILES)"

depends:
	rm -rf $(OBJ_DIR)/*.d
	$(MAKE) $(DEPFILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(C) $(C_FLAGS) $(INC_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(INC_DIRS) -c $< -o $@

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(INC_DIRS) -MM $< | tr '\n\r\\' ' ' | sed -e 's%^%$@ %' -e 's% % $(OBJ_DIR)/%' > $@

-include $(DEPFILES)
