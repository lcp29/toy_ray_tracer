#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    int i = 0;
    double off = 0;
    for (; off < 7; off += 0.1, i++)
    {
        string fn = "out" + to_string(i) + ".png";
        system((static_cast<string>("FoCG_3_Ray_Tracer.exe ") + to_string(off)).c_str());
        system((static_cast<string>("rename ") + string("output.png ") + fn).c_str());
    }
    for (; off > 0; off -= 0.1, i++)
    {
        string fn = "out" + to_string(i) + ".png";
        system((static_cast<string>("FoCG_3_Ray_Tracer.exe ") + to_string(off)).c_str());
        system((static_cast<string>("rename ") + string("output.png ") + fn).c_str());
    }
    return 0;
}