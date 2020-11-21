#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "structure.h"
#include "core.h"

void printBook(Livre l){
    printf( "ISBN: %s.\n", l.ISBN);
    printf( "Titre: %s.\n", l.titre);
    printf( "Auteur: %s.\n", l.auteur);
    printf( "Editeur: %s.\n", l.editeur);
    printf( "DateParution: %s.\n\n", l.dateParution);
}

Livre parseElement(char* line){
    assert(line != NULL);
    assert(strlen(line) != 0);


    const char s[2] = "|";
    char *token;

    Livre l;

    //Prend les chaines de caractères entre chaque caractère "s"
    //Et le stocke dans une chaine de caractère à la taille du token
    // pour finalement copier dans le livre de retour
    token = strtok(line, s);
    l.ISBN = (char*)malloc(sizeof(char)*(strlen(token)+1));
    assert(l.ISBN != NULL);
    strcpy(l.ISBN, token);

    token = strtok(NULL, s);
    l.titre = (char*)malloc(sizeof(char)*(strlen(token)+1));
    assert(l.titre != NULL);
    strcpy(l.titre, token);

    token = strtok(NULL, s);
    l.auteur = (char*)malloc(sizeof(char)*(strlen(token)+1));
    assert(l.auteur != NULL);
    strcpy(l.auteur, token);

    token = strtok(NULL, s);
    l.editeur = (char*)malloc(sizeof(char)*(strlen(token)+1));
    assert(l.editeur != NULL);
    strcpy(l.editeur, token);

    token = strtok(NULL, s);
    token[strlen(token)-1] = '\0';
    l.dateParution = (char*)malloc(sizeof(char)*(strlen(token)+1));
    assert(l.dateParution != NULL);
    strcpy(l.dateParution, token);


    return l;
}

Livre copyBook(Livre l){

        Livre newBook;

        //Prend chaque champs d'un livre pour les réallouer dans un nouveau
        //livre

        newBook.ISBN = (char*)malloc(sizeof(char)*(strlen(l.ISBN)+1));
        strcpy(newBook.ISBN, l.ISBN);

        newBook.titre = (char*)malloc(sizeof(char)*(strlen(l.titre)+1));
        strcpy(newBook.titre, l.titre);

        newBook.auteur = (char*)malloc(sizeof(char)*(strlen(l.auteur)+1));
        strcpy(newBook.auteur, l.auteur);

        newBook.editeur = (char*)malloc(sizeof(char)*(strlen(l.editeur)+1));
        strcpy(newBook.editeur, l.editeur);

        newBook.dateParution = (char*)malloc(sizeof(char)*(strlen(l.dateParution)+1));
        strcpy(newBook.dateParution, l.dateParution);

        return newBook;
}

Livre getFirstElementOfFile(){
    //Ouvre le fichier puis lit la 1ère ligne puis le ferme
    FILE* file = openFile();
    Livre l;
    char* line = (char*)malloc(sizeof(char)*(maxSizeLine));
    fgets(line,maxSizeLine,file);
    fclose(file);
    //la parse et renvoie le livre

    if (line != NULL){
        l = parseElement(line);
    }
    free(line);
    return l;
}

Livre getLastElementOfFile(){
    //Ouvre le fichier puis lit jusqu'à la dernière ligne puis le ferme
    FILE* file = openFile();
    char* line = (char*)malloc(sizeof(char)*(maxSizeLine));
    char* lineBefore;
    Livre l;

    while(fgets(line,maxSizeLine,file)!=NULL){
        lineBefore = line;
    }
    //la parse et renvoie le livre
    if (line != NULL){
        l = parseElement(line);
    }
    fclose(file);
    free(lineBefore);
    return l;
}

int maxSizeOfLine(){
    //Ouvre le fichier puis lit jusqu'à la dernière ligne puis le ferme
    //en stockant la taille de la plus grande ligne
    FILE* file = openFile();
    char line[100000];
    int maxSize = 0;
    if (file != NULL){
        while(fgets(line,100000,file)!=NULL){
            if (strlen(line) > maxSize){
                maxSize = strlen(line);
            }
        }
        fclose(file);
    }
    return maxSize;
}

int numberOfLines(){
    //Ouvre le fichier puis lit jusqu'à la dernière ligne puis le ferme
    //en incrémentant nbreLine
    FILE* file = openFile();
    char* line = (char*)malloc(sizeof(char)*(maxSizeLine));
    int nbreLine = 0;
    while(fgets(line,maxSizeLine,file)!=NULL){
        nbreLine++;
    }
    fclose(file);
    free(line);
    return nbreLine;
}

FILE* openFile(){
    FILE *file;
    file = fopen("test.dat", "r"); //r as read
    assert(file != NULL);
    return file;
}

void detruireLivre(Livre l){
    free(l.ISBN);
    free(l.titre);
    free(l.auteur);
    free(l.editeur);
    free(l.dateParution);
}
