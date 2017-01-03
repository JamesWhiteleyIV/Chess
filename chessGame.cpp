//
//  chessGame.cpp
//  chess
//
//  Created by James Whiteley IV on 12/31/16.
//  Copyright © 2016 James Whiteley IV. All rights reserved.
//

#include "chessGame.hpp"
#include <string>
#include <iostream>

void chessGame::playGame() {
    
    
    // cout << "playGame() called, current player: " << getPlayerTurn() << endl << endl;
    
    std::string move = " ";
    int rowFrom = -1000;
    int columnFrom = -1000;
    int rowToo = -1000;
    int columnToo = -1000;
    std::string player;
    
    
    if(getTurn() == 1)
        player = "White";
    else
        player = "Black";
    
    std::cout << player << " team please enter a move (ex: A1 to B2)" << std::endl;
    std::cin.clear();
    fflush(stdin);
    getline(std::cin, move);
    
    
    // validate length of move in order to validate move from and move too
    while(move.length() != 8)
    {
        // reset cin
        std::cin.clear();
        fflush(stdin);
        rowFrom = -1000;
        columnFrom = -1000;
        rowToo = -1000;
        columnToo = -1000;
        
        std::cout << "Please enter a valid move." << std::endl;
        std::cout << player << " team please enter a move (ex: A1 to B2)" << std::endl << std::endl;
        getline(std::cin, move);
    }
    
    
    // once a move of length 8 is entered...
    //convert string entered into valid array move
    columnFrom = tolower(move.at(0)) - '0' - 49;
    rowFrom = move.at(1) - '0' - 1;
    columnToo = tolower(move.at(6)) - '0' - 49;
    rowToo = move.at(7) - '0' - 1;
    
    /* testing purposes
     cout << "columnFrom: " << columnFrom << endl;
     cout << "rowFrom: " << rowFrom << endl;
     cout << "columnToo: " << columnToo << endl;
     cout << "rowToo: " << rowToo << endl;
     */
    
    
    // validate move from and too (while any contradict what we want)
    while(columnFrom < 0 || columnFrom > 7 || rowFrom < 0 || rowFrom > 7 || columnToo > 7 || columnToo < 0 || rowToo > 7 || rowToo < 0 || ((columnFrom == columnToo) && (rowFrom == rowToo)))
    {
        
        // reset cin
        std::cin.clear();
        fflush(stdin);
        rowFrom = -1000;
        columnFrom = -1000;
        rowToo = -1000;
        columnToo = -1000;
        
        std::cout << "Please enter a valid move." << std::endl;
        std::cout << player << " team please enter a move (ex: A1 to B2)" << std::endl << std::endl;
        getline(std::cin, move);
        
        
        // once a move of length 8 is entered...
        //convert string entered into valid array move
        if(move.length() == 8)
        {
            columnFrom = tolower(move.at(0)) - '0' - 49;
            rowFrom = move.at(1) - '0' - 1;
            columnToo = tolower(move.at(6)) - '0' - 49;
            rowToo = move.at(7) - '0' - 1;
        }
    }
    
    // AT THIS POINT WE SHOULD ONLY HAVE MOVES FROM INSIDE THE BOARD THAT ARE NOT TO THEMSELVES
    
    
    // validate correct player for move and ensure player isn't selecting empty space
    // check if -piece and black team is true  // else check if +piece and white team is true //else ask for input again
    if( (this->board.getBackEndBoard(rowFrom, columnFrom) < 0) && (this->board.getBackEndBoard(rowToo, columnToo) >= 0) && (getTurn() == 2))
    {
        bool validity = this->board.validMoveForPiece( this->board.getBackEndBoard(rowFrom, columnFrom), rowFrom, columnFrom, rowToo, columnToo);
        
        if(validity)
        {
            makeMove(rowFrom, columnFrom, rowToo, columnToo);
            
            if(this->board.checkPromotion(2))
                this->board.pawnPromotion(2);
            
            setTurn(1);
            printPlayerCaptures(1);
            printPlayerCaptures(2);
            getBoard().printFrontEndBoard();
            checkGameState(1);
            checkGameState(2);
        
        }
        else
        {
            std::cout << "Please enter a valid move." << std::endl << std::endl;
            playGame();
        }
    }
    else if ( (this->board.getBackEndBoard(rowFrom, columnFrom) > 0) && (this->board.getBackEndBoard(rowToo, columnToo) <= 0) && (getTurn() == 1))
    {
        bool validity = this->board.validMoveForPiece(this->board.getBackEndBoard(rowFrom, columnFrom), rowFrom, columnFrom, rowToo, columnToo);
        
        
        if(validity)
        {
            makeMove(rowFrom, columnFrom, rowToo, columnToo);
            
            if(this->board.checkPromotion(2))
                this->board.pawnPromotion(2);
            
            setTurn(2);
            printPlayerCaptures(1);
            printPlayerCaptures(2);
            getBoard().printFrontEndBoard();
            checkGameState(1);
            checkGameState(2);
            
        }
        else
        {
            std::cout << "Please enter a valid move." << std::endl << std::endl;
            playGame();
        }
        
    }
    else
    {
        std::cout << "Please enter a valid move." << std::endl << std::endl;
        playGame();
    }
    
    


}

