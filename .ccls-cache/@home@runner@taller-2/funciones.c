#include <stdio.h>
#include <string.h>
#include "funciones.h"
#define MAX_LENGTH 100
#define TAMANIO_PRODUCTO sizeof(Producto)
#include <stdlib.h>

Usuario usuarios[MAX_USUARIOS];
Producto productos[MAX_PRODUCTOS];
Venta ventas[MAX_PRODUCTOS];

int numUsuarios = 0;
int numProductos = 0;
int numVentas = 0;



int VerificarCredenciales(const char* nombreArchivo, const char* rolUsuario, const Usuario* usuarioActual, const char* claves) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0; // Retorna 0 si hay un error al abrir el archivo
    }
    
    char rol[20];
    char usuario[50];
    char clave[20];

  
    while (fscanf(archivo, "%s %s %s", rol, usuario, clave) != EOF) {
        if (strcmp(rol, rolUsuario) == 0 && strcmp(usuario,usuarioActual->nombre) == 0 && strcmp(clave, claves) == 0) {
            fclose(archivo); // Cerrar el archivo después de encontrar el usuario
            return 1; // Retorna 1 si el usuario es válido
        }
    }

    fclose(archivo);
    return 0; // Retorna 0 si el usuario no es válido
}

// -------------------PRODUCTOS---------------------------------


void ActualizarUsuarioEnArchivo(const char* nombreArchivo, const char* nuevoRol, const char* nombreUsuario, const char* nuevaClave) {
    FILE *archivoLectura = fopen(nombreArchivo, "r");
    FILE *archivoTemporal = fopen("temp.txt", "w");

    if (archivoLectura == NULL || archivoTemporal == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }

    char buffer[MAX_LENGTH];
    char rol[MAX_LENGTH];
    char usuario[MAX_LENGTH];
    char clave[MAX_LENGTH];
    int encontrado = 0;

    while (fgets(buffer, sizeof(buffer), archivoLectura) != NULL) {
        sscanf(buffer, "%s %s %s", rol, usuario, clave);

        if (strcmp(usuario, nombreUsuario) == 0) {
            fprintf(archivoTemporal, "%s %s %s\n", nuevoRol, nombreUsuario, nuevaClave);
            encontrado = 1;
        } else {
            fprintf(archivoTemporal, "%s %s %s\n", rol, usuario, clave);
        }
    }

    fclose(archivoLectura);
    fclose(archivoTemporal);

    remove(nombreArchivo);
    rename("temp.txt", nombreArchivo);

    if (encontrado) {
        printf("Usuario actualizado correctamente.\n");
    } else {
        printf("Usuario no encontrado.\n");
    }
}

void AgregarProductoArchivo(const char* nombreArchivo, const Producto* nuevoProducto) {
    FILE *archivo = fopen(nombreArchivo, "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de productos para agregar.\n");
        return;
    }

    fprintf(archivo,"%s %s %s %d %.2f %d\n", nuevoProducto->nombre, nuevoProducto->categoria,
            nuevoProducto->marca,nuevoProducto->codigo, nuevoProducto->precioCompra, nuevoProducto->bodega);

    fclose(archivo);
}


void AdministrarProductos() {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("Se ha alcanzado el límite de productos.\n");
        return;
    }

    Producto nuevoProducto;

    printf("Ingrese el nombre del nuevo producto: ");
    scanf("%s", nuevoProducto.nombre);
    printf("Ingrese la categoría del producto: ");
    scanf("%s", nuevoProducto.categoria);
    printf("Ingrese la marca del producto: ");
    scanf("%s", nuevoProducto.marca);
    printf("Ingrese el código del producto: ");
    scanf("%d", &nuevoProducto.codigo);
    printf("Ingrese el precio de compra del producto: ");
    scanf("%f", &nuevoProducto.precioCompra);
    printf("Ingrese la cantidad en bodega del producto: ");
    scanf("%d", &nuevoProducto.bodega);

    productos[numProductos] = nuevoProducto;
    numProductos++;

    printf("Producto registrado con éxito.\n");

    // Ahora, también guardamos el nuevo producto en el archivo
    AgregarProductoArchivo("productos.txt", &nuevoProducto);
}

