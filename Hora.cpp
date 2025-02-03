#include <iostream>
#include "Hora.h"

void Hora::setHora(int _hora) {
        if (_hora >= 0 && _hora < 24) {
            hora = _hora;
        } else {
            cout << "Hora invalida, debe estar entre 0 y 23." << endl;
        }
    }

void Hora::setMinuto(int _minuto) {
        if (_minuto >= 0 && _minuto < 60) {
            minuto = _minuto;
        } else {
            cout << "Minuto invalido, debe estar entre 0 y 59." << endl;
        }
    }

    /// Getters
int Hora::getHora() { return hora; }
int Hora::getMinuto() { return minuto; }

    /// Método para mostrar la hora en formato HH:MM
void Hora::mostrarHora() {
        cout << (hora < 10 ? "0" : "") << hora << ":"
             << (minuto < 10 ? "0" : "") << minuto;
    }

    /// Método para cargar la hora
void Hora::cargarHora() {
        int _hora, _minuto;
        while (true) {
            cout << "Ingrese la hora (0-23): ";
            cin >> _hora;
            cout << "Ingrese el minuto (0-59): ";
            cin >> _minuto;
            if (_hora >= 0 && _hora < 24 && _minuto >= 0 && _minuto < 60) {
                setHora(_hora);
                setMinuto(_minuto);
                break;
            } else {
                cout << "Hora o minuto inválido. Intente nuevamente." << endl;
            }
        }
    }


void Hora::cargarHoraReserva(){
int _hora;

do{
cout << "Ingrese la hora (20-23): ";
cin >> _hora;

if(_hora < 20 || _hora > 23){
    cout << "Hora no valida. Reintente." << endl;
    ///system("pause");
    ///system("cls");
    }
}while(_hora < 20 || _hora > 23);

hora = _hora;

}


