#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aeroport.h"

unsigned test = 0;

int taille_liste_av(Liste *liste) {
  int count = 0;
  Avion *cur = liste->premier;
  while (cur != NULL) {
    count++;
    cur = cur->suivant;
  }
  return count;
}

Avion* recherche_av(Liste *liste, char* identifiant) {
  Avion *cur = liste->premier;
  while (cur != NULL) {
    if (strcmp(cur->identifiant, identifiant) == 0) {
      return cur;
    }
    cur = cur->suivant;
  }
  return NULL;
}

void insere_tete_av(Liste *liste, Avion *avion) {
  avion->suivant = liste->premier;
  liste->premier = avion;
  if (liste->dernier == NULL) {
    liste->dernier = avion;
  }
}

void insere_queue_av(Liste *liste, Avion *avion) {
  if (liste->premier == NULL)
    liste->premier = avion;
  else
    liste->dernier->suivant = avion;
  liste->dernier = avion;
  avion->suivant = NULL;
}

void insere_pos_av(Liste *liste, Avion *avion, int pos) {
  if (pos <= 1 || pos > taille_liste_av(liste)) {
    printf("Erreur: Position invalide pour l'insertion.\n");
    return;
  }

  Avion *prev = NULL;
  Avion *cur = liste->premier;
  int i = 1;
  while (i < pos) {
    prev = cur;
    cur = cur->suivant;
    i++;
  }

    avion->suivant = cur;
    prev->suivant = avion;
}

void supprimer_tete_av(Liste *liste) {
  if (liste->premier == NULL) {
    return;
  }

  Avion *avion = liste->premier;
  liste->premier = avion->suivant;
  free(avion);
  if (liste->premier == NULL) {
    liste->dernier = NULL;
  }
}

void supprimer_queue_av(Liste *liste) {
    Avion *cur = liste->premier;
    if(cur->suivant == NULL) {
        liste->premier = liste->dernier = NULL;
    } else {
        while(cur->suivant != liste->dernier)
            cur = cur->suivant;
        liste->dernier = cur;
        cur = cur->suivant;
        liste->dernier->suivant = NULL;
    }
    free(cur);
}

void suppression_pos_av(Liste *liste, int pos) {
  if (pos <= 1 || pos > taille_liste_av(liste)) {
    printf("Erreur: Position invalide pour la suppression.\n");
    return;
  }

  Avion *prev = NULL;
  Avion *cur = liste->premier;
  int i = 1;
  while (i < pos) {
    prev = cur;
    cur = cur->suivant;
    i++;
  }

    prev->suivant = cur->suivant;
    free(cur);
}

void suppression_av_donne(Liste *liste, char* identifiant) {
  Avion *avion = recherche_av(liste, identifiant);
  if (avion == NULL) {
    return;
  }

  if (avion == liste->premier) {
    supprimer_tete_av(liste);
  } else if (avion == liste->dernier) {
    supprimer_queue_av(liste);
  } else {
    Avion *prev = NULL;
    Avion *cur = liste->premier;
    while (cur != avion) {
      prev = cur;
      cur = cur->suivant;
    }
    prev->suivant = cur->suivant;
    free(cur);
  }
}

void afficher_avion(Avion *avion) {
  printf("+-------------------------------------------------+\n");  
  printf("Identifiant: %s\n", avion->identifiant);
  printf("Carburant: %d litres\n", avion->carburant);
  printf("Consommation: %d par minute\n", avion->consommation);
  printf("Heure de decollage prevue: %c%c:%c%c\n", avion->heure_decollage[0], avion->heure_decollage[1], avion->heure_decollage[2], avion->heure_decollage[3]);
  printf("Compagnie: %s (%s)\n", avion->compagnie->nom, avion->compagnie->acronyme);
  printf("+-------------------------------------------------+\n");
}

void afficher_liste_avions(Liste *liste) {
  Avion *cur = liste->premier;
  while (cur != NULL) {
    afficher_avion(cur);
    cur = cur->suivant;
  }
  if (liste->premier == NULL) {
    printf("La liste est vide.\n");
  }
}

int avion_deja_present(Liste *liste, char* identifiant) {
  Avion *cur = liste->premier;

  while (cur != NULL) {
    if (strcmp(cur->identifiant, identifiant) == 0) {
      return 1;
    }
    cur = cur->suivant;
  }
  return 0;
}

