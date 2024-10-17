# Asteroids

## How It Works And What It Is

- This is our own version of the popular game asteroids. Press left, right, up, and down arrows to avoid falling asteroids in order to get the highest score. If you collide with an asteroid your game will end.
- Shooting: Press space bar to shoot at the asteoirds, one bullet will kill them, but you cannot spam the shooting in order to make it harder.
- Press ``Enter`` then enter your name and then press ``Enter`` again. Then press ``esc`` to leave the game.

### How It Works
- Ship is created in our ``drawPlayer()`` function
- ``Keyboard()`` and ``specialKeys()`` functions are used to process user inputs from the keyboard
- ``drawAsteroids()``  and ``drawasteroidcircle()`` is where we draw the asteroids that fall from the sky
- There are a few other smaller functions which are self names and should be easy to understand




## How To Compile And Run

- For linux machines like used in CSIL:
```g++ main.cpp lib/player.cpp lib/game.cpp lib/asteroid.cpp -std=c++17 -lGL -lglut```
- That should create an a.out executable which you can run by typing
```./a.out```
- To run the game again, simply re-enter ```./a.out```





## File Organization

All source code is in the ``src/`` directory, which contains:

```
- main.cpp
- lib/
  - highscore.txt
  - asteroids.h
  - asteroids.cpp
  - game.h
  - game.cpp
  - asteroid.cpp
  - asteroid.h

```
