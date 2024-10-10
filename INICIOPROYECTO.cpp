#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string apellido;
    string carrera;
    string departamento;
    string municipio;
    string telefonoPersonal;
    string telefonoCasa;
    string telefonoEmergencia;
    string correoElectronico;  
    int diaNacimiento, mesNacimiento, anioNacimiento;
    int edad;
    int anioIngreso;
};

const string departamentos[] = {
    "Guatemala", "Sacatepéquez", "Chimaltenango", "Escuintla", "Santa Rosa",
    "Sololá", "Totonicapán", "Quetzaltenango", "Suchitepéquez", "Retalhuleu",
    "San Marcos", "Huehuetenango", "Quiché", "Baja Verapaz", "Alta Verapaz",
    "Petén", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa", "El Progreso"
};

const string municipios[22][5] = {
    {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula"},
    {"Antigua Guatemala", "Ciudad Vieja", "Jocotenango", "Pastores", "Sumpango"},
    {"Chimaltenango", "San Martín de los Canes", "El Tejar", "San José Poaquil", "San Juan Comalapa"},
    {"Escuintla", "Santa Lucía Cotzumalguapa", "La Democracia", "San José", "Siquinalá"},
    {"Santa Rosa de Lima", "Cuilapa", "San Juan Tecuaco", "Barberena", "Chiquimulilla"},
    {"Solalá", "San Juan La Laguna", "San Pedro La Laguna", "Panajachel", "Santa Catarina Palopó"},
    {"Totonicapán", "San Cristóbal Totonicapán", "San Francisco el Alto", "San Andrés Xecul", "Momostenango"},
    {"Quetzaltenango", "Salcajá", "San Martín Sacatepéquez", "Sibilia", "Zunil"},
    {"Mazatenango", "San Bernardino", "El Asintal", "San Antonio Suchitepéquez", "Santo Domingo Suchitepéquez"},
    {"Retalhuleu", "San Sebastián", "San Martín Zapotitlán", "Tecoanapa", "Champerico"},
    {"San Marcos", "San Pedro Sacatepéquez", "Malacatán", "San Antonio Sacatepéquez", "Sibinal"},
    {"Huehuetenango", "Aguacatán", "Chiantla", "Colotenango", "Concepción Huista"},
    {"Santa Cruz del Quiché", "San Antonio Ilotenango", "San Bartolomé Jocotenango", "San Pedro Jocopilas", "Patzité"},
    {"Salamá", "Granados", "Rabinal", "San Jerónimo", "El Chol"},
    {"Cobán", "San Pedro Carchá", "San Cristóbal Verapaz", "Tactic", "Tucurú"},
    {"Flores", "Melchor de Mencos", "Poptún", "San Benito", "San Francisco"},
    {"Puerto Barrios", "Livingston", "El Estor", "Morales", "Los Amates"},
    {"Gualán", "Río Hondo", "La Unión", "San Jorge", "Estanzuela"},
    {"Chiquimula", "Jocotán", "Esquipulas", "Camotán", "Ipala"},
    {"Monjas", "San Pedro Pinula", "San Carlos Alzatate", "San Luis Jilotepeque", "Jalapa"},
    {"Jutiapa", "Jalpatagua", "El Progreso", "Asunción Mita", "Santa Catarina Mita"},
    {"Guastatoya", "Morazán", "Sanarate", "Sansare", "San Agustín Acasaguastlán"}
};

int generarCodigo() {
    static int codigo = 1000; 
    return codigo++;
}

int calcularEdad(int diaNacimiento, int mesNacimiento, int anioNacimiento) {
    time_t t = time(0);
    tm* ahora = localtime(&t);

    int anioActual = 1900 + ahora->tm_year;
    int mesActual = 1 + ahora->tm_mon;
    int diaActual = ahora->tm_mday;

    int edad = anioActual - anioNacimiento;

    if (mesNacimiento > mesActual || (mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        edad--;
    }
    
    return edad;
}

string escogerCarrera() {
    int opcion;
    cout << "\nSeleccione una carrera:\n";
    cout << "1. Ingeniería en sistemas\n";
    cout << "2. Administración de empresas\n";
    cout << "3. Derecho\n";
    while (true) {
        cout << "Ingrese el número de la carrera: ";
        if (cin >> opcion && opcion >= 1 && opcion <= 3) {
            switch(opcion) {
                case 1: return "Ingeniería en sistemas";
                case 2: return "Administración de empresas";
                case 3: return "Derecho";
            }
        } else {
            cout << "Valor inválido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void escogerDireccion(string& departamento, string& municipio) {
    int opcionDepto;
    cout << "\nSeleccione un departamento:\n";
    for (int i = 0; i < 22; i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    while (true) {
        cout << "Ingrese el número del departamento: ";
        if (cin >> opcionDepto && opcionDepto >= 1 && opcionDepto <= 22) {
            departamento = departamentos[opcionDepto - 1];
            break;
        } else {
            cout << "Valor inválido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int opcionMuni;
    cout << "\nSeleccione un municipio en " << departamento << ":\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << municipios[opcionDepto - 1][i] << endl;
    }
    while (true) {
        cout << "Ingrese el número del municipio: ";
        if (cin >> opcionMuni && opcionMuni >= 1 && opcionMuni <= 5) {
            municipio = municipios[opcionDepto - 1][opcionMuni - 1];
            break;
        } else {
            cout << "Valor inválido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void mostrarEstudiantes(const vector<Estudiante>& estudiantes) {
    cout << "\n--- Lista de Estudiantes Registrados ---\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        const Estudiante& estudiante = estudiantes[i];
        cout << "ID: " << estudiante.id << endl;
        cout << "Nombre: " << estudiante.nombre << " " << estudiante.apellido << endl;
        cout << "Carrera: " << estudiante.carrera << endl;
        cout << "Departamento: " << estudiante.departamento << endl;
        cout << "Municipio: " << estudiante.municipio << endl;
        cout << "Teléfono Personal: " << estudiante.telefonoPersonal << endl;
        cout << "Teléfono de Casa: " << estudiante.telefonoCasa << endl;
        cout << "Teléfono de Emergencia: " << estudiante.telefonoEmergencia << endl;
        cout << "Correo Electrónico: " << estudiante.correoElectronico << endl;
        cout << "Fecha de Nacimiento: " << estudiante.diaNacimiento << "/" 
             << estudiante.mesNacimiento << "/" << estudiante.anioNacimiento << endl;
        cout << "Edad: " << estudiante.edad << endl;
        cout << "Año de Ingreso: " << estudiante.anioIngreso << endl;
        cout << "----------------------------------------\n";
    }
}

void registrarEstudiante(vector<Estudiante>& estudiantes) {
    Estudiante nuevoEstudiante; 
    nuevoEstudiante.id = generarCodigo(); 

    cin.ignore();  
    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nuevoEstudiante.nombre);
    cout << "Ingrese el apellido del estudiante: ";
    getline(cin, nuevoEstudiante.apellido);
    
    nuevoEstudiante.carrera = escogerCarrera();
    
    escogerDireccion(nuevoEstudiante.departamento, nuevoEstudiante.municipio);
    
    cout << "Ingrese el número de teléfono personal: ";
    cin >> nuevoEstudiante.telefonoPersonal;
    cout << "Ingrese el número de teléfono de casa: ";
    cin >> nuevoEstudiante.telefonoCasa;
    cout << "Ingrese el número de teléfono de emergencia: ";
    cin >> nuevoEstudiante.telefonoEmergencia;

    cout << "Ingrese el correo electrónico: ";
    cin >> nuevoEstudiante.correoElectronico;

    // Nueva entrada para la fecha de nacimiento
    while (true) {
        cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
        char separator; // Para leer el '/' como separador
        if (cin >> nuevoEstudiante.diaNacimiento >> separator 
                  >> nuevoEstudiante.mesNacimiento >> separator 
                  >> nuevoEstudiante.anioNacimiento) {
            if (nuevoEstudiante.diaNacimiento >= 1 && nuevoEstudiante.diaNacimiento <= 31 &&
                nuevoEstudiante.mesNacimiento >= 1 && nuevoEstudiante.mesNacimiento <= 12) {
                break;
            }
        }
        cout << "Valor inválido. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.diaNacimiento, nuevoEstudiante.mesNacimiento, nuevoEstudiante.anioNacimiento);
    
    while (true) {
        cout << "Ingrese el año de ingreso a la universidad: ";
        if (cin >> nuevoEstudiante.anioIngreso) break;
        else {
            cout << "Valor inválido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    estudiantes.push_back(nuevoEstudiante);

    cout << "Estudiante registrado exitosamente!\n";
    mostrarEstudiantes(estudiantes);
}

void menu() {
    vector<Estudiante> estudiantes;
    int opcion;

    while (true) {
        cout << "\n--- Sistema de Registro de Estudiantes ---\n";
        cout << "1. Registrar un estudiante\n";
        cout << "2. Salir\n";

        if (!(cin >> opcion)) {
            cout << "Valor inválido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Repetir el ciclo
        }

        if (opcion == 1) {
            registrarEstudiante(estudiantes);
        } else if (opcion == 2) {
            cout << "Saliendo del programa...\n";
            break;
        } else {
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
