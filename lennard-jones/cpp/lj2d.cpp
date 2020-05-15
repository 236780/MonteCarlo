// Input format:
// ./lj2d L N MCS

#include <iostream>
#include <assert.h>
#include <random>
#include <limits>
#include <math.h>
using namespace std;

// GLOBAL CONSTANTS
double L;
int N;
int MCS;

// ARRAYS
double* x;
double* y;
double* U;

int main(int argc, char** argv)
{
    L = *argv[1];
    N = *argv[2];
    MCS = *argv[3];
    
    assert(L>0);
    assert(N>0);
    assert(MCS>0);
    
    double ro = (double)N / L / L;

    x = new double[N];
    y = new double[N];
    U = new double[N];

    cout <<"# L = "<< L << "  N = " << N << "  ro = " << ro <<  "  MCS = " << MCS << endl;


    delete x, y, U;
    return 0;
}

double pbc(double q)
{
   double pbc = (int)q % L + q - trunc(q);
   if(pbc < 0) pbc += 3;
   return pbc; 
}

double energy(int i)
{
    double Ui = 0;
    for(int j = 0; j < N; j++)
    {
        if(i != j)
        {
            double dxij = x[i] - x[j];
            if(dxij > L/2) dxij = L - dxij;

            double dyij = y[i] - y[j];
            if(dyij > L/2) dyij = L - dyij;
            
            double r2ij = dxij^2 + dyij^2;
           

        }
    }
}
