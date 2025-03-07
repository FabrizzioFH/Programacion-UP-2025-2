#include <iostream> // Biblioteca para entrada y salida de datos
#include <unordered_map> // Biblioteca para diccionarios
#include <vector> // Biblioteca para vectores
#include <string> // Biblioteca para cadenas de texto
#include <limits> // Biblioteca para valores máximos y mínimos
#include <unordered_set> // Biblioteca para conjuntos

using namespace std; // Espacio de nombres estándar de C++

// Definimos un valor para el infinito (distancia máxima)
/* La funcion numeric_limits es parte de <limits> y retorna 
 el valor máximo que puede almacenar una variable de tipo int */
const int INFINITO = numeric_limits<int>::max(); // 2147483647
/* const indica que el valor de la variable no puede ser modificado 
   durante la ejecución del programa */

/**
 * @brief Calcula las distancias mínimas desde el nodo 'origen' a todos los demás nodos
 *        del grafo utilizando el algoritmo de Dijkstra.
 *
 * @param grafo   Diccionario en el que cada clave es un nodo y su valor es un vector de pares (vecino, peso).
 * @param origen  Nodo de partida desde el cual se calcularán las distancias.
 * @return pair<unordered_map<string, int>, unordered_map<string, string>> 
 *         Primer elemento: Diccionario con la distancia mínima desde 'origen' a cada nodo.
 *         Segundo elemento: Diccionario que guarda el nodo anterior en el camino óptimo hacia cada nodo.
 */


/* unordered_map es una clase de la STL que representa un diccionario 
   (clave, valor) que no tiene un orden específico. */
/* el simbolo & indica que la variable es una referencia, es decir, 
   que se pasa la dirección de memoria de la variable y no una copia de la misma */
pair<unordered_map<string, int>, unordered_map<string, string>> dijkstra(
    const unordered_map<string, vector<pair<string, int>>>& grafo, 
    const string& origen) {

    // Manejo de errores: Verificar que no existan aristas con peso negativo en el grafo
    for (const auto &par : grafo) {
        for (const auto &vecino_par : par.second) {
            if (vecino_par.second < 0) {
                cerr << "Error: el grafo contiene una arista con peso negativo: "
                     << par.first << " -> " << vecino_par.first 
                     << " (peso: " << vecino_par.second << ")." << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    
    // Inicializar diccionarios para distancias y predecesores
    unordered_map<string, int> distancia;
    unordered_map<string, string> predecesor;
    
    // Para cada nodo en el grafo, se asigna distancia infinita y predecesor nulo (cadena vacía)
    /* auto es un tipo de dato que se utiliza para declarar una variable 
       cuyo tipo se deduce del valor que se le asigna, en este caso,
       se deduce que el tipo de dato es un par (string, vector<pair<string, int>>) */
    for (const auto &par : grafo) {
        // par.first es el nombre del nodo, par.second es la lista de vecinos
        const string &nodo = par.first;
        distancia[nodo] = INFINITO;
        predecesor[nodo] = "";
    }
    // La distancia del nodo origen es 0
    distancia[origen] = 0;
    
    // Crear el conjunto de nodos no visitados
    /* unordered_set es una clase de la STL que representa un conjunto 
       de elementos que no tienen un orden específico. */
    unordered_set<string> no_visitados;
    for (const auto &par : grafo) {
        // insert es un método de la clase unordered_set que agrega un elemento al conjunto
        no_visitados.insert(par.first);
    }
    
    // Mientras queden nodos no visitados
    while (!no_visitados.empty()) {
        // Seleccionar el nodo con la menor distancia estimada
        string nodo_actual;
        int distancia_minima = INFINITO;
        for (const string &nodo : no_visitados) {
            if (distancia[nodo] < distancia_minima) {
                distancia_minima = distancia[nodo];
                nodo_actual = nodo;
            }
        }
        
        // Marcar el nodo actual como visitado
        no_visitados.erase(nodo_actual);
        
        // Recorrer cada vecino del nodo actual
        for (const auto &vecino_par : grafo.at(nodo_actual)) {
            string nodo_vecino = vecino_par.first;
            int peso = vecino_par.second;
            // Calcular la distancia alternativa desde el nodo origen hasta el vecino
            if (distancia[nodo_actual] != INFINITO && 
                distancia[nodo_actual] + peso < distancia[nodo_vecino]) {
                distancia[nodo_vecino] = distancia[nodo_actual] + peso;
                predecesor[nodo_vecino] = nodo_actual;
            }
        }
    }
    
    return {distancia, predecesor};
}

int main() {
    // Ejemplo de grafo: cada nodo se asocia a una lista de pares (vecino, peso)
    unordered_map<string, vector<pair<string, int>>> grafo = {
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
        {"L", { {"K", 6}, {"G", 4}, {"H", 7}, {"I", 8}, {"M", 4} }}
    };
    // tambien se pueden agregar elementos al grafo de la siguiente manera
    grafo["M"] = { {"L", 4}, {"I", 2} };
    
    string origen = "A";
    // Ejecutar el algoritmo de Dijkstra
    auto resultado = dijkstra(grafo, origen);
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
   
        /* el operador ternario es una forma de simplificar un if-else,
           en este caso, si la cadena es vacía, se imprime "Nulo",
           de lo contrario, se imprime la cadena */
             << (par.second.empty() ? "Nulo" : par.second) << endl;
    }
    
    return 0;
}
