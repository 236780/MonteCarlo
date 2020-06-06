Uwagi:
    * Python używa podwójnej precyzji (10**308) domyślnie

    * Operacja reszty z dzielenia w pythonie jest zdefiniowana
        dla liczb rzeczywistych. Wynik dzielenia modulo (w przeciwieństwie do np. C++)
         ma zawsze znak dzielnika, tj.
             5.2 % 3.0 = 2.2
            -1.0 % 3.0 = 2.0
            -5.2 % 3.0 = 0.8
        Taka definicja pozwala na łatwą implementację periodycznych war. brzegowych:
            x_pbc = x % L
        
    * Korzystam z biblioteki numpy, która pozwala na szybkie obliczenia (jej funkcje
      są napisane w języku kompilowanym). Przy obliczaniu energii zastąpiłem pętlę operacjami
      na wektorach/macierzach, które są wykonywane równolegle
