#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Grafo.h"

using namespace std;

int main() {
    // Lista de adyacencia para grafo no dirigido (vértices A a M) + una componente adicional (X, Y, Z)
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
        {"M", { {"L", 4}, {"I", 2} }},
        // Agregamos otra componente conexa: un triángulo entre X, Y y Z
        {"X", { {"Y", 1}, {"Z", 1} }},
        {"Y", { {"X", 1}, {"Z", 1} }},
        {"Z", { {"X", 1}, {"Y", 1} }}
    };

    // Crear el objeto Grafo (no dirigido)
    Grafo grafoNoDirigido(listaGrafo);

    // Obtener las componentes conexas utilizando el método implementado
    vector<vector<string>> componentes = grafoNoDirigido.ComponentesConexas();

    // Imprimir las componentes conexas encontradas
    cout << "Componentes conexas del grafo no dirigido:" << endl;
    for (size_t i = 0; i < componentes.size(); ++i) {
        cout << "Componente " << i + 1 << ": ";
        for (const auto &vertice : componentes[i]) {
            cout << vertice << " ";
        }
        cout << endl;
    }

    return 0;
}
// g++ -o prueba_Componenetes componentes.cpp Grafo.cpp
// ./prueba_Componenetes