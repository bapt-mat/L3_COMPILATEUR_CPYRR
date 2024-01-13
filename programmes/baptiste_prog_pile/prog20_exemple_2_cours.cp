CPYRR

typedef struct date{
    int jour;
    int mois;
    int annee;
};

typedef struct personne{
    int numero;
    date naissance;
    int age;
};

typedef personne equipe[1,3; 1,2];

personne var p;
equipe var te;
bool var b;
float var i;
int var j;

procedure a(){
    procedure b(){
        int var T;
        procedure c(){
            DEBUT 
            VIDE;
            FIN
        };
        
        procedure saisie(){
            int var i;
            DEBUT
            ecrire("proc saisie();\n");
            i=0;
            j=0;
            TANT QUE (i<3) FAIRE {
                DEBUT
                i=i+1;
                TANT QUE (j<2) FAIRE{
                    DEBUT
                    j=j+1;
                    ecrire("Numero de securite sociale\n");
                    lire(te[i,j].numero);
                    FIN
                };
                T=j;
                FIN
            };
            FIN
        };

        DEBUT
        ecrire("proc b();\n");
        saisie();
        FIN
    };
    DEBUT
    ecrire("proc a();\n");
    b();
    FIN
};

procedure e(){
    procedure f(){
        procedure g(){
            DEBUT 
            ecrire("proc g();\n");
            a();
            FIN
        };
        DEBUT
        ecrire("proc f();\n");
        g();
        FIN
    };
    
    procedure h(){
        DEBUT
        ecrire("proc h();\n");
        f();
        FIN
    };

    DEBUT
    ecrire("proc e();\n");
    h();
    FIN
};

procedure i(){
    int var T;
    DEBUT
    ecrire("proc i();\n");
    e();
    T=j;
    ecrire("T = j (%d)\n", j);
    FIN
};

DEBUT
ecrire("prog principal;\n");
i();
FIN

CPYRR