/*
 * 080-problema-media-pesata.c
 *
 * Registro elettronico: la media pesata dei voti
 *
 * Nel registro di informatica ogni voto ha un peso percentuale: una
 * verifica scritta pesa 100, un'interrogazione 50, un esercizio di
 * laboratorio 25. La media pesata è
 *
 *     somma(voto * peso) / somma(peso)
 *
 * Due nomi separano i due ruoli:
 *
 *     typedef double Voto;        da 1 a 10, anche con il mezzo voto (6.5)
 *     typedef int Peso;           percentuale da 1 a 100
 *
 *     Voto media_pesata(const Voto *voti, const Peso *pesi, int n);
 *
 * Il programma legge coppie "voto peso" fino a "0 0" (al massimo 20 voti),
 * scarta le coppie non valide, stampa la media pesata, la media semplice
 * per confronto e l'esito (sufficiente da 6 in su).
 */

#include <stdio.h>

#define MAX_VOTI 20
#define SUFFICIENZA 6.0

typedef double Voto;
typedef int Peso;

Voto media_pesata(const Voto *voti, const Peso *pesi, int n);
Voto media_semplice(const Voto *voti, int n);
void svuota_riga(void);

int main(void)
{
    Voto voti[MAX_VOTI];
    Peso pesi[MAX_VOTI];
    Voto voto = 1;
    Peso peso = 1;
    Voto finale;
    int n = 0;
    int letti;

    while (n < MAX_VOTI && !(voto == 0 && peso == 0)) {
        printf("Voto e peso (0 0 per finire): ");
        /* Voto è double: in scanf serve %lf, il formato del tipo originale */
        letti = scanf("%lf %d", &voto, &peso);
        if (letti == EOF) {
            voto = 0;                   /* input terminato: come 0 0 */
            peso = 0;
        } else if (letti != 2) {
            svuota_riga();              /* non sono due numeri */
            voto = -1;                  /* coppia non valida */
        }
        if (voto >= 1 && voto <= 10 && peso >= 1 && peso <= 100) {
            voti[n] = voto;
            pesi[n] = peso;
            n++;
        } else if (!(voto == 0 && peso == 0)) {
            printf("  Coppia non valida, scartata.\n");
        }
    }

    if (n == 0) {
        printf("Nessun voto inserito.\n");
    } else {
        finale = media_pesata(voti, pesi, n);
        printf("\nVoti inseriti: %d\n", n);
        printf("Media semplice: %.2f\n", media_semplice(voti, n));
        printf("Media pesata:   %.2f  -> %s\n", finale,
               finale >= SUFFICIENZA ? "sufficiente" : "insufficiente");
    }

    return 0;
}

Voto media_pesata(const Voto *voti, const Peso *pesi, int n)
{
    double somma_prodotti = 0;
    int somma_pesi = 0;
    int i;

    for (i = 0; i < n; i++) {
        somma_prodotti = somma_prodotti + voti[i] * pesi[i];
        somma_pesi = somma_pesi + pesi[i];
    }
    return somma_prodotti / somma_pesi;
}

Voto media_semplice(const Voto *voti, int n)
{
    Voto somma = 0;
    int i;

    for (i = 0; i < n; i++) {
        somma = somma + voti[i];
    }
    return somma / n;
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
