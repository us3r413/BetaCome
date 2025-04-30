#include "piece.h"
class KingPiece : public GamePiece
{
public:
    KingPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~KingPiece() {}
    bool getMoved() {
        return moved;
    }
    void ResetMoved() {
        moved = false;
    }
private:
    bool moved = false;
    virtual char GetPiece() {
        return 'K';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        int iRowDelta = iDestRow - iSrcRow;
        int iColDelta = iDestCol - iSrcCol;
        if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
            ((iColDelta >= -1) && (iColDelta <= 1)))
        {
            moved = true; // King has moved
            return true;
        }
        return false;
    }
};