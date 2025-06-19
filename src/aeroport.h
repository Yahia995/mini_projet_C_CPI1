#define Nmax 50

typedef struct compagnie {
  char nom[Nmax];
  char acronyme[4];
} Compagnie;

typedef struct avion {
  char identifiant[7];
  int carburant;
  int consommation;
  char heure_decollage[5];
  struct compagnie *compagnie;
  struct avion *suivant;
} Avion;

typedef struct liste {
  Avion *premier, *dernier;
} Liste;

void creation(Liste *);
void menu_maj(Liste *);
void menu_recherche_affichage(Liste *);
void enregistrement(Liste *);
void chargement(Liste *);