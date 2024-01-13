%{
     #include "./Arbre/arbre.c" 
    #include "y.tab.h" 
    #include "./Erreurs/erreurs.h"

    int numero_ligne=1;
    int numero_car=0;

    tab_lexico table;
    int tab_hashcode[32];
    int premiere_pos_libre = 0;
    char test[20];
    int code_erreur=0;
%}

%%

CPYRR                               {/*MOTS-CLES*/numero_car+=yyleng; return CPYRR;}
DEBUT                               {numero_car+=yyleng; return DEBUT;}
FIN                                 {numero_car+=yyleng; return FIN;}
var                                 {numero_car+=yyleng; return DECLAR_VARIABLE;}
typedef                             {numero_car+=yyleng; return DECLAR_TYPE;}

int                                 {numero_car+=yyleng; return TYPE_INT;}
float                               {numero_car+=yyleng; return TYPE_FLOAT;}
bool                                {numero_car+=yyleng; return TYPE_BOOLEAN;}
char                                {numero_car+=yyleng; return TYPE_CHAR;}

struct                              {numero_car+=yyleng; return STRUCT;}
fonction                            {numero_car+=yyleng; return FONCTION;}
procedure                           {numero_car+=yyleng; return PROCEDURE;}
ret                                 {numero_car+=yyleng; return RETOURNE;}
VIDE                                {numero_car+=yyleng; return VIDE;}

SI                                  {numero_car+=yyleng; return SI;}
ALORS                               {numero_car+=yyleng; return ALORS;}
SINON                               {numero_car+=yyleng; return SINON;}
"TANT QUE"                          {numero_car+=yyleng; return TANT_QUE;}
FAIRE                               {numero_car+=yyleng; return FAIRE;}
POUR                                {numero_car+=yyleng; return POUR;}

ecrire                              {numero_car+=yyleng; return ECRIRE;}
lire                                {numero_car+=yyleng; return LIRE;}
randint                             {numero_car+=yyleng; return RANDINT;}

ET                                  {numero_car+=yyleng; return ET;}
OU                                  {numero_car+=yyleng; return OU;}
NON                                 {numero_car+=yyleng; return NON;}

\;                                  {numero_car+=yyleng; return POINT_VIRGULE;}
,                                   {numero_car+=yyleng; return VIRGULE;}
\.                                  {numero_car+=yyleng; return POINT;}
\(                                  {numero_car+=yyleng; return PARENTHESE_OUVRANTE;}
\)                                  {numero_car+=yyleng; return PARENTHESE_FERMANTE;}
\[                                  {numero_car+=yyleng; return CROCHET_OUVRANT;}
\]                                  {numero_car+=yyleng; return CROCHET_FERMANT;}
\{                                  {numero_car+=yyleng; return ACCOLADE_OUVRANTE;}
\}                                  {numero_car+=yyleng; return ACCOLADE_FERMANTE;}


\+                                  {/*OPERATEURS ARITHMETIQUES*/numero_car+=yyleng; return PLUS;}
\-                                  {numero_car+=yyleng; return MOINS;}
\*                                  {numero_car+=yyleng; return MULT;} 
\/                                  {numero_car+=yyleng; return DIV;}
\<=                                 {numero_car+=yyleng; return INFERIEUR_EGAL;}
>=                                  {numero_car+=yyleng; return SUPERIEUR_EGAL;}
\<                                  {numero_car+=yyleng; return INFERIEUR;}
>                                   {numero_car+=yyleng; return SUPERIEUR;}
==                                  {numero_car+=yyleng; return DOUBLEEGAL;}
=                                   {numero_car+=yyleng; return OPAFF;}
         
TRUE|FALSE                          {if (strcmp(yytext, "TRUE") == 0){yylval.ival = 1;}else{yylval.ival=0;}; numero_car+=yyleng; return CSTE_BOOLEAN;}
'[a-zA-Z\/\-\*\+]'            {yylval.ival=inserer_lexeme(yytext); numero_car+=yyleng; return CSTE_CHAR;}
\"[^"]*\"                           {yylval.ival=inserer_lexeme(yytext); numero_car+=yyleng; return CSTE_CHAINE;}

-?(0|[1-9][0-9]*)\.[0-9]+             {yylval.ival=inserer_lexeme(yytext); numero_car+=yyleng; return CSTE_FLOAT;}  
-?[0-9][0-9]*                         {yylval.ival=atoi(yytext); numero_car+=yyleng; return CSTE_INTEGER;}              

[a-zA-Z][a-zA-Z0-9_]*               {yylval.ival=inserer_lexeme(yytext); numero_car+=yyleng; return IDF;}

\/\/.*\n                            {numero_car+=yyleng;}
\/\*(.^*|\n)*\*\/                   {numero_car+=yyleng;}

[ ]                                 {numero_car+=yyleng;}
\n                                  {numero_ligne++; numero_car=0;}


%%

int yyerror(){
    switch(code_erreur){ //voir erreurs.h
        case code_erreur_declaration_var: 
            printf("\nERREUR de déclaration variable à la ligne %d et caractère %d\n", numero_ligne, numero_car);
            break;
        case code_erreur_parenthese_ouvrante:
            printf("\nERREUR de parenthésage (pas de parenthèse ouvrante) à la ligne %d et caractère %d\n", numero_ligne, numero_car);
            break;
        case code_erreur_parenthese_fermante:
            printf("\nERREUR de parenthésage (pas de parenthèse fermante) à la ligne %d et caractère %d\n", numero_ligne, numero_car);
            break;
        default:
            printf("\nERREUR de syntaxe à la ligne %d et caractère %d\n", numero_ligne, numero_car);
            break;
    }
}