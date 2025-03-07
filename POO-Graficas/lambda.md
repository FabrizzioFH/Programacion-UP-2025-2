# ¿Qué es y cómo se usa una función Lambda en C++?
Una lambda es una función anónima que puedes definir “en el momento” sin tener que declararla formalmente como función aparte.
La sintaxis general es:
```cpp
[capturas](parámetros) -> tipo_de_retorno {
    // Cuerpo de la función
};
```
- **Capturas**: Especifican qué variables del entorno se usan dentro de la lambda (por valor [=], por referencia [&] o combinaciones).
- **Parámetros**: Lista de parámetros de la función.
- **Tipo de retorno**: Opcional; si se omite, el compilador lo deduce.
Cuerpo: Código a ejecutar.