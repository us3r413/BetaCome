#include <unordered_map>
#include <iostream>
#include <stdlib.h>
#include "../Pieces/pawn.h"
#include "../Pieces/rook.h"
#include "../Pieces/knight.h"
#include "../Pieces/bishop.h"
#include "../Pieces/queen.h"
#include "../Pieces/king.h"

class CBoard
{
public:
    CBoard() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                MainGameBoard[iRow][iCol] = 0;
            }
        }
        // Allocate and place black pieces
        for (int iCol = 0; iCol < 8; ++iCol) {
            MainGameBoard[6][iCol] = new PawnPiece('B');
        }
        MainGameBoard[7][0] = new RookPiece('B');
        MainGameBoard[7][1] = new KnightPiece('B');
        MainGameBoard[7][2] = new BishopPiece('B');
        MainGameBoard[7][3] = new KingPiece('B');
        MainGameBoard[7][4] = new QueenPiece('B');
        MainGameBoard[7][5] = new BishopPiece('B');
        MainGameBoard[7][6] = new KnightPiece('B');
        MainGameBoard[7][7] = new RookPiece('B');
        // Allocate and place white pieces
        for (int iCol = 0; iCol < 8; ++iCol) {
            MainGameBoard[1][iCol] = new PawnPiece('W');
        }
        MainGameBoard[0][0] = new RookPiece('W');
        MainGameBoard[0][1] = new KnightPiece('W');
        MainGameBoard[0][2] = new BishopPiece('W');
        MainGameBoard[0][3] = new KingPiece('W');
        MainGameBoard[0][4] = new QueenPiece('W');
        MainGameBoard[0][5] = new BishopPiece('W');
        MainGameBoard[0][6] = new KnightPiece('W');
        MainGameBoard[0][7] = new RookPiece('W');
    }
    ~CBoard() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                delete MainGameBoard[iRow][iCol];
                MainGameBoard[iRow][iCol] = 0;
            }
        }
    }

    void Print() {
        using namespace std;
        cout<< "  A B C D E F G H\n";
        for (int i = 0; i < 8; ++i) {
            cout << i + 1 << " ";
    
            for (int j = 0; j < 8; ++j) {
                GamePiece* cell = MainGameBoard[i][j];
                int piece = 0;
                if (cell) {
                    switch (cell->GetPiece()) {
                        case 'P': piece = 1; break;
                        case 'R': piece = 2; break;
                        case 'N': piece = 3; break;
                        case 'B': piece = 4; break;
                        case 'Q': piece = 5; break;
                        case 'K': piece = 6; break;
                        default: piece = 0; break;
                    }
    
                    if (cell->GetColor() != 'W') {
                        piece = -piece;
                    }
                }
                cout << valueToEmoji[piece] << " ";
            }
            cout << endl;
        }
    }

    bool IsInCheck(char PieceColor) {
        // Find the king
        int iKingRow;
        int iKingCol;
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        if (MainGameBoard[iRow][iCol]->GetPiece() == 'K') {
                            iKingRow = iRow;
                            iKingCol = iCol;
                        }
                    }
                }
            }
        }
        // Run through the opponent's pieces and see if any can take the king
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    if (MainGameBoard[iRow][iCol]->GetColor() != PieceColor) {
                        if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iKingRow, iKingCol, MainGameBoard)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool CanMove(char PieceColor) {
        // Run through all pieces
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    // If it is a piece of the current player, see if it has a legal move
                    if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
                            for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
                                if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iMoveRow, iMoveCol, MainGameBoard)) {
                                    // Make move and check whether king is in check
                                    GamePiece* qpTemp                   = MainGameBoard[iMoveRow][iMoveCol];
                                    MainGameBoard[iMoveRow][iMoveCol]   = MainGameBoard[iRow][iCol];
                                    MainGameBoard[iRow][iCol]           = 0;
                                    bool bCanMove = !IsInCheck(PieceColor);
                                    // Undo the move
                                    MainGameBoard[iRow][iCol]           = MainGameBoard[iMoveRow][iMoveCol];
                                    MainGameBoard[iMoveRow][iMoveCol]   = qpTemp;
                                    if (bCanMove) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    GamePiece* MainGameBoard[8][8];

    std::unordered_map<int,std::string> valueToEmoji = {
        {1,"♟"}, {2,"♜"}, {3,"♞"}, {4,"♝"}, {5,"♛"}, {6,"♚"},
        {-1,"♙"},{-2,"♖"},{-3,"♘"},{-4,"♗"},{-5,"♕"},{-6,"♔"},
        {0,"."}
    };
};