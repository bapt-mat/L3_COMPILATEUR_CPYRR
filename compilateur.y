%{
    /**
     * @file compilateur.y
     * @author MATHEVON Baptiste ASSAL Yasser YILDIZ Tolga GUNES Ozan 
     * @brief TAD implémentation de la table des déclarations
     * @date 19-10-2023
    */

    /*-- NOTES --
    - pb affichage ligne dans les warnings (piste -> peut etre due aux coms)
    - TODO faire des programmes CPYRR montrant les erreurs/warnings et des progs qui marchent (calculatrice)
    */

    #include "./PileExecution/pile_execution.c"
    #include "./TAD_historique_region/historique.c"
    #include "./Erreurs/erreurs.c"

    #include <stdlib.h>
    #include <time.h>

    extern int code_erreur;

    int yylex();
    int yyerror();

    /*----------------------------------------*
    |                                         |
    | ~~~ DECLARATIONS DES VARIABLES ~~~
    |                                         |
    *-----------------------------------------*/

    /*----------------------------------------*
    | Pour pouvoir utiliser stdin on va modifier yyin (lex lit par défaut dans stdin)
    *-----------------------------------------*/
    extern FILE * yyin;

    /*----------------------------------------*
    | Compte le nombre de warnings 
    *-----------------------------------------*/
    int nb_warnings = 0;

    /*----------------------------------------*
    | TABLE LEXICOGRAPHIQUE
    *-----------------------------------------*/
    extern tab_lexico table;
    extern int tab_hashcode[32];
    extern int premiere_pos_libre;
    extern char test[20];
    
    /*----------------------------------------*
    | TABLE DES DÉCLARATIONS
    *-----------------------------------------*/
    int premiere_pos_zone_de_debordement=500;
    tab_declaration table_declaration;

    int premiere_pos_table_types=0;
    tab_types table_types;

    /*----------------------------------------*
    | Pour le champ exec de la table des déclarations
    *-----------------------------------------*/
    int exec_type_struct=0;
    int exec_type_tableau=1;
    int exec_variable=0;

    /*----------------------------------------*
    | PILE DES RÉGIONS
    *-----------------------------------------*/
    pile_region pile_des_regions;
    int numero_region=0;

    /*----------------------------------------*
    | TABLE DES RÉGIONS
    *-----------------------------------------*/
    tab_regions table_regions;
    int taille_regions = 0;
    historique_region historique_reg;

    /*----------------------------------------*
    | TABLES DES TYPES ET DES ENTÊTES
    *-----------------------------------------*/
    char type_actuel[500];
    /*----------------------------------------*
    | Pour le type structure
    *-----------------------------------------*/
    int pos_nb_champs=0;
    int num_lex_champ=0;
    int depl_champ=0;
    /*----------------------------------------*
    | Pour le type tableau
    *-----------------------------------------*/
    int pos_debut_desc_tab=0;
    int pos_nb_dimensions=0;
    /*----------------------------------------*
    | Pour les fonctions et les procédures
    *-----------------------------------------*/
    int pos_debut_fct=0;
    int type_res_fct=0;
    int pos_nb_param=0;
    int num_lex_param=0;
    int type_param=0;

    /*----------------------------------------*
    | ARBRES
    *-----------------------------------------*/
    int i_arbre = 0;
    arbre tab_arbre[MAX_REGIONS];
    int num_declaration_struct = 0;
    int num_declaration_tab = 0;
    int bool_struct_tab=0;
    int type_champ_tmp = 0;
    int type_champ_final = 0;
    int bool_var_simple = 0;

    /*----------------------------------------*
    | PILE A L'EXECUTION 
    *-----------------------------------------*/
    pile_execution pile;
    int BC=0;
    /*Pour le chainage statique et dynamique lors d'appels de fonctions/procédures*/
    int * tab_chainage_statique;
    int indice_tab_chainage_statique=0;
    int indice_affichage_pile=0;
    int indice_BC_dispo=0;

    /*Pour la liste des arguments d'une fonction/procedure*/
    int num_description_tmp=0;
    int num_argument_courant=0;
    int num_region_appelante_liste_arguments=0;

    /*Pour 'ecrire'*/
    union cellule_pile * tab_arguments_ecrire;
    int indice_tab_arguments_ecrire=0;

    /*Pour les structures et l'accés aux champs de ces dernieres*/
    int indice_description_tmp=0;
    int indice_champ_tmp=0;

    /*Pour les tableaux et l'accés aux indices de ces derniers*/
    int indice_tableau_tmp=0;
    int taille_dimension_tmp=0;
    int * tab_taille_dimensions;
    int indice_tab_taille_dimensions;
    int taille_case_tab=0;
%}

%union{
    char * sval;
    int ival;
    float fval;
    arbre arbre;
}

/*----------------------------------------*
|                                         |
| ~~~ TOKENS ~~~ 
|                                         |
*-----------------------------------------*/

