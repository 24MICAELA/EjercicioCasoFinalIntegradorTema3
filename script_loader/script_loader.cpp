#include "script_loader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;
using namespace std;

struct ColorConsole {
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto reset = "\033[0m";
};

bool is_valid_filename(const string& filename) {
    const string invalid_chars = "\\/:*?\"<>|";
    for (char c : filename) {
        if (invalid_chars.find(c) != string::npos) {
            return false;
        }
    }
    return true;
}

void log_error(const string& message) {
    ofstream log_file("error_log.txt", ios::app);
    if (log_file.is_open()) {
        log_file << message << endl;
    }
    log_file.close();
}

void load_script(const char* filename, bool show_script) {
    try {
        // Verificar si el archivo existe y es válido
        if (!fs::exists(filename)) {
            string error = "Error: El archivo '" + string(filename) + "' no existe.";
            cerr << error << endl;
            log_error(error);
            return;
        }

        if (!fs::is_regular_file(filename)) {
            string error = "Error: '" + string(filename) + "' no es un archivo válido.";
            cerr << error << endl;
            log_error(error);
            return;
        }

        ifstream file(filename, ios::in | ios::binary);
        if (!file.is_open()) {
            string error = "Error: No se pudo abrir el archivo '" + string(filename) + "'.";
            cerr << error << endl;
            log_error(error);
            return;
        }

        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        if (file.fail()) {
            string error = "Error: Fallo durante la lectura del archivo '" + string(filename) + "'.";
            cerr << error << endl;
            log_error(error);
            return;
        }

        if (show_script) {
            cout << ColorConsole::fg_blue << content << ColorConsole::reset << endl;
        }

        file.close();
    } catch (const exception& e) {
        string error = "Excepción: " + string(e.what());
        cerr << error << endl;
        log_error(error);
    }
}

void load_script() {
    char filename[500];
    cout << "Introduce el nombre del archivo: ";
    cin.getline(filename, 500);

    if (cin.fail() || filename[0] == '\0') {
        cerr << "Error: Entrada no válida. Introduce un nombre de archivo correcto." << endl;
        cin.clear();
        return;
    }

    if (!is_valid_filename(filename)) {
        cerr << "Error: El nombre del archivo contiene caracteres no válidos." << endl;
        return;
    }

    load_script(filename, true);
}
