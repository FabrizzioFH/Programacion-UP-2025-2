#include "Grafo.h"

int main() {
    // Definir el grafo dirigido con pesos (incluye un peso negativo)
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

    // Crear el grafo dirigido
    GrafoDirigido grafoDirigido(listaGrafoDirigido);
    grafoDirigido.mostrarGrafo();

    // Calcular caminos mínimos desde 'A' usando Bellman-Ford
    auto resultado = grafoDirigido.caminoMasCorto("A");

    cout << "\n=== Distancias desde A (Bellman-Ford) ===" << endl;
    for (const auto& par : resultado.first) {
        cout << "Nodo: " << par.first << " - Distancia: " << par.second << endl;
    }
    cout << "\n=== Predecesores desde A (Bellman-Ford) ===" << endl;
    for (const auto& par : resultado.second) {
        cout << "Nodo: " << par.first << " - Predecesor: " << par.second << endl;
    }

    return 0;
}
// $ g++ -o Prueba_BellmanFord pruebaBellman-Ford.cpp Grafo.cpp
// $ ./Prueba_BellmanFord