/**
 * @file table_declaration.c
 * @author MATHEVON Baptiste Secondaires : YILDIZ Tolga, GUNES Ozan
 * @brief TAD implémentation de la table des déclarations
 * @date 19-10-2023
*/

#include "./table_declaration.h"

extern int premiere_pos_zone_de_debordement;
extern tab_declaration table_declaration;
extern int numero_ligne;
extern int numero_car;
extern int premiere_pos_table_types;
extern tab_types table_types;

extern pile_region pile_des_regions;

extern int code_erreur;
extern int nb_warnings;

int yyerror();

/**
 * @author MATHEVON Baptiste
 * @brief Initialisation de la table des déclarations (toutes les cases sont mises a -1 + insertion des 4 types de bases)
 * @brief Et initialisation de la tables des types et des entêtes de sous-programmes
*/
void init_table_declaration(){
    memset(table_declaration, -1, sizeof(table_declaration));

    for (int i = 0; i<4; i++){
        table_declaration[i].nature = TYPE_B;
        table_declaration[i].suivant = -1;
        table_declaration[i].region = 0;
        table_declaration[i].description = -1;
        table_declaration[i].execution = 1;
    }
    
    //Initialisation de la table des types et des entêtes 
    memset(table_types, -1, sizeof(table_types));
}

/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'une declaration dans la table
 * @param numero_lexico Numero léxicographique du lexème que l'on veut ajouter à la table des déclarations
 * @param nature Nature du lexème à ajouter (VAR, TYPE_S, etc...)
 * @param region Région de déclaration
 * @param description Description de la déclaration
 * @param execution Valeur à l'execution (déplacement pour VAR, région pour FCT, etc...)
 * @return int : Numéro de déclaration
*/
int inserer_declaration(int numero_lexico, int nature, int region, int description, int execution){
    int retour = numero_lexico;

    //on vérifie que la déclaration n'existe pas déja dans la même région avec l'association de nom
    int num_declaration = association_nom(numero_lexico, nature);
    if (num_declaration != -1 && table_declaration[num_declaration].region == region){
        //si la déclaration existe déja on printf un msg d'erreur et on renvoie le numéro de la déclaration existante (ce qui signifique qu'on ne peut pas redéfinir un type dans la même région, seule la première déf sera prise en compte)
        erreur_redeclaration(numero_lexico, nature);
        return num_declaration;
    }

    //si l'emplacement dans la tables des declarations correspondant au numero lexico est vide on insére la nouvelle declaration
    if (table_declaration[numero_lexico].nature == -1){
        table_declaration[numero_lexico].nature = nature;
        table_declaration[numero_lexico].suivant = -1;
        table_declaration[numero_lexico].region = region;
        table_declaration[numero_lexico].description = description;
        table_declaration[numero_lexico].execution = execution;

        return retour;
    }

    //SINON tant qu'il y a un suivant on parcourt le chainage
    while(table_declaration[numero_lexico].suivant != -1){
        numero_lexico = table_declaration[numero_lexico].suivant;
    }
    //on met a jour le suivant 
    table_declaration[numero_lexico].suivant = premiere_pos_zone_de_debordement;
            
    //on insere la declaration dans la premiere position libre de la zone de debordement
    table_declaration[premiere_pos_zone_de_debordement].nature = nature;
    table_declaration[premiere_pos_zone_de_debordement].suivant = -1;
    table_declaration[premiere_pos_zone_de_debordement].region = region;
    table_declaration[premiere_pos_zone_de_debordement].description = description;
    table_declaration[premiere_pos_zone_de_debordement].execution = execution;

    retour = premiere_pos_zone_de_debordement;
    //on met a jour la premiere pos libre de la zone de debordement
    premiere_pos_zone_de_debordement++;

    return retour;
}

