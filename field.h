//
// Created by IGOR on 03.06.2024.
//

#ifndef PAMSIPROJ3_FIELD_H
#define PAMSIPROJ3_FIELD_H

enum team {NO_TEAM, BLACK, WHITE};
enum type {NONE, MAN, KING};

struct field {

    team pieceTeam;
    type pieceType;

    field();
    field(team t, type p);



};


#endif //PAMSIPROJ3_FIELD_H
