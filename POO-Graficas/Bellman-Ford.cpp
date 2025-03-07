#include <iostream>             // Biblioteca para entrada y salida de datos
#include <unordered_map>        // Biblioteca para diccionario
#include <vector>               // Biblioteca para vectores
#include <string>               // Biblioteca para cadenas de texto
#include <limits>               // Biblioteca para obtener valores máximos y mínimos
#include <cstdlib>              // Biblioteca para usar exit() y EXIT_FAILURE
#include <unordered_set>        // Biblioteca para conjuntos

using namespace std;            // Espacio de nombres estándar de C++

// Definimos un valor para el infinito (distancia máxima)
// numeric_limits<int>::max() retorna el valor máximo que puede almacenar un int
const int INFINITO = numeric_limits<int>::max();

/**
 * @brief Calcula las distancias mínimas desde el nodo 'origen' a todos los demás nodos
 *        del grafo utilizando el algoritmo de Bellman-Ford.
 *
 * @param grafo   Diccionario en el que cada clave es un nodo y su valor es un vector de pares (vecino, peso).
 * @param origen  Nodo de partida desde el cual se calcularán las distancias.
 * @return pair<unordered_map<string, int>, unordered_map<string, string>> 
 *         Primer elemento: Diccionario con la distancia mínima desde 'origen' a cada nodo.
 *         Segundo elemento: Diccionario que guarda el nodo anterior en el camino óptimo hacia cada nodo.
 */
pair<unordered_map<string, int>, unordered_map<string, string>> bellman_ford(
    const unordered_map<string, vector<pair<string, int>>>& grafo,
    const string& origen) {

     // Manejo de errores: Verificar que no existan aristas repetidas (con la misma dirección) en el grafo
     for (const auto &par : grafo) {
        const string &nodo = par.first;
        unordered_set<string> vecinosUnicos;  // Conjunto para almacenar los vecinos ya vistos
        for (const auto &arista : par.second) {
            string vecino = arista.first;
            // Si ya se encontró este vecino, se considera que la arista (nodo, vecino) está repetida
            if (vecinosUnicos.find(vecino) != vecinosUnicos.end()) {
                cerr << "Error: se detectó una arista repetida desde el nodo '"
                     << nodo << "' hacia el nodo '" << vecino << "'." << endl;
                exit(EXIT_FAILURE);
            }
            vecinosUnicos.insert(vecino);
        }
    }

    // Inicialización: establecer la distancia a todos los vértices como infinito y el predecesor como nulo (cadena vacía)
    unordered_map<string, int> distancia;
    unordered_map<string, string> predecesor;
    for (const auto &par : grafo) {
        // par.first es el nombre del nodo
        const string &nodo = par.first;
        distancia[nodo] = INFINITO;  // Se asigna infinito como distancia inicial
        predecesor[nodo] = "";       // Se asigna cadena vacía para indicar que no hay predecesor
    }
    // La distancia del nodo origen es 0, ya que es el punto de partida
    distancia[origen] = 0;

    // Número total de vértices en el grafo
    int num_vertices = grafo.size();

    // Relajación de todas las aristas |V|-1 veces
    // Se realizan |V|-1 iteraciones para asegurar que se encuentren los caminos más cortos
    for (int i = 1; i <= num_vertices - 1; i++) {
        // Para cada vértice u en el grafo
        for (const auto &par : grafo) {
            const string &u = par.first;
            // Para cada arista (u, v) con peso w
            for (const auto &arista : par.second) {
                string v = arista.first; // Nodo vecino
                int peso = arista.second;  // Peso de la arista
                // Si el nodo u es alcanzable (distancia distinta de INFINITO) y 
                // se encuentra un camino más corto hacia v, entonces actualizar
                if (distancia[u] != INFINITO && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    predecesor[v] = u;
                }
            }
        }
    }

    // Verificación de ciclos de peso negativo
    // Se recorre cada arista y se verifica si es posible mejorar la distancia
    // Lo que indicaría la existencia de un ciclo de peso negativo
    for (const auto &par : grafo) {
        const string &u = par.first;
        for (const auto &arista : par.second) {
            string v = arista.first;
            int peso = arista.second;
            if (distancia[u] != INFINITO && distancia[u] + peso < distancia[v]) {
                cout << "El grafo contiene un ciclo de peso negativo" << endl;
                // Terminar el algoritmo en caso de encontrar un ciclo negativo
                exit(EXIT_FAILURE);
            }
        }
    }

    // Retornar los diccionarios de distancias y predecesores
    return {distancia, predecesor};
}

int main() {
    // Ejemplo de grafo: cada nodo se asocia a una lista de pares (vecino, peso)
    unordered_map<string, vector<pair<string, int>>> grafo = {
        {"A", { {"B", 1}, {"C", 12}, {"E", 4} }},
        {"B", { {"G", 5}, {"D", 1} }},
        {"C", { {"H", 4} }},
        {"D", { {"F", 0}, {"C", -9}, {"H", 3}, {"G", 2} }},
        {"E", { {"B", 2}, {"F", -8} }},
        {"F", { }},
        {"G", { {"H", 6} }},
        {"H", { }}
    };

    string origen = "A";
    
    // Ejecutar el algoritmo de Bellman-Ford
    auto resultado = bellman_ford(grafo, origen);
    unordered_map<string, int> distancias = resultado.first;
    unordered_map<string, string> predecesores = resultado.second;

    // Mostrar las distancias mínimas desde el nodo origen
    cout << "Distancias minimas desde el nodo " << origen << ":\n";
    for (const auto &par : distancias) {
        cout << "Nodo: " << par.first << " - Distancia: ";
        if (par.second == INFINITO)
            cout << "Infinito";
        else
            cout << par.second;
        cout << endl;
    }

    // Mostrar los predecesores para reconstruir los caminos óptimos
    cout << "\nPredecesores en el camino optimo:\n";
    for (const auto &par : predecesores) {
        cout << "Nodo: " << par.first << " - Predecesor: " 
             << (par.second.empty() ? "Nulo" : par.second) << endl;
    }

    return 0;
}
