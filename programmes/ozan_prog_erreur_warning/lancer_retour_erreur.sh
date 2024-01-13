#!/bin/bash

# Effacer l'écran
clear

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Erreur sur le retour d'une fonction (int -> float).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/retour_fct_erreur1.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Erreur sur le retour d'une fonction (char -> int).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/retour_fct_erreur2.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Erreur sur le retour d'une fonction (char -> float).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/retour_fct_erreur3.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"
