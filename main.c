#include <stdio.h>
#include <stdbool.h>
#define MAX_SOMMETS 100
#include <time.h>

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

// Rechercher un chemin entre deux nœuds dans le graph
bool rech_chemin(int origine, int dest) {
  if (origine == dest) {
    return true;
  }

  // Marquer le nœud source comme visité
  matrice_adj[origine][origine] = 2;

  // Vérifier si il y a un chemin vers chaque nœud adjacent
  for (int i = 0; i < num_sommets; i++) {
    if (matrice_adj[origine][i] == 1 && matrice_adj[i][i] != 2) {
      if (rech_chemin(i, dest)) {
        return true;
      }
    }
  }

  return false;
}
  
  
// Ajouter un nœud avec ses liens au graph
void add_node_with_links(int node, int num_links, int links[]) {
  for (int i = 0; i < num_links; i++) {
    matrice_adj[node][links[i]] = 1;
    matrice_adj[links[i]][node] = 1;
  }
}    


// Supprimer un nœud avec ses liens
void delete_node_with_links(int node) {
  // Supprimer les liens du nœud
  for (int i = 0; i < num_sommets; i++) {
    matrice_adj[node][i] = 0;
    matrice_adj[i][node] = 0;
  }
  // Supprimer une colonne de la matrice
  for (int i = 0; i < num_sommets; i++) {
    for (int j = node; j < num_sommets - 1; j++) {
      matrice_adj[i][j] = matrice_adj[i][j + 1];
    }
  }
  // Supprimer une ligne de la matrice
  for (int i = node; i < num_sommets - 1; i++) {
    for (int j = 0; j < num_sommets; j++) {
      matrice_adj[i][j] = matrice_adj[i + 1][j];
    }
  }
}






/////////////////////////////////

void stop(clock_t start) {
  // Arrêter le chronomètre
  clock_t end = clock();

  // Calculer le temps d'exécution en secondes
  double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;

  // Afficher le résultat
  printf("Temps d'exécution : %f secondes\n", elapsed_time * 1000000);

}
///////////////////////////////
      
int main(void) {
  clock_t start = clock();
  stop(start);
  // Initialiser le graph avec 4 sommets
  num_sommets = 4;
  construct_graph(num_sommets);

  // Ajouter quelques arêtes
  add_arc(1,2);




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
  
  num_sommets++;
  int node2_links[] = { 3 };
  add_node_with_links(2, 1, node2_links);
  
  delete_node_with_links(0);
  num_sommets--;



  // Représentation du graph
  rep_graph(num_sommets);
  return 0;
}





