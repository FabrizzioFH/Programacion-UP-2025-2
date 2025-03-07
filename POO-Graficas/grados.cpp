#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Grafo.h"

using namespace std;

int main() {
    // --- Grafo No Dirigido ---
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

    // Se crea el objeto Grafo usando el constructor que recibe la lista de adyacencia.
    Grafo grafoNoDirigido(listaGrafo);

    cout << "Grados en grafo no dirigido:" << endl;
    // Se llama al método grado() (implementado en la clase Grafo) para obtener el grado (número de vecinos)
    unordered_map<string, int> grados = grafoNoDirigido.grado();
    for (const auto &par : grados) {
        cout << par.first << " -> " << par.second << endl;
    }

    // --- Grafo Dirigido ---
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

    // Se crea el objeto GrafoDirigido usando su constructor.
    GrafoDirigido grafoDirigido(listaGrafoDirigido);

    cout << "\nGrados en grafo dirigido (Ingrado, Exgrado):" << endl;
    // Se llama al método gradoDirigido() (definido en GrafoDirigido) para obtener ingrado y exgrado
    unordered_map<string, pair<int, int>> gradosDirigido = grafoDirigido.gradoDirigido();
    for (const auto &par : gradosDirigido) {
        cout << par.first << " -> (" << par.second.first << ", " << par.second.second << ")" << endl;
    }

    return 0;
}
// g++ -o prueba_grados grados.cpp Grafo.cpp
// ./prueba_grados