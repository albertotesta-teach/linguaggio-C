/*
 * 070-problema-cambio-valuta.c
 *
 * Scambio culturale: il cambio delle spese in euro
 *
 * Per lo scambio con le scuole partner gli studenti annotano le spese in
 * valuta locale. Un importo ha senso solo con la sua valuta:
 *
 *     typedef struct {
 *         double valore;
 *         char valuta[4];          "EUR", "GBP", "CHF", "USD"
 *     } Importo;
 *
 *     Importo crea_importo(double valore, const char *valuta);
 *     Importo converti(Importo i, const char *verso, int *ok);
 *
 * converti riceve l'importo per valore e restituisce un Importo nuovo
 * nella valuta richiesta, passando per l'euro: prima valore / cambio della
 * valuta di partenza, poi * cambio della valuta di arrivo. Se una valuta
 * non è nella tabella dei cambi scrive 0 in *ok.
 *
 * Il programma legge le spese (importo e valuta) e stampa ognuna in euro,
 * con il totale del viaggio. Un importo 0 termina.
 */

#include <stdio.h>
#include <string.h>

#define VALUTE 4

typedef struct {
    double valore;
    char valuta[4];
} Importo;

Importo crea_importo(double valore, const char *valuta);
Importo converti(Importo i, const char *verso, int *ok);
double cambio(const char *valuta, int *ok);
void svuota_riga(void);

int main(void)
{
    Importo spesa;
    Importo in_euro;
    Importo totale = {0, "EUR"};
    double valore = 1;
    char valuta[8];
    int ok;
    int letti;

    while (valore != 0) {
        printf("Spesa (importo valuta, 0 per finire): ");
        letti = scanf("%lf", &valore);
        if (letti == EOF) {
            valore = 0;                 /* input terminato: come 0 */
        } else if (letti == 0) {
            svuota_riga();              /* l'importo non e' un numero */
            printf("  Importo non valido.\n");
            valore = 1;                 /* si continua */
        } else if (valore != 0) {
            letti = scanf("%7s", valuta);
            svuota_riga();              /* una spesa per riga */
            if (letti != 1 || strlen(valuta) != 3) {
                printf("  Valuta non valida.\n");
            } else {
                spesa = crea_importo(valore, valuta);
                in_euro = converti(spesa, "EUR", &ok);
                if (ok) {
                    printf("  %.2f %s = %.2f %s\n", spesa.valore, spesa.valuta, in_euro.valore,
                           in_euro.valuta);
                    totale.valore = totale.valore + in_euro.valore;
                } else {
                    printf("  Valuta %s non in tabella.\n", spesa.valuta);
                }
            }
        }
    }
    printf("Totale del viaggio: %.2f %s\n", totale.valore, totale.valuta);

    return 0;
}

Importo crea_importo(double valore, const char *valuta)
{
    Importo i;

    i.valore = valore;
    strcpy(i.valuta, valuta);
    return i;
}

/* Converte passando per l'euro; *ok = 0 se una valuta è sconosciuta. */
Importo converti(Importo i, const char *verso, int *ok)
{
    int ok_da;
    int ok_a;
    double in_euro = i.valore / cambio(i.valuta, &ok_da);

    *ok = ok_da;
    in_euro = in_euro * cambio(verso, &ok_a);
    *ok = *ok && ok_a;
    return crea_importo(in_euro, verso);
}

/* Unità di valuta per 1 euro (cambi indicativi). */
double cambio(const char *valuta, int *ok)
{
    const char *sigle[VALUTE] = {"EUR", "GBP", "CHF", "USD"};
    double per_euro[VALUTE] = {1.0, 0.86, 0.95, 1.08};
    double risultato = 1.0;
    int v = 0;

    while (v < VALUTE && strcmp(sigle[v], valuta) != 0) {
        v++;
    }
    *ok = v < VALUTE;
    if (*ok) {
        risultato = per_euro[v];
    }
    return risultato;
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