void MostrarProducto(const Producto *producto) {
    printf("Nombre: %s\n", producto->nombre);
    printf("Categoría: %s\n", producto->categoria);
    printf("Marca: %s\n", producto->marca);
    printf("Código: %d\n", producto->codigo);
    printf("Precio de Compra: %.2f\n", producto->precioCompra);
    printf("Cantidad en Bodega: %d\n", producto->bodega);
}

 void ActualizarProductoEnArchivo(const char* nombreArchivo, int codigoProducto) {
   
    FILE *archivoLectura = fopen(nombreArchivo, "r");
    FILE *archivoTemporal = fopen("temp.txt", "w");

    if (archivoLectura == NULL || archivoTemporal == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }

    char buffer[MAX_LENGTH];
    int encontrado = 0;

    while (fgets(buffer, sizeof(buffer), archivoLectura) != NULL) {
        Producto producto;
        sscanf(buffer, "%s %s %s %d %f %d",
               producto.nombre, producto.categoria, producto.marca,
               &producto.codigo, &producto.precioCompra, &producto.bodega);

        if (producto.codigo == codigoProducto) {
            encontrado = 1;

            // Mostrar el producto encontrado para actualizar
            printf("Producto encontrado:\n");
            MostrarProducto(&producto);

            // Solicitar los nuevos valores para actualizar el producto
            printf("Ingrese el nuevo nombre del producto: ");
            scanf("%s", producto.nombre);
            printf("Ingrese la nueva categoría del producto: ");
            scanf("%s", producto.categoria);
            printf("Ingrese la nueva marca del producto: ");
            scanf("%s", producto.marca);
            printf("Ingrese el nuevo precio de compra del producto: ");
            scanf("%f", &producto.precioCompra);
            printf("Ingrese la nueva cantidad en bodega del producto: ");
            scanf("%d", &producto.bodega);
        }

        fprintf(archivoTemporal, "%s %s %s %d %.2f %d\n",
                producto.nombre, producto.categoria, producto.marca,
                producto.codigo, producto.precioCompra, producto.bodega);
    }

    fclose(archivoLectura);
    fclose(archivoTemporal);

    remove(nombreArchivo);
    rename("temp.txt", nombreArchivo);

    if (encontrado) {
        printf("Producto actualizado correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

//---------------------------VENTAS-------------------------------------
 void CargarProductosDesdeArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de productos.\n");
        return;
    }

    while (fscanf(archivo, "%s %s %s %d %f %d\n", productos[numProductos].nombre,
                  productos[numProductos].categoria, productos[numProductos].marca,
                  &productos[numProductos].codigo, &productos[numProductos].precioCompra,
                  &productos[numProductos].bodega) != EOF && numProductos < MAX_PRODUCTOS) {
        numProductos++;
    }

    fclose(archivo);
 }



void RealizarVenta() {
    if (numProductos == 0) {
        printf("No hay productos disponibles para la venta.\n");
        return;
    }

    // Mostrar los productos disponibles
    printf("Productos disponibles:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s\n", i + 1, productos[i].nombre);
    }

    int productoSeleccionado;
    printf("Seleccione un producto para la venta (1-%d): ", numProductos);
    scanf("%d", &productoSeleccionado);

    if (productoSeleccionado < 1 || productoSeleccionado > numProductos) {
        printf("Selección de producto no válida.\n");
        return;
    }

    int cantidadVendida;
    printf("Ingrese la cantidad vendida: ");
    scanf("%d", &cantidadVendida);

    if (cantidadVendida <= 0 || cantidadVendida > productos[productoSeleccionado - 1].bodega) {
        printf("Cantidad no válida o insuficiente en bodega.\n");
        return;
    }

    char nombreVendedor[MAX_LENGTH];
    printf("Ingrese el nombre del vendedor: ");
    scanf("%s", nombreVendedor);

    char nombreLocal[MAX_LENGTH];
    printf("Ingrese el nombre del local: ");
    scanf("%s", nombreLocal);

    // Registrar la venta
    Venta venta;
    strcpy(venta.local, nombreLocal);
    strcpy(venta.vendedor, nombreVendedor);
    venta.precioVenta = productos[productoSeleccionado - 1].precioCompra * 1.2; // Ejemplo de precio de venta
    venta.cantidadVendida = cantidadVendida;
    strcpy(venta.nombreProducto, productos[productoSeleccionado - 1].nombre); // Nombre del producto vendido
    ventas[numVentas] = venta;
    numVentas++;

    // Actualizar la cantidad en bodega
    productos[productoSeleccionado - 1].bodega -= cantidadVendida;

    // Registrar la venta en el archivo ventas.txt
    FILE *archivoVentas = fopen("ventas.txt", "a");
    if (archivoVentas == NULL) {
        printf("No se pudo abrir el archivo de ventas.\n");
        return;
    }

    fprintf(archivoVentas, "%s %s %.2f %d %s\n", nombreLocal, nombreVendedor, venta.precioVenta, cantidadVendida, venta.nombreProducto);
    fclose(archivoVentas);

    printf("Venta registrada con éxito.\n");
}








void AdministrarUsuarios(Usuario usuarioActual) {
    if (numUsuarios >= MAX_USUARIOS) {
        printf("Se ha alcanzado el límite de usuarios.\n");
        return;
    }
  if (strcmp(usuarioActual.rol, ROL_ADMINISTRADOR) != 0) {
      printf("No tienes permisos para crear usuarios de este tipo.\n");
      return;
  }

    Usuario nuevoUsuario;

    printf("Ingrese el nombre del nuevo usuario: ");
    scanf("%s", nuevoUsuario.nombre);
    printf("Ingrese el rol del usuario (Administrador, Bodeguero, Vendedor):");
    scanf("%s", nuevoUsuario.rol);

    if (strcmp(nuevoUsuario.rol,ROL_ADMINISTRADOR) == 0 || strcmp(nuevoUsuario.rol, ROL_BODEGUERO) == 0 || strcmp(nuevoUsuario.rol, ROL_VENDEDOR) == 0) {
        usuarios[numUsuarios] = nuevoUsuario;
        numUsuarios++;
        printf("Usuario Administrador registrado con éxito.\n");
    } else {
        printf("Por favor ingresar el rol adecuado.\n");
    }
}





void ActualizarUsuario(const char *nombreUsuario) {
// Buscar el usuario por su nombre de usuario
for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].nombre, nombreUsuario) == 0) {
        // Usuario encontrado, permite actualizarlo
        printf("Usuario encontrado:\n");
        printf("Nombre de Usuario: %s\n", usuarios[i].nombre);
        printf("Rol: %s\n", usuarios[i].rol);

        // Solicitar la actualización de los campos del usuario
        printf("Ingrese el nuevo nombre de usuario: ");
        scanf("%s", usuarios[i].nombre);
        printf("Ingrese el nuevo rol del usuario: ");
        scanf("%s", usuarios[i].rol);

        printf("Usuario actualizado con éxito.\n");
        return;
    }
}
}