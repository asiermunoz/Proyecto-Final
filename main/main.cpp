/*
Asier Munoz 31307510
Mikel Munoz 31307510
Samuel Sangroni
*/

#pragma warning(disable : 4996);
#include <iostream>
#include <string>
#include<string.h>
using namespace std;

//ESTRUCTURAS
struct producto {
    string codigo;
    string nombre;
    string descripcion;
    string cantidad;
    string min;
    string precio;
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
    producto* aba;

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
struct detalle{
    string codigo;
    string cantidad;
    int precio;
    detalle* prox;
};
struct factura {
    string facturas;
    string cedula;
    string fecha;
    int monto;
    factura* prox;
    detalle* aba;
    
};

char* convertir_string_a_char_puntero(string str) {
    char* cstr = new char[100];
    strcpy(cstr, str.c_str());
    return cstr;
}


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
void archivo_nuevo(string x) {
    FILE* archivo;
    char* y = convertir_string_a_char_puntero(x);
    strcat(y, ".txt");
    archivo = fopen(y, "w");
    if (!archivo)
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);

    }
    fclose(archivo);
}
//*************************************************************************************************************************************


//FUNCIONES DE INVENTARIO
//*************************************************************************************************************************************

//funciona
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
void producto_nuevo_archivo(string nombre, string a, string b, string c, string d) {
    FILE* archivo;
    char* x = convertir_string_a_char_puntero(nombre);
    strcat(x, ".txt");
    archivo = fopen(x, "w");
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
void mostrar_codigo_sucursales(sucursal* p) {
    while (p) {
        cout << p->codigo << endl;
        p = p->prox;
    }
}
sucursal* posicion_sucursal(sucursal* p, string codigo) {
    while (p) {
        if (p->codigo == codigo)
            return p;
        p = p->prox;
    }
}

//revisar no funciona
void mostrar_inventario(sucursal* p) {
    if(p->aba != NULL){
        producto* x = p->aba;
        while (x) {
            cout << x->codigo;
            cout << endl;
            cout << x->cantidad;
            cout << endl;
            cout << x->min;
            cout << endl;
            cout << x->precio;
            cout << "\n\n";
            x = x->prox;
        }
    }
}
void insertar_producto_en_sucursal(sucursal** p, string codigo, string existencia, string min, string precio) {
    sucursal* ax = *p;
    producto* t = new producto;
    t->codigo = codigo;
    t->cantidad = existencia;
    t->min = min;
    t->precio = precio;
    t->prox = NULL;

    producto* m = ax->aba;
    if (ax->aba == NULL) {
        ax->aba = t;
    }
    else {
        while (m->prox != NULL) {
            m = m->prox;
        }
        m->prox = t;
    }
}
void abrir_archivo_producto(sucursal** p, string codigo) {
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

        insertar_producto_en_sucursal(p, linea1String, linea2String, linea3String, linea4String);
    }

    fclose(archivo);
}
void asignar_productos_a_sucursales(sucursal* p) {
    while (p) {
        //leer archivo codigosucursal.txt y asignarle todo a ax
        abrir_archivo_producto(&p, p->codigo);
        p = p->prox;
    }
}
//*************************************************************************************************************************************


