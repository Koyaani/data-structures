#ifndef CL_H_INCLUDED
#define CL_H_INCLUDED

/***************************/
/** Fonctions Principales **/
/***************************/

/**
@description: Créer une bibliothèque vide (pointeur NULL).
@param: None
@return: Une CL vide.

@pre: None
@post: Le retour CL_Bibliotheque existe.
@inv: None
**/
CL_Bibliotheque CL_creer_bibliotheque();

/**
@description: Insère un "livre" (ISBN, titre, auteur, editeur, dateParution)
    dans b
@param: Une CL b et des chaines de caractères
@return: Une CL avec le "livre" en plus.

@pre: ISBN est non nul et n'existe pas encore dans b;
@post: le retour CL_Bibliotheque existe.
@inv: Les champs du livre existent (ISBN, titre, auteur, editeur, dateParution)
    et b existe.
**/
CL_Bibliotheque CL_inserer(CL_Bibliotheque b, char* ISBN, char* titre, char* auteur, char* editeur, char* dateParution);

/**
@description: Supprime un élément dans la CL en fonction de l'existence de
    ISBN dans celle ci.
@param: une CL b et une chaine de caractères
@return: Une CL avec possiblement un élement en moins.

@pre: ISBN n'est pas NULL.
@post: Le retour existe.
@inv: ISBN et b existent
**/
CL_Bibliotheque CL_supprimer(CL_Bibliotheque b, char* ISBN);

/**
@description: Recherche et retourne un nœud en fonction de son ISBN
@param: Une CL b et une chaine de caractères
@return: Une CL contenant si la recherche est fructueuse l'element recherché
    sinon NULL

@pre: ISBN n'est pas NULL
@post: le retour existe
@inv: ISBN et b existent
**/
CL_Bibliotheque CL_rechercher_livre(CL_Bibliotheque b, char* ISBN);

/**
@description: Recherche et retourne une CL en fonction de son titre
@param: Une CL b et une chaine de caractères
@return: Une CL contenant si la recherche est fructueuse l'element recherché
    sinon NULL

@pre: titre n'est pas NULL
@post: le retour existe
@inv: ISBN et b existent
**/
CL_Bibliotheque CL_rechercher_titre(CL_Bibliotheque b, char* prefixe);

/**
@description: Libère la mémoire de la liste chainee b.
@param: Une CL b
@return: None

@pre: b existe.
@post: None
@inv: None
**/
void CL_detruire_bibliotheque(CL_Bibliotheque b);

/***************************/
/** Fonctions utilitaires **/
/***************************/

/**
 * @description: Affiche les élements d'une liste chainée
 * @param: Une CL b
 * @return: None
 *
 * @pre: None
 * @post: None
 * @inv: b existe.
**/
void CL_printBibliotheque(CL_Bibliotheque b);

/**
 * @description: Renvoie 1 si le livre existe PAS et 0 si le livre existe.
 * @param: Une CL b et une chaine de caractères qui sera rechercher.
 * @return: Soit 0 soit 1.
 *
 * @pre: titre est différent de NULL
 * @post: le retour est un booléen.
 * @inv: b et titre existent.
**/
int CL_notExist(CL_Bibliotheque b, char* titre);

/**
 * @description: Donne la taille de la liste chainée.
 * @param: Une CL b.
 * @return: Le nombre de noeuds de la CL donée.
 *
 * @pre: None
 * @post: le retour est un int.
 * @inv: b existe.
**/
int CL_lenOf(CL_Bibliotheque b);

/**
 * @description: Extrait les donées du fichier pour les insérer dans une CL.
 * @param: None
 * @return: Une CL avec les donées insérer correctement dedans.
 *
 * @pre: None
 * @post: La CL de retour existe.
 * @inv: None
**/
CL_Bibliotheque CL_extration();

#endif // CL_H_INCLUDED
