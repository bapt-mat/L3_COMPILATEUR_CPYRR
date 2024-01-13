CPYRR

typedef float tab[1,4];
tab var t;

typedef int toto[1,4];
toto var a;

DEBUT
a[3]=1;
t[2] = 1.0;
SI ( t[2] == a[3]) ALORS {
    DEBUT
    VIDE;
    FIN
};


FIN
CPYRR