/**
 * @author MATHEVON Baptiste
 * @brief Renvoie le numéro de déclaration d'un objet déclaré dans une région accessible depuis la région d'utilisation
 * @param numero_lexico Numéro lexicographique de l'objet
 * @param nature Nature de l'objet (VAR, TYPE_S, etc...)
 * @return int : Si la déclaration existe/est accessible alors numéro de déclaration, sinon 0???
*/
int association_nom(int numero_lexico, int nature){
    //permet de parcourir toutes les régions actuelles de la pile des régions (toutes les régions englobantes au moment de l'association de nom)
    pile_region pile_temporaire = pile_des_regions;
    int region_pile_temporaire;

    int region_actuelle = sommet_pile_region();

    //le premier numero de declaration est identique au numero lexicographique 
    int numero_declaration = numero_lexico;
    int nature_num_lex;
    int region_num_lex;

    //tant qu'il reste des régions dans la pile on parcourt la pile    
    while(pile_temporaire != NULL){
        region_pile_temporaire = pile_temporaire->valeur;

        //tant qu'on ne tombe pas sur une declaration de la nature souhaitée on parcourt le chainage
        while (numero_declaration != -1){
            nature_num_lex = table_declaration[numero_declaration].nature;
            region_num_lex = table_declaration[numero_declaration].region;

            //VERSION TEMPORAIRE POUR TYPE_S ET TYPE_T -> si on ne fait pas ca, pb lors de la recup du champ execution d'un typedef
            switch(nature){
                case TYPE_S : if (nature_num_lex == TYPE_S && region_num_lex == region_pile_temporaire || nature_num_lex == TYPE_T && region_num_lex == region_pile_temporaire || nature_num_lex == TYPE_B && region_num_lex == region_pile_temporaire){
                    return numero_declaration;
                }

                default :
                    if (nature_num_lex == nature && region_num_lex == region_pile_temporaire){
                        return numero_declaration;
                    }

                    numero_declaration = table_declaration[numero_declaration].suivant;
                    break;
            } 

        }

        numero_declaration = numero_lexico; //il faut reparcourir toute la table des déclarations a partir du premier
       
        pile_temporaire=pile_temporaire->suivant; //on passe à la région suivante 
    }

    /* retour -1 car num_decl des int = 0 */
    return -1;

} 

/** --------------------------------------*
* @author : MATHEVON Baptiste, YILDIZ Tolga
* @brief : Récupération du numéro de déclaration d'un argument
*-----------------------------------------*/
int numero_declaration_argument(int num_lexico, int region){
    int num_declaration = num_lexico;

    while (num_declaration != -1){
        if (table_declaration[num_declaration].nature == PARAM && table_declaration[num_declaration].region == region){
            return num_declaration;
        }
        num_declaration = table_declaration[num_declaration].suivant;
    }
}

/**
 * @author MATHEVON Baptiste, YILDIZ Tolga
 * @brief Récupération de la valeur du champ execution dans la table des déclarations
 * @param num_declaration Numéro de la déclaration
 * @return int : Valeur du champ exécution
*/
int recup_champ_execution(int num_declaration){
    return table_declaration[num_declaration].execution;
}

/**
 * @author MATHEVON Baptiste, YILDIZ Tolga
 * @brief Calcul de la taille d'une dimension d'un tableau
 * @param borne_inf Borne inférieur de la dimension
 * @param borne_sup Borne supérieur de la dimension
 * @return int : Taille de la dimension
*/
int calcul_taille_dim_tableau(int borne_inf, int borne_sup){
    int taille;
    /*un tableau ne peut pas avoir une borne sup < borne inf OU une taille de 0 -> aucun sens*/
    if (borne_sup < borne_inf){ 
        printf("ERREUR [ligne %d car. %d] (bornes tableau) : la borne supérieur d'une dimension ne peut pas être inférieur à sa borne inférieur\n", numero_ligne+2/*numero ligne compte -2 -> trouver le bug*/, numero_car);
        return -1;
    }
    if (borne_sup == borne_inf){ 
        printf("WARNING [ligne %d car. %d] (bornes tableau) : les deux bornes de votre tableau sont égales -> inutile (tableau de 0 cases)\n", numero_ligne+1/*idem ici -> bug*/, numero_car);
        return 0;
    }

    taille = borne_sup - borne_inf + 1;

    return taille;
}

