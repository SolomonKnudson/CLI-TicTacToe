# *Over-Engineered Tic-Tac-Toe*(CLI-TicTacToe)

---

## *Synopsis*

This repository is my attempt at dynamic CLI tic-tac-toe. This implementation supports any row-by-column combination in between 3x3 and 55x55.

## *Building*

---
TODO

## *Game Rules*

---

* Wins are calculated by counting the number of board slots the current player has in a row and seeing if it's equal to whichever side of the board is smaller.

* If playing on a 4x8 board, players must get 4 in a row vertically/diagonally and 8 laterally.

* *Lateral*:
* ![ALT text][4x8LatWin]

* *Vertical*:
* ![ALT text][4x8VertWin]

* *Diagonal*
* ![ALT text][4x8DiaWin]

* Players are not allowed to make duplicate moves. Doing so will result in a warning from the game.
* ![ALT text][illegalMoveWarning]

* Players are permitted four illegal moves per game. Any player that exceeds four illegal moves will forfeit their current turn, as well as all subsequent turns resulting in an illegal move.
* ![ALT text][forfeitMoves]

---

## *Features*

---

* *Dynamic Board:*

  * *Limitations:*

    * Minimum size allowed: Row and Column individually must be > 3

    * Max size allowed: Row by Column must be <= 55x55(3025)

* Displays complete chronological match history

* Can automatically set the board in winning configuration to test different board sizes

* *Debug commands:*

  * *setL {value}:* used to set the board in a lateral win config starting at {value}.
  
    ![ALT text][setLDemo]

  * *setV {value}:* used to set the board in a vertical win config starting at {value}.
 
    ![ALT text][setVDemo]

  * *setD {value}:* used to set the board in a diagonal win config starting at {value}.
 
    ![ALT text][setDDemo] 

  * *setDr {value}:* used to set the board in a diagonal win config, starting at {value}, but in reverse.
 
    ![ALT text][setDrDemo] 

---

## *Limitations:*

  * Board max size: 55x55: due to it being the biggest I can display in my local command prompt, as well as my naive algorithms being too slow once past 1000x1000





[4x8LatWin]: https://i.imgur.com/GiVTRLQ.png
[4x8VertWin]: https://i.imgur.com/a5qMDuz.png
[4x8DiaWin]: https://i.imgur.com/5hp2DmH.png

[illegalMoveWarning]:  https://i.imgur.com/Pqw7mre.png
[forfeitMoves]: https://i.imgur.com/Uad3lgf.png

[setLDemo]: https://i.imgur.com/RhaTyAa.gif
[setVDemo]: https://i.imgur.com/RhaTyAa.gif
[setDDemo]: https://i.imgur.com/WIjINrl.gif
[setDrDemo]: https://i.imgur.com/61jeo2e.gif
