#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h> /// ASTERISCO
#include <locale.h>  /// ASTERISCO
#include <conio.h>
#include <time.h>

typedef struct
{
    int idCliente;                 // auto incremental
    int rol;    /// 0=ADMIN  1=CLIENTE  2=INVITADO  3=CLIENTE VIP
    char mail[30];  ///Comento los otros datos, para agilizar la carga
    char nombre[30];
    char apellido[30];
    char nombreUsuario[20];   /// cambie de userName a nombreUsuario
    unsigned int pin;     /// PIN, CONTRASE?A SOLO CON NUMEROS, VALIDACION EN FUNCIONES
    char genero;
    int activo; // indica 1 o 0 si el cliente est? activo
    unsigned  int edad;
} stUsuario;        /// Cambio de nombre de stCliente a stUsuario !!

typedef struct
{
    int idProducto;
    char nombre[30];
    float valor;
    int stock;
    int categoria; ///1 panes, 2 bebidas, 3 bebidas con alcohol(+18), 4 lacteos, 5 carnes, 6 verdu, 7 bazar, 8 almacen.
} stProducto;

typedef struct
{
    int idPedido;        // auto incremental
    int idCliente;       // este valor corresponde al id del cliente que realiz? el pedido
    char fecha[20];      // dd/MM/aaaa
    stProducto chango[100];
    int valChango;
    float costo;
    int pedidoAnulado;    // indica 1 o 0 si el pedido fue anulado o no

} stPedido;
/// ##############      FUNCIONES DE ADMINS / USUARIOS      ####################

///MENU'S
void seleccionRol(stUsuario conectado[], char dirClientes[], char dirPedidos[], char dirProductos[]);
void menuAdmin(char dirClientes[], char dirPedidos[], char dirProductos[]);
void menuCliente(stUsuario conectado[], char dirClientes[], char dirPedidos[], char dirProductos[]);

/// INICIOS DE SESION
void ingreso (); /// ABUELO
stUsuario inicioDeSesion ( char dirClientes []);
int vUsuarioyPIN(stUsuario aux[], int pos, char dirClientes[]);
stUsuario levantaUsuario (char dirClientes [], int pos);  ///FUNCION QUE LEVANTA EL USUARIO CONECTADO

///FUNCIONES DE LOS ADMINS
int pedidoAdmin (char dirClientes []);
///void altaClienteAdmin (char dirClientes[]); /// ??????QUE HACE ESTE PROTOTIPADO ??????????????
void vaciaArchi(char dirClientes[]);
int opcionEditar (int cantidad);
void admMenuModificador (char dirClientes[], char dirProductos []); ///modifica todo acomoden xD

/// FILTROS DE ADMINS

void filtrosAdmin(char dirClientes[]);  /// PADRE
void buscaUsuariosPorEstado(char dirClientes[], int dato);
void ordenarUsuariosAlfabeticamente(stUsuario A[], int cantidad);
void insertarUsuarioOrdenado(stUsuario A[], int pos, stUsuario B);
void buscarMayorDeEdad (char dirClientes []);
void admListados(char dirClientes[], char dirProductos[]);

///MODIFICACION/CONFIGURACION CLIENTES
void modCliente(stUsuario aux1, int aux, char dirClientes[]);
stUsuario modUsuarioConectado(stUsuario conectado[], char dirClientes[]);
void configCliente(stUsuario conectado[], char dirClientes[]);
void modUsuario(char dirClientes[]);
stUsuario modificaUsuario(stUsuario aux[], int pos, char dirClientes[]);

/// Validaciones de datos
int vMail(stUsuario aux[], int pos);
int vNUsuario(stUsuario aux[], int pos, char dirClientes[]);

