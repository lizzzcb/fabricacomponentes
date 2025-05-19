//Fabrica de componentes electronicos Liz Cisneros, Jordy Paz

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTOS 5
#define LONG_NOMBRE 50

typedef struct {
    char nombre[LONG_NOMBRE];
    int cantidad;
    float tiempo_fabricacion; // en horas
    float recursos_necesarios; // en unidades de recurso
} Producto;

Producto productos[MAX_PRODUCTOS];
int num_productos = 0;

void agregarProducto() {
    if (num_productos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos. Límite alcanzado.\n");
        return;
    }
    
    printf("\nIngrese el nombre del producto: ");
    scanf(" %[^\n]", productos[num_productos].nombre);
    
    printf("Ingrese la cantidad demandada: ");
    scanf("%d", &productos[num_productos].cantidad);
    
    printf("Ingrese el tiempo de fabricación por unidad (horas): ");
    scanf("%f", &productos[num_productos].tiempo_fabricacion);
    
    printf("Ingrese los recursos necesarios por unidad: ");
    scanf("%f", &productos[num_productos].recursos_necesarios);
    
    num_productos++;
    printf("Producto agregado con éxito.\n");
}

void editarProducto() {
    if (num_productos == 0) {
        printf("No hay productos para editar.\n");
        return;
    }
    
    char nombre[LONG_NOMBRE];
    printf("\nIngrese el nombre del producto a editar: ");
    scanf(" %[^\n]", nombre);
    
    int indice = -1;
    for (int i = 0; i < num_productos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    
    printf("\nEditando producto: %s\n", productos[indice].nombre);
    printf("Nueva cantidad demandada (actual: %d): ", productos[indice].cantidad);
    scanf("%d", &productos[indice].cantidad);
    
    printf("Nuevo tiempo de fabricación por unidad (actual: %.2f): ", productos[indice].tiempo_fabricacion);
    scanf("%f", &productos[indice].tiempo_fabricacion);
    
    printf("Nuevos recursos necesarios por unidad (actual: %.2f): ", productos[indice].recursos_necesarios);
    scanf("%f", &productos[indice].recursos_necesarios);
    
    printf("Producto editado con éxito.\n");
}

void eliminarProducto() {
    if (num_productos == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }
    
    char nombre[LONG_NOMBRE];
    printf("\nIngrese el nombre del producto a eliminar: ");
    scanf(" %[^\n]", nombre);
    
    int indice = -1;
    for (int i = 0; i < num_productos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    
    // Mover los productos posteriores una posición hacia atrás
    for (int i = indice; i < num_productos - 1; i++) {
        productos[i] = productos[i + 1];
    }
    
    num_productos--;
    printf("Producto eliminado con éxito.\n");
}

void calcularProduccion() {
    if (num_productos == 0) {
        printf("No hay productos para calcular.\n");
        return;
    }
    
    float tiempo_total = 0;
    float recursos_totales = 0;
    
    for (int i = 0; i < num_productos; i++) {
        tiempo_total += productos[i].cantidad * productos[i].tiempo_fabricacion;
        recursos_totales += productos[i].cantidad * productos[i].recursos_necesarios;
    }
    
    printf("\n--- RESUMEN DE PRODUCCIÓN ---\n");
    printf("Tiempo total de fabricación requerido: %.2f horas\n", tiempo_total);
    printf("Recursos totales necesarios: %.2f unidades\n", recursos_totales);
    
    float tiempo_disponible, recursos_disponibles;
    printf("\nIngrese el tiempo de producción disponible (horas): ");
    scanf("%f", &tiempo_disponible);
    printf("Ingrese los recursos disponibles: ");
    scanf("%f", &recursos_disponibles);
    
    if (tiempo_total <= tiempo_disponible && recursos_totales <= recursos_disponibles) {
        printf("\nLa fábrica PUEDE cumplir con la demanda.\n");
    } else {
        printf("\nLa fábrica NO PUEDE cumplir con la demanda.\n");
        if (tiempo_total > tiempo_disponible) {
            printf("- Faltan %.2f horas de producción.\n", tiempo_total - tiempo_disponible);
        }
        if (recursos_totales > recursos_disponibles) {
            printf("- Faltan %.2f unidades de recursos.\n", recursos_totales - recursos_disponibles);
        }
    }
}

void mostrarProductos() {
    if (num_productos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    
    printf("\n--- PRODUCTOS REGISTRADOS ---\n");
    for (int i = 0; i < num_productos; i++) {
        printf("\nProducto %d:\n", i + 1);
        printf("Nombre: %s\n", productos[i].nombre);
        printf("Cantidad demandada: %d\n", productos[i].cantidad);
        printf("Tiempo de fabricación por unidad: %.2f horas\n", productos[i].tiempo_fabricacion);
        printf("Recursos necesarios por unidad: %.2f\n", productos[i].recursos_necesarios);
    }
}

int main() {
    int opcion;
    
    printf("Sistema de Optimización de Producción\n");
    printf("Fábrica de Componentes Electrónicos\n\n");
    
    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Calcular producción\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                mostrarProductos();
                break;
            case 5:
                calcularProduccion();
                break;
            case 6:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 6);
    
    return 0;
}