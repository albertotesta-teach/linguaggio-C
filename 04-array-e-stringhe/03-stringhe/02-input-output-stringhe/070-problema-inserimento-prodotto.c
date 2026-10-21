/*
 * 070-problema-inserimento-prodotto.c
 *
 * Problema reale: terminale di inserimento prodotti per un magazzino.
 *
 * Scenario: un operatore di magazzino usa un terminale per inserire
 * nuovi prodotti nell'archivio. Il terminale legge il nome del prodotto
 * (che può contenere spazi, es. "Cavo HDMI 2m") e la categoria merceologica.
 * Prima di salvare, verifica che i campi non siano stati lasciati vuoti.
 *
 * Concetti applicati:
 *   - lettura di stringhe con spazi tramite fgets
 *   - lettura di token senza spazi tramite scanf
 *   - rimozione del '\n' lasciato da fgets
 *   - verifica campi obbligatori (non vuoti)
 *   - output formattato della scheda prodotto
 */

#include <stdio.h>

int main(void) {

    /* Campi della scheda prodotto */
    char nome_prodotto[81];  /* max 80 caratteri + '\0' */
    char categoria[21];      /* max 20 caratteri + '\0' */
    char codice[10];         /* formato XXX-NNN, max 9 caratteri + '\0' */

    /* Prezzo come stringa (evita problemi con virgola/punto decimale) */
    char prezzo[10];         /* es. "12.50", max 9 caratteri + '\0' */

    /* Quantità disponibile a magazzino */
    int quantita = 0;

    /* Indice per rimozione '\n' */
    int i;

    /* Carattere letto per svuotare il buffer di input */
    int c;

    /* Flags di validazione */
    int nome_valido;
    int categoria_valida;
    int quantita_valida;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║    TERMINALE INSERIMENTO PRODOTTI        ║\n");
    printf("║    Magazzino Centrale - Reparto IT       ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");

    /* --- LETTURA CODICE PRODOTTO ---
     * Il codice non contiene spazi: scanf è appropriato. */
    printf("Codice prodotto (es. ELE-042): ");
    scanf("%9s", codice);

    /* Svuota il buffer di input dopo scanf per prepararsi a fgets.
     * scanf lascia '\n' nel buffer: dobbiamo consumarlo. */
    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }

    /* --- LETTURA NOME PRODOTTO ---
     * Il nome può contenere spazi: usiamo fgets. */
    printf("Nome prodotto (es. Cavo HDMI 2m): ");
    fgets(nome_prodotto, 81, stdin);

    /* Rimozione '\n' dal nome prodotto */
    i = 0;
    while (nome_prodotto[i] != '\n' && nome_prodotto[i] != '\0') {
        i++;
    }
    /* Se fgets ha riempito il buffer senza leggere '\n', il nome era
     * più lungo di 80 caratteri: si scarta il resto della riga, altrimenti
     * finirebbe nel campo successivo. */
    if (nome_prodotto[i] == '\0' && i == 80) {
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }
    nome_prodotto[i] = '\0';

    /* --- LETTURA CATEGORIA ---
     * La categoria può contenere spazi (es. "Elettronica Consumer"). */
    printf("Categoria merceologica: ");
    fgets(categoria, 21, stdin);

    /* Rimozione '\n' dalla categoria */
    i = 0;
    while (categoria[i] != '\n' && categoria[i] != '\0') {
        i++;
    }
    /* Stesso controllo per la categoria (al massimo 20 caratteri). */
    if (categoria[i] == '\0' && i == 20) {
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }
    categoria[i] = '\0';

    /* --- LETTURA PREZZO E QUANTITÀ ---
     * Prezzo come stringa per evitare problemi di formato decimale.
     * Quantità come intero. */
    printf("Prezzo (es. 12.50): ");
    scanf("%9s", prezzo);

    printf("Quantità disponibile: ");
    if (scanf("%d", &quantita) == 1 && quantita >= 0) {
        quantita_valida = 1;
    } else {
        quantita_valida = 0;
    }

    /* --- VALIDAZIONE CAMPI OBBLIGATORI ---
     * Nome e categoria non possono essere vuoti; la quantità deve essere
     * un intero non negativo (la sua validità è già stata controllata). */
    if (nome_prodotto[0] == '\0') {
        nome_valido = 0;
    } else {
        nome_valido = 1;
    }

    if (categoria[0] == '\0') {
        categoria_valida = 0;
    } else {
        categoria_valida = 1;
    }

    /* --- OUTPUT SCHEDA PRODOTTO ---
     * Solo se tutti i campi obbligatori sono validi. */
    printf("\n");

    if (nome_valido && categoria_valida && quantita_valida) {
        printf("════════════════════════════════════════════════\n");
        printf("  SCHEDA PRODOTTO - PRONTA PER L'ARCHIVIAZIONE \n");
        printf("════════════════════════════════════════════════\n");
        printf("  Codice      : %s\n",   codice);
        printf("  Nome        : %s\n",   nome_prodotto);
        printf("  Categoria   : %s\n",   categoria);
        printf("  Prezzo      : %s EUR\n", prezzo);
        printf("  Disponibile : %d pz\n", quantita);
        printf("════════════════════════════════════════════════\n");
        printf("\nProdotto inserito correttamente nell'archivio.\n");
    } else {
        printf("ERRORE: campi obbligatori mancanti o non validi.\n");
        if (!nome_valido) {
            printf("  - Il nome del prodotto non può essere vuoto.\n");
        }
        if (!categoria_valida) {
            printf("  - La categoria non può essere vuota.\n");
        }
        if (!quantita_valida) {
            printf("  - La quantità deve essere un numero intero non negativo.\n");
        }
        printf("Inserimento annullato.\n");
    }

    return 0;
}
