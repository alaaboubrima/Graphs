#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define MAX_SOMMETS 200

// Structure de nœud pour représenter un nœud du graphe
typedef struct sommet {
  int val;
  struct sommet *suiv;
} Sommet;

// Tableau de tête de liste pour représenter le graphe
Sommet *liste_adja[MAX_SOMMETS];
int num_sommets;

// Ajouter un nœud au graphe
void add_sommet(int val) {
  // Allouer la mémoire pour le nouveau nœud
  Sommet *nv_sommet = malloc(sizeof(Sommet));
  nv_sommet->val = val;
  nv_sommet->suiv = NULL;

  // Ajouter le nœud à la liste d'adjacence
  liste_adja[num_sommets++] = nv_sommet;
}


// Ajouter une arête au graph
void add_lien_NO(int from, int to) {
  // Allouer de la mémoire pour le nouveau nœud
  Sommet *nv_sommet = malloc(sizeof(Sommet));
  nv_sommet->val = to;
  nv_sommet->suiv = NULL;

  // Ajouter le nœud à la fin de la liste d'adjacence du nœud "from"
  Sommet *cur = liste_adja[from];
  while (cur->suiv != NULL) {
    cur = cur->suiv;
  }
  cur->suiv = nv_sommet;
  
  nv_sommet = malloc(sizeof(Sommet));
  nv_sommet->val = from;
  nv_sommet->suiv = NULL;
  // Dans le cas ou le lien n'est pas orienté on ajoute ca
  // Ajouter le nœud à la fin de la liste d'adjacence du nœud "to"
  cur = liste_adja[to];
  while (cur->suiv != NULL) {
    cur = cur->suiv;
  }
  cur->suiv = nv_sommet;
}

// Ajouter une arête au graph non oriente
void add_lien(int from, int to) {
  // Allouer de la mémoire pour le nouveau nœud
  Sommet *nv_sommet = malloc(sizeof(Sommet));
  nv_sommet->val = to;
  nv_sommet->suiv = NULL;

  // Ajouter le nœud à la fin de la liste d'adjacence du nœud "from"
  Sommet *cur = liste_adja[from];
  while (cur->suiv != NULL) {
    cur = cur->suiv;
  }
  cur->suiv = nv_sommet;

}


// Représentation du graphe
void rep_graph(void) {
  for (int i = 0; i < num_sommets; i++) {
    Sommet *cur = liste_adja[i];
    printf("%d :", cur->val); // pour afficher le sommet
    cur = cur->suiv; 
    while (cur != NULL) {
      printf(" %d", cur->val);
      cur = cur->suiv;
    }
    printf("\n");
  }
}


// Calculer la densité du graphe
double densite(void) {
  int num_liens = 0;
  for (int i = 0; i < num_sommets; i++) {
    Sommet *cur = liste_adja[i];
    
    while (cur->suiv != NULL) {
      num_liens++;
      cur = cur->suiv;
    }
  }
  return (2.0 * num_liens) / (num_sommets * (num_sommets - 1));
}


// Rechercher un nœud dans le graph
bool rech_sommet(int val) {
    for (int i = 0; i < num_sommets; i++) {
        Sommet *cur = liste_adja[i];
        if (cur->val == val) {
            return true;
        }
    }
    return false;
}

// Rechercher un chemin entre deux nœuds dans le graph
bool DFS(int start, int end, bool visited[])
{
    if (start == end)
        return true;

    // On marque le sommet actuel comme visité et l'affiche
    visited[start] = true;
    Sommet* i = liste_adja[start];
    while(i)
    {
      if (!visited[i->val])
          if (DFS(i->val, end, visited))
              return true;
      i = i->suiv;
    }
    return false;
}

// Ajouter un nœud avec ses liens au graph
void add_sommet_avec_liens(int val) {
    // On fait l'appel a la fonction qui ajoute le sommet au graph
    add_sommet(val);
    int b, x, y;
    printf("Combien de liens ?\n");
    scanf("%d", &y);
    for (int i = 1; i < y+1; i++) {
      printf("Ecrit lien %d\n", i);
      scanf("%d", &b);
      printf("Ecrit 1 si c'est un lien orienté\nEcrit 0 sinon.\n");
      scanf("%d", &x);
      if (x == 0) {add_lien_NO(val, b);}
        else if (x == 1) {add_lien(val, b);}
    }
}


// Supprimer un nœud avec ses liens
void supp_sommet_avec_liens(int val) {
    // supprimer tous les liens
    for (int i = 0; i < num_sommets; i++) {
        Sommet *cur = liste_adja[i], *prec = NULL;
        while (cur != NULL) {
            if(cur->val == val){
                if(prec)
                    prec->suiv = cur->suiv;
                else
                    liste_adja[i] = cur->suiv;
                free(cur);
                cur = prec ? prec->suiv : liste_adja[i];
            }
            else{
                prec = cur;
                cur = cur->suiv;
            }
        }
    }
    //supprimer le sommet du graphe
    for (int i = 0; i < num_sommets; i++) {
        if(liste_adja[i]->val == val){
            Sommet* temp = liste_adja[i];
            for (int j = i; j < num_sommets-1; j++) {
                liste_adja[j] = liste_adja[j+1];
            }
            free(temp);
            num_sommets--;
            break;
        }
    }
}




