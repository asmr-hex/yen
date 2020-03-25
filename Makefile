# -----------------------------  c o m m o n  -------------------------------


OS                  := $(shell uname -s)


CXX                 := g++ -std=c++17
CXXFLAGS            := -Wall #-Wextra -Werror


INCLUDE_DIR         := ./vendor
INCLUDE             := -I/usr/include/rtmidi -I/usr/local/Cellar/rt-audio/5.1.0/include/rtaudio

LIBS                :=  -lrtaudio -lrtmidi -lyaml-cpp

BUILD_DIR           := ./build
OBJ_DIR             := $(BUILD_DIR)/objects
BIN_DIR             := $(BUILD_DIR)/bin


# -----------------------------  b i n a r y  -----------------------------


SRC_DIR      := src
YEN_DIR      := $(SRC_DIR)/yen

INCLUDE      += -I$(SRC_DIR) -I$(INCLUDE_DIR)/RxCpp/Rx/v2/src -I$(INCLUDE_DIR)/AudioFile

BIN_TARGET   := yen
YEN_SRC      := $(shell find $(YEN_DIR) -type f -name '*.cpp')
BIN_SRC      := $(YEN_SRC) $(SRC_DIR)/main.cpp
BIN_OBJECTS  := $(BIN_SRC:%.cpp=$(OBJ_DIR)/%.o)


CONF         := ./config.yml


# -----------------------------  c o m m a n d s  -------------------------


# list all phony targets, i.e. non-file target commands
.PHONY: all build clean debug default packages release


default: build


all: packages clean clean release


$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# binary target
$(BIN_DIR)/$(BIN_TARGET): $(BIN_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LIBS) -o $(BIN_DIR)/$(BIN_TARGET) $(BIN_OBJECTS)


# binary target (alias)
build: $(BIN_DIR)/$(BIN_TARGET)


debug: CXXFLAGS += -DDEBUG -g
debug: build
	@sudo gdb --args $(BIN_DIR)/$(BIN_TARGET) $(CONF)


release: CXXFLAGS += -O2
release: build


run: build
	@$(BIN_DIR)/$(BIN_TARGET) $(CONF)


clean:
	-@rm -rvf $(BUILD_DIR)