/*----------------------------------------*
| Mots clés
*-----------------------------------------*/
%token CPYRR DEBUT FIN
%token STRUCT
%token FONCTION RETOURNE
%token PROCEDURE
%token VIDE
%token DECLAR_VARIABLE DECLAR_TYPE
%token <ival> IDF  

/*----------------------------------------*
| Types
*-----------------------------------------*/
%token <ival> CSTE_INTEGER 
%token <ival> CSTE_FLOAT 
%token <ival> CSTE_BOOLEAN 
%token <ival> CSTE_CHAR CSTE_CHAINE
%token <ival> TYPE_INT TYPE_FLOAT TYPE_BOOLEAN TYPE_CHAR 

/*----------------------------------------*
| Symboles
*-----------------------------------------*/
%token POINT_VIRGULE VIRGULE POINT
%token PARENTHESE_OUVRANTE PARENTHESE_FERMANTE
%token CROCHET_OUVRANT CROCHET_FERMANT
%token ACCOLADE_OUVRANTE ACCOLADE_FERMANTE

/*----------------------------------------*
| Instructions de base CPYRR
*-----------------------------------------*/
%token ECRIRE LIRE RANDINT

/*----------------------------------------*
| Conditions
*-----------------------------------------*/
%token SI ALORS SINON
%token TANT_QUE FAIRE
%token POUR

/*----------------------------------------*
| Expressions booleennes
*-----------------------------------------*/
%token ET OU NON

/*----------------------------------------*
| Expressions arithmétiques
*-----------------------------------------*/
%token PLUS MOINS MULT DIV OPAFF 
%token DOUBLEEGAL INFERIEUR SUPERIEUR INFERIEUR_EGAL SUPERIEUR_EGAL
 
/*----------------------------------------*
|                                         |
| ~~~ TYPES DES SYMBOLES ~~~ 
|                                         |
*-----------------------------------------*/
%type <ival> nom_type type_simple
%type <ival> dimension liste_dimension
%type <ival> champ

%type <arbre> constante_integer constante_float
%type <arbre> exp_arith exp_arith_mult_div expression_arithmetique 
%type <arbre> base_var variable

%type <arbre> comparateur expression_booleenne_compare expression_booleenne expression_booleenne_non expression_booleenne_et expression_booleenne_ou exp_bool
%type <arbre> expression liste_indices_bis liste_indices liste_champs_var 
%type <arbre> affectation pour

%type <arbre> liste_instructions
%type <arbre> faire_tant_que tant_que condition condition_unique

%type <arbre> arguments liste_arguments appel resultat_retourne

%type <arbre> lire liste_expression_ecrire suite_ecrire_lire ecrire liste_expression_lire

%type <arbre> instruction corps_liste_instructions corps

%type <arbre> randint

%%

/*----------------------------------------*
|                                         |
| ~~~ CORPS DU PROGRAMME ~~~
|                                         |
*-----------------------------------------*/
programme_c_pyrr : CPYRR corps CPYRR {ajouterRegion(taille_regions+nis_region(numero_region)+(numero_region-1 != 0 ? 1 : 0), nis_region(numero_region), NULL);}
                ;
    
corps : liste_declarations liste_instructions {$$=$2; tab_arbre[sommet_pile_region()]=$$;}
            |liste_instructions {$$=$1; tab_arbre[sommet_pile_region()]=$$;}
            ;

liste_declarations : declaration POINT_VIRGULE  
                |liste_declarations declaration POINT_VIRGULE
                ;

liste_instructions :DEBUT corps_liste_instructions FIN {$$=$2;}
                | {$$=arbre_vide();}
                ;

corps_liste_instructions : instruction POINT_VIRGULE {$$=creer_noeud(T_LISTE, -1, -1); ajouter_fils($$, $1);}
                |instruction POINT_VIRGULE corps_liste_instructions 
                {$$=creer_noeud(T_LISTE, -1, -1); ajouter_frere($1, $3); ajouter_fils($$, $1);}
                ;

declaration : declaration_type {exec_type_struct = 0; exec_type_tableau = 1;  //on reinitialise la taille d'un type struct/tableau(pour le calcul de la taille d'une autre struct/d'un autre tableau si il y a)
                                pos_nb_champs = 0; depl_champ=0;} //reinitialisation pour la table des types
                |declaration_variable 
                |declaration_fonction  {pos_nb_param=0; pos_debut_fct=0; type_res_fct=0; type_param=0;} //inutile ?
                |declaration_procedure  {pos_nb_param=0; pos_debut_fct=0; type_res_fct=0; type_param=0;}
                ;

