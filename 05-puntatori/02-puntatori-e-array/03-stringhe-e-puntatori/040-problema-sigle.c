/*
 * 040-problema-sigle.c
 *
 * Generatore di sigle per la segreteria
 *
 * La segreteria di una scuola deve compilare moduli con la sigla degli enti
 * (ITIS, ASL, URP, ...). Il programma legge il nome completo di un ente e
 * costruisce la sigla con le iniziali maiuscole delle parole, saltando le
 * parole brevi (articoli e preposizioni come "di", "per", "il", "con").
 *
 * Regole:
 *   - una parola è una sequenza di lettere; spazi, apostrofi e trattini la
 *     separano ("l'Aviazione" contiene le parole "l" e "Aviazione");
 *   - si usano solo le parole con più di MAX_BREVE lettere.
 *
 * Un puntatore p scorre la riga; quando trova l'inizio di una parola ne
 * salva l'indirizzo in inizio e avanza fino alla fine della parola: la
 * lunghezza è p - inizio. Il '\n' letto da fgets si toglie con strchr.
 *
 * Il programma legge un nome per riga; una riga vuota termina.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LUNG      100
#define MAX_SIGLA 20
#define MAX_BREVE 3

void crea_sigla(const char *nome, char *sigla);

int main(void)
{
    char riga[LUNG];
    char sigla[MAX_SIGLA];
    char *a_capo;
    int continua = 1;

    printf("=== GENERATORE DI SIGLE ===\n");
    while (continua) {
        printf("Nome dell'ente (riga vuota per finire): ");
        if (fgets(riga, LUNG, stdin) == NULL) {
            continua = 0;
        } else {
            a_capo = strchr(riga, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            }
            if (riga[0] == '\0') {
                continua = 0;
            } else {
                crea_sigla(riga, sigla);
                printf("  Sigla: %s\n", sigla);
            }
        }
    }

    return 0;
}

/* Scrive in sigla le iniziali maiuscole delle parole di nome più lunghe
 * di MAX_BREVE lettere. sigla deve avere spazio per MAX_SIGLA caratteri. */
void crea_sigla(const char *nome, char *sigla)
{
    const char *p = nome;
    const char *inizio;
    char *s = sigla;

    while (*p != '\0') {
        if (isalpha((unsigned char) *p)) {
            inizio = p;
            while (isalpha((unsigned char) *p)) {
                p++;
            }
            if (p - inizio > MAX_BREVE && s < sigla + MAX_SIGLA - 1) {
                *s = (char) toupper((unsigned char) *inizio);
                s++;
            }
        } else {
            p++;
        }
    }
    *s = '\0';
}
