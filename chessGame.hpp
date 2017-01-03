//
//  chessGame.hpp
//  chess
//
//  Created by James Whiteley IV on 12/31/16.
//  Copyright © 2016 James Whiteley IV. All rights reserved.
//

#ifndef chessGame_hpp
#define chessGame_hpp

#include <stdio.h>
#include "board.hpp"

enum State{CHECK_MATE_WHITE, CHECK_MATE_BLACK, UNFINISHED};

class chessGame {
private:
    board board;
    State gameState;
    int playerTurn;
    int white;
    int black;
public:
    class board getBoard();
    void initPlayers();
    void playGame();
    int getTurn();
    void setTurn(int);
    void setGameState(State);
    State getGameState();
    void checkGameState(int);
    void makeMove(int, int, int, int);
    void capture(int, int);
    void printPlayerCaptures(int);
    std::vector<char> whiteCaptures;
    std::vector<char> blackCaptures;
    bool kingAlive(int);
};







#endif /* chessGame_hpp */