/// CARGA DE DATOS
void cargaCliente(char nombreArchivo[]);
int cuentaClientesEnArchivo(char dirClientes[]);
void cMail(stUsuario aux[], int pos);
void cNombre(stUsuario aux[], int pos);
void cApellido(stUsuario aux[], int pos);
void cNUsuario(stUsuario aux[], int pos, char dirClientes[]);
void cPin(stUsuario aux[], int pos);
void cGenero(stUsuario aux[], int pos);
void cEdad (stUsuario aux [], int pos);
stUsuario estadoCliente(stUsuario aux[], int pos, int estado);
stUsuario estadoRol(stUsuario aux[], int pos, int estado);


/// ALGO TO ARCHI'S
void arregloToArchi(char dirClientes[], stUsuario aux[], int pos);

/// ARCHI TO ARREGLO
int archivoUsuariosToArreglo(stUsuario aux[], char dirClientes[]);

///MOSTRADORES
void muestraArchivo(char dirClientes[]);
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
int cuentaPedidosEnArchivo(char dirPedidos[]);
stPedido diaYHora(stPedido aux);

stPedido cargaArregloChango( stPedido aux, stProducto arregloCat[], int validos,int dato, int k);
int arregloDeCategoria(stProducto aux[], stProducto aux1[], int validos, int dato);

stPedido bajaChango(stPedido aux, char estado);
stPedido modChango (stPedido aux);
void mostrarChango (stPedido aux);
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

int main()
{
    //char activo[]= {"clienteA.dat"};
    //char dirClientes[]= {"usuarios.dat"}; /// dir usuarios.dat = Va a contener todos mis usuarios, admins, clientes y clientes vip
    //char dirPedidos[]= {"pedidos.dat"};
    system("color F0"); /// Se declaran con hexadecimales  del 0 a la F (del 0 al 15)
    //stUsuario conectado[1];
    //conectado[1]= inicioDeSesion(dirClientes);
    //seleccionRol(conectado,dirClientes, dirPedidos);  /// Le pasamos dir pedidos, para manejar el archivo  de pedidos
    ingreso();


    return 0;
}

/// ##############      FUNCIONES DE ADMINS / USUARIOS      ####################

///MENU'S
void seleccionRol(stUsuario conectado[],char dirClientes[], char dirPedidos[], char dirProductos[])
{

    if(conectado[0].rol==0)
    {
        menuAdmin(dirClientes, dirPedidos, dirProductos);
    }
    else
    {
        if(conectado[0].rol==1)
        {
            menuCliente(conectado,dirClientes, dirPedidos, dirProductos);    /// Menu Cliente recibe por parametro, y la direccicon de los pedidos
        }

    }

    /*if(rol==2)
    if(rol==3)*/

}

void menuAdmin(char dirClientes[], char dirPedidos[], char dirProductos[])
{
    //char dirAdmins []= {"admins.dat"}; /// EN CONSTRUCCION
    //char dirClientes[]= {"datos/usuarios.dat"}; /// dir usuarios.dat = Va a contener todos mis usuarios, admins, clientes y clientes vip
    //char dirProductos[]= {"datos/productos.dat"};
    int op=0;
    do
    {
        printf("\n\n\tMENU ADMINISTRADORES.\n\n");
        printf("\n1 - CARGA DE CLIENTES  ");
        printf("\n2 - Filtros. ");
        printf("\n3 - Modificaciones. ");
        printf("\n4 - Carga productos.");
        printf("\n5 - Listados Completos.");
        printf("\n99 - VACIA EL ARCHIVO (**OJO**).");
        /*printf("5 - DESCRIPCION DE FUNCION A LLAMAR  ----------\n");*/
        printf("\n0 - Cerrar sesion.. ");
        printf("\nIngrese su opcion: ");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            cargaCliente(dirClientes);
            break;
        case 2:
            filtrosAdmin(dirClientes);
            // muestraArchivo(dirClientes);
            break;
        case 3:
            admMenuModificador (dirClientes, dirProductos);
            break;
        case 4:
            cargaProducto(dirProductos);
            break;
        case 5:
            admListados(dirClientes, dirProductos);
            break;
        case 6:
            //modProductos(dirProductos,);
            break;
        case 99:
            vaciaArchi(dirClientes);
            break;
        default:
            printf("\n");
            break;
        }
    }
    while (op!=0);

}

