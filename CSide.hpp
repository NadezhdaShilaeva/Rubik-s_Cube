#include <iostream>
#include <fstream>

class CSide
{
public:
    CSide();
    CSide(int color);
    CSide(int small_cube[3][3]);
    ~CSide();

    friend std::ifstream &operator>>(std::ifstream &stream, CSide &side);
    friend std::ostream &operator<<(std::ostream &stream, const CSide &side);
    friend std::ofstream &operator<<(std::ofstream &stream, const CSide &side);

    int GetNumColor(int y, int x) const;
    char GetColor(int y, int x) const;
    void SetColor(int y, int x, int color);

private:
    int small_cube_[3][3];
};