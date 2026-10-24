/*
 * 070-problema-cifratura-messaggi.c
 *
 * Club di crittografia: cifrare e decifrare con tre metodi classici
 *
 * Il club di crittografia della scuola confronta tre cifrari che agiscono
 * su una lettera alla volta (gli altri caratteri restano uguali):
 *   - Cesare:  ogni lettera avanza di 3 posizioni (A -> D, Z -> C);
 *   - ROT13:   avanza di 13; applicato due volte ridà il testo originale;
 *   - Atbash:  l'alfabeto rovesciato (A -> Z, B -> Y); anche lui si
 *              annulla applicandolo due volte.
 *
 * Una trasformazione è una funzione da char a char:
 *
 *     typedef char (*Trasforma)(char c);
 *
 *     Trasforma cifra[METODI]   = {cesare, rot13, atbash};
 *     Trasforma decifra[METODI] = {cesare_inverso, rot13, atbash};
 *
 *     void applica(char *testo, Trasforma t);     modifica il testo
 *
 * Per ogni messaggio letto il programma mostra il testo cifrato con i tre
 * metodi e controlla che, decifrandolo, si torni al messaggio originale.
 * Una riga vuota termina.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define METODI 3
#define LUNG   100

typedef char (*Trasforma)(char c);

char cesare(char c);
char cesare_inverso(char c);
char rot13(char c);
char atbash(char c);
char sposta(char c, int passo);
void applica(char *testo, Trasforma t);

int main(void)
{
    const char *nomi[METODI] = {"Cesare", "ROT13", "Atbash"};
    Trasforma cifra[METODI] = {cesare, rot13, atbash};
    Trasforma decifra[METODI] = {cesare_inverso, rot13, atbash};
    char messaggio[LUNG];
    char copia[LUNG];
    char *a_capo;
    int resto;
    int m;
    int continua = 1;

    while (continua) {
        printf("Messaggio (riga vuota per finire): ");
        if (fgets(messaggio, LUNG, stdin) == NULL) {
            continua = 0;
        } else {
            a_capo = strchr(messaggio, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            } else {
                resto = getchar();      /* riga troppo lunga: scarta il resto */
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            continua = messaggio[0] != '\0';
            for (m = 0; m < METODI && continua; m++) {
                strcpy(copia, messaggio);
                applica(copia, cifra[m]);
                printf("  %-7s %s", nomi[m], copia);
                applica(copia, decifra[m]);
                printf("   -> decifrato %s\n", strcmp(copia, messaggio) == 0 ? "ok" : "ERRATO");
            }
        }
    }

    return 0;
}

/* Sposta una lettera di passo posizioni nel suo alfabeto (maiuscolo o
 * minuscolo), ricominciando dall'inizio dopo la Z. */
char sposta(char c, int passo)
{
    char risultato = c;

    if (isupper((unsigned char) c)) {
        risultato = (char) ('A' + (c - 'A' + passo) % 26);
    } else if (islower((unsigned char) c)) {
        risultato = (char) ('a' + (c - 'a' + passo) % 26);
    }
    return risultato;
}

char cesare(char c)
{
    return sposta(c, 3);
}

/* Indietro di 3 equivale ad avanti di 23. */
char cesare_inverso(char c)
{
    return sposta(c, 23);
}

char rot13(char c)
{
    return sposta(c, 13);
}

char atbash(char c)
{
    char risultato = c;

    if (isupper((unsigned char) c)) {
        risultato = (char) ('Z' - (c - 'A'));
    } else if (islower((unsigned char) c)) {
        risultato = (char) ('z' - (c - 'a'));
    }
    return risultato;
}

/* Applica t a ogni carattere: il testo del chiamante viene modificato. */
void applica(char *testo, Trasforma t)
{
    while (*testo != '\0') {
        *testo = t(*testo);
        testo++;
    }
}
