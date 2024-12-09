#ifndef AVL_HPP
#define AVL_HPP

#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

struct AVLN {
   std::string categoria;  // Nombre de la categoría
   int index;              // Índice del anime en el arreglo 'animesArray'.
   int height;             // Altura del nodo.
   AVLN* left;             // Puntero al hijo izquierdo.
   AVLN* right;            // Puntero al hijo derecho;
   std::vector<int> productos; // Lista de productos asociados a esta categoría.

   AVLN(std::string n, int i)
       : categoria(n), index(i), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
private:
   AVLN* root;

   // Función para obtener la altura de un nodo.
   int height(AVLN* node) {
       return (node == nullptr) ? 0 : node->height;
   }

   // Función para obtener el factor de balance de un nodo.
   int balanceFactor(AVLN* node) {
       return (node == nullptr) ? 0 : height(node->left) - height(node->right);
   }

   // Función para rotar el subárbol a la derecha.
   AVLN* rotateRight(AVLN* y) {
       AVLN* x = y->left;
       AVLN* T2 = x->right;

       x->right = y;
       y->left = T2;

       y->height = std::max(height(y->left), height(y->right)) + 1;
       x->height = std::max(height(x->left), height(x->right)) + 1;

       return x;
   }

   // Función para rotar el subárbol a la izquierda.
   AVLN* rotateLeft(AVLN* x) {
       AVLN* y = x->right;
       AVLN* T2 = y->left;

       y->left = x;
       x->right = T2;

       x->height = std::max(height(x->left), height(x->right)) + 1;
       y->height = std::max(height(y->left), height(y->right)) + 1;

       return y;
   }

   // Función para insertar un nodo en el árbol.
   AVLN* insertar(AVLN* nodo, std::string categoria, int productoIndex) {
       if (!nodo) {
           AVLN* nuevoNodo = new AVLN(categoria, productoIndex);
           return nuevoNodo;
       }

       if (categoria < nodo->categoria) {
           nodo->left = insertar(nodo->left, categoria, productoIndex);
       } else if (categoria > nodo->categoria) {
           nodo->right = insertar(nodo->right, categoria, productoIndex);
       } else {
           nodo->productos.push_back(productoIndex); // Si ya existe, agregamos el producto.
           return nodo;
       }

       nodo->height = std::max(height(nodo->left), height(nodo->right)) + 1;

       int balance = balanceFactor(nodo);

       // Rotaciones según el factor de balance.
       if (balance > 1 && categoria < nodo->left->categoria) {
           return rotateRight(nodo);
       }
       if (balance < -1 && categoria > nodo->right->categoria) {
           return rotateLeft(nodo);
       }
       if (balance > 1 && categoria > nodo->left->categoria) {
           nodo->left = rotateLeft(nodo->left);
           return rotateRight(nodo);
       }
       if (balance < -1 && categoria < nodo->right->categoria) {
           nodo->right = rotateRight(nodo->right);
           return rotateLeft(nodo);
       }

       return nodo;
   }

   // Normaliza la cadena para eliminar espacios y convertir a minúsculas.
   std::string normalizeString(std::string str) {
       // Convertir a minúsculas
       std::transform(str.begin(), str.end(), str.begin(), ::tolower);

       // Eliminar espacios extra
       str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

       return str;
   }

   // Función para medir la distancia de Levenshtein (similaridad) entre dos cadenas
   int levenshteinDistance(const std::string& a, const std::string& b) {
       std::vector<std::vector<int>> dp(a.size() + 1, std::vector<int>(b.size() + 1));

       for (size_t i = 0; i <= a.size(); ++i) {
           for (size_t j = 0; j <= b.size(); ++j) {
               if (i == 0) {
                   dp[i][j] = j;
               } else if (j == 0) {
                   dp[i][j] = i;
               } else {
                   dp[i][j] = std::min({
                       dp[i - 1][j] + 1,
                       dp[i][j - 1] + 1,
                       dp[i - 1][j - 1] + (a[i - 1] != b[j - 1])
                   });
               }
           }
       }
       return dp[a.size()][b.size()];
   }

   // Función para buscar la categoría más cercana a la query
   AVLN* searchCategory(AVLN* node, const std::string& query, AVLN* bestMatch = nullptr) {
       if (node == nullptr) {
           return bestMatch;  // Si el nodo es nulo, devolvemos la mejor coincidencia
       }

       // Normaliza la query y la categoría antes de compararlas
       std::string normalizedQuery = normalizeString(query);
       std::string normalizedCategoria = normalizeString(node->categoria);

       // Si la categoría contiene la query, la encontramos
       if (normalizedCategoria.find(normalizedQuery) != std::string::npos) {
           return node;  // Si la categoría contiene la query, devuelve el nodo
       }

       // Comparar distancia de Levenshtein para encontrar la mejor coincidencia
       if (bestMatch == nullptr || levenshteinDistance(normalizedQuery, normalizedCategoria) < levenshteinDistance(normalizedQuery, bestMatch->categoria)) {
           bestMatch = node;
       }

       // Continuar buscando en los subárboles
       if (normalizedQuery < normalizedCategoria) {
           return searchCategory(node->left, normalizedQuery, bestMatch);
       } else {
           return searchCategory(node->right, normalizedQuery, bestMatch);
       }
   }

public:
   AVL() : root(nullptr) {}

   // Función pública para insertar un producto en el árbol
   void insertarProducto(std::string categoria, int productoIndex) {
       root = insertar(root, categoria, productoIndex);
   }

   // Función pública para buscar una categoría exacta o la más cercana
   AVLN* searchCategory(const std::string& categoria) {
       return searchCategory(root, categoria);
   }
};

#endif // AVL_HPP
