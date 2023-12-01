# arcade-cs32
CS 32 Scrypt Project

Elijah Williams, Liam Ronarch, Ran Chen, Tyler Canepa

## Coding Style

### Naming Conventions

- Function names: camelCase (example: ``getString``)
- Variable names: all lowercase; underscores for spaces (example: ``num_points``)
- Object names: first letter of each word is capitalized (example: ``MasterToken``)
- Constants: all caps; underscores for spaces (example: ``const int MAX_PTS = 100;``)
- Enumerations: same as a constant, but with a prefix (example: ``enum TokenType {TKN_PARENTH, TKN_OPER};``)

### Spacing

- 1 indent = 4 spaces
- Space between loop and condition (example: ``if (x == 1)``)
- No space between function name and arguments (example: ``getString(int& i);``)
- Spaces around operators (example: ``i += 4;``)
- Opening brackets for functions go on the same line (example: ``void printItems() {``)
- Space between closing parenthesis ``)`` and opening bracket ``{`` (example: ``void printItems() {``, not ``void printItems(){``)

## How It Works And What It Is

- This is our own version of the popular game asteroids. Press left, right, up, and down arrows to avoid falling asteroids in order to get the highest score. If you collide with an asteroid your game will end.

### How It Works
- Ship is created in our ``drawPlayer()`` function
- ``Keyboard()`` and ``specialKeys()`` functions are used to process user inputs from the keyboard
- ``drawAsteroids`` is where we draw the asteroids that fall from the sky
- There are a few other smaller functions which are self names and should be easy to understand




## How To Compile And Run

- For linux machines like used in CSIL:
```g++ main.cpp lib/player.cpp lib/game.cpp lib/asteroid.cpp -lGL -lglut```
- That should create an a.out executable which you can run by typing
```./a.out```
- To run the game again, simply re-enter ```./a.out```





## File Organization

All source code is in the ``src/`` directory, which contains:

```
- main.cpp
- lib/
  - asteroids.h
  - asteroids.cpp
  - game.h
  - game.cpp
  - asteroid.cpp
  - asteroid.h

```