/*----------------------------------------*
|                                         |
| ~~~ DECLARATION TYPES (ET TABLEAU) ~~~
|                                         |
*-----------------------------------------*/
declaration_type : DECLAR_TYPE STRUCT IDF corps_declaration_type {inserer_declaration($3, TYPE_S, sommet_pile_region(), pos_nb_champs, exec_type_struct);} 
                //la taille d'une structure est la somme de la taille de chacun de ses champs  
                |DECLAR_TYPE nom_type IDF tableau {exec_type_tableau=exec_type_tableau*$2; inserer_declaration($3, TYPE_T, sommet_pile_region(), pos_debut_desc_tab, exec_type_tableau);} 
                //la taille du type tableau est égale au nombres de cases (stocké dans exec_type_tableau) multiplié par la taille de chacune des cases (stocké dans le nom_type)
                ;       

corps_declaration_type : ACCOLADE_OUVRANTE {pos_nb_champs=premiere_pos_table_types; premiere_pos_table_types+=1;} 
                liste_champs ACCOLADE_FERMANTE 
                //pos_nb_champs récupère l'index dans la table des types contenant le nombre de champs de la struct actuelle 
                ;       
                                    
liste_champs : champ POINT_VIRGULE {incr_index_table_types(pos_nb_champs); //faire un truc plus condensé ?
                    inserer_table_types(num_lex_champ); 
                    inserer_table_types(num_declaration_type(type_actuel, TYPE_S)); 
                    inserer_table_types(depl_champ); 
                    depl_champ += $1;}
                |liste_champs champ POINT_VIRGULE {incr_index_table_types(pos_nb_champs); 
                    inserer_table_types(num_lex_champ); 
                    inserer_table_types(num_declaration_type(type_actuel, TYPE_S)); 
                    inserer_table_types(depl_champ); 
                    depl_champ += $2;}
                //incremente ensuite le nb champ puis insere toutes les infos sur le champ actuel
                ;

champ : nom_type IDF {/*exec*/exec_type_struct += $1; /*desc*/num_lex_champ=$2; $$=$1;} 
                ///*exec*/->incremente la taille de la structure actuelle de la taille du type du champ
                ///*desc*/->recupère infos du champ a insérer dans la table des types (num_lex et depl_champ) 
                ;

tableau : CROCHET_OUVRANT {pos_debut_desc_tab=premiere_pos_table_types; 
                inserer_table_types(num_declaration_type(type_actuel, TYPE_T)); 
                pos_nb_dimensions=premiere_pos_table_types; 
                premiere_pos_table_types+=1;} 
                liste_dimension CROCHET_FERMANT
                ;

liste_dimension : dimension {exec_type_tableau = exec_type_tableau * $1;
                incr_index_table_types(pos_nb_dimensions);} //incrémente le nombre de dimensions
                |liste_dimension POINT_VIRGULE dimension {exec_type_tableau = exec_type_tableau * $3;
                incr_index_table_types(pos_nb_dimensions);}
                ;

dimension : constante_integer VIRGULE constante_integer {$$ = calcul_taille_dim_tableau($1->num_lexico,$3->num_lexico); //calcul de la taille d'une dimension
                inserer_table_types($1->num_lexico);//insere la borne inférieure dans la table des types
                inserer_table_types($3->num_lexico);}//insere la borne supérieure
                ;

/*----------------------------------------*
|                                         |
| ~~~ TYPES ~~~
|                                         |
*-----------------------------------------*/
nom_type : type_simple {/*exec*/$$=1; //si type simple alors l'execution vaut 1 
                        /*desc*/strcpy(type_actuel, lexeme($1));} 
                |IDF {/*exec*/$$=recup_champ_execution(association_nom($1, TYPE_S)); //récupération de la taille du type associé a l'idf
                        /*desc*/strcpy(type_actuel, lexeme($1));} 
                ;

type_simple : TYPE_INT {$$=0;} //permet de recuperer le type de base dans type_actuel
                |TYPE_FLOAT {$$=1;}
                |TYPE_BOOLEAN {$$=2;}
                |TYPE_CHAR  {$$=3;}
                ;

/*----------------------------------------*
|                                         |
| ~~~ AUTRE DÉCLARATIONS ~~~
|                                         |
*-----------------------------------------*/
declaration_variable : nom_type DECLAR_VARIABLE IDF {inserer_declaration($3, VAR, sommet_pile_region(), num_declaration_type(type_actuel,VAR), exec_variable); exec_variable+=$1; taille_regions +=$1;} //on incrémente apres insertion de la variable car on va utiliser exec_variable pour le déplacement jusqu'a la variable suivante
                ;//association_nom(...) 4eme param : recupère le numero de déclaration du type de la variable pour le champ description

