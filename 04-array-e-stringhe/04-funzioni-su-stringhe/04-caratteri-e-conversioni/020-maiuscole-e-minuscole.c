/*
 * 020-maiuscole-e-minuscole.c
 *
 * Convertire maiuscole e minuscole con toupper e tolower
 *
 *   toupper(c)   restituisce la maiuscola di c, se c è una lettera minuscola;
 *                altrimenti restituisce c invariato
 *   tolower(c)   il contrario
 *
 * Le funzioni lavorano su UN carattere e lo restituiscono: per convertire
 * una stringa si applicano a ogni carattere con un ciclo.
 *
 *   in_maiuscolo(s)            converte s sul posto
 *   iniziali_maiuscole(s)      "anna maria rossi" -> "Anna Maria Rossi"
 *   uguali_senza_maiuscole(a, b)
 *                              confronto che ignora le maiuscole, carattere
 *                              per carattere con tolower
 *
 * Esempio: preparazione dei dati di un'anagrafica prima del salvataggio.
 */

#include <stdio.h>
#include <ctype.h>

void in_maiuscolo(char s[]);
void iniziali_maiuscole(char s[]);
int uguali_senza_maiuscole(const char a[], const char b[]);

int main(void)
{
    char codice[] = "rss mra 85t10 a944s";
    char nome[] = "aNNA mARIA de LUCA";
    char citta_1[] = "Alessandria";
    char citta_2[] = "ALESSANDRIA";

    printf("toupper('b') = '%c', toupper('B') = '%c', toupper('7') = '%c'\n\n",
           toupper('b'), toupper('B'), toupper('7'));

    printf("Codice prima : %s\n", codice);
    in_maiuscolo(codice);
    printf("Codice dopo  : %s\n\n", codice);

    printf("Nome prima   : %s\n", nome);
    iniziali_maiuscole(nome);
    printf("Nome dopo    : %s\n\n", nome);

    printf("\"%s\" e \"%s\": %s\n", citta_1, citta_2,
           uguali_senza_maiuscole(citta_1, citta_2) ? "stessa citta'" : "diverse");

    return 0;
}

/* Converte in maiuscolo tutte le lettere di s (modifica s). */
void in_maiuscolo(char s[])
{
    int i = 0;

    while (s[i] != '\0') {
        s[i] = (char) toupper((unsigned char) s[i]);
        i++;
    }
}

/* Prima lettera di ogni parola maiuscola, le altre minuscole. Una parola
 * inizia dopo uno spazio (o all'inizio della stringa). */
void iniziali_maiuscole(char s[])
{
    int i = 0;
    int inizio_parola = 1;

    while (s[i] != '\0') {
        if (inizio_parola) {
            s[i] = (char) toupper((unsigned char) s[i]);
        } else {
            s[i] = (char) tolower((unsigned char) s[i]);
        }
        inizio_parola = isspace((unsigned char) s[i]);
        i++;
    }
}

/* 1 se a e b contengono lo stesso testo, ignorando le maiuscole. */
int uguali_senza_maiuscole(const char a[], const char b[])
{
    int i = 0;

    while (a[i] != '\0' && tolower((unsigned char) a[i]) == tolower((unsigned char) b[i])) {
        i++;
    }
    return tolower((unsigned char) a[i]) == tolower((unsigned char) b[i]);
}
