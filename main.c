#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include <wchar.h> /// ASTERISCOS
#include <locale.h>  /// ASTERISCOS

typedef struct
{
    int idUsuario;                 /// Id Usuario.
    int rol;                /// 0=ADMIN  1=CLIENTE  2=INVITADO  3=CLIENTE VIP
    char mail[30];         /// CADENA CON VALIDACION: ' @ .  '
    char nombre[30];
    char apellido[30];
    char nombreUsuario[20];/// Nombre del usuario.
    unsigned int pin;      /// PIN, 6 DIGITOS DE NUMERO ENTERO
    char genero;
    int activo;             ///indica 1 o 0 si el usuario está activo
    unsigned  int edad;

} stUsuario;        /// Cambio de nombre de stCliente a stUsuario !!

typedef struct
{
    int idProducto;
    char nombre[30];
    float valor;
    int stock;          /// STOCK DE CADA PRODUCTO
    int categoria; ///1 panes, 2 bebidas, 3 bebidas con alcohol(+18), 4 lacteos, 5 carnes, 6 verdu, 7 bazar, 8 almacen.
} stProducto;

typedef struct
{
    int idPedido;        // auto incremental
    int idUsuario;       ///ID DEL USUARIO QUE ESTA PIDIENDO
    char fecha[20];      /// dd/MM/aaaa HORA
    stProducto chango[100];   /// CHANGUITO PARA EL USUARIO (TRANSPORTADOR DE PRODUCTOS)
    int valChango;            /// Cantidad de PRODUCTOS dentro del CHANGO
    float costo;        /// SUMA DE COSTOS TOTALES DEL CHANGUITO
    int pedidoAnulado;    /// indica 1 o 0 si el pedido fue anulado o no

} stPedido;

/// ##############      FUNCIONES DE ADMINS / USUARIOS      ####################

///MENU'S
void seleccionRol(stUsuario conectado[], char dirUsuarios[], char dirPedidos[], char dirProductos[]);
void menuAdmin(char dirUsuarios[], char dirPedidos[], char dirProductos[],stUsuario conectado);
void menuCliente(stUsuario conectado[], char dirUsuarios[], char dirPedidos[], char dirProductos[]);

/// INICIOS DE SESION
void ingreso ();                     /// ABUELO
stUsuario inicioDeSesion ( char dirUsuarios []);
int vUsuarioyPIN(stUsuario aux[], int pos, char dirUsuarios[]);
stUsuario levantaUsuario (char dirUsuarios [], int pos);  ///FUNCION QUE LEVANTA EL USUARIO CONECTADO

/// INVITADOS
void catalogoInvitado (char dirProductos []);

///FUNCIONES DE LOS ADMINS
int pedidoAdmin (char dirUsuarios []);
void vaciaArchi(char dirUsuarios[]);
int opcionEditar (int cantidad);
void admMenuModificador (char dirUsuarios[], char dirProductos []); ///modifica todo acomoden xD

/// FILTROS DE ADMINS

void filtrosAdmin(char dirUsuarios[]);  /// PADRE
void buscaUsuariosPorEstado(char dirUsuarios[], int dato);
void ordenarUsuariosAlfabeticamente(stUsuario A[], int cantidad);
void insertarUsuarioOrdenado(stUsuario A[], int pos, stUsuario B);
void buscarMayorDeEdad (char dirUsuarios []);
void admListados(char dirUsuarios[], char dirProductos[]);

///MODIFICACION/CONFIGURACION CLIENTES
void modCliente(stUsuario aux1, int aux, char dirUsuarios[]);
stUsuario modUsuarioConectado(stUsuario conectado[], char dirUsuarios[]);
void configCliente(stUsuario conectado[], char dirUsuarios[]);
void modUsuario(char dirUsuarios[]);
stUsuario modificaUsuario(stUsuario aux[], int pos, char dirUsuarios[]);

/// Validaciones de datos
int vMail(stUsuario aux[], int pos);
int vNUsuario(stUsuario aux[], int pos, char dirUsuarios[]);

/// CARGA DE DATOS
void cargaCliente(char nombreArchivo[]);
int cuentaClientesEnArchivo(char dirUsuarios[]);
void cMail(stUsuario aux[], int pos);
void cNombre(stUsuario aux[], int pos);
void cApellido(stUsuario aux[], int pos);
void cNUsuario(stUsuario aux[], int pos, char dirUsuarios[]);
void cPin(stUsuario aux[], int pos);
void cGenero(stUsuario aux[], int pos);
void cEdad (stUsuario aux [], int pos);
stUsuario estadoCliente(stUsuario aux[], int pos, int estado);
stUsuario estadoRol(stUsuario aux[], int pos, int estado);


/// ALGO TO ARCHI'S
void arregloToArchi(char dirUsuarios[], stUsuario aux[], int pos);

/// ARCHI TO ARREGLO
int archivoUsuariosToArreglo(stUsuario aux[], char dirUsuarios[]);

///MOSTRADORES
void muestraArchivo(char dirUsuarios[]);
void mostrarArregloUsuarios(stUsuario aux[], int cantidad);
void muestraArreglo(stUsuario aux[], int pos);
void mIdCliente(stUsuario aux[], int pos);
void mMail(stUsuario aux[], int pos);
void mNombre(stUsuario aux[], int pos);
void mApellido(stUsuario aux[], int pos);
void mNUsuario(stUsuario aux[], int pos);
void mPin(stUsuario aux[], int pos);
void mEdad(stUsuario aux[], int pos);
void mGenero(stUsuario aux[], int pos);
void mEstado(stUsuario aux[], int pos);
void mRol(stUsuario aux[], int pos);


///     ############        FUNCIONES DE PEDIDOS Y PRODUCTOS    ##############

/// PEDIDOS
void generaPedido(stUsuario conectado, char dirPedidos[], char dirProductos[]);
stPedido cargaPedido(char dirPedidos[], char dirProductos[], stUsuario conectado, stPedido aux);
stPedido bajaChango(stPedido aux, char estado);
stPedido modChango (stPedido aux);
int cuentaPedidosEnArchivo(char dirPedidos[]);
stPedido diaYHora(stPedido aux);

stPedido cargaArregloChango( stPedido aux, stProducto arregloCat[], int validos,int dato, int k);
int arregloDeCategoria(stProducto aux[], stProducto aux1[], int validos, int dato);

///PRODUCTOS

///Carga de productos
void cargaProducto(char dirProductos[]);
void cNombreProducto (stProducto aux [], int pos);
void cValor (stProducto aux [], int pos);
void cStock (stProducto stock [], int pos);
int cuentaProductosEnArchivo(char dirProductos[]);
void cCategoria (stProducto aux[], int pos);
int cargaDato();

