/*
 * 070-problema-copie-di-sicurezza.c
 *
 * Copie di sicurezza a rotazione prima di ogni modifica
 *
 * Il verbale del consiglio di classe viene aggiornato più volte. Prima
 * di ogni modifica il programma conserva le ultime tre versioni:
 *
 *     verbale.txt.bak1   la versione precedente
 *     verbale.txt.bak2   quella prima ancora
 *     verbale.txt.bak3   la più vecchia conservata
 *
 * La rotazione procede dalla copia più vecchia, così nessun nome viene
 * sovrascritto prima di essere spostato:
 *
 *     remove(bak3)              la più vecchia si perde
 *     rename(bak2, bak3)
 *     rename(bak1, bak2)
 *     copia(originale, bak1)    copia, perché l'originale resta
 *
 * Le rename e la remove falliscono se il file non c'è ancora (le prime
 * volte): non è un errore, quindi il risultato si ignora. La copia
 * invece deve riuscire: se fallisce, la modifica non viene fatta.
 *
 * Dopo la copia il programma aggiunge in fondo al verbale la riga
 * scritta dall'utente e mostra quante righe ha ogni versione presente.
 */

#include <stdio.h>

#define COPIE 3

int ruota_copie(const char *nome);
int copia(const char *da, const char *a);
int esiste(const char *nome);
void stampa_righe(const char *nome);

int main(void)
{
    char nome[40];
    char riga[100];
    char copia_nome[50];
    FILE *f;
    int ok = 1;
    int k;

    printf("File da modificare: ");
    if (scanf("%39s", nome) != 1) {
        ok = 0;
    } else {
        printf("Riga da aggiungere: ");
        ok = scanf(" %99[^\n]", riga) == 1;
    }
    if (ok && esiste(nome)) {
        ok = ruota_copie(nome);
        if (!ok) {
            fprintf(stderr, "Copia di sicurezza non riuscita: modifica annullata.\n");
        }
    }
    if (ok) {
        f = fopen(nome, "a");
        if (f == NULL) {
            fprintf(stderr, "Impossibile aprire %s\n", nome);
        } else {
            fprintf(f, "%s\n", riga);
            fclose(f);
            printf("Aggiunta a %s.\nVersioni presenti:\n", nome);
            printf("  %-18s ", nome);
            stampa_righe(nome);
            for (k = 1; k <= COPIE; k++) {
                sprintf(copia_nome, "%s.bak%d", nome, k);
                if (esiste(copia_nome)) {
                    printf("  %-18s ", copia_nome);
                    stampa_righe(copia_nome);
                }
            }
        }
    }

    return 0;
}

/* Fa scorrere le copie e copia l'originale in .bak1; 0 se la copia fallisce. */
int ruota_copie(const char *nome)
{
    char da[50];
    char a[50];
    int k;

    sprintf(a, "%s.bak%d", nome, COPIE);
    remove(a);
    for (k = COPIE - 1; k >= 1; k--) {
        sprintf(da, "%s.bak%d", nome, k);
        sprintf(a, "%s.bak%d", nome, k + 1);
        rename(da, a);
    }
    sprintf(a, "%s.bak1", nome);
    return copia(nome, a);
}

int copia(const char *da, const char *a)
{
    FILE *origine = fopen(da, "r");
    FILE *destinazione = NULL;
    int ok = 0;
    int c;

    if (origine != NULL) {
        destinazione = fopen(a, "w");
        if (destinazione != NULL) {
            c = fgetc(origine);
            while (c != EOF) {
                fputc(c, destinazione);
                c = fgetc(origine);
            }
            fclose(destinazione);
            ok = 1;
        }
        fclose(origine);
    }
    return ok;
}

int esiste(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int trovato = f != NULL;

    if (trovato) {
        fclose(f);
    }
    return trovato;
}

/* Stampa il numero di righe del file. */
void stampa_righe(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int righe = 0;
    int c;

    if (f != NULL) {
        c = fgetc(f);
        while (c != EOF) {
            if (c == '\n') {
                righe++;
            }
            c = fgetc(f);
        }
        fclose(f);
    }
    printf("righe: %d\n", righe);
}
