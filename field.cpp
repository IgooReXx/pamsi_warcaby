//
// Created by IGOR on 03.06.2024.
//

#include <stdexcept>

#include "field.h"


field::field(team t, type p) : pieceTeam(t), pieceType(p)
{

}

//team field::get_team()
//{
//    return pieceTeam;
//}
//
//type field::get_type()
//{
//    return pieceType;
//}

field::field() : pieceTeam(NO_TEAM), pieceType(NONE)
{}

//void field::set_type(type name)
//{
//    switch (name)
//    {
//        case NONE:
//            pieceType = NONE;
//            return;
//        case KING:
//            pieceType = KING;
//            return;
//        case MAN:
//            pieceType = MAN;
//            return;
//        default:
//            throw std::invalid_argument("field.set_type() - Invalid name");
//    }
//}
//
//void field::set_team(team name)
//{
//    switch (name)
//    {
//        case WHITE:
//            pieceTeam = WHITE;
//        case BLACK:
//            pieceTeam = BLACK;
//        case NO_TEAM:
//            pieceTeam = NO_TEAM;
//        default:
//            throw std::invalid_argument("field.set_type() - Invalid name");
//    }
//
//}

