/*
 * 040-problema-figure-geometriche.c
 *
 * Verifica di geometria: area e perimetro di figure diverse
 *
 * Ogni figura ha dati diversi: il cerchio un raggio, il rettangolo base
 * e altezza, il triangolo tre lati. Una Figura contiene l'etichetta e
 * una union delle tre alternative:
 *
 *     typedef struct {
 *         TipoFigura tipo;
 *         union {
 *             Cerchio cerchio;
 *             Rettangolo rettangolo;
 *             Triangolo triangolo;
 *         } dati;
 *     } Figura;
 *
 *     f.dati.triangolo.a
 *
 * area, perimetro e valida sono switch sull'etichetta. Un triangolo è
 * valido se ogni lato è minore della somma degli altri due; l'area del
 * triangolo si calcola con la formula di Erone.
 *
 * Il programma legge le figure fino a FINE:
 *     C raggio          R base altezza          T a b c
 * stampa area e perimetro di ognuna e alla fine la figura con l'area
 * maggiore.
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_FIGURE 8
#define PI_GRECO 3.14159265358979

typedef enum {
    CERCHIO, RETTANGOLO, TRIANGOLO
} TipoFigura;

typedef struct {
    double raggio;
} Cerchio;

typedef struct {
    double base;
    double altezza;
} Rettangolo;

typedef struct {
    double a;
    double b;
    double c;
} Triangolo;

typedef struct {
    TipoFigura tipo;
    union {
        Cerchio cerchio;
        Rettangolo rettangolo;
        Triangolo triangolo;
    } dati;
} Figura;

int leggi_figura(Figura *f);
int valida(const Figura *f);
double area(const Figura *f);
double perimetro(const Figura *f);
const char *nome(const Figura *f);
void svuota_riga(void);

int main(void)
{
    Figura figure[MAX_FIGURE];
    int n = 0;
    int esito = 1;
    int massima = 0;
    int i;

    while (esito != 0 && n < MAX_FIGURE) {
        printf("Figura (C r, R b h, T a b c, FINE): ");
        esito = leggi_figura(&figure[n]);
        if (esito != 0) {
            svuota_riga();              /* una figura per riga */
        }
        if (esito == -1) {
            printf("  Figura non riconosciuta.\n");
        } else if (esito == -2) {
            printf("  Misure mancanti.\n");
        } else if (esito == 1 && !valida(&figure[n])) {
            printf("  Misure non valide per un %s.\n", nome(&figure[n]));
        } else if (esito == 1) {
            printf("  %s: area %.2f, perimetro %.2f\n", nome(&figure[n]), area(&figure[n]),
                   perimetro(&figure[n]));
            n++;
        }
    }

    if (n > 0) {
        for (i = 1; i < n; i++) {
            if (area(&figure[i]) > area(&figure[massima])) {
                massima = i;
            }
        }
        printf("Area maggiore: figura %d (%s), %.2f\n", massima + 1, nome(&figure[massima]),
               area(&figure[massima]));
    }

    return 0;
}

/* 1 letta, 0 FINE o fine input, -1 lettera sconosciuta, -2 misure mancanti. */
int leggi_figura(Figura *f)
{
    char lettera[8];
    int esito = -1;

    if (scanf("%7s", lettera) != 1 || strcmp(lettera, "FINE") == 0) {
        esito = 0;
    } else if (strcmp(lettera, "C") == 0) {
        f->tipo = CERCHIO;
        esito = scanf("%lf", &f->dati.cerchio.raggio) == 1 ? 1 : -2;
    } else if (strcmp(lettera, "R") == 0) {
        f->tipo = RETTANGOLO;
        esito = scanf("%lf %lf", &f->dati.rettangolo.base, &f->dati.rettangolo.altezza) == 2
                    ? 1 : -2;
    } else if (strcmp(lettera, "T") == 0) {
        f->tipo = TRIANGOLO;
        esito = scanf("%lf %lf %lf", &f->dati.triangolo.a, &f->dati.triangolo.b,
                      &f->dati.triangolo.c) == 3 ? 1 : -2;
    }
    return esito;
}

int valida(const Figura *f)
{
    int ok = 0;

    switch (f->tipo) {
    case CERCHIO:
        ok = f->dati.cerchio.raggio > 0;
        break;
    case RETTANGOLO:
        ok = f->dati.rettangolo.base > 0 && f->dati.rettangolo.altezza > 0;
        break;
    case TRIANGOLO:
        ok = f->dati.triangolo.a < f->dati.triangolo.b + f->dati.triangolo.c &&
             f->dati.triangolo.b < f->dati.triangolo.a + f->dati.triangolo.c &&
             f->dati.triangolo.c < f->dati.triangolo.a + f->dati.triangolo.b;
        break;
    }
    return ok;
}

double area(const Figura *f)
{
    double risultato = 0;
    double p;

    switch (f->tipo) {
    case CERCHIO:
        risultato = PI_GRECO * f->dati.cerchio.raggio * f->dati.cerchio.raggio;
        break;
    case RETTANGOLO:
        risultato = f->dati.rettangolo.base * f->dati.rettangolo.altezza;
        break;
    case TRIANGOLO:
        p = perimetro(f) / 2;
        risultato = sqrt(p * (p - f->dati.triangolo.a) * (p - f->dati.triangolo.b) *
                         (p - f->dati.triangolo.c));
        break;
    }
    return risultato;
}

double perimetro(const Figura *f)
{
    double risultato = 0;

    switch (f->tipo) {
    case CERCHIO:
        risultato = 2 * PI_GRECO * f->dati.cerchio.raggio;
        break;
    case RETTANGOLO:
        risultato = 2 * (f->dati.rettangolo.base + f->dati.rettangolo.altezza);
        break;
    case TRIANGOLO:
        risultato = f->dati.triangolo.a + f->dati.triangolo.b + f->dati.triangolo.c;
        break;
    }
    return risultato;
}

const char *nome(const Figura *f)
{
    const char *testo = "";

    switch (f->tipo) {
    case CERCHIO:
        testo = "cerchio";
        break;
    case RETTANGOLO:
        testo = "rettangolo";
        break;
    case TRIANGOLO:
        testo = "triangolo";
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