/// MOSTRADORES
void mostrarProductos(char dirProductos[]);
void muestraListadoGeneral();
void mostrarProducto (stProducto aux, int cont);
void listadoProductos (stProducto aux[], int validos);
void mostrarArchivoPedidos(char dirPedidos[], int cant);
void mostrarArregloChango (stPedido aux);
void admMostrarProducto (stProducto aux, int cont);

/// ALGO TO ARCHi

void productoToarchi(char dirProductos[], stProducto aux[], int pos);

void pedidoToArchi(char dirPedidos[], stPedido aux );

/// ARCHI TO ARREGLOS

int archivoProductosToArreglo(char dirProductos[], stProducto aux[]);

/// MODIFICACION PRODUCTOS
void modProductos (char dirProducto [], stProducto aux, int aux1);
int idProductoEditar(char dirProductos[]);
void modificacionProductoToArchi(char dirProductos[]);
stProducto modificaProducto(stProducto aux[], int pos, char dirProductos[]);

///VARIOS
void infoVip ();
stUsuario vVip(stUsuario conectado[]);


void limpieza();

int main()
{
    //char activo[]= {"clienteA.dat"};
    //char dirUsuarios[]= {"usuarios.dat"}; /// dir usuarios.dat = Va a contener todos mis usuarios, admins, clientes y clientes vip
    //char dirPedidos[]= {"pedidos.dat"};
    system("color F0"); /// Se declaran con hexadecimales  del 0 a la F (del 0 al 15)
    //stUsuario conectado[1];
    //conectado[1]= inicioDeSesion(dirUsuarios);
    //seleccionRol(conectado,dirUsuarios, dirPedidos);  /// Le pasamos dir pedidos, para manejar el archivo  de pedidos
    ingreso();


    return 0;
}

/// ##############      FUNCIONES DE ADMINS / USUARIOS      ####################

///MENU'S
void seleccionRol(stUsuario conectado[],char dirUsuarios[], char dirPedidos[], char dirProductos[])
{
    //int valor =0;
    /*    valor = pagoVip();*/

    if(conectado[0].rol==0)
    {
        limpieza();
        menuAdmin(dirUsuarios, dirPedidos, dirProductos,conectado[0]);
    }
    else
    {
        if(conectado[0].rol==1)
        {
            limpieza();
            menuCliente(conectado,dirUsuarios, dirPedidos, dirProductos);    /// Menu Cliente recibe por parametro, y la direccicon de los pedidos
        }else
            if (conectado[0].rol == 3)
        {
            printf("\n SOS VIP");
            //menuClienteVip();
        }


    }
}

void menuAdmin(char dirUsuarios[], char dirPedidos[], char dirProductos[],stUsuario conectado)
{
    //char dirAdmins []= {"admins.dat"}; /// EN CONSTRUCCION
    //char dirUsuarios[]= {"datos/usuarios.dat"}; /// dir usuarios.dat = Va a contener todos mis usuarios, admins, clientes y clientes vip
    //char dirProductos[]= {"datos/productos.dat"};
    int op=0;
    do
    {
        limpieza();
        printf("\n ===============================================================================\n");
        printf("\n\t\t -Hola SR %s - ,  BIENVENIDO AL SISTEMA\n", conectado.nombreUsuario);
        printf("\n ===============================================================================\n");
        printf("\n\tMENU ADMINISTRADORES.\n");
        printf("\n\t1 - CARGA DE CLIENTES  ");
        printf("\n\t2 - Filtros. ");
        printf("\n\t3 - Modificaciones. ");
        printf("\n\t4 - Carga productos.");
        printf("\n\t5 - Listados Completos.");
        printf("\n\t99 - VACIA EL ARCHIVO (**OJO**).");
        /*printf("\t5 - DESCRIPCION DE FUNCION A LLAMAR  ----------\n");*/
        printf("\n\t0 - Cerrar sesion.. ");
        printf("\n\nIngrese su opcion: ");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            limpieza();
            cargaCliente(dirUsuarios);
            break;
        case 2:
            limpieza();
            filtrosAdmin(dirUsuarios);
            // muestraArchivo(dirUsuarios);
            break;
        case 3:
            limpieza();
            admMenuModificador (dirUsuarios, dirProductos);
            break;
        case 4:
            limpieza();
            cargaProducto(dirProductos);
            break;
        case 5:
            limpieza();
            admListados(dirUsuarios, dirProductos);
            break;
        case 6:
            //modProductos(dirProductos,);
            break;
        case 99:
            limpieza();
            vaciaArchi(dirUsuarios);
            break;
        default:
            printf("\n");
            break;
        }
    }
    while (op!=0);
    limpieza();

}

void admListados(char dirUsuarios[], char dirProductos[])
{
    int op=0;//validos=0;
    //stProducto aux[300];

    do
    {
        printf("\n\tListados.");
        printf("\n1- Listado de Clientes.");
        printf("\n2- Listado de Productos.");
        printf("\n0- Volver al menu anterior.");
        printf("\nIngrese una opcion: ");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            limpieza();
            muestraArchivo(dirUsuarios);

            break;
        case 2:
            limpieza();
            mostrarProductos(dirProductos);

            // validos=archivoProductosToArreglo(dirProductos, aux); verificar si se rompe el codigo cuando pasamos a un arreglo .
            //  listadoProductos(aux, validos);
            break;
        default:
            printf("\n");
            break;
        }

    }
    while(op!=0);
    limpieza();
}

void listadoProductos(stProducto aux[], int validos)
{
    int i = 0;
    for (i =0; i< validos; i++)
    {
        printf("\n %s\t %.2f\t %d\t %d\n",aux[i].nombre,aux[i].valor,aux[i].stock,aux[i].categoria);
    }
}

int archivoProductosToArreglo(char dirProductos[], stProducto aux[]) /// VALIDOS, PARA PRODUCTOS.
{
    int i=0;
    FILE *archi=fopen(dirProductos,"rb");

    if(archi!=NULL)
    {
        rewind(archi);
        while(fread(&aux[i], sizeof(stProducto), 1, archi)>0)
        {
            i++;
        }
        fclose(archi);
    }
    else
    {
        printf("\nERROR AL ABRIR EL ARCHIVO.");
    }
    return i;
}


