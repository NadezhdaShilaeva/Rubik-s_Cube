#include "CCube.hpp"

CCube::CCube() {}
CCube::CCube(CSide sides[6])
{
    memcpy(sides_, sides, sizeof(sides_));
}
CCube::~CCube() {}

const CSide &CCube::GetSide(int i) const
{
    return sides_[i];
}

std::ifstream &operator>>(std::ifstream &stream, CCube &cube)
{
    CSide sides[6];
    for (int i = 0; i < 6; ++i)
    {
        stream >> sides[i];
        stream.get();
    }
    cube = CCube(sides);
    return stream;
}
std::ostream &operator<<(std::ostream &stream, const CCube &cube)
{
    for (int i = 0; i < 6; ++i)
    {
        stream << cube.GetSide(i) << std::endl;
    }
    return stream;
}
std::ofstream &operator<<(std::ofstream &stream, const CCube &cube)
{
    for (int i = 0; i < 6; ++i)
    {
        stream << cube.GetSide(i) << std::endl;
    }
    return stream;
}