void admListados(char dirClientes[], char dirProductos[])
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
            muestraArchivo(dirClientes);
            break;
        case 2:
            //mostrarProductos(dirProductos);
            // validos=archivoProductosToArreglo(dirProductos, aux); verificar si se rompe el codigo cuando pasamos a un arreglo .
            //  listadoProductos(aux, validos);
            break;
        default:
            printf("\n");
            break;
        }

    }
    while(op!=0);
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


void filtrosAdmin(char dirClientes[])
{
    int op=0;
    int dim=100, validos=0;
    stUsuario aux[dim];

    do
    {
        printf("\n\tFILTROS PARA CLIENTE "); /// DESDE PERFILES ADMIN'S
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
            buscaUsuariosPorEstado(dirClientes, 1);
            break;
        case 2:
            buscaUsuariosPorEstado(dirClientes, 0);
            break;
        case 3:
            buscarMayorDeEdad (dirClientes);
            break;
        case 4:
            validos=archivoUsuariosToArreglo(aux, dirClientes);
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

}

void mostrarArregloUsuarios(stUsuario aux[], int cantidad)
{
    int i=0;

    for(i=0; i<cantidad; i++)
    {
        muestraArreglo(aux, i);
    }

}
int archivoUsuariosToArreglo(stUsuario aux[], char dirClientes[])
{
    int i=0;
    FILE *archi=fopen(dirClientes, "rb");

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

void buscaUsuariosPorEstado(char dirClientes[], int dato)
{
    FILE *archi=fopen(dirClientes, "rb");
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

void buscarMayorDeEdad (char dirClientes [])
{
    int i=0, edad =18, dim=100;
    stUsuario aux[dim];
    FILE * archi = fopen (dirClientes, "rb");
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

void menuCliente(stUsuario conectado[],char dirClientes[], char dirPedidos[], char dirProductos[])
{
    int op=0;
    do
    {
        printf("\n\tMENU.\n");
        printf("\n1 - GENERAR PEDIDO."); /// PEDIDOS
        printf("\n2 - CONFIGURACION. ");    /// CONFIGURACiON
        printf("\n3 - ....\n");
        printf("\n4 - ....\n");
        /*printf("5 - DESCRIPCION DE FUNCION A LLAMAR  ----------\n");*/
        printf("\n0 - Cerrar sesion. ");
        printf("\nIngrese su opcion:");
        fflush(stdin);
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            generaPedido(conectado[0], dirPedidos, dirProductos);
            break;
        case 2:
            configCliente(conectado, dirClientes);
            break;
        case 3:
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
}



///FUNCIONES DE LOS ADMINS
int pedidoAdmin(char dirClientes [])
{
    int dato =0, cant = 0;
    cant = cuentaClientesEnArchivo(dirClientes);
    dato = opcionEditar(cant);

    return dato;
}
void vaciaArchi(char dirClientes[])
{
    FILE *archivo=fopen(dirClientes, "w");
    fflush(archivo);
    fclose(archivo);
}

/// INICIOS DE SESION

void ingreso ()
{
    char dirClientes[]= {"datos/usuarios.dat"}; /// dir usuarios.dat = Va a contener todos mis usuarios, admins, clientes y clientes vip
    char dirPedidos[]= {"datos/pedidos.dat"};
    char dirProductos[]= {"datos/productos.dat"};

    stUsuario conectado[1];
    /// Le pasamos dir pedidos, para manejar el archivo  de pedidos

    int op = 0;
    // stUsuario aux[dim];

    do
    {
        printf("\n1 - Loguearse ");
        printf("\n2 - Crear Nueva Cuenta ");
        //printf("\n3 - Ingresar como invitado: ");
        printf("\n0 - Salir. ");
        printf("\n Ingrese su opcion: ");
        fflush(stdin);
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            conectado[0]= inicioDeSesion(dirClientes);
            seleccionRol(conectado,dirClientes, dirPedidos, dirProductos);
            // seleccionRol(aux,dirClientes,dirPedidos);
            break;
        case 2:
            cargaCliente(dirClientes);
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            printf("\n ");
            break;
        }
    }
    while (op != 0);

}

stUsuario inicioDeSesion ( char dirClientes [])
{
    stUsuario aux [1];
    //char usuario [30];
    stUsuario conectado;
    int pos=-1;

    while (pos<0)
    {
        printf("Ingrese usuario : ");
        fflush(stdin);
        gets(aux[0].nombreUsuario);
        printf("\nIngrese PIN (6 digitos numericos): ");
        fflush(stdin);
        scanf("%d", &aux[0].pin);
        pos=vUsuarioyPIN(aux, 0, dirClientes);
        if ( pos<0)
        {
            printf("\nDatos incorrectos o inexistentes.\n");
        }
        if(pos>=0)
        {
            conectado=levantaUsuario(dirClientes, pos);  /// RETORNA LA ESTRUCTURA DEL QUE INICIO SESION
        }
    }

    return conectado;
}

int vUsuarioyPIN(stUsuario aux[], int pos, char dirClientes[]) /// VALIDA Y BUSCA USUARIO Y PIN
{
    FILE *archi=fopen(dirClientes, "rb");
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

stUsuario levantaUsuario(char dirClientes [], int pos) ///FUNCION QUE LEVANTA EL USUARIO CONECTADO
{
    FILE * archi= fopen (dirClientes, "rb");
    stUsuario aux;

    if (archi != NULL)
    {

        fseek(archi,sizeof(stUsuario)*(pos), SEEK_SET);
        fread(&aux, sizeof(stUsuario), 1, archi);
        fclose(archi);
    }
    return aux;
}
///MODIFICACION/CONFIGURACION CLIENTES
void modCliente(stUsuario aux1, int aux, char dirClientes[])
{
    FILE *archi=fopen(dirClientes, "r+b");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stUsuario)*(aux-1),SEEK_SET);
        fwrite(&aux1,sizeof(stUsuario),1, archi);
        fclose(archi);
    }

}

stUsuario modUsuarioConectado(stUsuario conectado[], char dirClientes[])
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
            cNUsuario(conectado, 1, dirClientes);
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
void configCliente(stUsuario conectado[], char dirClientes[])
{
    stUsuario aux1;
    int aux=conectado[0].idCliente;
    int op=0;

    do
    {
        printf("\n\t1 - Darse de BAJA.");  /// PREGUNTARLE SI ESTA SEGURO .. $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        printf("\n\t2 - Modificar datos. ");
        printf("\n\t0 Volver al menu anterior. ");
        printf("\n\tIngrese su opcion: ");
        fflush(stdin);
        scanf("%i", &op);
        switch(op)
        {
        case 1:
            aux1=estadoCliente(conectado, 0, 0);
            break;
        case 2:
            aux1=modUsuarioConectado(conectado, dirClientes);
            modCliente(aux1, aux, dirClientes);
            break;
        }
    }
    while(op!=0);

}
void modUsuario(char dirClientes[])
{
    FILE *archi=fopen(dirClientes, "r+b");
    int i=0, dim=100, flag =0;
    stUsuario aux[dim];
    stUsuario aux1;

    int dato=pedidoAdmin(dirClientes);

    if  (archi!= NULL)
    {
        fseek(archi,0,SEEK_SET);
        while (flag == 0 && fread(&aux[i],sizeof(stUsuario),1,archi)>0)
        {
            if (aux[i].idCliente == dato)
            {
                aux1= modificaUsuario(aux, i, dirClientes);
                flag =1;
            }
            i++;
        }
        fseek(archi,sizeof(stUsuario)*(i-1),SEEK_SET);
        fwrite(&aux1,sizeof(stUsuario),1, archi);
        fclose(archi);
    }
}

stUsuario modificaUsuario(stUsuario aux[], int pos, char dirClientes[])
{
    int op=0, estado=0, rol=0;

    printf("\nMODIFICACION DE DATOS.");
    do
    {
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
            cNUsuario(aux, pos, dirClientes);
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

int vNUsuario(stUsuario aux[], int pos, char dirClientes[])
{
    FILE *archi=fopen(dirClientes, "rb");
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
void cargaCliente(char dirClientes[])
{
    int dim=100;
    stUsuario aux[dim];
    char letra ='s';
    int i=0, j=0;
    while (letra =='s')
    {
        puts("\n------------------------------------");
        i= cuentaClientesEnArchivo(dirClientes);
        i++;
        aux[j].idCliente= i;   /// 04/06 Por ahora no se rompio ...
        printf("\n ID %d \n\n", aux[j].idCliente);
        cMail(aux, j);
        cNombre(aux, j);
        cApellido(aux, j);
        cNUsuario(aux, j, dirClientes);
        cPin(aux, j);
        cGenero(aux, j);
        cEdad(aux,j);
        estadoCliente(aux, j, 0); ///  SERIA PARA CLIENTES QUE EMPIEZAN, INACTIVOS POR DEFAULT
        estadoRol(aux, j, 1);   /// 1 ES EL ESTADO PARA CIENTES NORMALES
        puts("\n-------------------------------------");
        arregloToArchi(dirClientes, aux, j);
        j++;
        printf("\nDesea Continuar? S/N: ");
        fflush(stdin);
        scanf("%c",&letra);
    }
}

int cuentaClientesEnArchivo(char dirClientes[])  /// CUENTA CANTIDAD DE CLIENTES
{
    //stUsuario alumno;
    int cantidad=0;
    FILE *archi;
    archi= fopen(dirClientes, "rb");
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

void cNUsuario(stUsuario aux[], int pos, char dirClientes[]) // Carga Nombre de Usuario
{
    int band=0;
    do
    {
        printf("\nIngrese nombre de usuario: ");
        fflush(stdin);
        scanf("%s",aux[pos].nombreUsuario);
        band=vNUsuario(aux, pos, dirClientes);

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

/// ALGO TO ARCHI'S
void arregloToArchi(char dirClientes[], stUsuario aux[], int pos)
{
    FILE *archi=fopen(dirClientes,"a+b");

    if (archi!=NULL)
    {
        fwrite(&aux[pos],sizeof(stUsuario),1,archi);

        fclose(archi);
    }
}

///MOSTRADORES
void muestraArchivo(char dirClientes[])
{
    FILE *archi=fopen(dirClientes, "rb");
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
    printf("\nID: %d ", aux[pos].idCliente);
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
    int op1=0, dim = 0, j= 0;
    char estado = ' ';
    stPedido aux;
    do
    {
        printf("\n1- Cargar Chango.");
        printf("\n2- Eliminar Producho Chango");
        printf("\n3- Cancelar Chango");
        printf("\n4- Mostrar Pedido");
        printf("\n5- Finalizar Compra");
        printf("\n0- Vuelve al Menu de Cliente");
        printf("\nIngrese opcion: ");
        scanf("%d", &op1);
        switch(op1)
        {
        case 1:
            aux=cargaPedido(dirPedidos, dirProductos,conectado,aux);
            break;
        case 2:
            aux=modChango(aux);
            break;
        case 3:
            printf("Seguro que quiere cancelar el pedido? s/n:\n");
            fflush(stdin);
            estado =getch();
            aux =bajaChango(aux,estado);
            break;
        case 4:
            mostrarChango(aux);
            break;
        case 5:
            pedidoToArchi(dirPedidos, aux);
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
    int valProductos=0, dim=150, valCat=0,i=0, k=0 ;
    int dato=0, dato1=0;
    char op='s';
    float total=0;
    stProducto arregloP[dim];
    stProducto arregloCat[dim];

    aux.idPedido= cuentaPedidosEnArchivo(dirPedidos)+1;
    aux.idCliente=conectado.idCliente;
    aux=diaYHora(aux);
    printf("\nFecha:  %s ", aux.fecha);
    aux.pedidoAnulado=0;
    valProductos=archivoProductosToArreglo(dirProductos, arregloP); /// Carga archivo de productos al arreglo
    muestraListadoGeneral();

    do
    {
        dato=cargaDato();
        // op=getch();
        valCat=arregloDeCategoria(arregloP, arregloCat, valProductos, dato);/// USUARIO INGRESA OPCION DE CATEGORIA
        /// ???????????????????????????????????? TAREA PARA CASA:  CASE MENU PARA USUARIO "AGREGAR PRODUCTO" "CANCELAR PRODUCTO" "FINALIAR COMPRA"
        /// hacerle acordar del cambio de tipo de dato en st pedido

        dato1=cargaDato();/// Carga en dato el producto que selecciono el usuario

        dato1--; /// para que el usuario ingrese la opcion 1, y obtengamos la posicion del arreglo 0

        aux= cargaArregloChango(aux, arregloCat, valCat,dato1, k); /// USUARIO INGRESA EL PRODUCTO SELECCIONADO  val chango
        k++;
        printf("\nDesea continuar: s/n");
        op=getch();

    }
    while(dato>0 && dato<9 && op!=27 && op=='s');

    aux.valChango=k;

    for(int j=0; j<k; j++)
    {
        total+=aux.chango[j].valor; ///suma el total del changuito seleccionado
    }

    aux.costo=total;
    printf("\nEl total de la compra es: %.2f\n", aux.costo);
    return aux;

}

stPedido modChango (stPedido aux)
{
    int dato=0,i = 0;
    char op='s';

    do
    {
        printf("Que producto desea quitar? \n");
        scanf("%d",&dato);
        dato--;
        if (dato > aux.valChango)
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

//
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
        mostrarProducto(aux[i], cont);
    }
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
            printf("\nId Cliente: %d ", aux[i].idCliente);
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
void mostrarChango (stPedido aux)
{
    int i=0;
    if (aux.pedidoAnulado==0)
    {
        for (i=0; i<aux.valChango; i++)
        {
            printf("|%c %d %s  \t $ %.2f  \t ",175,i+1,aux.chango[i].nombre,aux.chango[i].valor);

            if(i % 2 == 0)
            {
                printf("\n");
            }
        }
    }
    else
        printf("El pedido ha sido cancelado \n");
}
void mostrarProducto (stProducto aux, int cont )
{
    printf("|%c %d %s  \t $ %.2f  \t ",175,cont, aux.nombre, aux.valor);

    if(cont % 2 == 0)
    {
        printf("\n");
    }
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
    printf("\nMODIFICACION DE DATOS.");
    do
    {
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

void admMenuModificador (char dirClientes[], char dirProductos []) ///hay que cambiar los printf
{
    int op =0;
    do
    {
        printf("\nQue desea modificar. ");
        printf("\n1 - Clientes. ");
        printf("\n2 - Productos. ");
        printf("\n0 - Menu anterior.. ");
        printf("\nIngrese su Opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            modUsuario(dirClientes);
            break;
        case 2:
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
int validacionDatos(char dirClientes[])
{
    stUsuario aux;
    FILE * archi;
    int i=0;
    int flag=0;
    int j;

    archi =fopen(dirClientes,"ab");

    fread(&aux,sizeof(stUsuario),1,archi)>0;

    while(i<strlen(aux.nombreUsuario) && flag==0) ///
    {
        j=isalpha(dirClientes[i]);  /// ****** un sub indice en direccion de un dir
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
                                if(i >0) // no seguir borrando en el cursor de retrocedo.
                                {
                                    printf("\b \b"); // retrocedo del cursor hacia la izquierda
                                }
                            }
                            else
                            {
                                printf("*");
                            }
                        }*/




