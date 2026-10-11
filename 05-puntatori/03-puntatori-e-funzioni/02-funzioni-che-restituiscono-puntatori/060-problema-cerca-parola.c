/*
 * 060-problema-cerca-parola.c
 *
 * Ricerca nel regolamento d'istituto
 *
 * Il rappresentante degli studenti vuole sapere quante volte alcune parole
 * compaiono in un articolo del regolamento d'istituto e in che punto
 * compaiono per la prima volta, con qualche carattere di contesto.
 *
 * Il programma usa una propria versione di strstr:
 *
 *     const char *trova(const char *testo, const char *parola);
 *
 * che restituisce il puntatore al primo carattere dell'occorrenza nel
 * testo, NULL se la parola non c'è. Il puntatore restituito punta DENTRO
 * il testo del chiamante: per cercare l'occorrenza successiva basta
 * ripartire da trovato + 1.
 */

#include <stdio.h>
#include <string.h>

#define CONTESTO 12
#define PAROLE   4
#define LUNG     16

const char *trova(const char *testo, const char *parola);
int inizia_con(const char *testo, const char *parola);
int conta(const char *testo, const char *parola);

int main(void)
{
    const char *articolo =
        "Art. 7 - Uso del telefono. Durante le lezioni il telefono deve "
        "restare spento. Il telefono si puo' usare solo con il permesso "
        "del docente. In laboratorio vale lo stesso divieto.";
    char cercate[PAROLE][LUNG] = {"telefono", "docente", "divieto", "intervallo"};
    const char *trovato;
    int posizione;
    int da;
    int n;
    int i;

    printf("%s\n\n", articolo);
    for (i = 0; i < PAROLE; i++) {
        trovato = trova(articolo, cercate[i]);
        printf("\"%s\": ", cercate[i]);
        if (trovato == NULL) {
            printf("non presente\n");
        } else {
            /* il contesto parte CONTESTO caratteri prima, ma non prima del testo */
            posizione = trovato - articolo;
            da = posizione - CONTESTO;
            if (da < 0) {
                da = 0;
            }
            n = conta(articolo, cercate[i]);
            printf("%d %s, la prima in posizione %d: \"...%.*s...\"\n",
                   n, n == 1 ? "volta" : "volte", posizione,
                   posizione - da + (int) strlen(cercate[i]) + CONTESTO, articolo + da);
        }
    }

    return 0;
}

/* Puntatore alla prima occorrenza di parola in testo, NULL se assente. */
const char *trova(const char *testo, const char *parola)
{
    const char *p = testo;

    while (*p != '\0' && !inizia_con(p, parola)) {
        p++;
    }
    return *p != '\0' ? p : NULL;
}

/* 1 se testo inizia con tutti i caratteri di parola. */
int inizia_con(const char *testo, const char *parola)
{
    while (*parola != '\0' && *testo == *parola) {
        testo++;
        parola++;
    }
    return *parola == '\0';
}

/* Numero di occorrenze: dopo ogni occorrenza si riparte da trovato + 1. */
int conta(const char *testo, const char *parola)
{
    const char *trovato = trova(testo, parola);
    int volte = 0;

    while (trovato != NULL) {
        volte++;
        trovato = trova(trovato + 1, parola);
    }
    return volte;
}
