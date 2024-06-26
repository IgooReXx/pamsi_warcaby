//
// Created by kubab on 08.06.2024.
//

#include <iostream>

#include <limits>
#include <cstdlib>

#include "moveTree.h"
#include "heuristics_function.h"

// https://www.geeksforgeeks.org/generic-treesn-array-trees/
// https://en.wikipedia.org/wiki/M-ary_tree
// https://stackoverflow.com/questions/24402734/multi-branch-tree-in-c

// https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning

node::node()
{
    boardValue = 0;
    depth = 0;
    childNumber = 0;
    currentBoard = checkersBoard();

    next = nullptr;
    prev = nullptr;
}

moveTree::moveTree(checkersBoard currentBoard)
{
    root = new node();
    root->currentBoard = currentBoard;
    nodes.push_back(root);

    build_down(root);
}

moveTree::~moveTree()
{
    for(auto treeIterator = nodes.rbegin(); treeIterator < nodes.rend(); ++treeIterator)
    {
        delete[] (**treeIterator).next;
    }
}

void moveTree::build_down(node* currentNode)
{
    team team;
    if(currentNode->currentBoard.get_turn() % 2 == 0)
        team = BLACK;
    else
        team = WHITE;

    std::vector<std::pair<checkersBoard, std::vector<int>>> possibleStates = currentNode->currentBoard.possible_moves(team);

    currentNode->childNumber = static_cast<int>(possibleStates.size());

    if(!possibleStates.empty())
    {
        currentNode->next = new node[possibleStates.size()];

        int childIterator = 0;
        for(auto stateIterator : possibleStates)
        {
            currentNode->next[childIterator].prev = currentNode;
            currentNode->next[childIterator].currentBoard = stateIterator.first;
            currentNode->next[childIterator].moveMade = stateIterator.second;
            currentNode->next[childIterator].depth = currentNode->depth + 1;
            nodes.push_back(&(currentNode->next[childIterator]));
            childIterator++;
        }
    }
}

node* moveTree::first_child(node *currentNode)
{
    if(currentNode->next == nullptr)
        build_down(currentNode);
    return currentNode->next;
}

node* moveTree::next_child(node *currentNode)
{
    if(currentNode->prev == nullptr)
        return nullptr;

    if(currentNode - currentNode->prev->next < currentNode->prev->childNumber - 1)
        return (currentNode + 1);

    return nullptr;
}


int moveTree::minimax_alphabeta(node *currentNode, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if(currentNode->depth == depth or currentNode->currentBoard.check_game_end())
    {
        currentNode->boardValue = heuristics_function(currentNode->currentBoard, BLACK);
        return currentNode->boardValue;
    }

    node* childNode = first_child(currentNode);
    if(childNode == nullptr)
        return currentNode->boardValue;

    if(maximizingPlayer)
    {
        int value = std::numeric_limits<int>::min();
        while(childNode != nullptr)
        {
            value = std::max(value, minimax_alphabeta(childNode, depth, alpha, beta, false));
            if (value > beta)
                break;
            alpha = std::max(alpha, value);
            childNode = next_child(childNode);
        }
        currentNode->boardValue = value;
        return value;
    }
    else
    {
        int value = std::numeric_limits<int>::max();
        while (childNode != nullptr)
        {
            value = std::min(value, minimax_alphabeta(childNode, depth, alpha, beta, true));
            if(value < alpha)
                break;
            beta = std::min(beta, value);
            childNode = next_child(childNode);
        }
        currentNode->boardValue = value;
        return value;
    }
}

std::vector<int> moveTree::get_minimax_move(int depth, bool maximizingPlayer)
{
    std::vector<std::vector<int>> bestPlays;
    minimax_alphabeta(root, depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), maximizingPlayer);
    node* childNode = first_child(root);
    while (childNode != nullptr)
    {
        if(childNode->boardValue == root->boardValue)
            bestPlays.emplace_back(childNode->moveMade);
        childNode = next_child(childNode);
    }

    if(bestPlays.empty())
        return std::vector<int>();
    return (bestPlays[rand() % bestPlays.size()]);
}
