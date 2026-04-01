/*
 * 060-problema-calcolo-area.c
 *
 * Calcolo di area e perimetro di figure geometriche
 *
 * L'utente sceglie una figura piana inserendo un numero intero
 * (1=quadrato, 2=rettangolo, 3=cerchio), poi fornisce le misure
 * necessarie. Il programma calcola area e perimetro e li stampa
 * con due cifre decimali.
 *
 * Nota didattica: la selezione avviene con if/else perché switch
 * viene introdotto nel capitolo 02. Niente array, stringhe o funzioni
 * definite dall'utente, come richiesto dai vincoli del capitolo 01.
 */

#include <stdio.h>

#define PI_GRECO 3.14159265358979

int main(void)
{
    int    figura;    /* 1=quadrato, 2=rettangolo, 3=cerchio */
    double lato;      /* per il quadrato */
    double base;      /* per il rettangolo */
    double altezza;   /* per il rettangolo */
    double raggio;    /* per il cerchio */
    double area;
    double perimetro;

    /* ── input: scelta della figura ────────────────────────────────────── */
    printf("=== Calcolo area e perimetro ===\n\n");
    printf("Scegli la figura:\n");
    printf("  1 - Quadrato\n");
    printf("  2 - Rettangolo\n");
    printf("  3 - Cerchio\n");
    printf("Scelta: ");
    scanf("%d", &figura);

    /* ── input: misure e calcolo in base alla figura scelta ─────────────── */
    if (figura == 1) {

        printf("Lato (m): ");
        scanf("%lf", &lato);
        area      = lato * lato;
        perimetro = 4.0 * lato;
        printf("\n--- Quadrato ---\n");

    } else if (figura == 2) {

        printf("Base (m):    ");
        scanf("%lf", &base);
        printf("Altezza (m): ");
        scanf("%lf", &altezza);
        area      = base * altezza;
        perimetro = 2.0 * (base + altezza);
        printf("\n--- Rettangolo ---\n");

    } else if (figura == 3) {

        printf("Raggio (m): ");
        scanf("%lf", &raggio);
        area      = PI_GRECO * raggio * raggio;
        perimetro = 2.0 * PI_GRECO * raggio;
        printf("\n--- Cerchio ---\n");

    } else {

        /* scelta non valida: i valori rimangono non inizializzati,
         * quindi avvisiamo l'utente e usciamo con un codice di errore. */
        printf("\nErrore: scelta non valida.\n");
        area      = 0.0;
        perimetro = 0.0;
        printf("Area:      ---\n");
        printf("Perimetro: ---\n");
        return 1;   /* 1 indica errore al sistema operativo */

    }

    /* ── output ─────────────────────────────────────────────────────────── */
    printf("Area:       %.4f m^2\n", area);
    printf("Perimetro:  %.4f m\n",   perimetro);

    return 0;
}
