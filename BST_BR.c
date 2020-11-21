#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "structure.h"
#include "core.h"
#include "BST.h"
#include "BST_BR.h"

/// Cf: http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx

int is_red(BST_RB_Bibliotheque root){

    return root != NULL && root->red == 1;
}

BST_RB_Bibliotheque jsw_single(BST_RB_Bibliotheque root, int direction){
/** Effectue une rotation **/
    BST_RB_Bibliotheque save = root->fils[!direction];

    root->fils[!direction] = save->fils[direction];
    save->fils[direction] = root;

    root->red = 1;
    save->red = 0;

    return save;
}

BST_RB_Bibliotheque jsw_double(BST_RB_Bibliotheque root, int direction){
/** Effectue une rotation dans un sens puis une autre dans le même sens **/
    root->fils[!direction] = jsw_single(root->fils[!direction], !direction);
    return jsw_single(root, direction);
}


int jsw_rb_assert(BST_RB_Bibliotheque root){
/** Vérifie si l'arbre RB est valide
    0 s'il n'est pas valide
    nombre de noeud noir sinon **/
    int lh, rh;

    if (root == NULL){
        return 1;
    } else {
        BST_RB_Bibliotheque ln = root->fils[0];
        BST_RB_Bibliotheque rn = root->fils[1];

        //Regarde si il y a une violation rouge:
        //Cad 2 noeuds rouges d'affilés
        if (is_red(root)) {
            if (is_red(ln) || is_red(rn)) {
                puts("Red violation");
                return 0;
            }
        }
        //Vérifie les fils
        lh = jsw_rb_assert(ln);
        rh = jsw_rb_assert(rn);

        //Vérifie si les règles d'un BST normale sont respéctées
        //Cad les valeurs des fils supérieurs ou inférieurs
        if ((ln != NULL && ln->livre.ISBN >= root->livre.ISBN) ||
            (rn != NULL && rn->livre.ISBN <= root->livre.ISBN)) {
            puts("Binary tree violation");
            return 0;
        }

        //Vérifie le nombre de noeud noir est bien égal dans chaques
        //branches
        if (lh != 0 && rh != 0 && lh != rh) {
            puts("Black violation");
            return 0;
        }

        // Compte le noueud noir si tous les tests on étés validés
        if (lh != 0 && rh != 0) {
            return is_red(root) ? lh : lh + 1;
        } else {
            return 0;
        }
    }
}

BST_RB_Bibliotheque make_node(Livre l){
    //Construit un arbre à un noeud
    BST_RB_Bibliotheque rn = malloc(sizeof (struct MaillonBstRbSt));
    assert(rn != NULL);

    rn->livre = copyBook(l);
    rn->red = 1; /* 1 is red, 0 is black */
    rn->fils[0] = NULL;
    rn->fils[1] = NULL;


    return rn;
}

BST_RB_Bibliotheque jsw_insert_r(BST_RB_Bibliotheque root, char* ISBN,
                                                            char* titre,
                                                            char* auteur,
                                                            char* editeur,
                                                            char* dateParution)
{
    Livre l = {ISBN, titre, auteur, editeur, dateParution};
    if (root == NULL) {
    //Il descend tout en bas
        root = make_node(l);
    } else if (strcmp(root->livre.ISBN, ISBN) != 0) {
    //Recursicité: Il redéfinit le lien parent fils
        int direction = strcmp(root->livre.ISBN, ISBN) > 0;

        root->fils[direction] = jsw_insert_r(root->fils[direction],
                                             l.ISBN, l.titre, l.auteur,
                                             l.editeur, l.dateParution);

        //Puis on équilibre le sous-arbre, enlève les violations rouges
        if (is_red(root->fils[direction])){
            if (is_red(root->fils[!direction])){
                /* Case 1 : Les 2 fils sont rouges */
                root->red = 1;
                root->fils[0]->red = 0;
                root->fils[1]->red = 0;
            } else {
                /* Cases 2 : Le fils du fils dans le même direction
                             est rouge */
                if (is_red(root->fils[direction]->fils[direction])){
                    root = jsw_single(root, !direction);
                /* & 3 : Le fils du fils dans l'autre direction est
                         rouge*/
                }else if (is_red(root->fils[direction]->fils[!direction])) {
                    root = jsw_double(root, !direction);
                }
            }
        }
    }
    //Puis il renvoye le nouvel arbre (ou sous arbre) avec le noeud
    //en plus et est équilibré
    return root;
}

