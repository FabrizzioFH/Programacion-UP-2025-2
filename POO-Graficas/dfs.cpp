// dfs.cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

using namespace std;

// Función DFS recursiva: recorre el grafo desde 'start'
void dfsRecursive(const unordered_map<int, vector<int>> &graph, int start, unordered_set<int> &visited) {
    // Procesa el nodo actual (en este ejemplo, se imprime)
    cout << start << " ";
    visited.insert(start);
    // Recorrer cada vecino
    // graph.at(start) devuelve un vector con los vecinos de 'start'
    for (int neighbor : graph.at(start)) {
        if (visited.find(neighbor) == visited.end()) {
            dfsRecursive(graph, neighbor, visited);
        }
    }
}

int main() {
    // Ejemplo 1: Grafo simple representado con lista de adyacencia
    unordered_map<int, vector<int>> graph = {
        {1, {2, 3}},
        {2, {1, 4, 5}},
        {3, {1}},
        {4, {2}},
        {5, {2}}
    };

    // Realizar DFS a partir del nodo 1
    unordered_set<int> visited;
    cout << "Ejemplo 1: DFS desde el nodo 1: ";
    dfsRecursive(graph, 1, visited);
    cout << endl;

    // Ejemplo 2: Encontrar componentes conexas en el grafo
    // Reiniciamos el conjunto de visitados para encontrar cada componente
    unordered_set<int> allVisited;
    int component = 0;
    cout << "Ejemplo 2: Componentes conexas:" << endl;
    for (auto &pair : graph) {
        int node = pair.first;
        if (allVisited.find(node) == allVisited.end()) {
            component++;
            cout << "Componente " << component << ": ";
            // Conjunto para esta componente particular
            unordered_set<int> compVisited;
            dfsRecursive(graph, node, compVisited);
            // Fusionar los nodos visitados de esta componente con el conjunto global
            allVisited.insert(compVisited.begin(), compVisited.end());
            cout << endl;
        }
    }

    return 0;
}
