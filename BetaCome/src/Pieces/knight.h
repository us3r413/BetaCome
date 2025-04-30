#include "piece.h"
class KnightPiece : public GamePiece
{
public:
    KnightPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~KnightPiece() {}
private:
    virtual char GetPiece() {
        return 'N';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        // Destination square is unoccupied or occupied by opposite color
        if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
            if ((iSrcRow == iDestRow + 2) || (iSrcRow == iDestRow - 2)) {
                return true;
            }
        }
        if ((iSrcCol == iDestCol + 2) || (iSrcCol == iDestCol - 2)) {
            if ((iSrcRow == iDestRow + 1) || (iSrcRow == iDestRow - 1)) {
                return true;
            }
        }
        return false;
    }
};