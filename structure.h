#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#define SIZE 10000000

extern int maxSizeLine;

/*
 * Structure pour les livre
 * Champs : ISBN - pointeur de caractères contenant dans un maillon
 *          auteur - pointeur de caractères contenant l'Auteur
 *          editeur - pointeur de caractères contenant l'Editeur
 *          date - valeur entiere represantant da la date au format AAAAMMJJ
 *          suivant - pointeur vers le maillon suivant de la liste
 */
struct LivreSt {
	char* ISBN;
	char* titre;
	char* auteur;
	char* editeur;
	char* dateParution;
};
typedef struct LivreSt Livre;

/*
 * Structure pour les listes chainées (CL)
 * Champs : Livre - livre contenant les donées du noeud
 *          suivant - pointeur pointant sur le noeud suivant
 */
struct MaillonClSt {
	Livre livre;
	struct MaillonClSt * suivant;
};
typedef struct MaillonClSt * CL_Bibliotheque;

/*
 * Structure pour les arbres binaires de recherche (BST)
 * Champs : Livre - livre contenant les donées du noeud
 *          fils - tableau de pointeur pointant sur les fils
 */
struct MaillonBstSt {
	Livre livre;
	struct MaillonBstSt * fils[2];
	//Une autre solution permettant de fusionner les cas symetriques
};
typedef struct MaillonBstSt * BST_Bibliotheque;

/*
 * Structure pour les arbres binaires de recherche rouges et noirs (BST_RB)
 * Champs : Livre - livre contenant les donées du noeud
 *          red - int contenant la couleur du noeud (1 = rouge et 0 = noir)
 *          fils - tableau de pointeur pointant sur les fils
 */
struct MaillonBstRbSt {
	Livre livre;
	int red;
	struct MaillonBstRbSt * fils[2];
	//Une autre solution permettant de fusionner les cas symetriques
};
typedef struct MaillonBstRbSt * BST_RB_Bibliotheque;

/*
 * Structure pour la table de hashage (HT)
 * Champs : table[] - tableau de pointeur de type CL_Bibliothque
 */
struct TableHSt {
	CL_Bibliotheque table[SIZE];
};
typedef struct TableHSt * HT_Bibliotheque;

#endif // STRUCTURE_H_INCLUDED
