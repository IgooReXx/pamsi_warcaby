//
// Created by IGOR on 03.06.2024.
//

#include "possible_moves.h"

bool valid_etlj(int startSquare, int endSquare, field fields[]) // even top left jump
{
    bool piecePresent = (fields[startSquare - 5].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare - 5].pieceTeam != fields[startSquare].pieceTeam;
    bool topLeftJump = endSquare == startSquare - 4 - 5;
    if(topLeftJump and isEnemy)
        return true;
    return false;
}

bool valid_etrj(int startSquare, int endSquare, field fields[]) // even top right jump
{
    bool piecePresent = (fields[startSquare - 4].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare - 4].pieceTeam != fields[startSquare].pieceTeam;
    bool topRightJump = endSquare == startSquare - 3 - 4;
    if(topRightJump and isEnemy)
        return true;
    return false;
}

bool valid_eblj(int startSquare, int endSquare, field fields[])
{
    bool piecePresent = (fields[startSquare + 3].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare].pieceTeam != fields[startSquare + 3].pieceTeam;
    bool bottomLeftJump = endSquare == startSquare + 4 + 3;
    if(bottomLeftJump and isEnemy)
        return true;
    return false;
}

bool valid_ebrj(int startSquare, int endSquare, field fields[])
{
    bool piecePresent = (fields[startSquare + 4].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare + 4].pieceTeam != fields[startSquare].pieceTeam;
    bool bottomRightJump = endSquare == startSquare + 5 + 4;
    if(bottomRightJump and isEnemy)
        return true;
    return false;
}
bool valid_otlj(int startSquare, int endSquare, field fields[])
{
    bool piecePresent = (fields[startSquare - 4].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare].pieceTeam != fields[startSquare - 4].pieceTeam;
    bool topLeftJump = endSquare == startSquare - 5 - 4;
    if(topLeftJump and isEnemy)
        return true;
    return false;
}

bool valid_otrj(int startSquare, int endSquare, field fields[])
{
    bool piecePresent = (fields[startSquare - 3].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare - 3].pieceTeam != fields[startSquare].pieceTeam;
    bool topRightJump = endSquare == startSquare - 4 - 3;
    if(topRightJump and isEnemy)
        return true;
    return false;
}

bool valid_oblj(int startSquare, int endSquare, field fields[])
{
    bool piecePresent = (fields[startSquare + 4].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare + 4].pieceTeam != fields[startSquare].pieceTeam;
    bool bottomLeftJump = endSquare == startSquare + 3 + 4;
    if(bottomLeftJump and isEnemy)
        return true;
    return false;
}

bool valid_obrj(int startSquare, int endSquare, field fields[])
{
    bool piecePresent = (fields[startSquare + 5].pieceType != NONE);
    if(!piecePresent)
        return false;
    bool isEnemy = fields[startSquare + 5].pieceTeam != fields[startSquare].pieceTeam;
    bool bottomRightJump = endSquare == startSquare + 4 + 5;
    if(bottomRightJump and isEnemy)
        return true;
    return false;
}