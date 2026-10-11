/*
 * 010-classificazione-caratteri.c
 *
 * Riconoscere il tipo di un carattere con <ctype.h>
 *
 * Invece di confrontare i codici ASCII a mano (c >= 'a' && c <= 'z') si
 * usano le funzioni di <ctype.h>. Restituiscono un valore diverso da 0
 * (vero) oppure 0 (falso):
 *
 *   isalpha(c)   lettera               isdigit(c)   cifra 0-9
 *   isupper(c)   lettera maiuscola     islower(c)   lettera minuscola
 *   isalnum(c)   lettera o cifra       isspace(c)   spazio, tab, a capo
 *   ispunct(c)   segno di punteggiatura (né lettera, né cifra, né spazio)
 *
 * Attenzione: "vero" non vale per forza 1. Si scrive  if (isdigit(c)),
 * mai  if (isdigit(c) == 1).
 *
 * Le funzioni accettano un int che deve essere un valore di unsigned char
 * (oppure EOF). Le lettere accentate in alcune codifiche sono char
 * negativi: per sicurezza il carattere si converte con un cast,
 *
 *     isalpha((unsigned char) s[i])
 *
 * Esempio: analisi della composizione di una frase.
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char frase[] = "Lezione 3: il C e' nato nel 1972, ok?";
    int i = 0;
    int lettere = 0;
    int maiuscole = 0;
    int cifre = 0;
    int spazi = 0;
    int punteggiatura = 0;
    unsigned char c;

    printf("Frase: \"%s\"\n\n", frase);
    printf("Car. alpha digit upper space punct\n");
    while (frase[i] != '\0') {
        c = (unsigned char) frase[i];
        if (i < 10) {                   /* tabella dei primi 10 caratteri */
            printf(" '%c'  %5d %5d %5d %5d %5d\n", c,
                   isalpha(c) != 0, isdigit(c) != 0, isupper(c) != 0,
                   isspace(c) != 0, ispunct(c) != 0);
        }
        if (isalpha(c)) {
            lettere++;
            if (isupper(c)) {
                maiuscole++;
            }
        } else if (isdigit(c)) {
            cifre++;
        } else if (isspace(c)) {
            spazi++;
        } else if (ispunct(c)) {
            punteggiatura++;
        }
        i++;
    }

    printf("...\n\nRiepilogo su %d caratteri:\n", i);
    printf("  lettere        %2d (di cui maiuscole %d)\n", lettere, maiuscole);
    printf("  cifre          %2d\n", cifre);
    printf("  spazi          %2d\n", spazi);
    printf("  punteggiatura  %2d\n", punteggiatura);

    return 0;
}