void filtrosAdmin(char dirUsuarios[])
{
    int op=0;
    int dim=100, validos=0;
    stUsuario aux[dim];

    do
    {
        printf("\n\tFILTROS PARA CLIENTE\n "); /// DESDE PERFILES ADMIN'S
        printf("\n1 - Mostrar Usuarios Activos.");
        printf("\n2 - Mostrar Usuarios Inactivos.");
        printf("\n3 - Mostrar Usuarios mayores de edad.");
        printf("\n4 - Orden alfabetico, nombres de usuarios.");
        printf("\n- - Porcentaje de generos.");
        printf("\n0 - Volver al menu anterior..");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            limpieza();
            buscaUsuariosPorEstado(dirUsuarios, 1);
            break;
        case 2:
            limpieza();
            buscaUsuariosPorEstado(dirUsuarios, 0);
            break;
        case 3:
            limpieza();
            buscarMayorDeEdad (dirUsuarios);
            break;
        case 4:
            limpieza();
            validos=archivoUsuariosToArreglo(aux, dirUsuarios);
            ordenarUsuariosAlfabeticamente(aux, validos);
            mostrarArregloUsuarios(aux, validos);
            break;
        case 5:
            break;

        default:
            printf("\n");
            break;
        }
    }
    while(op!=0);
    limpieza();

}

void mostrarArregloUsuarios(stUsuario aux[], int cantidad)
{
    int i=0;

    for(i=0; i<cantidad; i++)
    {
        muestraArreglo(aux, i);
    }

}
int archivoUsuariosToArreglo(stUsuario aux[], char dirUsuarios[])
{
    int i=0;
    FILE *archi=fopen(dirUsuarios, "rb");

    if(archi!=NULL)
    {
        while(fread(&aux[i], sizeof(stUsuario), 1, archi)>0)
        {
            i++;
        }
        fclose(archi);
    }
    else
    {
        printf("\nERROR AL ABRIR EL ARCHIVO.");
    }
    return i;
}

void ordenarUsuariosAlfabeticamente(stUsuario A[], int cantidad)
{
    int u=0;
    stUsuario aux;
    while(u<cantidad-1)
    {
        aux=A[u+1];
        insertarUsuarioOrdenado(A, u, aux);
        u++;
    }
}

void insertarUsuarioOrdenado(stUsuario A[], int pos, stUsuario B)
{
    int i=pos;
    while(i>=0 && strcmp(B.nombreUsuario,A[i].nombreUsuario)<0)
    {
        A[i+1]=A[i];
        i--;
    }
    A[i+1]=B;
}

void buscaUsuariosPorEstado(char dirUsuarios[], int dato)
{
    FILE *archi=fopen(dirUsuarios, "rb");
    int i=0, dim=100;
    stUsuario aux[dim];

    if(archi!=NULL)
    {
        fseek(archi, 0, SEEK_SET);
        while(fread(&aux[i], sizeof(stUsuario), 1, archi)>0)
        {
            if(aux[i].activo==dato)
            {
                muestraArreglo(aux, i);
            }

            i++;
        }
        fclose(archi);
    }
    else
        printf("\nERROR AL ABRIR EL ARCHIVO.");
}

void buscarMayorDeEdad (char dirUsuarios [])
{
    int i=0, edad =18, dim=100;
    stUsuario aux[dim];
    FILE * archi = fopen (dirUsuarios, "rb");
    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_SET);

        while (fread(&aux[i], sizeof (stUsuario), 1, archi)>0)
        {
            if (aux[i].edad >= edad)
            {
                muestraArreglo(aux, i);
            }
        }
        fclose(archi);
    }

}

void menuCliente(stUsuario conectado[],char dirUsuarios[], char dirPedidos[], char dirProductos[])
{
    int op=0;
    do
    {
        printf("\n ===============================================================================\n");
        printf("\t\t\t- Hola %s -Bienvenido a HaC Pedidos \n", conectado[0].nombre);
        printf(" -------------------------------------------------------------------------------\n\n");
        printf("\n\t\tMENU.\n");
        printf("\n\t1 - GENERAR PEDIDO."); /// PEDIDOS
        printf("\n\t2 - CONFIGURACION. ");    /// CONFIGURACiON
        printf("\n\t3 - VIP\n");
        printf("\n\t4 - ....\n");
        /*printf("\t5 - DESCRIPCION DE FUNCION A LLAMAR  ----------\n");*/
        printf("\n\t0 - Cerrar sesion. ");
        printf("\nIngrese su opcion:");
        fflush(stdin);
        scanf("%d", &op);
        limpieza();
        switch(op)
        {
        case 1:
            generaPedido(conectado[0], dirPedidos, dirProductos);
            limpieza();
            break;
        case 2:
            configCliente(conectado, dirUsuarios);
            limpieza();
            break;

        case 3:
            infoVip();
            conectado[0]= vVip(conectado);
            printf("\n  %d \n\n", conectado[0].rol);
            break;
        case 4:

            break;
        case 5:
            break;
        default:
            printf("\n");
            break;
        }
    }
    while (op!=0);

    limpieza();
}

void menuInvitado (char dirProductos [])
{
    int op=0;
    printf("\n ===============================================================================\n");
    printf("\t\t\tBienvenido a HaC Pedidos \n");
    printf(" -------------------------------------------------------------------------------\n\n");
    do
    {
        printf("\n\t\tMENU.\n");
        printf("\n\t1 - Catalogo de Productos");
        printf("\n\t2 - Beneficios de Clientes");
        printf("\n\t0 - Cerrar sesion. ");
        printf("\nIngrese su opcion:");
        fflush(stdin);
        scanf("%d", &op);
        limpieza();
        switch(op)
        {
        case 1:
            catalogoInvitado(dirProductos);
            break;
        case 2:
            infoVip();
            break;
        default:
            printf("\n");
            break;

        }
    }
    while (op!=0);

}
void catalogoInvitado (char dirProductos [])
{
    int dim = 150, valProductos =0, dato =0, valCat=0;
    char op='s';
    stProducto aux[dim];
    stProducto arregloCat[dim];
    do
    {
        valProductos=archivoProductosToArreglo(dirProductos, aux);
        dato = cargaDato();
        valCat =arregloDeCategoria(aux, arregloCat, valProductos, dato);

        printf("Desea continuar? s/n ");
        op =getch();
    }
    while (op=='s');
}

///FUNCIONES DE LOS ADMINS
int pedidoAdmin(char dirUsuarios [])
{
    int dato =0, cant = 0;
    cant = cuentaClientesEnArchivo(dirUsuarios);
    dato = opcionEditar(cant);

    return dato;
}
void vaciaArchi(char dirUsuarios[])
{
    FILE *archivo=fopen(dirUsuarios, "w");
    fflush(archivo);
    fclose(archivo);
}

/// INICIOS DE SESION

