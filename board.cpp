//
//  board.cpp
//  chess
//
//  Created by James Whiteley IV on 12/2/16.
//  Copyright © 2016 James Whiteley IV. All rights reserved.
//

#include "board.hpp"
#include <iostream>
#include <iomanip>


board::board()
{
    /*
     
     2 = white rooks
     3 = white nights
     4 = white bishop
     9 = white king
     8 = white queen
     1 = white pawns
     
     Black pieces use negative values
     
     Blank spaces is 0
     */
    

    backEndBoard[0][0] = 2;
    backEndBoard[0][1] = 3;
    backEndBoard[0][2] = 4;
    backEndBoard[0][3] = 9;
    backEndBoard[0][4] = 8;
    backEndBoard[0][5] = 4;
    backEndBoard[0][6] = 3;
    backEndBoard[0][7] = 2;
    
    for(int i=0; i<8; i++)
    {
        backEndBoard[1][i] = 1;
        backEndBoard[2][i] = 0;
        backEndBoard[3][i] = 0;
        backEndBoard[4][i] = 0;
        backEndBoard[5][i] = 0;
        backEndBoard[6][i] = -1;
    }
    
    backEndBoard[7][0] = -2;
    backEndBoard[7][1] = -3;
    backEndBoard[7][2] = -4;
    backEndBoard[7][3] = -9;
    backEndBoard[7][4] = -8;
    backEndBoard[7][5] = -4;
    backEndBoard[7][6] = -3;
    backEndBoard[7][7] = -2;
    
    
    
}




