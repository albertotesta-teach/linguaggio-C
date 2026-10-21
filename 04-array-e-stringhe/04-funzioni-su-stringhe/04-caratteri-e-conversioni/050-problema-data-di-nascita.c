/*
 * 050-problema-data-di-nascita.c
 *
 * Leggere e controllare una data scritta come testo
 *
 * Nel modulo di iscrizione la data di nascita si scrive nel formato
 * gg/mm/aaaa. La riga letta è una stringa: per ricavare i tre numeri si usa
 * sscanf, che restituisce quanti valori ha convertito.
 *
 *     letti = sscanf(riga, "%d/%d/%d%c", &g, &m, &a, &resto);
 *
 *   - letti == 3   formato corretto (il %c finale non ha trovato nulla)
 *   - letti == 4   dopo la data c'è altro testo ("12/05/2010 ore 8")
 *   - letti <  3   la riga non ha la forma gg/mm/aaaa
 *
 * Poi si controllano i valori: anno tra 1900 e ANNO_CORRENTE, mese tra 1 e
 * 12, giorno compatibile con il mese, tenendo conto degli anni bisestili
 * (divisibili per 4, ma non per 100 a meno che lo siano per 400).
 *
 * Se la data è valida viene riscritta per esteso con snprintf
 * ("12 maggio 2010") e si calcola l'età compiuta alla data di riferimento.
 */

#include <stdio.h>
#include <string.h>

#define DIM            40
#define ANNO_CORRENTE  2026
#define MESE_CORRENTE  10
#define GIORNO_CORRENTE 11

int leggi_riga(char s[], int dim);
int bisestile(int anno);
int giorni_del_mese(int mese, int anno);

int main(void)
{
    char nomi_mesi[12][10] = {
        "gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno",
        "luglio", "agosto", "settembre", "ottobre", "novembre", "dicembre"
    };
    char riga[DIM];
    char per_esteso[DIM];
    int letta;
    int letti;
    int g;
    int m;
    int a;
    int eta;
    char resto;

    printf("=== DATA DI NASCITA (riferimento %02d/%02d/%d) ===\n",
           GIORNO_CORRENTE, MESE_CORRENTE, ANNO_CORRENTE);
    printf("Data gg/mm/aaaa (riga vuota per terminare): ");
    letta = leggi_riga(riga, DIM);

    while (letta && riga[0] != '\0') {
        letti = sscanf(riga, "%d/%d/%d%c", &g, &m, &a, &resto);

        if (letti < 3) {
            printf("  Formato non valido: usare gg/mm/aaaa\n");
        } else if (letti == 4) {
            printf("  Testo in piu' dopo la data\n");
        } else if (a < 1900 || a > ANNO_CORRENTE) {
            printf("  Anno %d fuori dall'intervallo 1900-%d\n", a, ANNO_CORRENTE);
        } else if (m < 1 || m > 12) {
            printf("  Il mese %d non esiste\n", m);
        } else if (g < 1 || g > giorni_del_mese(m, a)) {
            printf("  %s %d ha %d giorni\n", nomi_mesi[m - 1], a, giorni_del_mese(m, a));
        } else if (a == ANNO_CORRENTE &&
                   (m > MESE_CORRENTE || (m == MESE_CORRENTE && g > GIORNO_CORRENTE))) {
            printf("  La data e' successiva a quella di riferimento\n");
        } else {
            snprintf(per_esteso, sizeof(per_esteso), "%d %s %d", g, nomi_mesi[m - 1], a);
            eta = ANNO_CORRENTE - a;
            if (m > MESE_CORRENTE || (m == MESE_CORRENTE && g > GIORNO_CORRENTE)) {
                eta--;                  /* compleanno non ancora arrivato */
            }
            printf("  Data valida: %s, eta' %d anni\n", per_esteso, eta);
        }
        printf("Data gg/mm/aaaa (riga vuota per terminare): ");
        letta = leggi_riga(riga, DIM);
    }

    return 0;
}

int leggi_riga(char s[], int dim)
{
    int ok = 0;
    int n;
    int c;

    if (fgets(s, dim, stdin) != NULL) {
        ok = 1;
        n = (int) strlen(s);
        if (n > 0 && s[n - 1] == '\n') {
            s[n - 1] = '\0';
        } else {
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    return ok;
}

int bisestile(int anno)
{
    return (anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0;
}

int giorni_del_mese(int mese, int anno)
{
    int giorni = 31;

    if (mese == 4 || mese == 6 || mese == 9 || mese == 11) {
        giorni = 30;
    } else if (mese == 2) {
        giorni = bisestile(anno) ? 29 : 28;
    }
    return giorni;
}
