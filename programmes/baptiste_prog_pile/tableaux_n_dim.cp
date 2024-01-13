CPYRR

/*L'accès a une case d'un tableau se fait en indiquant le numéro/l'indice de la case*/
/*ex : dimension : [-3,3] -> indices de 1 a 7*/

int var i1;
int var i2;
int var i3;
int var i4;
int var indice;

typedef int toto[1,4; 1,4; 1,3; 1,3];

typedef struct tata{
    toto x;
    int y;
};

typedef struct structComplicado{
    tata un;
    toto deux;
};

toto var t;
tata var varTata;
structComplicado var varComplicado;


procedure un(){
    int var x;
    procedure procComplicado(){
        DEBUT
        ecrire("varComplicado.un.x[3,4,2,1] = %d\n", varComplicado.un.x[3,4,2,1]);
        ecrire("Modifier la valeur de varComplicado.un.x[3,4,2,1] : ");
        lire(varComplicado.un.x[3,4,2,1]);
        ecrire("Nouvelle valeur de varComplicado.un.x[3,4,2,1] : %d\n", varComplicado.un.x[3,4,2,1]);
        ecrire("x = varComplicado.un.x[3,4,2,1] + varComplicado.deux[4,4,3,3] (derniere valeur de la pile)\n");
        x = varComplicado.un.x[3,4,2,1] + varComplicado.deux[4,4,3,3];
        ecrire("x = %d\n", x);
        FIN
    };
    DEBUT
    procComplicado();
    FIN
};

DEBUT
indice=1;

POUR (i1 = 1; i1 <= 3; i1 = i1 + 1) FAIRE{
    DEBUT
    POUR (i2 = 1; i2 <= 3; i2 = i2 + 1) FAIRE{
        DEBUT
        POUR (i3 = 1; i3 <= 4; i3 = i3 + 1) FAIRE{
            DEBUT
            POUR (i4 = 1; i4 <= 4; i4 = i4 + 1) FAIRE{
                DEBUT
                t[i4, i3, i2, i1] = indice;
                indice = indice + 1;
                FIN
            };
            FIN
        };  
        FIN
    };        
    FIN
};


POUR (i1 = 1; i1 <= 3; i1 = i1 + 1) FAIRE{
    DEBUT
    POUR (i2 = 1; i2 <= 3; i2 = i2 + 1) FAIRE{
        DEBUT
        POUR (i3 = 1; i3 <= 4; i3 = i3 + 1) FAIRE{
            DEBUT
            POUR (i4 = 1; i4 <= 4; i4 = i4 + 1) FAIRE{
                DEBUT
                varTata.x[i4, i3, i2, i1] = indice;
                indice = indice + 1;
                FIN
            };
            FIN
        };  
        FIN
    };        
    FIN
};
varTata.y = 1111111;

POUR (i1 = 1; i1 <= 3; i1 = i1 + 1) FAIRE{
    DEBUT
    POUR (i2 = 1; i2 <= 3; i2 = i2 + 1) FAIRE{
        DEBUT
        POUR (i3 = 1; i3 <= 4; i3 = i3 + 1) FAIRE{
            DEBUT
            POUR (i4 = 1; i4 <= 4; i4 = i4 + 1) FAIRE{
                DEBUT
                varComplicado.un.x[i4, i3, i2, i1] = indice;
                indice = indice + 1;
                FIN
            };
            FIN
        };  
        FIN
    };        
    FIN
};
varComplicado.un.y = 1111111;

POUR (i1 = 1; i1 <= 3; i1 = i1 + 1) FAIRE{
    DEBUT
    POUR (i2 = 1; i2 <= 3; i2 = i2 + 1) FAIRE{
        DEBUT
        POUR (i3 = 1; i3 <= 4; i3 = i3 + 1) FAIRE{
            DEBUT
            POUR (i4 = 1; i4 <= 4; i4 = i4 + 1) FAIRE{
                DEBUT
                varComplicado.deux[i4, i3, i2, i1] = indice;
                indice = indice + 1;
                FIN
            };
            FIN
        };  
        FIN
    };        
    FIN
};

un();

FIN

CPYRR
