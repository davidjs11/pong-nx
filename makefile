HOME	= .
BIN		= $(HOME)/bin
INCLUDE	= $(HOME)/include

all:
	@mkdir $(BIN)
	@gcc -o $(BIN)/main\
			src/main.c src/game.c src/graphics.c\
		  	src/inet.c src/sdl.c src/rendering.c\
			-I$(INCLUDE) -lSDL2 -D__PC__

	@gcc -o $(BIN)/server server.c\
			src/game.c src/inet.c -I$(INCLUDE) -D__PC__

clean:
	@rm -r $(BIN)/*
	@rmdir $(BIN)
