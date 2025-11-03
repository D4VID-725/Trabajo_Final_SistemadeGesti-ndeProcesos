#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

using namespace std;

//------------------------------------------------------
// ESTRUCTURAS DE DATOS
//------------------------------------------------------

struct Ruta {
    int id;
    string nombre;
    int nivelCongestion; // 1 = bajo, 5 = alto
    string estado; // "fluido", "moderado", "congestionado"
    Ruta* siguiente;
};

struct Vehiculo {
    int id;
    string placa;
    string tipo; // "auto", "bus", "moto"
    string rutaActual;
    Vehiculo* siguiente;
};

struct Semaforo {
    string interseccion;
    string color; // "verde", "amarillo", "rojo"
    Semaforo* siguiente; // Pila
};

//------------------------------------------------------
// Punteros globales
//------------------------------------------------------

Ruta* listaRutas = NULL;
Vehiculo* colaVehiculos = NULL;
Semaforo* pilaSemaforos = NULL;

//------------------------------------------------------
// FUNCIONES PARA RUTAS (lista enlazada)
//------------------------------------------------------

void registrarRuta() {
    Ruta* nueva = new Ruta;
    cout << "\nIngrese ID de la ruta: ";
    cin >> nueva->id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nombre de la ruta: ";
    getline(cin, nueva->nombre);

    cout << "Nivel de congestion (1-5): ";
    cin >> nueva->nivelCongestion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (nueva->nivelCongestion >= 4)
        nueva->estado = "congestionado";
    else if (nueva->nivelCongestion == 3)
        nueva->estado = "moderado";
    else
        nueva->estado = "fluido";

    nueva->siguiente = NULL;

    if (!listaRutas)
        listaRutas = nueva;
    else {
        Ruta* aux = listaRutas;
        while (aux->siguiente)
            aux = aux->siguiente;
        aux->siguiente = nueva;
    }
    cout << "\nRuta registrada correctamente.\n";
    Sleep(1000);
}

void mostrarRutas() {
    if (!listaRutas) {
        cout << "\nNo hay rutas registradas.\n";
        return;
    }
    cout << "\n===== LISTADO DE RUTAS =====\n";
    Ruta* aux = listaRutas;
    while (aux) {
        cout << "ID: " << aux->id << " | " << aux->nombre
             << " | Congestion: " << aux->nivelCongestion
             << " | Estado: " << aux->estado << endl;
        aux = aux->siguiente;
    }
}

//------------------------------------------------------
// FUNCIONES PARA VEHÍCULOS (cola)
//------------------------------------------------------

void agregarVehiculo() {
    Vehiculo* nuevo = new Vehiculo;
    cout << "\nIngrese ID del vehículo: ";
    cin >> nuevo->id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Placa: ";
    getline(cin, nuevo->placa);

    cout << "Tipo (auto, bus, moto): ";
    getline(cin, nuevo->tipo);

    cout << "Ruta actual: ";
    getline(cin, nuevo->rutaActual);

    nuevo->siguiente = NULL;

    if (!colaVehiculos)
        colaVehiculos = nuevo;
    else {
        Vehiculo* aux = colaVehiculos;
        while (aux->siguiente)
            aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
    cout << "\nVehículo agregado a la cola.\n";
}

void despacharVehiculo() {
    if (!colaVehiculos) {
        cout << "\nNo hay vehículos en la cola.\n";
        return;
    }
    Vehiculo* aux = colaVehiculos;
    colaVehiculos = colaVehiculos->siguiente;
    cout << "\nVehículo con placa " << aux->placa << " ha sido despachado.\n";
    delete aux;
}

void mostrarVehiculos() {
    if (!colaVehiculos) {
        cout << "\nNo hay vehículos registrados.\n";
        return;
    }
    cout << "\n===== COLA DE VEHÍCULOS =====\n";
    Vehiculo* aux = colaVehiculos;
    while (aux) {
        cout << "ID: " << aux->id << " | Placa: " << aux->placa
             << " | Tipo: " << aux->tipo
             << " | Ruta: " << aux->rutaActual << endl;
        aux = aux->siguiente;
    }
}

//------------------------------------------------------
// FUNCIONES PARA SEMÁFOROS (pila)
//------------------------------------------------------

void cambiarSemaforo() {
    Semaforo* nuevo = new Semaforo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nInterseccion: ";
    getline(cin, nuevo->interseccion);

    cout << "Color actual (verde/amarillo/rojo): ";
    getline(cin, nuevo->color);

    nuevo->siguiente = pilaSemaforos;
    pilaSemaforos = nuevo;

    cout << "\nEstado del semaforo actualizado.\n";
}

void revertirSemaforo() {
    if (!pilaSemaforos) {
        cout << "\nNo hay registros de semaforos.\n";
        return;
    }
    Semaforo* aux = pilaSemaforos;
    pilaSemaforos = pilaSemaforos->siguiente;
    cout << "\nSe revirtio el cambio del semaforo en " << aux->interseccion << ".\n";
    delete aux;
}

void mostrarSemaforos() {
    if (!pilaSemaforos) {
        cout << "\nNo hay cambios registrados.\n";
        return;
    }
    cout << "\n===== PILA DE SEMAFOROS =====\n";
    Semaforo* aux = pilaSemaforos;
    while (aux) {
        cout << "Interseccion: " << aux->interseccion << " | Color: " << aux->color << endl;
        aux = aux->siguiente;
    }
}

//------------------------------------------------------
// MENÚ PRINCIPAL
//------------------------------------------------------

int main() {
    int opcion;
    do {
        cout << "\n========== OPTIMIZADOR DE TRAFICO ==========\n";
        cout << "1. Registrar ruta\n";
        cout << "2. Mostrar rutas\n";
        cout << "3. Agregar vehiculo\n";
        cout << "4. Despachar vehiculo\n";
        cout << "5. Mostrar vehiculos\n";
        cout << "6. Cambiar estado de semaforo\n";
        cout << "7. Revertir cambio de semaforo\n";
        cout << "8. Mostrar pila de semaforos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarRuta(); break;
            case 2: mostrarRutas(); break;
            case 3: agregarVehiculo(); break;
            case 4: despacharVehiculo(); break;
            case 5: mostrarVehiculos(); break;
            case 6: cambiarSemaforo(); break;
            case 7: revertirSemaforo(); break;
            case 8: mostrarSemaforos(); break;
            case 0: cout << "\nSaliendo del sistema...\n"; break;
            default: cout << "\nOpcion invalida.\n";
        }
        Sleep(1200);
    } while (opcion != 0);
    return 0;
}

