#include "CSide.hpp"
//#include <iostream>

class CCube
{
    public:
    CCube();
    ~CCube();
    friend std::fstream &operator>>(std::fstream &stream, CCube &cube);
    friend std::ostream &operator<<(std::ostream &stream, const CCube &cube);
    friend std::fstream &operator<<(std::fstrean &stream, const CCube &cube);
    private:
    CSide sides_[6];
};