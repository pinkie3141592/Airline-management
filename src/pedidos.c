#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validaciones.h"
#include "utilidades.h"
#include "datos.h"

void acomodar_pedidos_fecha()
{
    FILE *archivo_pedidos;
    archivo_pedidos = fopen("pedidos.bin", "rb");

    int n = calcular_elementos(archivo_pedidos, sizeof(Pedido));
    Pedido pedidos[n];

    fread(pedidos, sizeof(Pedido), n, archivo_pedidos);

    Pedido temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (comparar_fechas(pedidos[j].fecha, pedidos[j+1].fecha) == 1)
            {
                temp = pedidos[j];
                pedidos[j] = pedidos[j+1];
                pedidos[j+1] = temp;
            }
        }
    }

    fclose(archivo_pedidos);

    archivo_pedidos = fopen("pedidos.bin", "wb");

    fwrite(pedidos, sizeof(Pedido), n, archivo_pedidos);

    fclose(archivo_pedidos);
    
}

void lista_de_pedidos()
{
    acomodar_pedidos_fecha();

    FILE *archivo_pedidos;
    archivo_pedidos = fopen("pedidos.bin", "rb");

    rewind(archivo_pedidos);

    int i;

    Pedido envase;
    Fecha ultima_fecha = {};


    while(fread(&envase, sizeof(Pedido), 1, archivo_pedidos) == 1)
    {
        if(comparar_fechas(ultima_fecha, envase.fecha) != 0)
        {
            ultima_fecha = envase.fecha;
            printf("FECHA: %02d/%02d/%d\n", ultima_fecha.dia, ultima_fecha.mes, ultima_fecha.ano);
        }

        imprimir_pedido(envase);
    }

    fclose(archivo_pedidos);

    system("pause");

}

void buscar_pedido_cliente()
{
    FILE *archivo_pedidos;
    archivo_pedidos = fopen("pedidos.bin", "rb");

    char nombre[30];
    int n = 0;

    system("cls");
    printf("Introduce el nombre del cliente: ");
    fgets(nombre, sizeof(nombre), stdin);
    quitar_salto(nombre);

    Pedido envase;

    while(fread(&envase, sizeof(Pedido), 1, archivo_pedidos) == 1)
    {
        if(strcmp(envase.cliente, nombre) == 0)
        {
            imprimir_pedido(envase);
            n++;
        }
    }
    
    if(n != 0)
        printf("Total de coincidencias: %d\n", n);
    else
        printf("\nNo se encontraron pedidos de ese cliente\n");

    system("pause");

}

void buscar_pedido_fecha()
{
    FILE *archivo_pedidos;
    archivo_pedidos = fopen("pedidos.bin", "rb");

    char nombre[30];
    int n = 0;

    Fecha fecha_buscada = solicitar_fecha(1900, 2030);

    Pedido envase;

    while(fread(&envase, sizeof(Pedido), 1, archivo_pedidos) == 1)
    {
        if(comparar_fechas(envase.fecha, fecha_buscada) == 0)
        {
            imprimir_pedido(envase);
            n++;
        }
    }

    if(n != 0)
        printf("\nTotal de coincidencias: %d\n", n);
    else
        printf("\nNo se encontraron pedidos de esa fecha\n");

    system("pause");
}

void toptres_platillos()
{
    FILE *archivo_platillos;
    archivo_platillos = fopen("platillos.bin", "rb");

    int n = calcular_elementos(archivo_platillos, sizeof(Platillo));
    Platillo platillos[n];

    fread(platillos, sizeof(Platillo), n, archivo_platillos);

    Platillo temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (platillos[j].vendidos < platillos[j+1].vendidos)
            {
                temp = platillos[j];
                platillos[j] = platillos[j+1];
                platillos[j+1] = temp;
            }
        }
    }

    fclose(archivo_platillos);

    archivo_platillos = fopen("platillos.bin", "wb");

    fwrite(platillos, sizeof(Platillo), n, archivo_platillos);

    fclose(archivo_platillos);

    for(i=0; i < n && i < 3; i++)
    {
        printf("%d. %s - %d veces\n", i+1, platillos[i].nombre, platillos[i].vendidos);
    }

    system("pause");

}