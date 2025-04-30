#include "piece.h"
#include <vector>
class PawnPiece : public GamePiece
{
    public:
        PawnPiece(char PieceColor) : GamePiece(PieceColor), moved(false) {}
        ~PawnPiece() {}
        void ResetMoved() {
            moved = false;
        }
        bool getMoved() {
            return moved;
        }
    private:
        bool moved = false;
        virtual char GetPiece() {
            return 'P';
        }
        bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
            GamePiece* qpDest = GameBoard[iDestRow][iDestCol];
            if (qpDest == 0) {
                // Destination square is unoccupied
                if (iSrcCol == iDestCol) {
                    if (GetColor() == 'W') {
                        if (iDestRow == iSrcRow + 1 || (iDestRow == iSrcRow + 2 && !moved)) {
                            moved = false; // Reset moved status after a valid move
                            return true;
                        }
                    } else {
                        if (iDestRow == iSrcRow - 1 || (iDestRow == iSrcRow - 2 && !moved)) {
                            moved = false; // Reset moved status after a valid move
                            return true;
                        }
                    }
                }
            } else {
                // Dest holds piece of opposite color
                if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
                    if (GetColor() == 'W') {
                        if (iDestRow == iSrcRow + 1) {
                            moved = false; // Reset moved status after a valid move
                            return true;
                        }
                    } else {
                        if (iDestRow == iSrcRow - 1) {
                            moved = false; // Reset moved status after a valid move
                            return true;
                        }
                    }
                }
            }
            return false;
        }
};