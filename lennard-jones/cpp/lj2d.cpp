// Input format:
// ./lj2d L N MCS

#include <iostream>
#include <assert.h>
#include <random>
#include <limits>
using namespace std;

int main(int argc, char** argv)
{
    const int L = *argv[1];
    const int N = *argv[2];
    const int MCS = *argv[3];
    
    assert(L>0);
    assert(N>0);
    assert(MCS>0);
    
    const double ro = (double)N / L / L;

    cout <<"# L = "<< L << "  N = " << N << "  ro = " << ro <<  "  MCS = " << MCS << endl
         << "# Max value ~10e"<< DBL_MAX_10_EXP << endl;

    return 0;




}
