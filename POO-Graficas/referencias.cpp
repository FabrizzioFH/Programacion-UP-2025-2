// referencias.cpp
// Este archivo ilustra el uso de parámetros por valor y por referencia en C++,
// tanto en funciones como en lambdas, y cómo estos afectan el comportamiento del programa.

#include <iostream>
#include <vector>
#include <algorithm> // Para for_each

using namespace std;

// --------------------------------------------------------------------------
// Ejemplo 1: Funciones
// --------------------------------------------------------------------------

// Función que recibe el parámetro por valor (se copia el valor original)
void modificarPorValor(int x) {
    x += 10; // Modifica solo la copia local
    cout << "Dentro de modificarPorValor: x = " << x << endl;
}

// Función que recibe el parámetro por referencia (usa el símbolo '&')
// Esto permite modificar el valor original que se pasa a la función
void modificarPorReferencia(int &x) {
    x += 10; // Modifica directamente la variable original
    cout << "Dentro de modificarPorReferencia: x = " << x << endl;
}

// --------------------------------------------------------------------------
// Ejemplo 2: Lambdas
// --------------------------------------------------------------------------

int main() {
    cout << "----- Ejemplo 1: Paso por valor y por referencia en funciones -----" << endl;
    
    int a = 5;
    cout << "Valor original de a: " << a << endl;
    
    cout << "\nLlamada a modificarPorValor(a):" << endl;
    modificarPorValor(a);
    cout << "Después de modificarPorValor, a = " << a 
         << " (no se modificó porque se pasó por valor)" << endl;
    
    cout << "\nLlamada a modificarPorReferencia(a):" << endl;
    modificarPorReferencia(a);
    cout << "Después de modificarPorReferencia, a = " << a 
         << " (se modificó porque se pasó por referencia)" << endl;
    
    // --------------------------------------------------------------------------
    // Ejemplo 3: Lambdas con vectores
    // --------------------------------------------------------------------------
    cout << "\n----- Ejemplo 2: Lambdas, paso por copia vs. por referencia -----" << endl;
    
    vector<int> vec = {1, 2, 3};
    
    cout << "Vector original: ";
    for (int n : vec) {
        cout << n << " ";
    }
    cout << endl;
    
    // Lambda que recibe el vector por copia: se crea una copia del vector.
    // Se usa la palabra clave mutable para permitir modificar la copia local.
    auto lambdaPorCopia = [vec](int index, int nuevoValor) mutable {
        if (index < vec.size())
            vec[index] = nuevoValor;
        cout << "Dentro de lambdaPorCopia, vector modificado: ";
        for (int n : vec) {
            cout << n << " ";
        }
        cout << endl;
    };
    
    lambdaPorCopia(0, 100);
    cout << "Después de lambdaPorCopia, vector original: ";
    for (int n : vec) {
        cout << n << " ";
    }
    cout << " (no se modificó el original)" << endl;
    
    // Lambda que captura el vector por referencia: se usa [&vec] para modificar el vector original.
    auto lambdaPorReferencia = [&vec](int index, int nuevoValor) {
        if (index < vec.size())
            vec[index] = nuevoValor;
        cout << "Dentro de lambdaPorReferencia, vector modificado: ";
        for (int n : vec) {
            cout << n << " ";
        }
        cout << endl;
    };
    
    lambdaPorReferencia(1, 200);
    cout << "Después de lambdaPorReferencia, vector original: ";
    for (int n : vec) {
        cout << n << " ";
    }
    cout << " (se modificó el original)" << endl;
    
    return 0;
}
// g++ -o referencias referencias.cpp
// ./referencias