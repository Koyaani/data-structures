# Initiation aux structures de données en C

Ce dépot contient le code du projet sur les structures de données. Il a été réalisé en L2 (2017) durant une semaine.

La compilation se fait simplement avec :

    gcc -Wall -g  *.c -o output

## Structures

Les structures implémentées sont :
 * **CL** pour *Chained List*
 * **HT** pour *Hashed Table*
 * **BST** pour *Bynary Search Tree*

Chacune est définis dans le .c et .h du même nom. L'ensemble des tests sont effectués dans *test.c*.

## Dataset

La construction de la structure se fait à partir du fichier *test.dat*, contenant 500 lignes. C'est une petite version d'un dataset plus grand contenant plus de 700 000 entrées. Il faut indiquer le nom du fichier de données dans *core.c*

Les lignes sont structurés comme suit :

    ISBN | Titre | Auteur | Éditeur | Date de publication

## BST BR

Avec le temps restant, j'ai commencé à prendre en main une implémentation d'un *Binary Search Tree Black and Red*. Cet algorithme permet de ne pas avoir un arbre dégénéré (une branche bien plus longue que la plus petite.
