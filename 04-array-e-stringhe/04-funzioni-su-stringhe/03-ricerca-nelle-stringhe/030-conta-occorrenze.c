/*
 * 030-conta-occorrenze.c
 *
 * Contare quante volte una parola compare in un testo
 *
 * Si ripete la ricerca con cerca_da(), ripartendo ogni volta subito dopo
 * l'occorrenza trovata:
 *
 *     posizione = cerca_da(testo, parola, 0);
 *     while (posizione != -1) {
 *         conteggio++;
 *         posizione = cerca_da(testo, parola, posizione + passo);
 *     }
 *
 * Il valore di "passo" decide se le occorrenze possono sovrapporsi:
 *   - passo = 1                 occorrenze sovrapposte:  "aa" in "aaaa" -> 3
 *   - passo = strlen(parola)    occorrenze separate:     "aa" in "aaaa" -> 2
 *
 * Per una parola vera (non solo un gruppo di lettere) bisogna anche
 * controllare che prima e dopo non ci sia un'altra lettera: "re" compare in
 * "mare" e in "orecchio", ma come parola intera solo in "il re".
 *
 * Esempio: analisi di un breve testo per un esercizio di italiano.
 */

#include <stdio.h>
#include <string.h>

int combacia(const char s[], const char parola[], int i);
int cerca_da(const char s[], const char parola[], int da);
int conta(const char s[], const char parola[], int sovrapposte);
int conta_parole_intere(const char s[], const char parola[]);
int e_lettera(char c);

int main(void)
{
    char testo[] = "il re va al mare e vede le onde: il mare urla, il re ride e corre";
    char ripetuto[] = "aaaa";

    printf("Testo: \"%s\"\n\n", testo);

    printf("=== Occorrenze come gruppo di lettere ===\n");
    printf("  \"il\"   : %d\n", conta(testo, "il", 0));
    printf("  \"re\"   : %d\n", conta(testo, "re", 0));
    printf("  \"mare\" : %d\n\n", conta(testo, "mare", 0));

    printf("=== Occorrenze come parola intera ===\n");
    printf("  \"il\"   : %d\n", conta_parole_intere(testo, "il"));
    printf("  \"re\"   : %d\n", conta_parole_intere(testo, "re"));
    printf("  \"mare\" : %d\n\n", conta_parole_intere(testo, "mare"));

    printf("=== Sovrapposte o separate ===\n");
    printf("  \"aa\" in \"%s\": sovrapposte %d, separate %d\n",
           ripetuto, conta(ripetuto, "aa", 1), conta(ripetuto, "aa", 0));

    return 0;
}

int combacia(const char s[], const char parola[], int i)
{
    int j = 0;

    while (parola[j] != '\0' && s[i + j] == parola[j]) {
        j++;
    }
    return parola[j] == '\0';
}

int cerca_da(const char s[], const char parola[], int da)
{
    int i = da;
    int posizione = -1;

    while (s[i] != '\0' && posizione == -1) {
        if (combacia(s, parola, i)) {
            posizione = i;
        }
        i++;
    }
    return posizione;
}

/* Conta le occorrenze di parola in s; con sovrapposte = 1 si riparte dal
 * carattere successivo, altrimenti dopo la fine dell'occorrenza. */
int conta(const char s[], const char parola[], int sovrapposte)
{
    int conteggio = 0;
    int passo;
    int posizione;

    passo = sovrapposte ? 1 : (int) strlen(parola);
    posizione = cerca_da(s, parola, 0);
    while (posizione != -1) {
        conteggio++;
        posizione = cerca_da(s, parola, posizione + passo);
    }
    return conteggio;
}

/* Conta le occorrenze di parola non precedute né seguite da una lettera. */
int conta_parole_intere(const char s[], const char parola[])
{
    int conteggio = 0;
    int lung;
    int posizione;
    int inizio_ok;
    int fine_ok;

    lung = (int) strlen(parola);
    posizione = cerca_da(s, parola, 0);
    while (posizione != -1) {
        inizio_ok = (posizione == 0) || !e_lettera(s[posizione - 1]);
        fine_ok = !e_lettera(s[posizione + lung]);    /* '\0' non è una lettera */
        if (inizio_ok && fine_ok) {
            conteggio++;
        }
        posizione = cerca_da(s, parola, posizione + 1);
    }
    return conteggio;
}

int e_lettera(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
