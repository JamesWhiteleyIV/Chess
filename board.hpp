//
//  board.hpp
//  chess
//
//  Created by James Whiteley IV on 12/2/16.
//  Copyright © 2016 James Whiteley IV. All rights reserved.
//

#ifndef board_hpp
#define board_hpp
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <string>




class board
{
private:
    int backEndBoard[8][8];
    char frontEndBoard[8][8];
public:
    board();
    void printBackEndBoard();
    int getBackEndBoard(int, int);
    void setBackEndBoard(int, int, int);
    bool checkPromotion(int);
    void pawnPromotion(int);
    void setFrontEndBoard(int, int, char);
    void printFrontEndBoard();
    bool validMoveForPiece(int, int, int, int , int); // also checks for obstruction
    
};




#endif /* board_hpp */



