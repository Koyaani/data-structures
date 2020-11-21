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
 * @description: Transforme une ligne standardis�e don�e en un livre.
 * @param: Une chaine de caract�re.
 * @return: Un livre avec les don�es.
 *
 * @pre: line est diff�rent de NULL
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
 * @description: R�cup�re le livre de la 1�re ligne
 * @param: None
 * @return: Un livre.
 *
 * @pre: None
 * @post: Le retour existe mais peut �tre les champs peuvent �tre � NULL
 * @inv: None
**/
Livre getFirstElementOfFile();

/**
 * @description: R�cup�re le livre de la derni�re ligne
 * @param: None
 * @return: Un livre.
 *
 * @pre: None
 * @post: Le retour existe mais peut �tre les champs peuvent �tre � NULL.
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
 * @return: Un entier sup�rieur ou �gal � 0.
 *
 * @pre: None
 * @post: Le retour est sup�rieur ou �gal � 0.
 * @inv:
**/
int numberOfLines();

/**
 * @description: Ouvre le fichier et renvoie le pointeur sur le fichier.
 * @param: None
 * @return: Un pointeur de type FILE*.
 *
 * @pre: None
 * @post: Le pointeur retourn� est valide.
 * @inv: None
**/
FILE* openFile();

/**
 * @description: Lib�re la m�moire point� par les pointeurs d'un livre.
 * @param: Un livre l.
 * @return: None
 *
 * @pre: l existe.
 * @post: None
 * @inv: None
**/
void detruireLivre(Livre l);

#endif // CORE_H_INCLUDED
