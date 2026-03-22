/*
 * 060-problema-rubrica-telefonica.c
 *
 * Problema reale: rubrica telefonica semplificata.
 *
 * Scenario: un'applicazione gestisce una piccola rubrica con 6 contatti.
 * Il programma memorizza nomi e numeri di telefono in array paralleli,
 * stampa la rubrica completa, cerca un numero dato il nome e identifica
 * i numeri con prefisso specifico (es. tutti i cellulari che iniziano con 3).
 *
 * Concetti applicati:
 *  - scorrimento di array paralleli
 *  - confronto carattere per carattere (senza strcmp)
 *  - ricerca con variabile di controllo (senza break)
 */

#include <stdio.h>

#define NUM_CONTATTI 6
#define LEN_NOME     25
#define LEN_TELEFONO 13

int main(void) {

    char nomi[NUM_CONTATTI][LEN_NOME] = {
        "Rossi Marco",
        "Bianchi Sara",
        "Verdi Luca",
        "Ferrari Anna",
        "Russo Pietro",
        "Colombo Giulia"
    };
    char telefoni[NUM_CONTATTI][LEN_TELEFONO] = {
        "3471234567",
        "0212345678",
        "3389876543",
        "0612223344",
        "3201112233",
        "0116667788"
    };

    int i;
    int j;

    printf("======================================\n");
    printf("           RUBRICA TELEFONICA         \n");
    printf("======================================\n");
    for (i = 0; i < NUM_CONTATTI; i++) {
        printf("  %-20s %s\n", nomi[i], telefoni[i]);
    }
    printf("======================================\n\n");

    char ricerca[LEN_NOME] = "Rossi";
    int trovato = 0;
    int indice_trovato = -1;

    int len_ricerca = 0;
    while (ricerca[len_ricerca] != '\0') {
        len_ricerca++;
    }

    for (i = 0; i < NUM_CONTATTI && !trovato; i++) {
        int uguale = 1;
        for (j = 0; j < len_ricerca && uguale; j++) {
            if (nomi[i][j] != ricerca[j]) {
                uguale = 0;
            }
        }
        if (uguale) {
            trovato = 1;
            indice_trovato = i;
        }
    }

    printf("Ricerca '%s':\n", ricerca);
    if (trovato) {
        printf("  Trovato: %s - Tel: %s\n\n",
               nomi[indice_trovato], telefoni[indice_trovato]);
    } else {
        printf("  Nessun contatto trovato con questo nome.\n\n");
    }

    printf("Contatti con numero di cellulare (prefisso '3'):\n");
    int num_cellulari = 0;
    for (i = 0; i < NUM_CONTATTI; i++) {
        if (telefoni[i][0] == '3') {
            printf("  %s: %s\n", nomi[i], telefoni[i]);
            num_cellulari++;
        }
    }
    printf("Totale cellulari in rubrica: %d su %d\n", num_cellulari, NUM_CONTATTI);

    return 0;
}
