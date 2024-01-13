#!/bin/bash

# Effacer l'écran
clear

printf "\n\n--------------------------------------------------------------\n\n"


# Message d'introduction avec printf
printf "Erreur du type indice (float).\n\n"


# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/erreur_indice1.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Erreur du type indice (char).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/erreur_indice2.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Erreur du type indice (fonction qui retourne un float).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/erreur_indice3.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"

# Message d'introduction avec printf
printf "Erreur du type indice (bool).\n\n"

# Chemin vers le compilateur et le fichier à compiler
compilateur="./compilateur"
fichier="./programmes/ozan_prog_erreur_warning/erreur_indice4.cp"

# Exécuter la commande avec l'option -e
$compilateur $fichier -e

printf "\n\n--------------------------------------------------------------\n\n"
