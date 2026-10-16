#ifndef PERSISTENCIAS_H
#define PERSISTENCIAS_H

// ------------------------------------------------------------------//
// MODULO DE PERSISTENCIAS: guardar y recuperar la informacion en     //
// archivos .txt para que no se pierda al cerrar el programa.         //
// ------------------------------------------------------------------//

// Estudiantes (incluye los contadores usados para generar el carnet)
bool guardarEstudiantes();
bool cargarEstudiantes();

// Catalogo de cursos
bool guardarCursos();
bool cargarCursos();

// Notas (total por curso y detalle de las 6 calificaciones)
bool guardarNotas();
bool cargarNotas();

// Todo junto
bool guardarTodo();
void cargarTodo();

// Menu del modulo (opcion 5 del main)
void menuPersistencias();

// Guarda todo antes de cerrar el sistema (opcion 6 del main)
void guardarYSalir();

#endif