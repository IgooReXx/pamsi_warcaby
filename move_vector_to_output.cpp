//
// Created by IGOR on 09.06.2024.
//

#include "move_vector_to_output.h"

std::string move_vector_to_output(std::vector<int> moveVector)
{
    bool isJump = false;
    std::string output, buffer;
    if(std::abs(moveVector[0]-moveVector[1]) > 5)
	isJump = true;
    for(int moveIterator = 0; moveIterator < static_cast<int>(moveVector.size()); moveIterator++)
    {
        buffer = std::to_string(moveVector[moveIterator]);
        output.append(buffer);
        if(moveIterator+1 != static_cast<int>(moveVector.size()))
	{
		if(isJump)
			output.append("x");
		else
        		output.append("-");

	}
    }
    return output;
}
