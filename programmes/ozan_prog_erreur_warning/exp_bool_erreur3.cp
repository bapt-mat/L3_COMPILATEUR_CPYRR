CPYRR

typedef float tab[1,4];
tab var t;


fonction f() ret int {
    int var a;
    DEBUT
    a= 1;
    ret a;
    FIN
};

DEBUT
t[2] = 1.0;
SI ( t[2] == f()) ALORS {
    DEBUT
    VIDE;
    FIN
};


FIN
CPYRR