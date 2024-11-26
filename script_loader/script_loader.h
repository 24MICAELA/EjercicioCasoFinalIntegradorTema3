#ifndef SCRIPT_LOADER_H
#define SCRIPT_LOADER_H

#include <string>

// Declaración de la función load_script con el parámetro show_script
void load_script(const char* filename, bool show_script = false);

// Declaración de la función load_script para pedir el archivo al usuario
void load_script();

// Función para verificar si el nombre de archivo es válido
bool is_valid_filename(const std::string& filename);

// Función para registrar errores en un archivo
void log_error(const std::string& message);

#endif // SCRIPT_LOADER_H
