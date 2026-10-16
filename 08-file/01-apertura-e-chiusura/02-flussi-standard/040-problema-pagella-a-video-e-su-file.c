/*
 * 040-problema-pagella-a-video-e-su-file.c
 *
 * La pagella: la stessa funzione per lo schermo e per il file
 *
 * A fine trimestre il coordinatore inserisce i voti di uno studente
 * nelle materie della classe. La pagella si vede subito a video e si
 * salva in un file con il nome dello studente:
 *
 *     sprintf(nome_file, "pagella-%s.txt", cognome);
 *
 *     stampa_pagella(stdout, ...);     controllo a video
 *     stampa_pagella(file, ...);       copia da consegnare
 *
 * stampa_pagella riceve il flusso e scrive solo con fprintf su quel
 * flusso: le due copie sono identiche per costruzione.
 *
 * Il programma legge cognome e voti (da 1 a 10, ripetendo la domanda
 * se il voto non è valido), calcola la media, segnala le insufficienze
 * e chiede conferma prima di salvare.
 */

#include <stdio.h>

#define MATERIE 6

void stampa_pagella(FILE *f, const char *cognome, const char *materie[], const int voti[],
                    int n);
int leggi_voto(const char *materia);

int main(void)
{
    const char *materie[MATERIE] = {"Italiano", "Matematica", "Inglese",
                                    "Informatica", "Sistemi e reti", "Scienze motorie"};
    int voti[MATERIE];
    char cognome[30];
    char nome_file[50];
    char risposta = 'n';
    FILE *f;
    int ok = 1;
    int i;

    printf("Cognome dello studente: ");
    if (scanf("%29s", cognome) != 1) {
        ok = 0;
    }
    for (i = 0; i < MATERIE && ok; i++) {
        voti[i] = leggi_voto(materie[i]);
        ok = voti[i] != 0;
    }

    if (!ok) {
        printf("Dati incompleti.\n");
    } else {
        printf("\n");
        stampa_pagella(stdout, cognome, materie, voti, MATERIE);
        printf("\nSalvare la pagella? (s/n) ");
        if (scanf(" %c", &risposta) != 1) {
            risposta = 'n';
        }
    }
    if (ok && risposta == 's') {
        sprintf(nome_file, "pagella-%s.txt", cognome);
        f = fopen(nome_file, "w");
        if (f == NULL) {
            fprintf(stderr, "Impossibile creare %s\n", nome_file);
        } else {
            stampa_pagella(f, cognome, materie, voti, MATERIE);
            fclose(f);
            printf("Pagella salvata in %s\n", nome_file);
        }
    } else if (ok) {
        printf("Pagella non salvata.\n");
    }

    return 0;
}

/* Voto da 1 a 10, ripetendo la domanda; 0 se l'input finisce. */
int leggi_voto(const char *materia)
{
    int voto = 0;
    int letti = 0;

    while (letti != EOF && (voto < 1 || voto > 10)) {
        printf("  %s: ", materia);
        letti = scanf("%d", &voto);
        if (letti == 0) {
            scanf("%*s");
            voto = 0;
        }
        if (letti != EOF && (voto < 1 || voto > 10)) {
            fprintf(stderr, "  voto da 1 a 10\n");
        }
    }
    if (letti == EOF) {
        voto = 0;
    }
    return voto;
}

void stampa_pagella(FILE *f, const char *cognome, const char *materie[], const int voti[],
                    int n)
{
    int somma = 0;
    int insufficienze = 0;
    int i;

    fprintf(f, "PAGELLA DEL PRIMO TRIMESTRE - %s\n", cognome);
    fprintf(f, "----------------------------------\n");
    for (i = 0; i < n; i++) {
        fprintf(f, "%-18s %2d%s\n", materie[i], voti[i], voti[i] < 6 ? "  *" : "");
        somma += voti[i];
        if (voti[i] < 6) {
            insufficienze++;
        }
    }
    fprintf(f, "----------------------------------\n");
    fprintf(f, "Media: %.2f\n", (double) somma / n);
    if (insufficienze == 0) {
        fprintf(f, "Nessuna insufficienza.\n");
    } else {
        fprintf(f, "Insufficienze (*): %d\n", insufficienze);
    }
}
