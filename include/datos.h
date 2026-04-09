#ifndef DATOS_H
#define DATOS_H

typedef struct 
{
    int dia, mes, ano;
}Fecha;

typedef struct 
{
    int hora, minuto;
}Hora;

typedef struct 
{
    char nombre[20], contrasena[20];
    int nivel; //0-admin, 1-normie
}Usuario;

typedef struct 
{
    char nombre[20]; 
    int categoria, ID, vendidos; //1. plato fuerte, 2. entrada, 3. postre, 4. guarnicion
    float precio;
}Platillo;

typedef struct 
{
    char cliente[45];
    int platillos[100], ID, cantidad_platillos; 
    Fecha fecha;
    Hora hora;
    float total;
}Pedido;


#endif