#include <iostream>
#include <vector>
#include <string>
#include "core_numeric.h"
using namespace std;
class Esfera {
public:
     double radio;

     Esfera(double r) : radio(r) {}

     bool operator<(const Esfera& other) const {
          return radio < other.radio;
     }
};
class Coordenada {
public:
     double x, y;

     Coordenada(double x_, double y_) : x(x_), y(y_) {}

     bool operator<(const Coordenada& other) const {
          double d1 = x * x + y * y;
          double d2 = other.x * other.x + other.y * other.y;
          return d1 < d2;
     }
};

int main() {

    vector<int> v1 = {1, 2, 3};
    cout << "sum int: " << core_numeric::sum(v1) << endl; // OK

    vector<double> v2 = {1.5, 2.5, 3.0};
    cout << "sum double: " << core_numeric::sum(v2) << endl; // OK

    // NO COMPILA
    // vector<string> vs = {"a", "b", "c"};
    // core_numeric::sum(vs);
    // ERROR: string no cumple Arithmetic en esta implementacion

    // NO COMPILA
    // int x = 5;
    // core_numeric::sum(x);
    // ERROR: int no cumple Iterable

    vector<double> v3 = {1.0, 2.0, 3.0};
    cout << "mean double: " << core_numeric::mean(v3) << endl; // OK

    vector<int> v4 = {1, 2, 3};
    cout << "mean int: " << core_numeric::mean(v4) << endl; // OK

    // NO COMPILA
    // vector<string> vs2 = {"a", "b", "c"};
    // core_numeric::mean(vs2);
    // ERROR: string no cumple Divisible ni Arithmetic

    vector<double> v5 = {1.0, 2.0, 3.0};
    cout << "variance: " << core_numeric::variance(v5) << endl; // OK

    // NO COMPILA
    // vector<string> vs3 = {"a", "b", "c"};
    // core_numeric::variance(vs3);
    // ERROR: string no cumple Divisible ni Arithmetic

    vector<double> v6 = {1.0, 2.7, 0.3};
    cout << "max double: " << core_numeric::max(v6) << endl; // OK

    vector<int> v7 = {10, 5, 20};
    cout << "max int: " << core_numeric::max(v7) << endl; // OK

    // NO COMPILA
    // vector<string> vs4 = {"a", "b", "c"};
    // core_numeric::max(vs4);
    // ERROR: string esta excluido por la restriccion de max

    vector<double> v8 = {1.0, 2.0, 3.0};
    auto tr = core_numeric::transformacion(v8, [](double x) {
        return x * x;
    });
    cout << "transform reduce (x^2): " << tr << endl; // OK

    // NO COMPILA
    // core_numeric::transformacion(v8, [](string s) {
    //     return s;
    // });
    // ERROR: la lambda no acepta double, falla lambda_funciona

    cout << "sum_variadic: "
         << core_numeric::sum_variadic(1, 2, 3, 4) << endl; // OK

    cout << "mean_variadic: "
         << core_numeric::mean_variadic(1.0, 2.0, 3.0) << endl; // OK

    cout << "variance_variadic: "
         << core_numeric::variance_variadic(1, 2, 3, 4) << endl; // OK

    cout << "max_variadic: "
         << core_numeric::max_variadic(1, 5, 3, 2) << endl; // Ok

     vector<Esfera> esferas = {Esfera(1.0), Esfera(2.5), Esfera(0.8)};
     auto mayor = core_numeric::max(esferas);
     cout << "max esfera: " << mayor.radio << endl; // OK

    // NO COMPILA
    // core_numeric::sum_variadic(1, "hola", 3);
    // ERROR: "hola" no cumple Arithmetic

    // NO COMPILA
    // core_numeric::mean_variadic("a", "b");
    // ERROR: no cumplen Divisible ni Arithmetic

    // NO COMPILA
    // core_numeric::variance_variadic(1, "hola", 3);
    // ERROR: "hola" no cumple Arithmetic

    // NO COMPILA
    // core_numeric::variance_variadic("a", "b", "c");
    // ERROR: no cumplen Divisible ni Arithmetic

    // NO COMPILA
    // core_numeric::max_variadic(1, 2, "hola");
    // ERROR: "hola" no cumple Arithmetic

    // NO COMPILA
    // core_numeric::max_variadic("a", "b", "c");
    // ERROR: no cumplen Arithmetic

     vector<Coordenada> coords = {
          Coordenada(1, 1),
          Coordenada(3, 4),
          Coordenada(2, 2)
      };

     auto Mayor = core_numeric::max(coords);
     cout << "max coordenada: (" << Mayor.x << ", " << Mayor.y << ")" << endl;
    return 0;
}
