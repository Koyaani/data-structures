#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "structure.h"
#include "core.h"
#include "CL.h"
#include "BST.h"


/***************************/
/** Fonctions Principales **/
/***************************/

BST_Bibliotheque BST_creer_bibliotheque(){
    return NULL;
}

BST_Bibliotheque BST_inserer(BST_Bibliotheque b,
                             char* ISBN,
                             char* titre,
                             char* auteur,
                             char* editeur,
                             char* dateParution){

    assert(ISBN != NULL);
    assert(strlen(ISBN));

    //Le nouveau nœud est ajouté en tant que feuille (cad au bout de l'arbre)
    if (b == NULL){
        b = (BST_Bibliotheque)malloc(sizeof(struct MaillonBstSt));

        Livre l;
        l.ISBN = ISBN;
        l.titre = titre;
        l.auteur = auteur;
        l.editeur = editeur;
        l.dateParution = dateParution;

        b->livre= copyBook(l);

        b->fils[0] = NULL;
        b->fils[1] = NULL;


    //Sinon, si ce n'est pas une feuille, il descend
    } else{
        // Vrai -> il va a droite sinon gauche
        int side = strcmp(ISBN, b->livre.ISBN) > 0;
        b->fils[side] = BST_inserer(b->fils[side], ISBN, titre, auteur, editeur, dateParution);
    }
    //Il renvoie l'arbre avec le nœud ajouté
    //Il redefinie chaque fils à leur parent lors du retour de récursivité
    return b;
}

BST_Bibliotheque BST_supprimer(BST_Bibliotheque b, char* ISBN){
    assert(ISBN != NULL);
    assert(strlen(ISBN));

    /// Cas ou l'arbre est vide, il ne se passe rien
    if (b == NULL){
        return b;
    }
    ///Placement sur l'element à supprimer si on y est pas
    if (strcmp(ISBN, b->livre.ISBN) != 0){
        // Si la condition est vrai, il va à droite sinon à gauche
        int side = strcmp(ISBN, b->livre.ISBN) > 0;
        b->fils[side] = BST_supprimer(b->fils[side], ISBN);
    } else {
    ///Supression de l'element courant
        //Si un seul fils ou aucun, il utilise la méthode de décalage
        if (b->fils[0] == NULL) {
            //Il revoie le nœud suivant (NULL si aucun fils)
            ///Doit-on libérer le nœud à NULL ???
            BST_Bibliotheque tmp = b->fils[1];
            b->fils[0] = NULL;
            b->fils[1] = NULL;
            BST_detruire_bibliotheque(b);
            return tmp;
        } else if (b->fils[1] == NULL) {
            BST_Bibliotheque tmp = b->fils[0];
            b->fils[0] = NULL;
            b->fils[1] = NULL;
            BST_detruire_bibliotheque(b);
            return tmp;
        }

        //Si 2 fils, il prend la valeur la plus petite du sous arbre droit
        Livre l = BST_ISBNMini(b->fils[1]);
        b->livre = copyBook(l);
        //L'élement est forcement à droite vu qu'il l'a cherché à droite
        b->fils[1] = BST_supprimer(b->fils[1], l.ISBN);
    }
    //Il redefinie chaque fils à leur parent lors du retour de récursivité
    //Il renvoie l'arbre avec le nœud supprimé
    return b;
}

BST_Bibliotheque BST_rechercher_livre(BST_Bibliotheque b, char* ISBN){
    assert(ISBN != NULL);
    assert(strlen(ISBN));

    if (b == NULL){
    //Si l'arbre est NULL, il a donc rien trouvé, il renvoie un arbre vide
        return BST_creer_bibliotheque();
    } else if (strcmp(ISBN, b->livre.ISBN) == 0) {
    //Si l'iSBN courant est le même, il récupère le livre et arrète la
    //récursivité étant donné que le livre est unique car l'ISBN est unique
        BST_Bibliotheque res = (BST_Bibliotheque)malloc(sizeof(struct MaillonBstSt));
        res->fils[0] = NULL;
        res->fils[1] = NULL;
        res->livre = copyBook(b->livre);
        return res;

    } else {
    //En fonction de la valeur resultante ed la condition, il va à gauche ou à
    //droite
        int side = (strcmp(ISBN, b->livre.ISBN) > 0);
        return BST_rechercher_livre(b->fils[side], ISBN);
    }
}

BST_Bibliotheque BST_rechercher_titre(BST_Bibliotheque b, char* titre){
    assert(titre != NULL);
    assert(strlen(titre));

    BST_Bibliotheque res = BST_creer_bibliotheque();
    if (b == NULL){
    //Si l'arbre est NULL, il a donc rien trouvé, il renvoie un arbre vide
        return res;
    } else if (strncmp(b->livre.titre, titre, strlen(titre)) == 0 &&
               BST_notExist(res, b->livre.titre)){
    //Si il trouve la valeur, il récupère le livre
        res = BST_inserer(res ,b->livre.ISBN, b->livre.titre, b->livre.auteur,
                               b->livre.editeur, b->livre.dateParution);
    }
    //Ne sachant pas de quel côté se trouve les autre livres, il va des 2 côtés
    //Il récupère à chaque fois les arbres
    BST_Bibliotheque res1 = BST_rechercher_titre(b->fils[0], titre);
    BST_Bibliotheque res2 = BST_rechercher_titre(b->fils[1], titre);

    //POur les fusioner en enlevant les doublons
    res = BST_fusionWithUniqueness(res, res1);
    res = BST_fusionWithUniqueness(res, res2);

    BST_detruire_bibliotheque(res1);
    BST_detruire_bibliotheque(res2);

    return res;
}

