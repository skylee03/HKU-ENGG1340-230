<h1 align="center">Happy Eliminating</h1>

## Team Members

|Name|UID|GitHub|
|-|-|-|
|YANG Mingtian|3035845576|[skylee03](https://github.com/skylee03)|
|TU Huaqiang|3035772834|[Hawk-Tu](https://github.com/Hawk-Tu)|

## Game Description

- Initially, the board is filled with balloons in different colors and bombs.
- The player can eliminate three or more 8-connected balloons with the same color by selecting a not self-intersected path within the board. Once a balloon is eliminated, the bombs (if any) that are 8-connected with it will also be eliminated. The more bombs the player eliminate at a time, the higher the score they will get.
- However, if no bombs are eliminated after the operation, some random balloons will be replaced with bombs.
- After every operation, balloons and bombs that are no longer supported will fall down, and the vacancies will be filled with newly generated balloons.
- If all the bombs are eliminated, the player will advance to the next level, where there are more bombs.

## Game Features

1. Generation of random game sets or events
   - All the balloons and bombs are randomly generated. Player can also choose to manually enter a random seed.
2. Data structures for storing game status
   - class `Map`: store the content of the board.
   - class `Leaderboard`: store the leaderboard.
   - and some other data structures to be determined
3. Dynamic memory management
   - We use the `new` operator to allocate memory for the class objects and then call their object constructors. Pointers are used to store these memory addresses. Hence, when the game is over, we can use the `delete` operator to deallocate the memory allocated with the `new` operator.
4. File input/output (e.g., for loading/saving game status)
   - Before a game, the player can choose to load and continue a saved game.
   - During a game, the player can choose to save the game status. The status will be saved in `$HOME/.HappyEliminating/[timestamp].txt`.
   - After a game, the player can choose to upload the final score with their name to the Leaderboard. All the records will be saved in `$HOME/.HappyEliminating/leaderboard.txt`.
   - The player can also choose to delete a saved game or reset the leaderboard.
5. Program codes in multiple files
   - `./lib` includes the non-standard library files required by the code.
   - `./src` includes the source files:
     - `main.cpp`
     - and some other files to be determined
6. Proper indentation and naming styles
   - We mainly follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) but with some appropriate adjustments according to preferences.
7. In-code documentation

## External Libraries

We use [`ncurses`](https://invisible-island.net/ncurses/) to visualize the game as well as to accept inputs from both the keyboard and the mouse.
