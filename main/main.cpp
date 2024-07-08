/*
Asier Munoz 31307510
Mikel Munoz 31307510
Samuel Sangroni
*/

#include <iostream>
#include <string>
#include<string.h>
using namespace std;

//ESTRUCTURAS
struct producto {
    string codigo;
    string nombre;
    string descripcion;
    producto* prox;
};
struct sucursal {
    string codigo;
    string nombre;
    string ciudad;
    string estado;
    string telefono;
    string direccion;
    sucursal* prox;
};
struct stock {
    string codigo;
    string cantidad;
    string min;
    string precio;
    stock* prox;
};
struct inventario {
    string codigo;
    string nombre;
    stock* aba;
    inventario* sig;
};
struct personas {
    string cedula;
    string nombre;
    string direccion;
    string correo;
    string telefono;
    string ciudad;
    personas* prox;
};




//FUNCIONES DE MANTENIMINETO DE PRODUCTO
//*************************************************************************************************************************************
int validar_codigo_productos(producto* p, string x) {
    producto* ax = p;
    while (ax) {
        if (ax->codigo == x)
            return 1;
        ax = ax->prox;
    }
    return 0;
}
void insertar_codigo(producto** y, string x, string n, string z) {
    producto* t = new producto;
    if (!validar_codigo_productos(*y, x)) {
        t->codigo = x;
        t->nombre = n;
        t->descripcion = z;
        t->prox = *y;
        *y = t;
    }
};
void mostrar_lista_prodcutos(producto* y) {
    producto* t = y;
    cout << "\n\n\t\tProductos";
    cout << "\n------------------------------------------------------\n";
    cout << "codigo \t\t nombre \t descripcion";
    cout << "\n------------------------------------------------------\n";
    while (t) {
        cout << t->codigo << "\t\t" << t->nombre << "\t\t" << t->descripcion << "\n";
        t = t->prox;
    }
    cout << "\n-------------------------------------------------------\n";
}
void eliminar_producto(producto** y, string x) {
    producto* ax = *y, * h = ax;
    while (ax) {
        if ((*y)->codigo == x) {
            *y = ax->prox;
            delete ax;
            break;
        }
        if (ax->codigo == x) {
            h->prox = ax->prox;
            delete ax;
            break;
        }
        else {
            h = ax;
            ax = ax->prox;
        }
    }
}
void abrir_productos(producto** p) {
#pragma warning(disable : 4996);
    FILE* archivo;
    archivo = fopen("productos.txt", "r");
    if (!archivo) { cout << "Error al abrir archivo\n"; exit(EXIT_FAILURE); }

    char linea1[256], linea2[256], linea3[256];
    while (fgets(linea1, sizeof(linea1), archivo) != NULL &&
        fgets(linea2, sizeof(linea2), archivo) != NULL &&
        fgets(linea3, sizeof(linea3), archivo) != NULL) {
        linea1[strcspn(linea1, "\n")] = '\0';
        linea2[strcspn(linea2, "\n")] = '\0';
        linea3[strcspn(linea3, "\n")] = '\0';

        string linea1String(linea1);
        string linea2String(linea2);
        string linea3String(linea3);
        insertar_codigo(p, linea1String, linea2String, linea3String);

    }

    fclose(archivo);
};
void guardar_productos(producto* p) {
    producto* ax = p;
    FILE* archivo;
    archivo = fopen("Productos.txt", "w");
    if (!archivo)
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);

    }
    fflush(archivo);
    while (ax) {
        fprintf(archivo, "%s\n", ax->codigo.c_str());
        fprintf(archivo, "%s\n", ax->nombre.c_str());
        fprintf(archivo, "%s\n", ax->descripcion.c_str());
        ax = ax->prox;
    }
    fclose(archivo);
}
int consultar_codigo(producto* y, string x) {
    producto* ax = y;
    while (ax) {
        if (ax->codigo == x)
            return 1;
        else
            ax = ax->prox;
    }
    return 0;
}
int consultar_descripcion(producto* y, string x) {
    producto* ax = y;
    while (ax) {
        if (ax->descripcion == x)
            return 1;
        else
            ax = ax->prox;
    }
    return 0;
}
void modificar_nombre_productos(producto** y, string x, string n) {
    producto* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->nombre = n;
            break;

        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_descripcion_productos(producto** y, string x, string n) {
    producto* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->descripcion = n;
            break;

        }
        else {
            ax = ax->prox;
        }
    }
}
// MENU DE MANTENIMIENTO PRODUCTOS
void mantenimiento_productos() {
    int op = -1;
    string x, y, z, a;
    producto* p = NULL;
    abrir_productos(&p);
    while (op != 0) {
        int m = -1;
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t1.1. Mantenimiento de productos\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "1.1.1 Agregar \n";
        cout << "1.1.2 Modificar \n";
        cout << "1.1.3 Eliminar \n";
        cout << "1.1.4 Consulta por codigo \n";
        cout << "1.1.5 Consulta por descripcion \n";
        cout << "1.1.6 Mostrar todos los productos \n";
        cout << "0. VOLVER MENU ANTERIOR\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            cout << "ingrese el codigo: ";
            getline(cin, x);
            if (validar_codigo_productos(p, x) == 0) {
                cout << "ingrese el nombre: ";
                getline(cin, y);
                cout << "ingrese la descripcion: ";
                getline(cin, z);
                insertar_codigo(&p, x, y, z);
                guardar_productos(p);
            }
            else { cout << "el codigo ya existe \n\n"; }
            break;
        case 2:
            while (m != 0) {
                system("cls");
                cout << "\t----------------------------------------------------------------\n";
                cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
                cout << "\t----------------------------------------------------------------\n";
                cout << "\t\t\t1.1. Mantenimiento de productos (MODIFICAR)\n";
                cout << "\t----------------------------------------------------------------\n\n";
                cout << "1.1.1 Cambiar Nombre \n";
                cout << "1.1.2 Cambiar Descripcion \n";
                cout << "0. VOLVER MENU ANTERIOR \n";
                cout << "Elige una opcion: ";
                cin >> m;
                cin.ignore();
                switch (m) {
                case 1:
                    cout << "indique el codigo que quiere modificar: ";
                    getline(cin, x);
                    if (validar_codigo_productos(p, x) == 1) {
                        cout << "indique el nuevo nombre: ";
                        getline(cin, y);
                        modificar_nombre_productos(&p, x, y);
                        guardar_productos(p);
                        mostrar_lista_prodcutos(p);
                    }
                    else {
                        cout << "el codigo ingresado no es valido\n\n";
                    }
                    break;
                case 2:
                    cout << "indique el codigo que quiere modificar: ";
                    getline(cin, x);
                    if (validar_codigo_productos(p, x) == 1) {
                        cout << "indique la nueva descripcion: ";
                        getline(cin, y);
                        modificar_descripcion_productos(&p, x, y);
                        guardar_productos(p);
                        mostrar_lista_prodcutos(p);
                    }
                    else {
                        cout << "el codigo ingresado no es valido\n\n";
                    }
                    break;
                }
                system("pause");
            }
            break;
        case 3:
            cout << "ingrese el producto a eliminar : ";
            getline(cin, x);
            eliminar_producto(&p, x);
            guardar_productos(p);

            break;
        case 4:
            cout << "ingrese el codigo a buscar : ";
            getline(cin, x);
            if (consultar_codigo(p, x)) {
                cout << "el codigo " << x << " si se encuentra\n\n";
            }
            else {
                cout << "no se encontro nada.\n\n";
            }
            break;
        case 5:
            cout << "ingrese la descripcion a buscar : ";
            getline(cin, x);
            if (consultar_descripcion(p, x)) {
                cout << "la descripcion " << x << " si se encuentra\n\n";
            }
            else {
                cout << "no se encontro nada.\n\n";
            }
            break;
        case 6:
            mostrar_lista_prodcutos(p);
            guardar_productos(p);
            break;
        }
        system("pause");

    }
}
//*************************************************************************************************************************************