BST_RB_Bibliotheque jsw_remove_r(BST_RB_Bibliotheque root, char* ISBN, int *done){

    if (root == NULL){
        *done = 1;
    } else {
        int direction;
        //Si on est sur le noeud à supprimer
        if (strcmp(root->livre.ISBN, ISBN) == 0) {
            //Si il a qu'un seul fils
            if (root->fils[0] == NULL || root->fils[1] == NULL) {
                //le fils de l'élément à supprimer du côté qui n'est pas NULL
                BST_RB_Bibliotheque save = root->fils[root->fils[0] == NULL];

                /* Case 0 : Si le noeud est rouge
                alors il fait rien, pas de viloation rouge ou noir */
                if (is_red(root)) {
                    *done = 1;
                /* Si le noeud d'après est rouge (donc le noeud courrant est noir)
                alors il suffit de tranformer les noeud d'avant en noir*/
                } else if (is_red(save)) {
                    save->red = 0;
                    *done = 1;
                }

                //Puis il libère le noeud
                detruireLivre(root->livre);
                free(root);

                //retourne le nouvel arbre équilibré
                return save;
            } else {
            //Si les fils contienent des sous arbres
            //Il supprime en prenant un livre plus petit (fils gauche)
                BST_RB_Bibliotheque heir = root->fils[0];

                while (heir->fils[1] != NULL)
                {
                    heir = heir->fils[1];
                }

                //root->data = heir->data;
                root->livre = copyBook(heir->livre);
                //data = heir->data;
                ISBN = heir->livre.ISBN;
            }
        }

        //dir = root->data < data;
        direction = strcmp(root->livre.ISBN, ISBN) > 0;
        //Puis il supprime le fils gauche
        root->fils[direction] = jsw_remove_r(root->fils[direction], ISBN, done);

        if (!*done)
        {
            root = jsw_remove_balance(root, direction, done);
        }
    }

    return root;
}

BST_RB_Bibliotheque jsw_remove_balance(BST_RB_Bibliotheque root,
                                        int dir, int *done) {
    BST_RB_Bibliotheque p = root;
    BST_RB_Bibliotheque s = root->fils[!dir];

    if (s != NULL && !is_red(s)) {
        /* Black sibling cases */
        if (!is_red(s->fils[0]) && !is_red(s->fils[1])) {
            if (is_red(p)) {
                *done = 1;
            }

            p->red = 0;
            s->red = 1;
        } else {
            int save = root->red;

            if (is_red(s->fils[!dir])) {
                p = jsw_single(p, dir);
            } else {
                p = jsw_double(p, dir);
            }

            p->red = save;
            p->fils[0]->red = 0;
            p->fils[1]->red = 0;
            *done = 1;
        }
    }
    else if (s->fils[dir] != NULL)
    {
        /* Red sibling cases */
        BST_RB_Bibliotheque r = s->fils[dir];

        if (!is_red(r->fils[0]) && !is_red(r->fils[1]))
        {
            p = jsw_single(p, dir);
            p->fils[dir]->fils[!dir]->red = 1;
        }
        else
        {
            if (is_red(r->fils[dir]))
            {
                s->fils[dir] = jsw_single(r, !dir);
            }

            p = jsw_double(p, dir);
            s->fils[dir]->red = 0;
            p->fils[!dir]->red = 1;
        }

        p->red = 0;
        p->fils[dir]->red = 0;
        *done = 1;
    }

    return p;
}

