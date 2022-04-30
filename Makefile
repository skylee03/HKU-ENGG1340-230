# Predefined variables
FLAGS = -std=gnu++17 -I ~/local/include -I ~/local/include/ncurses -L ~/local/lib

# Build all
all: ncurses clean
	@echo "Building the whole game..."
	@make bin/game
	@echo "Done."

# Build targets
obj/leaderboard.o: src/leaderboard.cpp src/leaderboard.h
	@mkdir obj
	@echo "Compiling leaderboard.o..."
	@g++ $(FLAGS) -lncurses $< -g -c -o $@
	@echo "Done."

obj/interaction.o: src/interaction.cpp src/interaction.h
	@echo "Compiling interaction.o..."
	@g++ $(FLAGS) -lncurses $< -g -c -o $@
	@echo "Done."

obj/fileio.o: src/fileio.cpp src/fileio.h
	@echo "Compiling fileio.o..."
	@g++ $(FLAGS) -lncurses $< -g -c -o $@
	@echo "Done."

bin/game: src/main.cpp obj/leaderboard.o obj/interaction.o obj/fileio.o
	@mkdir bin
	@echo "Compiling game..."
	@g++ $(FLAGS) $^ -lncurses -g -o $@
	@mkdir -p log
	@touch log/leaderboard.txt
	@echo "Done."

# Build ncurses
ncurses:
	@echo "Building ncurses..."	
	@chmod +x getDependencies.sh
	@./getDependencies.sh
	@echo "Done."
	
# Clean build
clean:
	@echo "Cleaning build..."
	@rm -rf obj
	@rm -rf bin
	@echo "Done."
	
# Clean logs
clean-log:
	@echo "Cleaning logs..."
	@rm -rf log
	@echo "Done."

.PHONY: clean clean-log
