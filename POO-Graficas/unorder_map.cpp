#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    // Definir un unordered_map con claves de tipo string y valores enteros
    unordered_map<string, int> miMapa;

    // Insertar valores en el mapa
    miMapa["A"] = 10;
    miMapa["B"] = 20;
    miMapa["C"] = 30;

    cout << "=== Contenido del unordered_map ===" << endl;
    for (const auto& par : miMapa) {
        cout << par.first << " -> " << par.second << endl;
    }

    // Intentar encontrar una clave existente
    cout << "\n=== Probando .find() con una clave existente ===" << endl;
    auto it = miMapa.find("B");
    if (it != miMapa.end()) {
        cout << "Clave encontrada: " << it->first << " -> " << it->second << endl;
    } else {
        cout << "Clave NO encontrada en el mapa" << endl;
    }

    // Intentar encontrar una clave que NO existe
    cout << "\n=== Probando .find() con una clave inexistente ===" << endl;
    auto itNoExiste = miMapa.find("X");  // "X" no está en el mapa
    if (itNoExiste != miMapa.end()) {
        cout << "Clave encontrada: " << itNoExiste->first << " -> " << itNoExiste->second << endl;
    } else {
        cout << "Clave NO encontrada en el mapa" << endl;
    }
    return 0;
}
