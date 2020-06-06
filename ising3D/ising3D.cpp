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

int main(int argc, char** argv)
{
    // Ustawienie ziarna RNG:
    int rng_seed;
    if (argc > 1) rng_seed = stoi(argv[1]); //Jezeli uzytkownik nie podal ziarna przy
    else rng_seed = time(nullptr);          //uruchomieniu programu, uzyj obecnego czasu

    // Wczytaj parametry z wej. standardowego:
    cin >> L >> mcs >> T;
    cout << "# L = " << L << ", T* = " << T << ", " << mcs << " MCS" << endl;
    cout << "# seed: " << rng_seed;

    // Oblicz czynniki exp(-dU/T*)
    double boltzmann[7];
    for(char dU=-6; dU<=6; dU+=2)
    {
        boltzmann[(dU+6)/2] = exp(-double(dU)/T);
        cout << "#" << boltzmann[(dU+6)/2] << endl; //DEBUG
    }
    // Deklaracja tablicy:
    char spin[L][L][L];

    // Losowanie konf. poczatkowej
    for(uint i=0;i<L;i++){
    for(uint j=0;j<L;j++){
    for(uint k=0;k<L;k++)
    {
        char rand_spin = rnd()<0.5 ? -1 : 1;
        spin[i][j][k] = rand_spin;
    }}}

    // Monte Carlo
    for(uint step=0;step<mcs;step++)
    {
        long M=0;
        long E=0;
        for(uint i=0;i<L;i++){
        for(uint j=0;j<L;j++){
        for(uint k=0;k<L;k++)
        {
            char dU = -2*spin[i][j][k]*(
              spin[prev(i)][j][k]+spin[next(i)][j][k]+
              spin[i][prev(j)][k]+spin[i][next(j)][k]+
              spin[i][j][prev(k)]+spin[i][j][next(k)]);

            if(dU < 0 || rnd() < boltzmann[(dU+6)/2])
            {
                spin[i][j][k] = -spin[i][j][k];
                E += dU;
            }
            else
            {
                E += -dU;
            }
            
            M += spin[i][j][k];
        }}}

        if(step%100 == 0 && step > 30000)
        {
            double m = (double)M / (double)pow(L,3);
            cout << m << "\t\t" << E << endl;
        }
    }

    return 0;
}
