```plaintext
Función encontrarComponentesConexas(Grafo):
    visitados ← conjunto vacío
    componentes ← lista vacía

    Para cada vértice v en Grafo:
        Si v no está en visitados:
            componente ← lista vacía
            Llamar a DFS(v, visitados, componente)
            Agregar componente a componentes

    Retornar componentes

Función DFS(v, visitados, componente):
    Agregar v a visitados
    Agregar v a componente
    Para cada vecino u de v:
        Si u no está en visitados:
            Llamar a DFS(u, visitados, componente)
``` 