#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <windows.h> 

using namespace std;

const string MORADO = "\033[35m";    
const string VERDE = "\033[32m";     
const string AZUL = "\033[34m";      
const string BLANCO = "\033[37m";    
const string ROJO = "\033[31m";
const string GRIS_NORMAL = "\033[90m";
const string RESET = "\033[0m"; 

struct Curso {
    string nombre;
    string codigo;
    char seccion;
    float notaFinal; 
};

struct Estudiante {
    string codigoPersonal;
    string nombreCompleto;
    string carrera;
    string departamento;
    string municipio;
    string telefonoPersonal;
    string telefonoCasa;
    string correoElectronico;
    int edad;
    int anioIngreso;
    int semestre;
    vector<Curso> cursos; 
};

vector<Estudiante> estudiantes;

string generarCodigoPersonal() {
    int codigo = rand() % 9000 + 1000;
    ostringstream ss;
    ss << codigo;
    return ss.str();
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

bool validarTelefono(const string& telefono) {
    if (telefono.length() != 8) return false;
    for (size_t i = 0; i < telefono.length(); ++i) {
        if (!isdigit(telefono[i])) return false;
    }
    return true;
}

bool validarCodigoEstudiante(const string& codigo) {
    if (codigo.length() != 4) return false;
    for (size_t i = 0; i < codigo.length(); ++i) {
        if (!isdigit(codigo[i])) return false;
    }
    return true;
}

int seleccionarOpcion(const string& mensaje, int maxOpcion) {
    int opcion;
    while (true) {
        cout << mensaje;
        cin >> opcion;
        if (opcion >= 1 && opcion <= maxOpcion) {
            return opcion;
        } else {
            cout << "Valor inválido, intente de nuevo.\n";
        }
    }
}

void mostrarIconoGiratorio() {
    const char* iconos = "|/-\\";
    for (int i = 0; i < 20; ++i) {
        cout << "\r" << iconos[i % 4] << " Cargando... ";
        cout.flush();
        Sleep(100); 
    }
    cout << "\r"; 
    cout << "                \r"; 
}

void mostrarEstudiante(const Estudiante& estudiante) {           
    mostrarIconoGiratorio();
    cout << GRIS_NORMAL << MORADO;
    cout << "-----------------------------------------------------------\n";
    cout << "\n           --- Estudiante Registrado ---\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Código Personal: " << estudiante.codigoPersonal << "\n";
    cout << "\n";
    cout << "Nombre Completo: " << estudiante.nombreCompleto << "\n"; 
    cout << "\n";
    cout << "Carrera: " << estudiante.carrera << "\n";
    cout << "\n";
    cout << "Edad: " << estudiante.edad << "\n";
    cout << "\n";
    cout << "Departamento: " << estudiante.departamento << "\n";
    cout << "\n";
    cout << "Municipio: " << estudiante.municipio << "\n";
    cout << "\n";
    cout << "Teléfono Personal: " << estudiante.telefonoPersonal << "\n";
    cout << "\n";
    cout << "Teléfono de Casa: " << estudiante.telefonoCasa << "\n";
    cout << "\n";
    cout << "Correo Electrónico: " << estudiante.correoElectronico << "\n";
    cout << "\n";
    cout << "Año de Ingreso: " << estudiante.anioIngreso << "\n";
    cout << "\n";
    cout << "Semestre: " << estudiante.semestre << "\n";
    cout << "-----------------------------------------------------------\n";
}

void mostrarCursosAsignados(const Estudiante& estudiante) {          
    mostrarIconoGiratorio();
    cout << GRIS_NORMAL << AZUL;
    cout << " \n             --- Cursos Asignados ---\n";
    cout << "-----------------------------------------------------------\n";
    for (size_t k = 0; k < estudiante.cursos.size(); ++k) {
        cout << "Curso: " << estudiante.cursos[k].nombre << "\n";
        cout << "Código del Curso: " << estudiante.cursos[k].codigo << "\n";
        cout << "Sección Asignada: " << estudiante.cursos[k].seccion << "\n\n";
    }
    if (estudiante.cursos.empty()) {
        cout << "No se han asignado cursos a este estudiante.\n";
    }
}

void mostrarNotas(const Estudiante& estudiante) {               
    mostrarIconoGiratorio();
    cout << GRIS_NORMAL << ROJO;
    cout << "\n                 --- Notas Asignadas ---\n";
    cout << "-----------------------------------------------------------\n";
    for (size_t k = 0; k < estudiante.cursos.size(); ++k) {
        cout << "Curso: " << estudiante.cursos[k].nombre << "\n";
        cout << "Nota Final: " << estudiante.cursos[k].notaFinal << "\n";
        cout << "Estado Actual del Curso: " << (estudiante.cursos[k].notaFinal >= 60 ? "Aprobado" : "Desaprobado") << "\n";
        cout << "-----------------------------------------------------------\n";
    }
    if (estudiante.cursos.empty()) {
        cout << "No se han registrado notas para este estudiante.\n";
    }
}

bool registrarEstudiante() {
    Estudiante nuevoEstudiante;
    nuevoEstudiante.codigoPersonal = generarCodigoPersonal();

    cout << "            --- Registro de estudiantes ---                       \n";
    cout << "-----------------------------------------------------------\n";
    cout << "Elija la carrera que desea cursar:\n";
    cout << "1. Ingeniería en sistemas\n";
    cout << "2. Derecho\n";
    cout << "3. Auditoría\n";
    cout << "-----------------------------------------------------------\n";
    int carreraOpcion = seleccionarOpcion("Seleccione una opción (1-3): ", 3);
    cout << "-----------------------------------------------------------\n";
    switch (carreraOpcion) {
        case 1: nuevoEstudiante.carrera = "Ingeniería en sistemas"; break;
        case 2: nuevoEstudiante.carrera = "Derecho"; break;
        case 3: nuevoEstudiante.carrera = "Auditoría"; break;
    }

    
    string primerNombre;
    cout << "Ingrese el primer nombre: ";
    cin.ignore(); 
    getline(cin, primerNombre); 
    cout << "-----------------------------------------------------------\n";
    nuevoEstudiante.nombreCompleto = primerNombre;

    
    char agregarSegundoNombre;
    cout << "¿Desea agregar un segundo nombre? (s/n): ";
    cin >> agregarSegundoNombre;
    cout << "-----------------------------------------------------------\n";
    if (agregarSegundoNombre == 's' || agregarSegundoNombre == 'S') {
        string segundoNombre;
        cout << "Ingrese el segundo nombre: ";
        cin.ignore(); 
        getline(cin, segundoNombre);
        cout << "-----------------------------------------------------------\n";
        nuevoEstudiante.nombreCompleto += " " + segundoNombre;
    }

    // Ingresar tercer nombre
    char agregarTercerNombre;
    cout << "¿Desea agregar un tercer nombre? (s/n): ";
    cin >> agregarTercerNombre;
    cout << "-----------------------------------------------------------\n";
    if (agregarTercerNombre == 's' || agregarTercerNombre == 'S') {
        string tercerNombre;
        cout << "Ingrese el tercer nombre: ";
        cin.ignore(); // Ignorar el salto de línea anterior
        getline(cin, tercerNombre); // Permitir múltiples palabras
        cout << "-----------------------------------------------------------\n";
        nuevoEstudiante.nombreCompleto += " " + tercerNombre;
    }

    // Ingresar primer apellido
    string primerApellido;
    cout << "Ingrese el primer apellido: ";
    cin.ignore(); // Ignorar el salto de línea anterior
    getline(cin, primerApellido); // Permitir múltiples palabras
    cout << "-----------------------------------------------------------\n";
    nuevoEstudiante.nombreCompleto += " " + primerApellido;

    // Ingresar segundo apellido
    char agregarSegundoApellido;
    cout << "¿Desea agregar un segundo apellido? (s/n): ";
    cin >> agregarSegundoApellido;
    cout << "-----------------------------------------------------------\n";
    if (agregarSegundoApellido == 's' || agregarSegundoApellido == 'S') {
        string segundoApellido;
        cout << "Ingrese el segundo apellido: ";
        cin.ignore(); // Ignorar el salto de línea anterior
        getline(cin, segundoApellido); // Permitir múltiples palabras
        cout << "-----------------------------------------------------------\n";
        nuevoEstudiante.nombreCompleto += " " + segundoApellido;
    }

    int diaNacimiento, mesNacimiento, anioNacimiento;
    cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
    char slash;
    cin >> diaNacimiento >> slash >> mesNacimiento >> slash >> anioNacimiento;
    nuevoEstudiante.edad = calcularEdad(diaNacimiento, mesNacimiento, anioNacimiento);
    cout << "-----------------------------------------------------------\n";

    const string departamentos[] = {
        "Guatemala", "Sacatepéquez", "Chimaltenango", "Escuintla", "Santa Rosa",
        "Solalá", "Totonicapán", "Quetzaltenango", "Suchitepéquez", "Retalhuleu"
    };
    cout << "Ingrese el número del departamento en donde reside:\n";
    for (int i = 0; i < 10; ++i) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }
    cout << "-----------------------------------------------------------\n";
    int deptoOpcion = seleccionarOpcion("Seleccione una opción (1-10): ", 10);
    nuevoEstudiante.departamento = departamentos[deptoOpcion - 1];
    cout << "-----------------------------------------------------------\n";

    const string municipios[10][5] = {
        {"Guatemala", "Mixco", "Villa Nueva", "San Miguel Petapa", "Santa Catarina Pinula"},
        {"Antigua Guatemala", "Ciudad Vieja", "Jocotenango", "Pastores", "Sumpango"},
        {"Chimaltenango", "San Martín de los Canes", "El Tejar", "San José Poaquil", "San Juan Comalapa"},
        {"Escuintla", "Santa Lucía Cotzumalguapa", "La Democracia", "San José", "Siquinalá"},
        {"Santa Rosa de Lima", "Cuilapa", "San Juan Tecuaco", "Barberena", "Chiquimulilla"},
        {"Solalá", "San Juan La Laguna", "San Pedro La Laguna", "Panajachel", "Santa Catarina Palopó"},
        {"Totonicapán", "San Cristóbal Totonicapán", "San Francisco el Alto", "San Andrés Xecul", "Momostenango"},
        {"Quetzaltenango", "Salcajá", "San Martín Sacatepéquez", "Sibilia", "Zunil"},
        {"Mazatenango", "San Bernardino", "El Asintal", "San Antonio Suchitepéquez", "Santo Domingo Suchitepéquez"},
        {"Retalhuleu", "San Sebastián", "Champerico", "San Martín Zapotitlán", "Santa Cruz Muluá"}
    };
    cout << "Ingrese el número del municipio en donde reside:\n";
    for (int i = 0; i < 5; ++i) {
        cout << i + 1 << ". " << municipios[deptoOpcion - 1][i] << endl;
    }
    cout << "-----------------------------------------------------------\n";
    int municipioOpcion = seleccionarOpcion("Seleccione una opción (1-5): ", 5);
    nuevoEstudiante.municipio = municipios[deptoOpcion - 1][municipioOpcion - 1];
    cout << "-----------------------------------------------------------\n";

    cout << "Ingrese el teléfono personal (8 dígitos): ";
    while (true) {
        string telefono;
        cin >> telefono;
        cout << "-----------------------------------------------------------\n";
        if (validarTelefono(telefono)) {
            nuevoEstudiante.telefonoPersonal = telefono;
            break;
        } else {
            cout << "Teléfono inválido. Ingrese nuevamente (8 dígitos): ";
        }
    }

    cout << "Ingrese el teléfono de casa (8 dígitos): ";
    while (true) {
        string telefono;
        cin >> telefono;
        cout << "-----------------------------------------------------------\n";
        if (validarTelefono(telefono)) {
            nuevoEstudiante.telefonoCasa = telefono;
            break;
        } else {
            cout << "Teléfono inválido. Ingrese nuevamente (8 dígitos): ";
        }
    }

    cout << "Ingrese el correo electrónico: ";
    cin >> nuevoEstudiante.correoElectronico;
    cout << "-----------------------------------------------------------\n";

    cout << "Ingrese el año de ingreso: ";
    cin >> nuevoEstudiante.anioIngreso;
    cout << "-----------------------------------------------------------\n";

    cout << "Ingrese el semestre: ";
    cin >> nuevoEstudiante.semestre;
    cout << " \n";
    cout << " \n";

    estudiantes.push_back(nuevoEstudiante);
    
    mostrarEstudiante(nuevoEstudiante);
    cout << GRIS_NORMAL << BLANCO;
    cout << "Estudiante registrado con éxito. Código Personal: " << nuevoEstudiante.codigoPersonal << "\n";
    cout << "-----------------------------------------------------------\n";
    
    char volverARegistrar;
    cout << "¿Quiere volver a registrar un estudiante? (s/n): ";
    cin >> volverARegistrar;
    cout << " \n";
    cout << " \n";
    if (volverARegistrar == 's' || volverARegistrar == 'S') {
        registrarEstudiante(); 
    }

    return true;
}


