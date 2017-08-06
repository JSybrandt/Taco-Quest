CC=g++
LB=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CF=-g -Wall
OB=./obj
SR=./src
BN=./bin
GAME_NAME=game

# $@ - target
# $< - first dep
# $^ - all dep

all: dirs $(GAME_NAME)

$(GAME_NAME): $(BN)/$(GAME_NAME)
	ln -sf $<

$(BN)/$(GAME_NAME): $(SR)/main.cpp $(OB)/game.o $(OB)/settings.o $(OB)/constants.o $(OB)/player.o $(OB)/actor.o $(OB)/bullet.o
	$(CC) $(CF) -o $@ $^ $(LB)

$(OB)/game.o: $(SR)/game.cpp $(OB)/settings.o
	$(CC) $(CF) -c $^ $(LB) -o $@

$(OB)/settings.o: $(SR)/settings.cpp
	$(CC) $(CF) -c $^ $(LB) -o $@

$(OB)/constants.o: $(SR)/constants.cpp
	$(CC) $(CF) -c $^ $(LB) -o $@

$(OB)/player.o: $(SR)/player.cpp $(OB)/actor.o
	$(CC) $(CF) -c $^ $(LB) -o $@

$(OB)/bullet.o: $(SR)/bullet.cpp $(OB)/actor.o
	$(CC) $(CF) -c $^ $(LB) -o $@

$(OB)/actor.o: $(SR)/actor.cpp
	$(CC) $(CF) -c $^ $(LB) -o $@

dirs:
	mkdir -p $(OB)
	mkdir -p $(BN)

clean:
	rm -rf $(OB)
	rm -rf $(BN)



