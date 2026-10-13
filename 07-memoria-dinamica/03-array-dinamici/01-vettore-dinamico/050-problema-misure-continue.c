/*
 * 050-problema-misure-continue.c
 *
 * La centralina del rumore in mensa: letture fino al comando di stop
 *
 * Durante il pranzo una centralina misura il rumore in mensa (in
 * decibel) ogni minuto, finché il responsabile non scrive STOP. Le
 * letture vanno in un vettore dinamico di double:
 *
 *     typedef struct {
 *         double *dati;
 *         int n;
 *         int capacita;
 *     } Serie;
 *
 * Dopo lo stop il programma stampa:
 *   - la media mobile su 5 minuti, cioè per ogni minuto dal quinto in
 *     poi la media delle ultime 5 letture: attenua i picchi isolati;
 *   - il massimo e il minuto in cui è stato registrato;
 *   - i minuti con media mobile sopra 80 dB (rumore da ridurre).
 *
 * Una lettura non valida (negativa o non numerica diversa da STOP) viene
 * scartata.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FINESTRA 5
#define SOGLIA 80.0

typedef struct {
    double *dati;
    int n;
    int capacita;
} Serie;

Serie *crea_serie(int capacita);
int aggiungi(Serie *s, double valore);
int lunghezza(const Serie *s);
double elemento(const Serie *s, int i);
void distruggi_serie(Serie *s);
double media_mobile(const Serie *s, int fine);

int main(void)
{
    Serie *rumore = crea_serie(8);
    char parola[16];
    char dopo;
    double valore;
    double media;
    int finito = 0;
    int massimo = 0;
    int sopra = 0;
    int i;

    if (rumore == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("Letture in dB (STOP per terminare):\n");
        while (!finito) {
            if (scanf("%15s", parola) != 1 || strcmp(parola, "STOP") == 0) {
                finito = 1;
            } else if (sscanf(parola, "%lf%c", &valore, &dopo) != 1 || valore < 0) {
                printf("  %s scartata\n", parola);
            } else if (!aggiungi(rumore, valore)) {
                printf("Memoria insufficiente.\n");
                finito = 1;
            }
        }

        printf("\nLetture: %d\n", lunghezza(rumore));
        for (i = 0; i < lunghezza(rumore); i++) {
            if (elemento(rumore, i) > elemento(rumore, massimo)) {
                massimo = i;
            }
        }
        if (lunghezza(rumore) > 0) {
            printf("Massimo: %.1f dB al minuto %d\n", elemento(rumore, massimo), massimo + 1);
        }
        printf("Media mobile su %d minuti:\n", FINESTRA);
        for (i = FINESTRA - 1; i < lunghezza(rumore); i++) {
            media = media_mobile(rumore, i);
            printf("  minuto %2d: %5.1f", i + 1, media);
            if (media > SOGLIA) {
                printf("  troppo rumore");
                sopra++;
            }
            printf("\n");
        }
        if (lunghezza(rumore) < FINESTRA) {
            printf("  servono almeno %d letture\n", FINESTRA);
        }
        printf("Minuti sopra %.0f dB (media mobile): %d\n", SOGLIA, sopra);
        distruggi_serie(rumore);
    }

    return 0;
}

Serie *crea_serie(int capacita)
{
    Serie *s = malloc(sizeof *s);

    if (s != NULL) {
        s->dati = malloc(capacita * sizeof *s->dati);
        if (s->dati == NULL) {
            free(s);
            s = NULL;
        } else {
            s->n = 0;
            s->capacita = capacita;
        }
    }
    return s;
}

int aggiungi(Serie *s, double valore)
{
    double *tmp;
    int ok = 1;

    if (s->n == s->capacita) {
        tmp = realloc(s->dati, 2 * s->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            s->dati = tmp;
            s->capacita = 2 * s->capacita;
        }
    }
    if (ok) {
        s->dati[s->n] = valore;
        s->n++;
    }
    return ok;
}

int lunghezza(const Serie *s)
{
    return s->n;
}

double elemento(const Serie *s, int i)
{
    return s->dati[i];
}

void distruggi_serie(Serie *s)
{
    if (s != NULL) {
        free(s->dati);
        free(s);
    }
}

/* Media delle FINESTRA letture che finiscono in fine (>= FINESTRA - 1). */
double media_mobile(const Serie *s, int fine)
{
    double somma = 0;
    int i;

    for (i = fine - FINESTRA + 1; i <= fine; i++) {
        somma = somma + elemento(s, i);
    }
    return somma / FINESTRA;
}