// Recherche du chemin le plus court entre deux nœuds a et b
void bfs(int start, int end) {
    bool visited[num_sommets];
    int parent[num_sommets];
    int distance[num_sommets];
    int queue[num_sommets];
    int front = 0, rear = -1;
    // initialize all the arrays
    for (int i = 0; i < num_sommets; i++) {
        visited[i] = false;
        parent[i] = -1;
        distance[i] = INT_MAX;
    }
    // on met la distance = 0
    distance[start] = 0;
    visited[start] = true;
    queue[++rear] = start;
    // On utilise la methode BFS
    while (front <= rear) {
        int current = queue[front++];
        for (Sommet* adj = liste_adja[current]; adj != NULL; adj = adj->suiv) {
            if (!visited[adj->val]) {
                visited[adj->val] = true;
                parent[adj->val] = current;
                distance[adj->val] = distance[current] + 1;
                queue[++rear] = adj->val;
            }
        }
    }
    // On affiche le plus court chemin
    if (parent[end] == -1) {
        printf("Y a pas de chemin de %d a %d\n", start, end);
    } else {
        int current = end;
        int path[num_sommets];
        int path_index = 0;
        while (current != -1) {
            path[path_index++] = current;
            current = parent[current];
        }
        printf("Le plus court chemin entre %d et %d a une longueur de %d: ", start, end, distance[end]);
        for (int i = path_index - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
    }
}


void ConstGraph1() {
    
  add_sommet(0);add_sommet(1);add_sommet(2);add_sommet(3);
  add_lien_NO(0, 1);
  add_lien_NO(0, 2);
  add_lien_NO(0, 3);
  add_lien_NO(1, 2);
}
void ConstGraph2() {
    
  add_sommet(0);add_sommet(1);add_sommet(2);add_sommet(3);
  add_lien(0, 1);
  add_lien(0, 2);
  add_lien(0, 3);
  add_lien(1, 2);
}
void ConstGraph3() {
    
  add_sommet(0);add_sommet(1);add_sommet(2);add_sommet(3);add_sommet(4);add_sommet(5);
  add_sommet(6);add_sommet(7);add_sommet(8);add_sommet(9);add_sommet(10);add_sommet(11);
  add_sommet(12);add_sommet(13);add_sommet(14);add_sommet(15);add_sommet(16);add_sommet(17);
  add_sommet(18);add_sommet(19);add_sommet(20);add_sommet(21);add_sommet(22);add_sommet(23);
  add_sommet(24);add_sommet(25);add_sommet(26);add_sommet(27);add_sommet(28);add_sommet(29);
  add_sommet(30);add_sommet(31);add_sommet(32);add_sommet(33);add_sommet(34);add_sommet(35);add_sommet(36);
  add_sommet(37);add_sommet(38);add_sommet(39);add_sommet(40);add_sommet(41);add_sommet(42);add_sommet(43);
  add_sommet(44);add_sommet(45);add_sommet(46);add_sommet(47);add_sommet(48);add_sommet(49);


}







void stop(clock_t start) {
  // Arrêter le chronomètre
  clock_t end = clock();

  // Calculer le temps d'exécution en secondes
  double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;

  // Afficher le résultat
  printf("Temps d'exécution : %f micro-secondes\n", elapsed_time * 1000000);

}



int main(void) {
    

    
    int quit = 0;
    int a, b, x, y;
    bool visited[num_sommets];

    int num;
    char choix;
    //bool visited[num_sommets];

    do {
        printf("\nLISTE D'ADJACENCE");
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
                for (int i = 0; i < MAX_SOMMETS; i++) {
                liste_adja[i] = NULL;
                }
              start = clock();
              ConstGraph1();
              stop(start);
              
              break;
        
            case 12:
                printf("Construction terminee\n");
                for (int i = 0; i < MAX_SOMMETS; i++) {
                liste_adja[i] = NULL;
                }
              start = clock();
              ConstGraph2();
              stop(start);
              break;
              
            case 13:
                printf("Construction terminee\n");
                for (int i = 0; i < MAX_SOMMETS; i++) {
                liste_adja[i] = NULL;
                }
              start = clock();
              ConstGraph3();
              stop(start);
              break;
            
            case 2:
              start = clock();
              rep_graph();
              stop(start);
              break;
              
            case 3:
              start = clock();
              printf("Densité : %f\n", densite());
              stop(start);
              break;
              
            case 4:
              printf("Entre le sommet\n");
              scanf("%d", &a);
              start = clock();
              if(rech_sommet(a)) printf("Sommet trouvé.\n");
              else printf("Sommet non trouvé.\n");
              stop(start);
              break;
              
            case 5:
              //for(int i=0;i<num_sommets;i++) visited[i]=false;
              printf("Entre le noeud a\n");
              scanf("%d", &a);
              printf("Entre le noeud b\n");
              scanf("%d", &b);
              start = clock();
              if(DFS(a,b,visited)) printf("Chemin trouvé.\n");
              else printf("Chemin non trouvé.\n");
              stop(start);
              break;
              
            case 6:
              printf("Entre le noeud a\n");
              scanf("%d", &a);
              printf("Entre le noeud b\n");
              scanf("%d", &b);
              start = clock();
              bfs(a,b);
              stop(start);
              break;
              
            case 7:
              printf("");
              break;
              
            case 8:
              printf("Ecrit le noeud a (Choisi un noeud qui n'existe pas)\n");
              scanf("%d", &a);
              add_sommet(a);
              
              printf("Combien de liens ?\n");
              scanf("%d", &y);
              
              for (int i = 1; i < y+1; i++) {
                  printf("Ecrit lien %d\n", i);
                  scanf("%d", &b);
                  printf("Ecrit 1 si c'est un lien orienté\nEcrit 0 sinon.\n");
                  scanf("%d", &x);
                  start = clock();
                  if (x == 0) {add_lien_NO(a, b);stop(start);}
                  else {add_lien(a, b);stop(start);}

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
    } while (quit == 0);    
    
  return 0;
}


