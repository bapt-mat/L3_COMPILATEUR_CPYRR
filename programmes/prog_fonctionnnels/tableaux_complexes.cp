CPYRR
int var x;
int var i;
int var j;
int var compteur;

typedef struct toto{
  int a;
  int b;
};

typedef struct tata {
  toto z;
  int y;
};

typedef tata tabTata[1,3; 1,4];

typedef char chaine[1,10];

tabTata var var_tab_tata;
float var tutu;
bool var tutuBool;
chaine var c;

DEBUT
compteur = 1;

POUR (i=1; i<=4; i=i+1) FAIRE{
  DEBUT
  POUR (j=1; j<=3; j=j+1) FAIRE{
    DEBUT
    var_tab_tata[j,i].z.a = compteur;
    compteur = compteur + 1;
    var_tab_tata[j,i].z.b = compteur;
    compteur = compteur + 1;
    var_tab_tata[j,i].y = compteur;
    compteur = compteur + 1;
    FIN
  };
  FIN
};

ecrire("\nSaisir une valeur pour un entier de la structure var_tab_tata[2,3].z.a (%d): \n", var_tab_tata[2,3].z.a);
lire(var_tab_tata[2,3].z.a);
ecrire("var_tab_tata[2,3].z.a = %d\n", var_tab_tata[2,3].z.a);


FIN

CPYRR