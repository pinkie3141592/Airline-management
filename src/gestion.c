#include <stdio.h>
#include "datos.h"
#include "validaciones.h"
#include "utilidades.h"


void agregar_platillo()
{

    FILE *archivo_platillos;
    archivo_platillos = fopen("platillos.bin", "a+b");

    Platillo platillo;

    platillo.ID = calcular_elementos(archivo_platillos, sizeof(Platillo)) + 1;

    do
    {
        printf("Ingrese nombre del platillo: ");
        fgets(platillo.nombre, sizeof(platillo.nombre), stdin);
        quitar_salto(platillo.nombre);
    }while(!validar_cadena(platillo.nombre));

    do
    {
        printf("Seleccione la categoria:\n" 
            "1. Entrada\n" 
            "2. Plato fuerte\n" 
            "3. Guarnicion\n" 
            "4. Postre\n");
        scanf("%d", &platillo.categoria);
        getchar();

        platillo.categoria --;

    }while(!validar_entero(0,3, platillo.categoria));

    printf("Precio: ");
    scanf("%f", &platillo.precio);
    getchar();

    platillo.vendidos = 0;

    if(fwrite(&platillo, sizeof(Platillo), 1, archivo_platillos) == 1)
        printf("\nPlatillo agregado correctamente\n");

    fclose(archivo_platillos);

    system("pause");

}

void mostrar_menu()
{
    FILE *archivo_platillos;
    archivo_platillos = fopen("platillos.bin", "rb");

    Platillo envase;
    char categorias[4][15] = {"Entrada", "Plato fuerte", "Guarnicion", "Postre"};

    system("cls");

    printf("===MENU DEL RESTAURANTE=== \n\n");

    printf("%-5s | %-15s | %-20s | %-10s\n",  "ID", "CATEGORIA", "NOMBRE", "PRECIO");
    printf("-------------------------------------------------------\n");
    
    while(fread(&envase, sizeof(Platillo), 1, archivo_platillos) == 1)
    {
        
        printf("%-5d | %-15s | %-20s | %-10.2f\n",  envase.ID, categorias[envase.categoria], envase.nombre, envase.precio);

    }

    printf("\n");
    fclose(archivo_platillos);

    system("pause");

}