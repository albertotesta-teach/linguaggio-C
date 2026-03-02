/*
 * 020-input-con-scanf.c
 *
 * Lettura di stringhe da tastiera con scanf.
 *
 * scanf con il formato "%s" legge una sequenza di caratteri fino al
 * primo spazio, tabulazione o invio. È semplice da usare ma ha
 * limitazioni importanti che uno studente deve conoscere:
 *
 *   1. Non legge stringhe con spazi (si ferma al primo spazio)
 *   2. Non limita automaticamente i caratteri letti: se l'utente
 *      digita più caratteri del previsto, si va oltre i limiti
 *      dell'array (buffer overflow)
 *
 * Per limitare i caratteri letti si usa il modificatore di larghezza:
 *   scanf("%9s", buffer)  → legge al massimo 9 caratteri (+ '\0')
 */

#include <stdio.h>

int main(void) {

    /* Buffer per il nome utente: 20 caratteri + '\0' */
    char nome[21];

    /* Buffer per il cognome: 30 caratteri + '\0' */
    char cognome[31];

    /* Buffer per il codice utente (senza spazi): 8 caratteri + '\0' */
    char codice[9];

    /* --- LETTURA BASE CON scanf ---
     * "%s" legge fino al primo spazio.
     * Nota: con scanf non si usa & davanti al nome dell'array
     * perché il nome dell'array è già un indirizzo (lo vedremo
     * in dettaglio nella sezione sui puntatori). */
    printf("=== LETTURA DATI UTENTE CON scanf ===\n\n");

    printf("Inserisci il tuo nome (senza spazi): ");
    scanf("%20s", nome);     /* legge al massimo 20 caratteri */

    printf("Inserisci il tuo cognome (senza spazi): ");
    scanf("%30s", cognome);  /* legge al massimo 30 caratteri */

    printf("Inserisci il tuo codice utente (es. USR00042): ");
    scanf("%8s", codice);    /* legge al massimo 8 caratteri */

    /* Stampa i dati letti in una scheda formattata */
    printf("\n");
    printf("==============================\n");
    printf("  SCHEDA UTENTE              \n");
    printf("==============================\n");
    printf("Nome        : %s\n", nome);
    printf("Cognome     : %s\n", cognome);
    printf("Codice      : %s\n", codice);
    printf("==============================\n");
    printf("\n");

    /* --- LIMITAZIONE DI scanf con %s ---
     * Se l'utente inserisce "Mario Rossi" (con spazio),
     * scanf legge solo "Mario" e lascia " Rossi" nel buffer
     * di input. Questo causa problemi nelle letture successive.
     *
     * DIMOSTRAZIONE: proviamo a leggere due parole separate
     * con una sola chiamata a scanf → verrà letta solo la prima. */
    printf("--- Dimostrazione del limite di scanf ---\n");
    printf("Inserisci nome e cognome separati da spazio: ");

    /* Svuota il buffer di input dai caratteri rimasti dalla lettura
     * precedente (il '\n' dell'ultimo invio).
     * getchar() legge e scarta un carattere alla volta finché
     * non trova '\n' o la fine del file. */
    {
        int c;
        c = getchar(); /* legge il '\n' rimasto nel buffer */
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }

    /* Ora leggiamo: scanf si fermerà al primo spazio */
    scanf("%20s", nome);
    printf("scanf ha letto solo: \"%s\"\n", nome);
    printf("(il cognome è rimasto nel buffer di input)\n");
    printf("\n");

    /* --- QUANDO USARE scanf ---
     * scanf con %s è adatto quando:
     *   - si sa con certezza che l'input non contiene spazi
     *     (codici, username, password, numeri scritti come testo)
     *   - si vuole leggere token separati da spazi in sequenza
     *
     * Per stringhe con spazi (nomi completi, indirizzi, frasi)
     * è preferibile usare fgets, come mostrato in 030-input-con-fgets.c */
    printf("NOTA: per leggere stringhe con spazi, usa fgets.\n");
    printf("Vedi 030-input-con-fgets.c per gli esempi.\n");

    return 0;
}
