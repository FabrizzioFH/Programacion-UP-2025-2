#include "Grafo.h"

int main() {
    Grafo miGrafo;

    // Agregar aristas antes de eliminar vértices
    miGrafo.agregarArista("A", "B", 5);
    miGrafo.agregarArista("A", "C", 3);
    miGrafo.agregarArista("B", "C", 2);
    miGrafo.agregarArista("B", "D", 4);

    cout << "=== Grafo Original ===" << endl;
    miGrafo.mostrarGrafo();

    // Eliminar un vértice
    cout << "\n=== Eliminando vértice B ===" << endl;
    miGrafo.EliminarVertice("B");
    miGrafo.mostrarGrafo();

    return 0;
}
// $ g++ -o Prueba_EliminarVertice eliminarVertice.cpp Grafo.cpp
// $ ./Prueba_EliminarVertice