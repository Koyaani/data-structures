#ifndef HT_H_INCLUDED
#define HT_H_INCLUDED

/********************/
/** Main functions **/
/********************/

int HT_empty(HT_Bibliotheque b);
/**
 * @description: Créer la table de pointeur et la met complètement à NULL.
 * @param: Une HT.
 * @return: La HT initialisée
 *
 * @pre: None
 * @post: Une HT initialisée
 * @inv: None
**/
HT_Bibliotheque HT_creer_bibliotheque();

/**
 * @description: Insère un "livre" (ISBN, titre, auteur, editeur, dateParution)
 *  dans b.
 * @param: Une HT b et un "livre" (ISBN, titre, auteur, editeur, dateParution).
 * @return: Une HT avec le "livre" en plus.
 *
 * @pre: ISBN est non nul et n'existe pas encore dans b.
 * @post: le retour HT_Bibliotheque existe.
 * @inv: Les champs du livre existent (ISBN, titre, auteur, editeur, dateParution)
    et b existe.
**/
HT_Bibliotheque HT_inserer(HT_Bibliotheque b,
                              char* ISBN,
                              char* titre,
                              char* auteur,
                              char* editeur,
                              char* dateParution);

/**
 * @description: Supprime un élément dans la HT en fonction de l'existence de
 *  ISBN.
 * @param: Une HT ou sera faite la suppression et un ISBN qui sera le selecteur.
 * @return: Une HT avec possiblement un élement en moins.
 *
 * @pre: ISBN n'est pas NULL.
 * @post: Le retour existe.
 * @inv: ISBN et b existent.
**/
HT_Bibliotheque HT_supprimer(HT_Bibliotheque b, char* ISBN);

/**
 * @description: Recherche et retourne une HT en fonction de son ISBN.
 * @param: Une HT ou sera faite la recherche et un ISBN qui sera le selecteur.
 * @return: une HT contenant si la recherche est fructueuse l'element recherché
 *  sinon NULL.
 *
 * @pre: ISBN n'est pas NULL.
 * @post: le retour existe.
 * @inv: ISBN et b existent.
**/
HT_Bibliotheque HT_rechercher_livre(HT_Bibliotheque b, char* ISBN);

/**
 * @description: Recherche et retourne tous les livres possédante le prefixe
 *      dans une HT.
 * @param: Une HT ou sera faite la recherche et un prefixe qui sera le selecteur.
 * @return: une HT contenant si la recherche est fructueuse l'element recherché
 *  sinon NULL.
 *
 * @pre: titre n'est pas NULL
 * @post: le retour existe.
 * @inv: ISBN et b existent.
**/
HT_Bibliotheque HT_rechercher_titre(HT_Bibliotheque b, char* prefixe);

/**
 * @description: Libère la mémoire de la table b.
 * @param: Une HT b.
 * @return: None
 *
 * @pre: b existe.
 * @post: None
 * @inv: None
**/
void HT_detruire_bibliotheque(HT_Bibliotheque b);

/*********************/
/** Other functions **/
/*********************/

/**
 * @description: Affiche le contenu d'une table de hashage
 * @param: Une HT b
 * @return: None

 * @pre:
 * @post:
 * @inv: b existe.
**/
void HT_printBibliotheque(HT_Bibliotheque b);

/**
 * @description: Vérifie l'inexistence d'un titre dans une HT.
 * @param: une HT b et une chaine de caractère titre.
 * @return: 0 si il existe et 1 sinon.
 *
 * @pre: titre est different de NULL.
 * @post: le retour est un entier.
 * @inv: b et titre existent.
**/
int HT_notExist(HT_Bibliotheque b, char* titre);

/**
 * @description: Retourne le hash (key) en focntion du ISBN
 * @param: une chaine de caractères ISBN
 * @return: le hash contenu dans un int
 *
 * @pre: ISBN est different de NULL
 * @post: le hash (int) existe et est inférieur à SIZE
 * @inv: ISBN existe
**/
int GetKey(char* ISBN);

/**
 * @description: Extrait les donées du fichier pour les mettre dans une HT.
 * @param: None
 * @return: Une HT initialisée avec les valeurs dedans.
 *
 * @pre: None
 * @post: Une HT initialisée.
 * @inv: None
**/
HT_Bibliotheque HT_extraction();

int HT_lenOf(HT_Bibliotheque b);
int HT_nbreNULL(HT_Bibliotheque b);
float HT_moyenneNoeud(HT_Bibliotheque b);

#endif // HT_H_INCLUDED