void ingreso ()
{
    char dirUsuarios[]= {"datos/usuarios.dat"}; /// dir usuarios.dat = Va a contener todos mis usuarios, admins, clientes y clientes vip
    char dirPedidos[]= {"datos/pedidos.dat"};
    char dirProductos[]= {"datos/productos.dat"};

    stUsuario conectado[1];     /// Le pasamos dir pedidos, para manejar el archivo  de pedidos

    int op = 0;
    // stUsuario aux[dim];

    do
    {
        printf("\n ===============================================================\n");
        printf("\t\t\t HaC Pedidos \n");
        printf(" ---------------------------------------------------------------\n\n");
        printf("\n\t1 - Loguearse ");
        printf("\n\t2 - Crear Nueva Cuenta ");
        printf("\n\t3 - Ingresar como invitado: ");
        printf("\n\t0 - Salir. ");
        printf("\n Ingrese su opcion: ");
        fflush(stdin);
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            limpieza();
            conectado[0]= inicioDeSesion(dirUsuarios);
            seleccionRol(conectado,dirUsuarios, dirPedidos, dirProductos);
            // seleccionRol(aux,dirUsuarios,dirPedidos);
            break;
        case 2:
            limpieza();
            cargaCliente(dirUsuarios);
            break;
        case 3:
            limpieza();
            menuInvitado(dirProductos);
            break;
        case 4:
            break;
        default:
            printf("\n ");
            break;
        }
    }
    while (op != 0);
    limpieza();

}

stUsuario inicioDeSesion ( char dirUsuarios [])
{
    stUsuario aux [1];
    stUsuario conectado;
    stUsuario retorno;
    char op=' ';
    int pos=-1;

    while (pos<0 && op!=27)
    {
        printf("Ingrese usuario : ");
        fflush(stdin);
        gets(aux[0].nombreUsuario);
        printf("\nIngrese PIN (6 digitos numericos): ");
        fflush(stdin);
        scanf("%d", &aux[0].pin);
        pos=vUsuarioyPIN(aux, 0, dirUsuarios);
        if ( pos<0)
        {
            limpieza();
            printf("\nDatos incorrectos o inexistentes.\n\nPresione ESC para volver al menu anterior o cualquier tecla para volver a loguearse.\n");
            op=getch();

        }
        if(pos>=0)
        {
            conectado=levantaUsuario(dirUsuarios, pos);  /// RETORNA LA ESTRUCTURA DEL QUE INICIO SESION
            return conectado;
        }
    }
    limpieza();
    return retorno;

}

int vUsuarioyPIN(stUsuario aux[], int pos, char dirUsuarios[]) /// VALIDA Y BUSCA USUARIO Y PIN
{
    FILE *archi=fopen(dirUsuarios, "rb");
    int dim=100, i=0, band=-1;
    stUsuario aux1[dim];

    if(archi!=NULL)
    {
        rewind(archi);
        while(band<0 && fread(&aux1[i], sizeof(stUsuario), 1, archi)>0)   /// La comprobacion antes de que siga leyendo (lo puso el profe )
        {
            if( strcmpi(aux1[i].nombreUsuario,aux[pos].nombreUsuario) == 0 && aux1[i].pin == aux[pos].pin )
            {
                band=i;
            }

            i++;
        }

        fclose(archi);
    }

    return band;
}

stUsuario levantaUsuario(char dirUsuarios [], int pos) ///FUNCION QUE LEVANTA EL USUARIO CONECTADO
{
    FILE * archi= fopen (dirUsuarios, "rb");
    stUsuario aux;

    if (archi != NULL)
    {
        //if ()
        fseek(archi,sizeof(stUsuario)*(pos), SEEK_SET);
        fread(&aux, sizeof(stUsuario), 1, archi);
        fclose(archi);
    }
    return aux;
}
///MODIFICACION/CONFIGURACION CLIENTES
void modCliente(stUsuario aux1, int aux, char dirUsuarios[])
{
    FILE *archi=fopen(dirUsuarios, "r+b");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stUsuario)*(aux-1),SEEK_SET);
        fwrite(&aux1,sizeof(stUsuario),1, archi);
        fclose(archi);
    }

}

stUsuario modUsuarioConectado(stUsuario conectado[], char dirUsuarios[])
{
    int op=0;

    printf("\nMODIFIQUE SU INFORMACION.");
    do
    {
        printf("\n1- MAIL. ");
        printf("\n2- Nombre. ");
        printf("\n3- Apellido. ");
        printf("\n4- Nombre Usuario. ");
        printf("\n5- Genero. ");
        printf("\n0- Volver al menu anterior.");
        printf("\n\t: ");
        fflush(stdin);
        scanf("%i", &op);
        limpieza();
        switch(op)
        {
        case 1:
            cMail(conectado, 1);
            break;
        case 2:
            cNombre(conectado, 1);
            break;
        case 3:
            cApellido(conectado, 1);
            break;
        case 4:
            cNUsuario(conectado, 1, dirUsuarios);
            break;
        case 5:
            cGenero(conectado, 1);
            break;
        default:
            printf("\n");
            break;
        }

    }
    while(op!=0);

    return conectado[1];
}
void configCliente(stUsuario conectado[], char dirUsuarios[])
{
    stUsuario aux1;
    int aux=conectado[0].idUsuario;
    int op=0;

    do
    {
        printf("\n ===============================================================================\n");
        printf("\t\t\tConfiguracion De Usuario: \n");
        printf(" -------------------------------------------------------------------------------\n\n");
        printf("\n\t1 - Darse de BAJA");  /// PREGUNTARLE SI ESTA SEGURO .. $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        printf("\n\t2 - Modificar datos");
        printf("\n\t0 Volver al menu anterior");
        printf("\n\tIngrese su opcion: ");
        fflush(stdin);
        scanf("%i", &op);
        limpieza();
        switch(op)
        {
        case 1:
            aux1=estadoCliente(conectado, 0, 0);
            break;
        case 2:
            aux1=modUsuarioConectado(conectado, dirUsuarios);
            modCliente(aux1, aux, dirUsuarios);
            break;
        }
    }
    while(op!=0);

}
void modUsuario(char dirUsuarios[])
{
    FILE *archi=fopen(dirUsuarios, "r+b");
    int i=0, dim=100, flag =0;
    stUsuario aux[dim];
    stUsuario aux1;

    int dato=pedidoAdmin(dirUsuarios);

    if  (archi!= NULL)
    {
        fseek(archi,0,SEEK_SET);
        while (flag == 0 && fread(&aux[i],sizeof(stUsuario),1,archi)>0)
        {
            if (aux[i].idUsuario == dato)
            {
                limpieza();

                muestraArreglo(aux, i);
                printf("\n");
                aux1= modificaUsuario(aux, i, dirUsuarios);
                flag =1;
            }
            i++;
        }
        fseek(archi,sizeof(stUsuario)*(i-1),SEEK_SET);
        fwrite(&aux1,sizeof(stUsuario),1, archi);
        fclose(archi);
    }
}

