#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "structure.h"
#include "core.h"
#include "CL.h"
#include "HT.h"

/***************************/
/** Fonctions Principales **/
/***************************/

HT_Bibliotheque HT_creer_bibliotheque(){
    HT_Bibliotheque b = (HT_Bibliotheque)malloc(sizeof(struct TableHSt));

    int i;
    for(i = 0; i < SIZE; i++){
        b->table[i] = NULL;
    }
    return b;
}

int HT_empty(HT_Bibliotheque b){
    int i;
    for(i = 0; i < SIZE; i++){
        if (b->table[i] != NULL){
            return 0;
        }
    }
    return 1;
}

HT_Bibliotheque HT_inserer(HT_Bibliotheque b,
                              char* ISBN,
                              char* titre,
                              char* auteur,
                              char* editeur,
                              char* dateParution){
    assert(ISBN != NULL);
    assert(strlen(ISBN) != 0);

    int key = GetKey(ISBN);
    //Insère l'élément dans la liste chainée à l'emplacement "key"
    b->table[key] = CL_inserer(b->table[key], ISBN, titre, auteur,
                editeur, dateParution);
    return b;
}

HT_Bibliotheque HT_supprimer(HT_Bibliotheque b, char* ISBN){

    assert(ISBN != NULL);
    assert(strlen(ISBN) != 0);

    int key = GetKey(ISBN);
    //Supprime l'élement dans la liste chainée à l'emplacement
    //où il est supposé être
    b->table[key] = CL_supprimer(b->table[key], ISBN);
    return b;
}

HT_Bibliotheque HT_rechercher_livre(HT_Bibliotheque b, char* ISBN){

    assert(ISBN != NULL);
    assert(strlen(ISBN) != 0);

    int key = GetKey(ISBN);
    //Cherche l'élement dans la liste chainée à l'emplacement
    //où il est supposé être
    CL_Bibliotheque tmp = CL_rechercher_livre(b->table[key],
                                                ISBN);
    HT_Bibliotheque res = HT_creer_bibliotheque();

    //Et l'insère dans une table de hashage
    if(tmp != NULL){
        Livre l = tmp->livre;
        res = HT_inserer(res, l.ISBN, l.titre, l.auteur, l.editeur,
                                                            l.dateParution);
    }
    //Détruit la liste chainée temporaire (puisque les donées sont
    //copiées lors de l'insertion)
    CL_detruire_bibliotheque(tmp);

    return res;
}

HT_Bibliotheque HT_rechercher_titre(HT_Bibliotheque b, char* prefixe){

    assert(prefixe != NULL);
    assert(strlen(prefixe) != 0);

    int i;
    HT_Bibliotheque res = HT_creer_bibliotheque();
    for(i = 0; i < SIZE; i++){
    //Parcours l'entièreté de la table
        CL_Bibliotheque tmp;
        tmp = CL_rechercher_titre(b->table[i], prefixe);
        //Récupère pour chaque liste chainée les livres trouvées
        if (tmp != NULL){
            //Et les insères dans la table si le titre n'existe pas encore
            Livre l = tmp->livre;
            if (HT_notExist(res, l.titre)){
                res = HT_inserer(res, l.ISBN, l.titre, l.auteur,
                                            l.editeur, l.dateParution);
            }
        }
        CL_detruire_bibliotheque(tmp);
    }
    return res;
}

void HT_detruire_bibliotheque(HT_Bibliotheque b){
    int i;
    if (b != NULL){
        for(i=0; i<SIZE; i++){
        //Parcourt toute la table pour libérer toutes les listes chainées
            CL_detruire_bibliotheque(b->table[i]);
            b->table[i] = NULL;
        }
        //puis libère la table
        free(b);
    }
}

/***************************/
/** Fonctions utilitaires **/
/***************************/

void HT_printBibliotheque(HT_Bibliotheque b){
    int i;
    CL_Bibliotheque lc_b;
    printf("\nSTART HT:");

    for(i=0 ; i<SIZE; i++){
        lc_b = b->table[i];
        if (lc_b != NULL){
            printf("\nPointer: %p\n", lc_b);
            CL_printBibliotheque(lc_b);
        }
    }
    printf("END\n");
    printf("\n");
}

int HT_notExist(HT_Bibliotheque b, char* titre){

    assert(titre != NULL);
    assert(strlen(titre) != 0);

    int i;
    if (b != NULL){
        for(i = 0; i < SIZE; i++){
        //Parcours toutes la listes à la recherche d'un livre ayant le même
        //titre
            if (CL_notExist(b->table[i], titre) == 0 ){
                return 0;
            }
        }
    }
    return 1;
}

int GetKey(char* ISBN){

    assert(ISBN != NULL);
    assert(strlen(ISBN) != 0);

    unsigned long hash = 0;
    int c=*ISBN;
    while (c != '\0'){
    //Passe tous les caractères dan sla fonction de hash
        //Ajoute la valeur de c puis décale de 6 bit le le hash et de
        //16 bits - le hash
        //Cf: http://www.cse.yorku.ca/~oz/hash.html
        hash = c + (hash << 6) + (hash << 16) - hash;
        ISBN++;
        c= *ISBN;
    }
    //Puis récupère le modulo pour éviter les nombres
    //supérieur ou égale à SIZE

    return hash%SIZE;
}

int HT_lenOf(HT_Bibliotheque b){
    int i, len = 0;
    for(i=0; i<SIZE; i++){
        len = len + CL_lenOf(b->table[i]);
    }
    return len;
}

int HT_nbreNULL(HT_Bibliotheque b){
    int i, nbreNULL = 0;
    for(i=0; i<SIZE; i++){
        if (b->table[i] == NULL){
            nbreNULL++;
        }
    }
    return nbreNULL;
}

float HT_moyenneNoeud(HT_Bibliotheque b){
    int i, moyenne = 0, n = 0;
    for(i=0; i<SIZE; i++){
        if (b->table[i] != NULL){
           moyenne = moyenne + CL_lenOf(b->table[i]);
           n++;
        }
    }
    return (float)moyenne/n;
}

HT_Bibliotheque HT_extraction(){
    FILE* file = openFile();
    char* line = (char*)malloc(sizeof(char)*maxSizeLine);
    Livre l;
    HT_Bibliotheque res = HT_creer_bibliotheque();
    int i = 0;

    while(fgets(line, maxSizeLine, file) != NULL){ //read each line of file
        i++;
        l = parseElement(line);
        res = HT_inserer(res,
                    l.ISBN, l.titre, l.auteur, l.editeur,
                                                    l.dateParution);
        detruireLivre(l);
    }
    fclose(file);
    file = NULL;
    free(line);
    line = NULL;
    return res;
}

