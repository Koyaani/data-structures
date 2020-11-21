#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

void CL_test_creer_bibliotheque();
void CL_test_inserer();
void CL_test_supprimer();
void CL_test_rechercher_livre();
void CL_test_rechercher_titre();

CL_Bibliotheque CL_testInexistant(CL_Bibliotheque b);
CL_Bibliotheque CL_testPremier(CL_Bibliotheque b);
CL_Bibliotheque CL_testDernier(CL_Bibliotheque b);
CL_Bibliotheque CL_testRechercheTitre(CL_Bibliotheque b);
CL_Bibliotheque CL_testRechercheTitreUnicite(CL_Bibliotheque b);

int mainTest_CL();


void BST_test_creer_bibliotheque();
void BST_test_inserer();
void BST_test_supprimer();
void BST_test_rechercher_livre();
void BST_test_rechercher_titre();

BST_Bibliotheque BST_testInexistant(BST_Bibliotheque b);
BST_Bibliotheque BST_testPremier(BST_Bibliotheque b);
BST_Bibliotheque BST_testDernier(BST_Bibliotheque b);
BST_Bibliotheque BST_testRechercheTitre(BST_Bibliotheque b);
BST_Bibliotheque BST_testRechercheTitreUnicite(BST_Bibliotheque b);

int mainTest_BST();


void HT_test_creer_bibliotheque();
void HT_test_inserer();
void HT_test_supprimer();
void HT_test_rechercher_livre();
void HT_test_rechercher_titre();

HT_Bibliotheque HT_testInexistant(HT_Bibliotheque b);
HT_Bibliotheque HT_testPremier(HT_Bibliotheque b);
HT_Bibliotheque HT_testDernier(HT_Bibliotheque b);
HT_Bibliotheque HT_testRechercheTitre(HT_Bibliotheque b);
HT_Bibliotheque HT_testRechercheTitreUnicite(HT_Bibliotheque b);

int mainTest_HT();


void testFirstLastElement();
void testDiffBetweenBST_BSTRB();
#endif // TEST_H_INCLUDED
