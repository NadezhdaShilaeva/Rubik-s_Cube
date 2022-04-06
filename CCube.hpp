#include "CSide.hpp"

class CCube
{
public:
    CCube();
    CCube(CSide sides[6]);
    ~CCube();

    const CSide &GetSide(int i) const;
    bool IsCorrectCube() const;

    friend std::ifstream &operator>>(std::ifstream &stream, CCube &cube);
    friend std::ostream &operator<<(std::ostream &stream, const CCube &cube);
    friend std::ofstream &operator<<(std::ofstream &stream, const CCube &cube);

private:
    CSide sides_[6];
};