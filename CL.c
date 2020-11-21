#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "structure.h"
#include "core.h"
#include "CL.h"

/***************************/
/** Fonctions Principales **/
/***************************/

CL_Bibliotheque CL_creer_bibliotheque(){
    //Retourne un pointeur à NULL du type CL_Bibliotheque
    return NULL;
}

CL_Bibliotheque CL_inserer(CL_Bibliotheque b, char* ISBN, char* titre, char* auteur, char* editeur, char* dateParution) {
    assert(ISBN != NULL);
    assert(strlen(ISBN) != 0);

    //Créer le noeud à ajouter
    CL_Bibliotheque res = (CL_Bibliotheque)malloc(sizeof(struct MaillonClSt));

    //Met les donées dans un livre
    Livre l;
    l.ISBN = ISBN;
    l.titre = titre;
    l.auteur = auteur;
    l.editeur = editeur;
    l.dateParution = dateParution;

    //Fait une copie des donées
    res->livre = copyBook(l);

    //Et l'insère au début du fichier
    res->suivant = b;
    b = res;

    return b;
}

CL_Bibliotheque CL_supprimer(CL_Bibliotheque b, char* ISBN){
    assert(ISBN != NULL);
    assert(strlen(ISBN) != 0);

    CL_Bibliotheque res = CL_creer_bibliotheque();
    if (b != NULL){
        if (b->suivant == NULL){
        // Si dans la chaine, il y a qu'un seul élément, il renvoie NULL
            CL_detruire_bibliotheque(b);
            return res;
        } else if (strcmp(ISBN, b->livre.ISBN) == 0){
        // Si il est placer sur le noeud à supprimer
            //Retourne le noeud suivant en libérant le noeud courrant
            CL_Bibliotheque res = b->suivant;
            b->suivant = NULL;
            CL_detruire_bibliotheque(b);
            return res;
        } else {
            /*for(res = b; res->suivant != NULL; res = res->suivant){
            //Sinon on parcourt la chaine jusqu'à être sur le bon noeud
                if (strcmp(ISBN, res->suivant->livre.ISBN) == 0){
                    CL_Bibliotheque tmp = res->suivant;
                    res->suivant = res->suivant->suivant;
                    tmp->suivant = NULL;
                    CL_detruire_bibliotheque(tmp);
                    CL
                    return b;
                }
            }
            */
            for(res = b; res->suivant != NULL; res = res->suivant){
            //Sinon on parcourt la chaine jusqu'à être sur le bon noeud
                if (strcmp(ISBN, res->suivant->livre.ISBN) == 0){
                //Une fois qu'il est bien placé, il rappelle la fonction
                //pour qu'il supprime le noeud courrant.
                    res->suivant = CL_supprimer(res->suivant, ISBN);
                    return b;
                }
            }
        }
    }
    return b;
}



CL_Bibliotheque CL_rechercher_livre(CL_Bibliotheque b, char* ISBN){
    assert(ISBN != NULL);
    assert(strlen(ISBN) != 0);

    CL_Bibliotheque res = CL_creer_bibliotheque();
    for(; b != NULL; b = b->suivant){
    //Il parcourt toute la liste à la recherche du livre ayant le même
    //ISBN
        if (strcmp(ISBN, b->livre.ISBN) == 0){
            Livre l = b->livre;
            //Il insère les données dans la biliothèque res
            res = CL_inserer(res, l.ISBN, l.titre, l.auteur, l.editeur,
                                                        l.dateParution);
            return res;
        }
    }
    //Sinon renvoye NULL
    return res;
}

CL_Bibliotheque CL_rechercher_titre(CL_Bibliotheque b, char* prefixe){
    assert(prefixe != NULL);
    assert(strlen(prefixe) != 0);

    CL_Bibliotheque res = CL_creer_bibliotheque();
    for(; b != NULL; b = b->suivant){
    //On parcourt l'entièreté de la liste
        if (strncmp(prefixe, b->livre.titre, strlen(prefixe)) == 0 &&
            (CL_notExist(res, b->livre.titre) == 1)){
        //Et ajoute le livre a la bibliothèque res si le prefixe existe
        //dans le titre et si le titre n'existe pas déja dans res
            res = CL_inserer(res, b->livre.ISBN,
                            b->livre.titre,
                            b->livre.auteur,
                            b->livre.editeur,
                            b->livre.dateParution);
        }
    }
    return res;
}

void CL_detruire_bibliotheque(CL_Bibliotheque b){
    CL_Bibliotheque tmp = NULL;
    while(b != NULL){
    //Il va tout au bout de la liste chainée en libérant au fur et à mesure

        //lie le pointeur avec l'élément suivant en conservant
        //celui d'avant pour le libérer
        tmp = b;
        b = b->suivant;

        free(tmp->livre.ISBN);
        free(tmp->livre.titre);
        free(tmp->livre.auteur);
        free(tmp->livre.editeur);
        free(tmp->livre.dateParution);
        free(tmp);
    }
}

/***************************/
/** Fonctions utilitaires **/
/***************************/

void CL_printBibliotheque(CL_Bibliotheque b){
    printf("CL:\n");
    for(; b != NULL; b = b->suivant){
        printBook(b->livre);
        printf("\n");
    }
    printf("\n");
}

int CL_notExist(CL_Bibliotheque b, char* titre){
    assert(titre != NULL);
    assert(strlen(titre) != 0);

    if (b == NULL){
        return 1;
    } else if (strcmp(titre, b->livre.titre) == 0) {
        return 0;
    } else {
        return CL_notExist(b->suivant, titre);
    }
}

int CL_lenOf(CL_Bibliotheque b){
    int i = 0;
    for(; b != NULL; b = b->suivant){
        i++;
    }
    return i;
}

CL_Bibliotheque CL_extration(){
    FILE* file = openFile();
    char* line = (char*)malloc(sizeof(char)*maxSizeLine);
    Livre l;
    CL_Bibliotheque res = CL_creer_bibliotheque();
    int i = 0;
    while(fgets(line, maxSizeLine, file) != NULL){ //read each line of file
        i++;
        l = parseElement(line);
        res = CL_inserer(res,
                    l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
        detruireLivre(l);
    }
    fclose(file);
    file = NULL;
    free(line);
    line = NULL;

    return res;
}
