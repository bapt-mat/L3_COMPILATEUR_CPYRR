CPYRR
int var n;
int var a;
int var b;
int var c;

procedure suite_fibonacci(int limite) {
    DEBUT
    a = 0;
    b = 1;
    ecrire("Suite de Fibonacci jusqu'au terme %d :\n", limite);
    ecrire("%d\n%d\n", a, b);

    TANT QUE (c < limite) FAIRE {
        DEBUT
        c = a + b;
        ecrire("%d\n", c);
        a = b;
        b = c;
        FIN
    };
    FIN
};

DEBUT
ecrire("Suite de Fibonacci\n");
ecrire("Limite souhaitée ?\n");
lire(n);
suite_fibonacci(n);
FIN
CPYRR
