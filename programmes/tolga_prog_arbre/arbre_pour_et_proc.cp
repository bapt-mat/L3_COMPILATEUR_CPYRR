CPYRR

typedef char chaine_caractere[1, 5];
chaine_caractere var texte;


procedure remplire_txt (){
int var i;
DEBUT
	POUR (i = 0 ; i < 5 ; i=i+1 ) FAIRE {
		DEBUT
			texte[i] = 'a';
		FIN
	};
FIN
};


DEBUT

remplire_txt();


FIN
CPYRR
