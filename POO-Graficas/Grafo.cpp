#include "Grafo.h"
#include <cstdlib> // Para exit() y EXIT_FAILURE
#include <stack> // Para la implementación de ComponentesConexas

// ====================== IMPLEMENTACIÓN DE LA CLASE GRAFO ======================

Grafo::Grafo() {
    // Constructor por defecto: se crea un grafo vacío
}

Grafo::Grafo(const unordered_map<string, vector<pair<string, int>>>& listaInicial)
    : listaAdyacencia(listaInicial) {
    // Constructor que inicializa el grafo con la lista de adyacencia dada
}

void Grafo::agregarArista(const string& origen, const string& destino, int peso) {
    // Agregar nodos si no existen en el grafo
    if (listaAdyacencia.find(origen) == listaAdyacencia.end())
        listaAdyacencia[origen] = vector<pair<string, int>>();
    if (listaAdyacencia.find(destino) == listaAdyacencia.end())
        listaAdyacencia[destino] = vector<pair<string, int>>();

    // En un grafo no dirigido, se agrega la arista en ambos sentidos
    listaAdyacencia[origen].push_back(make_pair(destino, peso));
    listaAdyacencia[destino].push_back(make_pair(origen, peso));
}

void Grafo::EliminarVertice(const string& vertice) {
    // 1️⃣ Eliminar la entrada completa del vértice en la lista de adyacencia
    listaAdyacencia.erase(vertice);

    // 2️⃣ Recorrer cada nodo y eliminar manualmente las referencias al vértice
    for (auto& par : listaAdyacencia) {
        auto& vecinos = par.second;

        // Bucle para eliminar manualmente elementos en un vector
        for (auto it = vecinos.begin(); it != vecinos.end();) {
            if (it->first == vertice) {
                it = vecinos.erase(it); // Borrar y avanzar el iterador
            } else {
                ++it; // Solo avanzar el iterador
            }
        }
    }
}
void Grafo::EliminarArista(const string& origen, const string& destino) {
    // Verificamos si los nodos existen
    if (listaAdyacencia.find(origen) != listaAdyacencia.end()) {
        auto& vecinos = listaAdyacencia[origen];
        // Eliminamos la arista origen -> destino
        vecinos.erase(remove_if(vecinos.begin(), vecinos.end(),
                                [&destino](const pair<string, int>& arista) {
                                    return arista.first == destino;
                                }),
                      vecinos.end());
    }

    // Como es un grafo NO dirigido, eliminamos la arista destino -> origen
    if (listaAdyacencia.find(destino) != listaAdyacencia.end()) {
        auto& vecinos = listaAdyacencia[destino];
        vecinos.erase(remove_if(vecinos.begin(), vecinos.end(),
                                [&origen](const pair<string, int>& arista) {
                                    return arista.first == origen;
                                }),
                      vecinos.end());
    }
}

void Grafo::mostrarGrafo() const {
    for (const auto &par : listaAdyacencia) {
        cout << par.first << " -> ";
        for (const auto &vecino : par.second) {
            cout << vecino.first << "(" << vecino.second << ") ";
        }
        cout << endl;
    }
}

unordered_map<string, int> Grafo::grado() const {
    unordered_map<string, int> grados;
    for (const auto& par : listaAdyacencia) {
         // Cada entrada contiene los vecinos (cada uno representa una incidencia)
         grados[par.first] = par.second.size();
    }
    return grados;
}


vector<vector<string>> Grafo::ComponentesConexas() const {
    unordered_set<string> visitados;
    vector<vector<string>> componentes;
    
    for (const auto& par : listaAdyacencia) {
         const string& vertice = par.first;
         if (visitados.find(vertice) == visitados.end()) {
              vector<string> componente;
              stack<string> s;
              s.push(vertice);
              while (!s.empty()) {
                  string actual = s.top();
                  s.pop();
                  if (visitados.find(actual) == visitados.end()) {
                      visitados.insert(actual);
                      componente.push_back(actual);
                      for (const auto& vecino : listaAdyacencia.at(actual)) {
                          if (visitados.find(vecino.first) == visitados.end())
                              s.push(vecino.first);
                      }
                  }
              }
              componentes.push_back(componente);
         }
    }
    return componentes;
}


