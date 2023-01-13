#include <stdio.h>
#include <stdbool.h>
#define MAX_SOMMETS 200
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
void add_lien_NO(int origine, int dest) {
  matrice_adj[origine][dest] = 1;
  // Le cas ou le lien n'est pas oriente
  matrice_adj[dest][origine] = 1;
}

// Ajouter une arête au graph oriente
void add_lien(int origine, int dest) {
  matrice_adj[origine][dest] = 1;
}

// Représentation du graphe
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
void supp_sommet_avec_liens(int node) {
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
  printf("Temps d'exécution : %f micro-secondes\n", elapsed_time * 1000000);

}
///////////////////////////////
      
      
      

      
void ConstGraph1() {
  construct_graph(5);
  add_lien_NO(0, 1);
  add_lien_NO(0, 2);
  add_lien_NO(0, 3);
  add_lien_NO(1, 2);
}
void ConstGraph2() {
    
  construct_graph(5);  
  add_lien(0, 1);
  add_lien(0, 2);
  add_lien(0, 3);
  add_lien(1, 2);
}
void ConstGraph3() {
    
  construct_graph(50);
}
      
      

      
      
      
      
      
int main(void) {
  clock_t start = clock();
  
  
  int a, b, x, y;
    bool visited[num_sommets];

    int num;
    char choix;
    //bool visited[num_sommets];

    do {
        printf("\nMATRICE D'ADJACENCE");
        printf("\n11. Construction d’un graphe non orienté de 5 sommets.");
        printf("\n12. Construction d’un graphe orienté de 5 sommets.");
        printf("\n13. Construction d’un graphe de 50 sommets.");
        printf("\n2. Affichage du graphe.");
        printf("\n3. Calculer la densité du graphe.");
        printf("\n4. Recherche d’un nœud a dans le graphe (afficher le nœud et ses liens).");
        printf("\n5. Recherche d’un chemin entre un nœud a et un nœud b.");
        printf("\n6. Recherche du chemin le plus court entre deux nœuds a et b.");
        printf("\n7. Recherche d’une composante (fortement) connexe à partir d’un nœud a.");
        printf("\n8. Ajouter un nœud a avec ses liens.");
        printf("\n9. Supprimer un nœud a avec ses liens.");
        printf("\n10. Ajouter un lien (arc ou arête) entre deux nœuds existants.");
        printf("\n");


        scanf("%d", &num);
        clock_t start;
        switch (num)
        {
            case 11:
              printf("Construction terminee\n");
              num_sommets = 5;
              start = clock();
              ConstGraph1();
              stop(start);
              break;
        
            case 12:
              printf("Construction terminee\n");
              num_sommets = 5;
              start = clock();
              ConstGraph2();
              stop(start);
              break;
              
            case 13:
              printf("Construction terminee\n");
              num_sommets = 50;
              start = clock();
              ConstGraph3();
              stop(start);
              break;
            
            case 2:
              // Représentation du graph
              start = clock();
              rep_graph(num_sommets);
              stop(start);
              break;
              
            case 3:
              start = clock();
              printf("%f\n", densite(num_sommets));
              stop(start);
              break;
              
            case 4:
              // Rechercher un nœud dans le graph
              printf("Entre le sommet\n");
              scanf("%d", &a);
              start = clock();
              rech_sommet(a);
              stop(start);
              break;
              
            case 5:
              // Rechercher un chemin entre les nœuds 0 et 3
              
              printf("Entre le noeud a\n");
              scanf("%d", &a);
              printf("Entre le noeud b\n");
              scanf("%d", &b);
              start = clock();
              if (rech_chemin(a, b)) {
              printf("Chemin trouvé\n");
              } else {
              printf("Chemin non trouvé\n");
              stop(start);
              }
              
              break;
              
            case 6:
              printf("");
              break;
              
            case 7:
              printf("");
              break;
              
            case 8:
              printf("Ecrit le noeud a (Choisi un noeud qui n'existe pas)\n");
              scanf("%d", &a);
              num_sommets++;
              
              printf("Combien de liens ?\n");
              scanf("%d", &y);
              
              for (int i = 1; i < y+1; i++) {
                  printf("Ecrit lien %d\n", i);
                  scanf("%d", &b);
                  printf("Ecrit 1 si c'est un lien orienté\nEcrit 0 sinon.\n");
                  scanf("%d", &x);
                  start = clock();
                  if (x == 0) {add_lien_NO(a, b);}
                    else if (x == 1) {add_lien(a, b);}
                  stop(start);
                        
                }
              break;
              
            case 9:
              printf("Ecrit le noeud a supprimer\n");
              scanf("%d", &a);
              start = clock();
              supp_sommet_avec_liens(a);
              stop(start);
              num_sommets--;
            
              
              break;
              
            case 10:
              printf("Pour ajouter un lien entre deux noeuds :\nEcrit 1 si c'est un lien orienté\nEcrit 0 sinon.\n");
              scanf("%d", &x);
              printf("Choisi le noeud a\n");
              scanf("%d", &a);
              printf("Choisi le noeud b\n");
              scanf("%d", &b);
              
              start = clock();
              if (x == 0) {add_lien_NO(a, b);}
                else if (x == 1) {add_lien(a, b);}
              stop(start);
              break;
              
            default:
              printf("Erreur.\n");
        }
        printf("\nAttends 2s\n");
        sleep(2);
        //printf((y/n):");
        //scanf(" %c", &choix);
    } while (!0); 
  

  return 0;
}







