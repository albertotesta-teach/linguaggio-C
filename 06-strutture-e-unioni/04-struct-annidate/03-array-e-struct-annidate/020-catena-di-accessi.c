/*
 * 020-catena-di-accessi.c
 *
 * Più livelli insieme: scuola, classi, studenti, date
 *
 * Una scuola ha un array di classi, ogni classe un array di studenti,
 * ogni studente una data di nascita:
 *
 *     scuola.classi[c].alunni[s].nascita.anno
 *
 * Si legge da sinistra a destra, un passo alla volta:
 *
 *     scuola                          Scuola
 *     scuola.classi                   array di Classe
 *     scuola.classi[c]                una Classe
 *     scuola.classi[c].alunni         array di Studente
 *     scuola.classi[c].alunni[s]      uno Studente
 *     ...alunni[s].nascita            una Data
 *     ...alunni[s].nascita.anno       un int
 *
 * A ogni passo si sa che tipo si ha in mano: dopo un array viene [ ],
 * dopo una struct viene il punto. Due cicli annidati percorrono tutti gli
 * studenti: quello esterno sulle classi, quello interno sugli studenti
 * della classe c, fino a scuola.classi[c].n_alunni.
 *
 * Esempio: la sezione del corso serale; si cercano lo studente più
 * giovane e quanti sono nati in ogni anno.
 */

#include <stdio.h>

#define MAX_CLASSI 3
#define MAX_ALUNNI 4
#define PRIMO_ANNO 1990
#define ULTIMO_ANNO 2010

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char nome[16];
    Data nascita;
} Studente;

typedef struct {
    char nome[4];
    Studente alunni[MAX_ALUNNI];
    int n_alunni;
} Classe;

typedef struct {
    char nome[24];
    Classe classi[MAX_CLASSI];
    int n_classi;
} Scuola;

int main(void)
{
    Scuola serale = {
        "Corso serale",
        {
            {"1S", {{"Bassi Rita", {3, 5, 2004}}, {"Corti Ugo", {21, 1, 1998}}}, 2},
            {"2S", {{"Dini Ada", {9, 9, 2006}}, {"Elia Gino", {14, 2, 1995}},
                    {"Fumo Pia", {30, 6, 2006}}}, 3},
            {"3S", {{"Gallo Ivo", {11, 12, 1990}}}, 1}
        },
        3
    };
    int conteggi[ULTIMO_ANNO - PRIMO_ANNO + 1] = {0};
    int classe_giovane = 0;
    int alunno_giovane = 0;
    int anno;
    int c;
    int s;

    for (c = 0; c < serale.n_classi; c++) {
        printf("Classe %s\n", serale.classi[c].nome);
        for (s = 0; s < serale.classi[c].n_alunni; s++) {
            printf("  %-12s %02d/%02d/%d\n", serale.classi[c].alunni[s].nome,
                   serale.classi[c].alunni[s].nascita.giorno,
                   serale.classi[c].alunni[s].nascita.mese,
                   serale.classi[c].alunni[s].nascita.anno);

            anno = serale.classi[c].alunni[s].nascita.anno;
            if (anno >= PRIMO_ANNO && anno <= ULTIMO_ANNO) {
                conteggi[anno - PRIMO_ANNO]++;
            }

            /* più giovane: anno, poi mese, poi giorno più grandi */
            if (anno > serale.classi[classe_giovane].alunni[alunno_giovane].nascita.anno ||
                (anno == serale.classi[classe_giovane].alunni[alunno_giovane].nascita.anno &&
                 serale.classi[c].alunni[s].nascita.mese * 100 +
                         serale.classi[c].alunni[s].nascita.giorno >
                     serale.classi[classe_giovane].alunni[alunno_giovane].nascita.mese * 100 +
                         serale.classi[classe_giovane].alunni[alunno_giovane].nascita.giorno)) {
                classe_giovane = c;
                alunno_giovane = s;
            }
        }
    }

    printf("\nIl piu' giovane: %s della %s\n",
           serale.classi[classe_giovane].alunni[alunno_giovane].nome,
           serale.classi[classe_giovane].nome);
    printf("Nati per anno:");
    for (anno = PRIMO_ANNO; anno <= ULTIMO_ANNO; anno++) {
        if (conteggi[anno - PRIMO_ANNO] > 0) {
            printf("  %d: %d", anno, conteggi[anno - PRIMO_ANNO]);
        }
    }
    printf("\n");

    return 0;
}
