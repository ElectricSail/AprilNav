#include<stdio.h>
#include <string>
#include <vector>
using namespace std;

namespace AprilTags{
  class Input {
  public:
    void set(double TIME, int TAGID, double x, double y, double PITCH, double ROLL, double YAW);
    void inputParse(std::string str);
    void tail(int n);
    void setup(FILE* fp);
    double getX();
    double getY();
  private:
    FILE* fp;
    int count;
    char oldwp[255];
    std::vector<double> vect;
    double WPX;
    double WPY;
  };
}
