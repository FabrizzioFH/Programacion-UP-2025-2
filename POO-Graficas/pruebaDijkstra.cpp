#include "Grafo.h"

int main() {
    // Definir el grafo con la lista de adyacencia
    unordered_map<string, vector<pair<string, int>>> listaGrafo = {
        {"A", { {"B", 1}, {"C", 3}, {"D", 14} }},
        {"B", { {"A", 1}, {"C", 3}, {"E", 8}, {"F", 5} }},
        {"C", { {"A", 3}, {"B", 3}, {"D", 8}, {"E", 4} }},
        {"D", { {"A", 14}, {"C", 8} }},
        {"E", { {"B", 8}, {"C", 4}, {"F", 6} }},
        {"F", { {"B", 5}, {"E", 6} }}
    };

    // Crear el grafo
    Grafo grafo(listaGrafo);
    grafo.mostrarGrafo();

    // Calcular caminos mínimos desde 'A' usando Dijkstra
    auto resultado = grafo.caminoMasCorto("A");

    cout << "\n=== Distancias desde A (Dijkstra) ===" << endl;
    for (const auto& par : resultado.first) {
        cout << "Nodo: " << par.first << " - Distancia: " << par.second << endl;
    }
    cout << "\n=== Predecesores desde A (Dijkstra) ===" << endl;
    for (const auto& par : resultado.second) {
        cout << "Nodo: " << par.first << " - Predecesor: " << par.second << endl;
    }

    return 0;
}
// $ g++ -o Prueba_Dijkstra PruebaDijkstra.cpp Grafo.cpp
// $ ./Prueba_Dijkstra