void controlNotas() {
    string codigoEstudiante;
    
    cout << "Ingrese el código del estudiante: ";
    cin >> codigoEstudiante;
    cout << " \n";
    cout << " \n";
    cout << "-----------------------------------------------------------\n";
    cout << "\n              --- Control de notas ---\n";
    cout << "-----------------------------------------------------------\n";

    for (size_t i = 0; i < estudiantes.size(); ++i) {
        if (estudiantes[i].codigoPersonal == codigoEstudiante) {
            vector<string> resultados;

            if (estudiantes[i].cursos.empty()) {
                cout << "Ningún alumno con asignación de cursos.\n";
                return;
            }

            for (size_t j = 0; j < estudiantes[i].cursos.size(); ++j) {
                float notaParcial1, notaParcial2, zonaTotal, notaExamenFinal;

                // Mostrar el nombre del curso
                cout << "\nCurso: " << estudiantes[i].cursos[j].nombre << "\n";

                // Solicitar notas
                do {
                    cout << "Ingrese la nota del primer parcial (0-15): ";
                    cin >> notaParcial1;
                } while (notaParcial1 < 0 || notaParcial1 > 15);

                do {
                    cout << "Ingrese la nota del segundo parcial (0-15): ";
                    cin >> notaParcial2;
                } while (notaParcial2 < 0 || notaParcial2 > 15);

                do {
                    cout << "Ingrese la zona total (0-35): ";
                    cin >> zonaTotal;
                } while (zonaTotal < 0 || zonaTotal > 35);

                do {
                    cout << "Ingrese la nota del examen final (0-35): ";
                    cin >> notaExamenFinal;
                    cout << "-----------------------------------------------------------\n";
                } while (notaExamenFinal < 0 || notaExamenFinal > 35);

                estudiantes[i].cursos[j].notaFinal = notaParcial1 + notaParcial2 + zonaTotal + notaExamenFinal;

                string estado = (estudiantes[i].cursos[j].notaFinal >= 60) ? "Aprobado" : "Desaprobado";
                stringstream ss;
                ss << estudiantes[i].cursos[j].notaFinal;

                resultados.push_back("Curso: " + estudiantes[i].cursos[j].nombre);
                resultados.push_back("Nota Final: " + ss.str());
                resultados.push_back("Estado Actual del Curso: " + estado);
                resultados.push_back("-----------------------------------------------------------");
            }

            mostrarIconoGiratorio();  
            cout << GRIS_NORMAL << ROJO;
            cout << "\n               --- Resultados Finales ---\n";
            cout << "-----------------------------------------------------------\n";           
            for (size_t k = 0; k < resultados.size(); ++k) {
                cout << resultados[k] << "\n";
            }

            char volverRegistrar;
            cout << GRIS_NORMAL << BLANCO;
            cout << "¿Quieres volver a registrar notas? (s/n): ";
            cin >> volverRegistrar;
            cout << " \n";
            cout << " \n";
            if (volverRegistrar == 's' || volverRegistrar == 'S') {
                controlNotas(); 
            }
            return; 
        }
    }

    cout << "Estudiante no encontrado.\n";
}


