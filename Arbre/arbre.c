#include "arbre.h"
#include <string.h>
#include "../TAD_table_lexico/table_lexico.c"

/**
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @date 28-10-2023
*/

/**
 * @brief retourne un arbre vide 
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser 
 * @return NULL
*/
arbre arbre_vide(){
    return NULL;
}

/**
 * @brief Vérifie si l'arbre est vide
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param arbre : L'arbre à vérifier
 * @return int : 1 si vide, 0 sinon
*/
int est_arbre_vide(arbre a){
    if (a == arbre_vide()){
        return 1;
    }
    return 0;
}

/**
 * @brief Création d'un noeud avec ses information : type, numéro de déclaration et numéro lexicographique
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param type : Le type du noeud
 * @param num_lex : Le numéro lexicographique du noeud 
 * @param num_decl : Le numéro de déclaration du noeud  
 * @return arbre ; renvoie le noeud créé avec les champs numero de déclaration, numéro lexicographique, type, son fils et son fils remplient
*/
arbre creer_noeud(int type, int num_lex, int num_decl){
    arbre nouveau_arbre = arbre_vide();
    nouveau_arbre = (arbre)malloc(sizeof(struct noeud));
    if (nouveau_arbre == NULL){
        fprintf(stderr, "Erreur d'allocation mémoier de nouveau arbre.\n");
        exit(EXIT_FAILURE);
    }
    nouveau_arbre->num_declaration = num_decl;
    nouveau_arbre->num_lexico = num_lex;
    nouveau_arbre->type = type;
    nouveau_arbre->fils = arbre_vide();
    nouveau_arbre->frere = arbre_vide();
    return nouveau_arbre;
}

/**
 * @brief ajoute un fils à l'arbre
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param arbre a : ajout du noeud dans cet arbre
 * @param arbre fils : noeud "fils" ajouté à a 
*/
void ajouter_fils(arbre a, arbre fils){
    a->fils = fils;
}


/**
 * @brief ajoute un frère à l'arbre
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param arbre a : ajout du noeud dans cet arbre
 * @param arbre frere : noeud "frère" ajouté à a 
*/
void ajouter_frere(arbre a, arbre frere){
    a->frere = frere;
}

/**
 * @brief Affiche l'arbre en entier 
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param a : L'arbre entier a afficher 
*/
void afficher_arbre(arbre a){
    printf("\n---------------------------------------------------- ADRESSE %p\n", a);
    affichage_arbre(a, 0);
}

/**
 * @brief Affiche le noeud de a 
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param a : Le noeud a afficher  
*/
void affichage_arbre (arbre a, int i){
    if (a == arbre_vide()) {
        return;
    }
    switch (a->type){
    case T_IDF:
        printf("{[T_IDF %s] %d|%d}",lexeme(a->num_lexico), a->num_lexico,a->num_declaration);
        break;   
    case T_PLUS:
        printf("{[T_PLUS] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_MOINS:
        printf("{[T_MOINS] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_MULT:
        printf("{[T_MULT] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_DIV:
        printf("{[T_DIV] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_ECRIRE:
        printf("[T_ECRIRE] %s", lexeme(a->num_lexico));
        break;
    case T_LIRE:
        printf("[T_LIRE]");
        break;
     case T_AFFECT:
        printf("[T_AFFECT]");
        break;
    case T_APPEL_FCT:
        printf("{[T_APPEL_FCT %s] %d|%d}", lexeme(a->num_lexico), a->num_lexico, a->num_declaration);
        break;
    case T_APPEL_PROC:
        printf("{[T_APPEL_PROC %s] %d|%d}", lexeme(a->num_lexico), a->num_lexico, a->num_declaration);
        break;
    case T_VIDE:
        printf("[T_VIDE]");
        break;
    case T_RETOURNE:
        printf("[T_RETOURNE]");
        break;
    case T_CSTE_E:
        printf("[T_CSTE_E %d]",a->num_lexico);
        break;
    case T_CSTE_F:
        printf("[T_CSTE_F %f]", atof(lexeme(a->num_lexico)));
        break;
    case T_CSTE_CHAR:
        printf("[T_CSTE_CHAR %s]", lexeme(a->num_lexico));
        break;
    case T_CSTE_CHAINE:
        printf("[T_CSTE_CHAINE %s]", lexeme(a->num_lexico));
        break;
    case T_CSTE_BOOL:
        if(a->num_lexico == 1){
            printf("{[T_CSTE_BOOL true (1)] %d|%d}", a->num_lexico, a->num_declaration);
        }
        else{
            printf("{[T_CSTE_BOOL false (0)] %d|%d}", a->num_lexico, a->num_declaration);
        }
        break;
    case T_POUR:
        printf("[T_POUR]");
        break;
    case T_TANT_QUE:
        printf("[T_TANT_QUE]");
        break;
    case T_FAIRE_TANT_QUE:
        printf("[T_FAIRE_TANT_QUE]");
        break;

    case T_SI_ALORS_SINON:
        printf("[T_SI_ALORS_SINON]");
        break;
    case T_SI_ALORS:
        printf("[T_SI_ALORS]");
        break;
    case T_LISTE_CHAMPS:
        printf("{[T_LISTE_CHAMPS] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_LISTE_INDICES:
        printf("{[T_LISTE_INDICES] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_LISTE:
        printf("[T_LISTE]");
        break;
    case T_OU:
        printf("{[T_OU] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_ET:
        printf("{[T_ET] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_NON:
        printf("{[T_NON] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_DOUBLEEGAL:
        printf("{[T_DOUBLEEGAL] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_INF:
        printf("{[T_INF] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_SUP:
        printf("{[T_SUP] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_INF_EGAL:
        printf("{[T_INF_EGAL] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_SUP_EGAL:
        printf("{[T_SUP_EGAL] %d|%d}", a->num_lexico, a->num_declaration);
        break;
    case T_LISTE_ARGUMENTS_ECRIRE:
        printf("[T_LISTE_ARGUMENTS_ECRIRE]");
        break;
    case T_LISTE_ARGUMENTS_LIRE :
        printf("[T_LISTE_ARGUMENTS_LIRE]");
        break;
    case T_LISTE_ARGUMENTS:
        printf("[T_LISTE_ARGUMENTS]");
        break;
    case T_RANDINT:
        printf("[T_RANDINT]");
        break;
    default:
        printf("[%d voir quel define] [%d | %d]", a->type, a->num_declaration, a->num_lexico);
        break;
    }
    
    if(!est_arbre_vide(a->frere)){
        printf("--------");
        affichage_arbre(a->frere, i+1);
    }

    if(!est_arbre_vide(a->fils)){
        printf("\n\n");

        for(int j = 0; j < i; j++){
            printf("\t\t");
        }
        printf("    |\n");
        for(int j = 0; j < i; j++){
            printf("\t\t");
        }
        affichage_arbre(a->fils,i);
    }

}

/**
 * @brief Détruit l'arbre en entier  
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param a : L'arbre a détruire
*/
void detruire_arbre(arbre a){
    arbre courant = a;
    if(est_arbre_vide(courant)){
        return;
    }
    courant = a->fils;
    detruire_arbre(courant);
    courant = a->frere;
    detruire_arbre(courant);
    free(a);
    a = arbre_vide();
}
