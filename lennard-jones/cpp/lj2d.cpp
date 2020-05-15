// Input format:
// ./lj2d L N MCS T [start_dist] [delta]

//#define EVERY_STEP

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <random>
#include <math.h>
#include <string>
using namespace std;
typedef unsigned int uint;

// GLOBAL CONSTANTS (to be read from parameters) ___
double L;
double delta;
double T;
uint N;
uint MCS;
double start_dist;

// GLOBAL ARRAYS ___________________________________
double* x;
double* y;
double* U;

// RANDOM NUMBER GENERATOR
// (returns random double x = [0.0, 1.0)) __________
double rndReal()
{
    static default_random_engine eng;
    static uniform_real_distribution<double> dist(0., 1.);
    return dist(eng);
}

// PERIODIC BOUNDARY CONDITIONS ____________________
double pbc(double q)
{
   double pbc = fmod(q,L);
   if(pbc < 0) pbc += L;
   return pbc; 
}

// CALCULATION OF ENERGY OF AN ATOM
// (after being moved by [dx,dy]) __________________
double energy(uint i, double dx = 0.0, double dy = 0.0)
{
    double Ui = 0;
    for(int j = 0; j < N; j++)
    {
        if(i != j)
        {
            double dxij = pbc(x[i] + dx) - x[j];
            if(dxij > L/2) dxij = L - dxij;

            double dyij = pbc(y[i] + dy) - y[j];
            if(dyij > L/2) dyij = L - dyij;

            double r2ij = pow(dxij,2) + pow(dyij,2);
           
            Ui += 4.0*(pow(r2ij,-6) - pow(r2ij,-3));
        }
    }
    return Ui;
}

// SINGLE MONTE CARLO STEP _________________________
void mcStep()
{
    for(uint i = 0; i < N; i++)
    {
        double dx = delta*rndReal()-0.5;
        double dy = delta*rndReal()-0.5;
        double u_new = energy(i,dx,dy);
        double dU = u_new - U[i];
        if(dU < 0  ||  rndReal() < exp(-dU/T))
        {
            U[i] = u_new;
            x[i] = pbc(x[i]+dx);
            y[i] = pbc(y[i]+dy);
        }
    }
    return;
}

int main(int argc, char** argv)
{
    assert(argc > 4);
    // READ INPUT PARAMETERS _______________________
    L = stod(argv[1]);
    N = stoi(argv[2]);
    MCS = stoi(argv[3]);
    T = stod(argv[4]);
    start_dist = (argc > 5) ? stod(argv[5]) : 0.3;
    delta = (argc > 6) ? stod(argv[6]) : 0.1;

    
    assert(L>0);
    assert(N>0);
    assert(MCS>=0);
    assert(T>0);

    double ro = (double)N / L / L;

    cout <<"# L = "<< L << "  N = " << N << "  MCS =" << MCS 
    << "  ro* = " << ro << "  T* = "<< T << endl; 

    // GENERATE START CONFIGURATION ________________
    x = new double[N];
    y = new double[N];
    U = new double[N];

    uint rows = sqrt(N);
    uint i = 0;
    for (uint j = 0; j < rows; j++)
    {
        for (uint k = 0; k < N/rows +1; k++)
        {
            if (i < N)
            {
                x[i] = start_dist*j;
                y[i] = start_dist*k;
                i++;
            }
            
        }
        
    }
    
    for (uint i = 0; i < N; i++)
    {
        U[i] = energy(i);
    }
    
    // RUN THE SIMULATION __________________________
    for(uint step=0; step<MCS; step++)
    {
        mcStep();
        #ifdef EVERY_STEP
            for (uint i = 0; i < N; i++)
            {
                cout << fixed << x[i]<< "\t"  << y[i] << "\t" << scientific << U[i] << endl;
            }
            cout << endl << endl;
        #endif
    }

    // PRINT RESULTS _______________________________
    cout << "# x\t\t  y\t\t  U" << endl;
    for (uint i = 0; i < N; i++)
    {
        cout << fixed << x[i]<< "\t"  << y[i] << "\t" << scientific << U[i] << endl;
    }
    
    delete x;
    delete y;
    delete U;
    return 0;
}