void asignarCursos() {
    string codigo;
    bool codigoValido = false;

    while (!codigoValido) {
        cout << "Ingrese el código del estudiante: ";
        cin >> codigo;
        cout << " \n";
        cout << " \n";
        cout << "-----------------------------------------------------------\n";

        if (validarCodigoEstudiante(codigo)) {
            codigoValido = true;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigo) {
                    cout << "              --- Asignación de cursos ---\n";
                    cout << "-----------------------------------------------------------\n";
                    cout << "Cursos disponibles para " << estudiantes[i].nombreCompleto << ":\n";
                    cout << "-----------------------------------------------------------\n";

                    string cursos[5];
                    int cantidadCursos = 0;

                    if (estudiantes[i].carrera == "Ingeniería en sistemas") {
                        cursos[cantidadCursos++] = "Álgebra lineal";
                        cursos[cantidadCursos++] = "Algoritmos";
                        cursos[cantidadCursos++] = "Contabilidad";
                        cursos[cantidadCursos++] = "Matemática discreta";
                        cursos[cantidadCursos++] = "Pre cálculo";
                    } else if (estudiantes[i].carrera == "Derecho") {
                        cursos[cantidadCursos++] = "Derecho Civil";
                        cursos[cantidadCursos++] = "Derecho Penal";
                        cursos[cantidadCursos++] = "Derecho Constitucional";
                        cursos[cantidadCursos++] = "Derecho Internacional";
                        cursos[cantidadCursos++] = "Derecho Laboral";
                    } else if (estudiantes[i].carrera == "Auditoría") {
                        cursos[cantidadCursos++] = "Auditoría Financiera";
                        cursos[cantidadCursos++] = "Auditoría Interna";
                        cursos[cantidadCursos++] = "Auditoría de Sistemas";
                        cursos[cantidadCursos++] = "Auditoría de Cumplimiento";
                        cursos[cantidadCursos++] = "Auditoría Forense";
                    }

                    for (int j = 0; j < cantidadCursos; ++j) {
                        char seccion;
                        cout  << cursos[j] << "\n";
                        cout << "\n";
                        cout << "¿Qué sección desea asignarle? (A, B, C, D): ";
                        cin >> seccion;
                        cout << "-----------------------------------------------------------\n";

                        Curso nuevoCurso;
                        nuevoCurso.nombre = cursos[j];
                        nuevoCurso.codigo = generarCodigoPersonal(); 
                        nuevoCurso.seccion = seccion;

                        estudiantes[i].cursos.push_back(nuevoCurso);
                    }

                    mostrarCursosAsignados(estudiantes[i]);

                    // Opción para asignar cursos a otro alumno
                    char asignarOtro;
                    cout << "-----------------------------------------------------------\n";
                    cout << GRIS_NORMAL << BLANCO;
                    cout << "¿Quiere asignarle cursos a otro alumno? (s/n): ";
                    cin >> asignarOtro;
                    cout << " \n";
                    cout << " \n";
                    if (asignarOtro == 's' || asignarOtro == 'S') {
                        asignarCursos(); // Llama a la función nuevamente
                    }
                    break;
                }
            }
        }
    }
}



