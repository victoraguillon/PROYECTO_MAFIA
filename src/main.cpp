#include <iostream>
#include <locale>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif
#include "mafia_tree.h"
#include "utils.h"
using namespace std;

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "");
    locale::global(locale(""));
    cout.imbue(locale());
    cin.imbue(locale());

    MafiaTree familia;
    familia.load_from_csv("../bin/datos_familia.csv"); 
    MafiaTree familia;
    familia.load_from_csv("../bin/datos_familia.csv"); 

    int opcion = 0;
    while (opcion != 4) {
        UI::header("FAMILIA ADARME-AGUILLÓN");
        cout << "  " << MAGENTA << "1." << RESET << " Ver Linea de Sucesion" << endl;
        cout << "  " << MAGENTA << "2." << RESET << " Estado del Don (Sucesion)" << endl;
        cout << "  " << MAGENTA << "3." << RESET << " Editar Miembro" << endl;
        cout << "  " << MAGENTA << "4." << RESET << " Salir" << endl;
        UI::draw_line("-");
        cout << CYAN << "Seleccione una orden: " << RESET;
        
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            UI::clear();
            continue;
        }

        UI::clear();
        switch (opcion) {
            case 1:
                UI::header("LINEA DE SUCESION ACTUAL");
                familia.show_alive_succession();
                break;
            case 2:
                UI::header("PROTOCOLO DE SUCESION");
                familia.check_and_update_boss();
                break;
            case 3: {
                int id;
                UI::header("MODIFICAR REGISTRO");
                cout << "ID del miembro: "; cin >> id;
                cin.ignore(10000, '\n');
                familia.edit_node_data(id);
                break;
            }
            case 4:
                cout << RED << BOLD << "\nCerrando sistema..." << RESET << endl;
                break;
        }
    }
    return 0;
}