unsigned chaine_numerique(char *chaine) {
  if(chaine == NULL || *chaine == '\0')
    return 0;
  while (*chaine != '\0') {
    if(!isdigit(*chaine))
      return 0;
    chaine++;
  }
  return 1;
}

unsigned identifiant_valide(char id[]) {
  unsigned i;

  if(strlen(id) != 6)
    return 0;

  for(i = 0; i < 3; i++) {
    if('A' > id[i] || id[i] > 'Z')
      return 0;
  }

  char vol[4];
  vol[0] = id[3];
  vol[1] = id[4];
  vol[2] = id[5];
  vol[3] = '\0';
  
  return chaine_numerique(vol);
}

Compagnie *creer_compagnie(Avion *avion) {
  Compagnie *c = malloc(sizeof(Compagnie));

  printf("Nom de la compagnie : ");
  scanf(" %[^\n]", c->nom);
  strncpy(c->acronyme, avion->identifiant, 3);
  c->acronyme[3] = '\0';

  return c;
}

Avion *creer_avion(Liste *liste) {
  char h[3], m[3];
  unsigned h1, m1;
  Avion *avion = malloc(sizeof(Avion));

  do {
    printf("Identifiant (acronyme + numero de vol) : ");
    scanf("%s", avion->identifiant);
    if (avion_deja_present(liste, avion->identifiant))
      printf("Avion deja existe!\n");
  } while (avion_deja_present(liste, avion->identifiant) || !identifiant_valide(avion->identifiant));

  printf("Carburant (en litres) : ");
  scanf("%u", &avion->carburant);

  printf("Consommation par minute (en litres) : ");
  scanf("%u", &avion->consommation);

  do {
    printf("Heure de decollage prevue (HHMM) : ");
    scanf("%s", avion->heure_decollage);
    h[0] = avion -> heure_decollage[0];
    h[1] = avion -> heure_decollage[1];
    m[0] = avion -> heure_decollage[2];
    m[1] = avion -> heure_decollage[3];
    h[2] = m[2] = '\0';
    h1 = atoi(h);
    m1 = atoi(m);
  } while(strlen(avion->heure_decollage) != 4 || !chaine_numerique(avion->heure_decollage) || h1 > 23 || m1 > 59);

  avion->compagnie = creer_compagnie(avion);

  avion->suivant = NULL;

  return avion;
}

void creation(Liste *liste) {
  char choix;
  int pos;

  if (test == 1) {
    printf("\nListe deja cree!\n");
    return;
  }

  do {
    Avion *a = creer_avion(liste);

    printf("Donner la position de l'insertion de l'avion: ");
    scanf("%u", &pos);
    if(pos == 1) {
      insere_tete_av(liste, a);
    } else if(pos == taille_liste_av(liste) + 1) {
      insere_queue_av(liste, a);
    } else if(pos > taille_liste_av(liste) + 1) {
      printf("\nPosition invalide !\n");
    } else {
      insere_pos_av(liste, a, pos);
    }

    printf("Voulez-vous ajouter un autre avion ? (O/N): ");
    scanf(" %c", &choix);
  } while (choix == 'O' || choix == 'o');
}

void menu_ajouter_avion(Liste *liste) {
  int choix;
  do {
    printf("\nMenu Ajouter\n");
    printf("1 - Ajout en tete\n");
    printf("2 - Ajout en queue\n");
    printf("3 - Ajout dans une position\n");
    printf("4 - Retour au menu MAJ\n");
    printf("Donner votre choix SVP : ");
    scanf("%d", &choix);
    printf("\n");

    if (choix == 4)
      break;

    Avion *avion = creer_avion(liste);
    if (avion == NULL) {
      break;
    }

    switch (choix) {
      case 1:
        insere_tete_av(liste, avion);
        break;
      case 2:
        insere_queue_av(liste, avion);
        break;
      case 3:
        if (taille_liste_av(liste) < 2) {
          printf("Taille < 2!");
        }

        printf("Position d'insertion (2 a %d) : ", taille_liste_av(liste));
        int pos;
        scanf("%d", &pos);
        insere_pos_av(liste, avion, pos);
        break;
      case 4:
        free(avion);
        break;
      default:
        printf("Choix invalide.\n");
        free(avion);
    }
  } while (choix != 4);
}

