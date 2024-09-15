#include <iostream>
#include <string>
#include <locale> // Incluye <locale> para la configuraci�n de localizaci�n
#include <limits> // Para std::numeric_limits

using namespace std;

// Definici�n de una estructura para un Producto
struct Producto {
    string codigo;  // Cambiado a string para permitir letras y n�meros
    string nombre;
    float cantidad; // Cambiado a float para permitir decimales
};

// Definir un tama�o m�ximo para el inventario
const int MAX_PRODUCTOS = 100;
Producto inventario[MAX_PRODUCTOS];
int totalProductos = 0;

// Funci�n para validar la entrada de un n�mero decimal
float leerDecimal(const string& mensaje) {
    float valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) { // Si la entrada no es un n�mero decimal
            cin.clear(); // Limpiar el estado de error del flujo de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada inv�lida
            cout << "Entrada inv�lida. Por favor, ingrese un n�mero decimal: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
            return valor;
        }
    }
}

// Funci�n para validar la entrada de una cadena de texto
string leerCadena(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

// Funci�n para agregar un producto al inventario
void agregarProducto() {
    if (totalProductos < MAX_PRODUCTOS) {
        Producto nuevoProducto;
        
        // Leer el c�digo del producto
        nuevoProducto.codigo = leerCadena("Ingrese el c�digo del producto: ");
        
        // Verificaci�n para evitar c�digos duplicados
        for (int i = 0; i < totalProductos; i++) {
            if (nuevoProducto.codigo == inventario[i].codigo) {
                cout << "Este c�digo ya est� en uso." << endl;
                nuevoProducto.codigo = leerCadena("Ingrese un c�digo diferente: ");
                i = -1; // Reinicia el ciclo para verificar el nuevo c�digo ingresado
            }
        }

        // Leer el nombre del producto
        nuevoProducto.nombre = leerCadena("Ingrese el nombre del producto: ");
        
        // Leer la cantidad del producto
        nuevoProducto.cantidad = leerDecimal("Ingrese la cantidad del producto (puede ser decimal): ");

        inventario[totalProductos] = nuevoProducto;
        totalProductos++;

        cout << "Producto agregado exitosamente.\n";
        cout << "Total de productos: " << totalProductos << endl;
    } else {
        cout << "El inventario est� lleno.\n";
    }
}

// Funci�n para mostrar todos los productos del inventario
void mostrarProductos() {
    if (totalProductos == 0) {
        cout << "No hay productos en el inventario.\n";
    } else {
        cout << "Inventario de productos:\n";
        for (int i = 0; i < totalProductos; i++) {
            cout << "C�digo: " << inventario[i].codigo
                 << " | Nombre: " << inventario[i].nombre
                 << " | Cantidad: " << inventario[i].cantidad << endl;
        }
    }
}

// Funci�n para actualizar la cantidad de un producto
void actualizarProducto() {
    string codigo;
    codigo = leerCadena("Ingrese el c�digo del producto a actualizar: ");
    for (int i = 0; i < totalProductos; i++) {
        if (inventario[i].codigo == codigo) {
            inventario[i].cantidad = leerDecimal("Ingrese la nueva cantidad: ");
            cout << "Nueva cantidad agregada exitosamente." << endl;
            cout << "Cantidad actualizada a: " << inventario[i].cantidad << endl;
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

// Funci�n para eliminar un producto del inventario
void eliminarProducto() {
    string codigo;
    codigo = leerCadena("Ingrese el c�digo del producto a eliminar: ");
    for (int i = 0; i < totalProductos; i++) {
        if (inventario[i].codigo == codigo) {
            for (int j = i; j < totalProductos - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            totalProductos--;
            cout << "Producto eliminado con �xito." << endl;
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

// Funci�n principal con men�
int main() {
    setlocale(LC_CTYPE, "es_ES.UTF-8"); // Configura la localizaci�n para manejar caracteres especiales en espa�ol
    int opcion;
    do {
        cout << "\n--- Sistema de Gesti�n de Inventario ---\n";
        cout << "1. Agregar producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Actualizar cantidad de producto\n";
        cout << "4. Eliminar producto\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opci�n: ";

        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {  // Validaci�n de n�mero para opci�n del men�
            cout << "Error: Ingrese una de las opciones dadas.\n";
            cin.clear();  // Limpiar estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada no v�lida
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                mostrarProductos();
                break;
            case 3:
                actualizarProducto();
                break;
            case 4:
                eliminarProducto();
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opci�n no v�lida.\n";
        }
    } while (opcion != 5);

    return 0;
} //JHONY ABRAHAM DE LE�N P�REZ 0905-24-22282
