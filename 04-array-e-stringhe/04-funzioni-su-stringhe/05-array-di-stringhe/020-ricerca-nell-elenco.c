/*
 * 020-ricerca-nell-elenco.c
 *
 * Cercare una parola in un elenco
 *
 * La ricerca in un elenco di stringhe segue lo schema della ricerca
 * lineare negli array (capitolo 04, array monodimensionali): si scorre
 * l'elenco finché la parola non è trovata. L'unica differenza è il
 * confronto, che si fa con strcmp e non con ==.
 *
 *   cerca(elenco, n, parola)               indice o -1, confronto esatto
 *   cerca_senza_maiuscole(elenco, n, parola) indice o -1, ignora le maiuscole
 *   conta_iniziale(elenco, n, lettera)     quante parole iniziano con lettera
 *
 * Il parametro si scrive  const char elenco[][LUNG]: come per le matrici
 * di numeri, va indicato il numero di colonne.
 *
 * Esempio: elenco degli studenti iscritti al corso di robotica, con la
 * classe in un array parallelo.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ISCRITTI 7
#define LUNG     20

int cerca(const char elenco[][LUNG], int n, const char parola[]);
int cerca_senza_maiuscole(const char elenco[][LUNG], int n, const char parola[]);
int uguali_senza_maiuscole(const char a[], const char b[]);
int conta_iniziale(const char elenco[][LUNG], int n, char lettera);

int main(void)
{
    char iscritti[ISCRITTI][LUNG] = {
        "Bianchi Sara", "Colombo Luca", "Esposito Marco", "Ferrari Anna",
        "Bruno Elena", "Romano Davide", "Conti Giulia"
    };
    char classi[ISCRITTI][4] = {"3A", "4B", "3A", "5C", "4B", "3C", "5C"};
    char cercati[4][LUNG] = {"Ferrari Anna", "ferrari anna", "Rossi Mario", "Conti Giulia"};
    int k;
    int pos;

    printf("=== RICERCA ESATTA (strcmp) ===\n");
    for (k = 0; k < 4; k++) {
        pos = cerca(iscritti, ISCRITTI, cercati[k]);
        if (pos == -1) {
            printf("  %-14s non iscritto\n", cercati[k]);
        } else {
            printf("  %-14s posizione %d, classe %s\n", cercati[k], pos, classi[pos]);
        }
    }

    printf("\n=== RICERCA SENZA MAIUSCOLE ===\n");
    pos = cerca_senza_maiuscole(iscritti, ISCRITTI, cercati[1]);
    printf("  %-14s posizione %d, classe %s\n", cercati[1], pos, classi[pos]);

    printf("\n=== ISCRITTI PER INIZIALE DEL COGNOME ===\n");
    printf("  B: %d   C: %d   R: %d   Z: %d\n",
           conta_iniziale(iscritti, ISCRITTI, 'B'), conta_iniziale(iscritti, ISCRITTI, 'C'),
           conta_iniziale(iscritti, ISCRITTI, 'R'), conta_iniziale(iscritti, ISCRITTI, 'Z'));

    return 0;
}

int cerca(const char elenco[][LUNG], int n, const char parola[])
{
    int k = 0;
    int trovato = -1;

    while (k < n && trovato == -1) {
        if (strcmp(elenco[k], parola) == 0) {
            trovato = k;
        }
        k++;
    }
    return trovato;
}

int cerca_senza_maiuscole(const char elenco[][LUNG], int n, const char parola[])
{
    int k = 0;
    int trovato = -1;

    while (k < n && trovato == -1) {
        if (uguali_senza_maiuscole(elenco[k], parola)) {
            trovato = k;
        }
        k++;
    }
    return trovato;
}

int uguali_senza_maiuscole(const char a[], const char b[])
{
    int i = 0;

    while (a[i] != '\0' && tolower((unsigned char) a[i]) == tolower((unsigned char) b[i])) {
        i++;
    }
    return tolower((unsigned char) a[i]) == tolower((unsigned char) b[i]);
}

int conta_iniziale(const char elenco[][LUNG], int n, char lettera)
{
    int k;
    int conteggio = 0;

    for (k = 0; k < n; k++) {
        if (elenco[k][0] == lettera) {
            conteggio++;
        }
    }
    return conteggio;
}