void BST_RB_detruire_bibliotheque( BST_RB_Bibliotheque b){
    BST_RB_detruire_bibliotheque_true(&b);
}

void BST_RB_detruire_bibliotheque_true( BST_RB_Bibliotheque* b) {
    if ( b != NULL && *b != NULL ) {
    //Si le pointeur de pointeur et le pointeur ne sont pas nuls
        //Il libère d'abord les nœuds inférieurs
        BST_RB_detruire_bibliotheque_true(&((*b)->fils[0]));
    	BST_RB_detruire_bibliotheque_true(&((*b)->fils[1]));
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

void BST_RB_printBibliotheque(BST_RB_Bibliotheque b, int current_level, int max_level){
    //Affichage en infixe pour un affichage vertical
    int i;
    if (b != NULL) {
    //Il construit la partie existente de l'arbre
        BST_RB_printBibliotheque(b->fils[1], current_level + 1, max_level);
        for (i = 0; i < current_level; i++) {
            printf("               ");
        }
        printf("%s\n", b->livre.ISBN);
        BST_RB_printBibliotheque(b->fils[0], current_level + 1, max_level);
    } else {
    //IL construit la partie inexistente de l'arbre
        if (current_level < max_level) {
            BST_RB_printBibliotheque(NULL, current_level + 1, max_level);
            for (i = 0; i < current_level; i++) {
                printf("               ");
            }
        printf("..\n");
        BST_RB_printBibliotheque(NULL, current_level + 1, max_level);
        }
    }
}

BST_RB_Bibliotheque BST_RB_extration(){
    FILE* file = openFile();
    //Aloue exactement la bonne taille pour lire toutes les lignes
    char* line = (char*)malloc(sizeof(char)*maxSizeLine);
    Livre l;
    //Il crée le BST qu'il retournera
    BST_RB_Bibliotheque b = NULL;
    while(fgets(line,maxSizeLine,file)!=NULL){ //lit une ligne
        l = parseElement(line);
        b = jsw_insert_r(b,l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
        free(l.ISBN);
        free(l.titre);
        free(l.auteur);
        free(l.editeur);
        free(l.dateParution);
        //Ferme le fichier et libère la chaine de caractères
    }
    fclose(file);
    file = NULL;
    free(line);
    line=NULL;
    return b;
}

int BST_RB_lenOf(BST_RB_Bibliotheque b){
    if(b == NULL){
        return 0;
    } else {
        return BST_RB_lenOf(b->fils[0]) + BST_RB_lenOf(b->fils[1]) + 1;
    }
}

int BST_RB_numberOfLeaves(BST_RB_Bibliotheque b){
    if (b == NULL){
        return 0;
    } else if (b->fils[0] == NULL && b->fils[1] == NULL){
        return 1;
    } else {
        int right = 0, left = 0;
        if (b->fils[1] != NULL) {
            right = BST_RB_numberOfLeaves(b->fils[1]);
        }
        if (b->fils[0] != NULL) {
            left = BST_RB_numberOfLeaves(b->fils[0]);
        }
        return left + right;
    }
}

int BST_RB_longestBranch(BST_RB_Bibliotheque b){
    if(b == NULL){
        return 0;
    } else {
        int sizeG = BST_RB_longestBranch(b->fils[0]);
        int sizeD = BST_RB_longestBranch(b->fils[1]);
        return ((sizeD > sizeG)? sizeD : sizeG)+1;
    }
}

int BST_RB_shortestBranch(BST_RB_Bibliotheque b){
    if(b == NULL){
        return 0;
    } else if (b->fils[0] == NULL && b->fils[1] == NULL) {
        return 1;
    } else {
        int right = 0, left = 0;
        if (b->fils[1] != NULL) {
            right = BST_RB_shortestBranch(b->fils[1]);
        }
        if (b->fils[0] != NULL) {
            left = BST_RB_shortestBranch(b->fils[0]);
        }
        return ((left < right)? left : right)+1;
    }
}
