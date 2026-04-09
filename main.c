#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#include "validaciones.h"
#include "utilidades.h"
#include "datos.h"
#include "gestion.h"
#include "pedidos.h"

void registrar_pedido()
{
    Pedido pedido;
    Platillo platillo;

    pedido.total = 0;
    int n=0, i=0;

    FILE *archivo;
    archivo = fopen("pedidos.bin", "rb");    
    if(archivo != NULL)
        pedido.ID = calcular_elementos(archivo, sizeof(Pedido)) + 1;
    fclose(archivo);

    printf("Nombre del cliente: ");
    fgets(pedido.cliente, sizeof(pedido.cliente), stdin);
    pedido.cliente[strcspn(pedido.cliente, "\n")] = '\0';

    printf("Cantidad de platillos: ");
    scanf("%d", &pedido.cantidad_platillos);
    getchar();

    for(i = 0; i < pedido.cantidad_platillos ; i++)
    {
        do
        {
            printf("\nID platillo %d: ", i+1);
            scanf("%d", &pedido.platillos[i]);
        }while(!confirmar_existencia_platillos(pedido.platillos[i]));
        
        actualizar_platillo(pedido.platillos[i]);

        platillo = info_platillo(pedido.platillos[i]);

        pedido.total += platillo.precio;
    }

    printf("\nTotal del pedido: %.2f\n", pedido.total);
    
    archivo = fopen("pedidos.bin", "ab");
    
    pedido.fecha = fecha_actual();
    pedido.hora = hora_actual();

    fwrite(&pedido, sizeof(Pedido), 1, archivo);

    fclose(archivo);

    system("pause");

}

void iniciar_sesion()
{
    char usuario[20], pswd[20];

    FILE *archivo_usuarios;

    archivo_usuarios = fopen("usuarios.bin", "rb");

    if (archivo_usuarios == NULL)
    {
        Usuario admin = {"admin", "1234", 0};
        archivo_usuarios = fopen("usuarios.bin", "wb");
        fwrite(&admin, sizeof(Usuario), 1, archivo_usuarios);
        fclose(archivo_usuarios);

        archivo_usuarios = fopen("usuarios.bin", "rb");
    }

    do
    {
        system("cls");
        printf("==INICIO DE SESION==\n");
        printf("Usuario: ");
        fgets(usuario, sizeof(usuario), stdin);
        quitar_salto(usuario);

        printf("Contrasena: ");
        fgets(pswd, sizeof(pswd), stdin);
        quitar_salto(pswd);

    } while (!validar_usuario(archivo_usuarios, usuario, pswd));

    fclose(archivo_usuarios);

    printf("BIENVENIDO ADMINISTRADOR\n");
    Sleep(1000);
}

void reporte_general()
{

    system("cls");

    FILE *archivo;
    archivo = fopen("pedidos.bin", "rb");

    Pedido envase;
    int total_pedidos = 0;
    float ventas_totales = 0.0;

    while (fread(&envase, sizeof(Pedido), 1, archivo) == 1)
    {
        total_pedidos++;
        ventas_totales += envase.total;
    }

    fclose(archivo);

    printf("=== INFORME GENERAL DE PEDIDOS ===\n");
    printf("Total de pedidos: %d\n", total_pedidos);
    printf("Ventas totales: $%.2f\n", ventas_totales);
    printf("Promedio de venta: $%.2f\n", ventas_totales / total_pedidos);

    printf("\n");

    system("pause");
}

