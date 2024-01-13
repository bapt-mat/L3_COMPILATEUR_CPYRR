** Compilateur pour le langage CPYRR **

- Définition d'une syntaxe, sémantique pour le langage CPYRR
- Analyse syntaxique, sémantique et remplissages des tables lexico., de déclarations, etc...
- Transformation du code CPYRR en arbre abstrait d'instructions
- Lecture de l'arbre abstrait via la pile a l'éxécution (Machine Virtuelle)

Makefile : 
make : création de l'éxécutable
make clean : nettoyage

Executable : 
./compilateur <programmes/sous-dossier/nom_du_prog.cp> <-t (affich. tables)> <-a (affich. arbres)> <-p (affich.pile)> <-e (execution du programme)>
