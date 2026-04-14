CoreNumeric

Implementación de una librería numérica genérica desarrollada en C++20 como parte de la Tarea #2 del curso Programación III.

Descripción

Este proyecto consiste en el diseño e implementación de una librería numérica moderna utilizando las herramientas de programación genérica disponibles en C++20. Se hace uso de concepts, templates, variadic templates y restricciones en tiempo de compilación para construir una API segura, expresiva y reutilizable.

Características principales
Uso de concepts para restringir tipos en tiempo de compilación.

Implementación de algoritmos numéricos genéricos.

Aplicación de requires para validar operaciones sobre tipos.

Uso de variadic templates y fold expressions.

Diferenciación de comportamiento mediante if constexpr.

Concepts implementados

Addable: permite operaciones de suma.

Divisible: permite operaciones de división.

Iterable: permite recorrer contenedores.



La librería incluye las siguientes funciones:

sum: suma de elementos de un contenedor.

mean: cálculo del promedio.

variance: cálculo de la varianza.

max: obtención del valor máximo.

transform_reduce: transformación y reducción de elementos.

Versiones variádicas de las funciones anteriores:

sum_variadic

mean_variadic

variance_variadic

max_variadic


Implementación de la librería.

Archivo de prueba (test.cpp) con casos válidos e inválidos.
Ejemplos de uso con tipos primitivos y tipos definidos por el usuario.


Notas:

Se incluyen casos donde el código compila correctamente y otros donde falla, explicando en cada caso qué concepto no se cumple.