stUsuario modificaUsuario(stUsuario aux[], int pos, char dirUsuarios[])
{
    int op=0, estado=0, rol=0;

    printf("\nMODIFICACION DE DATOS.");
    do
    {
        limpieza();
        printf("\n1- ROL: "); /// SOLO ADMIN
        printf("\n2- MAIL: ");
        printf("\n3- Nombre: ");
        printf("\n4- Apellido: ");
        printf("\n5- Nombre Usuario: ");
        printf("\n6- Genero: ");
        printf("\n7- Cambiar estado: ");
        printf("\n0- Volver al menu anterior.");
        printf("\n\t: ");
        scanf("%i", &op);
        switch(op)
        {
        case 1:
            //if()
            printf("\nCambiar a ROL: ");
            scanf("%d", &rol);
            estadoRol(aux, pos, rol);
            break;
        case 2:
            cMail(aux, pos);
            break;
        case 3:
            cNombre(aux, pos);
            break;
        case 4:
            cApellido(aux, pos);
            break;
        case 5:
            cNUsuario(aux, pos, dirUsuarios);
            break;
        case 6:
            cGenero(aux, pos);
            break;

        case 7:
            printf("\nEstado actual: ");
            scanf("%i", &estado);
            estadoCliente(aux, pos, estado);
            break;
        default:
            printf("\n");
            break;
        }


    }
    while(op!=0);

    return aux[pos];
}


/// Validaciones de datos
int vMail(stUsuario aux[], int pos)  ///valida mail
{
    int band=0;
    char *arroba = strchr(aux[pos].mail, '@');

    if(arroba!=NULL)
    {
        char *punto= strchr(arroba,'.');

        if(punto!=NULL)
            band=1;
    }

    return band;
}

int vNUsuario(stUsuario aux[], int pos, char dirUsuarios[])
{
    FILE *archi=fopen(dirUsuarios, "rb");
    int dim=100, i=0, band=0;
    stUsuario aux1[dim];
    fseek(archi,0, SEEK_SET);
    if(archi!=NULL)
    {
        while(band==0 && fread(&aux1[i], sizeof(stUsuario), 1, archi)>0)   /// La comprobacion antes de que siga leyendo (lo puso el profe )
        {
            if(strcmpi(aux1[i].nombreUsuario,aux[pos].nombreUsuario) == 0)  /// comparo cadenas de strings
            {
                band=1;
            }
        }
        fclose(archi);
    }
    return band;
}

/// CARGA DE DATOS
void cargaCliente(char dirUsuarios[])
{
    int dim=100;
    stUsuario aux[dim];
    char letra ='s';
    int i=0, j=0;
    while (letra =='s')
    {
        puts("\n------------------------------------");
        i= cuentaClientesEnArchivo(dirUsuarios);
        i++;
        aux[j].idUsuario= i;   /// 04/06 Por ahora no se rompio ...
        printf("\n ID %d \n\n", aux[j].idUsuario);
        cMail(aux, j);
        cNombre(aux, j);
        cApellido(aux, j);
        cNUsuario(aux, j, dirUsuarios);
        cPin(aux, j);
        cGenero(aux, j);
        cEdad(aux,j);
        estadoCliente(aux, j, 0); ///  SERIA PARA CLIENTES QUE EMPIEZAN, INACTIVOS POR DEFAULT
        estadoRol(aux, j, 1);   /// 1 ES EL ESTADO PARA CIENTES NORMALES
        puts("\n-------------------------------------");
        arregloToArchi(dirUsuarios, aux, j);
        j++;
        printf("\nDesea Continuar? S/N: ");
        fflush(stdin);
        scanf("%c",&letra);
    }
}

int cuentaClientesEnArchivo(char dirUsuarios[])  /// CUENTA CANTIDAD DE CLIENTES
{
    //stUsuario alumno;
    int cantidad=0;
    FILE *archi;
    archi= fopen(dirUsuarios, "rb");
    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        cantidad = ftell(archi)/ sizeof (stUsuario);
        fclose(archi);
    }
    return cantidad;
}

void cMail(stUsuario aux[], int pos)
{
    int band=0;
    do
    {
        printf("\nIngrese su Correo Electronico:");
        fflush(stdin);
        scanf("%s",aux[pos].mail);
        band=vMail(aux, pos);
        if(band==0)
            printf("\nMail no valido.Ingrese uno correcto");

    }
    while(band==0);
}

void cNombre(stUsuario aux[], int pos)
{
    printf("\nIngrese su Nombre: ");
    fflush(stdin);
    scanf("%s",aux[pos].nombre);
}

void cApellido(stUsuario aux[], int pos)
{
    printf("\nIngrese su Apellido: ");
    fflush(stdin);
    scanf("%s", aux[pos].apellido);
}

void cNUsuario(stUsuario aux[], int pos, char dirUsuarios[]) // Carga Nombre de Usuario
{
    int band=0;
    do
    {
        printf("\nIngrese nombre de usuario: ");
        fflush(stdin);
        scanf("%s",aux[pos].nombreUsuario);
        band=vNUsuario(aux, pos, dirUsuarios);

        if(band==1)
            printf("\nNombre de usuario existente, para registrarse elija un nombre diferente.. ");
    }
    while(band==1);
}

void cPin(stUsuario aux[], int pos)
{
    printf("\nIngrese PIN (6 digitos numericos): ");
    scanf("%i", &aux[pos].pin);

    while(aux[pos].pin < 99999 || aux[pos].pin >999999)  ///valida pin
    {
        if(aux[pos].pin < 99999 || aux[pos].pin >999999)
            printf("\nLimitese a la cantidad de 6 digitos\n");
        printf("\nIngrese PIN :");
        fflush(stdin);
        scanf("%i", &aux[pos].pin);
    }
}

void cGenero(stUsuario aux[], int pos)
{
    printf("\nGenero: ");
    fflush(stdin);
    scanf("%c", &aux[pos].genero);
}

void cEdad (stUsuario aux [], int pos)
{
    printf("\nEdad: ");
    scanf("%d", &aux[pos].edad);
}

stUsuario estadoCliente(stUsuario aux[], int pos, int estado)
{
    char op='s';
    printf("Estas segurx %s ? s/n \n", aux[pos].nombre);
    op=getch();
    if (op=='s')
    {
        if(estado==0 || estado==1)
        {
            aux[pos].activo = estado;

            if(estado==0)
                printf("\nUsuario INACTIVO. Comuniquese con un ADMIN.\n");
            else
                printf("\nUsuario ACTIVO.\n");
        }
        else
            printf("\nESTADO NO VALIDO.\n");
    }
    limpieza();
    return aux[pos];

}