/**
 * @author MATHEVON Baptiste
 * @brief Récupération du numéro de déclaration d'un type
 * @param type Type souhaité
 * @param nature Nature de l'objet nécessitant de trouver ce type
 * @return int : numéro de déclaration
*/
int num_declaration_type(char type[], int nature){
    int num_dec = association_nom(numero_lexico(type), TYPE_S);
    if (num_dec == -1){
        erreur_declaration(numero_lexico(type), "déclaration", nature);
        return -1;
    }
    return num_dec;
}

/*-- TABLES DES TYPES --*/

/**
 * @author MATHEVON Baptiste
 * @brief Increment le nombres de champs d'une structure dans la table des types au fur et a mesure qu'un champ est traité
 * @param index Position dans la table des types du nombre de champs de la structure actuelle
*/
void incr_index_table_types(int index){
    /*Si le champ est a -1 il faut l'incrémenter a 1*/
    if (table_types[index]==-1){
        table_types[index]+=2;
    }
    else{
        table_types[index]+=1;
    }
}

/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'un entier dans la table des types à la position pos
*/
void inserer_table_types_position(int position, int entier){
    table_types[position]=entier;
}


/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'un entier dans la table des types a la première pos de la table des types
*/
void inserer_table_types(int entier){
    inserer_table_types_position(premiere_pos_table_types, entier);
    premiere_pos_table_types+=1;
}


/**
 * @author MATHEVON Baptiste
 * @brief Vérifie la déclaration d'une variable
*/
int recup_declaration_variable_param(int num_lex){
    /*La variable peut également être un paramètre*/

    int var=association_nom(num_lex, VAR);
    int param=association_nom(num_lex, PARAM);

    if (var == -1 && param == -1){
        return -1;
    }
    if (var == -1){
        return param;
    }
    return var;
}

/**
 * @author MATHEVON Baptiste, GUNES Ozan
 * @brief Vérifie existance d'un champ pour les types structure
*/
int verif_champ_type(int num_lex_type, int num_lex_champ){
    int num_decla_type = association_nom(num_lex_type, TYPE_S);

    if (table_declaration[num_decla_type].nature != TYPE_S){
        printf("ERROR : %s n'est pas une structure\n", lexeme(num_lex_type));
        exit(-1);
    }

    int description_type = table_declaration[num_decla_type].description;
    int nb_champs = table_types[description_type];
    
    if (nb_champs==0){
        printf("ERROR : La structure %s n'a pas de champ\n", lexeme(num_lex_type));
        exit(-1);
    }

    int index_num_lex_champ = description_type+1;
    for (int i=0; i < nb_champs; i++){
        if (table_types[index_num_lex_champ] == num_lex_champ){
            return 1;
        }
        i+=3;
    }
    return -1;

}

/*-- WARNINGS ET ERREURS --*/
/**
 * @author MATHEVON Baptiste, GUNES Ozan
 * @brief Affichage d'un Warning en cas de redéclaration
 * @brief Fonction appelée dans inserer_declaration si la déclaration existe déja 
*/
void erreur_redeclaration(int numero_lexico, int nature){//enlever le premier %s -> inutile
    nb_warnings++;
    switch(nature){
        case VAR : printf("WARNING [ligne %d] (redéclaration %s) : '%s' est déja déclaré. \n", numero_ligne, "VARIABLE", lexeme(numero_lexico));
        break;
        case FCT : printf("WARNING [ligne %d] (redéclaration %s) : '%s' est déja déclaré. \n", numero_ligne, "FONCTION", lexeme(numero_lexico));
        break;
        case PROC : printf("WARNING [ligne %d] (redéclaration %s) : '%s' est déja déclaré. \n", numero_ligne, "PROCEDURE", lexeme(numero_lexico));
        break;
        case PARAM : printf("WARNING [ligne %d] (redéclaration %s) : '%s' est déja déclaré. \n", numero_ligne, "PARAMETRE", lexeme(numero_lexico));
        break;
        case TYPE_S : printf("WARNING [ligne %d] (redéclaration %s) : '%s' est déja déclaré. \n", numero_ligne, "STRUCTURE", lexeme(numero_lexico));
        break;
        case TYPE_T : printf("WARNING [ligne %d] (redéclaration %s) : '%s' est déja déclaré. \n", numero_ligne, "TABLEAU", lexeme(numero_lexico));
        break;
        default : //pour gcc sinon pas content
        break;
    }
}

