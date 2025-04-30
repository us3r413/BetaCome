#include "../Board/board.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
class ChessBoard
{
public:
    ChessBoard() : mcPlayerTurn('W') {}
    ~ChessBoard() {}

    void Start() {
        do {
            GetNextMove(mqGameBoard.MainGameBoard);
            AlternateTurn();
        } while (!IsGameOver());
        mqGameBoard.Print();
    }
    bool IsValidChessCoord(const std::string& coord) {
        return coord.length() == 2 &&
               isalpha(coord[0]) &&
               isdigit(coord[1]) &&
               toupper(coord[0]) >= 'A' && toupper(coord[0]) <= 'H' &&
               coord[1] >= '1' && coord[1] <= '8';
    }
    void GetNextMove(GamePiece* GameBoard[8][8]) {
        using namespace std;
        bool bValidMove     = false;
        do {
            system ("cls");
            cout<<endl<<endl<<"Chess "<<endl<<endl<<endl;
            cout<<"Valid syntax is :"<<endl;
            cout<<"Ex. A1 to A2 / Castling"<<endl<<endl;
            mqGameBoard.Print();

            // Get input and convert to coordinates
            cout << mcPlayerTurn << "'s Move: ";
            string iStartMove;
            cin >> iStartMove;
            string moveLower = iStartMove; // Copy original input
            transform(moveLower.begin(), moveLower.end(), moveLower.begin(), ::tolower);
            if(moveLower == "castling") {
                cout << "Which?\n>>";
                string castlingMove;
                cin >> castlingMove;
                if(!IsValidChessCoord(castlingMove)) {
                    continue;
                }else{
                    int targetCol = toupper(castlingMove[0]) - 'A';
                    int targetRow = (castlingMove[1] - '0') -1;
                    GamePiece* rook = GameBoard[targetRow][targetCol];
                    if((rook == 0 || dynamic_cast<RookPiece*>(rook) -> getMoved())){
                        continue;
                    }
                }
                continue;
            }
            while (!IsValidChessCoord(iStartMove)){
                cout << "Invalid input\n>>";
                cin >> iStartMove;
            }
            int iStartCol = toupper(iStartMove[0]) - 'A';
            int iStartRow = (iStartMove[1] - '0') -1;

            cout << "To: ";
            string iEndMove;
            cin >> iEndMove;
            while (!IsValidChessCoord(iEndMove)){
                cout << "Invalid input\n>>";
                cin >> iEndMove;
            }
            int iEndCol = toupper(iEndMove[0]) - 'A';
            int iEndRow = (iEndMove[1] - '0') - 1;

            // Check that the indices are in range
            // and that the source and destination are different
            if ((iStartRow >= 0 && iStartRow <= 7) &&
                (iStartCol >= 0 && iStartCol <= 7) &&
                (iEndRow >= 0 && iEndRow <= 7) &&
                (iEndCol >= 0 && iEndCol <= 7)) {
                // Additional checks in here
                GamePiece* qpCurrPiece = GameBoard[iStartRow][iStartCol];
                // Check that the piece is the correct color
                if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == mcPlayerTurn)) {
                    // Check that the destination is a valid destination
                    if (qpCurrPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, GameBoard)) {
                        // Make the move
                        GamePiece* qpTemp  = GameBoard[iEndRow][iEndCol];
                        GameBoard[iEndRow][iEndCol] = GameBoard[iStartRow][iStartCol];
                        GameBoard[iStartRow][iStartCol] = 0;

                        bool originalMoved = false;
                        if(dynamic_cast<PawnPiece*>(GameBoard[iEndRow][iEndCol])) {
                            originalMoved = (dynamic_cast<PawnPiece*>(GameBoard[iEndRow][iEndCol]))->getMoved(); // Save moved status
                        }
                        if(dynamic_cast<RookPiece*>(GameBoard[iEndRow][iEndCol])) {
                            originalMoved = (dynamic_cast<RookPiece*>(GameBoard[iEndRow][iEndCol]))->getMoved(); // Save moved status
                        }
                        bool bPromoted = false;
                        GamePiece* qpOriginalPawn = nullptr;
                        if (dynamic_cast<PawnPiece*>(GameBoard[iEndRow][iEndCol]) && (iEndRow == 0 || iEndRow == 7)) {
                            cout << "Promote pawn to Queen.\n";
                            qpOriginalPawn = GameBoard[iEndRow][iEndCol];  // Save the original pawn
                            GameBoard[iEndRow][iEndCol] = new QueenPiece(mcPlayerTurn);
                            bPromoted = true;
                        }
                        // Make sure that the current player is not in check
                        if (!mqGameBoard.IsInCheck(mcPlayerTurn)) {
                            delete qpTemp;
                            if (bPromoted) delete qpOriginalPawn; // Delete original pawn
                            bValidMove = true;
                        } else { // Undo the last move
                            if (bPromoted) {
                                delete GameBoard[iEndRow][iEndCol];  // Delete promoted queen
                                GameBoard[iEndRow][iEndCol] = qpOriginalPawn;  // Restore original pawn
                            }
                            GameBoard[iStartRow][iStartCol] = GameBoard[iEndRow][iEndCol];
                            GameBoard[iEndRow][iEndCol]     = qpTemp;
                            if(dynamic_cast<PawnPiece*>(GameBoard[iStartRow][iStartCol])&&!originalMoved) {
                                (dynamic_cast<PawnPiece*>(GameBoard[iStartRow][iStartCol]))->ResetMoved(); // Reset moved status for the pawn
                            }
                            if(dynamic_cast<RookPiece*>(GameBoard[iStartRow][iStartCol])&&!originalMoved) {
                                (dynamic_cast<RookPiece*>(GameBoard[iStartRow][iStartCol]))->ResetMoved(); // Reset moved status for the rook
                            }
                        }
                    }
                }
            }
            if (!bValidMove) {
                cout << "Invalid Move!" << endl;
            }
        } while (!bValidMove);
    }

    void AlternateTurn() {
        mcPlayerTurn = (mcPlayerTurn == 'W') ? 'B' : 'W';
    }

    bool IsGameOver() {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        bool bCanMove(false);
        bCanMove = mqGameBoard.CanMove(mcPlayerTurn);
        if (!bCanMove) {
            if (mqGameBoard.IsInCheck(mcPlayerTurn)) {
                AlternateTurn();
                std::cout << "Checkmate, " << mcPlayerTurn << " Wins!" << std::endl;
            } else {
                std::cout << "Stalemate!" << std::endl;
            }
        }
        return !bCanMove;
    }
private:
    CBoard mqGameBoard;
    char mcPlayerTurn;
};