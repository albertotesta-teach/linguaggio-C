/*
 * 050-problema-copia-di-un-file.c
 *
 * Copiare un file di testo carattere per carattere
 *
 * Prima di modificare il diario delle uscite il coordinatore vuole
 * tenerne una copia. Il programma chiede il nome del file da copiare e
 * quello della copia, poi apre DUE file insieme:
 *
 *     origine      = fopen(nome_origine, "r")       deve esistere
 *     destinazione = fopen(nome_copia, "w")         creato o svuotato
 *
 *     c = fgetc(origine)
 *     finché c != EOF:
 *         fputc(c, destinazione)
 *         c = fgetc(origine)
 *
 * Le precauzioni:
 *   - lo stesso nome per origine e copia è rifiutato: aprire il file in
 *     "w" lo svuoterebbe prima di leggerlo, e il contenuto andrebbe perso;
 *   - si apre prima l'origine: se non esiste, la copia non viene creata;
 *   - se la copia non si può creare, si chiude l'origine già aperta;
 *   - se la copia esiste già, si chiede conferma prima di sovrascriverla.
 *
 * Alla fine il programma stampa quanti caratteri e quante righe ha copiato.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int esiste(const char *nome);

int main(void)
{
    FILE *origine = NULL;
    FILE *destinazione = NULL;
    char nome_origine[60];
    char nome_copia[60];
    char risposta = 's';
    int caratteri = 0;
    int righe = 0;
    int letti;
    int c;
    int ultimo = '\n';

    printf("File da copiare: ");
    letti = scanf("%59s", nome_origine);
    if (letti == 1) {
        printf("Nome della copia: ");
        letti = scanf("%59s", nome_copia);
    }
    while (letti == 1 && strcmp(nome_origine, nome_copia) == 0) {
        printf("  la copia deve avere un nome diverso\nNome della copia: ");
        letti = scanf("%59s", nome_copia);
    }

    if (letti == 1) {
        origine = fopen(nome_origine, "r");
        if (origine == NULL) {
            fprintf(stderr, "Impossibile leggere %s\n", nome_origine);
        } else if (esiste(nome_copia)) {
            printf("%s esiste gia': sovrascrivere? (s/n) ", nome_copia);
            if (scanf(" %c", &risposta) != 1) {
                risposta = 'n';
            }
            risposta = (char) tolower((unsigned char) risposta);
        }
    }
    if (origine != NULL && risposta == 's') {
        destinazione = fopen(nome_copia, "w");
        if (destinazione == NULL) {
            fprintf(stderr, "Impossibile creare %s\n", nome_copia);
        }
    }

    if (destinazione != NULL) {
        c = fgetc(origine);
        while (c != EOF) {
            fputc(c, destinazione);
            caratteri++;
            if (c == '\n') {
                righe++;
            }
            ultimo = c;
            c = fgetc(origine);
        }
        if (ultimo != '\n') {
            righe++;    /* ultima riga senza a capo */
        }
        fclose(destinazione);
        printf("Copiati %d caratteri e %d righe da %s a %s\n", caratteri, righe, nome_origine,
               nome_copia);
    } else if (origine != NULL) {
        printf("Copia annullata.\n");
    }
    if (origine != NULL) {
        fclose(origine);
    }

    return 0;
}

/* 1 se il file si può aprire in lettura. */
int esiste(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int trovato = f != NULL;

    if (trovato) {
        fclose(f);
    }
    return trovato;
}