//FUNCIONES DE MANTENIMIENTO DE SUCURSALES
//*************************************************************************************************************************************
int validar_codigo_sucursales(sucursal* p, string x) {
    sucursal* ax = p;
    while (ax) {
        if (ax->codigo == x)
            return 1;
        ax = ax->prox;
    }
    return 0;
}
void insertar_sucursal(sucursal** y, string a, string b, string c, string d, string e, string f) {
    sucursal* t = new sucursal;
    if (!validar_codigo_sucursales(*y, a))
        t->codigo = a;
        t->nombre = b;
        t->ciudad = c;
        t->estado = d;
        t->telefono = e;
        t->direccion = f;
        t->prox = *y;
        *y = t;
}
void mostrar_sucursales(sucursal* y) {
    sucursal* t = y;
    cout << "\n\n\t\tSucursales";
    cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "codigo \t\t nombre \t\tciudad \t\testado \t\ttelefono \t\t\tdireccion";
    cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n";
    while (t) {
        cout << t->codigo << "\t\t" << t->nombre << "\t\t" << t->ciudad << "\t\t" << t->estado << "\t\t" << t->telefono << "\t\t" << t->direccion << "\n";
        t = t->prox;
    }
    cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n";
}
void eliminar_sucursal(sucursal** y, string x) {
    sucursal* ax = *y, * h = ax;
    while (ax) {
        if ((*y)->codigo == x) {
            *y = ax->prox;
            delete ax;
            break;
        }
        if (ax->codigo == x) {
            h->prox = ax->prox;
            delete ax;
            break;
        }
        else {
            h = ax;
            ax = ax->prox;
        }
    }
}
int consultar_codigo_sucursal(sucursal* y, string x) {
    sucursal* ax = y;
    while (ax) {
        if (ax->codigo == x)
            return 1;
        else
            ax = ax->prox;
    }
    return 0;
}
int consultar_direccion_sucursal(sucursal* y, string x) {
    sucursal* ax = y;
    while (ax) {
        if (ax->direccion == x)
            return 1;
        else
            ax = ax->prox;
    }
    return 0;
};
void abrir_sucursales(sucursal** p) {
#pragma warning(disable : 4996);
    FILE* archivo;
    archivo = fopen("Sucursales.txt", "r");
    if (!archivo) { cout << "Error al abrir archivo\n"; exit(EXIT_FAILURE); }

    char linea1[256], linea2[256], linea3[256], linea4[256], linea5[256], linea6[256];
    while (fgets(linea1, sizeof(linea1), archivo) != NULL &&
        fgets(linea2, sizeof(linea2), archivo) != NULL &&
        fgets(linea3, sizeof(linea3), archivo) != NULL &&
        fgets(linea4, sizeof(linea4), archivo) != NULL &&
        fgets(linea5, sizeof(linea5), archivo) != NULL &&
        fgets(linea6, sizeof(linea6), archivo) != NULL) {
        linea1[strcspn(linea1, "\n")] = '\0';
        linea2[strcspn(linea2, "\n")] = '\0';
        linea3[strcspn(linea3, "\n")] = '\0';
        linea4[strcspn(linea4, "\n")] = '\0';
        linea5[strcspn(linea5, "\n")] = '\0';
        linea6[strcspn(linea6, "\n")] = '\0';

        string linea1String(linea1);
        string linea2String(linea2);
        string linea3String(linea3);
        string linea4String(linea4);
        string linea5String(linea5);
        string linea6String(linea6);
        insertar_sucursal(p, linea1String, linea2String, linea3String, linea4String, linea5String, linea6String);

    }

    fclose(archivo);
}
void guardar_sucursales(sucursal* p) {
    sucursal* ax = p;
    FILE* archivo;
    archivo = fopen("Sucursales.txt", "w");
    if (!archivo)
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);

    }
    fflush(archivo);
    while (ax) {
        fprintf(archivo, "%s\n", ax->codigo.c_str());
        fprintf(archivo, "%s\n", ax->nombre.c_str());
        fprintf(archivo, "%s\n", ax->ciudad.c_str());
        fprintf(archivo, "%s\n", ax->estado.c_str());
        fprintf(archivo, "%s\n", ax->telefono.c_str());
        fprintf(archivo, "%s\n", ax->direccion.c_str());
        ax = ax->prox;
    }
    fclose(archivo);

}
void modificar_codigo_sucursales(sucursal** y, string x, string n) {
    sucursal* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->codigo = n;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_nombre_sucursales(sucursal** y, string x, string n) {
    sucursal* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->nombre = n;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_ciudad_sucursales(sucursal** y, string x, string n) {
    sucursal* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->ciudad = n;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_estado_sucursales(sucursal** y, string x, string n) {
    sucursal* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->estado = n;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_telefono_sucursales(sucursal** y, string x, string n) {
    sucursal* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->telefono = n;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_direccion_sucursales(sucursal** y, string x, string n) {
    sucursal* ax = *y;
    while (ax) {
        if (ax->codigo == x) {
            ax->direccion = n;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
//*************************************************************************************************************************************



//FUNCIONES DE INVENTARIO
//*************************************************************************************************************************************
int validar_codigo_inventario(inventario* p, string x) {
    while (p) {
        if (p->codigo == x) {
            return 1;
        }
        p = p->sig;
    }
    return 0;
}
int validar_codigo_producto_en_stock(inventario* p,string a, string x) {
    // a codigo de sucursal
    // x codigo de producto a buscar
    stock* ax = NULL;
    int c = 0;
    while (p) {
        if (p->codigo == a) {
            ax = p->aba;
            c = 1;
        }
        p = p->sig;
    }
    if (c == 1) {
        while (ax) {
            if (ax->codigo == x) {
                return 1;
            }
            ax->prox;
        }
    }
    return 0;
}
char* convertir_string_a_char_puntero(string str) {
    char* cstr = new char[100];
    strcpy(cstr, str.c_str());
    return cstr;
}
void crear_archivo_producto(string y, string a, string b, string c, string d) {
    FILE* archivo;
    char* x = convertir_string_a_char_puntero(y);
    strcat(x, ".txt");
    archivo = fopen(x, "w");
    if (!archivo) { cout << "Error al abrir archivo\n"; exit(EXIT_FAILURE); }
    fprintf(archivo, "%s\n", a.c_str());
    fprintf(archivo, "%s\n", b.c_str());
    fprintf(archivo, "%s\n", c.c_str());
    fprintf(archivo, "%s\n", d.c_str());


    fclose(archivo);
}


//insertar producto nuevo en el archivo
void producto_nuevo_archivo(string nombre, string a, string b, string c, string d) {
    FILE* archivo;
    char* x = convertir_string_a_char_puntero(nombre);
    strcat(x, ".txt");
    archivo = fopen(x, "a");
    if (!archivo)
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);

    }
        fprintf(archivo, "%s\n", a.c_str());
        fprintf(archivo, "%s\n", b.c_str());
        fprintf(archivo, "%s\n", c.c_str());
        fprintf(archivo, "%s\n", d.c_str());
        
    
    fclose(archivo);
}


//inserta el stock en cada aba
void insertar_stock_en_sucursal(inventario** p, string codigo_sucursal, string codigo, string existencia, string min, string precio) {
    inventario* ax = *p;
    stock* m;
    stock* t = new stock;
    t->codigo = codigo;
    t->cantidad = existencia;
    t->min = min;
    t->precio = precio;

    while (ax->codigo != codigo_sucursal) { ax = ax->sig; }
    if (ax->codigo == codigo_sucursal) {
        if (ax->aba == NULL) {
            ax->aba = t;
            t->prox = NULL;
        }
        else {
            m = ax->aba;
            while (m) {
                if (m->prox == NULL) {
                    m->prox = t;
                    t->prox = NULL;
                }
                m = m->prox;
            }
        }
    }
}


//lee archivo de nombre codigo sucursal.txt y la inserta en la multilista
void abrir_archivo_stock(inventario** p, string codigo) {
#pragma warning(disable : 4996);
    FILE* archivo;
    char* x = convertir_string_a_char_puntero(codigo);
    strcat(x, ".txt");
    archivo = fopen(x, "r");
    if (!archivo) { cout << "Error al abrir archivo\n"; exit(EXIT_FAILURE); }

    char linea1[256], linea2[256], linea3[256], linea4[256];
    while (fgets(linea1, sizeof(linea1), archivo) != NULL &&
        fgets(linea2, sizeof(linea2), archivo) != NULL && fgets(linea3, sizeof(linea3), archivo) != NULL &&
        fgets(linea4, sizeof(linea4), archivo) != NULL) {
        linea1[strcspn(linea1, "\n")] = '\0';
        linea2[strcspn(linea2, "\n")] = '\0';
        linea3[strcspn(linea3, "\n")] = '\0';
        linea4[strcspn(linea4, "\n")] = '\0';
        string linea1String(linea1);
        string linea2String(linea2);
        string linea3String(linea3);
        string linea4String(linea4);

        //insete el stock en la multilista inventario
        insertar_stock_en_sucursal(p, codigo, linea1String, linea2String, linea3String, linea4String);
    }

    fclose(archivo);
}


//mete todos los productos a sus respectivas sucursales
void insertar_stock_todos(inventario** p) {
    inventario* ax = *p;
    string codigo;
    while (ax) {
        codigo = ax->codigo;
        abrir_archivo_stock(p, codigo);
        ax = ax->sig;
    }
}

//mostrar solo codigo de sucursales
void mostrar_sucursales_inventario(inventario* p) {
    while (p) {
        cout << p->codigo << endl;
        p = p->sig;
    }
}

// recibe lista de sucursales y agrega a otro archivo codigo y nombre (inventario)
void insertar_codigos_en_archivo_inventario(sucursal* y) {
    sucursal* ax = y;
    FILE* archivo;
    archivo = fopen("codigos sucursales en inventario.txt", "w");
    if (!archivo){
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);
    }

    fflush(archivo);
    while (ax) {
        fprintf(archivo, "%s\n", ax->codigo.c_str());
        fprintf(archivo, "%s\n", ax->nombre.c_str());
        ax = ax->prox;
    }
    fclose(archivo);

}

//inserta los valores en la multilista
void insertar_inventario(inventario** p, string c, string n) {
    inventario* t = new inventario;
    //validar codigo de inventario
    t->codigo = c;
    t->nombre = n;
    t->sig = *p;
    *p = t;


}

//lee archivo codigos sucursales en inventario y le agrega a la multilista los valores
void abrir_inventario(inventario** p) {
#pragma warning(disable : 4996);
    FILE* archivo;
    archivo = fopen("codigos sucursales en inventario.txt", "r");
    if (!archivo) { cout << "Error al abrir archivo\n"; exit(EXIT_FAILURE); }

    char linea1[256], linea2[256];
    while (fgets(linea1, sizeof(linea1), archivo) != NULL &&
        fgets(linea2, sizeof(linea2), archivo) != NULL) {
        linea1[strcspn(linea1, "\n")] = '\0';
        linea2[strcspn(linea2, "\n")] = '\0';
        string linea1String(linea1);
        string linea2String(linea2);

        insertar_inventario(p, linea1String, linea2String);

    }

    fclose(archivo);

}

// eliminar producto del stock
//*************************************************************************************************************************************



// MENU DE MANTENIMIENTO SUCURSALES
//*************************************************************************************************************************************
void mantenimiento_sucursales_inventario() {
    string a, b, c, d, e;
    char* z;
    inventario* p = NULL;
    sucursal* y = NULL;
    int op = -1;
    abrir_sucursales(&y);
    insertar_codigos_en_archivo_inventario(y);
    abrir_inventario(&p);
    while (op != 0) {
        int m = -1;
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t1.2.7 Mantenimiento de sucursales/inventario\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "Seleccione primero una de las siguientes sucursales para poder acceder a su inventario: \n";
        mostrar_sucursales_inventario(p);
        cout << "\n";
        cout << "1.2.7.1 Seleccionar sucursal \n";
        cout << "0. VOLVER MENU ANTERIOR \n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            cout << "ingrese la sucursal: ";
            getline(cin, a);
            if (validar_codigo_inventario(p, a)) {
                string nombre;
                string codigo = a;
                while (y) {
                    if (y->codigo == codigo) {
                        nombre = y->nombre;
                        break;
                    }
                    y = y->prox;
                }
                while (m != 0) {
                    system("cls");
                    cout << "\t----------------------------------------------------------------\n";
                    cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
                    cout << "\t----------------------------------------------------------------\n";
                    cout << "\t\t\t1.2.7 Mantenimiento de sucursales/inventario\n";
                    cout << "\t----------------------------------------------------------------\n";
                    cout << "\t\t\t Sucursal:" << a << "   Nombre: " << nombre << "\n";
                    cout << "\t----------------------------------------------------------------\n\n\n";
                    cout << "1.2.7.1.1 Agregar productos \n";
                    cout << "1.2.7.1.2 Eliminar productos \n";
                    cout << "1.2.7.1.3 modificar Inventario \n";
                    cout << "1.2.7.1.4 Mostrar Productos \n";
                    cout << "0. VOLVER MENU ANTERIOR \n";

                    cout << "Elige una opcion: ";
                    cin >> m;
                    cin.ignore();

                    switch (m) {
                    case 1:
                        cout << "ingrese codigo del producto: ";
                        getline(cin, b);

                        cout << "ingrese existencia del producto: ";
                        getline(cin, c);
                        cout << "ingrese la existencia minima del producto: ";
                        getline(cin, d);
                        cout << "ingrese el precio del producto: ";
                        getline(cin, e);
                        producto_nuevo_archivo(a, b, c, d, e);
                        /*if (!validar_codigo_producto_en_stock(p, a, b)) { //NO FUNCIONA

                        }
                        else {
                            cout << "ese producto ya existe" << "\n\n";
                        }*/
                        break;
                    case 2:
                        cout << "ingrese el codigo de producto a eliminar: ";
                        getline(cin, b);
                        if (validar_codigo_producto_en_stock(p, a, b)) {

                        }
                        else {
                            cout << "el producto no existe" << "\n\n";
                        }
                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    }
                    system("pause");
                }
            }
            else {
                cout << "codigo invalido" << "\n\n";
            }
            break;


        }
        system("pause");

    }
};
void mantenimiento_sucursales() {
    int op = -1;
    string a, b, c, d, e, f;
    sucursal* p = NULL;
    abrir_sucursales(&p);
    string x, y;
    while (op != 0) {
        int m = -1;
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t1.2. Mantenimiento de sucursales\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "1.2.1 Agregar \n";
        cout << "1.2.2 Modificar \n";
        cout << "1.2.3 Eliminar \n";
        cout << "1.2.4 Consulta por codigo \n";
        cout << "1.2.5 Consulta por direccion \n";
        cout << "1.2.6 Mostrar todos los productos \n";
        cout << "1.2.7 Inventario \n";
        cout << "0. VOLVER MENU ANTERIOR \n";
        cout << "Elige una opcion: "; cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            cout << "ingrese el codigo: "; getline(cin, a);
            if (validar_codigo_sucursales(p, a) == 0) {
                cout << "ingrese el nombre: "; getline(cin, b);
                cout << "ingrese el ciudad: "; getline(cin, c);
                cout << "ingrese el estado: "; getline(cin, d);
                cout << "ingrese el telefono: "; getline(cin, e);
                cout << "ingrese el direccion: "; getline(cin, f);
                insertar_sucursal(&p, a, b, c, d, e, f);
                guardar_sucursales(p);
            }
            else { cout << "el codigo ya existe \n\n"; }
            break;
        case 2:
            while (m != 0) {
                system("cls");
                cout << "\t----------------------------------------------------------------\n";
                cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
                cout << "\t----------------------------------------------------------------\n";
                cout << "\t\t\t1.1. Mantenimiento de sucursales (MODIFICAR)\n";
                cout << "\t----------------------------------------------------------------\n\n";
                cout << "1.1.1 Cambiar Nombre \n";
                cout << "1.1.2 Cambiar Ciudad \n";
                cout << "1.1.3 Cambiar Estado \n";
                cout << "1.1.4 Cambiar Telefono \n";
                cout << "1.1.5 Cambiar Direccion \n";
                cout << "0. VOLVER MENU ANTERIOR \n";
                cout << "Elige una opcion: ";
                cin >> m;
                cin.ignore();


                switch (m) {
                case 1:
                    cout << "indique el codigo que quiere modificar: ";
                    getline(cin, x);
                    if (validar_codigo_sucursales(p, x) == 1) {
                        cout << "indique el nuevo nombre: ";
                        getline(cin, y);
                        modificar_nombre_sucursales(&p, x, y);
                        guardar_sucursales(p);
                        mostrar_sucursales(p);
                    }
                    else {
                        cout << "el codigo ingresado no es valido\n\n";
                    }
                    break;
                case 2:
                    cout << "indique el codigo que quiere modificar: ";
                    getline(cin, x);
                    if (validar_codigo_sucursales(p, x) == 1) {
                        cout << "indique el nuevo ciudad: ";
                        getline(cin, y);
                        modificar_ciudad_sucursales(&p, x, y);
                        guardar_sucursales(p);
                        mostrar_sucursales(p);
                    }
                    else {
                        cout << "el codigo ingresado no es valido\n\n";
                    }
                    break;
                case 3:
                    cout << "indique el codigo que quiere modificar: ";
                    getline(cin, x);
                    if (validar_codigo_sucursales(p, x) == 1) {
                        cout << "indique el nuevo estado: ";
                        getline(cin, y);
                        modificar_estado_sucursales(&p, x, y);
                        guardar_sucursales(p);
                        mostrar_sucursales(p);
                    }
                    else {
                        cout << "el codigo ingresado no es valido\n\n";
                    }
                    break;
                case 4:
                    cout << "indique el codigo que quiere modificar: ";
                    getline(cin, x);
                    if (validar_codigo_sucursales(p, x) == 1) {
                        cout << "indique el nuevo telefono: ";
                        getline(cin, y);
                        modificar_telefono_sucursales(&p, x, y);
                        guardar_sucursales(p);
                        mostrar_sucursales(p);
                    }
                    else {
                        cout << "el codigo ingresado no es valido\n\n";
                    }
                    break;
                case 5:
                    cout << "indique el codigo que quiere modificar: ";
                    getline(cin, x);
                    if (validar_codigo_sucursales(p, x) == 1) {
                        cout << "indique la nueva direccion: ";
                        getline(cin, y);
                        modificar_direccion_sucursales(&p, x, y);
                        guardar_sucursales(p);
                        mostrar_sucursales(p);
                    }
                    else {
                        cout << "el codigo ingresado no es valido\n\n";
                    }
                    break;
                }
                system("pause");
            }
            break;
        case 3:
            cout << "ingrese el codigo de la sucursal a eliminar: ";
            getline(cin, a);
            eliminar_sucursal(&p, a);
            guardar_sucursales(p);
            break;
        case 4:
            cout << "ingrese el codigo de la sucursal a buscar: ";
            getline(cin, a);
            if (consultar_codigo_sucursal(p, a)) {
                cout << "el codigo " << a << " si se encuentra\n\n";
            }
            else {
                cout << "no se encontro nada.";
            }
            break;
        case 5:
            cout << "ingrese la direccion de la sucursal a buscar: ";
            getline(cin, a);
            if (consultar_direccion_sucursal(p, a)) {
                cout << "la direccion " << a << " si se encuentra\n\n";
            }
            else {
                cout << "no se encontro nada.";
            }
            break;
        case 6:
            mostrar_sucursales(p);
            break;
        case 7:
            mantenimiento_sucursales_inventario();
            break;
        }
        system("pause");
    }
}
//*************************************************************************************************************************************


//PERSONAS
//*************************************************************************************************************************************
int validar_cedula_personas(personas* p, string x) {
    personas* ax = p;
    while (ax) {
        if (ax->cedula == x)
            return 1;
        ax = ax->prox;
    }
    return 0;
}
void insertar_persona(personas** y, string c, string n, string direccion, string correo, string telefono, string ciudad) {
    personas* t = new personas;
    if (!validar_cedula_personas(*y, c)) {
        t->cedula = c;
        t->nombre = n;
        t->direccion = direccion;
        t->correo = correo;
        t->telefono = telefono;
        t->ciudad = ciudad;
        
        t->prox = *y;
        *y = t;
    }
};
void mostrar_lista_personas(personas* y) {
    personas* t = y;
    cout << "\n\n\t\Personas";
    cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "cedula\t\t\tnombre\t\t\tdireccion\t\t\tcorreo\t\t\t\t telefono \t\t ciudad";
    cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    while (t) {
        cout << t->cedula << "\t\t" << t->nombre << "\t\t" << t->direccion << "\t\t" << t->correo << "\t\t" << t->telefono << "\t\t" << t->ciudad << "\n";
        t = t->prox;
    }
    cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}
void eliminar_persona(personas** y, string x) {
    personas* ax = *y, * h = ax;
    while (ax) {
        if ((*y)->cedula == x) {
            *y = ax->prox;
            delete ax;
            break;
        }
        if (ax->cedula == x) {
            h->prox = ax->prox;
            delete ax;
            break;
        }
        else {
            h = ax;
            ax = ax->prox;
        }
    }
}
void abrir_personas(personas** p) {
#pragma warning(disable : 4996);
    FILE* archivo;
    archivo = fopen("Personas.txt", "r");
    if (!archivo) { cout << "Error al abrir archivo\n"; exit(EXIT_FAILURE); }

    char linea1[256], linea2[256], linea3[256], linea4[256], linea5[256], linea6[256];
    while (fgets(linea1, sizeof(linea1), archivo) != NULL &&
        fgets(linea2, sizeof(linea2), archivo) != NULL &&
        fgets(linea3, sizeof(linea3), archivo) != NULL &&
        fgets(linea4, sizeof(linea4), archivo) != NULL &&
        fgets(linea5, sizeof(linea5), archivo) != NULL &&
        fgets(linea6, sizeof(linea6), archivo) != NULL) {

        linea1[strcspn(linea1, "\n")] = '\0';
        linea2[strcspn(linea2, "\n")] = '\0';
        linea3[strcspn(linea3, "\n")] = '\0';
        linea4[strcspn(linea4, "\n")] = '\0';
        linea5[strcspn(linea5, "\n")] = '\0';
        linea6[strcspn(linea6, "\n")] = '\0';

        string linea1String(linea1);
        string linea2String(linea2);
        string linea3String(linea3);
        string linea4String(linea4);
        string linea5String(linea5);
        string linea6String(linea6);

        insertar_persona(p, linea1String, linea2String, linea3String, linea4String, linea5String, linea6String);

    }

    fclose(archivo);
};
void guardar_personas(personas* p) {
    personas* ax = p;
    FILE* archivo;
    archivo = fopen("Personas.txt", "w");
    if (!archivo)
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);

    }
    fflush(archivo);
    while (ax) {
        fprintf(archivo, "%s\n", ax->cedula.c_str());
        fprintf(archivo, "%s\n", ax->nombre.c_str());
        fprintf(archivo, "%s\n", ax->direccion.c_str());
        fprintf(archivo, "%s\n", ax->correo.c_str());
        fprintf(archivo, "%s\n", ax->telefono.c_str());
        fprintf(archivo, "%s\n", ax->ciudad.c_str());
        
        ax = ax->prox;
    }
    fclose(archivo);
}
int consultar_cedula(personas* y, string x) {
    personas* ax = y;
    while (ax) {
        if (ax->cedula == x)
            return 1;
        else
            ax = ax->prox;
    }
    return 0;
}
int consultar_nombre(personas* y, string x) {
    personas* ax = y;
    while (ax) {
        if (ax->nombre == x)
            return 1;
        else
            ax = ax->prox;
    }
    return 0;
}
void modificar_nombre(personas** y, string x, string nombre) {
    personas* ax = *y;
    while (ax) {
        if (ax->cedula == x) {
            ax->nombre = nombre;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_direccion(personas** y, string x, string direccion) {
    personas* ax = *y;
    while (ax) {
        if (ax->cedula == x) {
            ax->direccion = direccion;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_correo(personas** y, string x, string correo) {
    personas* ax = *y;
    while (ax) {
        if (ax->cedula == x) {
            ax->correo = correo;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_telefono(personas** y, string x, string telefono) {
    personas* ax = *y;
    while (ax) {
        if (ax->cedula == x) {
            ax->telefono = telefono;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}
void modificar_ciudad(personas** y, string x, string ciudad) {
    personas* ax = *y;
    while (ax) {
        if (ax->cedula == x) {
            ax->ciudad = ciudad;
            break;
        }
        else {
            ax = ax->prox;
        }
    }
}

// MENU DE MANTENIMIENTO PERSONAS
void mantenimiento_personas() {
    int op = -1;
    string x, y, z, a;
    string nombre, direccion, correo, telefono, ciudad;
    personas* p = NULL;
    abrir_personas(&p);
    while (op != 0) {
        int m = -1;
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE MANTENIMIENTO DE PERSONAS\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t1.1. Mantenimiento de Personas\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "1.1.1 Agregar Personas \n";
        cout << "1.1.2 Modificar Persona \n";
        cout << "1.1.3 Eliminar Persona \n";
        cout << "1.1.4 Consulta por cedula \n";
        cout << "1.1.5 Consulta por nombre \n";
        cout << "1.1.6 Mostrar todos las personas registradas \n";
        cout << "0. VOLVER MENU ANTERIOR\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            cout << "ingrese el cedula: ";
            getline(cin, x);
            if (validar_cedula_personas(p, x) == 0) {
                cout << "ingrese el nombre y Apellido (Xxxx Xxxx): ";
                getline(cin, nombre);
                cout << "ingrese la direccion: ";
                getline(cin, direccion);
                cout << "ingrese el correo (example@example.com): ";
                getline(cin, correo);
                cout << "ingrese el telefono: ";
                getline(cin, telefono);
                cout << "ingrese la ciudad: ";
                getline(cin, ciudad);
                insertar_persona(&p, x, nombre, direccion, correo, telefono, ciudad);
                guardar_personas(p);
            }
            else { cout << "la cedula ya existe \n\n"; }
            break;
        case 2:
            /*cout << "ingrese el cedula: ";
            getline(cin, x);
            if (validar_cedula_personas(p, x) == 1) {
                cout << "ingrese el nuevo nombre: ";
                getline(cin, y);
                modificar_nombre(&p, x, y);
                guardar_personas(p);
            }
            else { cout << "la cedula no existe \n\n"; }*/
            while (m != 0) {
                system("cls");
                cout << "\t----------------------------------------------------------------\n";
                cout << "\t\t\tSISTEMA DE MANTENIMIENTO DE PERSONAS\n";
                cout << "\t----------------------------------------------------------------\n";
                cout << "\t\t\t1.3. Mantenimiento de Personas (MODIFICAR)\n";
                cout << "\t----------------------------------------------------------------\n\n";
                cout << "1.1.1 Cambiar Nombre \n";
                cout << "1.1.2 Cambiar Direccion \n";
                cout << "1.1.3 Cambiar Correo \n";
                cout << "1.1.4 Cambiar Telefono \n";
                cout << "1.1.5 Cambiar Ciudad \n";
                cout << "0. VOLVER MENU ANTERIOR \n";
                cout << "Elige una opcion: ";
                cin >> m;
                cin.ignore();


                switch (m) {
                case 1:
                    cout << "indique la cedula que quiere modificar: ";
                    getline(cin, x);
                    if (validar_cedula_personas(p, x) == 1) {
                        cout << "indique el nuevo nombre: ";
                        getline(cin, y);
                        modificar_nombre(&p, x, y);
                        guardar_personas(p);
                        mostrar_lista_personas(p);
                    }
                    else {
                        cout << "la cedula ingresado no es valido\n\n";
                    }
                    break;
                case 2:
                    cout << "indique la cedula que quiere modificar: ";
                    getline(cin, x);
                    if (validar_cedula_personas(p, x) == 1) {
                        cout << "indique la nueva direccion: ";
                        getline(cin, y);
                        modificar_direccion(&p, x, y);
                        guardar_personas(p);
                        mostrar_lista_personas(p);
                    }
                    else {
                        cout << "la cedula ingresado no es valido\n\n";
                    }
                    break;
                case 3:
                    cout << "indique la cedula que quiere modificar: ";
                    getline(cin, x);
                    if (validar_cedula_personas(p, x) == 1) {
                        cout << "indique el nuevo estado: ";
                        getline(cin, y);
                        modificar_correo(&p, x, y);
                        guardar_personas(p);
                        mostrar_lista_personas(p);
                    }
                    else {
                        cout << "la cedula ingresado no es valido\n\n";
                    }
                    break;
                case 4:
                    cout << "indique la cedula que quiere modificar: ";
                    getline(cin, x);
                    if (validar_cedula_personas(p, x) == 1) {
                        cout << "indique el nuevo telefono: ";
                        getline(cin, y);
                        modificar_telefono(&p, x, y);
                        guardar_personas(p);
                        mostrar_lista_personas(p);
                    }
                    else {
                        cout << "la cedula ingresado no es valido\n\n";
                    }
                    break;
                case 5:
                    cout << "indique la cedula que quiere modificar: ";
                    getline(cin, x);
                    if (validar_cedula_personas(p, x) == 1) {
                        cout << "indique la nueva ciudad: ";
                        getline(cin, y);
                        modificar_ciudad(&p, x, y);
                        guardar_personas(p);
                        mostrar_lista_personas(p);
                    }
                    else {
                        cout << "la cedula ingresado no es valido\n\n";
                    }
                    break;
                }
                system("pause");
            }
            break;
        case 3:
            cout << "ingrese la cedula a eliminar : ";
            getline(cin, x);
            if (validar_cedula_personas(p, x) == 1) {
                eliminar_persona(&p, x);
                guardar_personas(p);

            }
            else { cout << "la cedula no existe \n\n"; }


            break;
        case 4:
            cout << "ingrese la cedula a buscar : ";
            getline(cin, x);
            if (consultar_cedula(p, x) == 1) {
                cout << "la cedula " << x << " si se encuentra\n\n";
            }
            else {
                cout << "no se encontro nada.\n\n";
            }
            break;
        case 5:
            cout << "ingrese el nombre a buscar a buscar : ";
            getline(cin, x);
            if (consultar_nombre(p, x)) {
                cout << "la descripcion " << x << " si se encuentra\n\n";
            }
            else {
                cout << "no se encontro nada.\n\n";
            }
            break;
        case 6:
            mostrar_lista_personas(p);
            guardar_personas(p);
            break;
        }
        system("pause");

    }
}
//*************************************************************************************************************************************


// FACTURACION



// SUB MENU -------------------------------------------------------------------------------------------
void mantenimiento() {
    int op = -1;
    while (op != 0) {
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t1. Mantenimiento\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "1.1. Productos\n";
        cout << "1.2. Sucursales\n";
        cout << "1.3. Personas\n\n";
        cout << "0. VOLVER MENU ANTERIOR\n\n";
        cout << "Elige una opcion: ";
        cin >> op;



        switch (op) {
        case 1:
            mantenimiento_productos();
            break;

        case 2:
            mantenimiento_sucursales();
            break;
        case 3:
            mantenimiento_personas();
            break;
        }
    }
};
void facturacion() {}
void reportes() {}

//MAIN ------------------------------------------------------------------------------------------------
int main() {
    int op = -1;


    while (op) {
        system("cls");
        cout << "\t----------------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------------\n";
        cout << "Menu principal\n\n";
        cout << "1. Mantenimiento\n";
        cout << "2. Facturacion\n";
        cout << "3. Reportes\n\n";
        cout << "0. SALIR\n\n";
        cout << "\t----------------------------------------------------------------------\n";
        cout << "\t\t\tRealizado por: Mikel Munoz y Asier Munoz\n";
        cout << "\t----------------------------------------------------------------------\n\n";
        cout << "Elige una opcion: ";
        cin >> op;


        switch (op) {
        case 1:
            mantenimiento();
            break;
        case 2:
            facturacion();
            break;
        case 3:
            reportes();
            break;

        }
        system("pause");
    }
};