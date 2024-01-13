CPYRR

int var x;

typedef char tabDeChar[-5,4;5,9;-10,9];

typedef struct declarType{
    typeperso x;
    typeperso2 y;
};

fonction testfonction(int x) ret int{
    typedef char tabDeChar[-5,4;5,9;-10,9];

    typedef struct declarType{
        typeperso x;
        typeperso2 y;
    };

    int var x;

    DEBUT

    VariableTestEntiere = 3;
    VariableTestChar = 'Z';
    VariableTestFloat = 1298.031531511210053;
    VariableTestBool = FALSE;
    VariableTestBool = TRUE;
    VariableTestVariable = vartest;
    
    FIN
};

procedure testProcedure(int x, char toto, float testFloat, bool testBool){
    typedef char tabDeChar[-5,4;5,9;-10,9];

    typedef struct declarType{
        typeperso x;
        typeperso2 y;
    };

    int var x;

    DEBUT

    VariableTestEntiere = 3;
    VariableTestChar = 'Z';
    VariableTestFloat = 1298.031531511210053;
    VariableTestBool = FALSE;
    VariableTestBool = TRUE;
    VariableTestVariable = vartest;
    
    FIN
};


DEBUT 

VariableTestEntiere = 3;
VariableTestChar = 'Z';
VariableTestFloat = 1298.031531511210053;
VariableTestBool = FALSE;
VariableTestBool = TRUE;
VariableTestVariable = vartest;

SI (x == y) ALORS{
    DEBUT
    x=6;
    VariableTestChar = 'Z';
    VariableTestFloat = 1298.031531511210053;
    FIN
}
SINON{
    DEBUT 
    x=4;
    SI (varToto < varTata) ALORS{
        DEBUT
        x42x = 5;
        FIN
    }
    SINON{
        DEBUT
        ytoto = 10;
        FIN
    };
    FIN
};

SI ((a==b ET x>c) OU (NON z>=x OU TRUE)) ALORS{
    DEBUT
    SI ((a==x OU (a<=z ET z>=a) OU NON a>x) OU TRUE) ALORS{
        DEBUT ; FIN
    };
    FIN
}
SINON{
    DEBUT a=c;FIN
};

FIN

CPYRR