void board::printBackEndBoard()
{
    
    std::cout << std::endl << std::endl;
    std::cout << "    ";
    char topLetter = 'A';
    for(int i=0; i<8; i++)
    {
        std::cout << std::setw(3) << std::right << topLetter;
        topLetter++;
    }
    std::cout << std::endl << "    --------------------------" << std::endl;
    for (int i =0; i<8; i++)
    {
        std::cout << std::setw(3) << std::left << i+1 << "|";
        for(int j=0; j<8; j++)
        {
            std::cout << std::setw(3) << std::right << getBackEndBoard(i,j);
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl << std::endl;
    
}


int board::getBackEndBoard(int i, int j)
{
    return backEndBoard[i][j];
}

void board::setBackEndBoard(int i, int j, int piece)
{
    backEndBoard[i][j] = piece;
}



bool board::validMoveForPiece(int piece, int rowFrom, int columnFrom, int rowToo, int columnToo)
{
    
    int currentRow = rowFrom;
    int currentColumn = columnFrom;
    int toRow = rowToo;
    int toColumn = columnToo;
    
    
    if(piece == 1) // white pawn
    {
        if(rowFrom == 1)  // check if still in starting position
        {
            if( (currentRow + 1 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) == 0) )
                return true;
            else if( (currentRow + 2 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) == 0) && (getBackEndBoard(toRow-1, toColumn) == 0)  )
                return true;
            else if( (currentRow + 1 == toRow) && (currentColumn + 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) < 0)  )
                return true;
            else if( (currentRow + 1 == toRow) && (currentColumn - 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) < 0)  )
                return true;
            else
                return false;
        }
        else
        {
            if( (currentRow + 1 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) == 0) )
                return true;
            else if( (currentRow + 1 == toRow) && (currentColumn + 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) < 0)  )
                return true;
            else if( (currentRow + 1 == toRow) && (currentColumn - 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) < 0)  )
                return true;
            else
                return false;
        }
        
    }
    else if(piece == 2) // white rook
    {
        if((currentRow == toRow) && (toColumn != currentColumn) )  // check horizontal move
        {
            if(toColumn < currentColumn)  // if move is to the left
            {
                int testObstructions = currentColumn - 1;  // set to 1 column left of current
                while(testObstructions > toColumn)  // while column to left of current > column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to left have a piece in them return false
                    testObstructions--;
                }
            
                return true;  // if no obstructions, return true
            }
            
            else if(currentColumn < toColumn)  // if move is to the right
            {
            
                int testObstructions = currentColumn + 1;  // set to 1 column right of current
                while(testObstructions < toColumn)  // while column to right of current < column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to right have a piece in them return false
                    testObstructions++;
                }
             
                
                return true;  // if no obstructions, return true
            }
            
            
            
        }
        else if( (currentRow != toRow) && (toColumn == currentColumn))  // check vertical move
        {
            
            
            
            if(toRow < currentRow)  // if move is up
            {
                int testObstructions = currentRow - 1;  // set to 1 row up of current
                while(testObstructions > toRow)  // while row up from current > row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions up from current have a piece in them return false
                    testObstructions--;
                }
                
                return true;  // if no obstructions, return true
            }
            
            else if(currentRow < toRow)  // if move is down
            {
                
                int testObstructions = currentRow + 1;  // set to 1 row down of current
                while(testObstructions < toRow)  // while row down from current < row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions down have a piece in them return false
                    testObstructions++;
                }
                
                
                return true;  // if no obstructions, return true
            }
            
        }
        
        
        else
            return false;
    
    
    }
    
    
    else if(piece == 3) // white knight
    {
        if( (currentRow - 1 == toRow) && (currentColumn + 2  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0) )
            return true;
        else if( (currentRow - 2 == toRow) && (currentColumn + 1  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else if( (currentRow - 2 == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn - 2  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn + 2  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else if( (currentRow + 2 == toRow) && (currentColumn + 1  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else if( (currentRow + 2 == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn - 2  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else
            return false;
    }
    
    else if(piece == 4) // white bishop
    {
        
        
        if(currentRow - toRow == currentColumn - toColumn)  // SE or NW
        {

            if(currentRow - toRow > 0)  // check NW obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol--;
                }
                
                return true;
        
            }
            else if(currentRow - toRow < 0) // check SE obstructions
            {

                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
        }
        
        else if(currentColumn + currentRow == toRow + toColumn) //SW or NE
        {
            
            if(currentRow - toRow > 0)  // check NE obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
            else if(currentRow - toRow < 0) // check SW obstructions
            {
                
                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol--;
                }
                
                return true;
                
            }
            
            
            
        }
        
        
        else
            return false;
    }
    
    else if(piece == 8) // white queen
    {

        if((currentRow == toRow) && (toColumn != currentColumn) )  // check horizontal move
        {
            if(toColumn < currentColumn)  // if move is to the left
            {
                int testObstructions = currentColumn - 1;  // set to 1 column left of current
                while(testObstructions > toColumn)  // while column to left of current > column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to left have a piece in them return false
                    testObstructions--;
                }
                
                return true;  // if no obstructions, return true
            }
            
            else if(currentColumn < toColumn)  // if move is to the right
            {
                
                int testObstructions = currentColumn + 1;  // set to 1 column right of current
                while(testObstructions < toColumn)  // while column to right of current < column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to right have a piece in them return false
                    testObstructions++;
                }
                
                
                return true;  // if no obstructions, return true
            }
            
            
            
        }
        else if( (currentRow != toRow) && (toColumn == currentColumn))  // check vertical move
        {
            
            
            
            if(toRow < currentRow)  // if move is up
            {
                int testObstructions = currentRow - 1;  // set to 1 row up of current
                while(testObstructions > toRow)  // while row up from current > row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions up from current have a piece in them return false
                    testObstructions--;
                }
                
                return true;  // if no obstructions, return true
            }
            
            else if(currentRow < toRow)  // if move is down
            {
                
                int testObstructions = currentRow + 1;  // set to 1 row down of current
                while(testObstructions < toRow)  // while row down from current < row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions down have a piece in them return false
                    testObstructions++;
                }
                
                
                return true;  // if no obstructions, return true
            }
            
        }
        
        else if(currentRow - toRow == currentColumn - toColumn)  // SE or NW
        {
            
            if(currentRow - toRow > 0)  // check NW obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol--;
                }
                
                return true;
                
            }
            else if(currentRow - toRow < 0) // check SE obstructions
            {
                
                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
        }
        
        else if(currentColumn + currentRow == toRow + toColumn) //SW or NE
        {
            
            if(currentRow - toRow > 0)  // check NE obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
            else if(currentRow - toRow < 0) // check SW obstructions
            {
                
                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol--;
                }
                
                return true;
                
            }
            
            
            
        }
        
        
        else
            return false;

        
        
        
        
        
    }
    
    else if(piece == 9) // white king
    {
        if( (currentRow + 1 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0)  )
            return true;
        else if( (currentRow == toRow) && (currentColumn + 1  == toColumn)&& (getBackEndBoard(toRow, toColumn) <= 0) )
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn  == toColumn)&& (getBackEndBoard(toRow, toColumn) <= 0) )
            return true;
        else if( (currentRow == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0) )
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn + 1  == toColumn)&& (getBackEndBoard(toRow, toColumn) <= 0) )
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn + 1  == toColumn)&& (getBackEndBoard(toRow, toColumn) <= 0) )
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn - 1  == toColumn)&& (getBackEndBoard(toRow, toColumn) <= 0) )
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) <= 0))
            return true;
        else
            return false;
    }
    
    
    else if(piece == -1)  // black pawn
    {
        if(rowFrom == 6)  // check if still in starting position
        {
            if( (currentRow - 1 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) == 0)  )
                return true;
            else if( (currentRow - 2 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) == 0) && (getBackEndBoard(toRow+1, toColumn) == 0))
                return true;
            else if( (currentRow - 1 == toRow) && (currentColumn - 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) > 0)  )
                return true;
            else if( (currentRow - 1 == toRow) && (currentColumn + 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) > 0)  )
                return true;
            else
                return false;
        }
        else
        {
            if( (currentRow - 1 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) == 0) )
                return true;
            else if( (currentRow - 1 == toRow) && (currentColumn - 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) > 0)  )
                return true;
            else if( (currentRow - 1 == toRow) && (currentColumn + 1 == toColumn) && ( getBackEndBoard(toRow, toColumn) > 0)  )
                return true;
            else
                return false;
        }
    }
    
    
    else if(piece == -2) // black rook
    {
        if((currentRow == toRow) && (toColumn != currentColumn) )  // check horizontal move
        {
            if(toColumn < currentColumn)  // if move is to the left
            {
                int testObstructions = currentColumn - 1;  // set to 1 column left of current
                while(testObstructions > toColumn)  // while column to left of current > column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to left have a piece in them return false
                    testObstructions--;
                }
                
                return true;  // if no obstructions, return true
            }
            
            else if(currentColumn < toColumn)  // if move is to the right
            {
                
                int testObstructions = currentColumn + 1;  // set to 1 column right of current
                while(testObstructions < toColumn)  // while column to right of current < column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to right have a piece in them return false
                    testObstructions++;
                }
                
                
                return true;  // if no obstructions, return true
            }
            
            
            
        }
        else if( (currentRow != toRow) && (toColumn == currentColumn))  // check vertical move
        {
            
            
            
            if(toRow < currentRow)  // if move is up
            {
                int testObstructions = currentRow - 1;  // set to 1 row up of current
                while(testObstructions > toRow)  // while row up from current > row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions up from current have a piece in them return false
                    testObstructions--;
                }
                
                return true;  // if no obstructions, return true
            }
            
            else if(currentRow < toRow)  // if move is down
            {
                
                int testObstructions = currentRow + 1;  // set to 1 row down of current
                while(testObstructions < toRow)  // while row down from current < row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions down have a piece in them return false
                    testObstructions++;
                }
                
                
                return true;  // if no obstructions, return true
            }
            
        }
        
        
        else
            return false;
        
        
        
    }
    else if(piece == -3) // black knight
    {
        if( (currentRow - 1 == toRow) && (currentColumn + 2  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow - 2 == toRow) && (currentColumn + 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0))
            return true;
        else if( (currentRow - 2 == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0))
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn - 2  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0))
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn + 2  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0))
            return true;
        else if( (currentRow + 2 == toRow) && (currentColumn + 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0))
            return true;
        else if( (currentRow + 2 == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0))
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn - 2  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0))
            return true;
        else
            return false;
        
    }
    else if(piece == -4)  // black bishop
    {
        if(currentRow - toRow == currentColumn - toColumn)  // SE or NW
        {
            
            if(currentRow - toRow > 0)  // check NW obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol--;
                }
                
                return true;
                
            }
            else if(currentRow - toRow < 0) // check SE obstructions
            {
                
                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
        }
        
        else if(currentColumn + currentRow == toRow + toColumn) //SW or NE
        {
            
            if(currentRow - toRow > 0)  // check NE obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
            else if(currentRow - toRow < 0) // check SW obstructions
            {
                
                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol--;
                }
                
                return true;
                
            }
            
            
            
        }
        
        
        else
            return false;
    }
    else if(piece == -8) // black queen
    {
        if((currentRow == toRow) && (toColumn != currentColumn) )  // check horizontal move
        {
            if(toColumn < currentColumn)  // if move is to the left
            {
                int testObstructions = currentColumn - 1;  // set to 1 column left of current
                while(testObstructions > toColumn)  // while column to left of current > column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to left have a piece in them return false
                    testObstructions--;
                }
                
                return true;  // if no obstructions, return true
            }
            
            else if(currentColumn < toColumn)  // if move is to the right
            {
                
                int testObstructions = currentColumn + 1;  // set to 1 column right of current
                while(testObstructions < toColumn)  // while column to right of current < column going to
                {
                    if(getBackEndBoard(currentRow, testObstructions) != 0)
                        return false;   // if positions to right have a piece in them return false
                    testObstructions++;
                }
                
                
                return true;  // if no obstructions, return true
            }
            
            
            
        }
        else if( (currentRow != toRow) && (toColumn == currentColumn))  // check vertical move
        {
            
            
            
            if(toRow < currentRow)  // if move is up
            {
                int testObstructions = currentRow - 1;  // set to 1 row up of current
                while(testObstructions > toRow)  // while row up from current > row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions up from current have a piece in them return false
                    testObstructions--;
                }
                
                return true;  // if no obstructions, return true
            }
            
            else if(currentRow < toRow)  // if move is down
            {
                
                int testObstructions = currentRow + 1;  // set to 1 row down of current
                while(testObstructions < toRow)  // while row down from current < row going to
                {
                    if(getBackEndBoard(testObstructions, currentColumn) != 0)
                        return false;   // if positions down have a piece in them return false
                    testObstructions++;
                }
                
                
                return true;  // if no obstructions, return true
            }
            
        }
        
        else if(currentRow - toRow == currentColumn - toColumn)  // SE or NW
        {
            
            if(currentRow - toRow > 0)  // check NW obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol--;
                }
                
                return true;
                
            }
            else if(currentRow - toRow < 0) // check SE obstructions
            {
                
                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
        }
        
        else if(currentColumn + currentRow == toRow + toColumn) //SW or NE
        {
            
            if(currentRow - toRow > 0)  // check NE obstructions
            {
                int testObstructionRow = currentRow - 1;
                int testObstructionCol = currentColumn + 1;
                
                while (testObstructionRow > toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow--;
                    testObstructionCol++;
                }
                
                return true;
                
            }
            
            else if(currentRow - toRow < 0) // check SW obstructions
            {
                
                int testObstructionRow = currentRow + 1;
                int testObstructionCol = currentColumn - 1;
                
                while (testObstructionRow < toRow )
                {
                    if(getBackEndBoard(testObstructionRow, testObstructionCol) != 0)
                        return false;
                    testObstructionRow++;
                    testObstructionCol--;
                }
                
                return true;
                
            }
            
            
            
        }
        
        
        else
            return false;
        
        
        
        

    }
    else if(piece == -9) // black king
    {
        if( (currentRow + 1 == toRow) && (currentColumn == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow == toRow) && (currentColumn + 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn  == toColumn)&&  (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn + 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn + 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow + 1 == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else if( (currentRow - 1 == toRow) && (currentColumn - 1  == toColumn) && (getBackEndBoard(toRow, toColumn) >= 0) )
            return true;
        else
            return false;
    }
    
    
    // if somehow it gets here which it shouldn't :)
    return false;
    

}



bool board::checkPromotion(int player) {
    
    if(player == 1) {
        for(int i=0; i<8; i++) {
            if(getBackEndBoard(7, i) == 1)
                return true;
        }
    }
    
    if(player == 2) {
        for(int i=0; i<8; i++) {
            if(getBackEndBoard(0, i) == -1)
                return true;
        }
    }
    
    return false;
    
    
}


 
void board::pawnPromotion(int player)
{
    
    char choice = NULL;
    std::cout << "Would you like to promote your pawn to rook, knight, bishop, or queen?" << std::endl;
    std::cout << " 'R' for rook" << std::endl;
    std::cout << " 'K' for knight" << std::endl;
    std::cout << " 'B' for bishop" << std::endl;
    std::cout << " 'Q' for queen" << std::endl;
    std::cin >> choice;
    
    while (choice != 'r' && choice != 'R' && choice != 'k' && choice != 'K' && choice != 'b' && choice != 'B' && choice != 'q' && choice != 'Q') {
        char choice = NULL;
        std::cout << "Enter a valid piece" << std::endl;
        std::cout << "Would you like to promote your pawn to rook, knight, bishop, or queen?" << std::endl;
        std::cout << " 'R' for rook" << std::endl;
        std::cout << " 'K' for knight" << std::endl;
        std::cout << " 'B' for bishop" << std::endl;
        std::cout << " 'Q' for queen" << std::endl;
        std::cin >> choice;
        
    }
    
    int numChoice = 0;
    
    switch(choice) {
        case 'r':
        case 'R': numChoice = 2;
            break;
        case 'k':
        case 'K': numChoice = 3;
            break;
        case 'b':
        case 'B': numChoice = 4;
            break;
        case 'q':
        case 'Q': numChoice = 8;
            break;
    
    
    }
    
    if(player == 1) {
        for(int i = 0; i < 8; i++) {
            if(getBackEndBoard(7, i) == 1) {
                setBackEndBoard(7, i, numChoice);
            }
        }
    }
    
    if(player == 2) {
        for(int i = 0; i < 8; i++) {
            if(getBackEndBoard(0, i) == -1) {
                setBackEndBoard(0, i, -numChoice);
            }
        }
    }
    
    
    
    
}
 







void board::setFrontEndBoard(int i, int j, char piece)
{
    frontEndBoard[i][j] = piece;
}

void board::printFrontEndBoard()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            /*   will figure this front end out eventually....
            int piece = getBackEndBoard(i, j);
            switch(piece)
            {
                case 0:
                    setFrontEndBoard(i, j, " ");
                    break;
                case 1:
                    setFrontEndBoard(i, j, "♙");
                    break;
                case 2:
                    setFrontEndBoard(i, j, "♖");
                    break;
                case 3:
                    setFrontEndBoard(i, j, "♘");
                    break;
                case 4:
                    setFrontEndBoard(i, j, "♗");
                    break;
                case 9:
                    setFrontEndBoard(i, j, "♕");
                    break;
                case 8:
                    setFrontEndBoard(i, j, "♔");
                    break;
                    
                case -1:
                    setFrontEndBoard(i, j, "♟");
                    break;
                case -2:
                    setFrontEndBoard(i, j, "♜");
                    break;
                case -3:
                    setFrontEndBoard(i, j, "♞");
                    break;
                case -4:
                    setFrontEndBoard(i, j, "♝");
                    break;
                case -9:
                    setFrontEndBoard(i, j, "♛");
                    break;
                case -8:
                    setFrontEndBoard(i, j, "♚");
                    break;
                */
            
            
            int piece = getBackEndBoard(i, j);
            switch(piece)
            {
                case 0:
                    setFrontEndBoard(i, j, ' ');
                    break;
                case 1:
                    setFrontEndBoard(i, j, 'p');
                    break;
                case 2:
                    setFrontEndBoard(i, j, 'r');
                    break;
                case 3:
                    setFrontEndBoard(i, j, 'n');
                    break;
                case 4:
                    setFrontEndBoard(i, j, 'b');
                    break;
                case 9:
                    setFrontEndBoard(i, j, 'k');
                    break;
                case 8:
                    setFrontEndBoard(i, j, 'q');
                    break;
                    
                case -1:
                    setFrontEndBoard(i, j, 'P');
                    break;
                case -2:
                    setFrontEndBoard(i, j, 'R');
                    break;
                case -3:
                    setFrontEndBoard(i, j, 'N');
                    break;
                case -4:
                    setFrontEndBoard(i, j, 'B');
                    break;
                case -9:
                    setFrontEndBoard(i, j, 'K');
                    break;
                case -8:
                    setFrontEndBoard(i, j, 'Q');
                    break;
            
            
                    
                    
            }
        }
    }
    
    
    std::cout << std::endl << std::endl;
    std::cout << "    ";
    char topLetter = 'A';
    for(int i=0; i<8; i++)
    {
        std::cout << std::setw(3) << std::right << "    " << topLetter << "   ";
        topLetter++;
    }
    std::cout << std::endl << "    #################################################################     White team" << std::endl;
    for (int i =0; i<8; i++)
    {
        std::cout << "    #       #       #       #       #       #       #       #       #" << std::endl;
        std::cout << std::setw(3) << std::left << i+1 ;
        for(int j=0; j<8; j++)
        {
            std::cout << std::setw(3) << std::left << " #   " << frontEndBoard[i][j] <<  "  ";
        }
        std::cout << " #" << std::endl;
        std::cout << "    #       #       #       #       #       #       #       #       #" << std::endl;
        std::cout << "    #################################################################" << std::endl;

    }
    
    std::cout << "                                                                            Black team" << std::endl;
    std::cout << std::endl << std::endl;


}
 


