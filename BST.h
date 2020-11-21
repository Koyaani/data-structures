#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

/********************/
/** Main functions **/
/********************/

/**
 * @description: Créer une bibliothèque vide (un pointeur NULL).
 * @param: None
 * @return: Un BST vide.
 *
 * @pre: None
 * @post: Le retour BST_Bibliotheque existe.
 * @inv: None
**/
BST_Bibliotheque BST_creer_bibliotheque();

/**
 * @description: Insère un "livre" (ISBN, titre, auteur, editeur, dateParution)
 *      dans l'arbre b
 * @param: b un arbre recuillant l'insersion; ISBN, titre, auteur, editeur,
 *      dateParution; des chaines de caractères
 * @return: Un BST avec le "livre" en plus.
 *
 * @pre: ISBN est non nul et n'existe pas encore dans b;
 * @post: le retour BST_Bibliotheque existe.
 * @inv: Les champs du livre existent (ISBN, titre, auteur, editeur, dateParution)
 *      et b existe.
**/
BST_Bibliotheque BST_inserer(BST_Bibliotheque b,
                              char* ISBN,
                              char* titre,
                              char* auteur,
                              char* editeur,
                              char* dateParution);

/**
 * @description: Supprime un élément dans le BST en fonction de l'existence de
 *        l'ISBN donné.
 * @param: b un arbre où sera supprimé l'élement, ISBN une chaine de caractères.
 * @return: Un BST avec possiblement un élement en moins.
 *
 * @pre: ISBN n'est pas NULL.
 * @post: Le retour existe.
 * @inv: ISBN et b existent
**/
BST_Bibliotheque BST_supprimer(BST_Bibliotheque b, char* ISBN);

/**
 * @description: Recherche et retourne un arbre en fonction de son ISBN
 * @param: Un BST ou sera faite la recherhche, ISBN une chaine de caractère
 *      utilisé pour la recherche.
 * @return: un BST contenant si la recherche est fructueuse l'element recherché
 *      sinon NULL
 *
 * @pre: ISBN n'est pas NULL
 * @post: le retour existe
 * @inv: ISBN et b existent
**/
BST_Bibliotheque BST_rechercher_livre(BST_Bibliotheque b, char* ISBN);

/**
 * @description: Recherche et retourne un arbre en fonction de son titre.
 * @param: Un BST où sera faite la recherhche, prefixe une chaine de caractère
 *      utilisé pour la recherche.
 * @return: un BST contenant si la recherche est fructueuse les elements recherchés
 *      sinon NULL.
 *
 * @pre: titre n'est pas NULL
 * @post: le retour existe
 * @inv: ISBN et b existent
**/
BST_Bibliotheque BST_rechercher_titre(BST_Bibliotheque b, char* prefixe);

/**
 * @description: Gère la compabilité entre la fonction demandé et la fonction
 *      faite pour "BST_detruire_bibliotheque".
 * @param: Un BST quelconque.
 * @return: None
 *
 * @pre: b existe
 * @post: None
 * @inv: None
**/
void BST_detruire_bibliotheque(BST_Bibliotheque b);

/**
 * @description: Libère la mémoire de l'arbre b.
 * @param: Un pointeur sur le pointeur pointant sur un BST.
 * @return: None
 *
 * @pre: b existe.
 * @post: b est à NULL
 * @inv: None
**/
void BST_detruire_bibliotheque_true( BST_Bibliotheque* b);

/****************************/
/** Complementary Fuctions **/
/****************************/

/**
 * @description: Extrait les donées du fichier pour les insérer dans un BST.
 * @param: None
 * @return: Un BST avec les donées insérer correctement dedans.
 *
 * @pre: None
 * @post: Le BST de retour existe.
 * @inv: None
**/
BST_Bibliotheque BST_extration();

/**
 * @description: Fusione 2 arbres en verifiant l'unicité du nom
 *      (ne le rajoute pas si il existe déja.).
 * @param: b1, un arbre recuillant la fuision, b2 un arbre.
 * @return: Un arbre créer de la fusion de 2 arbres.
 *
 * @pre: None
 * @post: le retour existe.
 * @inv: b1 et b2 existent.
**/
BST_Bibliotheque BST_fusionWithUniqueness(BST_Bibliotheque b1,
                                         BST_Bibliotheque b2);

/**
 * @description: Affiche un arbre horizontalement.
 * @param: b un BST, current_level est la hauteur de l'arbre à laquelle on
 *      veut commencer à l'affciher et max_level est la hauteur de l'arbre.
 * @return: None
 *
 * @pre: current_level inférieur ou égale à max_level.
 * @post:
 * @inv: b existe.
**/
void BST_printBibliotheque(BST_Bibliotheque b, int current_level, int max_level);

/**
 * @description: Retourne le livre du plus petit élement de l'arbre.
 * @param: Un BST b.
 * @return: Un livre (type Livre).
 *
 * @pre: b est non vide.
 * @post: Livre existe et est non NULL.
 * @inv: b existe.
**/
Livre BST_ISBNMini(BST_Bibliotheque b);

/**
 * @description: Renvoie 1 si le livre existe PAS et 0 si le livre existe.
 * @param: Un arbre BST b et une chaine de caractères qui sera rechercher.
 * @return: Soit 0 soit 1.
 *
 * @pre: None
 * @post: le retour est un booléen.
 * @inv: b et titre existent.
**/
int BST_notExist(BST_Bibliotheque b, char* titre);

/**
 * @description: Donne la taille de l'arbre.
 * @param: Un BST b.
 * @return: Le nombre de noeuds de l'arbre donée.
 *
 * @pre: None
 * @post: le retour est un int.
 * @inv: L'arbre b existe.
**/
int BST_lenOf(BST_Bibliotheque b);

/**
 * @description: Donne le nombre de feuilles d'un arbre.
 * @param: Un BST b.
 * @return: Un entier donnant le nombre de feuilles.
 *
 * @pre:
 * @post: le retour est un entier.
 * @inv: b existe.
**/
int BST_numberOfLeaves(BST_Bibliotheque b);

/**
 * @description: Donne la longueur de la plus longue branche de l'arbre donné.
 * @param: Un BST b.
 * @return: Le nombre de noeud dans la plus longue branche.
 *
 * @pre: None
 * @post: le retour est un entier
 * @inv: b existe
**/
int BST_shortestBranch(BST_Bibliotheque b);

/**
 * @description: Donne la longueur de la plus courte branche de l'arbre donné.
 * @param: Un BST b.
 * @return: Le nombre de noeud dans la plus courte branche.
 *
 * @pre: None
 * @post: le retour est un entier.
 * @inv: b existe.
**/
int BST_longestBranch(BST_Bibliotheque b);

#endif // BST_H_INCLUDED
