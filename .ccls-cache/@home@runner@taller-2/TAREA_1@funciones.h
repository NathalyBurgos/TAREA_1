#ifndef FUNCIONES_H
#define FUNCIONES_H
#define TAMANIO_PRODUCTO sizeof(Producto)


#define MAX_PRODUCTOS 50
#define MAX_USUARIOS 10

#define ROL_ADMINISTRADOR "Administrador"
#define ROL_BODEGUERO "Bodeguero"
#define ROL_VENDEDOR "Vendedor"

typedef struct {
    char nombre[50];
    char rol[20];// Campo para el rol
    char claves[20];
} Usuario;

typedef struct {
    char nombre[50];
    char categoria[50];
    char marca[50];
    int codigo;
    float precioCompra;
    int bodega;
} Producto;

typedef struct {
    char local[50];
    char vendedor[50];
    char fecha[20];
    float precioVenta;
    int cantidadVendida;
    char nombreProducto[50];
} Venta;


void InicializarVentas();

int VerificarCredenciales(const char* nombreArchivo, const char* rolUsuario, const Usuario* usuarioActual, const char* claves);

void ActualizarUsuarioEnArchivo(const char* nombreArchivo, const char* nombreUsuario, const char* nuevoRol, const char* nuevaContraseña);
void AdministrarUsuarios(Usuario usuarioActual);
void ActualizarUsuario(const char *nombreUsuario);





void AdministrarProductos();

void ActualizarProductoEnArchivo(const char* nombreArchivo, int codigoProducto);



void CargarProductosDesdeArchivo(const char *nombreArchivo);
void RealizarVenta();

#endif
