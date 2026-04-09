#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "datos.h"


bool confirmar_existencia_platillos(int id)
{
    FILE *archivo;
    archivo = fopen("platillos.bin", "rb");

    int n=0, i;
    n = calcular_elementos(archivo, sizeof(Platillo));

    Platillo platillos[n];

    fread(platillos, sizeof(Platillo), n, archivo);

    for(i=0; i < n; i++)
    {
        if(id == platillos[i].ID)
            return true;
    }

    printf("\nNo se encontro un platillo con el id especificado\n");
    return false;
}

Platillo info_platillo(int id)
{

    FILE *archivo;
    archivo = fopen("platillos.bin", "rb");

    int n=0, i=0, indice = -1;
    n = calcular_elementos(archivo, sizeof(Platillo));

    Platillo platillos[n];

    fread(platillos, sizeof(Platillo), n, archivo);

    for(i=0; i < n; i++)
    {
        if(id == platillos[i].ID)
        {
            indice = i;
            break;
        }
    }

    if(indice != -1)
        return platillos[indice];
    else
        return;

}

void quitar_salto(char *cadena)
{
    cadena[strcspn((cadena), "\n")] = '\0';
}

bool validar_usuario(FILE *archivo, char *usuario, char *contrasena)
{

    rewind(archivo);
    Usuario envase;

    while (fread(&envase, sizeof(Usuario), 1, archivo) == 1)
    {
        if (strcmp(usuario, envase.nombre) == 0 && strcmp(contrasena, envase.contrasena) == 0)
            return true;
    }

    printf("\nLos datos son incorrectos\n");
    return false;
}

int calcular_elementos(FILE *archivo, long tamano_elemento)
{

    fseek(archivo, 0, SEEK_END);
    long tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    return tamano / tamano_elemento;
}

int comparar_fechas(Fecha a, Fecha b)
{

    if (a.ano == b.ano)
        if (a.mes == b.mes)
            if (a.dia > b.dia)
                return 1;
            else if (b.dia > a.dia)
                return 2;
            else
                return 0;
        else if (a.mes > b.mes)
            return 1;
        else
            return 2;

    if (a.ano > b.ano)
        return 1;

    if (b.ano > a.ano)
        return 2;
}

Fecha fecha_actual()
{
    Fecha fecha;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    fecha.dia = tm_info->tm_mday;
    fecha.mes = tm_info->tm_mon + 1;
    fecha.ano = tm_info->tm_year + 1900;

    return fecha;
}

Hora hora_actual()
{
    Hora hora_actual;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    hora_actual.hora = tm_info->tm_hour;
    hora_actual.minuto = tm_info->tm_min;

    return hora_actual;
}

void imprimir_pedido(Pedido envase)
{
    FILE *archivo_platillos;
    archivo_platillos = fopen("platillos.bin", "rb");

    int n = calcular_elementos(archivo_platillos, sizeof(Platillo));
    Platillo platillos[n];

    fread(platillos, sizeof(Platillo), n, archivo_platillos);

    int i, j;

    char nombres_platillos[envase.cantidad_platillos][20];

    for(i = 0; i < envase.cantidad_platillos; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(envase.platillos[i] == platillos[j].ID)
            {
                strcpy(nombres_platillos[i], platillos[j].nombre);
                break;
            }

        }
    }

    printf("Pedido #%-3d | Cliente: %-25s | Total: $%-6.2f\n", envase.ID, envase.cliente, envase.total);
    printf("Platillos: ");

    for (i = 0; i < envase.cantidad_platillos; i++)
    {
        if (i != envase.cantidad_platillos - 1)
            printf("%s, ", nombres_platillos[i]);
        else
            printf("%s", nombres_platillos[i]);
    }
    printf("\n\n");
}

Fecha solicitar_fecha(int ano_min, int ano_max)
{
    int c;
    Fecha fecha;

    do
    {
        printf("\nIntroduzca el ano: ");
        scanf("%d", &fecha.ano);
        getchar();
    } while (!validar_entero(ano_min, ano_max, fecha.ano));


    do
    {
        printf("Introduzca el mes (1-12): ");
        scanf("%d", &fecha.mes);
        getchar();
    } while (!validar_entero(1, 12, fecha.mes));


    int max_dias;
    if (fecha.mes == 1 || fecha.mes == 3 || fecha.mes == 5 || fecha.mes == 7 ||
        fecha.mes == 8 || fecha.mes == 10 || fecha.mes == 12)
        max_dias = 31;
    else if (fecha.mes == 2)
        max_dias = 29;
    else
        max_dias = 30;

    do
    {
        printf("Introduzca el dia (1-%d): ", max_dias);
        scanf("%d", &fecha.dia);
        getchar();
    } while (!validar_entero(1, max_dias, fecha.dia));


    return fecha;
}

int existencia_platillos()
{
    int num_platillos = 0;

    FILE *archivo_platillos = fopen("platillos.bin", "rb");

    if (archivo_platillos != NULL)
        num_platillos = calcular_elementos(archivo_platillos, sizeof(Platillo));

    fclose(archivo_platillos);

    return num_platillos;
}

int existencia_pedidos()
{
    int num_pedidos = 0;

    FILE *archivo_pedidos = fopen("pedidos.bin", "rb");

    if (archivo_pedidos != NULL)
        num_pedidos = calcular_elementos(archivo_pedidos, sizeof(Pedido));

    fclose(archivo_pedidos);

    return num_pedidos;
}

void actualizar_platillo(int id)
{
    FILE *archivo = fopen("platillos.bin", "r+b");

    Platillo platillo;

    while (fread(&platillo, sizeof(Platillo), 1, archivo) == 1)
    {
        if (platillo.ID == id)
        {
            platillo.vendidos++;
            fseek(archivo, -sizeof(Platillo), SEEK_CUR);
            fwrite(&platillo, sizeof(Platillo), 1, archivo); 
            break;
        }
    }

    fclose(archivo);

}