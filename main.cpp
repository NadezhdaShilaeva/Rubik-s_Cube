#include <iostream>
#include <fstream>
#include "GameCube.cpp"

int main()
{
    //GameCube();
    CCube cube;
    std::string solution;
    std::ifstream fin("cube1.txt");
    fin >> cube;
    cube.SolveCube(solution);
    return 0;
}