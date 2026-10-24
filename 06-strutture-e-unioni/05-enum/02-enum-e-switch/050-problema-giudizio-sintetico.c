/*
 * 050-problema-giudizio-sintetico.c
 *
 * Verifica di storia: dal voto al giudizio, e la distribuzione dei
 * giudizi nella classe
 *
 * Sul registro, accanto al voto numerico, va il giudizio sintetico:
 *
 *     typedef enum {
 *         GRAV_INSUFFICIENTE, INSUFFICIENTE, SUFFICIENTE, DISCRETO,
 *         BUONO, OTTIMO, NUM_GIUDIZI
 *     } Giudizio;
 *
 *     Giudizio da_voto(double voto);
 *     const char *nome(Giudizio g);
 *
 * Fasce: sotto 5 gravemente insufficiente, sotto 6 insufficiente, sotto
 * 7 sufficiente, sotto 8 discreto, sotto 9 buono, da 9 ottimo.
 *
 * Il programma legge i voti (da 1 a 10, anche con il mezzo voto) fino a
 * -1, stampa il giudizio di ognuno e poi un istogramma con un asterisco
 * per ogni studente in ciascun giudizio. Il giudizio è un indice
 * dell'array dei conteggi.
 */

#include <stdio.h>

typedef enum {
    GRAV_INSUFFICIENTE, INSUFFICIENTE, SUFFICIENTE, DISCRETO, BUONO, OTTIMO, NUM_GIUDIZI
} Giudizio;

Giudizio da_voto(double voto);
const char *nome(Giudizio g);
void svuota_riga(void);

int main(void)
{
    int conteggi[NUM_GIUDIZI] = {0};
    double voto = 0;
    int studenti = 0;
    Giudizio g;
    int k;
    int letti;

    while (voto != -1) {
        printf("Voto (-1 per finire): ");
        letti = scanf("%lf", &voto);
        if (letti == EOF) {
            voto = -1;                  /* input terminato: come -1 */
        } else if (letti == 0) {
            svuota_riga();              /* non e' un numero */
            printf("  Voto non valido.\n");
            voto = 0;                   /* si continua */
        } else if (voto != -1 && (voto < 1 || voto > 10)) {
            printf("  Voto non valido.\n");
        } else if (voto != -1) {
            g = da_voto(voto);
            conteggi[g]++;
            studenti++;
            printf("  %.1f: %s\n", voto, nome(g));
        }
    }

    printf("\nGiudizi della classe (%d studenti)\n", studenti);
    for (g = GRAV_INSUFFICIENTE; g < NUM_GIUDIZI; g++) {
        printf("  %-26s ", nome(g));
        for (k = 0; k < conteggi[g]; k++) {
            printf("*");
        }
        printf(" %d\n", conteggi[g]);
    }

    return 0;
}

Giudizio da_voto(double voto)
{
    Giudizio g = OTTIMO;

    if (voto < 5) {
        g = GRAV_INSUFFICIENTE;
    } else if (voto < 6) {
        g = INSUFFICIENTE;
    } else if (voto < 7) {
        g = SUFFICIENTE;
    } else if (voto < 8) {
        g = DISCRETO;
    } else if (voto < 9) {
        g = BUONO;
    }
    return g;
}

const char *nome(Giudizio g)
{
    const char *testo = "";

    switch (g) {
    case GRAV_INSUFFICIENTE:
        testo = "gravemente insufficiente";
        break;
    case INSUFFICIENTE:
        testo = "insufficiente";
        break;
    case SUFFICIENTE:
        testo = "sufficiente";
        break;
    case DISCRETO:
        testo = "discreto";
        break;
    case BUONO:
        testo = "buono";
        break;
    case OTTIMO:
        testo = "ottimo";
        break;
    case NUM_GIUDIZI:
        break;
    }
    return testo;
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
