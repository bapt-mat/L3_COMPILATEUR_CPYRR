#!/bin/bash

# Effacer l'écran
clear

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Erreur d'affectation d'une variable et une constante\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/affectation1_erreur.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Erreur d'affectation d'une variable et une fonction\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/affectation2_erreur.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Erreur d'affectation d'une variable et un tableau\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/affectation3_erreur.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e