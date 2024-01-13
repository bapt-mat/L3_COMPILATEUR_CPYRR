#!/bin/bash

# Effacer l'écran
clear

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Erreur de comparaison entre deux tableaux\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_bool_erreur1.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Erreur de comparaison entre une variable et un tableau\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_bool_erreur2.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Erreur de comparaison entre un tableau et une fonction\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_bool_erreur3.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Erreur de comparaison entre deux fonctions\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/exp_bool_erreur4.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"
