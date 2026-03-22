/*
 * 030-tappo-su-array-di-char.c
 *
 * Il tappo applicato agli array di caratteri: le stringhe C.
 *
 * Una stringa in C è esattamente un array di char con tappo '\0'.
 * Il valore '\0' (ASCII 0) svolge lo stesso ruolo che -1 svolge
 * negli array di interi non negativi: segnala la fine dei dati validi.
 *
 * Questo file mostra come le funzioni scritte per array a tappo di
 * interi si riscrivono in modo identico per array di char, evidenziando
 * l'unificazione concettuale tra "array a tappo" e "stringhe C".
 *
 * Le funzioni implementate qui — lunghezza_stringa, copia_stringa,
 * confronta_stringhe, concatena — sono versioni didattiche di strlen,
 * strcpy, strcmp, strcat dalla libreria standard <string.h>.
 */

#include <stdio.h>

#define MAX_STR 50

/* Lunghezza della stringa: conta i caratteri fino a '\0' (escluso).
 * Identico al conteggio fino al tappo negli array di interi. */
int lunghezza_stringa(const char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;   /* i = indice del '\0' = numero di caratteri validi */
}

/* Copia src in dst incluso il terminatore '\0'.
 * dst deve avere spazio sufficiente. */
void copia_stringa(char dst[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';   /* copia anche il tappo */
}

/* Confronta due stringhe carattere per carattere.
 * Restituisce 0 se uguali, valore non zero se diverse.
 * Si ferma al primo carattere diverso o al '\0'. */
int confronta_stringhe(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i]) {
        i++;
    }
    /* Se entrambe sono finite insieme e coincidono: uguali (diff = 0) */
    return a[i] - b[i];
}

/* Concatena src in fondo a dst (dopo il suo '\0').
 * dst deve avere spazio sufficiente per contenere entrambe. */
void concatena(char dst[], const char src[]) {
    int i = lunghezza_stringa(dst);   /* trova il '\0' di dst */
    int j = 0;
    while (src[j] != '\0') {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';   /* posiziona il nuovo tappo */
}

/* Inverte una stringa in-place (swap con variabile d'appoggio) */
void inverti_stringa(char s[]) {
    int len = lunghezza_stringa(s);
    int i;
    char temp;
    for (i = 0; i < len / 2; i++) {
        temp            = s[i];
        s[i]            = s[len - 1 - i];
        s[len - 1 - i]  = temp;
    }
}

int main(void) {

    printf("=== ARRAY DI CHAR CON TAPPO '\\0' ===\n\n");

    /* ---------------------------------------------------------------- */
    /* Visualizzazione del tappo in una stringa */
    char parola[] = "ciao";
    int i;

    printf("Struttura di \"%s\" in memoria:\n", parola);
    printf("  Indice | Char | ASCII\n");
    printf("  -------|------|------\n");
    for (i = 0; parola[i] != '\0'; i++) {
        printf("    %d    |  %c   |  %3d\n", i, parola[i], parola[i]);
    }
    printf("    %d    |  \\0  |    0  <- tappo\n\n", i);

    /* ---------------------------------------------------------------- */
    /* Lunghezza */
    char s1[] = "programmazione";
    char s2[] = "C";
    printf("lunghezza_stringa(\"%s\") = %d\n", s1, lunghezza_stringa(s1));
    printf("lunghezza_stringa(\"%s\")             = %d\n\n", s2, lunghezza_stringa(s2));

    /* ---------------------------------------------------------------- */
    /* Copia */
    char copia[MAX_STR];
    copia_stringa(copia, s1);
    printf("copia_stringa: \"%s\" -> \"%s\"\n\n", s1, copia);

    /* ---------------------------------------------------------------- */
    /* Confronto */
    char a[] = "mela";
    char b[] = "mela";
    char c[] = "pera";
    printf("confronta(\"%s\", \"%s\") = %d  (uguali)\n",
           a, b, confronta_stringhe(a, b));
    printf("confronta(\"%s\", \"%s\") = %d  (diverse)\n\n",
           a, c, confronta_stringhe(a, c));

    /* ---------------------------------------------------------------- */
    /* Concatenazione */
    char base[MAX_STR] = "linguaggio ";
    concatena(base, "C");
    printf("Dopo concatena: \"%s\"\n\n", base);

    /* ---------------------------------------------------------------- */
    /* Inversione */
    char da_invertire[] = "abcdef";
    printf("Prima inversione : \"%s\"\n", da_invertire);
    inverti_stringa(da_invertire);
    printf("Dopo inversione  : \"%s\"\n\n", da_invertire);

    /* ---------------------------------------------------------------- */
    /* Riepilogo concettuale */
    printf("=== CONFRONTO TAPPI ===\n");
    printf("  Array int a tappo : while (arr[i] != -1)  { ... i++; }\n");
    printf("  Stringa C         : while (str[i] != '\\0') { ... i++; }\n");
    printf("  Stesso pattern, tappo diverso.\n");

    return 0;
}
