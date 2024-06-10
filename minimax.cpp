//
// Created by IGOR on 02.06.2024.
//
#include <iostream>

#include <limits>

#include "minimax.h"
#include "checkersBoard.h"
#include "heuristics_function.h"


std::pair<int, std::vector<int>> minimax_alphabeta(checkersBoard& boardNode, int depth, int alpha, int beta, bool maximizingPlayer);
