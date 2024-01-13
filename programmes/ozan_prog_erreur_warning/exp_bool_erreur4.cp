CPYRR


fonction f() ret int {
    int var a;
    DEBUT
    a= 1;
    ret a;
    FIN
};

fonction g() ret float {
    float var a;
    DEBUT
    a= 1.0;
    ret a;
    FIN
};

DEBUT
SI (g() == f()) ALORS {
    DEBUT
    VIDE;
    FIN
};


FIN
CPYRR