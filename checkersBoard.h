//
// Created by IGOR on 03.06.2024.
//

#ifndef PAMSIPROJ3_CHECKERSBOARD_H
#define PAMSIPROJ3_CHECKERSBOARD_H

#include <vector>

#include "field.h"


class checkersBoard {

    field board[32];
    team player = BLACK;
    team enemy = WHITE;
    int turn = 0;

    static bool is_forward(int startSquare, int endSquare, team playerTeam);

    bool initial_check(int startSquare, int endSquare, team playerTeam);

    static bool is_valid_move_row(int startSquare, int endSquare);
    static bool is_valid_move(int startSquare, int endSquare);
    bool move_check(int startSquare, int endSquare, team playerTeam);

    static bool is_valid_jump_row(int startSquare, int endSquare);
    bool jump_check(int startSquare, int endSquare, team playerTeam, field fields[]);


    void move_make(int startSquare, int endSquare, team playerTeam);
    void jump_make(int startSquare, int endSquare, team playerTeam);


    std::vector<std::vector<int>> list_valid_moves(int position, field currentField);
    void multi_jump_recursion(std::vector<std::vector<int>>& validJumps, int currentPosition, int nextPosition, field currentField);
    std::vector<std::vector<int>> list_valid_jumps(int position, field currentField);
    void check_promotion();



public:

    checkersBoard();
    checkersBoard(const checkersBoard& chkBrd) = default;
    void board_display();

    team get_player();
    team get_enemy();
    field* get_board();
    int get_turn();

    void set_player(team playerTeam);
    void set_enemy(team enemyTeam);

    std::vector<std::pair<checkersBoard,std::vector<int>>> possible_moves(team playerTeam);

    void play_turn(std::vector<int> moves, team playerTeam);

    bool check_game_end();

};


#endif //PAMSIPROJ3_CHECKERSBOARD_H
