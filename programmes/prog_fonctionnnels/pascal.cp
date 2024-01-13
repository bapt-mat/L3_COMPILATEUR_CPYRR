CPYRR
typedef int tableau[1, 200];

tableau var ligne_precedente;
tableau var ligne_actuelle;
int var nombre_lignes;

procedure afficher_ligne_tableau() {
    int var i;
    int var tmp;
    DEBUT
    POUR (i = 1; i <= nombre_lignes; i = i + 1) FAIRE {
        DEBUT
        SI (ligne_actuelle[i] == -1)ALORS {
            DEBUT
            VIDE;
            FIN
        } SINON {
            DEBUT
            ecrire("%d ", ligne_actuelle[i]);
            FIN
        };
        FIN
    };
    ecrire("\n");
    FIN
};

procedure triangle_pascal(int lignes) {
    int var i;
    int var j;

    DEBUT
    ecrire("Triangle de Pascal pour les %d premières lignes :\n", lignes);
    
    POUR (i = 1; i <= lignes; i = i + 1) FAIRE {
        DEBUT
        ligne_actuelle[1] = 1;
        ligne_actuelle[i] = 1;
        
        POUR (j = 1; j < i; j = j + 1) FAIRE {
            DEBUT
            ligne_actuelle[j] = ligne_precedente[j - 1] + ligne_precedente[j];
            FIN
        };
        
        afficher_ligne_tableau(ligne_actuelle);
        
        POUR (j = 1; j < i + 1; j = j + 1) FAIRE {
            DEBUT
            ligne_precedente[j] = ligne_actuelle[j];
            FIN
        };
        FIN
    };
    FIN
};

DEBUT
ecrire("Combien de lignes du triangle de Pascal voulez-vous afficher ? ");
lire(nombre_lignes);
triangle_pascal(nombre_lignes);
FIN
CPYRR
