/*
 * 040-problema-dizionario.c
 *
 * Un piccolo dizionario italiano-inglese
 *
 * Il dizionario è formato da due elenchi paralleli: italiano[k] e
 * inglese[k] sono la stessa parola nelle due lingue. L'utente scrive una
 * parola in una delle due lingue e il programma la traduce:
 *
 *   - se la parola è nell'elenco italiano  -> mostra l'inglese
 *   - se è nell'elenco inglese             -> mostra l'italiano
 *   - altrimenti suggerisce le parole che iniziano con le stesse due
 *     lettere (in entrambe le lingue), se ce ne sono
 *
 * Il confronto ignora le maiuscole: la parola letta viene convertita in
 * minuscolo prima della ricerca (il dizionario è già in minuscolo).
 * Le ricerche continuano finché non si inserisce una riga vuota.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define VOCI 10
#define LUNG 16
#define DIM  30

int leggi_riga(char s[], int dim);
void in_minuscolo(char s[]);
int cerca(const char elenco[][LUNG], int n, const char parola[]);
int suggerisci(const char elenco[][LUNG], const char traduzioni[][LUNG], int n,
               const char parola[]);

int main(void)
{
    char italiano[VOCI][LUNG] = {
        "casa", "scuola", "libro", "quaderno", "penna",
        "insegnante", "lavagna", "zaino", "orario", "compito"
    };
    char inglese[VOCI][LUNG] = {
        "house", "school", "book", "notebook", "pen",
        "teacher", "blackboard", "backpack", "timetable", "homework"
    };
    char parola[DIM];
    int letta;
    int k;
    int suggerimenti;

    printf("=== DIZIONARIO ITALIANO-INGLESE (%d voci) ===\n", VOCI);
    printf("Parola (riga vuota per uscire): ");
    letta = leggi_riga(parola, DIM);

    while (letta && parola[0] != '\0') {
        in_minuscolo(parola);
        k = cerca(italiano, VOCI, parola);
        if (k != -1) {
            printf("  IT -> EN: %s = %s\n", italiano[k], inglese[k]);
        } else {
            k = cerca(inglese, VOCI, parola);
            if (k != -1) {
                printf("  EN -> IT: %s = %s\n", inglese[k], italiano[k]);
            } else {
                printf("  \"%s\" non e' nel dizionario.\n", parola);
                suggerimenti = suggerisci(italiano, inglese, VOCI, parola)
                             + suggerisci(inglese, italiano, VOCI, parola);
                if (suggerimenti == 0) {
                    printf("  Nessun suggerimento.\n");
                }
            }
        }
        printf("Parola (riga vuota per uscire): ");
        letta = leggi_riga(parola, DIM);
    }

    return 0;
}

int leggi_riga(char s[], int dim)
{
    int ok = 0;
    int n;
    int c;

    if (fgets(s, dim, stdin) != NULL) {
        ok = 1;
        n = (int) strlen(s);
        if (n > 0 && s[n - 1] == '\n') {
            s[n - 1] = '\0';
        } else {
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    return ok;
}

void in_minuscolo(char s[])
{
    int i = 0;

    while (s[i] != '\0') {
        s[i] = (char) tolower((unsigned char) s[i]);
        i++;
    }
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

/* Stampa le voci di elenco che iniziano con le prime due lettere di parola
 * (con la loro traduzione) e restituisce quante sono. */
int suggerisci(const char elenco[][LUNG], const char traduzioni[][LUNG], int n,
               const char parola[])
{
    int k;
    int trovate = 0;

    if (strlen(parola) >= 2) {
        for (k = 0; k < n; k++) {
            if (strncmp(elenco[k], parola, 2) == 0) {
                printf("  Forse cercavi: %s (%s)\n", elenco[k], traduzioni[k]);
                trovate++;
            }
        }
    }
    return trovate;
}
