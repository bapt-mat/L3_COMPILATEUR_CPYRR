CPYRR

float var toto;
int var tata;

procedure un(){
    int var x;
    DEBUT
    x=8888;
    FIN
};

procedure deux(){
    int var x;
    DEBUT
    x=9999;
    FIN
};

procedure tatata(){
    int var x;
    
    procedure teteAToto(){
        int var z;
        procedure fctA(){
            float var y;
            int var xy;
            DEBUT
            y=toto+4.5;
            xy = 4;
            tata=xy+xy+xy;
            FIN
        };

        DEBUT
        z=tata+4;
        fctA();
        FIN
    };

    DEBUT
    x=1234;
    teteAToto();
    FIN
};

procedure tolga(){
    int var x;
    int var y;
    DEBUT
    x=4321;
    tatata();
    y=9;
    un();
    deux();
    FIN
};

fonction zazou() ret int{
    int var a;
    int var c;
    DEBUT
    a = 1;
    c = 3;
    tolga();
    FIN
};


DEBUT

toto=100.5;
toto = toto+2.5;
tata=2;
//ecrire("Salut a tous !");
zazou();

FIN

CPYRR