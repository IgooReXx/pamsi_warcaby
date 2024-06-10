//
// Created by IGOR on 03.06.2024.
//

#ifndef PAMSIPROJ3_POSSIBLE_MOVES_H
#define PAMSIPROJ3_POSSIBLE_MOVES_H

#include "field.h"

bool valid_etlj(int startSquare, int endSquare, field fields[]); // even top left jump
bool valid_etrj(int startSquare, int endSquare, field fields[]); // even top right jump
bool valid_eblj(int startSquare, int endSquare, field fields[]);
bool valid_ebrj(int startSquare, int endSquare, field fields[]);

bool valid_otlj(int startSquare, int endSquare, field fields[]);
bool valid_otrj(int startSquare, int endSquare, field fields[]);
bool valid_oblj(int startSquare, int endSquare, field fields[]);
bool valid_obrj(int startSquare, int endSquare, field fields[]);

#endif //PAMSIPROJ3_POSSIBLE_MOVES_H
