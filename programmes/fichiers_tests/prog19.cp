CPYRR

int var toto; 

char var toto; //doit provoquer un warning -> variable déja déclaré 

typedef struct x{
    int toto;
    char tata;
    bool teteAToto;
};

typedef struct x{ //doit provoquer un warning -> type déja déclaré
    char tata;
};


procedure toto(){
    bool var toto; //pas de warning car changement de région

    typedef struct x{ 
        x superVariable; //utilise donc le premier typedef x (ligne 7)
        x deuxiemeSuperVariable;    //idem
    };

    typedef x tabDeX[-5,10]; //utilise le typedef x de la ligne 26

    typedef x tabDeX[10,15]; //warning tableau déja déclaré;

    typedef struct y{
        bool teteAToto;
    };

    typedef struct y{ //doit provoquer un warning -> type déja déclaré
        int titi;
    };

    procedure machinBidule(int x){
        DEBUT
        VIDE;
        FIN
    };

    DEBUT
    VIDE;
    FIN
};

fonction biduleTruc() ret int{
    DEBUT
    VIDE;
    FIN
};

DEBUT
biduleTruc();
machinBidule(); //warning -> déclaré dans une région non englobante (dans procedure toto)
FIN

CPYRR