CPYRR

typedef struct t1{
    int ch1;
    float ch2;
};

typedef t1 t2[1,5];

typedef struct t3{
    t2 ch1t3;
    float ch2t3;
};

float var y;
t2 var tab1;
int var x;

procedure il(){
    int var z;

    procedure davoir(){
        int var y;
        
        procedure compilation(){
            t3 var v3;
            DEBUT
            y=x;
            v3.ch1t3[4].ch1 = tab1[5].ch1;
            FIN
        };

        procedure le(){

            procedure module(){
                DEBUT compilation(); FIN
            };

            DEBUT module(); FIN
        };

        DEBUT le(); FIN
    };

    procedure est(){
        
        procedure possible(){
            int var x;
            DEBUT
            davoir(); x=z;
            FIN
        };

        procedure toujours(){
            DEBUT possible(); FIN
        };

        DEBUT toujours(); FIN
    };

    DEBUT est(); FIN
};

procedure en(int x){
    
    procedure revisant(){

        procedure peu(){
            DEBUT il(); FIN
        };

        procedure un(){
            t2 var v2;
            DEBUT
            v2[4].ch1 = 3;
            peu();
            FIN
        };

        DEBUT un(); FIN
    };

    DEBUT revisant(); FIN
};

DEBUT
tab1[5].ch1 = 99;
y = 3.14;
en(4);
FIN

CPYRR