/*
 * 050-problema-cambio-password.c
 *
 * Cambiare la password di un account
 *
 * Il portale del registro elettronico permette di cambiare la password.
 * La procedura è:
 *   1. inserire la password attuale: sono ammessi al massimo TENTATIVI
 *      errori, poi la procedura viene annullata;
 *   2. inserire la nuova password, che deve
 *        - avere da MIN_LUNG a MAX_LUNG caratteri (strlen),
 *        - essere diversa da quella attuale (strcmp);
 *   3. riscrivere la nuova password per conferma: se le due versioni sono
 *      diverse (strcmp) si ricomincia dal punto 2.
 *
 * Alla fine la nuova password viene salvata con strcpy al posto di quella
 * vecchia. Nella realtà le password non si salvano mai in chiaro: questo
 * esempio serve solo a mostrare l'uso di strlen, strcmp e strcpy.
 */

#include <stdio.h>
#include <string.h>

#define DIM        40
#define TENTATIVI  3
#define MIN_LUNG   8
#define MAX_LUNG   20

int leggi_riga(char s[], int dim);

int main(void)
{
    char password[DIM] = "Sole2024";
    char inserita[DIM];
    char nuova[DIM];
    char conferma[DIM];
    int errori = 0;
    int autenticato = 0;
    int cambiata = 0;
    int lung;

    printf("=== CAMBIO PASSWORD ===\n");

    /* ── 1. Verifica della password attuale ───────────────────────── */
    while (!autenticato && errori < TENTATIVI) {
        printf("Password attuale: ");
        leggi_riga(inserita, DIM);
        if (strcmp(inserita, password) == 0) {
            autenticato = 1;
        } else {
            errori++;
            printf("  Password errata (%d di %d tentativi).\n", errori, TENTATIVI);
        }
    }

    /* ── 2. e 3. Nuova password e conferma ────────────────────────── */
    while (autenticato && !cambiata) {
        printf("Nuova password (%d-%d caratteri): ", MIN_LUNG, MAX_LUNG);
        leggi_riga(nuova, DIM);
        lung = (int) strlen(nuova);

        if (lung < MIN_LUNG || lung > MAX_LUNG) {
            printf("  Lunghezza non valida: %d caratteri.\n", lung);
        } else if (strcmp(nuova, password) == 0) {
            printf("  La nuova password deve essere diversa da quella attuale.\n");
        } else {
            printf("Conferma la nuova password: ");
            leggi_riga(conferma, DIM);
            if (strcmp(nuova, conferma) != 0) {
                printf("  Le due password non coincidono, ricomincia.\n");
            } else {
                strcpy(password, nuova);
                cambiata = 1;
            }
        }
    }

    if (cambiata) {
        printf("Password cambiata (%d caratteri).\n", (int) strlen(password));
    } else {
        printf("Troppi tentativi errati: procedura annullata.\n");
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
