#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

/***************************/
/** Fonctions utilitaires **/
/***************************/

/**
 * @description: Affiche tous les champs d'un Livre.
 * @param: Un Livre l.
 * @return: None
 *
 * @pre: None
 * @post: None
 * @inv: l existe.
**/
void printBook(Livre l);

/**
 * @description: Transforme une ligne standardisée donée en un livre.
 * @param: Une chaine de caractère.
 * @return: Un livre avec les donées.
 *
 * @pre: line est différent de NULL
 * @post: Livre existe mais peux avoir des champs vides.
 * @inv: line existe.
**/
Livre parseElement(char* line);

/**
 * @description: Copie le contenu un livre l pour le retourner
 * @param: Un livre l
 * @return: None
 *
 * @pre: None
 * @post: Le livre retour est une copie parfaite de l
 * @inv: l existe
**/
Livre copyBook(Livre l);

/**
 * @description: Rècupère le livre de la 1ère ligne
 * @param: None
 * @return: Un livre.
 *
 * @pre: None
 * @post: Le retour existe mais peut être les champs peuvent être à NULL
 * @inv: None
**/
Livre getFirstElementOfFile();

/**
 * @description: Rècupère le livre de la dernière ligne
 * @param: None
 * @return: Un livre.
 *
 * @pre: None
 * @post: Le retour existe mais peut être les champs peuvent être à NULL.
 * @inv: None
**/
Livre getLastElementOfFile();

/**
 * @description: Renvoie la taille de la plus longue ligne du fichier.
 * @param: None
 * @return: Un entier compris entre 0 et 100 000.
 *
 * @pre: None
 * @post: le retour est compris entre 0 et 100 000.
 * @inv: None
**/
int maxSizeOfLine();

/**
 * @description: Renvoie le nombre de ligne du fichier.
 * @param: None
 * @return: Un entier supérieur ou égal à 0.
 *
 * @pre: None
 * @post: Le retour est supérieur ou égal à 0.
 * @inv:
**/
int numberOfLines();

/**
 * @description: Ouvre le fichier et renvoie le pointeur sur le fichier.
 * @param: None
 * @return: Un pointeur de type FILE*.
 *
 * @pre: None
 * @post: Le pointeur retourné est valide.
 * @inv: None
**/
FILE* openFile();

/**
 * @description: Libère la mémoire pointé par les pointeurs d'un livre.
 * @param: Un livre l.
 * @return: None
 *
 * @pre: l existe.
 * @post: None
 * @inv: None
**/
void detruireLivre(Livre l);

#endif // CORE_H_INCLUDED
