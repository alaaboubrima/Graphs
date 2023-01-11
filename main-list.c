#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 100

// Structure de nœud pour représenter un nœud du graphe
typedef struct node {
  int value;
  struct node *next;
} Node;

// Tableau de tête de liste pour représenter le graphe
Node *adjacency_list[MAX_NODES];
int num_nodes;

// Ajouter un nœud au graphe
void add_node(int value) {
  // Allouer de la mémoire pour le nouveau nœud
  Node *new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = NULL;

  // Ajouter le nœud à la liste d'adjacence
  adjacency_list[num_nodes++] = new_node;
}


// Ajouter une arête au graph
void add_link(int from, int to) {
  // Allouer de la mémoire pour le nouveau nœud
  Node *new_node = malloc(sizeof(Node));
  new_node->value = to;
  new_node->next = NULL;

  // Ajouter le nœud à la fin de la liste d'adjacence du nœud "from"
  Node *cur = adjacency_list[from];
  while (cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = new_node;
  
  new_node = malloc(sizeof(Node));
  new_node->value = from;
  new_node->next = NULL;
  
  // Ajouter le nœud à la fin de la liste d'adjacence du nœud "to"
  cur = adjacency_list[to];
  while (cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = new_node;
}

// Ajouter une arête au graph non oriente
void add_link_NO(int from, int to) {
  // Allouer de la mémoire pour le nouveau nœud
  Node *new_node = malloc(sizeof(Node));
  new_node->value = to;
  new_node->next = NULL;

  // Ajouter le nœud à la fin de la liste d'adjacence du nœud "from"
  Node *cur = adjacency_list[from];
  while (cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = new_node;

}


// Représentation du graphe
void print_graph(void) {
  for (int i = 0; i < num_nodes; i++) {
    Node *cur = adjacency_list[i];
    printf("%d :", cur->value); // pour afficher le sommet
    cur = cur->next; 
    while (cur != NULL) {
      printf(" %d", cur->value);
      cur = cur->next;
    }
    printf("\n");
  }
}


// Calculer la densité du graphe
double density(void) {
  int num_edges = 0;
  for (int i = 0; i < num_nodes; i++) {
    Node *cur = adjacency_list[i];
    
    while (cur->next != NULL) {
      num_edges++;
      cur = cur->next;
    }
  }
  return (2.0 * num_edges) / (num_nodes * (num_nodes - 1));
}


// Rechercher un nœud dans le graph
bool search_node(int value) {
    for (int i = 0; i < num_nodes; i++) {
        Node *cur = adjacency_list[i];
        if (cur->value == value) {
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

    // Mark the current node as visited and print it
    visited[start] = true;
    Node* i = adjacency_list[start];
    while(i)
    {
      if (!visited[i->value])
          if (DFS(i->value, end, visited))
              return true;
      i = i->next;
    }
    return false;
}

// Ajouter un nœud avec ses liens au graph

void add_node_with_links(int value, int to) {
    // Add the node to the graph
    add_node(value);
    add_link(value, to);
}


// Supprimer un nœud avec ses liens
void remove_node_with_links(int value) {
    // remove edges from the graph
    for (int i = 0; i < num_nodes; i++) {
        Node *cur = adjacency_list[i], *prev = NULL;
        while (cur != NULL) {
            if(cur->value == value){
                if(prev)
                    prev->next = cur->next;
                else
                    adjacency_list[i] = cur->next;
                free(cur);
                cur = prev ? prev->next : adjacency_list[i];
            }
            else{
                prev = cur;
                cur = cur->next;
            }
        }
    }
    //remove the node from the graph
    for (int i = 0; i < num_nodes; i++) {
        if(adjacency_list[i]->value == value){
            Node* temp = adjacency_list[i];
            for (int j = i; j < num_nodes-1; j++) {
                adjacency_list[j] = adjacency_list[j+1];
            }
            free(temp);
            num_nodes--;
            break;
        }
    }
}




// Recherche du chemin le plus court entre deux nœuds a et b
void bfs(int start, int end) {
    bool visited[num_nodes];
    int parent[num_nodes];
    int distance[num_nodes];
    int queue[num_nodes];
    int front = 0, rear = -1;
    // initialize all the arrays
    for (int i = 0; i < num_nodes; i++) {
        visited[i] = false;
        parent[i] = -1;
        distance[i] = INT_MAX;
    }

    // set the source distance to 0
    distance[start] = 0;
    visited[start] = true;
    queue[++rear] = start;

    // perform BFS
    while (front <= rear) {
        int current = queue[front++];
        for (Node* adj = adjacency_list[current]; adj != NULL; adj = adj->next) {
            if (!visited[adj->value]) {
                visited[adj->value] = true;
                parent[adj->value] = current;
                distance[adj->value] = distance[current] + 1;
                queue[++rear] = adj->value;
            }
        }
    }

    // print the shortest path
    if (parent[end] == -1) {
        printf("No path from %d to %d\n", start, end);
    } else {
        int current = end;
        int path[num_nodes];
        int path_index = 0;
        while (current != -1) {
            path[path_index++] = current;
            current = parent[current];
        }
        printf("Shortest path between %d and %d has length %d: ", start, end, distance[end]);
        for (int i = path_index - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
    }
}


void ConstGraph1() {
  add_node(0);
  add_node(1);
  add_node(2);
  add_node(3);
  add_link(0, 1);
  add_link(0, 2);
  add_link(0, 3);
  add_link(1, 2);
}
void ConstGraph2() {
  add_node(0);
  add_node(1);
  add_node(2);
  add_node(3);
  add_link_NO(0, 1);
  add_link_NO(0, 2);
  add_link_NO(0, 3);
  add_link(1, 2);
}


int main(void) {
    
  num_nodes = 0;
  for (int i = 0; i < MAX_NODES; i++) {
    adjacency_list[i] = NULL;
  }
    
    
    int x;

   int num;
   char choice;
    do {
        printf("Construction d’un graphe orienté ? Choisi 1");
        printf("\nConstruction d’un graphe non orienté ? Choisi 2");
        printf("\nAffichage du graphe ? Choisi 3");
        printf("\nCalculer la densité du graphe ? Choisi 4");
        printf("\nRecherche d’un nœud a dans le graphe (afficher le nœud et ses liens) ? Choisi 5");
        printf("\nRecherche d’un chemin entre un nœud a et un nœud b ? Choisi 6");
        printf("\nRecherche du chemin le plus court entre deux nœuds a et b ? Choisi 7");
        printf("\nRecherche d’une composante (fortement) connexe à partir d’un nœud a ? Choisi 8");
        printf("\nAjouter un nœud a avec ses liens ? Choisi 9");
        printf("\nSupprimer un nœud a avec ses liens ? Choisi 10");
        printf("\nAjouter un lien (arc ou arête) entre deux nœuds existants ? Choisi 11");
        printf("\n");


        scanf("%d", &num);

        switch (num)
        {
            case 1:
              ConstGraph1();
              break;
        
            case 2:
              ConstGraph2();
              break;
            
            case 3:
              print_graph();
              break;
              
            case 4:
              break;
              
            case 5:
              printf("Entre le sommet\n");
              scanf("%d", &x);
              if(search_node(x)) printf("Node found.\n");
              else printf("Node not found.\n");
              break;
              
            case 6:
              printf("2");
              break;
              
            case 7:
              printf("2");
              break;
              
            case 8:
              printf("2");
              break;
              
            case 9:
              printf("2");
              break;
              
            case 10:
              printf("2");
              break;
              
            case 11:
              printf("2");
              break;
              
            default:
              printf("0");
        }

        printf("Would you like to return to the homepage? (y/n):");
        scanf(" %c", &choice);
    } while (choice != 'y');    
    

  // Initialiser le graphe avec 4 nœuds et aucun lien

  // Ajouter les nœuds 0, 1, 2, et 3


  // Ajouter des liens au nœud 0


  // Ajouter des liens au nœud 1
  //add_link(1, 2);

  // Rechercher un nœud dans le graph
  //if(search_node(3)) printf("Node found.\n");
  //else printf("Node not found.\n");
  
  
  // Rechercher un chemin entre les nœuds 0 et 3
  //bool visited[num_nodes];
    //for(int i=0;i<num_nodes;i++) visited[i]=false;
    //if(DFS(0,3,visited)) printf("Path found.\n");
    //else printf("Path not found.\n");
    
 // Ajouter un nœud avec ses liens au graph
  //add_node_with_links(4,2);
  //print_graph();
  
  // Supprimer un nœud avec ses liens
  //remove_node_with_links(4);
  //print_graph();
  

  // Recherche du chemin le plus court entre deux nœuds a et b

  //bfs(2,3);



  return 0;
}

