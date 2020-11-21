#ifndef BST_BR_H_INCLUDED
#define BST_BR_H_INCLUDED

int is_red(BST_RB_Bibliotheque root);
BST_RB_Bibliotheque jsw_single(BST_RB_Bibliotheque root, int direction);
BST_RB_Bibliotheque jsw_double(BST_RB_Bibliotheque root, int direction);
int jsw_rb_assert(BST_RB_Bibliotheque root);
BST_RB_Bibliotheque make_node(Livre l);
BST_RB_Bibliotheque jsw_insert_r(BST_RB_Bibliotheque root, char* ISBN,
                                                            char* titre,
                                                            char* auteur,
                                                            char* editeur,
                                                            char* dateParution);
BST_RB_Bibliotheque jsw_remove_r(BST_RB_Bibliotheque root, char* ISBN, int *done);
void BST_RB_printBibliotheque(BST_RB_Bibliotheque b, int current_level, int max_level);
void BST_RB_detruire_bibliotheque( BST_RB_Bibliotheque b);
void BST_RB_detruire_bibliotheque_true( BST_RB_Bibliotheque* b);
BST_RB_Bibliotheque jsw_remove_balance(BST_RB_Bibliotheque root, int dir, int *done);

int BST_RB_shortestBranch(BST_RB_Bibliotheque b);
int BST_RB_longestBranch(BST_RB_Bibliotheque b);
int BST_RB_numberOfLeaves(BST_RB_Bibliotheque b);

BST_RB_Bibliotheque BST_RB_extration();
int BST_RB_lenOf(BST_RB_Bibliotheque b);

#endif // BST_BR_H_INCLUDED
