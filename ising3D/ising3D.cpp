#include <iostream>
#include <assert.h>
using namespace std;

// Parametry:
uint L,mcs;
double T;

// Periodyczne war. brzegowe:
uint next(uint i){return i==L-1 ? 0 : i+1;}
uint prev(uint i){return i==0 ? L-1 : i-1;}

double dE(uint i, uint j, uint k)
{
    
}

int main (int argc, char** argv)
{
    // Wczytaj parametry:
    cin >> L >> mcs >> T;
    cout << "# L = " << L << ", T = " << T << ", " << mcs << " MCS" << endl;

    // Inicjalizacja tablicy:
    char spin[L][L][L];
    char newspin[L][L][L];
    


    return 0;
}