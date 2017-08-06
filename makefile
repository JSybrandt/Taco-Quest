CC=g++
GAME_NAME=tacoQuest

# $@ - target
# $< - first dep
# $^ - all dep

CPP_FILES := $(wildcard ./src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CC_FLAGS := -g -Wall -MMD


all: dirs $(GAME_NAME)

$(GAME_NAME): $(OBJ_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

dirs:
	mkdir -p ./obj

clean:
	rm -rf ./obj

