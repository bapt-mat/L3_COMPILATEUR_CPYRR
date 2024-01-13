CPYRR
char var type_calcul;
char var operateur;

typedef struct calculatrice{
    int entier;
    float reel;
};

typedef calculatrice tab_operation[1,3];

tab_operation var calcul;

bool var calculatrice;

procedure calculatrice(){
    DEBUT
    TANT QUE (calculatrice == 1) FAIRE {
        DEBUT
        ecrire("Sur quel ensemble voulez-vous faire vos calculs ? (E pour entier, F pour flottant) : ");
        lire(type_calcul);

        ecrire("Quel type d'opération voulez-vous faire ? (+, -, *, /) : ");
        lire(operateur);

        SI (type_calcul == 'E') ALORS{
            DEBUT
            ecrire("Entrez le premier entier : ");
            lire(calcul[1].entier);
            ecrire("Entrez le deuxième entier : ");
            lire(calcul[2].entier);

            SI (operateur == '+') ALORS{
                DEBUT
                calcul[3].entier = calcul[1].entier + calcul[2].entier;
                FIN
            };
            SI (operateur == '-') ALORS{
                DEBUT
                calcul[3].entier = calcul[1].entier - calcul[2].entier;
                FIN
            };
            SI (operateur == '*') ALORS{
                DEBUT
                calcul[3].entier = calcul[1].entier * calcul[2].entier;
                FIN
            };
            SI (operateur == '/') ALORS{
                DEBUT
                calcul[3].entier = calcul[1].entier / calcul[2].entier;
                FIN
            };
            ecrire("Resultat : %d\n", calcul[3].entier);
            FIN
        }SINON{
            DEBUT
            ecrire("Entrez le premier flottant : ");
            lire(calcul[1].reel);
            ecrire("Entrez le deuxième flottant : ");
            lire(calcul[2].reel);
            SI (operateur == '+') ALORS{
                DEBUT
                calcul[3].reel = calcul[1].reel + calcul[2].reel;
                FIN
            };
            SI (operateur == '-') ALORS{
                DEBUT
                calcul[3].reel = calcul[1].reel - calcul[2].reel;
                FIN
            };
            SI (operateur == '*') ALORS{
                DEBUT
                calcul[3].reel = calcul[1].reel * calcul[2].reel;
                FIN
            };
            SI (operateur == '/') ALORS{
                DEBUT
                calcul[3].reel = calcul[1].reel / calcul[2].reel;
                FIN
            };
            ecrire("Resultat : %f\n", calcul[3].reel);
            FIN
        };
        ecrire("Voulez-vous refaire un calcul ? ");
        lire(calculatrice);
        FIN
    };
    FIN
};

DEBUT
calculatrice = TRUE;

calculatrice();
FIN

CPYRR