stUsuario estadoRol(stUsuario aux[], int pos, int estado)
{
    if(estado==0 || estado==1 || estado==2 || estado==3)
        aux[pos].rol=estado;
    else
        printf("\nROL NO VALIDO.");

    return aux[pos];
}
void cPinVipAdmin(stUsuario aux[], int pos)
{
    printf("\nIngrese PIN (4 digitos numericos): ");
    scanf("%d", &aux[pos].pin);

    while(aux[pos].pin < 999 || aux[pos].pin >9999)  ///valida pin
    {
        if(aux[pos].pin < 999 || aux[pos].pin >9999)
            printf("\nLimitese a la cantidad de 4 digitos\n");
        printf("\nIngrese PIN :");
        fflush(stdin);
        scanf("%i", &aux[pos].pin);
    }
}
/// ALGO TO ARCHI'S
void arregloToArchi(char dirUsuarios[], stUsuario aux[], int pos)
{
    FILE *archi=fopen(dirUsuarios,"a+b");

    if (archi!=NULL)
    {
        fwrite(&aux[pos],sizeof(stUsuario),1,archi);

        fclose(archi);
    }
}

///MOSTRADORES
void muestraArchivo(char dirUsuarios[])
{
    FILE *archi=fopen(dirUsuarios, "rb");
    int i=0, dim=100;
    stUsuario aux[dim];

    if(archi!=NULL)
    {
        fseek(archi, 0,SEEK_SET);
        while(fread(&aux[i], sizeof(stUsuario), 1, archi)>0)
        {
            muestraArreglo(aux, i);
            i++;
        }

        fclose(archi);
    }
    else
        printf("\nERROR AL ABRIR EL ARCHIVO!.");

}

void muestraArreglo(stUsuario aux[], int pos)
{
    mIdCliente(aux, pos);
    mRol(aux, pos);
    mMail(aux, pos);
    mNombre(aux, pos);
    mApellido(aux, pos);
    mNUsuario(aux, pos);
    mPin(aux, pos);
    mEdad(aux, pos);
    mGenero(aux, pos);
    mEstado(aux, pos);
    printf("\n");

}
void mIdCliente(stUsuario aux[], int pos)
{
    printf("\nID: %d ", aux[pos].idUsuario);
}
void mRol(stUsuario aux[], int pos)
{
    int aux1=0;
    aux1=aux[pos].rol;

    if(aux1==0)
        printf("\nADMIN.");
    else  if(aux1==1)
        printf("\nCliente.");
    else  if(aux1==2)
        printf("\nInvitado.");
    else  if(aux1==3)
        printf("\nClienteVIP");

}
void mMail(stUsuario aux[], int pos)
{
    printf("\nMail: %s ", aux[pos].mail);
}
void mNombre(stUsuario aux[], int pos)
{
    printf("\nNombre: %s ", aux[pos].nombre);
}
void mApellido(stUsuario aux[], int pos)
{
    printf("\nApellido: %s ", aux[pos].apellido);
}
void mNUsuario(stUsuario aux[], int pos)
{
    printf("\nNombre Usuario: %s ", aux[pos].nombreUsuario);
}
void mPin(stUsuario aux[], int pos)
{
    printf("\nPIN: %i ", aux[pos].pin);
}
void mEdad(stUsuario aux[], int pos)
{
    printf("\nEdad: %d ", aux[pos].edad);
}
void mGenero(stUsuario aux[], int pos)
{
    printf("\nGenero: %c ", aux[pos].genero);
}
void mEstado(stUsuario aux[], int pos)
{
    printf("\nEstado: %i ", aux[pos].activo);
}

///     ############        FUNCIONES DE PEDIDOS Y PRODUCTOS    ##############

/// PEDIDOS

void generaPedido(stUsuario conectado, char dirPedidos[], char dirProductos[])
{
    int op1=0;
    stPedido aux;
    aux.valChango=0;
    do
    {
        limpieza();
        printf("\n1- Cargar Chango.");
        printf("\n2- Mostrar Chango.");
        printf("\n3- Modificar Chango");
        printf("\n4- Cancelar Chango");
        printf("\n5- Finalizar Compra");
        printf("\n0- Volver al menu anterior");
        printf("\nIngrese opcion: ");
        scanf("%d", &op1);

        switch(op1)
        {
        case 1:
            limpieza();
            aux=cargaPedido(dirPedidos, dirProductos,conectado,aux);
            break;
        case 2:
            limpieza();
            mostrarArregloChango(aux);
            break;
        case 3:
            limpieza();
            mostrarArregloChango(aux);
            aux=modChango(aux);
            break;
        case 4:
            aux=bajaChango(aux,0);
            break;
        case 5:
            pedidoToArchi(dirPedidos, aux);
            printf("\nEl local esta preparando su pedido.\nLo recibira en su domicilio a la hora estimada.."); /// VER SI PODEMOS PONERLE EL HORARIO EN QUE LLEGHUE
            limpieza();
            op1=0;
            break;
        default:
            printf("\n");
            break;

        }
    }
    while(op1!=0);

    // mostrarArchivoPedidos(dirPedidos, k);

}

stPedido cargaPedido(char dirPedidos[], char dirProductos[], stUsuario conectado, stPedido aux)
{
    int valProductos=0, dim=150, valCat=0, k=0, var=0;
    int dato=0, dato1=0;
    char op='s';
    float total=0;
    stProducto arregloP[dim];
    stProducto arregloCat[dim];

    aux.idPedido= cuentaPedidosEnArchivo(dirPedidos)+1;
    aux.idUsuario=conectado.idUsuario;
    aux=diaYHora(aux);
    // printf("\nFecha:  %s ", aux.fecha);
    valProductos=archivoProductosToArreglo(dirProductos, arregloP); /// Carga archivo de productos al arreglo

    var=aux.valChango;

    do
    {
        muestraListadoGeneral();
        dato=cargaDato();
        // op=getch();
        valCat=arregloDeCategoria(arregloP, arregloCat, valProductos, dato);/// USUARIO INGRESA OPCION DE CATEGORIA
        /// ···································· TAREA PARA CASA:  CASE MENU PARA USUARIO "AGREGAR PRODUCTO" "CANCELAR PRODUCTO" "FINALIAR COMPRA"
        /// hacerle acordar del cambio de tipo de dato en st pedido

        dato1=cargaDato();/// Carga en dato el producto que selecciono el usuario
        dato1--; /// para que el usuario ingrese la opcion 1, y obtengamos la posicion del arreglo 0
        aux= cargaArregloChango(aux, arregloCat, valCat,dato1, k); /// USUARIO INGRESA EL PRODUCTO SELECCIONADO  val chango
        k++;
        printf("\nDesea continuar: s/n");
        op=getch();
        limpieza();

    }
    while(dato>0 && dato<9 && op!=27 && op=='s');

    aux.valChango=k+var;

    for(int j=0; j<k; j++)
    {
        total+=aux.chango[j].valor; ///suma el total del changuito seleccionado
    }

    aux.costo=total;


    return aux;

}

