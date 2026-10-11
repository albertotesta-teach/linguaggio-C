/*
 * 080-problema-rubrica-cognome.c
 *
 * Cercare i contatti di una rubrica per cognome
 *
 * La rubrica di un ufficio è formata da tre array paralleli di stringhe:
 * cognomi, nomi e numeri di telefono. L'utente scrive un testo e il
 * programma mostra tutti i contatti il cui cognome INIZIA con quel testo,
 * senza distinguere maiuscole e minuscole:
 *
 *     "ross"  ->  Rossi Mario, Rossi Anna, Rossetti Paolo
 *     "Rossi" ->  Rossi Mario, Rossi Anna
 *
 * Quando il testo coincide con l'intero cognome il contatto è segnalato
 * come corrispondenza esatta. La ricerca si ripete finché l'utente non
 * scrive "fine".
 *
 * Funzioni:
 *   inizia_con(s, prefisso)       1 se s comincia con prefisso
 *   uguali_ignorando_maiuscole(a, b)
 *   leggi_riga(s, dim)            lettura con fgets e rimozione del '\n'
 */

#include <stdio.h>

#define CONTATTI 8
#define LUNG     20
#define DIM      30

int leggi_riga(char s[], int dim);
int inizia_con(const char s[], const char prefisso[]);
int uguali_ignorando_maiuscole(const char a[], const char b[]);
char minuscola(char c);

int main(void)
{
    char cognomi[CONTATTI][LUNG] = {
        "Rossi", "Bianchi", "Rossetti", "Verdi",
        "Rossi", "Bianco", "Neri", "Bianchini"
    };
    char nomi[CONTATTI][LUNG] = {
        "Mario", "Lucia", "Paolo", "Giorgio",
        "Anna", "Stefano", "Chiara", "Davide"
    };
    char telefoni[CONTATTI][LUNG] = {
        "0131 220145", "0131 220178", "0131 220102", "0131 220190",
        "0131 220133", "0131 220166", "0131 220121", "0131 220155"
    };
    char ricerca[DIM];
    int letta;
    int k;
    int trovati;

    printf("=== RUBRICA DELL'UFFICIO (%d contatti) ===\n", CONTATTI);
    printf("Cognome o sua parte iniziale (\"fine\" per uscire): ");
    letta = leggi_riga(ricerca, DIM);

    while (letta && !uguali_ignorando_maiuscole(ricerca, "fine")) {
        trovati = 0;
        if (ricerca[0] == '\0') {
            printf("  Scrivi almeno una lettera.\n");
        } else {
            for (k = 0; k < CONTATTI; k++) {
                if (inizia_con(cognomi[k], ricerca)) {
                    printf("  %-10s %-8s %s", cognomi[k], nomi[k], telefoni[k]);
                    if (uguali_ignorando_maiuscole(cognomi[k], ricerca)) {
                        printf("  (esatto)");
                    }
                    printf("\n");
                    trovati++;
                }
            }
            if (trovati == 0) {
                printf("  Nessun contatto trovato.\n");
            } else {
                printf("  %d %s\n", trovati, trovati == 1 ? "contatto" : "contatti");
            }
        }
        printf("Cognome o sua parte iniziale (\"fine\" per uscire): ");
        letta = leggi_riga(ricerca, DIM);
    }
    printf("Arrivederci.\n");

    return 0;
}

int leggi_riga(char s[], int dim)
{
    int ok = 0;
    int i = 0;
    int c;

    if (fgets(s, dim, stdin) != NULL) {
        ok = 1;
        while (s[i] != '\0' && s[i] != '\n') {
            i++;
        }
        if (s[i] == '\n') {
            s[i] = '\0';
        } else {
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    return ok;
}

/* 1 se s comincia con prefisso (maiuscole e minuscole indifferenti).
 * Il ciclo si ferma alla fine del prefisso o al primo carattere diverso:
 * il prefisso è trovato se è stato percorso tutto. */
int inizia_con(const char s[], const char prefisso[])
{
    int i = 0;

    while (prefisso[i] != '\0' && minuscola(s[i]) == minuscola(prefisso[i])) {
        i++;
    }
    return prefisso[i] == '\0';
}

/* 1 se a e b contengono lo stesso testo, maiuscole e minuscole indifferenti. */
int uguali_ignorando_maiuscole(const char a[], const char b[])
{
    int i = 0;

    while (minuscola(a[i]) == minuscola(b[i]) && a[i] != '\0') {
        i++;
    }
    return minuscola(a[i]) == minuscola(b[i]);
}

char minuscola(char c)
{
    char risultato = c;

    if (c >= 'A' && c <= 'Z') {
        risultato = c + ('a' - 'A');
    }
    return risultato;
}
