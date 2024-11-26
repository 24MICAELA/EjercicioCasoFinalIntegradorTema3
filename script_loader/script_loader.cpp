#include "script_loader.h"
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

void log_error(const string& error_message) {
    ofstream error_log("error_log.txt", ios::app);  // Abrir en modo append
    if (error_log.is_open()) {
        error_log << error_message << endl;
        error_log.close();
    } else {
        cerr << "Error al intentar escribir en el archivo de log." << endl;
    }
}

void load_script(const char* filename, bool show_script = false) {
    string script;
    FILE* f = nullptr;

    try {
        f = fopen(filename, "rb");
        if (!f) {
            string error = "Error al abrir el archivo: " + string(filename);
            cerr << error << endl;
            log_error(error);  // Registrar el error en el log
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0) {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script) {
            cout << script << endl;
        }

    } catch (const exception& e) {
        cerr << "Error durante la lectura del archivo: " << e.what() << endl;
        log_error("Error durante la lectura del archivo: " + string(e.what()));  // Registrar el error en el log
        if (f) fclose(f);
    }
}

void load_script() {
    char filename[500];
    printf("Introduce el nombre del archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
