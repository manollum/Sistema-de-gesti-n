#include <iostream>
#include "Fecha.h"

using namespace std;

extern int diasMeses[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; ///array de los dias del mes que ayuda a verificar validacion de los parametros.


Fecha::Fecha(): dia (1), mes(1), anio(2024){}


Fecha::Fecha(int _dia, int _mes , int _anio) : dia(1), mes(1), anio(2024){ ///inicializacion fecha por defecto en caso de que los parametros no cumplan con las validaciones.

if(_mes >= 1 && _mes <= 12){
    if((_dia >= 1 && _dia <= diasMeses[_mes-1]) ||
        (_mes == 2 && _dia >= 1 &&
            ((_dia <= 29 && _anio %4 ==0  && _anio %100 != 0) ||
            ( _dia <= 29 && _anio %400 == 0)))){  ///verifica segun un limite de dias (array diasMeses) y si es año bisiesto.

            dia = _dia;
            mes = _mes;
            anio = _anio;
            }

        else{
        dia = 1;
        mes = 1;
        anio = 2024;
            }
        }
}

///Constructor para inicializar con la fecha del sistema
Fecha::Fecha(bool usarFechaSistema) {
if(usarFechaSistema){
    actualizarFecha();
    }
else{
dia = 1;
mes = 1;
anio = 2024;
    }
}

/// Nuevo método para actualizar la fecha con la fecha actual del sistema
void Fecha::actualizarFecha() {
time_t t = time(nullptr);          /// Obtiene el tiempo actual en formato epoch
tm* tiempoLocal = localtime(&t);  /// Convierte a tiempo local
dia = tiempoLocal->tm_mday;       /// Día del mes
mes = tiempoLocal->tm_mon + 1;    /// Mes (0-11, por eso sumamos 1)
anio = tiempoLocal->tm_year + 1900; /// Año desde 1900
}

void Fecha::setAnio(int _anio){
    anio = _anio; }

void Fecha::setMes(int _mes){
    mes = _mes; }

void Fecha::setDia(int _dia){
    dia = _dia; }


void Fecha::cargarFecha() {
    Fecha fechaActual(true);

    int _dia, _mes, _anio, volverMenu;

do{
        cout << "Ingrese el dia: ";
        cin >> _dia;
        cout << "Ingrese el mes: ";
        cin >> _mes;
        cout << "Ingrese el anio: ";
        cin >> _anio;

        if(_mes >= 1 && _mes <= 12){
        if((_dia >= 1 && _dia <= diasMeses[_mes-1]) ||
            (_mes == 2 && _dia >= 1 &&
                ((_dia <= 29 && _anio %4 ==0  && _anio %100 != 0) ||
                ( _dia <= 29 && _anio %400 == 0)))){  ///verifica segun un limite de dias (array diasMeses) y si es año bisiesto.

            dia = _dia;
            mes = _mes;
            anio = _anio;
            }

        else{
        dia = 1;
        mes = 1;
        anio = 2024;
            }
        }
        if (Fecha::getFecha()<fechaActual) {
            cout << "Fecha invalida. Presione '1' para volver a intentar o '0' para volver: " << endl;
            cin >> volverMenu;

            if(!volverMenu){
                dia = 0;
                system("cls");

                cout << "Volviendo al menu anterior..." << endl;
                system("pause");
                system("cls");
                break;
                }

            else
                system("cls");

        } else {
            break;
        }

    }while(true);
}


int Fecha::getDia(){ return dia; }
int Fecha::getMes(){ return mes; }
int Fecha::getAnio(){ return anio; }
Fecha Fecha::getFecha(){ return *this; }

void Fecha::mostrarFecha(){
cout << dia << "/" << mes << "/" << anio << endl;
}

bool Fecha::operator==(Fecha obj){
if(anio == obj.anio && mes == obj.mes && dia == obj.dia) return true;

return false;
}


bool Fecha::operator >= (Fecha obj){
if(anio > obj.anio) return true;
if(anio == obj.anio && mes > obj.mes) return true;
if(anio == obj.anio && mes == obj.mes && dia >= obj.dia) return true;

return false;

}


bool Fecha::operator >(Fecha obj){
if(anio > obj.getAnio()) return true;
if(anio == obj.getAnio() && mes > obj.getMes()) return true;
if(anio == obj.getAnio() && mes == obj.getMes() && dia > obj.getDia()) return true;

return false;
}


bool Fecha::operator <(Fecha obj){
if(anio<obj.anio) return true;
if(anio==obj.anio && mes<obj.mes) return true;
if(anio==obj.anio && mes==obj.mes && dia<obj.dia) return true;

return false;

}

bool Fecha::esFechaValida() {
    /// Obtener la fecha actual del sistema
    auto now = std::chrono::system_clock::now();
    std::time_t tiempoActual = std::chrono::system_clock::to_time_t(now);
    std::tm *horaLocal = std::localtime(&tiempoActual);

    int diaActual = horaLocal->tm_mday;
    int mesActual = horaLocal->tm_mon + 1; // Mes comienza en 0
    int anioActual = horaLocal->tm_year + 1900; // Año comienza en 1900

    /// Verificar si el año ingresado es menor al actual
    if (anio < anioActual) return false;

    /// Verificar si el mes ingresado es menor en el mismo año
    if (anio == anioActual && mes < mesActual) return false;

    /// Verificar si el día ingresado es menor en el mismo mes y año
    if (anio == anioActual && mes == mesActual && dia < diaActual) return false;

    /// Verificar días válidos para el mes ingresado
    if (mes < 1 || mes > 12 || dia < 1 || dia > diasMeses[mes - 1]) return false;

    /// Validar años bisiestos para febrero
    if (mes == 2 && dia == 29) {
        if (!((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))) return false;
    }

    return true; /// Fecha válida
}