stPedido bajaChango(stPedido aux, char estado)///CANCELAR CHANGO
{
    if(estado=='s' || estado=='n')///s(1) activo, n anulado(0)
    {


        if(estado=='s')
        {
            aux.pedidoAnulado = 1;
            printf("\nEl pedido fue anulado.\n");
        }
        else
            printf("\nPedido sigue activo.\n");

    }
    else
        printf("\nPEDIDO NO VALIDO.\n");

    return aux;
}

stPedido modChango (stPedido aux)
{
    int dato=0,i = 0;
    char op='s';

    do
    {
        printf("\nQue producto desea quitar? \n");
        scanf("%d",&dato);
        dato--;
        if (dato > aux.valChango || dato<0)
        {
            printf("El producto no existe\n\n");
        }
        else
        {
            for (i=dato; i<aux.valChango; i++)
            {
                aux.chango[i]=aux.chango[i+1];
            }
            aux.valChango=aux.valChango -1;
        }
        printf("Desea continuar quitando productos? Presione s/n: \n");
        fflush(stdin);
        op=getch();
    }
    while(op == 's' && dato >= aux.valChango);


    return aux;
}

void pedidoToArchi(char dirPedidos[], stPedido aux )
{
    FILE *archi= fopen(dirPedidos, "ab");

    if(archi!=NULL)
    {
        fwrite(&aux, sizeof(stPedido), 1, archi);

        fclose(archi);
    }
}

int cuentaPedidosEnArchivo(char dirPedidos[])  /// CUENTA CANTIDAD DE PEDIDOS
{
    //stUsuario alumno;
    int cantidad=0;
    FILE *archi;
    archi= fopen(dirPedidos, "rb");
    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        cantidad = ftell(archi)/ sizeof (stPedido);
        fclose(archi);
    }

    return cantidad;
}

stPedido diaYHora(stPedido aux)
{
    time_t t=time(NULL);
    struct tm fechahora = *localtime(&t); ///el lugar en donde ponemos la fecha y hora
    char fechayhora[100];
    char *formato;
    formato = "%d/%m/%Y %H:%M:%S";///formato
    strftime(fechayhora, sizeof fechayhora,formato,&fechahora);
    //printf ("Hoy es: %s\n", fechayhora);

    strcpy(aux.fecha,fechayhora);

    return aux;
}

///PRODUCTOS
///Carga de productos
void cargaProducto(char dirProductos[])
{
    int i = 0, dim = 100;
    char op='s';
    stProducto aux [dim];
    while (op=='s')
    {

        aux[i].idProducto= cuentaProductosEnArchivo(dirProductos) + 1 ;
        printf("\nID Producto: %d \n", aux[i].idProducto);

        cNombreProducto(aux,i);

        cValor(aux, i);

        cStock(aux, i);

        cCategoria(aux,i);
        productoToarchi(dirProductos,aux,i);

        printf("Desea Continuar S/N");
        fflush(stdin);
        scanf("%c",&op);

    }
}
int cuentaProductosEnArchivo(char dirProductos[])
{
    FILE *archi=fopen(dirProductos, "rb");

    int cant=0;

    if(archi!=NULL)
    {
        fseek(archi, 0, SEEK_END);
        cant= ftell(archi)/ sizeof(stProducto);

        fclose(archi);
    }

    return cant;
}

/// MOSTRADORES
stPedido cargaArregloChango( stPedido aux, stProducto arregloCat[], int validos,int dato, int k)
{
    if(dato>= 0 && dato<=validos)
    {
        aux.chango[k]=arregloCat[dato];
    }
    else
        printf("\nProducto ingresado no es valido, limitese desde 1 a %d .", validos);

    return aux;
}

int arregloDeCategoria(stProducto aux[], stProducto aux1[], int validos, int dato)
{
    int i=0, cont=0;

    if(dato<9) /// (Para agregar mas categoria llame al admin ..) -> 8 CATEGORIAS !!
    {
        for(i=0; i<validos; i++)
        {
            if(aux[i].categoria==dato)
            {
                aux1[cont]= aux[i];
                cont++;
                mostrarProducto(aux[i], cont);
            }
        }
    }

    return cont;
}

void mostrarProductos(char dirProductos[])
{
    int i=0, cont=0, dim=150;
    stProducto aux[dim];

    cont=archivoProductosToArreglo(dirProductos, aux);

    for(i=0; i<cont; i++)
    {
        mostrarProducto(aux[i], i+1);
    }
    printf("\n");
    limpieza();

}

void mostrarArchivoPedidos(char dirPedidos[], int cant)
{
    FILE * archi= fopen(dirPedidos, "rb");
    int dim=150, i=0;
    stPedido aux[dim];
    stProducto chango1[dim];
    if(archi!=NULL)
    {
        while(fread(&aux[i], sizeof(stPedido), 1, archi)>0)
        {
            printf("\nId Pedido: %d ", aux[i].idPedido);
            printf("\nId Cliente: %d ", aux[i].idUsuario);
            printf("\nFecha: %s ", aux[i].fecha);
            printf("\nChango: \n");

            for(int j=0; j<cant; j++)
            {
                chango1[j]=aux[i].chango[j];
                mostrarProducto(chango1[j], j+1);
            }
            printf("\nCosto total del chango: %.2f ", aux[i].costo);

            i++;
        }

        fclose(archi);
    }

}

void mostrarArregloChango (stPedido aux)
{
    for( int i=0; i<aux.valChango; i++)
    {
        printf("|%c %d %s  \t $ %.2f  \t ",175,i+1, aux.chango[i].nombre, aux.chango[i].valor);

        if(i % 2 == 0)
        {
            printf("\n\n");
        }
    }

}

void mostrarProducto (stProducto aux, int cont )
{
    printf("|%c %d %s  \t $ %.2f  \t ",175,cont, aux.nombre, aux.valor);

    if(cont % 2 == 0)
    {
        printf("\n\n");
    }
}

void admMostrarProducto (stProducto aux, int cont )
{
    printf("|%c %d %s  \t $ %.2f  \t %d ",175,  cont, aux.nombre, aux.valor, aux.stock);
}

/// PRODUCTOS TO ARCHi
void productoToarchi(char dirProductos[], stProducto aux[], int pos)
{
    FILE * archi =fopen(dirProductos, "ab");
    if (archi!= NULL)
    {
        fwrite(&aux[pos],sizeof(stProducto),1,archi);
        fclose(archi);
    }
}
void cNombreProducto (stProducto aux [], int pos)
{
    printf(" Nombre de producto: ");
    fflush(stdin);
    gets(aux[pos].nombre);
}
void cValor (stProducto aux [], int pos)
{
    printf("\nValor: ");
    scanf("%f",&aux[pos].valor);
}

void cStock (stProducto aux [], int pos)
{
    printf(" \nStock disponible: ");
    scanf("%d",&aux[pos].stock);
}

void cCategoria (stProducto aux[], int pos)
{
    printf("\n Categoria: ");
    scanf("%d", &aux[pos].categoria);
}

