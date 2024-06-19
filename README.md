# ♟️ Chess Game

This is a Chess Game project developed as part of the Object-Oriented Programming course at Seoul National University of Science and Technology (SeoulTech). The project was quickly put together in a day using C++.

## 🎥 Implementation Video
<a href="https://youtu.be/SfbcNh9sHxw"><img src="https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white"/></a>  

## 🛠️ Features
1. **Initial Piece Placement**: Pieces are placed in standard positions at the start of the game.
2. **Turn Management**: Turns alternate between players, and the current turn is indicated.
3. **Piece Selection**: Players can select pieces, and the selection is visually indicated.
4. **Valid Moves Highlighting**: Shows all possible moves for the selected piece.
5. **Piece Movement**: Allows players to move pieces to valid positions.
6. **Board Update**: The board updates to reflect moves, including capturing opponent pieces.
7. **Check/Checkmate Indication**: Visual and/or audio indication of check or checkmate situations.
8. **Game Result Display**: Displays the game's outcome, and disables further moves once a winner is determined.

![Chess Game Screenshot](https://github.com/foodinsect/C/assets/36304709/17703b38-441b-4f6a-a38e-f9c21cef1532)

## 🧩 Class Descriptions

### `ChessGame` Class
1. **paint()**
   - Calls the parent class `ChessBoard`'s paint method to draw the base chessboard.
   - Highlights the currently selected piece and possible move locations.
   - Displays the current game state (ongoing, check, win, etc.).

2. **mouseDown(int x, int y)**
   - Handles mouse click events to select or move pieces based on the clicked location.
   - Calculates possible moves for the selected piece and performs the move if valid.

3. **switchPlayer()**
   - Changes the current player, called at the end of a turn.

4. **calculatePossibleMoves(int x, int y)**
   - Computes all possible moves for the selected piece.

5. **movePiece(const std::pair<int, int>& from, const std::pair<int, int>& to)**
   - Moves a piece from one location to another, checks move validity, and updates the game state.

6. **isValidMove(...)**
   - Validates whether a move is legal for a given piece, implemented through the `Piece` class's `isValidMove` method.

7. **canSelect(int row, int col)**
   - Checks if the current player can select a piece at the given position.

8. **findKingPosition(Player currentPlayer)**
   - Finds the position of the current player's king.

9. **isCheck()**
   - Determines if the current player's king is in check.

### `ChessBoard` Class
1. **drawChessBoard()**
   - Draws each tile of the chessboard, with colors determined by position.

2. **initializeBoard()**
   - Places pieces in their initial positions at the start of the game.

3. **drawPieces()**
   - Renders each piece on the chessboard according to its type and position.

4. **drawText(const TCHAR text, int length, int x, int y)**
   - Draws text at the specified position.

5. **drawPiece(const Piece piece, int x, int y)**
   - Draws a specific piece at the given position.

### `Piece` Class and Subclasses
Each chess piece's movement rules are implemented in the `isValidMove` method of its respective class.

1. **Pawn**
   - Moves forward one square, or two squares from its initial position. Captures diagonally.

2. **Knight**
   - Moves in an 'L' shape: two squares in one direction and then one square perpendicular.

3. **Bishop**
   - Moves diagonally any number of squares, without jumping over other pieces.

4. **Rook**
   - Moves vertically or horizontally any number of squares, without jumping over other pieces.

5. **Queen**
   - Moves vertically, horizontally, or diagonally any number of squares.

6. **King**
   - Moves one square in any direction.

## 📫 Contact
- <a href="https://mail.google.com/mail/?view=cm&fs=1&to=opqrs0422@gmail.com"><img src="https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white"/></a>

---