void reporte_txt()
{
    acomodar_pedidos_fecha();

    FILE *archivo_pedidos = fopen("pedidos.bin", "rb");
    FILE *archivo_platillos = fopen("platillos.bin", "rb");
    FILE *reporte = fopen("reporte_pedidos.txt", "w");

    int n_platillos = calcular_elementos(archivo_platillos, sizeof(Platillo));
    Platillo platillos[n_platillos];
    fread(platillos, sizeof(Platillo), n_platillos, archivo_platillos);
    fclose(archivo_platillos);

    Pedido envase;
    Fecha ultima_fecha = {};
    float total_ventas = 0.0;

    int i, j;

    while (fread(&envase, sizeof(Pedido), 1, archivo_pedidos) == 1)
    {
        if (comparar_fechas(ultima_fecha, envase.fecha) != 0)
        {
            ultima_fecha = envase.fecha;
            fprintf(reporte, "FECHA: %02d/%02d/%d\n", ultima_fecha.dia, ultima_fecha.mes, ultima_fecha.ano);
        }

        fprintf(reporte, "Pedido #%d | Cliente: %-25s | Total: $%.2f\n", envase.ID, envase.cliente, envase.total);

        fprintf(reporte, "Platillos: ");
        for (i = 0; i < envase.cantidad_platillos; i++)
        {
            int id_platillo = envase.platillos[i];
            for (j = 0; j < n_platillos; j++)
            {
                if (platillos[j].ID == id_platillo)
                {
                    fprintf(reporte, "%s", platillos[j].nombre);
                    break;
                }
            }
            if (i != envase.cantidad_platillos - 1)
                fprintf(reporte, ", ");
        }
        fprintf(reporte, "\n\n");

        total_ventas += envase.total;
    }

    fprintf(reporte, "=== Total de ventas: $%.2f ===\n", total_ventas);

    fclose(archivo_pedidos);
    fclose(reporte);
}

void generar_reporte()
{
    reporte_general();
    reporte_txt();
}

void menu_gestion()
{
    int opcion;

    do
    {
        system("cls");
        printf("---GESTION DE MENU---\n");
        printf("1. Agregar platillo\n"
               "2. Mostrar menu\n"
               "0. Volver\n");
        scanf("%d", &opcion);
        getchar();

    } while (!validar_entero(0, 2, opcion));

    if (opcion == 0)
        return;

    switch (opcion)
    {
    case 1:
        agregar_platillo();
        break;
    case 2:
        mostrar_menu();
        break;
    }
}

void menu_pedidos()
{

    int opcion;

    do
    {
        system("cls");
        printf("---CONSULTA DE PEDIDOS---\n");
        printf("1. PEDIDOS\n"
               "2. PEDIDOS POR CLIENTE\n"
               "3. PEDIDO POR RANGO DE FECHAS\n"
               "4. PLATILLOS MAS VENDIDOS\n"
               "0. Volver\n");
        scanf("%d", &opcion);
        getchar();

    } while (!validar_entero(0, 4, opcion));

    if (opcion == 0)
        return;

    switch (opcion)
    {
    case 1:
        lista_de_pedidos();
        break;
    case 2:
        buscar_pedido_cliente();
        break;
    case 3:
        buscar_pedido_fecha();
        break;
    case 4:
        toptres_platillos();
        break;
    }
}

int main()
{
    int opcion;

    iniciar_sesion();
    system("cls");

    do
    {
        system("cls");
        printf("MENU PRINCIPAL\n");
        printf("\n===MENU DE GESTION DE RESTAURANTE===\n");

        do
        {
            printf("1. Gestionar menu del restaurante\n"
                   "2. Registrar nuevo pedido\n"
                   "3. Consultar pedidos realizados\n"
                   "4. Generar reporte de ventas\n"
                   "0. Salir\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcion);
            getchar();

        } while (!validar_entero(0, 4, opcion));

        switch (opcion)
        {
        case 1:
            menu_gestion();
            break;
        case 2:
            if (existencia_platillos != 0)
                registrar_pedido();
            else
            {
                printf("\nERROR: Debes registrar platillos antes de hacer pedidos!\n");
                system("pause");
            }
            break;
        case 3:
            if (existencia_pedidos != 0)
                menu_pedidos();
            else
            {
                printf("\nERROR: Debes registrar pedidos antes de ir al menu de pedidos!\n");
                system("pause");
            }
            break;
        case 4:
            if (existencia_pedidos != 0)
                generar_reporte();
            else
            {
                printf("\nERROR: Debes registrar pedidos antes de generar un reporte!\n");
                system("pause");
            }
            break;
        }
    } while (opcion != 0);
}
