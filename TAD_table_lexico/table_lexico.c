/**
 * @file table_lexico.c
 * @author MATHEVON Baptiste
 * @brief TAD implémentation de la table lexicographique
 * @date 15-10-2023
*/
#include "table_lexico.h"

/*Variables globales*/
extern tab_lexico table;
extern int tab_hashcode[32];
extern int premiere_pos_libre;

/**
 * @author MATHEVON Baptiste
 * @brief Initialisation de la table lexico (et de la table de hashcode)
*/
void init_table_lexico(){
    memset(tab_hashcode, -1, sizeof(tab_hashcode));
    inserer_lexeme("int");
    inserer_lexeme("float");
    inserer_lexeme("bool");
    inserer_lexeme("char");
}

/**
 * @author MATHEVON Baptiste
 * @brief Calcul du hashcode d'un lexeme donné
 * @param lexeme Lexeme dont on calcule le hashcode
 * @return int : numéro de hashcode du lexème
*/
int calcul_hashcode(char * lexeme){
    int hashcode=0;

    for (int i=0; i<strlen(lexeme); i++){
        hashcode+=lexeme[i];
    }

    hashcode=hashcode%32;

    return hashcode;
}

/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'un lexeme dans la table des lexemes
 * @param lexeme Lexeme a insérer dans la table
 * @return int : numero lexico du lexème si déja dans la table, sinon numéro lexico du lexème qui vient d'être inséré
*/
int inserer_lexeme(char lexeme[]){
    int hashcode;
    int i, ret;
    int num_lex = numero_lexico(lexeme);
    
    //si le lexeme est déja dans la table on renvoie son numéro lexicographique
    if (num_lex != -1){
        /* printf("%s est déja dans la table des lexèmes\n", lexeme); */
        return num_lex;
    }

    //sinon on l'insere a la premiere position de libre
    table[premiere_pos_libre].longueur = strlen(lexeme);
    strcpy(table[premiere_pos_libre].lexeme, lexeme);
    table[premiere_pos_libre].suivant=-1;

    //on calcule le hashcode pour mettre en place le chainage dans la table de hashcode
    hashcode = calcul_hashcode(lexeme);

    //si aucun lexeme de meme hashcode il devient le premier dans la table de hashcode
    if (tab_hashcode[hashcode]==-1){
        tab_hashcode[hashcode]=premiere_pos_libre;
    }
    //sinon on parcourt la table des lexemes pour le placer dans le premier champ suivant disponible des lexemes de meme hashcode
    else{
        i=tab_hashcode[hashcode];
        while(table[i].suivant!=-1){
            i=table[i].suivant;
        }
        table[i].suivant = premiere_pos_libre;
    }

    //on recupere le numero lexico du lexeme qui vient d'être inséré 
    ret=premiere_pos_libre;

    //incrementation de la premiere position libre dans la table des lexemes
    premiere_pos_libre++;

    //on renvoie le numero lexico du lexeme qui vient d'être inséré
    return ret;
};

/**
 * @author MATHEVON Baptiste
 * @brief Recupération du numéro lexicographique (donc verification si le lexème est déja dans la table ou non)
 * @param lexeme Lexeme dont on veut récupérer le numéro lexicographique
 * @return int : numero lexico du lexeme si déja dans la table, -1 sinon
*/
int numero_lexico(char * lexeme){
    int hashcode_nouveau_lexeme = calcul_hashcode(lexeme);
    int longueur_nouveau_lexeme = strlen(lexeme);
    //on démarre la vérification a l'indice i qui correspond au premier lexeme de même hashcode
    int i = tab_hashcode[hashcode_nouveau_lexeme];

    while(table[i].suivant!=0){
        if (table[i].longueur == longueur_nouveau_lexeme){
            //si les deux lexemes ont la même longueur on les compare
            if (strcmp(table[i].lexeme, lexeme)==0){
                //si identique on retourne le num lexico correspondant 
                return i;
            }
        }
        
        //si pas la meme longueur on passe directement au lexeme suivant de même hashcode
        i=table[i].suivant;
    }
    //sinon on renvoie -1
    return -1;
}

/**
 * @author MATHEVON Baptiste
 * @brief Affichage sur le terminal de la table des lexèmes
*/
void affichage_table_lexeme(){
    int i=0;
    printf("-- TABLE DES LEXEMES --\n");
    while(table[i].suivant!=0){
        printf("[%2d]|Long : %2d | Lexeme : %10s | Suiv : %d\n", i, table[i].longueur, table[i].lexeme, table[i].suivant);
        i++;
    }
}

/**
 * @author MATHEVON Baptiste
 * @brief Affichage sur le terminal de la table de hashcode
*/
void affichage_table_hashcode(){ 
    printf("-- TABLE DE HASHCODE --\n");
    for (int i=0; i<32; i++){
        printf("[%d] | %d\n", i, tab_hashcode[i]);
    }
}

/**
 * @author MATHEVON Baptiste
 * @brief Récupération du lexème associé à un certain numéro lexicographique
 * @param numero_lexico Numéro lexicographique dont on veut récupérer le lexème
 * @return char* : le lexème associé à ce numéro
*/
char * lexeme(int numero_lexico){
    return table[numero_lexico].lexeme;
}

