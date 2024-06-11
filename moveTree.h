//
// Created by kubab on 08.06.2024.
//

#ifndef PAMSIPROJ3_MOVETREE_H
#define PAMSIPROJ3_MOVETREE_H

#include "checkersBoard.h"

struct node {

    int boardValue;
    int depth;
    int childNumber;
    std::vector<int> moveMade;
    checkersBoard currentBoard;

    node* next;
    node* prev;

    node();
};


class moveTree {

    node* root;
    std::vector<node*> nodes;

    void build_down(node* currnetNode);
    int minimax_alphabeta(node* currentNode, int depth, int alpha, int beta, bool maximizingPlayer);

    node* first_child(node* currentNode);
    node* next_child(node* currentNode);


public:
    moveTree(checkersBoard currentBoard);
    ~moveTree();

    std::vector<int> get_minimax_move(int depth, bool maximizingPlayer);

};


#endif //PAMSIPROJ3_MOVETREE_H
