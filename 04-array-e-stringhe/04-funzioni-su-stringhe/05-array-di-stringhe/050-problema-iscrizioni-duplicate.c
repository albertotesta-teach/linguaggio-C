/*
 * 050-problema-iscrizioni-duplicate.c
 *
 * Trovare le iscrizioni duplicate in un elenco
 *
 * Per la gita di istituto gli studenti si sono iscritti compilando un
 * modulo online, e alcuni lo hanno compilato più volte, scrivendo il nome
 * in modi diversi:
 *
 *     "Rossi Mario", "ROSSI MARIO", "  rossi   mario "
 *
 * Il programma:
 *   1. normalizza ogni nome in una copia (spazi superflui eliminati,
 *      tutto in minuscolo), così che le varianti diventino uguali;
 *   2. confronta ogni nome con tutti quelli che lo precedono (doppio ciclo
 *      i, j con j < i): se trova un uguale segnala il duplicato;
 *   3. costruisce l'elenco pulito copiando con strcpy solo le iscrizioni
 *      non duplicate (array a tappo).
 *
 * Gli elenchi originale e normalizzato sono paralleli: la riga k di
 * entrambi descrive la stessa iscrizione.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ISCRIZIONI 10
#define LUNG       28

void normalizza(char dest[], const char sorg[]);

int main(void)
{
    char moduli[ISCRIZIONI][LUNG] = {
        "Rossi Mario", "Bianchi Sara", "ROSSI MARIO", "Verdi Luca",
        "  bianchi  sara", "Neri Anna", "Gallo Paolo", "Rossi Maria",
        "Verdi  Luca ", "Neri Anna"
    };
    char normalizzati[ISCRIZIONI][LUNG];
    char pulito[ISCRIZIONI][LUNG];
    int n_pulito = 0;
    int i;
    int j;
    int duplicato;
    int duplicati = 0;

    for (i = 0; i < ISCRIZIONI; i++) {
        normalizza(normalizzati[i], moduli[i]);
    }

    printf("=== CONTROLLO DEI DUPLICATI ===\n");
    for (i = 0; i < ISCRIZIONI; i++) {
        duplicato = 0;
        j = 0;
        while (j < i && !duplicato) {
            if (strcmp(normalizzati[i], normalizzati[j]) == 0) {
                duplicato = 1;
                printf("  modulo %2d [%s] e' un duplicato del modulo %d [%s]\n",
                       i + 1, moduli[i], j + 1, moduli[j]);
            }
            j++;
        }
        if (duplicato) {
            duplicati++;
        } else {
            strcpy(pulito[n_pulito], moduli[i]);
            n_pulito++;
        }
    }

    printf("\nModuli ricevuti: %d, duplicati: %d, iscritti: %d\n",
           ISCRIZIONI, duplicati, n_pulito);
    printf("Elenco degli iscritti:\n");
    for (i = 0; i < n_pulito; i++) {
        printf("  %d. %s\n", i + 1, pulito[i]);
    }

    return 0;
}

/* Copia sorg in dest in minuscolo, senza spazi iniziali e finali e con
 * un solo spazio tra le parole. */
void normalizza(char dest[], const char sorg[])
{
    int i = 0;
    int j = 0;

    while (sorg[i] != '\0') {
        if (sorg[i] != ' ') {
            dest[j] = (char) tolower((unsigned char) sorg[i]);
            j++;
        } else if (j > 0 && dest[j - 1] != ' ') {
            dest[j] = ' ';
            j++;
        }
        i++;
    }
    if (j > 0 && dest[j - 1] == ' ') {
        j--;
    }
    dest[j] = '\0';
}
