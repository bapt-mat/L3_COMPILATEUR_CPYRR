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
            i=0;
            j=0;
            TANT QUE (i<3) FAIRE {
                DEBUT
                i=i+1;
                TANT QUE (j<2) FAIRE{
                    DEBUT
                    j=j+1;
                    ecrire("\nNumero de securite sociale");
                    lire(te[i,j].numero);
                    FIN
                };
                T=j;
                FIN
            };
            FIN
        };

        DEBUT
        saisie();
        FIN
    };
    DEBUT
    VIDE;
    FIN
};

procedure e(){
    procedure f(){
        procedure g(){
            DEBUT 
            a();
            FIN
        };
        DEBUT
        g();
        FIN
    };
    
    procedure h(){
        DEBUT
        f();
        FIN
    };

    DEBUT
    h();
    FIN
};

procedure i(){
    int var T;
    DEBUT
    e();
    T=j;
    FIN
};

DEBUT
i();
FIN

CPYRR