declaration_procedure : PROCEDURE {incremente_num_region();} //on rentre dans une nouvelle procedure -> num_region +1  
                        IDF {inserer_declaration($3, PROC, sommet_pile_region(), premiere_pos_table_types, numero_region);  empiler_pile_region(numero_region); ajout_region(numero_region, niveau_imbrication_statique()-1); ajouterRegion(taille_regions+nis_region(numero_region-1)+(numero_region-1 != 0 ? 1 : 0) , nis_region(numero_region-1), NULL); taille_regions = 0;//on entre dans une nouvelle région donc on empile le numero_region actuel
                        pos_nb_param=premiere_pos_table_types; //index du nb de param pour incrémenter a chaque param rencontré
                        premiere_pos_table_types+=1;}
                        liste_parametres  
                        ACCOLADE_OUVRANTE corps ACCOLADE_FERMANTE  {tab_arbre[sommet_pile_region()]=$7; depiler_pile_region();} //on sort-> on dépile
                ;

//NOTE : rajouter verif retour de type -> seulement types de bases -> ajouter warning
declaration_fonction : FONCTION {incremente_num_region();} //on rentre dans une nouvelle fonction -> num_region +1   
                        IDF {inserer_declaration($3, FCT, sommet_pile_region(), premiere_pos_table_types, numero_region); empiler_pile_region(numero_region); ajout_region(numero_region, niveau_imbrication_statique()-1); ajouterRegion(taille_regions+nis_region(numero_region-1)+(numero_region-1 != 0 ? 1 : 0), nis_region(numero_region-1), NULL); taille_regions = 0; //on entre dans une nouvelle région donc on empile le numero_region actuel
                        pos_debut_fct=premiere_pos_table_types; //index de début de déclaration de la fct pour y insérer la valeur de retour
                        premiere_pos_table_types+=1;
                        pos_nb_param=premiere_pos_table_types;//index du nb de param
                        premiere_pos_table_types+=1;}
                        liste_parametres 
                        RETOURNE type_simple {inserer_table_types_position(pos_debut_fct, num_declaration_type(lexeme($7), TYPE_B));}//insere le type de retour
                        ACCOLADE_OUVRANTE corps ACCOLADE_FERMANTE {tab_arbre[sommet_pile_region()]=$10; depiler_pile_region();} //on sort-> on dépile
                ;

liste_parametres :{exec_variable=niveau_imbrication_statique();} //on calcul le nombre de liens de chainage nécessaires avant d'atteindre le premier parametre 
                {erreur(code_erreur_parenthese_ouvrante);} PARENTHESE_OUVRANTE parametres {erreur(code_erreur_parenthese_fermante);} PARENTHESE_FERMANTE 
                ;

parametres : un_parametre   {incr_index_table_types(pos_nb_param);}
                |parametres VIRGULE un_parametre  {incr_index_table_types(pos_nb_param);}
                |{inserer_table_types_position(pos_nb_param, 0);}
                ;

un_parametre : type_simple IDF {inserer_declaration($2, PARAM, sommet_pile_region(), num_declaration_type(lexeme($1),VAR), exec_variable); exec_variable+=1; taille_regions += 1;
                inserer_table_types($2); 
                inserer_table_types($1);}
                ;

/*----------------------------------------*
|                                         |
| ~~~ INSTRUCTIONS ~~~
|                                         |
*-----------------------------------------*/

instruction : affectation {$$ = $1;}
                |condition {$$ = $1;}
                |condition_unique {$$ = $1;}
                |tant_que {$$ = $1;}
                |faire_tant_que {$$ = $1;}
                |pour {$$ = $1;}
                |appel {$$ = $1;}
                |ecrire {$$ = $1;}
                |lire {$$ = $1;}
                |VIDE {$$=creer_noeud(T_VIDE, -1, -1);}
                |resultat_retourne {$$=$1;}
                //sleep ?
                ;

/*version temporaire de lire et ecrire a completer*/
ecrire : ECRIRE PARENTHESE_OUVRANTE CSTE_CHAINE suite_ecrire_lire PARENTHESE_FERMANTE
                {$$=creer_noeud(T_ECRIRE, $3, -1); ajouter_fils($$, $4);}
                ;

suite_ecrire_lire : VIRGULE liste_expression_ecrire {$$=$2;}
                |{$$=arbre_vide();}
                ;

liste_expression_ecrire : expression {$$=creer_noeud(T_LISTE_ARGUMENTS_ECRIRE, -1, -1); ajouter_fils($$, $1);}
                |expression VIRGULE liste_expression_ecrire 
                {$$=creer_noeud(T_LISTE_ARGUMENTS_ECRIRE, -1, -1); ajouter_frere($1, $3); ajouter_fils($$, $1);}
                ;

lire : LIRE PARENTHESE_OUVRANTE liste_expression_lire PARENTHESE_FERMANTE  
                {$$=creer_noeud(T_LIRE, -1, -1); ajouter_fils($$, $3);}
                ;

liste_expression_lire : expression {$$=creer_noeud(T_LISTE_ARGUMENTS_LIRE, -1, -1); ajouter_fils($$, $1);}
                |expression VIRGULE liste_expression_lire 
                {$$=creer_noeud(T_LISTE_ARGUMENTS_LIRE, -1, -1); ajouter_frere($1, $3); ajouter_fils($$, $1);}

