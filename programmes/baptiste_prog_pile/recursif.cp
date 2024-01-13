CPYRR
int var x;

typedef struct info{
    int ch1;
    float ch2;
    bool ch3;
};

typedef info tab[1,3];

tab var t;

info var s;

procedure p1(){
    int var z;
    procedure p2(){
        int var y;
        DEBUT
        y = x;
        FIN
    };
    procedure p3(int a){
        DEBUT
        ecrire("a = %d\n", a);
        ecrire("x = %d\n", x);
        SI (a>1) ALORS{
            DEBUT
            ecrire("Appel récursif\n");
            p3(a-(10));
            FIN
        }SINON{
            DEBUT
            ecrire("Fin récursivité\n");
            p2();
            x = 888;
            FIN
        };
        FIN
    };
    DEBUT
    p3(x-(5));
    FIN
};

procedure p6(float x1, int x2, bool x3){
    info var j;
    procedure p7(){
        procedure p56(){
            DEBUT
            VIDE;
            FIN
        };
        procedure p8(float r){
            procedure p9(){
                DEBUT 
                r = x1;
                p1();
                FIN
            };
            DEBUT
            p9();
            FIN
        };
        DEBUT
        p8(3.14);
        FIN
    };
    DEBUT
    j.ch1 = 3;
    j.ch2 = 2.8;
    j.ch3 = FALSE;
    p7();
    FIN
};

procedure p4(){
    info var i;
    procedure p5(){
        DEBUT 
        i.ch2 = 6.5;
        p6(3.14, 5, TRUE);
        FIN
    };
    DEBUT
    p5();
    FIN
};

DEBUT
t[1].ch1 = 5;
t[2].ch2 = 12.0;
t[3].ch1 = 47;
x = 43;
p4();
ecrire("x=%d\n",x);
FIN

CPYRR