void menu_supprimer_avion(Liste *liste) {
  if (liste->premier == NULL) {
    printf("La liste est vide.\n");
    return;
  }

  int choix;
  do {
    printf("\nMenu Suppression\n");
    printf("1 - Suppression en tete\n");
    printf("2 - Suppression en queue\n");
    printf("3 - Suppression a partir d'une position\n");
    printf("4 - Suppression d'un avion donne\n");
    printf("5 - Suppression des avions d'une compagnie donnee\n");
    printf("6 - Retour au menu MAJ\n");
    printf("Donner votre choix SVP : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
      case 1:
        supprimer_tete_av(liste);
        break;
      case 2:
        supprimer_queue_av(liste);
        break;
      case 3: {
        if (taille_liste_av(liste) <= 2) {
          printf("Taille < 2 !\n");
          break;
        }
        int pos;
        printf("Position de suppression (2 a %d) : ", taille_liste_av(liste) - 1);
        scanf("%d", &pos);
        if (pos < 2 || pos > taille_liste_av(liste) - 1) {
          printf("\nPosition invalide !\n");
          break;
        }
        suppression_pos_av(liste, pos);
        break;
      }
      case 4: {
        char identifiant[7];
        printf("Identifiant de l'avion a supprimer : ");
        scanf("%s", identifiant);
        suppression_av_donne(liste, identifiant);
        printf("\nLa avion est supprimee (s'il exite)!\n");
        break;
      }
      case 5: {
          char nom_compagnie[50];
          unsigned position = 1;
          printf("Saisissez le nom de la compagnie: ");
          scanf(" %[^\n]", nom_compagnie);
          Avion *temp = liste->premier, *temp1;
          while(temp != NULL) {
              if(strcmp(temp->compagnie->nom, nom_compagnie) == 0) {
                temp1 = temp -> suivant;
                suppression_av_donne(liste, temp -> identifiant);
                temp = temp1;
              } else {
                temp = temp->suivant;
                position++;
              }
            }
      }
      case 6:
        break;
      default:
        printf("\nChoix invalide.\n");
    }
  } while (choix != 6);
}

void menu_modifier_avion(Liste *liste) {
  unsigned x;
  char id[7];
  
  if (liste->premier == NULL) {
    printf("La liste est vide.\n");
    return;
  }

  char identifiant[7];
  printf("Identifiant de l'avion a modifier : ");
  scanf("%s", identifiant);

  Avion *avion = recherche_av(liste, identifiant);
  if (avion == NULL) {
    printf("Avion introuvable.\n");
    return;
  }

  int choix;
  do {
    printf("\nMenu Modification\n");
    printf("1 - Identifiant\n");
    printf("2 - Compagnie\n");
    printf("3 - Retour au menu MAJ\n");
    printf("Donner votre choix SVP : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
      case 1: {
        do {
          printf("Num du vol de l'avion (123): ");
          scanf("%u", &x);
          sprintf(id, "%s%0.3u", avion -> compagnie -> acronyme, x);
        } while(x >= 1000 || avion_deja_present(liste, id));
        sprintf(avion -> identifiant, "%s%0.3u", avion -> compagnie -> acronyme, x);
        break;
      }
      case 2: {
        printf("Nouveau compagnie:\n");
        Compagnie *c = malloc(sizeof(Compagnie));
        printf("Nom de la compagnie: ");
        scanf(" %[^\n]", c -> nom);
        do {
          printf("Acronyme de la compagnie (XXX): ");
          scanf("%s", c -> acronyme);
        } while(strlen(c -> acronyme) != 3 || !('A' <= c -> acronyme[0] && c -> acronyme[0] <= 'Z') || !('A' <= c -> acronyme[1] && c -> acronyme[1] <= 'Z') || !('A' <= c -> acronyme[2] && c -> acronyme[2] <= 'Z'));
        *(avion -> compagnie) = *c;
        free(c);
        strcpy(id, avion -> identifiant);
        sprintf(avion -> identifiant, "%s%c%c%c", avion -> compagnie -> acronyme, id[3], id[4], id[5]);
        }
        break;
      case 3:
        break;
      default:
        printf("Choix invalide.\n");
    }
  } while (choix != 3);
}

void menu_maj(Liste *liste) {
  int choix;

  if (test == 0) {
    printf("\nListe n'est pas cree!\n");
    return;
  }

  do {
    printf("\nMENU MAJ\n");
    printf("1 - Ajouter un nouvel avion\n");
    printf("2 - Supprimer un avion\n");
    printf("3 - Modifier les donnees d'un avion\n");
    printf("4 - Retour au menu general\n");
    printf("Donner votre choix SVP : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
      case 1:
        menu_ajouter_avion(liste);
        break;
      case 2:
        menu_supprimer_avion(liste);
        break;
      case 3:
        menu_modifier_avion(liste);
        break;
      case 4:
        break;
      default:
        printf("Choix invalide.\n");
    }
  } while (choix != 4);
}

