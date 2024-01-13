CPYRR

typedef char chaine[1, 20];

chaine var prenom;
chaine var hello;
char var tmp;
char var fin;
int var i;
int var j;

procedure ecrire_hello(){
    int var indice;
    DEBUT
    hello[1] = 'H';
    hello[2] = 'e';
    hello[3] = 'l';
    hello[4] = 'l';
    hello[5] = 'o';

    ecrire("\n");

    POUR (j=1; j<=5; j=j+1) FAIRE {
        DEBUT 
        indice = j;
        ecrire("%c", hello[indice]);
        FIN
    };
    FIN
};

DEBUT
i=1;
fin = '/';

ecrire("Quel est votre prenom ? (Entrez * pour indiquer la fin (20 lettres max))\n");

FAIRE{
    DEBUT
    lire(tmp);
    SI (tmp == '*') ALORS{
        DEBUT
        fin = tmp;
        FIN
    }SINON{
        DEBUT 
        prenom[i] = tmp;
        i = i + 1;

        SI (i == 20) ALORS{
            DEBUT
            fin = '*';
            FIN
        };
        FIN
    };
    FIN
}TANT QUE (NON(fin == '*'));

ecrire_hello();

ecrire(" World !\nHello ");

POUR (j=1; j<=i; j=j+1) FAIRE{
    DEBUT
    ecrire("%c",prenom[j]);
    FIN
};

ecrire(" !\n");

FIN

CPYRR
