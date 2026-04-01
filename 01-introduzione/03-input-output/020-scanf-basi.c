/*
 * 020-scanf-basi.c
 *
 * Basi di scanf
 *
 * Introduce scanf per la lettura di dati da tastiera. Spiega la sintassi
 * con l'operatore & (indirizzo della variabile), mostra gli specificatori
 * di formato per i tipi principali e accenna al problema del carattere
 * residuo nel buffer quando si legge un char dopo un intero.
 *
 * Nota: & viene spiegato come "dove salvare il dato". La teoria completa
 * dei puntatori è trattata nel capitolo 05.
 */

#include <stdio.h>

int main(void)
{
    /* variabili che riceveranno i dati dell'utente */
    int    eta;
    double altezza;
    double peso;
    char   sesso;    /* 'M' o 'F' come carattere singolo */
    int    anno;

    /* ── lettura di un intero ────────────────────────────────────────────── */
    /* scanf riceve la stringa di formato e l'INDIRIZZO della variabile.
     * L'operatore & davanti al nome significa: "passa a scanf il posto
     * in memoria dove salvare il valore letto".
     * Senza & il programma si comporta in modo imprevedibile. */
    printf("Eta' (anni): ");
    scanf("%d", &eta);

    /* ── lettura di un double ────────────────────────────────────────────── */
    /* ATTENZIONE: in scanf si usa %lf per double, non %f.
     * %f in scanf è riservato al tipo float.
     * In printf invece sia %f che %lf stampano un double correttamente. */
    printf("Altezza (es. 1.75): ");
    scanf("%lf", &altezza);

    printf("Peso in kg (es. 70.5): ");
    scanf("%lf", &peso);

    /* ── lettura di un char dopo un intero ───────────────────────────────── */
    /* Dopo aver letto un intero con %d, nel buffer di input rimane
     * il carattere '\n' (invio) che l'utente ha premuto.
     * Se si legge subito un char con %c, scanf leggerebbe quel '\n'
     * invece del carattere desiderato.
     * SOLUZIONE: inserire uno spazio prima di %c nella stringa di formato.
     * Lo spazio dice a scanf di saltare tutti i caratteri "bianchi"
     * (spazi, tab, newline) prima di leggere il carattere. */
    printf("Sesso (M/F): ");
    scanf(" %c", &sesso);   /* lo spazio prima di %c è intenzionale */

    printf("Anno di nascita: ");
    scanf("%d", &anno);

    /* ── riepilogo dei dati inseriti ─────────────────────────────────────── */
    printf("\n--- Dati inseriti ---\n");
    printf("Eta':            %d anni\n",  eta);
    printf("Altezza:         %.2f m\n",   altezza);
    printf("Peso:            %.1f kg\n",  peso);
    printf("Sesso:           %c\n",       sesso);
    printf("Anno di nascita: %d\n",       anno);

    /* ── errori comuni (solo in commento) ───────────────────────────────── */
    /*
     * ERRORE 1: dimenticare &
     *   scanf("%d", eta);    // comportamento indefinito: eta non è un indirizzo
     *   scanf("%d", &eta);   // corretto
     *
     * ERRORE 2: usare %f per double in scanf
     *   scanf("%f", &altezza);    // sbagliato: altezza è double, non float
     *   scanf("%lf", &altezza);   // corretto
     *
     * ERRORE 3: non gestire il '\n' residuo prima di %c
     *   scanf("%d", &eta);
     *   scanf("%c", &sesso);    // legge '\n', non il carattere voluto
     *   scanf(" %c", &sesso);   // corretto: lo spazio salta i caratteri bianchi
     */

    return 0;
}
