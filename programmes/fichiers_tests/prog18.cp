CPYRR

typedef struct s{
    int ch1;
    int ch2;
    float ch3;
};

typedef s tableau[-5,5];

typedef struct toto{
    tableau machintruc; 
    s xoxo;
    int bidule;
};

procedure trucTest(){
    typedef struct bidulemachin{
        int tata;
    };
    DEBUT
    VIDE;
    FIN
};

bidulemachin var trucchouette; //doit provoquer un warning -> type déclaré dans une région non englobante de cette variable
tableau var t;
bool var y;
float var e;

typedef int tableauDeux[5,5]; //doit provoquer un warning -> bornes égales

typedef char tableauTrois[10,15; 5,-2]; //doit provoquer une erreur -> borne sup > borne inf


fonction fff (float i) ret int{
    
    DEBUT
    VIDE;
    FIN
};

procedure p99 (int a, float y){
    DEBUT
    VIDE;
    FIN
};

procedure p27 (int x, int y, bool s){
    float var a;

    typedef struct teteAToto{
        int x;
    };

    procedure p12 (float x){
        int var i;
        s var s1;
        float var s2;

        typedef superToto tabSuperToto[-10,10; 5,15; -15, 25]; //warning car type superToto inexistant

        procedure p42(char toto){
            teteAToto var titi; //pas d'erreur car declaré dans une région englobante
            DEBUT
            VIDE;
            FIN
        };
        
        DEBUT
        i=1;
        //switch a faire (dans le yacc)
        t[y].ch1 = 1;
        FIN
    };
};

CPYRR