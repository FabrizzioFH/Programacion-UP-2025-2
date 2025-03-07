#include <chrono>    // Para medir el tiempo de ejecución
#include <fstream>   // Para escribir en un archivo
#include "Grafo.h"

using namespace std;
using namespace std::chrono;

int main() {
    // Definición de un grafo de prueba (no dirigido)
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

    Grafo grafoNoDirigido(listaGrafo);

    // Medir el tiempo de ejecución del método caminoMasCorto("A") usando Dijkstra
    auto inicio = high_resolution_clock::now();
    auto resultado = grafoNoDirigido.caminoMasCorto("A");
    auto fin = high_resolution_clock::now();

    // Calcular la duración en microsegundos
    auto duracion = duration_cast<microseconds>(fin - inicio).count();
    cout << "Tiempo de ejecución (Dijkstra): " << duracion << " microsegundos." << endl;

    // Puedes guardar los resultados en un archivo CSV para graficarlos luego con Python o gnuplot
    ofstream archivo("tiempos_ejecucion.csv");
    if (archivo.is_open()) {
        // Escribimos la cabecera: tamaño del grafo, tiempo de ejecución, etc.
        archivo << "Metodo,TiempoMicrosegundos" << endl;
        archivo << "Dijkstra," << duracion << endl;
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir los datos." << endl;
    }

    return 0;
}
