#include <iostream>
#include <fstream>
#include "GameCube.cpp"

int main()
{
    //GameCube();
    CCube cube;
    std::string solution;
    std::ifstream fin("cube.txt");
    cube.GenerationCube();
    //cube.SolveCube(solution);
    return 0;
}