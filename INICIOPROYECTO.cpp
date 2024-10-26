#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include <fstream>
#include <sstream>
#include <cstdlib> // Para usar atoi

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

    string toString() const {
        stringstream ss;
        ss << id << "," << nombre << "," << apellido << "," << carrera << "," << departamento << "," << municipio << ","
           << telefonoPersonal << "," << telefonoCasa << "," << telefonoEmergencia << "," << correoElectronico << ","
           << diaNacimiento << "," << mesNacimiento << "," << anioNacimiento << "," << edad << "," << anioIngreso;
        return ss.str();
    }
};

const string departamentos[] = {
    "Guatemala", "Sacatep�quez", "Chimaltenango", "Escuintla", "Santa Rosa",
    "Solol�", "Totonicap�n", "Quetzaltenango", "Suchitep�quez", "Retalhuleu",
    "San Marcos", "Huehuetenango", "Quich�", "Baja Verapaz", "Alta Verapaz",
    "Pet�n", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa", "El Progreso"
};

const string municipios[22][5] = {
    {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula"},
    {"Antigua Guatemala", "Ciudad Vieja", "Jocotenango", "Pastores", "Sumpango"},
    {"Chimaltenango", "San Mart�n de los Canes", "El Tejar", "San Jos� Poaquil", "San Juan Comalapa"},
    {"Escuintla", "Santa Luc�a Cotzumalguapa", "La Democracia", "San Jos�", "Siquinal�"},
    {"Santa Rosa de Lima", "Cuilapa", "San Juan Tecuaco", "Barberena", "Chiquimulilla"},
    {"Solal�", "San Juan La Laguna", "San Pedro La Laguna", "Panajachel", "Santa Catarina Palop�"},
    {"Totonicap�n", "San Crist�bal Totonicap�n", "San Francisco el Alto", "San Andr�s Xecul", "Momostenango"},
    {"Quetzaltenango", "Salcaj�", "San Mart�n Sacatep�quez", "Sibilia", "Zunil"},
    {"Mazatenango", "San Bernardino", "El Asintal", "San Antonio Suchitep�quez", "Santo Domingo Suchitep�quez"},
    {"Retalhuleu", "San Sebasti�n", "San Mart�n Zapotitl�n", "Tecoanapa", "Champerico"},
    {"San Marcos", "San Pedro Sacatep�quez", "Malacat�n", "San Antonio Sacatep�quez", "Sibinal"},
    {"Huehuetenango", "Aguacat�n", "Chiantla", "Colotenango", "Concepci�n Huista"},
    {"Santa Cruz del Quich�", "San Antonio Ilotenango", "San Bartolom� Jocotenango", "San Pedro Jocopilas", "Patzit�"},
    {"Salam�", "Granados", "Rabinal", "San Jer�nimo", "El Chol"},
    {"Cob�n", "San Pedro Carch�", "San Crist�bal Verapaz", "Tactic", "Tucur�"},
    {"Flores", "Melchor de Mencos", "Popt�n", "San Benito", "San Francisco"},
    {"Puerto Barrios", "Livingston", "El Estor", "Morales", "Los Amates"},
    {"Gual�n", "R�o Hondo", "La Uni�n", "San Jorge", "Estanzuela"},
    {"Chiquimula", "Jocot�n", "Esquipulas", "Camot�n", "Ipala"},
    {"Monjas", "San Pedro Pinula", "San Carlos Alzatate", "San Luis Jilotepeque", "Jalapa"},
    {"Jutiapa", "Jalpatagua", "El Progreso", "Asunci�n Mita", "Santa Catarina Mita"},
    {"Guastatoya", "Moraz�n", "Sanarate", "Sansare", "San Agust�n Acasaguastl�n"}
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
    cout << "1. Ingenier�a en sistemas\n";
    cout << "2. Administraci�n de empresas\n";
    cout << "3. Derecho\n";
    while (true) {
        cout << "Ingrese el n�mero de la carrera: ";
        if (cin >> opcion && opcion >= 1 && opcion <= 3) {
            switch(opcion) {
                case 1: return "Ingenier�a en sistemas";
                case 2: return "Administraci�n de empresas";
                case 3: return "Derecho";
            }
        } else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
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
        cout << "Ingrese el n�mero del departamento: ";
        if (cin >> opcionDepto && opcionDepto >= 1 && opcionDepto <= 22) {
            departamento = departamentos[opcionDepto - 1];
            break;
        } else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
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
        cout << "Ingrese el n�mero del municipio: ";
        if (cin >> opcionMuni && opcionMuni >= 1 && opcionMuni <= 5) {
            municipio = municipios[opcionDepto - 1][opcionMuni - 1];
            break;
        } else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
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
        cout << "Tel�fono Personal: " << estudiante.telefonoPersonal << endl;
        cout << "Tel�fono de Casa: " << estudiante.telefonoCasa << endl;
        cout << "Tel�fono de Emergencia: " << estudiante.telefonoEmergencia << endl;
        cout << "Correo Electr�nico: " << estudiante.correoElectronico << endl;
        cout << "Fecha de Nacimiento: " << estudiante.diaNacimiento << "/" 
             << estudiante.mesNacimiento << "/" << estudiante.anioNacimiento << endl;
        cout << "Edad: " << estudiante.edad << endl;
        cout << "A�o de Ingreso: " << estudiante.anioIngreso << endl;
        cout << "----------------------------------------\n";
    }
}

void guardarEstudianteEnArchivo(const Estudiante& estudiante) {
    ofstream archivo("estudiantes.txt", ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << estudiante.toString() << endl;
        archivo.close();
    } else {
        cout << "Error al abrir el archivo para guardar los datos.\n";
    }
}

void mostrarDatosDesdeArchivo() {
    ifstream archivo("estudiantes.txt");
    if (archivo.is_open()) {
        string linea;
        cout << "\n--- Datos de Estudiantes Registrados desde el Archivo ---\n";
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            Estudiante estudiante;
            string temp;

            getline(ss, temp, ','); estudiante.id = atoi(temp.c_str());
            getline(ss, estudiante.nombre, ',');
            getline(ss, estudiante.apellido, ',');
            getline(ss, estudiante.carrera, ',');
            getline(ss, estudiante.departamento, ',');
            getline(ss, estudiante.municipio, ',');
            getline(ss, estudiante.telefonoPersonal, ',');
            getline(ss, estudiante.telefonoCasa, ',');
            getline(ss, estudiante.telefonoEmergencia, ',');
            getline(ss, estudiante.correoElectronico, ',');
            getline(ss, temp, ','); estudiante.diaNacimiento = atoi(temp.c_str());
            getline(ss, temp, ','); estudiante.mesNacimiento = atoi(temp.c_str());
            getline(ss, temp, ','); estudiante.anioNacimiento = atoi(temp.c_str());
            getline(ss, temp, ','); estudiante.edad = atoi(temp.c_str());
            getline(ss, temp, ','); estudiante.anioIngreso = atoi(temp.c_str());

            // Mostrar en formato de lista
            cout << "ID: " << estudiante.id << endl;
            cout << "Nombre: " << estudiante.nombre << " " << estudiante.apellido << endl;
            cout << "Carrera: " << estudiante.carrera << endl;
            cout << "Departamento: " << estudiante.departamento << endl;
            cout << "Municipio: " << estudiante.municipio << endl;
            cout << "Tel�fono Personal: " << estudiante.telefonoPersonal << endl;
            cout << "Tel�fono de Casa: " << estudiante.telefonoCasa << endl;
            cout << "Tel�fono de Emergencia: " << estudiante.telefonoEmergencia << endl;
            cout << "Correo Electr�nico: " << estudiante.correoElectronico << endl;
            cout << "Fecha de Nacimiento: " << estudiante.diaNacimiento << "/" 
                 << estudiante.mesNacimiento << "/" << estudiante.anioNacimiento << endl;
            cout << "Edad: " << estudiante.edad << endl;
            cout << "A�o de Ingreso: " << estudiante.anioIngreso << endl;
            cout << "----------------------------------------\n";
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo para mostrar los datos.\n";
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
    
    cout << "Ingrese el n�mero de tel�fono personal: ";
    cin >> nuevoEstudiante.telefonoPersonal;
    cout << "Ingrese el n�mero de tel�fono de casa: ";
    cin >> nuevoEstudiante.telefonoCasa;
    cout << "Ingrese el n�mero de tel�fono de emergencia: ";
    cin >> nuevoEstudiante.telefonoEmergencia;

    cout << "Ingrese el correo electr�nico: ";
    cin >> nuevoEstudiante.correoElectronico;

    while (true) {
        cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
        char separator; 
        if (cin >> nuevoEstudiante.diaNacimiento >> separator 
                  >> nuevoEstudiante.mesNacimiento >> separator 
                  >> nuevoEstudiante.anioNacimiento) {
            if (nuevoEstudiante.diaNacimiento >= 1 && nuevoEstudiante.diaNacimiento <= 31 &&
                nuevoEstudiante.mesNacimiento >= 1 && nuevoEstudiante.mesNacimiento <= 12) {
                break;
            }
        }
        cout << "Valor inv�lido. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.diaNacimiento, nuevoEstudiante.mesNacimiento, nuevoEstudiante.anioNacimiento);
    
    while (true) {
        cout << "Ingrese el a�o de ingreso a la universidad: ";
        if (cin >> nuevoEstudiante.anioIngreso) break;
        else {
            cout << "Valor inv�lido. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    estudiantes.push_back(nuevoEstudiante);
    guardarEstudianteEnArchivo(nuevoEstudiante); // Guardar en archivo

    cout << "Estudiante registrado exitosamente!\n";
    mostrarEstudiantes(estudiantes);
}

int main() {
    vector<Estudiante> estudiantes;
    int opcion;

    do {
        cout << "\n--- Men� Principal ---\n";
        cout << "1. Registrar Estudiante\n";
        cout << "2. Mostrar Estudiantes Registrados\n";
        cout << "3. Mostrar Datos desde Archivo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                registrarEstudiante(estudiantes);
                break;
            case 2:
                mostrarEstudiantes(estudiantes);
                break;
            case 3:
                mostrarDatosDesdeArchivo();
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opci�n inv�lida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}


