/*
 * 050-problema-cifrario-cesare.c
 *
 * Problema reale: cifratura e decifratura con il cifrario di Cesare.
 *
 * Scenario: il cifrario di Cesare è uno dei più antichi sistemi crittografici.
 * Ogni lettera del messaggio viene sostituita con la lettera che si trova
 * N posizioni più avanti nell'alfabeto (con avvolgimento circolare: dopo 'z'
 * si torna ad 'a'). La decifratura applica lo spostamento inverso.
 *
 * Struttura dati chiave:
 *  - un array di char che rappresenta il messaggio
 *  - le funzioni cifra() e decifra() modificano l'array in-place
 *  - solo le lettere vengono modificate; spazi e punteggiatura restano invariati
 *
 * Concetti applicati:
 *  - funzioni che modificano array di char in-place
 *  - aritmetica modulare per l'avvolgimento circolare dell'alfabeto
 *  - separazione tra cifratura e decifratura in funzioni distinte
 *  - scorrimento stringa fino al terminatore '\0'
 */

#include <stdio.h>

#define SPOSTAMENTO 3   /* chiave del cifrario: Cesare usava 3 */

/* Cifra il messaggio applicando lo spostamento in avanti.
 * Solo le lettere (maiuscole e minuscole) vengono modificate.
 * L'avvolgimento usa il modulo 26: (c - 'a' + SPOSTAMENTO) % 26. */
void cifra(char msg[], int spostamento) {
    int i;
    for (i = 0; msg[i] != '\0'; i++) {
        if (msg[i] >= 'a' && msg[i] <= 'z') {
            /* Porta la lettera in [0,25], aggiunge lo spostamento,
             * applica il modulo 26 per l'avvolgimento, poi riporta in ASCII */
            msg[i] = (char)('a' + (msg[i] - 'a' + spostamento) % 26);
        } else if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = (char)('A' + (msg[i] - 'A' + spostamento) % 26);
        }
        /* spazi, numeri e punteggiatura: invariati */
    }
}

/* Decifra il messaggio applicando lo spostamento inverso.
 * Aggiunge 26 prima del modulo per evitare valori negativi:
 * (c - 'a' - spostamento + 26) % 26 è sempre in [0,25]. */
void decifra(char msg[], int spostamento) {
    int i;
    for (i = 0; msg[i] != '\0'; i++) {
        if (msg[i] >= 'a' && msg[i] <= 'z') {
            msg[i] = (char)('a' + (msg[i] - 'a' - spostamento + 26) % 26);
        } else if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = (char)('A' + (msg[i] - 'A' - spostamento + 26) % 26);
        }
    }
}

/* Conta i caratteri della stringa fino a '\0' (lunghezza senza terminatore) */
int lunghezza(const char msg[]) {
    int i = 0;
    while (msg[i] != '\0') {
        i++;
    }
    return i;
}

/* Conta quante lettere (esclusi spazi e punteggiatura) contiene il messaggio */
int conta_lettere(const char msg[]) {
    int i;
    int contatore = 0;
    for (i = 0; msg[i] != '\0'; i++) {
        if ((msg[i] >= 'a' && msg[i] <= 'z') ||
            (msg[i] >= 'A' && msg[i] <= 'Z')) {
            contatore++;
        }
    }
    return contatore;
}

int main(void) {

    /* Il messaggio è un array di char modificabile.
     * Attenzione: una stringa letterale come "ciao" non è modificabile
     * se assegnata a char *p = "ciao". Qui usiamo char msg[] = "..." che
     * crea una copia modificabile nello stack. */
    char messaggio[] = "Veni Vidi Vici";

    printf("=== CIFRARIO DI CESARE (spostamento: %d) ===\n\n", SPOSTAMENTO);
    printf("Messaggio originale  : %s\n", messaggio);
    printf("Lunghezza            : %d caratteri (%d lettere)\n\n",
           lunghezza(messaggio), conta_lettere(messaggio));

    /* Cifratura: modifica il messaggio in-place */
    cifra(messaggio, SPOSTAMENTO);
    printf("Messaggio cifrato    : %s\n", messaggio);

    /* Decifratura: ripristina il messaggio originale */
    decifra(messaggio, SPOSTAMENTO);
    printf("Messaggio decifrato  : %s\n\n", messaggio);

    /* ---------------------------------------------------------------- */
    /* Dimostrazione con spostamento variabile */
    char secondo[] = "Attacco all alba";
    int chiave;

    printf("Secondo messaggio: \"%s\"\n\n", secondo);

    for (chiave = 1; chiave <= 5; chiave++) {
        char copia[50];
        int i;

        /* Copia manuale del messaggio originale */
        for (i = 0; secondo[i] != '\0'; i++) {
            copia[i] = secondo[i];
        }
        copia[i] = '\0';

        cifra(copia, chiave);
        printf("  Chiave %d: %s\n", chiave, copia);
    }

    return 0;
}