randint : RANDINT PARENTHESE_OUVRANTE constante_integer VIRGULE constante_integer PARENTHESE_FERMANTE
                {$$=creer_noeud(T_RANDINT, -1, 0); ajouter_fils($$, $3); ajouter_frere($3, $5);}
                ;
/*----------------------------------------*
|                                         |
| ~~~ APPELS FONCTIONS ET PROCEDURES ~~~
|                                         |
*-----------------------------------------*/
resultat_retourne : RETOURNE expression  {$$=creer_noeud_retour($2);}
                | RETOURNE {$$=creer_noeud_retour(arbre_vide());}
                ;

appel : IDF liste_arguments {if (association_nom($1, FCT)==-1 && association_nom($1, PROC)==-1){
                                erreur_declaration($1, "APPEL PROCEDURE / FONCTION :", PROC_FCT);}
                            else{
                                if(association_nom($1, FCT) != -1){
                                    $$ = creer_noeud(T_APPEL_FCT, $1, association_nom($1, FCT));
                                }
                                else{
                                    $$ = creer_noeud(T_APPEL_PROC, $1, association_nom($1, PROC));
                                }			
                            }
                            ajouter_fils($$, $2);
                            }
                ;

liste_arguments : {erreur(code_erreur_parenthese_ouvrante);} PARENTHESE_OUVRANTE arguments {erreur(code_erreur_parenthese_fermante);} PARENTHESE_FERMANTE
                {$$=$3;}/*on recupere l'arbre de la liste des arguments*/
                ;

arguments : expression {$$=creer_noeud(T_LISTE_ARGUMENTS, -1, -1); ajouter_fils($$, $1);}
                |expression VIRGULE arguments  {$$=creer_noeud(T_LISTE_ARGUMENTS, -1, -1); ajouter_frere($1, $3); ajouter_fils($$, $1);} 
                |{$$=arbre_vide();}
                ;

/*----------------------------------------*
|                                         |
| ~~~ CONDITIONS ~~~
|                                         |
*-----------------------------------------*/
condition_unique : SI exp_bool
                ALORS ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
                {$$=creer_noeud(T_SI_ALORS, -1, -1); ajouter_frere($2, $5); ajouter_fils($$, $2);}
                ;

condition : SI exp_bool
            ALORS ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
            SINON ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
            {$$=creer_noeud(T_SI_ALORS_SINON, -1, -1); ajouter_frere($2, $5); ajouter_frere($5, $9); ajouter_fils($$, $2);}
                ;

/*----------------------------------------*
|                                         |
| ~~~ BOUCLES ~~~
|                                         |
*-----------------------------------------*/
tant_que : TANT_QUE exp_bool 
            FAIRE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
            {$$=creer_noeud(T_TANT_QUE, -1, -1); ajouter_frere($2, $5); ajouter_fils($$, $2);}
                ;

faire_tant_que : FAIRE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
                TANT_QUE exp_bool
                {$$=creer_noeud(T_FAIRE_TANT_QUE, -1, -1); ajouter_frere($3, $6); ajouter_fils($$, $3);}
                ;

pour : POUR PARENTHESE_OUVRANTE affectation POINT_VIRGULE
                expression_booleenne_compare POINT_VIRGULE
                affectation PARENTHESE_FERMANTE
                FAIRE ACCOLADE_OUVRANTE liste_instructions ACCOLADE_FERMANTE
                /*ici la deuxieme affectation (câd le i++ par ex.) est placé après le bloc d'instruction pour qu'elle soit executée en dernier (comme en C)*/ 
                {$$=creer_noeud(T_POUR, -1, -1); ajouter_fils($$, $3); ajouter_frere($3, $5); ajouter_frere($5, $11); ajouter_frere($11, $7);}
                ;


