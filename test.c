#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "core.h"
#include "CL.h"
#include "BST.h"
#include "BST_BR.h"
#include "HT.h"

/*******************/
/** Liste Chainée **/
/*******************/

///Tests basiques
void CL_test_creer_bibliotheque(){
    CL_Bibliotheque b = CL_creer_bibliotheque();
    printf("Test créer CL_creer_bibliotheque: %p\n", b);
    CL_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void CL_test_inserer(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    CL_Bibliotheque b = CL_creer_bibliotheque();
    printf("Insertion du livre\n");
    b = CL_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    printf("Affichage de la bibliothèque : \n");
    CL_printBibliotheque(b);
    CL_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void CL_test_supprimer(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    CL_Bibliotheque b = CL_creer_bibliotheque();
    printf("Insertion du livre\n");
    b = CL_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    printf("Affichage de la bibliothèque : \n");
    CL_printBibliotheque(b);
    printf("Suppression du livre\n");
    b = CL_supprimer(b, l.ISBN);
    printf("Affichage de la bibliothèque : \n");
    CL_printBibliotheque(b);
    CL_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void CL_test_rechercher_livre(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    CL_Bibliotheque b = CL_creer_bibliotheque(),
                    res = CL_creer_bibliotheque();
    res = CL_rechercher_livre(b, l.ISBN);
    printf("Affichage de la bibliothèque recherche : \n");
    CL_printBibliotheque(res);
    CL_detruire_bibliotheque(res);
    printf("Insertion du livre\n");
    b = CL_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    res = CL_rechercher_livre(b, l.ISBN);
    printf("Affichage de la bibliothèque recherche : \n");
    CL_printBibliotheque(res);
    CL_detruire_bibliotheque(res);
    CL_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void CL_test_rechercher_titre(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    CL_Bibliotheque b = CL_creer_bibliotheque(),
                    res = CL_creer_bibliotheque();
    res = CL_rechercher_titre(b, l.titre);
    printf("Affichage de la bibliothèque recherche : \n");
    CL_printBibliotheque(res);
    CL_detruire_bibliotheque(res);
    printf("Insertion du livre\n");
    b = CL_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    res = CL_rechercher_titre(b, l.titre);
    printf("Affichage de la bibliothèque recherche : \n");
    CL_printBibliotheque(res);
    CL_detruire_bibliotheque(b);
    CL_detruire_bibliotheque(res);
    printf("#######\n\n");
}

///Tests approfondis

CL_Bibliotheque CL_testInexistant(CL_Bibliotheque b){
/**Vérifie si les fonctions fonctionnent avec un ISBN inexstant**/
    CL_Bibliotheque recherche1, recherche2;

    printf("ISBN 'aaaaaaaaaa' existe ?: ");
    recherche1 = CL_rechercher_livre(b, "aaaaaaaaaa");
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Tentative de supression de 'aaaaaaaaaa'\n");
    b = CL_supprimer(b, "aaaaaaaaaa");
    printf("aaaaaaaaaa existe maintenant ?: ");
    recherche2 = CL_rechercher_livre(b, "aaaaaaaaaa");
    if (recherche2 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    CL_detruire_bibliotheque(recherche1);
    CL_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}

CL_Bibliotheque CL_testPremier(CL_Bibliotheque b){
/** Vérifie si les fonctions fonctionnent sur la 1ère entrée du fichier **/
    CL_Bibliotheque recherche1, recherche2, recherche3;

    ///Verifie la fonction recherche
    Livre firstBook = getFirstElementOfFile();
    printf("\nLe 1er livre du fichier '%s' existe ?: ", firstBook.ISBN);
    recherche1 = CL_rechercher_livre(b, firstBook.ISBN);
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }

    ///Verifie la fonction supprime
    printf("Tentative de supression du 1er livre\n");
    b = CL_supprimer(b, firstBook.ISBN);
    printf("Le 1er livre du fichier existe encore ?: ");
    recherche2 = CL_rechercher_livre(b, firstBook.ISBN);
    if (recherche2 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }

    ///Verifie la fonction insérer
    printf("Taille de la liste chainée : %d\n", CL_lenOf(b));
    printf("Insertion du 1er livre du fichier\n");
    b = CL_inserer(b, firstBook.ISBN, firstBook.titre, firstBook.auteur, firstBook.editeur, firstBook.dateParution);
    printf("Le 1er livre du fichier '%s' existe de nouveau ?: ", firstBook.ISBN);
    recherche3 = CL_rechercher_livre(b, firstBook.ISBN);
    if (recherche3 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }

    CL_detruire_bibliotheque(recherche1);
    CL_detruire_bibliotheque(recherche2);
    CL_detruire_bibliotheque(recherche3);

    detruireLivre(firstBook);

    printf("#######\n\n");

    return b;
}

CL_Bibliotheque CL_testDernier(CL_Bibliotheque b){
/** Vérifie si les fonctions fonctionnent sur la dernière entrée du fichier **/
    CL_Bibliotheque recherche1, recherche2;

    ///Verifie la fonction recherche
    Livre lastBook = getLastElementOfFile();
    printf("\nLe dernier livre du fichier '%s' existe ?: ", lastBook.ISBN);
    recherche1 = CL_rechercher_livre(b, lastBook.ISBN);
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }

    ///Verifie la fonction supprime
    printf("Tentative de supression du dernier livre\n");
    b = CL_supprimer(b, lastBook.ISBN);
    printf("Le dernier livre du fichier existe encore ?: ");
    recherche2 = CL_rechercher_livre(b, lastBook.ISBN);
    if (recherche2 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }

    detruireLivre(lastBook);
    CL_detruire_bibliotheque(recherche1);
    CL_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}

CL_Bibliotheque CL_testRechercheTitre(CL_Bibliotheque b){
///Test si la fonction recherche titre fonctionne
    CL_Bibliotheque recherche1;

    printf("\n'Babar et l' existe ?: ");
    recherche1 = CL_rechercher_titre(b, "Babar et l");
    if (recherche1 != NULL){
        printf("\nTaille de la liste chainée : %d\n", CL_lenOf(recherche1));
        CL_printBibliotheque(recherche1);
    } else {
        printf("0\n");
    }
    CL_detruire_bibliotheque(recherche1);

    printf("#######\n\n");

    return b;
}

CL_Bibliotheque CL_testRechercheTitreUnicite(CL_Bibliotheque b){
///Test si la fonction rechercher titre renvoye uniquement un seul livre du même titre
    CL_Bibliotheque recherche1, recherche2;

    ///Verifie si le livre n'existe pas
    printf("\nLe livre ayant pour titre 'Babar découvre l'éléctrostatique' existe ?:");
    recherche1 = CL_rechercher_titre(b, "Babar découvre l'éléctrostatique");
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }

    //Ajout de 2 livres avec le même titre
    Livre l1 = {"aaaaaaaaaa", "Babar découvre l'éléctrostatique", "Moi", "Moi", "2017"};
    Livre l2 = {"aaaaaaaaab", "Babar découvre l'éléctrostatique", "Moi", "Moi", "2017"};
    printf("Ajout de 2 livres ayant le même titre 'Babar découvre l'éléctrostatique'\n");
    b = CL_inserer(b, l1.ISBN, l1.titre, l1.auteur, l1.editeur, l1.dateParution);
    b = CL_inserer(b, l2.ISBN, l2.titre, l2.auteur, l2.editeur, l2.dateParution);

    //Effectue à nouveau la recherche
    recherche2 = CL_rechercher_titre(b, "Babar découvre l'éléctrostatique");
    printf("Le livre ayant pour titre 'Babar découvre l'éléctrostatique' existe ?:");
    if (recherche2 != NULL){
        //Et montre le nombre de noeuds retournés
        printf("\nTaille de la liste chainée resultante de la recherche : %d\n", CL_lenOf(recherche2));
        CL_printBibliotheque(recherche2);
    } else {
        printf("Non\n");
    }
    CL_detruire_bibliotheque(recherche1);
    CL_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}

int mainTest_CL(){
/** Regroupement des fonctions de test sur la liste chainée **/

    printf("\n\n\n\n\nTEST DE LA LISTE CHAINéE\n");

    CL_Bibliotheque b = CL_extration();

    printf("\nTaille de la liste chainée : %d\n\n", CL_lenOf(b));

    printf("### Tests simples ###\n\n");

    CL_test_creer_bibliotheque();
    CL_test_inserer();
    CL_test_supprimer();
    CL_test_rechercher_livre();
    CL_test_rechercher_titre();

    printf("### Tests approfondis ###\n\n");

    printf("Tests 'inexistant'\n");
    b = CL_testInexistant(b);

    printf("\nTaille de la liste chainée : %d\n", CL_lenOf(b)); //A segmenter
    printf("Tests 'premier'\n");
    b = CL_testPremier(b);

    printf("\nTaille de la liste chainée : %d\n", CL_lenOf(b));
    printf("Tests 'dernier'\n");
    b = CL_testDernier(b);

    printf("\nTaille de la liste chainée : %d\n", CL_lenOf(b));
    printf("Tests 'recherche'\n");
    b = CL_testRechercheTitre(b);

    printf("\nTaille de la liste chainée : %d\n", CL_lenOf(b));
    printf("Tests 'recherche unicité'\n");
    b = CL_testRechercheTitreUnicite(b);


    printf("\nNombre éléments finaux: %d\n\n", CL_lenOf(b));
    CL_detruire_bibliotheque(b);

    return 0;
}

///Tests basiques
void BST_test_creer_bibliotheque(){
    BST_Bibliotheque b = BST_creer_bibliotheque();
    printf("Test créer BST_creer_bibliotheque: %p\n", b);
    BST_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void BST_test_inserer(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    BST_Bibliotheque b = BST_creer_bibliotheque();
    printf("Insertion du livre\n");
    b = BST_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    printf("Affichage de la bibliothèque : \n");
    BST_printBibliotheque(b, 0, BST_longestBranch(b));
    BST_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void BST_test_supprimer(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    BST_Bibliotheque b = BST_creer_bibliotheque();
    printf("Insertion du livre\n");
    b = BST_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    printf("Affichage de la bibliothèque : \n");
    BST_printBibliotheque(b, 0, BST_longestBranch(b));
    printf("Suppression du livre\n");
    b = BST_supprimer(b, l.ISBN);
    printf("Affichage de la bibliothèque : \n");
    BST_printBibliotheque(b, 0, BST_longestBranch(b));
    BST_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void BST_test_rechercher_livre(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    BST_Bibliotheque b = BST_creer_bibliotheque(),
                    res = BST_creer_bibliotheque();
    res = BST_rechercher_livre(b, l.ISBN);
    printf("Affichage de la bibliothèque recherche : \n");
    BST_printBibliotheque(res, 0, BST_longestBranch(res));
    BST_detruire_bibliotheque(res);
    printf("Insertion du livre\n");
    b = BST_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    res = BST_rechercher_livre(b, l.ISBN);
    printf("Affichage de la bibliothèque recherche : \n");
    BST_printBibliotheque(res, 0, BST_longestBranch(res));
    BST_detruire_bibliotheque(res);
    BST_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void BST_test_rechercher_titre(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    BST_Bibliotheque b = BST_creer_bibliotheque(),
                    res = BST_creer_bibliotheque();
    res = BST_rechercher_titre(b, l.titre);
    printf("Affichage de la bibliothèque recherche : \n");
    BST_printBibliotheque(res, 0, BST_longestBranch(res));
    BST_detruire_bibliotheque(res);
    printf("Insertion du livre\n");
    b = BST_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    res = BST_rechercher_titre(b, l.titre);
    printf("Affichage de la bibliothèque recherche : \n");
    BST_printBibliotheque(res, 0, BST_longestBranch(res));
    BST_detruire_bibliotheque(b);
    BST_detruire_bibliotheque(res);
    printf("#######\n\n");
}

///Tests approfondis

void BST_testStat(BST_Bibliotheque b){
    printf("Taille de l'arbre : %d\n", BST_lenOf(b));
    printf("Nombre de feuilles: %d\n", BST_numberOfLeaves(b));
    printf("Nombre d'éléments dans la branche la plus courte: %d\n", BST_shortestBranch(b));
    printf("Nombre d'éléments dans la branche la plus longue: %d\n", BST_longestBranch(b));
    printf("#######\n\n");
}

BST_Bibliotheque BST_testInexistant(BST_Bibliotheque b){
/**Vérifie si les fonctions fonctionnent avec un ISBN inexstant**/
    BST_Bibliotheque recherche1, recherche2;

    printf("ISBN 'aaaaaaaaaa' existe ?: ");
    recherche1 = BST_rechercher_livre(b, "aaaaaaaaaa");
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Tentative de supression de 'aaaaaaaaaa'\n");
    b = BST_supprimer(b, "aaaaaaaaaa");
    printf("aaaaaaaaaa existe maintenant ?: ");
    recherche2 = BST_rechercher_livre(b, "aaaaaaaaaa");
    if (recherche2 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    BST_detruire_bibliotheque(recherche1);
    BST_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}

BST_Bibliotheque BST_testPremier(BST_Bibliotheque b){
    BST_Bibliotheque recherche1, recherche2, recherche3;

    ///1er
    Livre firstBook = getFirstElementOfFile();
    printBook(firstBook);

    printf("\n\nLe 1er livre du fichier '%s' existe ?: ", firstBook.ISBN);
    recherche1 = BST_rechercher_livre(b, firstBook.ISBN);
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Tentative de supression du 1er livre\n");
    b = BST_supprimer(b, firstBook.ISBN);
    printf("Le 1er livre du fichier existe encore ?: ");
    recherche2 = BST_rechercher_livre(b, firstBook.ISBN);
    if (recherche2 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Taille de l'arbre : %d\n", BST_lenOf(b));
    printf("Insertion du 1er livre du fichier\n");
    b = BST_inserer(b, firstBook.ISBN, firstBook.titre, firstBook.auteur, firstBook.editeur, firstBook.dateParution);
    printf("Le 1er livre du fichier '%s' existe de nouveau ?: ", firstBook.ISBN);
    recherche3 = BST_rechercher_livre(b, firstBook.ISBN);
    if (recherche3 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    BST_detruire_bibliotheque(recherche1);
    BST_detruire_bibliotheque(recherche2);
    BST_detruire_bibliotheque(recherche3);
    detruireLivre(firstBook);

    printf("#######\n\n");

    return b;
}

BST_Bibliotheque BST_testDernier(BST_Bibliotheque b){
    BST_Bibliotheque recherche1, recherche2;

    ///Dernier
    Livre lastBook = getLastElementOfFile();
    printf("\n\nLe dernier livre du fichier '%s' existe ?: ", lastBook.ISBN);
    recherche1 = BST_rechercher_livre(b, lastBook.ISBN);
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Tentative de supression du dernier livre\n");
    b = BST_supprimer(b, lastBook.ISBN);
    printf("Le dernier livre du fichier existe encore ?: ");
    recherche2 = BST_rechercher_livre(b, lastBook.ISBN);
    if (recherche2 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    detruireLivre(lastBook);
    BST_detruire_bibliotheque(recherche1);
    BST_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}

BST_Bibliotheque BST_testRechercheTitre(BST_Bibliotheque b){
    BST_Bibliotheque recherche1;

    ///Recherche par titre
    printf("\n'Babar et l' existe ?: ");
    recherche1 = BST_rechercher_titre(b, "Babar et l");
    if (recherche1 != NULL){
        printf("\nTaille de l'arbre : %d\n", BST_lenOf(recherche1));
        printf("Nombre de feuille: %d\n", BST_numberOfLeaves(recherche1));
        printf("Nombre d'éléments dans la branche la plus courte: %d\n", BST_shortestBranch(recherche1));
        printf("Nombre d'éléments dans la branche la plus longue: %d\n\n", BST_longestBranch(recherche1));
        BST_printBibliotheque(recherche1, 0, BST_longestBranch(recherche1));
    } else {
        printf("0\n");
    }
    BST_detruire_bibliotheque(recherche1);

    printf("#######\n\n");

    return b;
}

BST_Bibliotheque BST_testRechercheTitreUnicite(BST_Bibliotheque b){
    BST_Bibliotheque recherche1, recherche2;

    ///Test unicité
    printf("\nLe livre ayant pour titre 'Babar découvre l'éléctrostatique' existe ?:");
    recherche1 = BST_rechercher_titre(b, "Babar découvre l'éléctrostatique");
    if (recherche1 != NULL){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    Livre l1 = {"aaaaaaaaaa", "Babar découvre l'éléctrostatique", "Moi", "Moi", "2017"};
    Livre l2 = {"aaaaaaaaab", "Babar découvre l'éléctrostatique", "Moi", "Moi", "2017"};
    printf("Ajout de 2 livres ayant le même titre 'Babar découvre l'éléctrostatique'\n");
    b = BST_inserer(b, l1.ISBN, l1.titre, l1.auteur, l1.editeur, l1.dateParution);
    b = BST_inserer(b, l2.ISBN, l2.titre, l2.auteur, l2.editeur, l2.dateParution);
    recherche2 = BST_rechercher_titre(b, "Babar découvre l'éléctrostatique");
    printf("Le livre ayant pour titre 'Babar découvre l'éléctrostatique' existe ?:");
    if (recherche2 != NULL){
        printf("\nTaille de l'arbre : %d\n", BST_lenOf(recherche2));
        BST_printBibliotheque(recherche2, 0, BST_longestBranch(recherche2));
    } else {
        printf("Non\n");
    }
    BST_detruire_bibliotheque(recherche1);
    BST_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}


int mainTest_BST() {

    printf("\n\n\n\n\nTEST DE L'ARBRE BINAIRE DE RECHERCHE\n");

    BST_Bibliotheque b = BST_extration();

    BST_testStat(b);

    printf("### Tests simples ###\n\n");

    BST_test_creer_bibliotheque();
    BST_test_inserer();
    BST_test_supprimer();
    BST_test_rechercher_livre();
    BST_test_rechercher_titre();

    printf("### Tests approfondis ###\n\n");

    b = BST_testInexistant(b);

    printf("Taille de l'arbre : %d\n", BST_lenOf(b));
    b = BST_testPremier(b);

    printf("Taille de l'arbre : %d\n", BST_lenOf(b));
    b = BST_testDernier(b);

    printf("Taille de l'arbre : %d\n", BST_lenOf(b));
    b = BST_testRechercheTitre(b);

    printf("Taille de l'arbre : %d\n", BST_lenOf(b));
    b = BST_testRechercheTitreUnicite(b);

    printf("\nNombre éléments finaux: %d\n\n", BST_lenOf(b));

    BST_detruire_bibliotheque(b);

    return 0;
}

///Tests basiques
void HT_test_creer_bibliotheque(){
    HT_Bibliotheque b = HT_creer_bibliotheque();
    printf("Test créer HT_creer_bibliotheque: %p\n", b);
    HT_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void HT_test_inserer(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    HT_Bibliotheque b = HT_creer_bibliotheque();
    printf("Insertion du livre\n");
    b = HT_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    printf("Affichage de la bibliothèque : \n");
    HT_printBibliotheque(b);
    HT_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void HT_test_supprimer(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    HT_Bibliotheque b = HT_creer_bibliotheque();
    printf("Insertion du livre\n");
    b = HT_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    printf("Affichage de la bibliothèque : \n");
    HT_printBibliotheque(b);
    printf("Suppression du livre\n");
    b = HT_supprimer(b, l.ISBN);
    printf("Affichage de la bibliothèque : \n");
    HT_printBibliotheque(b);
    HT_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void HT_test_rechercher_livre(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    HT_Bibliotheque b = HT_creer_bibliotheque(),
                    res = HT_creer_bibliotheque();
    res = HT_rechercher_livre(b, l.ISBN);
    printf("Affichage de la bibliothèque recherche : \n");
    HT_printBibliotheque(res);
    HT_detruire_bibliotheque(res);
    printf("Insertion du livre\n");
    b = HT_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    res = HT_rechercher_livre(b, l.ISBN);
    printf("Affichage de la bibliothèque recherche : \n");
    HT_printBibliotheque(res);
    HT_detruire_bibliotheque(res);
    HT_detruire_bibliotheque(b);
    printf("#######\n\n");
}

void HT_test_rechercher_titre(){
    Livre l = {"ISBN", "titre", "auteur", "editeur", "date parution"};
    HT_Bibliotheque b = HT_creer_bibliotheque(),
                    res = HT_creer_bibliotheque();
    res = HT_rechercher_titre(b, l.titre);
    printf("Affichage de la bibliothèque recherche : \n");
    HT_printBibliotheque(res);
    HT_detruire_bibliotheque(res);
    printf("Insertion du livre\n");
    b = HT_inserer(b, l.ISBN, l.titre, l.auteur, l.editeur, l.dateParution);
    res = HT_rechercher_titre(b, l.titre);
    printf("Affichage de la bibliothèque recherche : \n");
    HT_printBibliotheque(res);
    HT_detruire_bibliotheque(b);
    HT_detruire_bibliotheque(res);
    printf("#######\n\n");
}

///Tests approfondis

void HT_testStat(HT_Bibliotheque b){
    printf("Nombre de cases vides : %d\n", HT_nbreNULL(b));
    printf("Moyenne de la taille de la liste chainée quand\n");
    printf("elle n'est pas vide: %f\n", HT_moyenneNoeud(b));
    printf("#######\n\n");
}

HT_Bibliotheque HT_testInexistant(HT_Bibliotheque b){
    HT_Bibliotheque recherche1, recherche2;

    ///Inexistant
    printf("ISBN 'aaaaaaaaaa' existe ?: ");
    recherche1 = HT_rechercher_livre(b, "aaaaaaaaaa");
    if (!HT_empty(recherche1)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Tentative de supression de 'aaaaaaaaaa'\n");
    b = HT_supprimer(b, "aaaaaaaaaa");
    printf("aaaaaaaaaa existe maintenant ?: ");
    recherche2 = HT_rechercher_livre(b, "aaaaaaaaaa");
    if (!HT_empty(recherche2)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    HT_detruire_bibliotheque(recherche1);
    HT_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}

HT_Bibliotheque HT_testPremier(HT_Bibliotheque b){
    HT_Bibliotheque recherche1, recherche2, recherche3;

    ///1er
    Livre firstBook = getFirstElementOfFile();
    printf("\n\nLe 1er livre du fichier '%s' existe ?: ", firstBook.ISBN);
    recherche1 = HT_rechercher_livre(b, firstBook.ISBN);
    if (!HT_empty(recherche1)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Tentative de supression du 1er livre\n");
    b = HT_supprimer(b, firstBook.ISBN);
    printf("Le 1er livre du fichier existe encore ?: ");
    recherche2 = HT_rechercher_livre(b, firstBook.ISBN);
    if (!HT_empty(recherche2)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Taille de la liste chainée : %d\n", HT_lenOf(b));
    printf("Insertion du 1er livre du fichier\n");
    b = HT_inserer(b, firstBook.ISBN, firstBook.titre, firstBook.auteur, firstBook.editeur, firstBook.dateParution);
    printf("Le 1er livre du fichier '%s' existe de nouveau ?: ", firstBook.ISBN);
    recherche3 = HT_rechercher_livre(b, firstBook.ISBN);
    if (!HT_empty(recherche3)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Taille de l'arbre : %d\n", HT_lenOf(b));
    HT_detruire_bibliotheque(recherche1);
    HT_detruire_bibliotheque(recherche2);
    HT_detruire_bibliotheque(recherche3);
    detruireLivre(firstBook);

    printf("#######\n\n");

    return b;
}

HT_Bibliotheque HT_testDernier(HT_Bibliotheque b){
    HT_Bibliotheque recherche1, recherche2;

    ///Dernier
    Livre lastBook = getLastElementOfFile();
    printf("\n\nLe dernier livre du fichier '%s' existe ?: ", lastBook.ISBN);
    recherche1 = HT_rechercher_livre(b, lastBook.ISBN);
    if (HT_empty(recherche1)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Tentative de supression du dernier livre\n");
    b = HT_supprimer(b, lastBook.ISBN);
    printf("Le dernier livre du fichier existe encore ?: ");
    recherche2 = HT_rechercher_livre(b, lastBook.ISBN);
    if (HT_empty(recherche2)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    printf("Nombre d'éléments dans la table : %d\n", HT_lenOf(b));
    detruireLivre(lastBook);
    HT_detruire_bibliotheque(recherche1);
    HT_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}

HT_Bibliotheque HT_testRechercheTitre(HT_Bibliotheque b){
    HT_Bibliotheque recherche1;

    ///Recherche par titre
    printf("\n'Babar et l' existe ?: ");
    recherche1 = HT_rechercher_titre(b, "Babar et l");
    if (!HT_empty(recherche1)){
        printf("\nTaille de la liste chainée : %d\n", HT_lenOf(recherche1));
        HT_printBibliotheque(recherche1);
    } else {
        printf("0\n");
    }
    HT_detruire_bibliotheque(recherche1);

    printf("#######\n\n");

    return b;
}

HT_Bibliotheque HT_testRechercheTitreUnicite(HT_Bibliotheque b){
    HT_Bibliotheque recherche1, recherche2;

    ///Test unicité
    printf("\nLe livre ayant pour titre 'Babar découvre l'éléctrostatique' existe ?:");
    recherche1 = HT_rechercher_titre(b, "Babar découvre l'éléctrostatique");
    if (!HT_empty(recherche1)){
        printf("Oui\n");
    } else {
        printf("Non\n");
    }
    Livre l1 = {"aaaaaaaaaa", "Babar découvre l'éléctrostatique", "Moi", "Moi", "2017"};
    Livre l2 = {"aaaaaaaaab", "Babar découvre l'éléctrostatique", "Moi", "Moi", "2017"};

    printf("Ajout de 2 livres ayant le même titre 'Babar découvre l'éléctrostatique'\n");
    b = HT_inserer(b, l1.ISBN, l1.titre, l1.auteur, l1.editeur, l1.dateParution);
    b = HT_inserer(b, l2.ISBN, l2.titre, l2.auteur, l2.editeur, l2.dateParution);

    recherche2 = HT_rechercher_titre(b, "Babar découvre l'éléctrostatique");

    printf("Le livre ayant pour titre 'Babar découvre l'éléctrostatique' existe ?:");

    if (!HT_empty(recherche2)){
        printf("\nTaille de la liste chainée : %d\n", HT_lenOf(recherche2));
        HT_printBibliotheque(recherche2);
    } else {
        printf("Non\n");
    }

    HT_detruire_bibliotheque(recherche1);
    HT_detruire_bibliotheque(recherche2);

    printf("#######\n\n");

    return b;
}


int mainTest_HT() {

    HT_Bibliotheque b = HT_extraction();
    printf("\n\n\n\n\nTEST DE LA TABLE DE HASHAGE\n");

    printf("### Tests simples ###\n\n");

    HT_test_creer_bibliotheque();
    HT_test_inserer();
    HT_test_supprimer();
    HT_test_rechercher_livre();
    HT_test_rechercher_titre();

    printf("### Tests approfondis ###\n\n");

    HT_testStat(b);

    b = HT_testInexistant(b);

    printf("Nombres d'éléments dans la table : %d\n", HT_lenOf(b));
    b = HT_testPremier(b);

    printf("Nombre d'éléments dans la table : %d\n", HT_lenOf(b));
    b = HT_testDernier(b);

    printf("Nombre d'éléments dans la table : %d\n", HT_lenOf(b));
    b = HT_testRechercheTitre(b);

    printf("Nombre d'éléments dans la table : %d\n", HT_lenOf(b));
    b = HT_testRechercheTitreUnicite(b);

    printf("\nNombre éléments finaux: %d\n\n", HT_lenOf(b));

    HT_detruire_bibliotheque(b);


    return 0;
}

void testDiffBetweenBST_BSTRB(){
    BST_Bibliotheque b1 = BST_extration();
    printf("Arbre non équilibré : \n\n");
    printf("Taille de l'arbre : %d\n", BST_lenOf(b1));
    printf("Nombre de feuilles: %d\n", BST_numberOfLeaves(b1));
    printf("Nombre d'éléments dans la branche la plus courte: %d\n", BST_shortestBranch(b1));
    printf("Nombre d'éléments dans la branche la plus longue: %d\n\n\n", BST_longestBranch(b1));
    BST_detruire_bibliotheque(b1);
    BST_RB_Bibliotheque b2 = BST_RB_extration();
    printf("Arbre non équilibré : \n\n");
    printf("Taille de l'arbre : %d\n", BST_RB_lenOf(b2));
    printf("Nombre de feuilles: %d\n", BST_RB_numberOfLeaves(b2));
    printf("Nombre d'éléments dans la branche la plus courte: %d\n", BST_RB_shortestBranch(b2));
    printf("Nombre d'éléments dans la branche la plus longue: %d\n\n\n", BST_RB_longestBranch(b2));
    BST_RB_detruire_bibliotheque(b2);

}

void testParseElement(){
    char line[] = "10|titre|auteur|editeur|date";
    Livre l = parseElement(line);
    printBook(l);
    detruireLivre(l);
}

void testFirstLastElement(){
    printf("First book:\n");
    Livre book1 = getFirstElementOfFile();
    Livre book2 = getLastElementOfFile();
    printBook(book1);
    printf("\n\nLast book:\n");
    printBook(book2);
    detruireLivre(book1);
    detruireLivre(book2);
}

void testNumberOfLines(){
    int number = numberOfLines();
    printf("Nombre de lignes dans le fichier : %d\n\n", number);
}
