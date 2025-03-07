#include "Grafo.h"

// ============================== FUNCIÓN MAIN PARA PROBAR LAS CLASES ==============================
int main() {
    // Crear un grafo no dirigido
    Grafo miGrafo;

    // Agregar algunas aristas
    miGrafo.agregarArista("A", "B", 5);
    miGrafo.agregarArista("A", "C", 3);
    miGrafo.agregarArista("B", "C", 2);
    miGrafo.agregarArista("B", "D", 4);

    cout << "=== Grafo Original ===" << endl;
    miGrafo.mostrarGrafo();

    // Prueba de eliminación de arista
    cout << "\n=== Eliminando arista (B - C) ===" << endl;
    miGrafo.EliminarArista("B", "C");
    miGrafo.mostrarGrafo();

    // Prueba de eliminación de vértice
    cout << "\n=== Eliminando vértice B ===" << endl;
    miGrafo.EliminarVertice("B");
    miGrafo.mostrarGrafo();


    // --- Prueba para el grafo no dirigido (usando Dijkstra) ---
    cout << "===== Prueba Grafo No Dirigido (Dijkstra) =====" << endl;
    // Definición del grafo para Dijkstra (aristas simples, no dirigidas)
    unordered_map<string, vector<pair<string, int>>> listaGrafo = {
        {"A", { {"B", 1}, {"C", 3}, {"D", 14} }},
        {"B", { {"A", 1}, {"C", 3}, {"E", 8}, {"J", 3}, {"F", 5} }},
        {"C", { {"A", 3}, {"B", 3}, {"D", 8}, {"E", 4}, {"G", 3}, {"H", 9} }},
        {"D", { {"A", 14}, {"C", 8}, {"H", 10}, {"I", 8} }},
        {"E", { {"B", 8}, {"C", 4}, {"G", 3}, {"J", 1} }},
        {"F", { {"B", 5}, {"J", 6} }},
        {"G", { {"C", 3}, {"H", 4}, {"L", 4}, {"K", 2}, {"J", 8}, {"E", 3} }},
        {"H", { {"C", 9}, {"D", 10}, {"I", 6}, {"L", 7}, {"G", 4} }},
        {"I", { {"D", 8}, {"H", 6}, {"L", 8}, {"M", 2} }},
        {"J", { {"F", 6}, {"E", 1}, {"G", 8}, {"K", 8} }},
        {"K", { {"J", 8}, {"G", 2}, {"L", 6} }},
        {"L", { {"K", 6}, {"G", 4}, {"H", 7}, {"I", 8}, {"M", 4} }},
        {"M", { {"L", 4}, {"I", 2} }}
    };

    // Crear un objeto Grafo utilizando el constructor que recibe la lista de adyacencia
    Grafo grafoNoDirigido(listaGrafo);
    grafoNoDirigido.mostrarGrafo();

    // Calcular caminos mínimos desde el nodo "A" utilizando Dijkstra
    auto resultadoDijkstra = grafoNoDirigido.caminoMasCorto("A");
    unordered_map<string, int> distanciasDijkstra = resultadoDijkstra.first;
    unordered_map<string, string> predecesoresDijkstra = resultadoDijkstra.second;

    cout << "\nDistancias (Dijkstra) desde 'A':" << endl;
    for (const auto &par : distanciasDijkstra) {
        cout << "Nodo: " << par.first << " - Distancia: " 
             << (par.second == INFINITO ? "Infinito" : to_string(par.second)) << endl;
    }
    cout << "\nPredecesores (Dijkstra):" << endl;
    for (const auto &par : predecesoresDijkstra) {
        cout << "Nodo: " << par.first << " - Predecesor: " 
             << (par.second.empty() ? "Nulo" : par.second) << endl;
    }

    // --- Prueba para el grafo dirigido (usando Bellman-Ford) ---
    cout << "\n===== Prueba Grafo Dirigido (Bellman-Ford) =====" << endl;
    // Definición del grafo dirigido para Bellman-Ford:
    // { "A": [("B", 1), ("C", 12), ("E", 4)],
    //   "B": [("G", 5), ("D", 1)],
    //   "C": [("H", 4)],
    //   "D": [("F", 0), ("C", -9), ("H", 3), ("G", 2)],
    //   "E": [("B", 2), ("F", -8)],
    //   "F": [ ],
    //   "G": [("H", 6)],
    //   "H": [ ] }
    unordered_map<string, vector<pair<string, int>>> listaGrafoDirigido = {
        {"A", { {"B", 1}, {"C", 12}, {"E", 4} }},
        {"B", { {"G", 5}, {"D", 1} }},
        {"C", { {"H", 4} }},
        {"D", { {"F", 0}, {"C", -9}, {"H", 3}, {"G", 2} }},
        {"E", { {"B", 2}, {"F", -8} }},
        {"F", { }},
        {"G", { {"H", 6} }},
        {"H", { }}
    };

    // Crear un objeto GrafoDirigido utilizando el constructor que recibe la lista de adyacencia
    GrafoDirigido grafoDirigido(listaGrafoDirigido);
    grafoDirigido.mostrarGrafo();

    // Calcular caminos mínimos desde el nodo "A" utilizando Bellman-Ford
    auto resultadoBellman = grafoDirigido.caminoMasCorto("A");
    unordered_map<string, int> distanciasBellman = resultadoBellman.first;
    unordered_map<string, string> predecesoresBellman = resultadoBellman.second;

    cout << "\nDistancias (Bellman-Ford) desde 'A':" << endl;
    for (const auto &par : distanciasBellman) {
        cout << "Nodo: " << par.first << " - Distancia: " 
             << (par.second == INFINITO ? "Infinito" : to_string(par.second)) << endl;
    }
    cout << "\nPredecesores (Bellman-Ford):" << endl;
    for (const auto &par : predecesoresBellman) {
        cout << "Nodo: " << par.first << " - Predecesor: " 
             << (par.second.empty() ? "Nulo" : par.second) << endl;
    }
    
    return 0;
}