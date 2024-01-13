CPYRR
/*L'accès a une case d'un tableau se fait en indiquant le numéro/l'indice de la case*/
/*ex : dimension : [-3,3] -> indices de 1 a 7*/

typedef int toto[1,4; 1,4];

typedef struct tata{
    toto x;
    int y;
};

toto var t;
char var c;
tata var varTata;
int var indice;

procedure un(){
    int var x;
    DEBUT
    x = 4 + t[4, 3];
    ecrire("t[4,3] = %d\n", t[4, 3]);
    ecrire("varTata.[4,6] = %d\n", varTata.x[4, 6]);
    ecrire("x = 4 + t[4,3] = %d\n",x);
    FIN
};

DEBUT
indice = 4;

t[1, 1] = 1;
t[2, 1] = 2;
t[3, 1] = 3;
t[4, 1] = 4;
t[1, 2] = 5;
t[2, 2] = 6;
t[3, 2] = 7;
t[4, 2] = 8;
t[1, 3] = 9;
t[2, 3] = 10;
t[3, 3] = 11;
t[4, 3] = 12;
t[1, 4] = 13;
t[2, 4] = 14;
t[3, 4] = 15;
t[4, 4] = 16;
t[indice, indice] = 1899;

c='z';
varTata.x[1, 1] = 17;
varTata.x[2, 1] = 18;
varTata.x[3, 1] = 19;
varTata.x[4, 1] = 20;
varTata.x[1, 2] = 21;
varTata.x[2, 2] = 22;
varTata.x[3, 2] = 23;
varTata.x[4, 2] = 24;
varTata.x[1, 3] = 25;
varTata.x[2, 3] = 26;
varTata.x[3, 3] = 27;
varTata.x[4, 3] = 28;
varTata.x[1, 4] = 29;
varTata.x[2, 4] = 30;
varTata.x[3, 4] = 31;
varTata.x[indice, 4] = 666;
varTata.y = 8;

ecrire("t[2, 3] = %d\n", t[2, 3]);
ecrire("varTata.x[1, 1] = %d\n", varTata.x[1, 1]);

un();

FIN

CPYRR
