#include <iostream>
#include <fstream>
#include <string>
#include "CCube.cpp"
//#pragma once

void GameCube()
{
    CCube cube;
    cube.GenerationCube();

    std::cout << "Game started\n"
              << "Enter \"stop\" to stop the game.\n"
              << "Enter \"show\" to show current state of the cube."
              << "Enter \"F\" / \"B\" / \"R\" / \"L\" / \"U\" / \"D\" to rotate clockwise the corresponding side"
              << "Enter \"F'\" / \"B'\" / \"R'\" / \"L'\" / \"U'\" / \"D'\" to rotate counterclockwise the corresponding side";

    while (true)
    {
        if(cube.IsSolvedCube())
        {
            std::cout << "You solve the cube!\n";
            break;
        }
        std::string command;
        std::cout << "Enter the command for the cube:\n";
        std::cin >> command;
        if(command == "stop")
        {
            std::cout << "Thank you for playing the game!\n";
            break;
        }
        else if(command == "show")
        {
            std::cout << cube;
        }
        else if(command == "F")
        {
            cube.F();
        }
        else if(command == "B")
        {
            cube.B();
        }
        else if(command == "R")
        {
            cube.R();
        }
        else if(command == "L")
        {
            cube.L();
        }
        else if(command == "U")
        {
            cube.U();
        }
        else if(command == "D")
        {
            cube.D();
        }
        else if(command == "F'")
        {
            cube.F_();
        }
        else if(command == "B'")
        {
            cube.B_();
        }
        else if(command == "R'")
        {
            cube.R_();
        }
        else if(command == "L'")
        {
            cube.L_();
        }
        else if(command == "U'")
        {
            cube.U_();
        }
        else if(command == "D'")
        {
            cube.D_();
        }
        else
        {
            std::cout << "The command is not recognised!\n";
        }
    }
}

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