import numpy as np
import random as rnd
import math
# WEJŚCIE ________________________________________________________________

L = float(input())
N = int(input())
MCS = int(input())
T = float(input())
delta = float(input())
start_distance = float(input())

assert L > 0
assert N > 0
assert MCS > 0
assert T > 0
ro = N/L**2
assert ro <= 1.0

print("# L = {}   N = {}   ro* = {}   T = {}   MCS = {}   delta = {}".format(L,N,ro,T,MCS,delta))


# PRZYGOTOWANIE SYMULACJI ____________________________________________________

R = np.zeros((N,2))  # tablica złożona z wektorów [x,y] położeń atomów

rows = math.floor(N**0.5)  #rozmieszczenie atomów
i = 0
for ix in range(rows):
    for iy in range(N//rows + 1):
        if i < N:
            R[i] = [ix*start_distance,iy*start_distance]
            i += 1


def energy(i,dr):    # funkcja zwraca energię atomu o indeksie i, po przesunięciu o wektor dr
    ri = (R[i] + dr) % L
    Rj = np.delete(R,i,0)                    # kopia tablicy R bez elementu ri
    r_ij = np.linalg.norm(Rj - ri, axis = 1) # tablica odległości [r_i1, r_i2, r_i3, ..., r_iN]  #BUG - uwzględnić PBC!
    u = np.sum(4.0*(r_ij**(-12)-r_ij**(-6))) # suma po atomach rj (j != i)
    return u

U = [energy(i,0) for i in range(N)]

# SYMULACJA ___________________________________________________________________
for step in range(MCS):
    
    # KROK MONTE CARLO ________________________________________________________
    
    for i in range(N):
        dr = [delta*(rnd.random()-0.5), delta*(rnd.random()-0.5)]
        u_new = energy(i,dr)
        dU = u_new - U[i]

        # METROPOLIS __________________________________________________________
        if dU < 0:
            U[i] = u_new
            R[i] = (R[i] + dr) % L
        
        elif rnd.random() < math.exp(-dU/T):
            U[i] = u_new
            R[i] = (R[i] + dr) % L

for ri in R:
     print("{}\t{}".format(ri[0],ri[1]))