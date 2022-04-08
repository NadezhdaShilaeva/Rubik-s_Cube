#include <fstream>
#include <string>
#include "CCube.cpp"

void GameCube()
{
    CCube cube;
    cube.GenerationCube();
    std::cout << cube.IsCorrectCube();

    std::cout << "Game started\n"
              << "Enter \"stop\" to stop the game.\n"
              << "Enter \"show\" to show current state of the cube.\n"
              << "Enter \"file\" to save current state of cube in file.\n"
              << "Enter \"solve\" to show the cube solution\n"
              << "Enter \"F\" / \"B\" / \"R\" / \"L\" / \"U\" / \"D\" to rotate clockwise the corresponding side.\n"
              << "Enter \"F'\" / \"B'\" / \"R'\" / \"L'\" / \"U'\" / \"D'\" to rotate counterclockwise the corresponding side.\n";

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
        else if (command == "file")
        {
            std::string file_name;
            std::cout << "Enter the file name:\n";
            std::cin >> file_name;
            std::ofstream fout(file_name);
            fout << cube;
            fout.close();
        }
        else if(command == "show")
        {
            std::cout << cube;
        }
        else if(command == "solve")
        {
            std::string solution;
            cube.SolveCube(solution);
            std::cout << solution;
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