int cargaDato()
{
    int num=0;
    printf("\n %c> ",(192));
    scanf("%d", &num);
    return num;
}
void modProductos (char dirProducto [], stProducto aux, int aux1)
{
    FILE * archi = fopen(dirProducto,"rb");

    if (archi != NULL)
    {
        fseek(archi, sizeof(stProducto)* (aux1-1),SEEK_SET);
        fwrite(&aux, sizeof (stProducto),1,archi);
        fclose(archi);
    }
}
void modificacionProductoToArchi(char dirProductos[])
{
    FILE *archi=fopen(dirProductos, "r+b");
    int i=0, dim=100, flag =0;
    stProducto aux[dim];
    stProducto aux1;

    int dato=idProductoEditar(dirProductos);

    if  (archi!= NULL)
    {
        fseek(archi,0,SEEK_SET);
        while (flag == 0 && fread(&aux[i],sizeof(stProducto),1,archi)>0)
        {
            if (aux[i].idProducto == dato)
            {
                admMostrarProducto(aux[i],1);
                limpieza();
                aux1= modificaProducto(aux, i, dirProductos);
                flag =1;
            }
            i++;
        }

        fseek(archi,sizeof(stProducto)*(i-1),SEEK_SET);
        fwrite(&aux1,sizeof(stProducto),1, archi);
        fclose(archi);
    }
}
int idProductoEditar(char dirProductos[])
{
    int dato =0, cant = 0;
    cant = cuentaProductosEnArchivo(dirProductos);
    dato = opcionEditar(cant);
    return dato;
}

int opcionEditar (int cantidad)
{
    int dato = 0;
    do
    {
        printf("\nID: ");
        scanf("%d",&dato);
        if (dato > cantidad)
        {
            printf("\nIngrese ID valido:  ");
            fflush(stdin);
            scanf("%d",&dato);
        }
    }
    while (dato > cantidad);

    return dato;
}
stProducto modificaProducto(stProducto aux[], int pos, char dirProductos[])
{
    int op=0;
    //mostrarProducto(aux[pos]);
    do
    {
        printf("\n ===============================================================================\n");
        printf("\t\t\tMODIFICACION DE DATOS\n");
        printf(" -------------------------------------------------------------------------------\n\n");
        printf("\n1- Nombre: "); /// SOLO ADMIN
        printf("\n2- Valor: ");
        printf("\n3- Stock: ");
        printf("\n0- Volver al menu anterior.");
        printf("\n\t: ");
        scanf("%i", &op);
        switch(op)
        {
        case 1:
            cNombreProducto(aux, pos);
            break;
        case 2:
            cValor(aux,pos);
            break;
        case 3:
            cStock(aux,pos);
            break;
        default:
            printf("\n");
            break;
        }
    }
    while(op!=0);

    return aux[pos];
}

void admMenuModificador (char dirUsuarios[], char dirProductos []) ///hay que cambiar los printf
{
    int op =0;
    do
    {
        limpieza();
        printf("\n\tQue desea modificar?\n");
        printf("\n\t1 - Clientes ");
        printf("\n\t2 - Productos ");
        printf("\n\t0 - Menu anterior.. ");
        printf("\nIngrese su Opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            limpieza();
            modUsuario(dirUsuarios);

            break;
        case 2:
            limpieza();
            modificacionProductoToArchi(dirProductos);
            break;
        default:
            printf("\n");
            break;
        }
    }
    while (op!=0);
}

void muestraListadoGeneral()
{
    printf("\n ===============================================================================\n");
    printf("\t\t\tINGRESE UNA CATEGORIA: \n");
    printf(" -------------------------------------------------------------------------------\n\n");
    printf("|1 Panificados| \t |2 Bebidas Sin alcohol| \t |3 Bebidas con Alcohol|\n\n");
    printf("|4 Lacteos|\t |5 Carnes| \t\t |6 Verduleria|\n\n");
    printf("\t|7 Bazar| \t\t |8 Almacen|\t\n");
    printf("\n ===============================================================================\n\n");
}

void infoVip ()
{
    puts("\n\t==========================================================");
    puts("\n\t|             INFO V.I.P de HaC Pedidos.                  |");
    puts("\n\t----------------------------------------------------------");
    puts("\n\t| Al Convertirse en VIP Usted Tendra:                     |");
    puts("\n\t| Descuento de un 15% en el total de sus Compras.         |");
    puts("\n\t| Va a participar de un Sorteo de un TV 50''.             |");
    puts("\n\t| Suma Chances para un Viaje a Qatar 2022  .              |");
    puts("\n\t|                                                         |");
    puts("\n\t| Usted obtendra un codigo UNICO para darse de alta       |");
    puts("\n\t| le llegara un codigo a su correo electronico            |");
    puts("\n\t==========================================================\n");
}

void limpieza()
{
    printf("\n\nPresione una tecla para continuar..\n");
    getch();
    system("cls");
}

stUsuario vVip (stUsuario conectado[])
{
    int valor=0, aux=3;
    printf("Ingresar Codigo VIP: \n");
    scanf("%d",&valor);
    if (valor == 6422)
    {
        printf("Felicidades por su Membresia!! \nCierre sesion para aprovechar sus beneficios !\n\n");
        conectado[0].rol = aux;
        limpieza();
    }else { printf("\nCodigo incorrecto. Hasta luego.");
    }

    return conectado[0];
}

/*
void menuMuestraListado()
{
   // stProducto aux;
    int op=0;
    muestraListadoGeneral();
    op=cargaDato();

    do
    {
        switch (op)
        {

        case 1:
            printf("Panificados");
            break;
        case 2:
            break;
        default:
            printf("\n");
            break;

        }
    }
    while (op !=0);
}
*/
/*
int validacionDatos(char dirUsuarios[])
{
    stUsuario aux;
    FILE * archi;
    int i=0;
    int flag=0;
    int j;

    archi =fopen(dirUsuarios,"ab");

    fread(&aux,sizeof(stUsuario),1,archi)>0;

    while(i<strlen(aux.nombreUsuario) && flag==0) ///
    {
        j=isalpha(dirUsuarios[i]);  /// ****** un sub indice en direccion de un dir
        if (j !=0)
        {
            i++;
        }
        else
        {
            puts("Error el nombre ya esta ingresado.. Pruebe con otro por favor \n\n");
            flag = 1 ;
        }

    }
    fclose(archi);
    return flag;
}
///
*/
/// OCULTA EL CARACTER Y PONE ASTERISCOS **

/*
                        while(caracter=getch())
                        {
                            if (caracter==13) // 13 enter en ascii
                            {
                                break;
                            }
                            else if (caracter==8) // borrado hacia la izquierda
                            {
                                if(i >0) // ... (Tiempo restante: 1 KB)
*/
