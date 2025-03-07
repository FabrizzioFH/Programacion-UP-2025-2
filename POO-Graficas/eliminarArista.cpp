#include "Grafo.h"

int main() {
    Grafo miGrafo;

    // Agregar aristas antes de eliminar
    miGrafo.agregarArista("A", "B", 5);
    miGrafo.agregarArista("A", "C", 3);
    miGrafo.agregarArista("B", "C", 2);

    cout << "=== Grafo Original ===" << endl;
    miGrafo.mostrarGrafo();

    // Eliminar una arista
    cout << "\n=== Eliminando arista (B - C) ===" << endl;
    miGrafo.EliminarArista("B", "C");
    miGrafo.mostrarGrafo();

    return 0;
}
// $ g++ -o Prueba_EliminarArista eliminarArista.cpp Grafo.cpp
// $ ./Prueba_EliminarArista