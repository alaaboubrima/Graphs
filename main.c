#include <stdio.h>
#include <stdbool.h>
#define MAX_SOMMETS 100

// Matrice d'adjacence pour représenter un graph
int matrice_adj[MAX_SOMMETS][MAX_SOMMETS];
int num_sommets;

// Initialiser le graph
void construct_graph(int num_sommets) {
  for (int i = 0; i < num_sommets; i++) {
    for (int j = 0; j < num_sommets; j++) {
      matrice_adj[i][j] = 0;
    }
  }
}

// Ajouter une arête au graph
void add_arc(int origine, int dest) {
  matrice_adj[origine][dest] = 1;
  matrice_adj[dest][origine] = 1;
}

// Représentation
void rep_graph(int num_sommets) {
  for (int i = 0; i < num_sommets; i++) {
    for (int j = 0; j < num_sommets; j++) {
      printf("%d ", matrice_adj[i][j]);
    }
    printf("\n");
  }
}

// Densité
double densite(num_sommets) {
  int num_arcs = 0;
  for (int i = 0; i < num_sommets; i++) {
    for (int j = 0; j < num_sommets; j++) {
      if (matrice_adj[i][j]) {
        num_arcs++;
      }
    }
  }
  return (2.0 * num_arcs) / (num_sommets * (num_sommets - 1));
}

// Rechercher un nœud dans le graph
void rech_sommet(int sommet) {
  printf("Sommet %d:\n", sommet);
  for (int i = 0; i < num_sommets; i++) {
    if (matrice_adj[sommet][i]) {
      printf("  vers sommet %d\n", i);
    }
  }
}


      
int main(void) {
  // Initialiser le graph avec 4 sommets
  num_sommets = 4;
  construct_graph(num_sommets);

  // Ajouter quelques arêtes
  add_arc(0, 1);
  add_arc(0, 2);
  add_arc(2, 1);
  add_arc(1, 2);
  add_arc(2, 3);


  // Représentation du graph
  rep_graph(num_sommets);

  // Densite
  printf("%f\n", densite(num_sommets));
  
  // Rechercher un nœud dans le graph
  rech_sommet(3);
  
  
  
  // Rechercher un chemin entre les nœuds 0 et 3
  if (rech_chemin(0, 3)) {
    printf("Chemin trouvé\n");
  } else {
    printf("Chemin non trouvé\n");
  }
  
  
  return 0;
}