void tri_par_consommation(Liste *liste) {
  Avion *i, *j, *temp = malloc(sizeof(Compagnie)), *suiv1, *suiv2;
  for (i = liste->premier; i != liste -> dernier; i = i->suivant) {
    for (j = i->suivant; j != NULL; j = j->suivant) {
      if (i->consommation < j->consommation) {
        suiv1 = i -> suivant;
        suiv2 = j -> suivant;
        *temp = *i;
        *i = *j;
        *j = *temp;
        i -> suivant = suiv1;
        j -> suivant = suiv2;
      }
    }
  }
  free(temp);
}

void menu_recherche_affichage(Liste *liste) {
  if (liste->premier == NULL) {
    printf("La liste est vide.\n");
    return;
  }

  int choix;
  do {
    printf("\nMenu Recherche et Affichage\n");
    printf("1 - Contenu de la liste des avions\n");
    printf("2 - Recherche par identifiant avion\n");
    printf("3 - Recherche par compagnie\n");
    printf("4 - Tri par consommation decroissante\n");
    printf("5 - Retour au menu general\n");
    printf("Donner votre choix SVP : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
      case 1:
        printf("\n");
        afficher_liste_avions(liste);
        break;
      case 2: {
        char identifiant[7];
        printf("\n");
        printf("Identifiant de l'avion à rechercher : ");
        scanf("%s", identifiant);
        Avion *avion = recherche_av(liste, identifiant);
        if (avion == NULL) {
          printf("Avion introuvable.\n");
        } else {
          afficher_avion(avion);
        }
        break;
      }
      case 3: {
        Avion *temp;
        char compagnie[50];
        unsigned x = 0;
        printf("\nNom de compagnie de l'avion: ");
        scanf(" %[^\n]", compagnie);
        temp = liste->premier;
        while(temp != NULL) {
            if(strcmp(temp -> compagnie -> nom, compagnie) == 0) {
                afficher_avion(temp);
                x = 1;
            }
            temp = temp -> suivant;
        }
        if(x == 0)
            printf("Compagnie n'existe pas.\n");
        printf("\n");
        break;
      }
      case 4:
        tri_par_consommation(liste);
        printf("\nTri effectue.\n");
        break;
      case 5:
        break;
      default:
        printf("\nChoix invalide.\n");
    }
  } while (choix != 5);
}

void enregistrement(Liste *liste) {
  if (test == 0) {
    printf("\nListe n'est pas cree!\n");
    return;
  }

  FILE *fichier = fopen("rep.txt", "w");

  Avion *cur = liste->premier;
  while (cur != NULL) {
    fprintf(fichier, "%s %d %d %s %s %s\n", cur->identifiant, cur->carburant, cur->consommation, cur->heure_decollage, cur->compagnie->acronyme, cur->compagnie->nom);
    cur = cur->suivant;
  }

  fclose(fichier);
  printf("\nEnregistrement effectue dans le fichier.\n");
}

void chargement(Liste *liste) {
  FILE *fichier = fopen("rep.txt", "r");

  while (liste->premier != NULL) {
    supprimer_tete_av(liste);
  }

  Avion *avion = malloc(sizeof(Avion));
  avion -> compagnie = (Compagnie *) malloc(sizeof(Compagnie));
  char compagnie_nom[50], compagnie_acronyme[4];
  while (fscanf(fichier, "%s %d %d %s %s %[^\n]\n", avion->identifiant, &avion->carburant, &avion->consommation, avion->heure_decollage, compagnie_acronyme, compagnie_nom) == 6) {
    strcpy(avion->compagnie->nom, compagnie_nom);
    strcpy(avion->compagnie->acronyme, compagnie_acronyme);
    insere_queue_av(liste, avion);
    avion = (Avion *) malloc(sizeof(Avion));
    avion->compagnie = (Compagnie *) malloc(sizeof(Compagnie));
    if (test == 0)
      test = 1;
  }

  free(avion -> compagnie);
  free(avion);
  fclose(fichier);
  printf("\nChargement effectue depuis le fichier.\n");
}