/*----------------------------------------*
|                                         |
| ~~~ AFFECTATION ~~~
|                                         |
*-----------------------------------------*/
affectation : variable OPAFF expression {
                int type_variable = table_declaration[$1->num_declaration].description;
                if ($1->fils != NULL){
                    if($1->fils->type == T_LISTE_INDICES || $1->fils->type == T_LISTE_CHAMPS){
                        type_variable = $1->fils->num_declaration;
                    }
                }
                /*----------------------------------------*
                | Si on affecte une variable a un appel de fonction on vérifie que le type de retour de la fonction corresponde au type de la variable
                *-----------------------------------------*/
                if ($3->type == T_APPEL_FCT){
                    if (type_variable != table_types[table_declaration[$3->num_declaration].description]){
                        erreur_affectation(type_variable, table_types[table_declaration[$3->num_declaration].description]);
                    }
                    else{
                        $$=creer_noeud(T_AFFECT, -1, -1); ajouter_frere($1, $3); ajouter_fils($$, $1);
                    }
                }
                /*----------------------------------------*
                | Si on affecte une variable a une autre variable on vérifie que les deux variables ont le même type
                *-----------------------------------------*/
                else if ($3->type == T_IDF){
                    int type_expression = table_declaration[$3->num_declaration].description;
                    if ($3->fils != NULL){
                        if($3->fils->type == T_LISTE_INDICES || $3->fils->type == T_LISTE_CHAMPS){
                            type_expression = $3->fils->num_declaration;
                        }
                    }
                    if (type_variable != type_expression){
                        erreur_affectation(type_variable, type_expression);
                    }
                    else{
                        $$=creer_noeud(T_AFFECT, -1, -1); ajouter_frere($1, $3); ajouter_fils($$, $1);
                    }
                }
                /*----------------------------------------*
                | Si on affecte une variable a autre chose (constante, expression arithmetique, ...) on vérifie que le type de la variable corresponde au type de l'expression
                *-----------------------------------------*/
                else if (type_variable != $3->num_declaration){
                        printf("%d %d\n", type_variable, $3->num_declaration);
                        erreur_affectation(type_variable, $3->num_declaration);
                }
                else{
                    $$=creer_noeud(T_AFFECT, -1, -1); ajouter_frere($1, $3); ajouter_fils($$, $1);
                }}
                ;


/*----------------------------------------*
|                                         |
| ~~~ VARIABLES ET EXPRESSIONS ~~~
|                                         |
*-----------------------------------------*/
variable : base_var liste_champs_var {$$=$1; 
                /*Si la variable possede une liste d'indices*/
                if ($$->fils != NULL){
                    ajouter_frere($$->fils, $2);
                    if ($2 != NULL){
                        $$->fils->num_declaration = $2->num_declaration;
                    }
                }
                else{
                    ajouter_fils($$, $2);
                }
                /*Reinit les var globales pour les structures et tableaux seulement si on a pas rencontré une variable simple*/
                if(bool_var_simple == 0){
                    bool_struct_tab = 0;
                    num_declaration_struct = 0;
                }
                }
                ;

base_var : IDF {
                /*Si on est en train d'accéder a une var de type structure ou tableau*/
                if ((table_declaration[table_declaration[recup_declaration_variable_param($1)].description].nature == TYPE_S && bool_struct_tab == 0) || (table_declaration[table_declaration[recup_declaration_variable_param($1)].description].nature == TYPE_T && bool_struct_tab == 0)){
                    num_declaration_struct = table_declaration[table_declaration[recup_declaration_variable_param($1)].description].description;
                    bool_struct_tab = 1;
                    /*Si c'est un tableau*/
                    if (table_declaration[table_declaration[recup_declaration_variable_param($1)].description].nature == TYPE_T){
                        num_declaration_struct = table_declaration[table_types[num_declaration_struct]].description;
                        num_declaration_tab = table_declaration[table_declaration[recup_declaration_variable_param($1)].description].description;
                    }
                }
                /*Pour l'instant on ne peut pas savoir si c'est une variable qui possédent des champs ou des indices donc c'est par défaut une variable simple*/
                bool_var_simple = 1;
                }
                liste_indices {
                /*Si il y a une liste d'indices -> plus une variable simple*/
                if ($3 != NULL){
                    bool_var_simple = 0;
                }
                if ((table_declaration[table_declaration[recup_declaration_variable_param($1)].description].nature == TYPE_S && bool_struct_tab == 0) || (table_declaration[table_declaration[recup_declaration_variable_param($1)].description].nature == TYPE_T && bool_struct_tab == 0)){
                    num_declaration_struct = table_declaration[table_declaration[recup_declaration_variable_param($1)].description].description;
                    bool_struct_tab = 1;
                    if (table_declaration[table_declaration[recup_declaration_variable_param($1)].description].nature == TYPE_T){
                        num_declaration_struct = table_declaration[table_types[num_declaration_struct]].description;
                        num_declaration_tab = table_declaration[table_declaration[recup_declaration_variable_param($1)].description].description;
                    }
                }
                if (recup_declaration_variable_param($1) == -1 && bool_struct_tab == 0){
                    erreur_declaration($1, "VARIABLE :", VAR);
                }
                else{
                    $$=creer_noeud(T_IDF, $1, recup_declaration_variable_param($1)); ajouter_fils($$, $3);
                }
                }
                ;

liste_champs_var : POINT base_var liste_champs_var {
                bool_var_simple = 0;
                type_champ_tmp = verif_declaration_champ(num_declaration_struct, $2->num_lexico);
                if (type_champ_tmp == -1){
                    erreur_declaration_champ_structure($2->num_lexico);
                    exit(-1);
                }
                else{
                    if (table_declaration[type_champ_tmp].nature == TYPE_T){
                        type_champ_tmp = table_types[table_declaration[type_champ_tmp].description];
                    }
                    if (type_champ_tmp < 3){
                        type_champ_final = type_champ_tmp;
                    }
                    $$=creer_noeud(T_LISTE_CHAMPS, $2->num_lexico, type_champ_final); ajouter_frere($2,$3); ajouter_fils($$, $2);}
                }
                |{$$=arbre_vide();}
                ;

