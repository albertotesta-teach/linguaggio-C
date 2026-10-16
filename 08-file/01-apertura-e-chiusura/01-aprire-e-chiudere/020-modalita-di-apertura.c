/*
 * 020-modalita-di-apertura.c
 *
 * Le modalità di apertura: r, w, a e le varianti con +
 *
 * Il secondo argomento di fopen dice che cosa si vuole fare del file:
 *
 *     modalità  file esistente           file inesistente   operazioni
 *     "r"       letto dall'inizio        NULL               lettura
 *     "w"       SVUOTATO                 creato             scrittura
 *     "a"       scrittura in fondo       creato             scrittura
 *     "r+"      letto dall'inizio        NULL               lett. e scritt.
 *     "w+"      SVUOTATO                 creato             lett. e scritt.
 *     "a+"      scrittura in fondo       creato             lett. e scritt.
 *
 * "w" cancella il contenuto precedente senza chiedere nulla: è la
 * modalità più pericolosa. "a" (append) aggiunge sempre in fondo e non
 * perde nulla. Le varianti con + servono quando si legge e si scrive lo
 * stesso file e richiedono il posizionamento (04-posizionamento-nel-file).
 *
 * Su Windows esiste anche la distinzione tra file di testo e file
 * binari ("rb", "wb"): si vedrà in 03-lettura-e-scrittura-binaria.
 *
 * Il programma scrive nello stesso file prima con "w", poi di nuovo con
 * "w", poi con "a", e stampa il contenuto dopo ogni passo; infine prova
 * ad aprire in "r" un file che non esiste.
 */

#include <stdio.h>

int scrivi(const char *nome, const char *modalita, const char *testo);
void stampa(const char *nome);

int main(void)
{
    FILE *f;

    printf("1. fopen(\"modalita.txt\", \"w\") e scrittura di \"prima riga\"\n");
    if (scrivi("modalita.txt", "w", "prima riga\n")) {
        stampa("modalita.txt");
    }
    printf("2. fopen(\"modalita.txt\", \"w\") e scrittura di \"seconda riga\"\n");
    if (scrivi("modalita.txt", "w", "seconda riga\n")) {
        stampa("modalita.txt");
    }
    printf("3. fopen(\"modalita.txt\", \"a\") e scrittura di \"terza riga\"\n");
    if (scrivi("modalita.txt", "a", "terza riga\n")) {
        stampa("modalita.txt");
    }
    printf("4. fopen(\"mancante.txt\", \"r\")\n");
    f = fopen("mancante.txt", "r");
    if (f == NULL) {
        printf("   NULL: in lettura il file deve esistere\n");
    } else {
        printf("   aperto (il file esiste gia')\n");
        fclose(f);
    }

    return 0;
}

/* Apre con la modalità indicata e scrive il testo; 0 se non si apre. */
int scrivi(const char *nome, const char *modalita, const char *testo)
{
    FILE *f = fopen(nome, modalita);
    int ok = f != NULL;

    if (!ok) {
        fprintf(stderr, "   impossibile aprire %s in modalita' %s\n", nome, modalita);
    } else {
        fputs(testo, f);
        fclose(f);
    }
    return ok;
}

/* Stampa il file rientrato di tre spazi, una riga sotto l'altra. */
void stampa(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int c;
    int inizio_riga = 1;

    if (f == NULL) {
        fprintf(stderr, "   impossibile leggere %s\n", nome);
    } else {
        printf("   contenuto:\n");
        c = fgetc(f);
        while (c != EOF) {
            if (inizio_riga) {
                printf("     | ");
            }
            putchar(c);
            inizio_riga = c == '\n';
            c = fgetc(f);
        }
        fclose(f);
    }
}
