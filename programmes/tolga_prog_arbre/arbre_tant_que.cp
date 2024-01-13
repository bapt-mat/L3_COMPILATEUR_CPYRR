CPYRR

typedef char chaine_caractere[1, 5];
chaine_caractere var texte;


procedure remplire_txt (){
int var i;
DEBUT
i=0;
	TANT QUE( NON (i==5) ) FAIRE {
		DEBUT
			texte[i] = 'a';
			i = i+1;
		FIN
	};
FIN
};






DEBUT

remplire_txt();


FIN
CPYRR