liste_indices : CROCHET_OUVRANT liste_indices_bis CROCHET_FERMANT {$$=$2;}
                |{$$=arbre_vide();}
                ;
            
liste_indices_bis : expression {
                $$=creer_noeud_indice($1, num_declaration_struct);
                $$->num_declaration = table_types[num_declaration_tab];
                }
                |expression VIRGULE liste_indices_bis {
                ajouter_frere($1, $3); $$=creer_noeud_indice($1, num_declaration_struct);
                $$->num_declaration = table_types[num_declaration_tab];
                }

                ;

expression : exp_arith {$$=$1;}
                ;

/*----------------------------------------*
|                                         |
| ~~~ EXPRESSIONS BOOLEENNES ~~~
|                                         |
*-----------------------------------------*/
exp_bool : expression_booleenne_ou {$$=$1;}
                ;
/*IDEM ICI*/
expression_booleenne_ou :expression_booleenne_et OU expression_booleenne_ou{$$=creer_noeud(T_OU, -1, 2); ajouter_frere($1, $3); ajouter_fils($$, $1);}
                |expression_booleenne_et {$$=$1;}
                ;
/*VERIFIER LES TYPES*/
expression_booleenne_et :expression_booleenne_non ET expression_booleenne_et{$$=creer_noeud(T_ET, -1, 2); ajouter_frere($1, $3); ajouter_fils($$, $1);}
                |expression_booleenne_non {$$=$1;}
                ;

expression_booleenne_non :NON expression_booleenne {$$=creer_noeud(T_NON, -1, 2); ajouter_fils($$, $2);}
                |expression_booleenne {$$=$1;}
                ;

expression_booleenne : exp_arith {$$=$1;}
                |expression_booleenne_compare {$$=$1;}
                ;

expression_booleenne_compare : exp_arith comparateur exp_arith {$$=creer_noeud_expression_booleenne_compare($1,$3,$2);}
                ;

comparateur : DOUBLEEGAL        {$$=creer_noeud(T_DOUBLEEGAL, -1, 2);}
                |INFERIEUR      {$$=creer_noeud(T_INF, -1, 2);}
                |SUPERIEUR      {$$=creer_noeud(T_SUP, -1, 2);}
                |INFERIEUR_EGAL {$$=creer_noeud(T_INF_EGAL, -1, 2);}
                |SUPERIEUR_EGAL {$$=creer_noeud(T_SUP_EGAL, -1, 2);}
                ;

/*----------------------------------------*
|                                         |
| ~~~ EXPRESSIONS ARITHMÉTIQUES ~~~
|                                         |
*-----------------------------------------*/
exp_arith : exp_arith_mult_div  {$$=$1;}
        |exp_arith PLUS exp_arith_mult_div  {$$ = creer_noeud_expression_arithmetique($1, $3, T_PLUS);}
        |exp_arith MOINS exp_arith_mult_div {$$ = creer_noeud_expression_arithmetique($1, $3, T_MOINS);}
        ;                                

exp_arith_mult_div : expression_arithmetique {$$=$1;}
                    |exp_arith_mult_div MULT expression_arithmetique {$$ = creer_noeud_expression_arithmetique($1, $3, T_MULT);}
                    |exp_arith_mult_div DIV expression_arithmetique {$$ = creer_noeud_expression_arithmetique($1, $3, T_DIV);}
                    ;

expression_arithmetique : PARENTHESE_OUVRANTE exp_bool PARENTHESE_FERMANTE {$$=$2;}
            |constante_integer {$$=$1;}
            |constante_float {$$=$1;}
            |variable {$$=$1;}
            |appel {$$=$1;}
            |randint {$$=$1;}
            |CSTE_BOOLEAN {$$ = creer_noeud(T_CSTE_BOOL, $1, 2);}
            |CSTE_CHAR {$$ = creer_noeud(T_CSTE_CHAR, $1, 3);}
            ;

constante_integer : CSTE_INTEGER {$$=creer_noeud(T_CSTE_E, $1, 0);}
            |MOINS CSTE_INTEGER {$$=creer_noeud(T_CSTE_E, $2, 0);}
            ;

constante_float : CSTE_FLOAT {$$=creer_noeud(T_CSTE_F, $1, 1);}
            |MOINS CSTE_FLOAT {$$=creer_noeud(T_CSTE_F, $2, 1);}
            ;


%%


