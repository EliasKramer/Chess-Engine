# ChessCpp
I tried to program chess in c# before, but the program was terrible. <br>
So i started programming in c++ and made chess.
## Version 1:
This is my first project in c++.

I would call it "the normal approach". You start with a 8x8 array of pieces and work from there. <br>
The Problem with this solution is, that it is really slow.

I learned a lot in this first try, but it has some issues. <br>
So i made a minimum viable product (MVP) and started again.

It has no concept of checkmating, but that can be implemented easily in the future. <br>
(Now implemented in V2)

## Version 2:
I did a lot of research on the chess programming wiki and looked into some chess repos. <br>
Research:
- https://www.chessprogramming.org/Main_Page
- https://github.com/official-stockfish/Stockfish
- https://github.com/Gigantua/Gigantua

Then I started V2 with some major changes:

- bitboards
- fen-string setup implementation

Bitboards are basically a 64 bit number (unsigned long long), that can be used to represent a board of 0s and 1s. <br>
You can now use bitwise operations like '&', '|' or '^' to combine different bitboards. <br>
There is a really nice tool online to visiualize these boards: https://tearth.dev/bitboard-viewer/

A Fen String represents a board, so you can set up a testing position with only one short string. <br>
Description: https://www.chess.com/terms/fen-chess <br>
Set up a board: https://www.chess.com/analysis <br>

### V2 has 2 possible Players right now:
- HumanPlayer (A Player that plays with console input)
- RandomPlayer (A Player that picks its moves randomly)

## Future:
Adding an algorithm, that can actually win chess. <br>