// MENU DE MANTENIMIENTO SUCURSALES
//*************************************************************************************************************************************
void mantenimiento_sucursales_inventario() {
    string a, b, c, d, e;
    char* z;
    sucursal* p = NULL;
    int op = -1;
    abrir_sucursales(&p);
    sucursal* ax;
    //asigne los productos a cada sucursal
    asignar_productos_a_sucursales(p);
    while (op != 0) {
        int m = -1;
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t1.2.7 Mantenimiento de sucursales/inventario\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "Seleccione primero una de las siguientes sucursales para poder acceder a su inventario: \n";
        mostrar_codigo_sucursales(p);
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
            if (validar_codigo_sucursales(p, a)) {
                string nombre;
                while (p) {
                    if (p->codigo == a) {
                        nombre = p->nombre;
                        break;
                    }
                    p = p->prox;
                }
                while (m != 0) {
                    system("cls");
                    ax = posicion_sucursal(p, a);
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
                        insertar_producto_en_sucursal(&ax, b, c, d, e);
                        producto_nuevo_archivo(a, b, c, d, e);
                       
                        break;
                    case 2:
                        cout << "ingrese el codigo de producto a eliminar: ";
                        getline(cin, b);
                        
                        break;
                    case 3:

                        break;
                    case 4:
                        mostrar_inventario(ax);
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
                //crear_archivo_producto(a, )
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





//*************************************************************************************************************************************

// SUB MENUS -------------------------------------------------------------------------------------------
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
void facturacion_submenu(string tienda, string persona) {
    int op = -1;
    personas* m = NULL;
    sucursal* y = NULL;
    abrir_personas(&m);
    abrir_sucursales(&y);
    while (op != 0) {
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\tTIENDA" << "[" << tienda << "]\t\t\t\t\t" << "PERSONA" << "[" << persona << "]\t\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t2. Facturacion\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "2.1. Agregar producto\n";
        cout << "2.2. Mostrar factura\n";
        cout << "2.3. Eliminar factura\n";
        cout << "2.4. Mostrar resumen de facturas\n\n";
        cout << "0. VOLVER MENU ANTERIOR\n\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();


        switch (op) {
        case 1:
            //REVISAR PORQUE NO FUNCIONA
            abrir_archivo_producto(&y, tienda);
            mostrar_inventario(y);
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;
        }
        system("pause");
    }
};
void facturacion() {
    int op = -1;
    int c = 0;
    string cedula;
    string codigo;
    personas* m = NULL;
    sucursal* y = NULL;
    abrir_personas(&m);
    abrir_sucursales(&y);
    
    while (op != 0) {
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t2. Facturacion\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "Debde de seleccionar las dos opciones para proceder al siguiente menu\n";
        cout << "2.1. Seleccionar tienda\n";
        cout << "2.2. Seleccionar cliente\n"; 
        cout << "2.3. Proceder\n\n";
        cout << "0. VOLVER MENU ANTERIOR\n\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();


        switch (op) {
        case 1:
            cout << "introduce el codigo de la tienda: "; getline(cin, codigo);
            if (consultar_codigo_sucursal(y, codigo)) {
                c += 1;
            }
            else {
                cout << "No se encontro la tienda\n\n";
            }
            break;

        case 2:
            cout << "introduce la cedula del cliente: "; getline(cin, cedula);
            if (consultar_cedula(m, cedula)) {
                c += 1;
            }
            else {
                cout << "No se encontro la cedula del cliente\n\n";
            }
            break;

        case 3:
            if (c >= 2) {
                facturacion_submenu(codigo, cedula);
            }
            else {
                cout << "Debes de completar las dos opciones anteriores para seguir\n\n";
            }
            
            break;
        }
        system("pause");
    }
};
void submenu_de_reportes_clientes(char cedula[256]) {
    int op = -1;
    while (op != 0) {
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t3.1 Reportes del cliente\t" << "[" << cedula << "]\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "3.1.1 Mostrar el resumen de todas sus facturas \n";
        cout << "3.1.2 Mostrar el resumen de los productos adquiridos \n";
        cout << "3.1.3 Ingresar cedula del cliente \n\n";
        cout << "0. VOLVER MENU ANTERIOR\n\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;
        }
        system("pause");
    }
}
void submenu_de_reportes_tienda(char tienda[256]) {
    int op = -1;
    while (op != 0) {
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t3.2 Reportes de la tienda\t\t" << "[" << tienda << "]\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "3.2.1 Mostrar total de unidades vendidas \n";
        cout << "3.2.2 Mostrar total de unidades en existencia \n";
        cout << "3.2.3 Mostrar resumen de cliente en una fecha \n\n";
        cout << "0. VOLVER MENU ANTERIOR\n\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;
        }
        system("pause");
    }
}
void submenu_de_reportes_mercadeo() {
    int op = -1;
    while (op != 0) {
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t3.3 Reportes (mercadeo)\t\t\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "3.3.1 Total de ventas por codigo del producto \n";
        cout << "3.3.2 Total de ventas por codigo de la tienda \n";
        cout << "3.3.3 Total de cantidad comprada por cada cliente \n";
        cout << "3.3.4 Monto total de cada cliente\n";
        cout << "3.3.5 Total de ingresos de cada tienda \n\n";
        cout << "0. VOLVER MENU ANTERIOR\n\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;
        }
        system("pause");
    }
}
void reportes() {
    int op = -1;
    char cedula[256], tienda[256];
    while (op != 0) {
        system("cls");
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\tSISTEMA DE INVENTARIO Y FACTURACION\n";
        cout << "\t----------------------------------------------------------------\n";
        cout << "\t\t\t3. Reportes\n";
        cout << "\t----------------------------------------------------------------\n\n\n";
        cout << "3.1. Reportes de cliente \n";
        cout << "3.2. Reportes de tienda \n";
        cout << "3.3. Mercadeo \n\n";
        cout << "0. VOLVER MENU ANTERIOR\n\n";
        cout << "Elige una opcion: ";
        cin >> op;
        cin.ignore();


        switch (op) {
        case 1:
            cout << "Ingresa la cedula del cliente: "; cin >> cedula;
            // validar si la cedula del cliente existe, de ser asi se abre este menu:
            submenu_de_reportes_clientes(cedula);
            break;

        case 2:
            cout << "Ingresa el codigo de la tienda: "; cin >> tienda;
            // validar si el codigo de la tienda existe, de ser asi se abre este menu:
            submenu_de_reportes_tienda(tienda);
            break;

        case 3:
            submenu_de_reportes_mercadeo();
            break;
        }
        system("pause");
    }
}

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