/*----------------------------------------*
|                                         |
| ~~~ FONCTION PRINCIPAL (MAIN) ~~~
|                                         |
*-----------------------------------------*/
//rajouter une option pour l'affichage des tables et des arbres et de la pile (argument -a)
int main(int argc, char * argv[]){

    int aff_tables=0, aff_arbres=0, aff_pile=0, execution=0;

    if (argc < 2){
        printf("Usage : ./compilateur <fichier_source> < -t (affich. tables)> < -a (affich. arbres)> < -p (affich.pile)> < -e (execution du programme)\n");
        exit(-1);
    }

    if (argc > 2){
        if (strcmp(argv[2], "-t") == 0){
            aff_tables = 1;
        }
        else if (strcmp(argv[2], "-a") == 0){
            aff_arbres = 1;
        }
        else if (strcmp(argv[2], "-p") == 0){
            aff_pile = 1;
        }
        else if (strcmp(argv[2], "-e") == 0){
            execution = 1;
        }
        else{
            printf("Usage : ./compilateur <fichier_source> < -t (affich. tables)> < -a (affich. arbres)> < -p (affich.pile)> < -e (execution du programme)\n");
            exit(-1);
        }
    }

    if (argc > 3){
        if (strcmp(argv[3], "-t") == 0){
            aff_tables = 1;
        }
        else if (strcmp(argv[3], "-a") == 0){
            aff_arbres = 1;
        }
        else if (strcmp(argv[3], "-p") == 0){
            aff_pile = 1;
        }
        else if (strcmp(argv[3], "-e") == 0){
            execution = 1;
        }
        else{
            printf("Usage : ./compilateur <fichier_source> < -t (affich. tables)> < -a (affich. arbres)> < -p (affich.pile)> < -e (execution du programme)\n");
            exit(-1);
        }
    }

    if (argc > 4){
        if (strcmp(argv[4], "-t") == 0){
            aff_tables = 1;
        }
        else if (strcmp(argv[4], "-a") == 0){
            aff_arbres = 1;
        }
        else if (strcmp(argv[4], "-p") == 0){
            aff_pile = 1;
        }
        else if (strcmp(argv[4], "-e") == 0){
            execution = 1;
        }
        else{
            printf("Usage : ./compilateur <fichier_source> < -t (affich. tables)> < -a (affich. arbres)> < -p (affich.pile)> < -e (execution du programme)\n");
            exit(-1);
        }
    }

    if (argc > 5){
        if (strcmp(argv[5], "-t") == 0){
            aff_tables = 1;
        }
        else if (strcmp(argv[5], "-a") == 0){
            aff_arbres = 1;
        }
        else if (strcmp(argv[5], "-p") == 0){
            aff_pile = 1;
        }
        else if (strcmp(argv[5], "-e") == 0){
            execution = 1;
        }
        else{
            printf("Usage : ./compilateur <fichier_source> < -t (affich. tables)> < -a (affich. arbres)> < -p (affich.pile)> < -e (execution du programme)\n");
            exit(-1);
        }
    }

    /*----------------------------------------*
    | Modifie la lecture par défaut de lex -> permet donc d'utiliser stdin
    *-----------------------------------------*/
    FILE * fichier = fopen(argv[1], "r");
    yyin = fichier;

    /*----------------------------------------*
    | Initialisations des Tables et de la Pile des régions
    *-----------------------------------------*/
    init_table_lexico();
    init_table_declaration();
    init_pile_region();
    initTableRegions();
    srand(time(NULL));

    if (yyparse()==0){ 
        if (nb_warnings > 0){
            printf("Nombre de warnings : %d\n", nb_warnings);
            printf("\n/-----------------------------------------\\\n|                                         |\n|    XXX COMPILATION NON TERMINÉE XXX     |\n|                                         |\n\\-----------------------------------------/\n\n");
            exit(-1);
        }

        /*Bricolage ?*/
        for (int i=0; i<=numero_region; i++){
            table_regions[i].arbre = tab_arbre[i];
        }

        /*----------------------------------------*
        | Affichage des tables
        *-----------------------------------------*/
        if (aff_tables == 1){
            affichage_table_lexeme();
            affichage_table_declaration();
            affichage_table_types();
            afficherRegions();
        }

        for (int i=0; i<=numero_region; i++){
            if (aff_arbres == 1){
                printf("\n\n\n------ ARBRE REGION %d --------", i);
                affichage_arbre(tab_arbre[i], 0);
            }

            indice_affichage_pile+=table_regions[i].taille; /*Pour un joli affichage de la pile*/
        }

        printf("\n/-----------------------------------------\\\n|                                         |\n|      ~~~ COMPILATION TERMINÉE ~~~       |\n|                                         |\n\\-----------------------------------------/\n\n");

        /*Bricolage aussi ?*/
        for (int i=0; i<5000; i++){
            pile[i].type = CELLULE_VIDE;
            pile[i].valeur.entier = -1;
        }

        if (execution == 1){
            parcours_arbre(table_regions[0].arbre, 0);
        }
              
        if (aff_pile == 1){
            affichage_pile();
        }
        

        exit(0);
    }
}
