# the build target
all: game

# builds the game using both of the source files
game: main.cpp GuessingGame.cpp 
	g++ main.cpp GuessingGame.cpp -o game

# cleans up the compiled files
clean:
	rm -f game