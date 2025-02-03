#pragma once
#include <iostream>
#include <string>

using namespace std;

class Login {
private:
    string username;
    string password;

public:
    /// Constructor
    Login(const string &user, const string &pass){ ///como en el main estan "hardcodeados" son datos que no cambian, se ponen const. y el &porque son las variables pasadas por referencia.
        username=user;
        password=pass;
    }

    /// Método para verificar las credenciales
    bool authenticate(const string &inputUser, const string &inputPass) {
        return (inputUser==username) && (inputPass==password);
    }


    bool login() {
        string inputUser, inputPass;
        system("cls");
        system("color 60");

        cout << "=== Login ===" << endl;
        cout << "Usuario: ";
        cin >> inputUser;
        cout << "Contrasenia: ";
        cin >> inputPass;

        if (authenticate(inputUser, inputPass)) {
            cout << "Bienvenido, " << inputUser << "!" << endl;
            system("pause");
            return true;
        } else {
            cout << "Usuario o contrasenia incorrectos. Intenta nuevamente." << endl;
            system("pause");
            return false;
        }
    }
};
