// ------------------------------------------------------------------//
// MODULO DE PERSISTENCIAS: GUARDAR Y RECUPERAR INFORMACION           //
// ------------------------------------------------------------------//

#include "Persistencias.h"
#include "../Estudiantes/Estudiantes.h" // estudiantes[], cantidadEstudiantes, struct Estudiante
#include "../Cursos/CURSOS.H"           // cursos, matrizNotas, detalleNotas, struct Curso
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// Variables globales de Estudiantes.cpp que se usan para armar el carnet.
// Se guardan para que los carnets nuevos sigan la secuencia despues de reabrir.
extern int CodCarrera;
extern int contador[4];

//---------- NOMBRES DE LOS ARCHIVOS ----------//
const string ARCH_ESTUDIANTES = "datos_estudiantes.txt";
const string ARCH_CURSOS = "datos_cursos.txt";
const string ARCH_NOTAS = "datos_notas.txt";

const int MAX_ESTUDIANTES = 100;
const int MAX_CURSOS = 5;
const int NUM_NOTAS = 6;

//==================== ESTUDIANTES ====================//
// Formato: cantidad, CodCarrera, 4 contadores y luego
// 9 lineas por estudiante (una por campo, asi se permiten espacios).

bool guardarEstudiantes()
{
    ofstream f(ARCH_ESTUDIANTES);
    if (!f)
        return false;

    f << cantidadEstudiantes << '\n';
    f << CodCarrera << '\n';
    for (int k = 0; k < 4; k++)
        f << contador[k] << '\n';

    for (int i = 0; i < cantidadEstudiantes; i++)
    {
        f << estudiantes[i].nombre1 << '\n';
        f << estudiantes[i].nombre2 << '\n';
        f << estudiantes[i].apellido1 << '\n';
        f << estudiantes[i].apellido2 << '\n';
        f << estudiantes[i].NombreCompleto << '\n';
        f << estudiantes[i].correo << '\n';
        f << estudiantes[i].FechaNacimiento << '\n';
        f << estudiantes[i].carrera << '\n';
        f << estudiantes[i].RegistroEstudiantil << '\n';
    }
    return f.good();
}

bool cargarEstudiantes()
{
    ifstream f(ARCH_ESTUDIANTES);
    if (!f)
        return false; // primera ejecucion: aun no existe el archivo

    int n = 0;
    int codigo = 0;
    int cont[4] = {0, 0, 0, 0};

    f >> n >> codigo;
    for (int k = 0; k < 4; k++)
        f >> cont[k];
    if (!f || n < 0 || n > MAX_ESTUDIANTES)
        return false;

    string resto;
    getline(f, resto); // termina la linea del ultimo contador

    for (int i = 0; i < n; i++)
    {
        getline(f, estudiantes[i].nombre1);
        getline(f, estudiantes[i].nombre2);
        getline(f, estudiantes[i].apellido1);
        getline(f, estudiantes[i].apellido2);
        getline(f, estudiantes[i].NombreCompleto);
        getline(f, estudiantes[i].correo);
        getline(f, estudiantes[i].FechaNacimiento);
        getline(f, estudiantes[i].carrera);
        getline(f, estudiantes[i].RegistroEstudiantil);
        if (!f)
            return false; // archivo incompleto: no se toca nada mas
    }

    cantidadEstudiantes = n;
    CodCarrera = codigo;
    for (int k = 0; k < 4; k++)
        contador[k] = cont[k];
    return true;
}

//==================== CURSOS ====================//
// Formato: cantidad y luego 2 lineas por curso (nombre y codigo).

bool guardarCursos()
{
    ofstream f(ARCH_CURSOS);
    if (!f)
        return false;

    f << cursos.size() << '\n';
    for (const auto &c : cursos)
    {
        f << c.nombre << '\n';
        f << c.codigo << '\n';
    }
    return f.good();
}

bool cargarCursos()
{
    ifstream f(ARCH_CURSOS);
    if (!f)
        return false;

    int n = 0;
    f >> n;
    if (!f || n < 0 || n > MAX_CURSOS)
        return false;
    f.ignore(1000, '\n');

    vector<Curso> leidos;
    for (int i = 0; i < n; i++)
    {
        Curso c;
        getline(f, c.nombre);
        f >> c.codigo;
        f.ignore(1000, '\n');
        if (!f)
            return false;
        leidos.push_back(c);
    }

    cursos = leidos;
    return true;
}

//==================== NOTAS ====================//
// Formato: matrizNotas (100 lineas de 5 valores) y luego
// detalleNotas (una linea de 6 valores por estudiante y curso).

bool guardarNotas()
{
    ofstream f(ARCH_NOTAS);
    if (!f)
        return false;

    for (int i = 0; i < MAX_ESTUDIANTES; i++)
    {
        for (int j = 0; j < MAX_CURSOS; j++)
            f << matrizNotas[i][j] << ' ';
        f << '\n';
    }

    for (int i = 0; i < MAX_ESTUDIANTES; i++)
    {
        for (int j = 0; j < MAX_CURSOS; j++)
        {
            for (int k = 0; k < NUM_NOTAS; k++)
                f << detalleNotas[i][j][k] << ' ';
            f << '\n';
        }
    }
    return f.good();
}

bool cargarNotas()
{
    ifstream f(ARCH_NOTAS);
    if (!f)
        return false;

    for (int i = 0; i < MAX_ESTUDIANTES; i++)
        for (int j = 0; j < MAX_CURSOS; j++)
            f >> matrizNotas[i][j];

    for (int i = 0; i < MAX_ESTUDIANTES; i++)
        for (int j = 0; j < MAX_CURSOS; j++)
            for (int k = 0; k < NUM_NOTAS; k++)
                f >> detalleNotas[i][j][k];

    return !f.fail();
}

//==================== TODO JUNTO ====================//

bool guardarTodo()
{
    bool ok = true;
    ok = guardarEstudiantes() && ok;
    ok = guardarCursos() && ok;
    ok = guardarNotas() && ok;
    return ok;
}

void cargarTodo()
{
    bool est = cargarEstudiantes();
    bool cur = cargarCursos();
    bool not_ = cargarNotas();

    if (!est && !cur && !not_)
        cout << "[Persistencias] No hay datos guardados, se inicia con el sistema vacio." << endl;
    else
        cout << "[Persistencias] Datos cargados: "
             << cantidadEstudiantes << " estudiante(s), "
             << cursos.size() << " curso(s)." << endl;
}

//==================== MENU Y SALIDA ====================//

void menuPersistencias()
{
    int opcion = 0;

    do
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "        MODULO DE PERSISTENCIAS" << endl;
        cout << "========================================" << endl;
        cout << "1. Guardar todos los datos" << endl;
        cout << "2. Cargar datos guardados" << endl;
        cout << "3. Regresar al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            if (guardarTodo())
                cout << "Datos guardados correctamente." << endl;
            else
                cout << "Error: no se pudieron guardar todos los datos." << endl;
            system("pause");
            break;

        case 2:
            cout << "Se reemplazaran los datos actuales por los guardados." << endl;
            cargarTodo();
            system("pause");
            break;

        case 3:
            break;

        default:
            cout << "Opcion invalida." << endl;
            system("pause");
            break;
        }
    } while (opcion != 3);
}

void guardarYSalir()
{
    if (guardarTodo())
        cout << "[Persistencias] Datos guardados. Saliendo..." << endl;
    else
        cout << "[Persistencias] Aviso: no se pudieron guardar todos los datos." << endl;
}