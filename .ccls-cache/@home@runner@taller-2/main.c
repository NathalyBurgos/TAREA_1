#include <stdio.h>
#include "funciones.h"
#include <string.h>


int main() {
    int opcion;
    int rol;
    

    char claves[20];
    char rolUsuario[20];
    Usuario usuarioActual;

   char nombreUsuario[50];
   char nuevoRol[20];
   char nuevaContraseña[20];


    int codigoProducto;

    // Inicializar las estructuras de datos
    

   


    printf("Bienvenido al Sistema de Registro de Productos Electrónicos\n");

    // Solicitar al usuario que ingrese su rol
    printf("Por favor, seleccione su rol:\n");
    printf("1. Administrador\n");
    printf("2. Bodeguero\n");
    printf("3. Vendedor\n");
    printf("Seleccione su rol (1/2/3): ");
    scanf("%d", &rol);

    // Asignar el rol de acuerdo a la elección del usuario
    switch (rol) {
        case 1:
            strcpy(usuarioActual.rol, ROL_ADMINISTRADOR);
            break;
        case 2:
            strcpy(usuarioActual.rol, ROL_BODEGUERO);
            break;
        case 3:
            strcpy(usuarioActual.rol, ROL_VENDEDOR);
            break;
        default:
            printf("Rol no válido. Saliendo del programa...\n");
            return 1;
    }


  //verificar si el usuario es permitido o no 

  while (1) {
      // Solicitar credenciales al usuario
      printf("Ingrese su rol: ");
      scanf("%s", rolUsuario);
      printf("Ingrese su usuario: ");
      scanf("%s", usuarioActual.nombre);
      printf("Ingrese su contraseña: ");
      scanf("%s", claves);

      // Verificar las credenciales
      int esValido = VerificarCredenciales("usuario.txt", rolUsuario, &usuarioActual, claves);

      if (esValido) {
          printf("Las credenciales son válidas. Acceso permitido.\n");
          break; // Salir del bucle si las credenciales son válidas
      } else {
          printf("Credenciales inválidas. Vuelva a intentarlo.\n");
          // Limpiar el buffer de entrada
          while ((getchar()) != '\n');
      }
  }





  
   if (strcmp(usuarioActual.rol, ROL_ADMINISTRADOR) == 0) {
       // Usuario con rol de Administrador
       while (1) {
           // Menú para el Administrador
         printf("\n--------------Menú del Administrador------------\n");
           printf("1. Crear Usuario\n");
           printf("2. Actualizar Usuario\n");
           printf("3. Salir\n");
           printf("Seleccione una opción: ");
           scanf("%d", &opcion);

           switch (opcion) {
               case 1:
                   AdministrarUsuarios(usuarioActual);
                   break;
               case 2: {
              

                   printf("Ingrese el nombre de usuario que desea actualizar: ");
                   scanf("%s", nombreUsuario);
                   printf("Ingrese el nuevo rol para el usuario: ");
                   scanf("%s", nuevoRol);
                   printf("Ingrese la nueva contraseña para el usuario: ");
                   scanf("%s", nuevaContraseña);


                     
                   // Llamada a la función para actualizar el usuario en el archivo
                   ActualizarUsuarioEnArchivo("usuario.txt", nuevoRol,nombreUsuario,nuevaContraseña);
                   break;
               }
                 

               case 3:
                   printf("Saliendo del programa...\n");
                   return 0;
               default:
                   printf("Opción no válida. Por favor, seleccione una opción válida.\n");
           }
       }
   } else if (strcmp(usuarioActual.rol, ROL_BODEGUERO) == 0) {
       // Usuario con rol de Bodeguero
       while (1) {
           // Menú para el Bodeguero
        printf("\n-----------Menú del Bodeguero--------------\n");
           printf("1. Crear Producto\n");
           printf("2. Actualizar Producto\n");
           printf("3. Salir\n");
           printf("Seleccione una opción: ");
           scanf("%d", &opcion);

           switch (opcion) {
               case 1:
                   AdministrarProductos();
                   break;
               case 2:
                 printf("Ingrese el código del producto que desea actualizar: ");
                 scanf("%d", &codigoProducto);
                 ActualizarProductoEnArchivo("productos.txt", codigoProducto);
                 


                 
                   break;
               case 3:
                   printf("Saliendo del programa...\n");
                   return 0;
               default:
                   printf("Opción no válida. Por favor, seleccione una opción válida.\n");
           }
       }
   } else if (strcmp(usuarioActual.rol, ROL_VENDEDOR) == 0) {
       // Usuario con rol de Vendedor
       while (1) {
           // Menú para el Vendedor
           printf("\n----------------------Menú del Vendedor-------------------\n");
           printf("1. Realizar Venta\n");
           printf("2. Salir\n");
           printf("Seleccione una opción: ");
           scanf("%d", &opcion);

           switch (opcion) {
               case 1:
                  CargarProductosDesdeArchivo("productos.txt");
                 
                   RealizarVenta();
                   break;
               case 2:
                   printf("Saliendo del programa...\n");
                   return 0;
               default:
                   printf("Opción no válida. Por favor, seleccione una opción válida.\n");
           }
       }
   }





















  

    return 0;
}


