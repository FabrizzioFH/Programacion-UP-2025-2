Pseudocódigo del método `componentesConexas`:

```plaintext
vector<vector<string>> ComponentesConexas() const {
    unordered_set<string> visitados;
    vector<vector<string>> componentes;
    
    // Itera por cada vértice en el grafo
    for (cada vértice v en listaAdyacencia) {
         if (v no ha sido visitado) {
              vector<string> componente;
              stack<string> s;
              s.push(v);
              
              while (s no esté vacía) {
                  string actual = s.top();
                  s.pop();
                  
                  if (actual no ha sido visitado) {
                      marcar actual como visitado;
                      añadir actual a la componente;
                      para cada vecino w de actual:
                          si w no ha sido visitado, s.push(w);
                  }
              }
              
              añadir componente a componentes;
         }
    }
    return componentes;
}


```