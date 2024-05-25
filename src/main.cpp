#include <iostream>
#include <string>
#include <cmath>
#include "exprtk.hpp"

// Función que define la ecuación a evaluar
double f(const std::string& equation, double x) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(equation, expression);

    return expression.value();
}

// Implementación del método de la regla falsa
double false_position_method(const std::string& equation, double a, double b, double tol, int max_iter) {
    double fa = f(equation, a);
    double fb = f(equation, b);

    if (fa * fb > 0) {
        std::cerr << "La función debe tener signos opuestos en los extremos a y b." << std::endl;
        return std::nan("");
    }

    double c = a;
    for (int i = 0; i < max_iter; ++i) {
        c = (a * fb - b * fa) / (fb - fa);
        double fc = f(equation, c);

        if (std::abs(fc) < tol) {
            return c;
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    return c;
}

int main() {
    std::string equation;
    double a, b, tol;
    int max_iter;

    std::cout << "Ingrese la ecuación (ejemplo: x^3 - 4*x - 9): ";
    std::getline(std::cin, equation);

    std::cout << "Ingrese el valor inicial a: ";
    std::cin >> a;

    std::cout << "Ingrese el valor inicial b: ";
    std::cin >> b;

    std::cout << "Ingrese la tolerancia: ";
    std::cin >> tol;

    std::cout << "Ingrese el número máximo de iteraciones: ";
    std::cin >> max_iter;

    double root = false_position_method(equation, a, b, tol, max_iter);

    if (!std::isnan(root)) {
        std::cout << "La raíz aproximada es: " << root << std::endl;
    } else {
        std::cout << "No se pudo encontrar una raíz en el intervalo dado." << std::endl;
    }

    return 0;
}
