CPYRR
int var xyz;
int var x;

fonction addition(int a, int b) ret int{
    DEBUT
    ret(a+b);
    FIN
};

fonction multiplication(int a, int b) ret int{
    DEBUT
    ret(a*b);
    FIN
};

procedure une(){
    int var x;
    int var z;
    DEBUT
    x=555;
    z=999;
    FIN
};

procedure test(){
    int var x;
    DEBUT
    x=52;
    FIN
};

procedure voila(){
    int var x;
    DEBUT
    x=111;
    test();
    FIN
};

procedure toto(){
    int var x;

    procedure tata(){
        int var y;
        procedure titi(){
            int var z;
            DEBUT
            z=addition(x, y);
            ecrire("x = %d et y = %d\n",x, y);
            ecrire ("z = %d\n",z);
            voila();
            FIN
        };
        DEBUT
        y=multiplication(xyz,5);
        une();
        titi();
        FIN
    };
    DEBUT
    x=8;
    tata();
    FIN
};


DEBUT
xyz=15;

x=multiplication(4, 11);
toto();
xyz = addition(12,addition(x,x));

//ecrire("fin du programme");
FIN

CPYRR