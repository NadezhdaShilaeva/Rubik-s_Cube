#include <iostream>
#include <fstream>
#include "CCube.cpp"
//#pragma once

int main()
{
    std::ifstream fin("cube.txt");
    CCube cube;
    fin >> cube;
    fin.close();

    std::ofstream fout("result.txt");
    fout << cube;
    fout.close();

    std::cout << cube;
    
    return 0;
}