/***************************/
/** Fonctions utilitaires **/
/***************************/

Livre BST_ISBNMini(BST_Bibliotheque b){
    //Il va toujours plus à gauche pour trouver la valeur minimale de l'arbre
    //qui est sur une feuille
    if(b->fils[0] == NULL){
        return b->livre;
    } else {
        return BST_ISBNMini(b->fils[0]);
    }
}

BST_Bibliotheque BST_extration(){
    FILE* file = openFile();
    //Aloue exactement la bonne taille pour lire toutes les lignes
    char* line = (char*)malloc(sizeof(char)*maxSizeLine);
    Livre l;
    //Il crée le BST qu'il retournera
    BST_Bibliotheque b = BST_creer_bibliotheque();
    while(fgets(line,maxSizeLine,file)!=NULL){ //lit une ligne
        l = parseElement(line);
        b = BST_inserer(b,l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
        free(l.ISBN);
        free(l.titre);
        free(l.auteur);
        free(l.editeur);
        free(l.dateParution);
    }
    //Ferme le fichier et libère la chaine de caractères
    fclose(file);
    file = NULL;
    free(line);
    line=NULL;
    return b;
}

BST_Bibliotheque BST_fusionWithUniqueness(BST_Bibliotheque b1, BST_Bibliotheque b2){
    if (b2 == NULL){
    //Si b2 est vide, il n'y a rien à faire
        return b1;
    } else {
        b1 = BST_fusionWithUniqueness(b1, b2->fils[0]);
        b1 = BST_fusionWithUniqueness(b1, b2->fils[1]);
        if (BST_notExist(b1, b2->livre.titre)){
            Livre l = b2->livre;
            b1 = BST_inserer(b1, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
        }
        return b1;
    }
}

void BST_detruire_bibliotheque( BST_Bibliotheque b){
    BST_detruire_bibliotheque_true(&b);
}

void BST_detruire_bibliotheque_true( BST_Bibliotheque* b) {
    if ( b != NULL && *b != NULL ) {
    //Si le pointeur de pointeur et le pointeur ne sont pas nuls
        //Il libère d'abord les nœuds inférieurs

        BST_detruire_bibliotheque_true(&((*b)->fils[0]));
    	BST_detruire_bibliotheque_true(&((*b)->fils[1]));
        //avant de se libérer
        free((*b)->livre.ISBN);
        free((*b)->livre.titre);
        free((*b)->livre.auteur);
        free((*b)->livre.editeur);
        free((*b)->livre.dateParution);
    	free(*b);
        //Il met directement le pointeur à NULL
        *b = NULL;
	}
}

int BST_notExist(BST_Bibliotheque b, char* titre){
    assert(titre != NULL);
    assert(strlen(titre));

    if (b == NULL){
        return 1;
    } else if (strcmp(titre, b->livre.titre) == 0) {
        return 0;
    } else {
        return BST_notExist(b->fils[0], titre) && BST_notExist(b->fils[1], titre);
    }
}

int BST_lenOf(BST_Bibliotheque b){
    if(b == NULL){
        return 0;
    } else {
        return BST_lenOf(b->fils[0]) + BST_lenOf(b->fils[1]) + 1;
    }
}

int BST_numberOfLeaves(BST_Bibliotheque b){
    if (b == NULL){
        return 0;
    } else if (b->fils[0] == NULL && b->fils[1] == NULL){
        return 1;
    } else {
        int right = 0, left = 0;
        if (b->fils[1] != NULL) {
            right = BST_numberOfLeaves(b->fils[1]);
        }
        if (b->fils[0] != NULL) {
            left = BST_numberOfLeaves(b->fils[0]);
        }
        return left + right;
    }
}

int BST_longestBranch(BST_Bibliotheque b){
    if(b == NULL){
        return 0;
    } else {
        int sizeG = BST_longestBranch(b->fils[0]);
        int sizeD = BST_longestBranch(b->fils[1]);
        return ((sizeD > sizeG)? sizeD : sizeG)+1;
    }
}

int BST_shortestBranch(BST_Bibliotheque b){
    if(b == NULL){
        return 0;
    } else if (b->fils[0] == NULL && b->fils[1] == NULL) {
        return 1;
    } else {
        int right = 0, left = 0;
        if (b->fils[1] != NULL) {
            right = BST_shortestBranch(b->fils[1]);
        }
        if (b->fils[0] != NULL) {
            left = BST_shortestBranch(b->fils[0]);
        }
        return ((left < right)? left : right)+1;
    }
}

void BST_printBibliotheque(BST_Bibliotheque b, int current_level, int max_level){
    //Affichage en infixe pour un affichage vertical
    assert(current_level <= max_level);

    int i;
    if (b != NULL) {
    //Il construit la partie existente de l'arbre
        BST_printBibliotheque(b->fils[1], current_level + 1, max_level);
        for (i = 0; i < current_level; i++) {
            printf("               ");
        }
        printf("%s\n", b->livre.ISBN);
        BST_printBibliotheque(b->fils[0], current_level + 1, max_level);
    } else {
    //IL construit la partie inexistente de l'arbre
        if (current_level < max_level) {
            BST_printBibliotheque(NULL, current_level + 1, max_level);
            for (i = 0; i < current_level; i++) {
                printf("               ");
            }
        printf("..\n");
        BST_printBibliotheque(NULL, current_level + 1, max_level);
        }
    }
}