pair<unordered_map<string, int>, unordered_map<string, string>> Grafo::caminoMasCorto(const string& origen) const {
    // Verificar que no existan aristas con pesos negativos (Dijkstra no admite negativos)
    for (const auto &par : listaAdyacencia) {
        for (const auto &arista : par.second) {
            if (arista.second < 0) {
                cerr << "Error: el grafo contiene una arista con peso negativo: "
                     << par.first << " -> " << arista.first 
                     << " (peso: " << arista.second << ")." << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    
    // Inicialización de diccionarios para distancias y predecesores
    unordered_map<string, int> distancia;
    unordered_map<string, string> predecesor;
    for (const auto &par : listaAdyacencia) {
        distancia[par.first] = INFINITO;
        predecesor[par.first] = "";
    }
    distancia[origen] = 0;
    
    // Conjunto de nodos no visitados
    unordered_set<string> no_visitados;
    for (const auto &par : listaAdyacencia) {
        no_visitados.insert(par.first);
    }
    
    // Algoritmo de Dijkstra
    while (!no_visitados.empty()) {
        string nodo_actual;
        int distancia_minima = INFINITO;
        for (const string &nodo : no_visitados) {
            if (distancia[nodo] < distancia_minima) {
                distancia_minima = distancia[nodo];
                nodo_actual = nodo;
            }
        }
        no_visitados.erase(nodo_actual);
        for (const auto &vecino_par : listaAdyacencia.at(nodo_actual)) {
            string nodo_vecino = vecino_par.first;
            int peso = vecino_par.second;
            if (distancia[nodo_actual] != INFINITO &&
                distancia[nodo_actual] + peso < distancia[nodo_vecino]) {
                distancia[nodo_vecino] = distancia[nodo_actual] + peso;
                predecesor[nodo_vecino] = nodo_actual;
            }
        }
    }
    return {distancia, predecesor};
}

// ================== IMPLEMENTACIÓN DE LA SUBCLASE GRAFODIRIGIDO ==================

GrafoDirigido::GrafoDirigido() : Grafo() {
    // Constructor por defecto: se crea un grafo dirigido vacío
}

GrafoDirigido::GrafoDirigido(const unordered_map<string, vector<pair<string, int>>>& listaInicial)
    : Grafo(listaInicial) {
    // Constructor que inicializa el grafo dirigido con la lista de adyacencia dada
}

void GrafoDirigido::agregarArista(const string& origen, const string& destino, int peso) {
    // Verificar si ya existe la arista inversa (de destino a origen) para evitar doble sentido
    bool existeAristaInversa = false;
    if (listaAdyacencia.find(destino) != listaAdyacencia.end()) {
        for (const auto &par : listaAdyacencia[destino]) {
            if (par.first == origen) {
                existeAristaInversa = true;
                break;
            }
        }
    }
    if (existeAristaInversa) {
        cerr << "Error: se detectó una arista de doble sentido en el grafo dirigido ("
             << origen << " -> " << destino << ")." << endl;
        exit(EXIT_FAILURE);
    }
    if (listaAdyacencia.find(origen) == listaAdyacencia.end())
        listaAdyacencia[origen] = vector<pair<string, int>>();
    if (listaAdyacencia.find(destino) == listaAdyacencia.end())
        listaAdyacencia[destino] = vector<pair<string, int>>();

    // En un grafo dirigido, solo se agrega la arista en la dirección indicada
    listaAdyacencia[origen].push_back(make_pair(destino, peso));
}

void GrafoDirigido::EliminarArista(const string& origen, const string& destino) {
    // Verificar si el nodo origen existe en el grafo
    if (listaAdyacencia.find(origen) != listaAdyacencia.end()) {
        auto& vecinos = listaAdyacencia[origen];
        // Buscar y eliminar la arista origen -> destino (únicamente en esa dirección)
        vecinos.erase(remove_if(vecinos.begin(), vecinos.end(),
                                [&destino](const pair<string, int>& arista) {
                                    return arista.first == destino;
                                }),
                      vecinos.end());
    }
}

unordered_map<string, pair<int, int>> GrafoDirigido::gradoDirigido() const {
    unordered_map<string, pair<int, int>> grados;
    // Inicializamos: para cada vértice, el segundo valor (exgrado) es el tamaño del vector de adyacencia.
    for (const auto& par : listaAdyacencia) {
         grados[par.first] = {0, static_cast<int>(par.second.size())};
    }
    // Calculamos el ingrado recorriendo todas las aristas
    for (const auto& par : listaAdyacencia) {
         for (const auto& vecino : par.second) {
              // Aseguramos que el vértice exista en el mapa
              if (grados.find(vecino.first) == grados.end())
                  grados[vecino.first] = {0, 0};
              grados[vecino.first].first++;  // Incrementa el ingrado
         }
    }
    return grados;
}

pair<unordered_map<string, int>, unordered_map<string, string>> GrafoDirigido::caminoMasCorto(const string& origen) const {
    // Implementación del algoritmo de Bellman-Ford para grafos dirigidos
    unordered_map<string, int> distancia;
    unordered_map<string, string> predecesor;
    for (const auto &par : listaAdyacencia) {
        distancia[par.first] = INFINITO;
        predecesor[par.first] = "";
    }
    distancia[origen] = 0;
    int num_vertices = listaAdyacencia.size();
    // Relajación de todas las aristas |V| - 1 veces
    for (int i = 1; i <= num_vertices - 1; i++) {
        for (const auto &par : listaAdyacencia) {
            const string &u = par.first;
            for (const auto &arista : par.second) {
                string v = arista.first;
                int peso = arista.second;
                if (distancia[u] != INFINITO && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    predecesor[v] = u;
                }
            }
        }
    }
    // Verificación de ciclos de peso negativo
    for (const auto &par : listaAdyacencia) {
        const string &u = par.first;
        for (const auto &arista : par.second) {
            string v = arista.first;
            int peso = arista.second;
            if (distancia[u] != INFINITO && distancia[u] + peso < distancia[v]) {
                cerr << "Error: el grafo dirigido contiene un ciclo de peso negativo." << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    return {distancia, predecesor};
}