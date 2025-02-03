#include "Producto.h"
#include "Comanda.h"
#include "ArchivoComanda.h"
#include "Mesa.h"
#include <iostream>

using namespace std;


ArchivoComandas::ArchivoComandas(const char *_nombre) {
    strncpy(nombre, _nombre, 19); // Limitar el nombre del archivo a 19 caracteres
    tam = sizeof(Comanda);  // Tamaño de la clase Comanda
}

int ArchivoComandas::obtenerIdRegistro() {
    int cant;

    FILE *pComandas;
    pComandas = fopen(nombre, "ab+");  // Abrir archivo en modo binario lectura/escritura

    if (pComandas == nullptr) {
        cout << "Algo salio mal. Volviendo al menu" << endl;
        system("pause");
        system("cls");
        return -1;
    }

    fseek(pComandas, 0, 2);  // Ir al final del archivo
    cant = ftell(pComandas);  // Obtener el tamaño del archivo

    fclose(pComandas);

    if (!cant) return 1;  // Si el archivo está vacío, el primer ID es 1
    else return cant / tam + 1;  // ID es el tamaño del archivo dividido por el tamaño de la comanda
}

bool ArchivoComandas::grabarRegistro(Comanda obj) {
    FILE *pComandas;
    pComandas = fopen(nombre, "ab");  // Abrir archivo en modo binario para agregar datos

    if (pComandas == nullptr) {
        cout << "No se pudo establecer la conexion." << endl;
        return false;
    }

    int escribio = fwrite(&obj, tam, 1, pComandas);  // Escribir la comanda en el archivo

    fclose(pComandas);

    if (escribio) {
        cout << "Registro grabado con exito" << endl;
        system("pause");
        system("cls");
        return true;
    } else {
        cout << "No se pudo grabar el registro" << endl;
        system("pause");
        system("cls");
        return false;
    }
}

int ArchivoComandas::buscarRegistro() {
    system("cls");
    FILE *pComandas = fopen(nombre, "rb");
    if (!pComandas) {
        cout << "No se pudo establecer la conexión." << endl;
        system("pause");
        system("cls");
        return -1;
    }

    int id;
    cout << "Ingrese el ID a buscar (0 para volver al menú anterior): ";
    cin >> id;
    if (id == 0) return -2;

    int pos = 0;
    Comanda obj;
    while (fread(&obj, tam, 1, pComandas)) {
        if (obj.getIdComanda() == id) {  // Buscar por ID
            fclose(pComandas);
            return pos;
        }
        pos++;
    }

    fclose(pComandas);
    cout << "No se encontro una comanda con ese ID." << endl;
    return -1;
}

bool ArchivoComandas::listarRegistros() {
    system("cls");
    Comanda obj;

    FILE *pComandas = fopen(nombre, "rb");
    if (!pComandas) {
        cout << "No se encontraron registros en el archivo." << endl;
        system("pause");
        system("cls");
        return false;
    }

    while (fread(&obj, tam, 1, pComandas)) {
        obj.mostrarComanda();  // Mostrar la comanda
        cout << endl;
    }

    fclose(pComandas);
    system("pause");
    system("cls");
    return true;
}



bool ArchivoComandas::leerRegistro(int pos) {
    system("cls");

    if (pos == -1) {
        cout << "El ID no se encuentra en los registros." << endl;
        system("pause");
        system("cls");
        return false;
    }

    Comanda obj;
    FILE *pComandas = fopen(nombre, "rb");

    if (pComandas == nullptr) {
        cout << "No se pudo establecer la conexión." << endl;
        system("cls");
        return false;
    }

    fseek(pComandas, tam * pos, 0);

    int leyo = fread(&obj, tam, 1, pComandas);

    if (leyo) obj.mostrarComanda();
    else cout << "No se encuentran comandas con ese ID" << endl;

    system("pause");
    system("cls");
    fclose(pComandas);

    return leyo;
}


Comanda ArchivoComandas::buscarComanda(int idComanda) {
    system("cls");
    Comanda comanda;
    FILE *pComandas = fopen(nombre, "rb");

    if (pComandas == nullptr) {
        cout << "El archivo de comandas no se pudo encontrar o no existen registros." << endl;
        system("pause");
        system("cls");
        return comanda;  // Retorna una comanda vacía (por defecto)
    }

    // Buscamos la comanda por su ID
    while (fread(&comanda, tam, 1, pComandas)) {
        if (comanda.getIdComanda() == idComanda) {
            fclose(pComandas);
            return comanda;  // Retorna la comanda encontrada
        }
    }

    fclose(pComandas);  // Cerramos el archivo después de leerlo

}

void ArchivoComandas::resetearComandas() {
        // Abrir el archivo en modo binario para escritura (esto lo vacía)
        FILE* archivo = fopen(nombre, "wb");

        if (archivo == nullptr) {
            cout<< "Error al abrir el archivo para resetear." <<endl;
            return;
        }
        system("cls");
        // Si el archivo se abrió correctamente, lo truncamos a cero, sin escribir datos
        cout << "El archivo de comandas ha sido reiniciado." <<endl;

        // Cerramos el archivo
        fclose(archivo);
    }

