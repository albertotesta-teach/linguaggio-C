/*
 * 040-problema-codice-fiscale.c
 *
 * Controllare il formato di un codice fiscale
 *
 * Il codice fiscale italiano ha 16 caratteri con questa struttura:
 *
 *     R S S M R A 8 5 T 1 0 A 9 4 4 S
 *     ----------- --- - --- ------- -
 *     cognome e   anno mese giorno  comune  carattere
 *     nome (6 L)  (2 C)(1 L)(2 C)   (L+3 C) di controllo (L)
 *
 *   L = lettera (isalpha), C = cifra (isdigit)
 *
 * Il programma:
 *   1. converte il codice in maiuscolo (toupper), così l'utente può
 *      scriverlo anche in minuscolo;
 *   2. controlla la lunghezza e, posizione per posizione, il tipo di
 *      carattere, confrontandolo con lo schema "LLLLLLCCLCCLCCCL";
 *   3. controlla che la lettera del mese sia una di "ABCDEHLMPRST";
 *   4. se il formato è corretto ricava sesso e data di nascita: per le
 *      donne il giorno è aumentato di 40.
 *
 * Non viene verificato il carattere di controllo né i casi di omocodia
 * (cifre sostituite da lettere).
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM       30
#define LUNG_CF   16

int leggi_riga(char s[], int dim);
void in_maiuscolo(char s[]);
int primo_errore(const char cf[], const char schema[]);
int indice_mese(char lettera, const char mesi[]);

int main(void)
{
    char schema[] = "LLLLLLCCLCCLCCCL";
    char lettere_mesi[] = "ABCDEHLMPRST";
    char nomi_mesi[12][10] = {
        "gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno",
        "luglio", "agosto", "settembre", "ottobre", "novembre", "dicembre"
    };
    char cf[DIM];
    int letta;
    int errore;
    int mese;
    int giorno;
    int anno;

    printf("=== CONTROLLO CODICE FISCALE ===\n");
    printf("Codice fiscale (riga vuota per terminare): ");
    letta = leggi_riga(cf, DIM);

    while (letta && cf[0] != '\0') {
        in_maiuscolo(cf);
        printf("  %s: ", cf);

        if ((int) strlen(cf) != LUNG_CF) {
            printf("deve avere %d caratteri, ne ha %d\n", LUNG_CF, (int) strlen(cf));
        } else {
            errore = primo_errore(cf, schema);
            mese = indice_mese(cf[8], lettere_mesi);
            if (errore != -1) {
                printf("in posizione %d serve %s\n", errore + 1,
                       schema[errore] == 'L' ? "una lettera" : "una cifra");
            } else if (mese == -1) {
                printf("la lettera del mese '%c' non esiste\n", cf[8]);
            } else {
                /* le cifre si convertono con c - '0' */
                anno = (cf[6] - '0') * 10 + (cf[7] - '0');
                giorno = (cf[9] - '0') * 10 + (cf[10] - '0');
                printf("formato corretto\n");
                if (giorno > 40) {
                    printf("    sesso F, nata il %d %s '%02d\n", giorno - 40,
                           nomi_mesi[mese], anno);
                } else {
                    printf("    sesso M, nato il %d %s '%02d\n", giorno,
                           nomi_mesi[mese], anno);
                }
            }
        }
        printf("Codice fiscale (riga vuota per terminare): ");
        letta = leggi_riga(cf, DIM);
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

void in_maiuscolo(char s[])
{
    int i = 0;

    while (s[i] != '\0') {
        s[i] = (char) toupper((unsigned char) s[i]);
        i++;
    }
}

/* Indice del primo carattere che non rispetta lo schema
 * ('L' = lettera, 'C' = cifra), oppure -1 se il codice è conforme. */
int primo_errore(const char cf[], const char schema[])
{
    int i = 0;
    int errore = -1;
    unsigned char c;

    while (schema[i] != '\0' && errore == -1) {
        c = (unsigned char) cf[i];
        if ((schema[i] == 'L' && !isalpha(c)) || (schema[i] == 'C' && !isdigit(c))) {
            errore = i;
        }
        i++;
    }
    return errore;
}

/* Indice (0-11) della lettera del mese, oppure -1. */
int indice_mese(char lettera, const char mesi[])
{
    int i = 0;
    int indice = -1;

    while (mesi[i] != '\0' && indice == -1) {
        if (mesi[i] == lettera) {
            indice = i;
        }
        i++;
    }
    return indice;
}
