#!/bin/bash

# Effacer l'écran
clear

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Addition entre une constante (int) et une constante (float).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_arith_erreur1.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Soustraction entre une constante (int) et une variable (float).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_arith_erreur2.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Multiplication entre un retour de fonction (int) et une variable (float).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_arith_erreur3.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Division entre un tableau (int) et une constante (float).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_arith_erreur4.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"
