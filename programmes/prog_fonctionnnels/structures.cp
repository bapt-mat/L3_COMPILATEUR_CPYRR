CPYRR
typedef struct toto{
    int x; 
    int y;
    int z;
};

typedef struct tata{
    int a;
    int b;
    toto c;
};

typedef struct titi{
    int un;
    toto deux;
    tata trois;
};

typedef struct superStructure{
    titi premiere;
    titi deuxieme;
};

toto var varToto;
tata var varTata;
titi var varTiti;
superStructure var superVariable;

procedure modifier(){
    DEBUT
    ecrire("Entrez une nouvelle valeur pour superVariable.deuxieme.trois.c.x (actuellement 33)\n");
    lire(superVariable.deuxieme.trois.c.x);
    ecrire("Nouvelle valeur de superVariable.deuxieme.trois.c.x : %d\n", superVariable.deuxieme.trois.c.x);
    FIN
};

procedure un(){
    procedure deux(){
        DEBUT
        ecrire("On va modifier quelques valeurs\n");
        modifier();
        FIN
    };
    DEBUT
    deux();
    FIN
};


DEBUT

varToto.x=1;
varToto.y=2;
varToto.z=3;

varTata.a=4;
varTata.b=5;
varTata.c.x = 6;
varTata.c.y = 7;
varTata.c.z = 8;

varTiti.un = 9;
varTiti.deux.x = 1 + varTiti.un;
varTiti.deux.y = varTiti.deux.x + varToto.x;
varTiti.deux.z = 12;
varTiti.trois.a = 13;
varTiti.trois.b = 14;
varTiti.trois.c.x = 15;
varTiti.trois.c.y = 16;
varTiti.trois.c.z = 17;

superVariable.premiere.un = 18;
superVariable.premiere.deux.x = 19;
superVariable.premiere.deux.y = 20;
superVariable.premiere.deux.z = 21;
superVariable.premiere.trois.a = 22;
superVariable.premiere.trois.b = 23;
superVariable.premiere.trois.c.x = 24;
superVariable.premiere.trois.c.y = 25;
superVariable.premiere.trois.c.z = 26;
superVariable.deuxieme.un = 27;
superVariable.deuxieme.deux.x = 28;
superVariable.deuxieme.deux.y = 29;
superVariable.deuxieme.deux.z = 30;
superVariable.deuxieme.trois.a = 31;
superVariable.deuxieme.trois.b = 32;
superVariable.deuxieme.trois.c.x = 33;
superVariable.deuxieme.trois.c.y = 34;
superVariable.deuxieme.trois.c.z = 35;

un();

FIN
CPYRR