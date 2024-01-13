CPYRR

typedef int renard[1,5];

typedef struct prince{
    renard roses;
    int planete;
};

renard var animal;
int var x;

procedure on(){
    procedure ne(){
        procedure voit(){
            prince var petit;
            DEBUT
            petit.roses[3] = 7;
            ecrire("petit.roses[3] = %d\n", petit.roses[3]);
            FIN
        };
        DEBUT
        voit();
        FIN
    };
    procedure qu(){
        DEBUT
        ne();
        FIN
    };
    procedure avec(){
        DEBUT
        qu();
        FIN
    };
    procedure le(){
        procedure coeur(){
            DEBUT
            ne();
            FIN
        };
        procedure l(){
            DEBUT
            avec();
            FIN
        };
        DEBUT
        coeur();
        FIN
    };
    procedure essentiel(){
        procedure est(){
            int var z;
            DEBUT 
            z=x;
            ecrire ("z=%d\n", z);
            le();
            FIN
        };
        procedure invisible(){
            renard var serpent;
            int var y;
            procedure pour(){
                procedure les(){
                    DEBUT
                    le();
                    y=x;
                    ecrire("y=%d\n", y);
                    FIN
                };
                DEBUT
                les();
                FIN
            };
            DEBUT
            serpent[1] = 99;
            ecrire("serpent[1] = %d\n", serpent[1]);
            pour();
            FIN
        };
        DEBUT 
        invisible();
        FIN
    };
    procedure yeux(){
        DEBUT
        essentiel();
        FIN
    };
    DEBUT
    yeux();
    FIN
};
DEBUT
animal[1] = 77;
x=5;
ecrire ("animal[1] = %d\n", animal[1]);
ecrire ("x=%d\n", x);
on();
FIN

CPYRR