#include <stdio.h>
#include "aeroport.c"

void main() {
    int choix;
    Liste liste;
    liste.premier = liste.dernier = NULL;
    do {
        printf("\nMenu Genral\n");
        printf("1 - Creation du repertoire Avion\n");
        printf("2 - Mise a jour des Avions\n");
        printf("3 - Recherche, affichage et Tri\n");
        printf("4 - Enregistrement dans un fichier\n");
        printf("5 - Chargement d'un fichier\n");
        printf("6 - Quitter\n");
        printf("Donner votre choix SVP : ");
        scanf("%d", &choix);
        printf("\n");
        switch(choix) {
            case 1:
                creation(&liste);
                break;
            case 2:
                menu_maj(&liste);
                break;
            case 3:
                menu_recherche_affichage(&liste);
                break;
            case 4:
                enregistrement(&liste);
                break;
            case 5:
                chargement(&liste);
                break;
            case 6:
                printf("Programme termine.\n");
                break;
            default:
                printf("Choix invalide. Veuillez choisir une option valide.\n");
        }
    } while(choix != 6);
}