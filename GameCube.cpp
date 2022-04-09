#include <fstream>
#include <string>
#include "CCube.cpp"

void GameCube()
{
    CCube cube;

    std::cout << "\nWelcome to our Rubik's cube game!\n"
              << "Enter \"file\" to read the cube from file.\n"
              << "Enter \"generate\" to generate the cube.\n"
              << "Enter \"solved\" to start the game with solved cube.\n";

    std::string command;
    std::cin >> command;

    if (command == "file")
    {
        std::cout << "\nEnter the file name:\n";
        std::string file_name;
        std::cin >> file_name;
        std::ifstream fin(file_name);
        if (fin)
        {
            fin >> cube;
            fin.close();
        }
        else
        {
            std::cout << "The file cannot be open!\n";
            GameCube();
        }
    }
    else if (command == "generate")
    {
        cube.GenerationCube();
    }
    else if (command == "solved")
    {
    }
    else
    {
        std::cout << "The command is not recognised!\n";
        GameCube();
    }

    std::cout << "\nGame started!\n"
              << "Enter \"stop\" to stop the game.\n"
              << "Enter \"show\" to show current state of the cube.\n"
              << "Enter \"file\" to save current state of cube in file.\n"
              << "Enter \"solve\" to solve the cube and show the cube solution.\n"
              << "Enter \"F\" / \"B\" / \"R\" / \"L\" / \"U\" / \"D\" to rotate clockwise the corresponding side.\n"
              << "Enter \"F'\" / \"B'\" / \"R'\" / \"L'\" / \"U'\" / \"D'\" to rotate counterclockwise the corresponding side.\n";

    while (true)
    {
        std::cout << "\nEnter the command for the cube:\n";
        std::cin >> command;

        if (command == "stop")
        {
            std::cout << "\nThank you for playing the game!\n"
                      << "Would you like to play the game again?\n"
                      << "Enter \"yes\" if you want and \"no\" if you don't want:\n";
            std::cin >> command;
            if (command == "yes")
            {
                GameCube();
            }
            else
            {
                return;
            }
        }
        else if (command == "file")
        {
            std::cout << "\nEnter the file name:\n";
            std::string file_name;
            std::cin >> file_name;
            std::ofstream fout(file_name);
            if (fout)
            {
                fout << cube;
                fout.close();
            }
            else
            {
                std::cout << "The file cannot be open!\n";
            }
            continue;
        }
        else if (command == "show")
        {
            std::cout << cube;
            continue;
        }
        else if (command == "solve")
        {
            std::string solution;
            cube.SolveCube(solution);
            std::cout << solution << "\n";
            std::cout << "\nThank you for playing the game!\n"
                      << "Would you like to play the game again?\n"
                      << "Enter \"yes\" if you want and \"no\" if you don't want:\n";
            std::cin >> command;
            if (command == "yes")
            {
                GameCube();
            }
            else
            {
                return;
            }
        }
        else if (command == "F")
        {
            cube.F();
        }
        else if (command == "B")
        {
            cube.B();
        }
        else if (command == "R")
        {
            cube.R();
        }
        else if (command == "L")
        {
            cube.L();
        }
        else if (command == "U")
        {
            cube.U();
        }
        else if (command == "D")
        {
            cube.D();
        }
        else if (command == "F'")
        {
            cube.F_();
        }
        else if (command == "B'")
        {
            cube.B_();
        }
        else if (command == "R'")
        {
            cube.R_();
        }
        else if (command == "L'")
        {
            cube.L_();
        }
        else if (command == "U'")
        {
            cube.U_();
        }
        else if (command == "D'")
        {
            cube.D_();
        }
        else
        {
            std::cout << "The command is not recognised!\n";
            continue;
        }
    }

    if (cube.IsSolvedCube())
    {
        std::cout << "\nCongratulations!\nYou solve the cube!\n"
                  << "Would you like to play the game again?\n"
                  << "Enter \"yes\" if you want and \"no\" if you don't want:\n";
        std::cin >> command;
        if (command == "yes")
        {
            GameCube();
        }
        else
        {
            return;
        }
    }
}