void chessGame::initPlayers() {
    white = 1;
    black = 2;
}


int chessGame::getTurn() {
    return playerTurn;
}

void chessGame::setTurn(int turn) {
    this->playerTurn = turn;
}

void chessGame::setGameState(State current) {
    this->gameState = current;
}


State chessGame::getGameState() {
    return gameState;
}


void chessGame::checkGameState(int playerCheck) {
    //passing current players turn into check game state
    
    
    // checkmate -> if player does not move king this turn, other player can kill king on his next turn && anywhere king moves player can kill king on next turn CHECKMATE
    // check -> else if player does not move king this turn, other player can kill king on his next turn  CHECK
    // unfinished ->  else UNFINISHED
    //valid move parameters:  int piece, int rowFrom, int columnFrom, int rowToo, int columnToo

    int kingPlayer;
    if (playerCheck == 1)
        kingPlayer = 9;
    else
        kingPlayer = -9;
    
    int kingRow = -1;
    int kingCol = -1;
    //find king position for player
    for (int i = 0; i < 8; i++) {
        for(int j=0; j<8; j++) {
            if(this->board.getBackEndBoard(i,j) == kingPlayer) {
                kingCol = j;
                kingRow = i;
            }
        }
    }
    
    //iterate through all valid moves for black player to see if any pieces could get king on next move
    bool checkPossible = false;
    for (int i = 0; i < 8; i++) {
        for(int j=0; j<8; j++) {
            if(playerCheck == 1) {
            if(this->board.getBackEndBoard(i, j) < 0) { //only check moves of black pieces
                if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow, kingCol)) {
                    checkPossible = true;
                }
            }
            }
            else if(playerCheck == 2) {
                if(this->board.getBackEndBoard(i, j) > 0) { //only check moves of white pieces
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow, kingCol)) {
                        checkPossible = true;
                    }
                }
            }
            
        }
    }
    
    if(!checkPossible)
        return;
    
    //at this point check is possible, now we will check for check mate.
    
    //check if all positions around king are available or could also kill king if moved to
    bool spot1 = false; //see if statements below for corresponding spots
    bool spot2 = false;
    bool spot3 = false;
    bool spot4 = false;
    bool spot5 = false;
    bool spot6 = false;
    bool spot7 = false;
    bool spot8 = false;
    
    
    
    //check for possible moves, set corresponding spot to true if that's not a position the king could move to (off board)
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow-1, kingCol-1))) {
        spot1 = true;
    }
    else if(kingRow-1 < 0 || kingCol-1 < 0)
        spot1 = true;
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow-1, kingCol))) {
        spot2 = true;
    }
    else if(kingRow-1 < 0)
        spot2 = true;
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow-1, kingCol+1))) {
        spot3 = true;
    }
    else if(kingRow-1 < 0 || kingCol + 1 > 7 )
        spot3 = true;
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow, kingCol-1))) {
        spot4 = true;
    }
    else if(kingCol - 1 < 0)
        spot4 = true;
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow, kingCol+1))) {
        spot5 = true;
    }
    else if(kingCol +1 > 7)
        spot5 = true;
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow+1, kingCol-1))) {
        spot6 = true;
    }
    else if(kingRow+1 > 7 || kingCol-1 < 0)
        spot6 = true;
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow+1, kingCol))) {
        spot7 = true;
    }
    else if(kingRow+1 > 7)
        spot7 = true;
    if(!(this->board.validMoveForPiece(this->board.getBackEndBoard(kingRow, kingCol), kingRow, kingCol, kingRow+1, kingCol+1))) {
        spot8 = true;
    }
    else if(kingRow+1 > 7 || kingCol +1 > 7)
        spot8 = true;
     
    
    
    // iterate through each piece and see if each spot is possible for each piece
    // if spot is still false, check each game piece to see if they could move to that spot
    if(playerCheck == 1) {
            //function to check each negative piece
            for (int i = 0; i < 8; i++) {
                for(int j=0; j<8; j++) {
                    if(this->board.getBackEndBoard(i, j) < 0) {
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow-1, kingCol-1)) {
                            spot1 = true;
                      
                        }
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow-1, kingCol)) {
                            spot2 = true;
                         
                        }
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow-1, kingCol+1)) {
                            spot3 = true;
                        
                        }
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow, kingCol-1)) {
                            spot4 = true;
                     
                        }
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow, kingCol+1)) {
                            spot5 = true;
                
                        }
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow+1, kingCol-1)) {
                            spot6 = true;
                        
                        }
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow+1, kingCol)) {
                            spot7 = true;
                       
                        }
                        if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow+1, kingCol+1)) {
                            spot8 = true;
                   
                        }
                        
                    }
                }
            }
        
        if(spot1 == true && spot2 == true && spot3 == true && spot4 == true && spot5 == true && spot6 == true && spot7 == true && spot8 == true) {
                gameState = CHECK_MATE_BLACK;
                return;
        }
    }
    
    
    if(playerCheck == 2) {
        //function to check each negative piece
        for (int i = 0; i < 8; i++) {
            for(int j=0; j<8; j++) {
                if(this->board.getBackEndBoard(i, j) > 0) {
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow-1, kingCol-1)) {
                        spot1 = true;
                
                    }
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow-1, kingCol)) {
                        spot2 = true;
                     
                    }
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow-1, kingCol+1)) {
                        spot3 = true;
                     
                    }
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow, kingCol-1)) {
                        spot4 = true;
                  
                    }
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow, kingCol+1)) {
                        spot5 = true;
                   
                    }
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow+1, kingCol-1)) {
                        spot6 = true;
               
                    }
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow+1, kingCol)) {
                        spot7 = true;
                    
                    }
                    if(this->board.validMoveForPiece(this->board.getBackEndBoard(i, j), i, j, kingRow+1, kingCol+1)) {
                        spot8 = true;
                
                    }
                    
                }
            }
        }
        
        if(spot1 == true && spot2 == true && spot3 == true && spot4 == true && spot5 == true && spot6 == true && spot7 == true && spot8 == true) {
            gameState = CHECK_MATE_WHITE;
            return;
        }
        
    }
    
    
    if(playerCheck == 1) {
        std::cout << "White team, you are in check!" << std::endl;
    }
    else
        std::cout << "Black team, you are in check!" << std::endl;
    
    

    
}






