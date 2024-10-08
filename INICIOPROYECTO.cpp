#include <iostream>
#include <vector>
#include <string>
#include <ctime>

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

// Lista de departamentos
const string departamentos[] = {
    "Guatemala", "Sacatepéquez", "Chimaltenango", "Escuintla", "Santa Rosa",
    "Sololá", "Totonicapán", "Quetzaltenango", "Suchitepéquez", "Retalhuleu",
    "San Marcos", "Huehuetenango", "Quiché", "Baja Verapaz", "Alta Verapaz",
    "Petén", "Izabal", "Zacapa", "Chiquimula", "Jalapa", "Jutiapa", "El Progreso"
};

// Lista de municipios por departamento
const string municipios[22][5] = {
    {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula"}, //GUTEMALA
    {"Antigua Guatemala", "Ciudad Vieja", "Jocotenango", "Pastores", "Sumpango"}, //SACATEPEQUEZ
    {"Chimaltenango", "San Martín de los Canes", "El Tejar", "San José Poaquil", "San Juan Comalapa"}, //CHIMALTENANGO
    {"Escuintla", "Santa Lucía Cotzumalguapa", "La democracia", "San José", "Siquinalá"}, //ESCUINTLA
    {"Santa Rosa de Lima", "Cuilapa", "San Juan Tecuaco", "Barberena", "Chiquimulilla"}, //SANTA ROSA
    {"Solalá", "San Juan La Laguna", "San Pedro La Laguna", "Panajachel", "Santa Catarina Palopó"}, //SOLOLA
    {"Totonicapán", "San Cristóbal Totonicapán", "San Francisco el Alto", "San Andrés Xecul", "Momostenango"}, //TOTONICAPAN
    {"Quetzaltenango", "Salcajá", "San Martín Sacatepéquez", "Sibilia", "Zunil"}, //QUETZALTENANGO
    {"Mazatenango", "San Bernardino", "El Asintal", "San Antonio Suchitepéquez", "Santo Domingo Suchitepéquez"}, //SUCHITEPEQUEZ
    {"Retalhuleu", "San Sebastián", "San Martín Zapotitlán", "Tecoanapa", "Champerico"}, //RETALHULEU
    {"San Marcos ","San Pedro Sacatepéquez", "Malacatán", "San Antonio Sacatepéquez", "Sibinal"}, //SAN MARCOS
	{"Huehuetenango", "Aguacatán", "Chiantla", "Colotenango", "Concepción Huista"}, //HUEHUTENENGO
	{"Santa Cruz del Quiche", "San Antonio Ilotenango", "San Bartolomé Jocotenango", "San Pedro Jocopilas", "Patzité"}, //QUICHE
	{"Salamá", "Granados", "Rabinal", "San Jerónimo", "El Chol"},  //BAJA VERAPAZ
	{"Cobán", "San Pedro Carchá", "San Cristóbal Verapaz", "Tactic", "Tucurú"}, // ALTA VERAPAZ
	{"Flores", "Melchor de Mencos", "Poptún", "San Benito", "San Francisco"}, //PETEN
	{"Puerto Barrios", "Livingston", "El Estor", "Morales", "Los Amates"}, //IZABAL
	{"Gualán", "Río Hondo", "La Unión", "San Jorge", "Estanzuela"}, //ZACAPA
	{"Chiquimula", "Jocotán", "Esquipulas", "Camotán", "Ipala"}, //CHIQUIMULA
	{"Monjas", "San Pedro Pinula", "San Carlos Alzatate", "San Luis Jilotepeque", "Jalapa"}, //JALAPA
    {"Jutiapa", "Jalpatagua", "El Progreso", "Asunción Mita", "Santa Catarina Mita"}, //JUTIAPA
    {"Guastatoya", "Morazán", "Sanarate", "Sansare", "San Agustín Acasaguastlán"} //EL PROGRESO
};

// Función para generar el código automáticamente
int generarCodigo() {
    static int codigo = 1000; 
    return codigo++;
}

// Función para calcular la edad actual
int calcularEdad(int diaNacimiento, int mesNacimiento, int anioNacimiento) {
    time_t t = time(0);
    tm* ahora = localtime(&t);

    int anioActual = 1900 + ahora->tm_year;
    int mesActual = 1 + ahora->tm_mon;
    int diaActual = ahora->tm_mday;

    // Calcular la edad
    int edad = anioActual - anioNacimiento;

    // Ajustar si el cumpleaños aún no ha ocurrido este año
    if (mesNacimiento > mesActual || (mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        edad--;
    }
    
    return edad;
}

// Función para mostrar el menú de carreras y permitir al usuario escoger una
string escogerCarrera() {
    int opcion;
    cout << "\nSeleccione una carrera:\n";
    cout << "1. Ingeniería\n";
    cout << "2. Administración\n";
    cout << "3. Derecho\n";
    cout << "Ingrese el número de la carrera: ";
    cin >> opcion;
    
    switch(opcion) {
        case 1:
            return "Ingeniería";
        case 2:
            return "Administración";
        case 3:
            return "Derecho";
        default:
            cout << "Opción no válida. Se asignará Ingeniería por defecto.\n";
            return "Ingeniería";
    }
}

// Función para que el usuario elija su departamento y municipio
void escogerDireccion(string& departamento, string& municipio) {
    int opcionDepto;
    cout << "\nSeleccione un departamento:\n";
    for (int i = 0; i < 22; i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    cout << "Ingrese el número del departamento: ";
    cin >> opcionDepto;

    if (opcionDepto < 1 || opcionDepto > 22) {
        cout << "Opción no válida. Se asignará Guatemala por defecto.\n";
        departamento = "Guatemala";
    } else {
        departamento = departamentos[opcionDepto - 1];
    }

    // Mostrar municipios del departamento seleccionado
    int opcionMuni;
    cout << "\nSeleccione un municipio en " << departamento << ":\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << municipios[opcionDepto - 1][i] << endl;
    }
    cout << "Ingrese el número del municipio: ";
    cin >> opcionMuni;

    if (opcionMuni < 1 || opcionMuni > 5) {
        cout << "Opción no válida. Se asignará " << municipios[opcionDepto - 1][0] << " por defecto.\n";
        municipio = municipios[opcionDepto - 1][0];
    } else {
        municipio = municipios[opcionDepto - 1][opcionMuni - 1];
    }
}

// Función para registrar un estudiante
void registrarEstudiante(vector<Estudiante>& estudiantes) {
    Estudiante nuevoEstudiante; 
    
    nuevoEstudiante.id = generarCodigo(); 
    
    cout << "Ingrese el nombre del estudiante: ";
  	getline(cin, nuevoEstudiante.nombre);
    cout << "Ingrese el apellido del estudiante: ";
    getline(cin, nuevoEstudiante.apellido);
    
    // El usuario escoge la carrera
    nuevoEstudiante.carrera = escogerCarrera();
    
    // El usuario escoge la dirección (departamento y municipio)
    escogerDireccion(nuevoEstudiante.departamento, nuevoEstudiante.municipio);
    
    // Ingresar teléfonos
    cout << "Ingrese el número de teléfono personal: ";
    cin >> nuevoEstudiante.telefonoPersonal;
    cout << "Ingrese el número de teléfono de casa: ";
    cin >> nuevoEstudiante.telefonoCasa;
    cout << "Ingrese el número de teléfono de emergencia: ";
    cin >> nuevoEstudiante.telefonoEmergencia;

    // Ingresar correo electrónico
    cout << "Ingrese el correo electrónico del estudiante: ";
    cin >> nuevoEstudiante.correoElectronico;

    // Fecha de nacimiento
    cout << "Ingrese el día de nacimiento (DD): ";
    cin >> nuevoEstudiante.diaNacimiento;
    cout << "Ingrese el mes de nacimiento (MM): ";
    cin >> nuevoEstudiante.mesNacimiento;
    cout << "Ingrese el año de nacimiento (YYYY): ";
    cin >> nuevoEstudiante.anioNacimiento;
    
    // Calcular la edad
    nuevoEstudiante.edad = calcularEdad(nuevoEstudiante.diaNacimiento, nuevoEstudiante.mesNacimiento, nuevoEstudiante.anioNacimiento);
    
    // Ingresar el año de ingreso a la universidad
    cout << "Ingrese el año de ingreso a la universidad: ";
    cin >> nuevoEstudiante.anioIngreso;

    // Agregar el estudiante al vector
    estudiantes.push_back(nuevoEstudiante);  // Usamos push_back correctamente para agregar el objeto
    
    cout << "Estudiante registrado con ID: " << nuevoEstudiante.id << ", Edad: " << nuevoEstudiante.edad 
         << " años, Carrera: " << nuevoEstudiante.carrera 
         << ", Departamento: " << nuevoEstudiante.departamento 
         << ", Municipio: " << nuevoEstudiante.municipio
         << ", Teléfono Personal: " << nuevoEstudiante.telefonoPersonal
         << ", Teléfono de Casa: " << nuevoEstudiante.telefonoCasa
         << ", Teléfono de Emergencia: " << nuevoEstudiante.telefonoEmergencia
         << ", Correo Electrónico: " << nuevoEstudiante.correoElectronico
         << ", Año de Ingreso: " << nuevoEstudiante.anioIngreso << endl;
}

int main() {
    vector<Estudiante> estudiantes;  // Vector que contiene estudiantes
    char continuar = 's';
    
    while (continuar == 's' || continuar == 'S') {
        registrarEstudiante(estudiantes);
        cout << "¿Desea registrar otro estudiante? (s/n): ";
        cin >> continuar;
    }
    
    // Muestra todos los estudiantes registrados
    cout << "\nLista de estudiantes registrados:\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        Estudiante estudiante = estudiantes[i];
        cout << "ID: " << estudiante.id << ", Nombre: " << estudiante.nombre 
             << " " << estudiante.apellido << ", Edad: " << estudiante.edad 
             << ", Carrera: " << estudiante.carrera 
             << ", Departamento: " << estudiante.departamento 
             << ", Municipio: " << estudiante.municipio
             << ", Teléfono Personal: " << estudiante.telefonoPersonal
             << ", Teléfono de Casa: " << estudiante.telefonoCasa
             << ", Teléfono de Emergencia: " << estudiante.telefonoEmergencia
             << ", Correo Electrónico: " << estudiante.correoElectronico
             << ", Año de Ingreso: " << estudiante.anioIngreso << endl;
    }
    
    return 0;
}

