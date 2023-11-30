# *Over-Engineered Tic-Tac-Toe*(CLI-TicTacToe)

---

## *Synopsis*

---

* This repository is my attempt at dynamic CLI tic-tac-toe and my first-ever feature-complete C++ project! This implementation supports any row-by-column combination in between 3x3 and 55x55.

---

## *Downloading*

---

#### *Requirements::*

* must have ***git installed locally*** if you're going to use `git clone`
  
#### *Cloning from GitHub::*

* `cd` <*full-path/where git should clone the repo*>

* From command line: `git clone` <https://github.com/SolomonKnudson/CLI-TicTacToe.git>

  ![ALT text][gitCloneCommand]

#### *Using Zip provided by github::*

* Click on green code button

  ![ALT text][codeButton]

* Click *download zip*

  ![ALT text][codeDropDown]

* Un-zip directory, you just downloaded, where you want the project located on your machine  

---

## *Building*

---

### *Supported Platforms:*

* Windows

* Linux

---

#### *Requirements::*

1. Must have ***cmake installed*** if you plan of following my ***cmake build instructions*** or using the ***CMakeLists.txt*** provided by the repository

1. Must be able to run c++ files on your machine

#### *From command line::*

* `cd` <*full-path/repo name*>

* `mkdir` <*build directory name*>

* `cd` <*build directory*>

* ***FROM COMMAND LINE: INSIDE BUILD DIRECTORY::*** `cmake -S .. -B .`

  ![ALT text][buildInsideBuildDir]

* ***FROM COMMAND LINE: INSIDE REPO ROOT DIRECTORY::*** `cmake` -S . -B <*build directory*>

  ![ALT text][buildInsideRepoRootDir]

* ***FROM COMMAND LINE: ANY DIRECTORY::*** `cmake` -S <*full-path/CLI-TicTacToe/*> -B <*full-path/CLI-TicTacToe/<*build directory*>*>

  ![ALT text][buildFromAnyDir]

---

## *Running Code*

---
* Build excutable

  ![ALT][buildExcutable]

* Run excutable

  ![ALT text][runExcutable]

---

## *Game Rules*

---

* Wins are calculated by counting the number of board slots the current player has in a row and seeing if it's equal to whichever side of the board is smaller. Winner always starts.

* If playing on a 4x8 board, players must get 4 in a row vertically/diagonally and 8 laterally.

* *Lateral:*
  
  ![ALT text][4x8LatWin]

* *Vertical:*
  
  ![ALT text][4x8VertWin]

* *Diagonal:*
  
  ![ALT text][4x8DiaWin]

* *Tie:*

  ![ALT text][tieGame]

* Players are not allowed to make duplicate moves. Doing so will result in a warning from the game.
  
  ![ALT text][illegalMoveWarning]

* Players are permitted four illegal moves per game. Any player that exceeds four illegal moves will forfeit their current turn, as well as all subsequent turns resulting in an illegal move.
  
  ![ALT text][forfeitMoves]

---

## *Features*

---

* *Dynamic Board:*

  * *Limitations:*

    * Minimum size allowed: Row and Column individually must be > 3

    * Max size allowed: Row by Column must be <= 55x55(3025)

* Displays complete chronological match history
  
   ![ALT text][chronoMatchHist]

* Can automatically set the board in winning configuration to test different board sizes

  ![ALT text][testBoard]

* *Debug commands:*

  * *setL {value}:* used to set the board in a lateral win config starting at {value}.
  
    ![ALT text][setLDemo]

  * *setV {value}:* used to set the board in a vertical win config starting at {value}.

    ![ALT text][setVDemo]

  * *setD {value}:* used to set the board in a diagonal win config starting at {value}.

    ![ALT text][setDDemo]

  * *setDr {value}:* used to set the board in a diagonal win config, starting at {value}, but in reverse.

    ![ALT text][setDrDemo]

  * *endGame:* used to end the game.

    ![ALT text][endGame]

---

### *Limitations::*

* Board max size: 55x55: due to it being the biggest I can display in my local command prompt, as well as my naive algorithms being too slow once past 1000x1000

---

[codeButton]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/Installing/codeButton.png
[codeDropDown]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/Installing/codeDropDown.png

[gitCloneCommand]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/Installing/gitCloneCommand.gif

[buildInsideBuildDir]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/LinuxBuild/buildInsideBuildDir.gif
[buildInsideRepoRootDir]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/LinuxBuild/buildInsideRepoRootDir.gif
[buildFromAnyDir]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/LinuxBuild/buildFromAnyDir.gif

[buildExcutable]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/LinuxBuild/buildExcutable.gif
[runExcutable]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/runExcutable.gif

[4x8LatWin]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/GameRules/4x8LatWin.png
[4x8VertWin]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/GameRules/4x8VertWin.png
[4x8DiaWin]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/GameRules/4x8DiaWin.png
[tieGame]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/GameRules/tieGame.png

[illegalMoveWarning]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/GameRules/illegalMoveWarning.png
[forfeitMoves]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/GameRules/foreitMoves.png
[chronoMatchHist]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/Features/chronoMatchHist.png
[testBoard]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/Features/testBoard.gif

[setLDemo]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/CommandDemos/setLDemo.gif
[setVDemo]:https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/CommandDemos/setVDemo.gif
[setDDemo]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/CommandDemos/setDDemo.gif
[setDrDemo]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/CommandDemos/setDrDemo.gif
[endGame]: https://github.com/SolomonKnudson/CLI-TicTacToe/blob/main/img/CommandDemos/endGameDemo.gif