/**
 * @author MATHEVON Baptiste, GUNES Ozan
 * @brief Affichage d'un Warning en cas de non déclaration
*/
void erreur_declaration(int numero_lexico, char type_erreur[], int nature){
    nb_warnings++;
    switch(nature){
        case VAR : printf("WARNING [ligne %d] (%s) : '%s' non déclaré. \n", numero_ligne, type_erreur, lexeme(numero_lexico));
        break;
        case PROC_FCT : printf("WARNING [ligne %d] (%s) : '%s' non déclaré. \n", numero_ligne, type_erreur, lexeme(numero_lexico)); 
        break;
        case PARAM : printf("WARNING [ligne %d] (%s) : '%s' non déclaré. \n", numero_ligne, type_erreur, lexeme(numero_lexico)); 
        break;
        case TYPE_S : printf("WARNING [ligne %d] (%s) : '%s' non déclaré. \n", numero_ligne, type_erreur, lexeme(numero_lexico)); 
        break;
        case TYPE_T : printf("WARNING [ligne %d] (%s) : '%s' non déclaré. \n", numero_ligne, type_erreur, lexeme(numero_lexico));
        break;
        default : //pour gcc sinon pas content
        break;
    }
}

/*-- AFFICHAGE TERMINAL DES TABLES --*/

/**
 * @author MATHEVON Baptiste
 * @brief Affichage dans le terminal de la table des déclarations
*/
void affichage_table_declaration(){
    char nature[7];
    //temporaire
    printf("-- TABLE DES DECLARATIONS --\n");
    int i=0;
    while(i<500){ 
        //faire une fonction en dehors plutot que ce grand switch moche
        switch (table_declaration[i].nature){
            case TYPE_B : strcpy(nature, "TYPE_B");
            break;        
            case VAR : strcpy(nature, "VAR");
            break;
            case FCT : strcpy(nature, "FCT");
            break;
            case PROC : strcpy(nature, "PROC");
            break;
            case PARAM : strcpy(nature, "PARAM");
            break;
            case TYPE_S : strcpy(nature, "TYPE_S");
            break;
            case TYPE_T : strcpy(nature, "TYPE_T");
            break;
            default : strcpy(nature, "-1");
            break;

        }
        if (table_declaration[i].nature != -1){
            printf("[%2d]|Nature : %6s | Suivant : %d | Region : %d | Description : %2d | Execution : %d \n", i, nature, table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution);
        }
        i++;
    }

    //affichage zone de débordement
    printf("-- ZONE DE DEBORDEMENT -- \n");
    i=500;
    while(i<=premiere_pos_zone_de_debordement-1){
        //faire une fonction en dehors plutot que ce grand switch moche
        switch (table_declaration[i].nature){
            case TYPE_B : strcpy(nature, "TYPE_B");
            break;        
            case VAR : strcpy(nature, "VAR");
            break;
            case FCT : strcpy(nature, "FCT");
            break;
            case PROC : strcpy(nature, "PROC");
            break;
            case PARAM : strcpy(nature, "PARAM");
            break;
            case TYPE_S : strcpy(nature, "TYPE_S");
            break;
            case TYPE_T : strcpy(nature, "TYPE_T");
            break;
            default : strcpy(nature, "-1");
            break;
        }
        printf("[%d]|Nature : %6s | Suivant : %d | Region : %d | Description : %2d | Execution : %d \n", i, nature, table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution);
        i++;
    }
}

/**
 * @author MATHEVON Baptiste
 * @brief Affichage sur le terminal de la table des types et des entêtes
*/
void affichage_table_types(){
    int i=0;
    printf("-- TABLE DES TYPES ET DES ENTETES --\n");
    while (table_types[i]!=-1){
        printf("|%2d", i);
        i++;
    }
    printf("\n");
    i=0;
    while (table_types[i]!=-1){
        printf("|%2d", table_types[i]);
        i++;
    }
}
