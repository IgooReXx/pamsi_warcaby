//
// Created by kubab on 31.05.2024.
//

#include <iostream>
#include "heuristics_function.h"


int heuristics_function(checkersBoard currentNode, team currentPlayer)
{
    int sum = 0;
    field* fields = currentNode.get_board();
    for(int boardIterator = 0; boardIterator < 32; ++boardIterator)
    {
        if(fields[boardIterator].pieceTeam == currentPlayer)
        {
            if(fields[boardIterator].pieceType == KING)
                sum += 3;
            else if(fields[boardIterator].pieceType == MAN)
                sum += 1;
        }
        else
        {
            if(fields[boardIterator].pieceType == KING)
            {
                sum-=3;
            }
            else if(fields[boardIterator].pieceType == MAN)
            {
                sum -= 1;
            }
        }
    }
    return sum;
}