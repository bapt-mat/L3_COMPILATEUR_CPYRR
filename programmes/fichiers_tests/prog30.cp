CPYRR 

int var i;
float var j;
int var k;
float var l;
int var test;
float var ftest;

fonction f() ret int {
    int var x;
    DEBUT
    x=1;
    ret x;
    FIN
};

fonction g() ret float {
    float var y;
    DEBUT 
    y= 1.0;
    ret y;
    FIN
};

DEBUT
i=2;
j=2.0;
j = j / 0.0;
j = i / 1;
j = f() / (1.0);
j = 1.0 / f();

FIN

CPYRR