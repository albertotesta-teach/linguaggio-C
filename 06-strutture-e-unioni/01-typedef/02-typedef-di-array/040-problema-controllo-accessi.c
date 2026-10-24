/*
 * 040-problema-controllo-accessi.c
 *
 * Sbarra del parcheggio: controllo delle targhe autorizzate
 *
 * All'ingresso del parcheggio della scuola una telecamera legge la targa
 * e il programma decide se alzare la sbarra. Una targa italiana ha il
 * formato AA000AA: due lettere maiuscole, tre cifre, due lettere.
 *
 *     typedef char Targa[8];
 *
 *     int targa_valida(const Targa t);
 *     int autorizzata(const Targa t, const Targa elenco[], int n);
 *
 * Il programma legge una targa per riga (FINE termina). Per ogni targa:
 *   - formato non valido   -> "lettura non valida, ripetere";
 *   - non in elenco        -> "accesso negato";
 *   - autorizzata          -> "sbarra alzata".
 * Alla fine stampa quanti ingressi sono stati consentiti e negati.
 *
 * La riga si legge con fgets in un array più lungo e si copia nella Targa
 * solo se ha esattamente 7 caratteri: così una lettura troppo lunga non
 * esce dai limiti della Targa.
 */

#include <stdio.h>
#include <string.h>

#define AUTORIZZATE 5
#define LUNG_TARGA 7
#define LUNG_RIGA 40

typedef char Targa[LUNG_TARGA + 1];

int targa_valida(const Targa t);
int autorizzata(const Targa t, const Targa elenco[], int n);
int lettera(char c);
int cifra(char c);

int main(void)
{
    const Targa elenco[AUTORIZZATE] = {"EK301TZ", "DM774PA", "FH052LC", "GB918RN", "CX640MD"};
    char riga[LUNG_RIGA];
    char *a_capo;
    int resto;
    Targa targa;
    int fine = 0;
    int consentiti = 0;
    int negati = 0;

    while (!fine) {
        printf("Targa letta (FINE per terminare): ");
        if (fgets(riga, LUNG_RIGA, stdin) == NULL) {
            fine = 1;
        } else {
            a_capo = strchr(riga, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            } else {
                resto = getchar();      /* riga troppo lunga: scarta il resto */
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            if (strcmp(riga, "FINE") == 0) {
                fine = 1;
            } else if (strlen(riga) != LUNG_TARGA) {
                printf("  Lettura non valida, ripetere.\n");
            } else {
                strcpy(targa, riga);
                if (!targa_valida(targa)) {
                    printf("  Lettura non valida, ripetere.\n");
                } else if (autorizzata(targa, elenco, AUTORIZZATE)) {
                    printf("  %s: sbarra alzata.\n", targa);
                    consentiti++;
                } else {
                    printf("  %s: accesso negato.\n", targa);
                    negati++;
                }
            }
        }
    }

    printf("\nIngressi consentiti: %d, negati: %d\n", consentiti, negati);

    return 0;
}

/* Formato AA000AA. */
int targa_valida(const Targa t)
{
    return lettera(t[0]) && lettera(t[1]) && cifra(t[2]) && cifra(t[3]) && cifra(t[4]) &&
           lettera(t[5]) && lettera(t[6]);
}

int autorizzata(const Targa t, const Targa elenco[], int n)
{
    int i = 0;

    while (i < n && strcmp(t, elenco[i]) != 0) {
        i++;
    }
    return i < n;
}

int lettera(char c)
{
    return c >= 'A' && c <= 'Z';
}

int cifra(char c)
{
    return c >= '0' && c <= '9';
}
