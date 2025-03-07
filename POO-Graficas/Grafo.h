#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <limits>
#include <utility>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Definición de la constante INFINITO para representar la distancia máxima.
const int INFINITO = numeric_limits<int>::max();

/**
 * @brief Clase base que representa un grafo simple (no dirigido).
 *
 * Permite agregar aristas simples (no dirigidas) y calcular el camino más corto
 * desde un nodo de origen usando el algoritmo de Dijkstra.
 */
class Grafo {
protected:
    // Representación interna del grafo: cada nodo se asocia a un vector de pares (vecino, peso)
    unordered_map<string, vector<pair<string, int>>> listaAdyacencia;
public:
    /**
     * @brief Constructor por defecto: crea un grafo vacío.
     */
    Grafo();

    /**
     * @brief Constructor que inicializa el grafo con una lista de adyacencia dada.
     * @param listaInicial Lista de adyacencia inicial.
     */
    Grafo(const unordered_map<string, vector<pair<string, int>>>& listaInicial);

    // Destructor virtual
    virtual ~Grafo() {}

    /**
     * @brief Agrega una arista simple (no dirigida) entre dos nodos.
     *
     * Se agrega la arista en ambos sentidos: de origen a destino y de destino a origen.
     *
     * @param origen  Nodo de origen.
     * @param destino Nodo destino.
     * @param peso    Peso de la arista.
     */
    virtual void agregarArista(const string& origen, const string& destino, int peso);


    virtual void EliminarVertice(const string& vertice);

    virtual void EliminarArista(const string& origen, const string& destino);

    /**
     * @brief Muestra la representación del grafo por consola.
     */
    virtual void mostrarGrafo() const;

    virtual unordered_map<string, int> grado() const;

    vector<vector<string>> ComponentesConexas() const;

    /**
     * @brief Calcula el camino más corto desde el nodo 'origen' a todos los demás nodos usando Dijkstra.
     *
     * Se verifica que el grafo no contenga aristas con pesos negativos, ya que Dijkstra no los admite.
     *
     * @param origen Nodo de partida.
     * @return pair<unordered_map<string, int>, unordered_map<string, string>>
     *         Primer elemento: diccionario de distancias mínimas.
     *         Segundo elemento: diccionario de predecesores en el camino óptimo.
     */
    virtual pair<unordered_map<string, int>, unordered_map<string, string>> caminoMasCorto(const string& origen) const;
};

/**
 * @brief Clase derivada que representa un grafo dirigido.
 *
 * En este grafo, se permiten solo aristas dirigidas. El método agregarArista solo agrega la
 * arista en la dirección indicada y verifica (con manejo de errores) que no se intente agregar
 * una arista inversa (doble sentido). Además, el método para calcular caminos utiliza el algoritmo
 * de Bellman-Ford.
 */
class GrafoDirigido : public Grafo {
public:
    /**
     * @brief Constructor por defecto: crea un grafo dirigido vacío.
     */
    GrafoDirigido();

    /**
     * @brief Constructor que inicializa el grafo dirigido con una lista de adyacencia dada.
     * @param listaInicial Lista de adyacencia inicial.
     */
    GrafoDirigido(const unordered_map<string, vector<pair<string, int>>>& listaInicial);

    // Destructor virtual
    virtual ~GrafoDirigido() {}

    /**
     * @brief Agrega una arista dirigida del nodo 'origen' al nodo 'destino' con un peso.
     *
     * Verifica que no exista ya una arista inversa (de destino a origen) para evitar doble sentido.
     *
     * @param origen  Nodo de origen.
     * @param destino Nodo destino.
     * @param peso    Peso de la arista.
     */
    virtual void agregarArista(const string& origen, const string& destino, int peso) override;

    virtual void EliminarArista(const string& origen, const string& destino) override;

    virtual unordered_map<string, pair<int, int>> gradoDirigido() const;


    /**
     * @brief Calcula el camino más corto desde el nodo 'origen' usando el algoritmo de Bellman-Ford.
     *
     * @param origen Nodo de partida.
     * @return pair<unordered_map<string, int>, unordered_map<string, string>>
     *         Primer elemento: diccionario de distancias mínimas.
     *         Segundo elemento: diccionario de predecesores en el camino óptimo.
     */
    virtual pair<unordered_map<string, int>, unordered_map<string, string>> caminoMasCorto(const string& origen) const override;
};

#endif // GRAFO_H
