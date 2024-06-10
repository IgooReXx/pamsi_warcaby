//
// Created by IGOR on 03.06.2024.
//

#include <stdexcept>
#include "piece_char.h"

char piece_char(field currentField)
{
    switch (currentField.pieceTeam)
    {
        case WHITE:
            if(currentField.pieceType == MAN)
                return 'w';
            else if(currentField.pieceType == KING)
                return 'W';
            else
                return ' ';
        case BLACK:
            if(currentField.pieceType == MAN)
                return 'b';
            else if(currentField.pieceType == KING)
                return 'B';
            else
                return ' ';
        case NO_TEAM:
            return ' ';
    }
    throw std::invalid_argument("piece_char - Invalid piece.");
}