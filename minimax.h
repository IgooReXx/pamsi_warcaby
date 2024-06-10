//
// Created by IGOR on 03.06.2024.
//

#ifndef PAMSIPROJ3_MINIMAX_H
#define PAMSIPROJ3_MINIMAX_H

class checkersBoard;

#include <vector>

std::pair<int, std::vector<int>> minimax_alphabeta(checkersBoard& boardNode, int depth, int alpha, int beta, bool maximizingPlayer);

#endif //PAMSIPROJ3_MINIMAX_H
