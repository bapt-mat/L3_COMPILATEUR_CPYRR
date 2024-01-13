CPYRR
int var x;
int var y;
int var z;
bool var continue;

procedure affiche_y(int val_de_x){
    fonction affecte_y(int val) ret int{
        DEBUT
        SI (val == 29) ALORS{
            DEBUT
            ecrire("x = 29 -> continue devient FALSE\n");
            continue = FALSE;
            FIN
        };
        ret val;
        FIN
    };
    DEBUT
    y = affecte_y(val_de_x);
    ecrire("y = %d\n", y);
    FIN
};

DEBUT
y=0;
z=0;
continue = TRUE;

POUR (x=0; x<10; x=x+1) FAIRE{
    DEBUT
    TANT QUE (z<10) FAIRE{
        DEBUT
        ecrire("boucle sur z = %d\n", z);
        z=z+1;
        FIN
    };
    affiche_y(x);
    z=0;
    FIN
};

TANT QUE (x<20) FAIRE{
    DEBUT
    affiche_y(x);
    x=x+1;
    FIN
};

FAIRE {
    DEBUT
    affiche_y(x);
    x=x+1;
    FIN
} TANT QUE (continue == TRUE);

FIN
CPYRR