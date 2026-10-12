/*
 * 010-switch-su-enum.c
 *
 * switch su un enum: un case per ogni costante
 *
 * Un enum elenca tutti i valori possibili: uno switch su un enum ha un
 * case per ognuno.
 *
 *     switch (f) {
 *     case CERCHIO:    ...  break;
 *     case QUADRATO:   ...  break;
 *     case TRIANGOLO:  ...  break;
 *     }
 *
 * Il compilatore aiuta: con -Wall (che comprende -Wswitch), se uno switch
 * su un enum non ha default e manca il case di una costante, avverte:
 *
 *     warning: enumeration value 'TRIANGOLO' not handled in switch
 *
 * Quando si aggiunge una costante all'enum (ESAGONO), il compilatore
 * indica tutti gli switch da aggiornare. Per questo, sugli enum, si
 * preferisce elencare tutti i case e non mettere default: un default
 * zittirebbe l'avviso.
 *
 * Esempio: l'area delle figure per il compito di geometria, con la
 * misura principale di ogni figura (raggio, lato o lato del triangolo
 * equilatero).
 */

#include <stdio.h>
#include <math.h>

#define FIGURE 4
#define PI_GRECO 3.14159265358979

typedef enum {
    CERCHIO, QUADRATO, TRIANGOLO
} Forma;

typedef struct {
    Forma forma;
    double misura;
} Figura;

double area(Forma f, double misura);
const char *nome(Forma f);

int main(void)
{
    Figura figure[FIGURE] = {{CERCHIO, 2.0}, {QUADRATO, 3.0}, {TRIANGOLO, 4.0}, {CERCHIO, 0.5}};
    int i;

    for (i = 0; i < FIGURE; i++) {
        printf("%-10s misura %4.1f  area %6.2f\n", nome(figure[i].forma), figure[i].misura,
               area(figure[i].forma, figure[i].misura));
    }

    return 0;
}

double area(Forma f, double misura)
{
    double risultato = 0;

    switch (f) {
    case CERCHIO:
        risultato = PI_GRECO * misura * misura;
        break;
    case QUADRATO:
        risultato = misura * misura;
        break;
    case TRIANGOLO:
        risultato = sqrt(3.0) / 4 * misura * misura;
        break;
    }
    return risultato;
}

const char *nome(Forma f)
{
    const char *testo = "";

    switch (f) {
    case CERCHIO:
        testo = "cerchio";
        break;
    case QUADRATO:
        testo = "quadrato";
        break;
    case TRIANGOLO:
        testo = "triangolo";
        break;
    }
    return testo;
}
