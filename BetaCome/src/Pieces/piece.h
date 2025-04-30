#pragma once
class GamePiece
{
    public:
        GamePiece(char PieceColor) : mPieceColor(PieceColor) {}
        ~GamePiece() {}
        virtual char GetPiece() = 0;
        char GetColor() {
            return mPieceColor;
        }
        bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
            GamePiece* qpDest = GameBoard[iDestRow][iDestCol];
            if ((qpDest == 0) || (mPieceColor != qpDest->GetColor())) {
                return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, GameBoard);
            }
            return false;
        }
    private:
        virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) = 0;
        char mPieceColor;
};