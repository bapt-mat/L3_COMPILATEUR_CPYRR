CPYRR

typedef struct date{
    int jour;
    int mois;
    int annee;
};

typedef struct personne{
    int numero;
    date naissance;
    int age;
};

typedef struct personne{ //warning déja déclaré
    int x;
};

typedef personne equipe[1,3; 1,2];

personne var p;

procedure personne(){
    DEBUT VIDE; FIN
};

equipe var te;
bool var b;
float var i;
int var j;

//int var teteAtoto;

char var personne; //pas de warning car pas même type

procedure a(){
    procedure b(int toto, char tata){
        int var T;
        procedure c(){
            DEBUT 
            superFonction();//warning non déclaré car déclaré dans une région non englobante
            FIN
        };
        
        procedure saisie(int x){
            int var i;

            fonction superFonction(int y12)ret int{
                DEBUT
                VIDE;
                FIN
            }; 

            DEBUT
            i=0;
            j=0;

            appeldelafonctionToto(x,y,j); //warning fct non déclaré + warning variable y non déclaré

            TANT QUE (i<3) FAIRE {
                DEBUT
                i=i+1;
                TANT QUE (j<2) FAIRE{
                    DEBUT
                    j=j+1;
                    teteAtoto=2; //warning var non déclaré
                    FIN
                };
                T=j;
                FIN
            };
            FIN
        };

        DEBUT
        saisie();
        FIN
    };
    DEBUT
    VIDE;
    FIN
};

procedure e(){
    procedure f(){
        procedure g(){
            DEBUT 
            a();
            FIN
        };
        DEBUT
        g();
        FIN
    };
    
    procedure h(){
        DEBUT
        f();
        FIN
    };

    DEBUT
    h();
    FIN
};

procedure i(){
    int var T;
    DEBUT
    e();
    T=j;
    FIN
};

procedure i(){//warning déja déclaré
    procedure i(){//ok car pas dans même région
        DEBUT
        VIDE;
        FIN
    };

    procedure i(){ //warning déja déclaré
        DEBUT
        VIDE;
        FIN
    };

    DEBUT
    VIDE;
    FIN
};

fonction turlututu() ret int{
    DEBUT
    VIDE;
    FIN
};

fonction turlututu() ret char{ //warning déja déclaré
    fonction turlututu() ret char{ //ok car pas la même région
        DEBUT
        VIDE;
        FIN
    };
    DEBUT
    VIDE;
    FIN
};

DEBUT
appelI();//warning non déclaré

tutu=0.242; //var non déclaré

FIN

CPYRR