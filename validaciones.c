#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool validar_entero(int min, int max, int num)
{

    if(min <= num && num <= max)
        return true;
    else
    {
        printf("\nERROR: Respuesta fuera de rango\n");
        return false;
    }

}

bool validar_cadena(char *cadena)
{

    int i=0;
    for(i = 0; i < strlen(cadena); i++)
    {
        
        if((cadena[i] < 'a' || cadena[i] > 'z') && (cadena[i] < 'A' || cadena[i] > 'Z') && cadena[i] != ' ')
            return false;
    }

    return true;

}