void mostrarDatosRegistrados() {
    int opcion;
    do {
        cout << GRIS_NORMAL << BLANCO;
        cout << "\n            --- Mostrar Datos Registrados ---\n";
        cout << "-----------------------------------------------------------\n";
        cout << "1. Mostrar Estudiantes Registrados\n";
        cout << "2. Mostrar Cursos Asignados\n";
        cout << "3. Mostrar Notas Ingresadas\n";
        cout << "4. Salir\n"; // Opción para salir
        opcion = seleccionarOpcion("Seleccione una opción (1-4): ", 4);

        if (opcion == 1) {
            string codigoEstudiante;
            cout << "Ingrese el código del estudiante: ";
            cin >> codigoEstudiante;

            bool encontrado = false;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigoEstudiante) {
                    mostrarEstudiante(estudiantes[i]);
                    encontrado = true;
                    break; // Salir del bucle si se encuentra el estudiante
                }
            }
            // No se muestra "Estudiante no encontrado"
        } else if (opcion == 2) {
            string codigoEstudiante;
            cout << "Ingrese el código del estudiante: ";
            cin >> codigoEstudiante;

            bool encontrado = false;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigoEstudiante) {
                    mostrarCursosAsignados(estudiantes[i]);
                    encontrado = true;
                    break; // Salir del bucle si se encuentra el estudiante
                }
            }
            // No se muestra "Estudiante no encontrado"
        } else if (opcion == 3) {
            string codigoEstudiante;
            cout << "Ingrese el código del estudiante: ";
            cin >> codigoEstudiante;

            bool encontrado = false;
            for (size_t i = 0; i < estudiantes.size(); ++i) {
                if (estudiantes[i].codigoPersonal == codigoEstudiante) {
                    mostrarNotas(estudiantes[i]);
                    encontrado = true;
                    break; // Salir del bucle si se encuentra el estudiante
                }
            }
            // No se muestra "Estudiante no encontrado"
        }

    } while (opcion != 4); // Terminar cuando se selecciona la opción 4 (salir)
}


int main() {
	system("COLOR 8F");
    srand(static_cast<unsigned int>(time(0))); 
    
    mostrarIconoGiratorio();



    int opcion;
    do {
    	cout << GRIS_NORMAL << BLANCO;
    	cout << "===========================================================\n";
        cout << "\n                 --- Menu Principal ---                          \n";
        cout << "===========================================================\n";
        cout << "1. Registrar Estudiante                          \n";
        cout << "2. Asignacion de Cursos                          \n";
        cout << "3. Control de Notas                          \n";
        cout << "4. Mostrar Datos Registrados            \n";
        cout << "5. Salir                             \n";
        cout << "-----------------------------------------------------------\n";
        opcion = seleccionarOpcion("Seleccione una opcion (1-5): ", 5); 
        cout << " \n";
        cout << " \n";
        cout << "-----------------------------------------------------------\n";

        switch (opcion) {
            case 1:
                registrarEstudiante();
                break;
            case 2:
                asignarCursos();
                break;
            case 3:
                controlNotas();
                break;
            case 4:
                mostrarDatosRegistrados();
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
        }
    } while (opcion != 5);
    
    return 0;
}


