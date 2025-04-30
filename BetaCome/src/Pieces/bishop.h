#include "piece.h"
class BishopPiece : public GamePiece
{
public:
    BishopPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~BishopPiece() {}
private:
    virtual char GetPiece() {
        return 'B';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
            // Make sure that all invervening squares are empty
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
                iCheckRow !=  iDestRow;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (GameBoard[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};