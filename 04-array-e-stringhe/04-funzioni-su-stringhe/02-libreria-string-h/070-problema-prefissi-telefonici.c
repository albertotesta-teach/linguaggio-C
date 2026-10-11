/*
 * 070-problema-prefissi-telefonici.c
 *
 * Calcolare il costo delle chiamate internazionali
 *
 * Il centralino di un'azienda registra le chiamate in uscita: per ognuna il
 * numero composto (in formato internazionale, senza spazi) e la durata in
 * minuti. Il tariffario è formato da tre array paralleli:
 *
 *     prefissi[]   "+39", "+393", "+33", ...
 *     zone[]       "Italia fisso", "Italia mobile", "Francia", ...
 *     tariffe[]    costo al minuto in centesimi
 *
 * Per riconoscere la zona si confronta l'inizio del numero con ogni
 * prefisso usando strncmp(numero, prefisso, strlen(prefisso)).
 * Alcuni prefissi sono l'inizio di altri: "+393..." (cellulari italiani)
 * comincia anche con "+39". Per questo si sceglie il prefisso PIÙ LUNGO tra
 * quelli che corrispondono.
 *
 * Il programma stampa il dettaglio delle chiamate, il totale per zona e
 * segnala i numeri con prefisso non presente nel tariffario.
 */

#include <stdio.h>
#include <string.h>

#define ZONE     8
#define CHIAMATE 9
#define LUNG_PREF 6
#define LUNG_ZONA 16
#define LUNG_NUM  20

int cerca_zona(const char numero[], const char prefissi[][LUNG_PREF], int n);

int main(void)
{
    char prefissi[ZONE][LUNG_PREF] = {
        "+39", "+393", "+33", "+34", "+41", "+44", "+49", "+1"
    };
    char zone[ZONE][LUNG_ZONA] = {
        "Italia fisso", "Italia mobile", "Francia", "Spagna",
        "Svizzera", "Regno Unito", "Germania", "USA/Canada"
    };
    int tariffe[ZONE] = {2, 5, 9, 9, 15, 12, 9, 18};

    char numeri[CHIAMATE][LUNG_NUM] = {
        "+390131220145", "+393471234567", "+33142685300", "+41223456789",
        "+12125550198", "+393289876543", "+81312345678", "+4930123456",
        "+390112345678"
    };
    int minuti[CHIAMATE] = {12, 5, 8, 20, 15, 3, 10, 6, 25};

    int minuti_zona[ZONE] = {0};
    int k;
    int z;
    int costo;
    int totale = 0;
    int sconosciute = 0;

    printf("=== DETTAGLIO DELLE CHIAMATE ===\n");
    printf("  %-15s %-14s %5s %9s\n", "Numero", "Zona", "Min", "Costo");
    for (k = 0; k < CHIAMATE; k++) {
        z = cerca_zona(numeri[k], prefissi, ZONE);
        if (z == -1) {
            printf("  %-15s %-14s %5d %9s\n", numeri[k], "?", minuti[k], "-");
            sconosciute++;
        } else {
            costo = minuti[k] * tariffe[z];
            minuti_zona[z] = minuti_zona[z] + minuti[k];
            totale = totale + costo;
            printf("  %-15s %-14s %5d %6d.%02d\n", numeri[k], zone[z], minuti[k],
                   costo / 100, costo % 100);
        }
    }

    printf("\n=== TOTALE PER ZONA ===\n");
    for (z = 0; z < ZONE; z++) {
        if (minuti_zona[z] > 0) {
            costo = minuti_zona[z] * tariffe[z];
            printf("  %-14s %4d min  %3d.%02d euro\n", zone[z], minuti_zona[z],
                   costo / 100, costo % 100);
        }
    }
    printf("  Totale da addebitare: %d.%02d euro\n", totale / 100, totale % 100);
    if (sconosciute > 0) {
        printf("  %d %s con prefisso non in tariffario: da verificare\n", sconosciute,
               sconosciute == 1 ? "chiamata" : "chiamate");
    }

    return 0;
}

/* Restituisce l'indice del prefisso più lungo con cui inizia numero,
 * oppure -1 se nessun prefisso corrisponde. */
int cerca_zona(const char numero[], const char prefissi[][LUNG_PREF], int n)
{
    int k;
    int migliore = -1;
    int lung;

    for (k = 0; k < n; k++) {
        lung = (int) strlen(prefissi[k]);
        if (strncmp(numero, prefissi[k], lung) == 0) {
            if (migliore == -1 || lung > (int) strlen(prefissi[migliore])) {
                migliore = k;
            }
        }
    }
    return migliore;
}
