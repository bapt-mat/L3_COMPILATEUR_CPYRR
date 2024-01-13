CPYRR
bool var x;
bool var y;
bool var xy;
bool var z;
int var un;
int var deux;
int var trois;
char var caractere;

fonction premiere(int a) ret int{
    int var res;
    procedure deuxieme() {
        DEBUT
        z = TRUE;
        FIN
    };

    DEBUT
    res = un + a; 
    deuxieme();
    ret res;
    FIN
};

fonction troisieme(int a) ret int{
    procedure quatrieme(){
        DEBUT
        trois = a;
        ecrire("\ndans proc quatrieme -> trois = %d\n", trois);
        FIN
    };
    DEBUT
    z = FALSE;
    trois = 0;
    quatrieme();
    ret (trois-(3));
    FIN
};

DEBUT
x=FALSE;
y=TRUE;
xy=FALSE;
un = 1; 
deux = 2;
caractere = 'a';

SI (x OU (y ET xy)) ALORS{
    DEBUT
    trois = premiere(deux);
    ecrire("\nfin -> trois = %d\n", trois);
    FIN
}SINON{
    DEBUT
    trois = troisieme(11);
    ecrire("\nfin -> trois = %d\n", trois);
    FIN
};

SI ((un <= trois) ET ((deux-(2) >= 2) OU x) OU (caractere == 'a')) ALORS{
    DEBUT
    ecrire("\nOn est dans la condition !\n");
    FIN
}SINON{
    DEBUT
    ecrire("\nOn n'est pas dans la condition !\n");
    FIN
};


FIN

CPYRR