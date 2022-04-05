#include <iostream>
#include <fstream>
#include "CCube.cpp"
//#pragma once

int main()
{
    std::ifstream fin("cube.txt");
    std::ofstream fout("result.txt");
    CCube cube;
    if (!fout)
    std::cout << "lknkl";
    //fout << 'j';
    fin >> cube;
    //fout << cube;
    //std::cout << cube;
    return 0;
}