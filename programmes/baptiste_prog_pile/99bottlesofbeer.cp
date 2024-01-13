CPYRR
int var bieres;

procedure zero_bieres(){
    DEBUT
    ecrire("Il n'y a plus de bouteilles de bières sur le mur.\n");
    FIN
};

procedure une_biere(){
    DEBUT
    ecrire("Il n'y a plus de bouteilles de bières sur le mur.\n");
    FIN
};

procedure plusieurs_bieres(int nb){
    DEBUT
    ecrire("Il y a %d bouteilles de bières sur le mur.\n", nb);
    FIN
};

procedure main(){
    DEBUT
    ecrire("Combien de bouteilles voulez-vous sur le mur ?\n");
    lire(bieres);
    POUR (bieres=bieres; bieres>0; bieres = bieres-(1)) FAIRE{
        DEBUT
        SI (bieres==0) ALORS{
            DEBUT
            zero_bieres();
            FIN
        }SINON{
            DEBUT
            SI (bieres==1)ALORS{
                DEBUT
                une_biere();
                FIN
            }
            SINON {
                DEBUT
                plusieurs_bieres(bieres);
                FIN
            };
            FIN
        };

        FIN
    };
    FIN
};

DEBUT

main();

FIN

CPYRR
