//
//  main.cpp
//  chess
//
//  Created by James Whiteley IV on 12/2/16.
//  Copyright © 2016 James Whiteley IV. All rights reserved.
//

#include <iostream>
#include "board.hpp"
#include <iomanip>
#include "chessGame.hpp"

int main() {
   
    chessGame game;
    game.initPlayers(); // set white = 1, black = 2
    game.setTurn(1);  // white will go first
    game.setGameState(UNFINISHED);
    game.getBoard().printFrontEndBoard();
    
    while(game.getGameState() != CHECK_MATE_BLACK && game.getGameState() != CHECK_MATE_WHITE && game.kingAlive(1) && game.kingAlive(2) )
        game.playGame();
    
    switch (game.getGameState()) {
        case CHECK_MATE_WHITE:
            std::cout << std::endl << "White team wins!! CHECKMATE!" << std::endl;
            break;
        case CHECK_MATE_BLACK:
            std::cout << std::endl << "Black team wins!! CHECKMATE!" << std::endl;
            break;
        case UNFINISHED:  //if it somehow gets here, but it won't :)
            if(game.kingAlive(1)) {
                std::cout << std::endl << "White team wins!!" << std::endl;
            }
            else
                std::cout << std::endl << "Black team wins!!" << std::endl;
            break;
    }
    

    return 0;
}
