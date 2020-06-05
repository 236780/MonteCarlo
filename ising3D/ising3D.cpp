#include <iostream>
#include <assert.h>
#include <random>
#include <time.h>
using namespace std;

// Parametry:
uint L,mcs;
double T;

// Periodyczne war. brzegowe:
uint next(uint i){return i==L-1 ? 0 : i+1;}
uint prev(uint i){return i==0 ? L-1 : i-1;}

// Gener. liczb pseudolosowych:
default_random_engine rng_engine;
uniform_real_distribution<double> rng_distribution(0.0,1.0);
inline double rnd() {return rng_distribution(rng_engine);}

double dE(uint i, uint j, uint k);  // TODO

int main(int argc, char** argv)
{
    // Ustawienie ziarna RNG:
    int rng_seed;
    if (argc > 1) rng_seed = stoi(argv[1]); //Jezeli uzytkownik nie podal ziarna przy
    else rng_seed = time(nullptr);          //uruchomieniu programu, uzyj obecnego czasu

    // Wczytaj parametry z wej. standardowego:
    cin >> L >> mcs >> T;
    cout << "# L = " << L << ", T = " << T << ", " << mcs << " MCS" << endl;
    cout << "# seed: " << rng_seed;

    // Inicjalizacja tablicy:
    char spin[L][L][L];
    char newspin[L][L][L];

    // Losowanie konf. poczatkowej
    for(uint i=0;i<L;i++)
    {
        for(uint j=0;j<L;j++)
        {
            for(uint k=0;k<L;k++)
            {
                char rand_spin = rnd()<0.5 ? -1 : 1;
                spin[i][j][k] = rand_spin;
            }
        }
    }

    return 0;
}