#include <unordered_map>
class AI{
    protected:
        int board[8][8] = {
            { 2, 3, 4, 5, 6, 4, 3, 2 },   // Black major pieces
            { 1, 1, 1, 1, 1, 1, 1, 1 },   // Black pawns
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            {-1,-1,-1,-1,-1,-1,-1,-1 },   // White pawns
            {-2,-3,-4,-5,-6,-4,-3,-2 }    // White major pieces
        };
    public:
        
};