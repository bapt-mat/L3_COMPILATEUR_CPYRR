CPYRR
int var pre_ou;
int var deux_ou;

int var pre_et;
int var deu_et;
int var x;


DEBUT
	x=randint(0,10);
	pre_ou=100;
	deux_ou=200;
	
	pre_et = 300;
	deu_et = 400;
	
	
	SI ( (pre_ou == 100) OU (deux_ou == 300)) ALORS {
	DEBUT
		ecrire("on rentre dans le si du OU\n");
		SI ((pre_et == 300) ET (deu_et == 400)) ALORS {
			DEBUT
				ecrire("on rentre dans le si du ET\n");
			FIN
			};
	FIN
	};
FIN
CPYRR
