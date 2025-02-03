#include <iostream>
#include <cstring>
#include "Fecha.h"
#include "Login.h"
#include "Persona.h"
#include "Cliente.h"
#include "Empleado.h"
#include "ArchivoEmpleados.h"
#include "ArchivoProductos.h"
#include "ArchivoReservas.h"
#include "ArchivoMesas.h"
#include "ArchivoComanda.h"
#include "Comanda.h"
#include "Producto.h"
#include "Reserva.h"
#include "Menues.h"
#include "Hora.h"
#include "Mesa.h"
#include "Reportes.h"

using namespace std;

int main() {
    Login obj("admin","1234");

    while(true){
    if(obj.login()){
        mostrarMenuPrincipal();
        }
    }


    return 0;
}
