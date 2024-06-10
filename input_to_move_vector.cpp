//
// Created by IGOR on 08.06.2024.
//

#include "input_to_move_vector.h"


std::vector<int> input_to_move_vector(std::string input)
{
    std::vector<int> enemyMoves;
    std::string buffer;
    for (int inputIndex = 0; inputIndex < input.length(); ++inputIndex)
    {
        if(!isdigit(input[inputIndex]))
        {
            if(buffer.length() > 0)
                enemyMoves.push_back(stoi(buffer));
            buffer.clear();
            continue;
        }
        buffer.push_back(input[inputIndex]);
    }
    if(buffer.length() > 0)
        enemyMoves.push_back(stoi(buffer));
    return enemyMoves;
}