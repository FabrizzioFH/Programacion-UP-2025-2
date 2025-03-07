// lambda.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Ejemplo 1: Lambda simple que suma dos números
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    cout << "Ejemplo 1: 5 + 3 = " << add(5, 3) << endl;

    // Ejemplo 2: Lambda para imprimir elementos de un vector
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "Ejemplo 2: Elementos del vector: ";
    // Utilizando lambda en for_each
    for_each(vec.begin(), vec.end(), [](int x) {
        cout << x << " ";
    });
    cout << endl;

    // Ejemplo 3: Lambda que captura una variable por valor
    int factor = 2;
    auto multiply = [factor](int x) -> int {
        return x * factor;
    };
    cout << "Ejemplo 3: 4 * factor (2) = " << multiply(4) << endl;

    // Ejemplo 4: Lambda que captura por referencia para modificar una variable externa
    int sum = 0;
    for_each(vec.begin(), vec.end(), [&sum](int x) {
        sum += x;
    });
    cout << "Ejemplo 4: Suma de los elementos del vector = " << sum << endl;

    return 0;
}
