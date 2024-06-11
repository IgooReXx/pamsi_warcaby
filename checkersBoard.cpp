//
// Created by IGOR on 03.06.2024.
//
#include "checkersBoard.h"

#include <iostream>
#include <vector>

#include "piece_char.h"
#include "possible_moves.h"


enum DIRECTION {EVEN_TOP_LEFT, EVEN_TOP_RIGHT, EVEN_BOTTOM_LEFT, EVEN_BOTTOM_RIGHT, ODD_TOP_LEFT, ODD_TOP_RIGHT, ODD_BOTTOM_LEFT, ODD_BOTTOM_RIGHT, INVALID};

checkersBoard::checkersBoard()
{
    for(int i = 0; i < 12; i++)
    {
        board[i] = field{BLACK, MAN};
    }

    for(int i = 20; i < 32; i++)
    {
        board[i] = field{WHITE, MAN};
    }



    //std::swap(board[11], board[15]);
    //std::swap(board[18], board[22]);

    //board[5] = field{BLACK, KING};
    //board[8] = field{WHITE, MAN};
    //board[9] = field{WHITE, MAN};
    //board[16] = field{WHITE, MAN};
    //board[17] = field{WHITE, MAN};
    //board[25] = field{WHITE, MAN};

}

void checkersBoard::board_display()
{
    for(int row = 0; row < 8; row++)
    {
        if(row % 2 == 0)
        {
            for (int column = 0; column < 8; column++)
            {
                if(column % 2 == 0)
                    continue;
                std::cout << "  ";
                if(board[((row * 8 + column) / 2 )].pieceType != NONE  or board[((row * 8 + column) / 2 )].pieceType != NONE)
                {
                    std::cout << piece_char(board[((row * 8 + column) / 2)]);
                }
                else
                    std::cout << "_";
                std::cout << " ";
            }
        }
        else
        {
            for (int column = 0; column < 8; column++)
            {
                if(column % 2 == 0)
                    continue;
                if(board[((row * 8 + column) / 2)].pieceType != NONE or board[((row * 8 + column) / 2)].pieceType != NONE)
                {
                    std::cout << piece_char(board[((row * 8 + column) / 2)]);
                }
                else
                    std::cout << "_";
                std::cout << "  ";
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool checkersBoard::is_forward(int startSquare, int endSquare, team playerTeam)
{
    switch (playerTeam)
    {
        case WHITE:
            if(startSquare > endSquare and (startSquare) / 4  > (endSquare) / 4) // większe pole and większy rząd
                return true;
            return false;
        case BLACK:
            if(startSquare < endSquare and (startSquare) / 4 < (endSquare) / 4 ) // mniejsze pole and mniejszy rząd
                return true;
            return false;
        default:
            return false;
    }
}

bool checkersBoard::is_valid_move_row(int startSquare, int endSquare)
{
    bool rowUp = (startSquare / 4 - 1 == endSquare / 4);
    bool rowDown = (startSquare / 4 == endSquare / 4 - 1);
    return (rowUp or rowDown);
}

bool checkersBoard::is_valid_move(int startSquare, int endSquare)
{
    switch((startSquare / 4 + 1 ) % 2)
    {
        case 0: // rząd parzysty
            if((endSquare == startSquare - 5) or (endSquare == startSquare - 4)) // możliwe ruchy piona (lewo or prawo)
                return true;
            if((endSquare == startSquare + 3) or (endSquare == startSquare + 4)) // możliwe ruchy damy (lewo or prawo)
                return true;
            return false;
        case 1: // rząd nieparzysty
            if((endSquare == startSquare - 4) or (endSquare == startSquare - 3)) // możliwe ruchy piona (lewo or prawo)
                return true;
            if((endSquare == startSquare + 4) or (endSquare == startSquare + 5)) // możliwe ruchy damy (lewo or prawo)
                return true;
            return false;
        default:
            throw std::invalid_argument("Invalid move");
    }
}

bool checkersBoard::initial_check(int startSquare, int endSquare, team playerTeam)
{
    if(startSquare < 0 or startSquare > 32 or endSquare < 0 or endSquare > 32) // wewnątrz planszy
        return false;
    type fieldType = board[startSquare].pieceType;
    if(fieldType == NONE) // czy pole startowe ma pion
        return false;
    if(board[endSquare].pieceType != NONE) // czy pole końcowe jest zajęte
        return false;
    if(board[startSquare].pieceTeam != playerTeam) // czy nasz pion
        return false;
    if(fieldType != KING) // jeśli nie dama, czy do przodu
        if(!is_forward(startSquare, endSquare, playerTeam))
            return false;
    return true;
}

bool checkersBoard::move_check(int startSquare, int endSquare, team playerTeam)
{
    if(!initial_check(startSquare, endSquare, playerTeam))
        return false;
    if(!is_valid_move_row(startSquare, endSquare)) // tylko jeden rząd
        return false;
    if(!is_valid_move(startSquare, endSquare)) // zgodny numer pola
        return false;
    return true;
}

bool checkersBoard::is_valid_jump_row(int startSquare, int endSquare)
{
    bool rowUp = ((startSquare)/ 4 - 2 == (endSquare) / 4);
    bool rowDown = ((startSquare) / 4 == (endSquare) / 4 - 2);
    return (rowDown or rowUp);
}

DIRECTION is_valid_jump(int startSquare, int endSquare, field fields[])
{
    switch ((((startSquare) / 4) + 1) % 2)
    {
        case 0: // rząd parzysty
            if(valid_etlj(startSquare, endSquare, fields)) // możliwe ruchy piona (lewo or prawo)
                return EVEN_TOP_LEFT;
            if(valid_etrj(startSquare, endSquare, fields))
                return EVEN_TOP_RIGHT;
            if(valid_eblj(startSquare, endSquare, fields)) // możliwe ruchy damy (lewo or prawo)
                return EVEN_BOTTOM_LEFT;
            if(valid_ebrj(startSquare, endSquare, fields))
                return EVEN_BOTTOM_RIGHT;
            return INVALID;
        case 1: // rząd nieparzysty
            if(valid_otlj(startSquare, endSquare, fields)) // możliwe ruchy piona (lewo or prawo)
                return ODD_TOP_LEFT;
            if(valid_otrj(startSquare, endSquare, fields))
                return ODD_TOP_RIGHT;
            if(valid_oblj(startSquare, endSquare, fields)) // możliwe ruchy damy (lewo or prawo)
                return ODD_BOTTOM_LEFT;
            if(valid_obrj(startSquare, endSquare, fields))
                return ODD_BOTTOM_RIGHT;
            return INVALID;
        default:
            throw std::invalid_argument("Invalid move");
    }

}


bool checkersBoard::jump_check(int startSquare, int endSquare, team playerTeam, field fields[])
{
    if(!initial_check(startSquare, endSquare, playerTeam))
        return false;

    if(!is_valid_jump_row(startSquare, endSquare)) // tylko jeden rząd
        return false;

    switch (is_valid_jump(startSquare, endSquare, fields))
    {
        case INVALID:
            return false;
        default:
            ;
    }
    return true;
}

void checkersBoard::move_make(int startSquare, int endSquare, team playerTeam)
{
    if(!move_check(startSquare, endSquare, playerTeam))
    {
        throw std::invalid_argument("Invalid move");
    }
    std::swap(board[startSquare], board[endSquare]);
}

void checkersBoard::jump_make(int startSquare, int endSquare, team playerTeam)
{
    if(!jump_check(startSquare, endSquare, playerTeam, board))
    {
        throw std::invalid_argument("chkBrd::jump_make() - Invalid jump");
    }
    switch(is_valid_jump(startSquare, endSquare, board))
    {
        case EVEN_TOP_RIGHT:
            board[startSquare-4].pieceType = NONE;
            board[startSquare-4].pieceTeam = NO_TEAM;
            break;
        case EVEN_TOP_LEFT:
            board[startSquare-5].pieceType = NONE;
            board[startSquare-5].pieceTeam = NO_TEAM;
            break;
        case EVEN_BOTTOM_RIGHT:
            board[startSquare+4].pieceType = NONE;
            board[startSquare+4].pieceTeam = NO_TEAM;
            break;
        case EVEN_BOTTOM_LEFT:
            board[startSquare+3].pieceType = NONE;
            board[startSquare+3].pieceTeam = NO_TEAM;
            break;
        case ODD_TOP_RIGHT:
            board[startSquare-3].pieceType = NONE;
            board[startSquare-3].pieceTeam = NO_TEAM;
            break;
        case ODD_TOP_LEFT:
            board[startSquare-4].pieceType = NONE;
            board[startSquare-4].pieceTeam = NO_TEAM;
            break;
        case ODD_BOTTOM_RIGHT:
            board[startSquare+5].pieceType = NONE;
            board[startSquare+5].pieceTeam = NO_TEAM;
            break;
        case ODD_BOTTOM_LEFT:
            board[startSquare+4].pieceType = NONE;
            board[startSquare+4].pieceTeam = NO_TEAM;
            break;
        case INVALID:
            throw std::invalid_argument("chkBrd::jump_make : Invalid jump");

    }
    std::swap(board[startSquare], board[endSquare]);
}

team checkersBoard::get_player()
{
    return player;
}

field *checkersBoard::get_board()
{
    return board;
}

std::vector<std::vector<int>> checkersBoard::list_valid_moves(int position, field currentField)
{
    std::vector<std::vector<int>> validMoves;
    switch ((((position) / 4) + 1) % 2)
    {
        case 0:
            if(move_check(position, position-5, currentField.pieceTeam))
                validMoves.emplace_back(1,position-5);
            if(move_check(position, position-4, currentField.pieceTeam))
                validMoves.emplace_back(1, position-4);
            if(move_check(position, position+3, currentField.pieceTeam))
                validMoves.emplace_back(1, position+3);
            if(move_check(position, position+4, currentField.pieceTeam))
                validMoves.emplace_back(1, position+4);
            break;
        case 1:
            if(move_check(position, position-4, currentField.pieceTeam))
                validMoves.emplace_back(1, position-4);
            if(move_check(position, position-3, currentField.pieceTeam))
                validMoves.emplace_back(1, position-3);
            if(move_check(position, position+4, currentField.pieceTeam))
                validMoves.emplace_back(1, position+4);
            if(move_check(position, position+5, currentField.pieceTeam))
                validMoves.emplace_back(1, position+5);
            break;
    }
    return validMoves;
}

void checkersBoard::multi_jump_recursion(std::vector<std::vector<int>>& validJumps, int currentPosition, int nextPostition, field currentField)
{
    if(jump_check(currentPosition, nextPostition, currentField.pieceTeam, board))
    {
        checkersBoard tmpBoard = *this;
        // hipotetyczny jump
        tmpBoard.jump_make(currentPosition, nextPostition, currentField.pieceTeam);
        auto wynik = tmpBoard.list_valid_jumps(nextPostition, currentField); // sprzężenie zwrotne rekurencji
        // koniec hipotetycznego jumpa
        if (wynik.empty())
            validJumps.push_back({nextPostition});
        for (auto vectorIter: wynik)
        {
            vectorIter.insert(vectorIter.begin(), nextPostition);
            validJumps.push_back(vectorIter);
        }
    }
}

std::vector<std::vector<int>> checkersBoard::list_valid_jumps(int position, field currentField)
{
    std::vector<std::vector<int>> validJumps;
    switch ((((position) / 4) + 1) % 2)
    {
        case 0:
            multi_jump_recursion(validJumps, position, position-5-4, currentField); // salto rekurencji
            multi_jump_recursion(validJumps, position, position-4-3, currentField);
            multi_jump_recursion(validJumps, position, position+3+4, currentField);
            multi_jump_recursion(validJumps, position, position+4+5, currentField);
            break;
        case 1:
            multi_jump_recursion(validJumps, position, position-4-5, currentField); // salto rekurencji
            multi_jump_recursion(validJumps, position, position-3-4, currentField);
            multi_jump_recursion(validJumps, position, position+4+3, currentField);
            multi_jump_recursion(validJumps, position, position+5+4, currentField);
            break;
    }

    return validJumps;
}

std::vector<std::pair<checkersBoard,std::vector<int>>> checkersBoard::possible_moves(team playerTeam)
{
    bool jumpsFound = false;
    std::vector<std::pair<checkersBoard,std::vector<int>>> jumpNodes;
    std::vector<std::pair<checkersBoard,std::vector<int>>> moveNodes;
    for(int boardIterator = 0; boardIterator < 32; ++boardIterator)
    {
        if(board[boardIterator].pieceTeam != playerTeam)
            continue;
        std::vector<std::vector<int>> moves;
        std::vector<std::vector<int>> jumps = list_valid_jumps(boardIterator, board[boardIterator]);
        if(jumps.empty())
        {
            if(jumpsFound)
                continue;
            moves = list_valid_moves(boardIterator, board[boardIterator]);
            for(auto moveVector : moves)
            {
                checkersBoard bufferNode = *this;
                field tmpField = board[boardIterator];
                int firstMove = boardIterator;
                for(auto moveIterator : moveVector)
                {
                    if (bufferNode.move_check(boardIterator, moveIterator, tmpField.pieceTeam))
                    {
                        bufferNode.turn++;
                        bufferNode.move_make(boardIterator, moveIterator, tmpField.pieceTeam);
                    }
                }
                moveVector.insert(moveVector.begin(), firstMove);
                moveNodes.emplace_back(bufferNode, moveVector);
            }
        }
        else
        {
            jumpsFound = true;
            int firstJump = boardIterator;
            for(auto jumpVector : jumps)
            {
                checkersBoard bufferNode = *this;
                field tmpField = board[boardIterator];
                int jumpStartPos = boardIterator;
                for(auto jumpIterator : jumpVector)
                {
                    if(bufferNode.jump_check(jumpStartPos, jumpIterator, tmpField.pieceTeam, bufferNode.get_board()))
                    {
                        bufferNode.jump_make(jumpStartPos, jumpIterator, tmpField.pieceTeam);
                        jumpStartPos = jumpIterator;
                        tmpField.pieceTeam = tmpField.pieceTeam;
                    }
                    bufferNode.turn++;
                }
                jumpVector.insert(jumpVector.begin(), firstJump);
                jumpNodes.emplace_back(bufferNode,jumpVector);
            }
        }

    }
    if(jumpsFound)
        return jumpNodes;
    return moveNodes;
}


//checkersBoard::checkersBoard(const checkersBoard &chkBrd)
//{
//    for(int i = 0; i<32; ++i)
//    {
//        this->board[i] = chkBrd.board[i];
//    }
//    this->player = chkBrd.player;
//    this->enemy = chkBrd.enemy;
//}

void checkersBoard::check_promotion()
{
    for(int boardIterator = 0; boardIterator < 4; ++boardIterator)
    {
        if(board[boardIterator].pieceTeam == WHITE and board[boardIterator].pieceType == MAN)
        {
            board[boardIterator].pieceType = KING;
        }
    }

    for(int boardIterator = 28; boardIterator < 32; ++boardIterator)
    {
        if(board[boardIterator].pieceTeam == BLACK and board[boardIterator].pieceType == MAN)
        {
            board[boardIterator].pieceType = KING;
        }
    }
}

int checkersBoard::get_turn()
{
    return turn;
}

void checkersBoard::play_turn(std::vector<int> moves, team playerTeam)
{
    if(moves.size() == 2)
    {
        if(move_check(moves[0], moves[1], playerTeam))
            move_make(moves[0], moves[1], playerTeam);
        else
            jump_make(moves[0], moves[1], playerTeam);
    }
    else
    {
        for (int jumpIterator = 0; jumpIterator < static_cast<int>(moves.size()-1); jumpIterator++)
            jump_make(moves[jumpIterator], moves[jumpIterator+1], playerTeam);
    }
    turn++;
    check_promotion();
}

void checkersBoard::set_player(team playerTeam)
{
    player = playerTeam;
}

void checkersBoard::set_enemy(team enemyTeam)
{
    enemy = enemyTeam;
}

team checkersBoard::get_enemy()
{
    return enemy;
}

bool checkersBoard::check_game_end()
{
    int whiteCount = 0, blackCount = 0;
    for(int fieldIterator = 0; fieldIterator < 32; ++fieldIterator)
    {
        if(board[fieldIterator].pieceTeam == WHITE)
            whiteCount++;
        if(board[fieldIterator].pieceTeam == BLACK)
            blackCount++;
    }
    if(whiteCount == 0)
        return true;
    if(blackCount == 0)
        return true;
    return false;
}
