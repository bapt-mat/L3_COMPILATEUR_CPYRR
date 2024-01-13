CPYRR

typedef char chaine_caractere[1, 5];
chaine_caractere var texte;
char var le_carac;
char var le_nx_carac;
int var i;

fonction remplire_txt (char x,int i) ret char{
DEBUT
	POUR (i = 0 ; i < 5 ; i=i+1 ) FAIRE {
		DEBUT
			texte[i] = x;
		FIN
	};
	ret texte[2];
FIN
};


DEBUT
i=0;
le_carac = 'z';
le_nx_carac = remplire_txt(le_carac,i);


FIN
CPYRR
