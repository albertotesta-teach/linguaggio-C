/*
 * 100-problema-censura-testo.c
 *
 * Problema reale: sistema di moderazione e censura automatica.
 *
 * Scenario: una piattaforma di messaggistica deve censurare automaticamente
 * parole non consentite nei messaggi degli utenti, sostituendo ogni
 * carattere della parola vietata con '*'. La sostituzione avviene
 * direttamente nella stringa, modificando i caratteri per indice.
 *
 * Algoritmo:
 * Per ogni posizione del testo, si verifica se la parola vietata
 * inizia in quella posizione confrontando i caratteri uno a uno.
 * Se corrisponde, si sovrascrivono i caratteri con '*'.
 *
 * Esempio:
 *   testo:   "questo prodotto e' pessimo davvero"
 *   vietata: "pessimo"
 *   output:  "questo prodotto e' ******* davvero"
 *
 * Concetti applicati:
 *   - lettura di stringhe con fgets e scanf
 *   - accesso e modifica di caratteri per indice
 *   - ciclo while annidato per il confronto e la sostituzione
 *   - variabile di stato per tracciare le corrispondenze trovate
 */

#include <stdio.h>

int main(void) {

    /* Buffer per il testo da moderare */
    char testo[201];

    /* Parola vietata da cercare e censurare */
    char vietata[31]; /* max 30 caratteri + '\0' */

    /* Lunghezza della parola vietata (calcolata manualmente) */
    int lung_vietata = 0;

    /* Numero di sostituzioni effettuate */
    int sostituzioni = 0;

    /* Indici per la scansione */
    int i; /* posizione nel testo */
    int j; /* posizione nella parola vietata durante il confronto */

    /* Flag: 1 se la parola vietata corrisponde a partire dalla posizione i */
    int corrispondenza;

    /* Indice temporaneo per la sostituzione */
    int k;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║     SISTEMA DI MODERAZIONE TESTO         ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");

    /* --- LETTURA TESTO ---
     * fgets per permettere spazi nel testo da moderare. */
    printf("Inserisci il messaggio da controllare:\n> ");
    fgets(testo, 201, stdin);

    /* Rimozione '\n' */
    i = 0;
    while (testo[i] != '\n' && testo[i] != '\0') {
        i++;
    }
    testo[i] = '\0';

    /* --- LETTURA PAROLA VIETATA ---
     * scanf senza spazi: la parola vietata è una singola parola. */
    printf("Inserisci la parola da censurare: ");
    scanf("%30s", vietata);

    /* --- CALCOLO LUNGHEZZA PAROLA VIETATA ---
     * Necessaria per sapere quanti caratteri sostituire
     * e quanti caratteri confrontare ad ogni posizione. */
    j = 0;
    while (vietata[j] != '\0') {
        lung_vietata++;
        j++;
    }

    /* --- SCANSIONE E SOSTITUZIONE ---
     * Per ogni posizione i del testo, confrontiamo i caratteri
     * successivi con la parola vietata.
     * Se corrisponde, sostituiamo i caratteri con '*'. */
    i = 0;
    while (testo[i] != '\0') {

        /* Confronto: verifichiamo se la parola vietata inizia in posizione i.
         * Scorriamo j caratteri finché corrispondono o troviamo differenza. */
        j = 0;
        corrispondenza = 1; /* assumiamo corrispondenza, falsifichiamo se diversi */

        while (j < lung_vietata && corrispondenza) {
            /* Se il carattere del testo è '\0' oppure diverso
             * dalla parola vietata, non c'è corrispondenza. */
            if (testo[i + j] == '\0' || testo[i + j] != vietata[j]) {
                corrispondenza = 0;
            }
            j++;
        }

        /* Se c'è corrispondenza: sostituiamo i caratteri con '*' */
        if (corrispondenza) {
            k = 0;
            while (k < lung_vietata) {
                testo[i + k] = '*'; /* sovrascrittura diretta per indice */
                k++;
            }
            sostituzioni++;
            i += lung_vietata; /* saltiamo oltre la parola appena censurata */
        } else {
            i++; /* nessuna corrispondenza: avanza di un carattere */
        }
    }

    /* --- OUTPUT RISULTATO --- */
    printf("\n");
    printf("════════════════════════════════════════════\n");
    printf("  RISULTATO MODERAZIONE\n");
    printf("════════════════════════════════════════════\n");
    printf("  Parola censurata : \"%s\"\n", vietata);
    printf("  Sostituzioni     : %d\n", sostituzioni);
    printf("  Testo moderato   :\n  \"%s\"\n", testo);
    printf("════════════════════════════════════════════\n");

    if (sostituzioni == 0) {
        printf("\nNessuna occorrenza trovata: messaggio approvato.\n");
    } else {
        printf("\nTesto modificato: %d occorrenza/e censurata/e.\n",
               sostituzioni);
    }

    return 0;
}
