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
    int quantita;

    /* Indice per rimozione '\n' */
    int i;

    /* Flags di validazione */
    int nome_valido;
    int categoria_valida;

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
    {
        int c;
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
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
    categoria[i] = '\0';

    /* --- LETTURA PREZZO E QUANTITÀ ---
     * Prezzo come stringa per evitare problemi di formato decimale.
     * Quantità come intero. */
    printf("Prezzo (es. 12.50): ");
    scanf("%9s", prezzo);

    printf("Quantità disponibile: ");
    scanf("%d", &quantita);

    /* --- VALIDAZIONE CAMPI OBBLIGATORI ---
     * Nome e categoria non possono essere vuoti. */
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

    if (nome_valido && categoria_valida) {
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
        printf("ERRORE: campi obbligatori mancanti.\n");
        if (!nome_valido) {
            printf("  - Il nome del prodotto non può essere vuoto.\n");
        }
        if (!categoria_valida) {
            printf("  - La categoria non può essere vuota.\n");
        }
        printf("Inserimento annullato.\n");
    }

    return 0;
}
