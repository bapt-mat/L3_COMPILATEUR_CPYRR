CPYRR
typedef int tab[1,500];
int var taille;
tab var tableau;
int var somme;
bool var trouver;
int var element_recherche;
bool var trierTab;

procedure remplir_tableau(int t) {
    int var i;
    int var j;
    DEBUT
    j=1;
    POUR (i = t; i > 0; i = i - 1) FAIRE {
        DEBUT
        tableau[j] = randint(0, 1000); 
        j=j+1;
        FIN
    };
    FIN
};

procedure afficher_tableau(int t) {
    int var i;
    int var tmp;
    DEBUT
    ecrire("\nContenu du tableau : \n");
    POUR (i = 1; i <= t; i = i + 1) FAIRE {
        DEBUT
        ecrire("%d |", tableau[i]);
        FIN
    };
    ecrire("\n");
    FIN
};

fonction somme_tableau(int t) ret int {
    int var i;
    int var somme;
    DEBUT
    somme = 0;
    POUR (i = 1; i <= t; i = i + 1) FAIRE {
        DEBUT
        somme = somme + tableau[i];
        FIN
    };
    ret somme;
    FIN
};

procedure trier_tableau(int t) {
    int var i;
    int var j;
    int var temp;
    int var temp2;
    DEBUT
    POUR (i = 1; i <= t; i = i + 1) FAIRE {
        DEBUT
        POUR (j = 1; j <= t; j = j + 1) FAIRE {
            DEBUT
            SI (tableau[i] < tableau[j]) ALORS {
                DEBUT
                temp = tableau[i];
                temp2 = tableau[j];
                tableau[i] = temp2;
                tableau[j] = temp;
                FIN
            };
            FIN
        };
        FIN
    };
    FIN
};

fonction rechercher(int element, int t) ret bool {
    int var i;
    int var tmp;
    bool var res;
    DEBUT
    res = FALSE;
    POUR (i = 1; i <= t; i = i + 1) FAIRE {
        DEBUT
        tmp = tableau[i];
        SI (tmp == element) ALORS {
            DEBUT
            res = TRUE;
            FIN
        };
        FIN
    };
    ret res;
    FIN
};

procedure main() {
    DEBUT
    taille = 0;

    ecrire("Remplissage d'un tableau d'entiers aléatoires et recherche d'un élément.\n\n");

    TANT QUE ((taille == 0) OU (taille > 500))FAIRE{
        DEBUT
        ecrire("Combien d'éléments voulez-vous dans le tableau ? (500 max)\n");
        lire(taille);
        FIN
    };

    remplir_tableau(taille);
    afficher_tableau(taille);
    somme = somme_tableau(taille);
    ecrire("\nSomme des éléments du tableau : %d\n", somme);
    
    ecrire("Souhaitez-vous trier le tableau ?");
    lire(trierTab);
    SI (trierTab == TRUE) ALORS {
        DEBUT
        trier_tableau(taille);
        ecrire("\nTableau trié : ");
        afficher_tableau(taille);        
        FIN
    };
    
    ecrire("Quel élément voulez-vous rechercher dans le tableau ?\n");
    lire(element_recherche);

    trouver = rechercher(element_recherche, taille);

    SI (trouver == TRUE) ALORS {
        DEBUT
        ecrire("L'élément %d est présent dans le tableau.\n", element_recherche);
        FIN
    } SINON {
        DEBUT
        ecrire("L'élément %d n'est pas présent dans le tableau.\n", element_recherche);
        FIN
    };
    FIN
};

DEBUT
main();
FIN
CPYRR