void chessGame::makeMove(int rowFrom, int columnFrom, int rowToo, int columnToo)
{
    // if space moving to == 0, switch array numbers
    // else remove space moving to from board, then switch array numbers
    // check if opposite team king is in check, if in check, see if check mate
    // else cout check statement
    
    if(this->board.getBackEndBoard(rowToo, columnToo) == 0)
    {
        this->board.setBackEndBoard(rowToo, columnToo, this->board.getBackEndBoard(rowFrom, columnFrom));
        this->board.setBackEndBoard(rowFrom, columnFrom, 0);
        
    }
    else  // else it is either - or + piece
    {
        capture(this->board.getBackEndBoard(rowToo, columnToo), getTurn());
        this->board.setBackEndBoard(rowToo, columnToo, this->board.getBackEndBoard(rowFrom, columnFrom));
        this->board.setBackEndBoard(rowFrom, columnFrom, 0);
    }
    
}





void chessGame::capture(int piece, int player)
{
    char translate;
    
    switch(piece)
    {
        case 1:
            translate = 'p';
            break;
        case 2:
            translate = 'r';
            break;
        case 3:
            translate = 'n';
            break;
        case 4:
            translate = 'b';
            break;
        case 9:
            translate = 'k';
            break;
        case 8:
            translate = 'q';
            break;
            
        case -1:
            translate = 'P';
            break;
        case -2:
            translate = 'R';
            break;
        case -3:
            translate = 'N';
            break;
        case -4:
            translate = 'B';
            break;
        case -9:
            translate = 'K';
            break;
        case -8:
            translate = 'Q';
            break;
    }
    
    if(player == 1)
    {
        whiteCaptures.push_back(translate);
    }
    else
    {
        blackCaptures.push_back(translate);
    }
}


void chessGame::printPlayerCaptures(int player)
{
    
    if(player == 1)
    {
        std::cout << "White team captives: ";
        for(int i = 0; i < whiteCaptures.size(); i++)
            std::cout << whiteCaptures[i] << ", ";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Black team captives: ";
        for(int i = 0; i < blackCaptures.size(); i++)
            std::cout << blackCaptures[i] << ", ";
        std::cout << std::endl;
    }
}

board chessGame::getBoard() {
    return this->board;
}

bool chessGame::kingAlive(int player) {
    bool checkKingState = false;
    int king;
    if(player == 1) {
        king = 9;
    }
    else
        king = -9;
    
    for (int i = 0; i < 8; i++) {
        for(int j=0; j<8; j++) {
            if(this->board.getBackEndBoard(i, j) == king) {
                checkKingState = true;
            }
                
        }
    }
    
    return checkKingState;
    
}
