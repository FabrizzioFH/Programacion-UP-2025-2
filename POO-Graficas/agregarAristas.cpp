#include "Grafo.h"

int main() {
    Grafo miGrafo;

    // Agregar algunas aristas
    miGrafo.agregarArista("A", "B", 5);
    miGrafo.agregarArista("A", "C", 3);
    miGrafo.agregarArista("B", "C", 2);

    cout << "=== Grafo con aristas añadidas ===" << endl;
    miGrafo.mostrarGrafo();

    return 0;
}
// $ g++ -o Prueba_agregarArista agregarAristas.cpp Grafo.cpp 
// $ ./Prueba_agregarArista