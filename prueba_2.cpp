// ============================================
// PROYECTO: Simulador de Tráfico - Cusco
// Descripción: Este programa simula el tráfico en
// diferentes rutas del Cusco y recomienda rutas alternas
// en base a niveles aleatorios de congestión.
// ============================================

#include <iostream>
#include <string>
#include <windows.h>  // Para Sleep()
#include <cstdlib>    // Para rand(), srand()
#include <ctime>      // Para time()
#include <iomanip>    // Para formato de salida

using namespace std;

// ==========================================================
// ESTRUCTURAS DE DATOS
// ==========================================================
struct Ruta {
    string principal;
    string alterna1;
    string alterna2;
    float distancia;   // en kilómetros
    int trafico;       // 0 = bajo, 1 = medio, 2 = alto
    float tiempo;      // tiempo estimado en minutos
};

// ==========================================================
// FUNCIONES
// ==========================================================

// Genera un nivel de tráfico aleatorio y actualiza el tiempo estimado
void actualizarTrafico(Ruta &r) {
    r.trafico = rand() % 3; // 0, 1 o 2
    switch (r.trafico) {
        case 0: r.tiempo = r.distancia * 1.2; break; // tráfico fluido
        case 1: r.tiempo = r.distancia * 2.0; break; // tráfico medio
        case 2: r.tiempo = r.distancia * 3.5; break; // tráfico alto
    }
}

// Muestra una recomendación según el nivel de tráfico
void mostrarRecomendacion(const Ruta &r) {
    cout << "\n--------------------------------------------\n";
    cout << "Ruta principal: " << r.principal << endl;
    cout << "Distancia: " << fixed << setprecision(1) << r.distancia << " km" << endl;
    cout << "Nivel de tráfico: ";

    if (r.trafico == 0) cout << "BAJO\n";
    else if (r.trafico == 1) cout << "MEDIO\n";
    else cout << "ALTO\n";

    cout << "Tiempo estimado: " << fixed << setprecision(1) << r.tiempo << " minutos\n";

    // Recomendaciones según tráfico
    if (r.trafico == 2) {
        cout << "?? Tráfico alto detectado. Se recomienda tomar:\n";
        cout << "   - Alterna 1: " << r.alterna1 << "\n";
        cout << "   - Alterna 2: " << r.alterna2 << "\n";
    } else if (r.trafico == 1) {
        cout << "?? Tráfico medio. Puede considerar usar " << r.alterna1 << " para reducir tiempo.\n";
    } else {
        cout << "? Tráfico fluido. Puede continuar por " << r.principal << ".\n";
    }
}

// Muestra todas las rutas con sus datos actuales
void mostrarTodasLasRutas(Ruta rutas[], int n) {
    cout << "\n================= LISTADO DE RUTAS =================\n";
    cout << left << setw(25) << "Ruta Principal"
         << setw(15) << "Distancia(km)"
         << setw(12) << "Trafico"
         << setw(15) << "Tiempo(min)\n";
    cout << "----------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        string nivel;
        if (rutas[i].trafico == 0) nivel = "Bajo";
        else if (rutas[i].trafico == 1) nivel = "Medio";
        else nivel = "Alto";
        cout << left << setw(25) << rutas[i].principal
             << setw(15) << rutas[i].distancia
             << setw(12) << nivel
             << setw(15) << fixed << setprecision(1) << rutas[i].tiempo << endl;
    }
}

// Simula varios ciclos de análisis de tráfico
void ejecutarSimulacion(Ruta rutas[], int n, int ciclos) {
    for (int i = 1; i <= ciclos; i++) {
        cout << "\n===== CICLO DE SIMULACIÓN " << i << " =====\n";
        cout << "Analizando niveles de tráfico...\n";
        Sleep(1000);

        for (int j = 0; j < n; j++) {
            actualizarTrafico(rutas[j]);
            mostrarRecomendacion(rutas[j]);
            Sleep(700);
        }

        cout << "\nFin del ciclo " << i << ". Actualizando datos...\n";
        Sleep(1500);
    }
}

// ==========================================================
// FUNCIÓN PRINCIPAL
// ==========================================================
int main() {
    srand((unsigned)time(0));

    const int NUM_RUTAS = 5;
    Ruta rutas[NUM_RUTAS] = {
        {"Av. El Sol", "Av. La Cultura", "Av. Tullumayo", 3.5, 0, 0},
        {"Av. La Cultura (UNSAAC)", "Circunvalacion", "Av. Los Incas", 4.2, 0, 0},
        {"Av. De La Paz", "Av. Los Angeles", "Av. 28 de Julio", 2.8, 0, 0},
        {"Av. Tullumayo", "Av. Collasuyo", "Av. Pachacutec", 3.9, 0, 0},
        {"Wanchaq", "Av. Garcilaso", "Av. Velasco Astete", 2.5, 0, 0}
    };

    int opcion, ciclos;

    do {
        cout << "\n============================================\n";
        cout << "    SIMULADOR DE TRÁFICO - CUSCO (Preliminar)\n";
        cout << "============================================\n";
        cout << "1. Iniciar simulación\n";
        cout << "2. Mostrar rutas actuales\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\nIngrese la cantidad de ciclos de simulación: ";
                cin >> ciclos;
                ejecutarSimulacion(rutas, NUM_RUTAS, ciclos);
                break;
            case 2:
                mostrarTodasLasRutas(rutas, NUM_RUTAS);
                break;
            case 3:
                cout << "\nSaliendo del simulador...\n";
                break;
            default:
                cout << "\nOpción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 3);

    cout << "\n? Simulación finalizada.\n";
    return 0;
}

