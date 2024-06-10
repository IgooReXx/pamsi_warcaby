//
// Created by kubab on 08.06.2024.
//

#include <iostream>

#include <limits>
#include <cstdlib>

#include "moveTree.h"
#include "heuristics_function.h"

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
    std::vector<std::pair<checkersBoard, std::vector<int>>> possibleStates;
    if(currentNode->currentBoard.get_turn() % 2 == 0)
        possibleStates = currentNode->currentBoard.possible_moves(BLACK);
    else
        possibleStates = currentNode->currentBoard.possible_moves(WHITE);

    currentNode->childNumber = static_cast<int>(possibleStates.size());

    if(possibleStates.empty())
        return;

    currentNode->next = new node[possibleStates.size()];

    int childIterator = 0;
    for(auto stateIterator : possibleStates)
    {
         currentNode->next[childIterator].currentBoard = stateIterator.first;
         currentNode->next[childIterator].moveMade = stateIterator.second;
         currentNode->next[childIterator].depth = currentNode->depth + 1;
         currentNode->next[childIterator].prev = currentNode;
         childIterator++;
    }
}

node* moveTree::down(node *currentNode)
{
    return currentNode->next;
}

node* moveTree::right(node *currentNode)
{
    if(currentNode->prev == nullptr)
        return nullptr;

    if(currentNode - currentNode->prev->next < currentNode->prev->childNumber - 1)
        return (currentNode + 1);

    return nullptr;
}


int moveTree::minimax_alphabeta(node *currentNode, int depth, int alpha, int beta, bool maximizingPlayer)
{

    if(depth == 0 or currentNode->next == nullptr)
    {
        currentNode->boardValue = heuristics_function(currentNode->currentBoard, BLACK);
        return currentNode->boardValue;
    }

    node* childNode = down(currentNode);

    if(maximizingPlayer)
    {
        int value = std::numeric_limits<int>::min();
        do
        {
            value = std::max(value, minimax_alphabeta(childNode, depth, alpha, beta, false));
            if(value > beta)
                break;
            alpha = std::max(alpha, value);
            childNode = right(childNode);
        } while (childNode != nullptr);
        currentNode->boardValue = value;
        return value;
    }
    else
    {
        int value = std::numeric_limits<int>::max();
        do
        {
            value = std::min(value, minimax_alphabeta(childNode, depth, alpha, beta, true));
            if(value < alpha)
                break;
            beta = std::min(beta, value);
            childNode = right(childNode);
        } while (childNode != nullptr);
        currentNode->boardValue = value;
        return value;
    }
}

std::vector<int> moveTree::get_minimax_move(int depth, bool maximizingPlayer)
{
    std::vector<std::vector<int>> bestPlays;
    minimax_alphabeta(root, depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), maximizingPlayer);
    node* childNode = down(root);
    do
    {
        if(childNode->boardValue == root->boardValue)
            bestPlays.emplace_back(childNode->moveMade);
        childNode = right(childNode);
    } while (childNode != nullptr);
    if(bestPlays.empty())
        return std::vector<int>();
    return (bestPlays[rand() % bestPlays.size()]);
}
