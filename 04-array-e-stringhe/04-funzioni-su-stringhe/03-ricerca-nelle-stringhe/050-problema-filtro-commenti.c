/*
 * 050-problema-filtro-commenti.c
 *
 * Censurare le parole vietate nei commenti di un forum scolastico
 *
 * Prima di pubblicare un commento, il forum della scuola sostituisce con
 * asterischi le parole presenti in un elenco di parole vietate:
 *
 *     "Che compito STUPIDO, sei proprio uno stupido"
 *  -> "Che compito *******, sei proprio uno *******"
 *
 * La ricerca non deve distinguere maiuscole e minuscole. Per questo si
 * lavora su una copia del commento convertita in minuscolo: le posizioni
 * trovate nella copia valgono anche per l'originale, perché i due testi
 * hanno la stessa lunghezza.
 *
 * Per ogni parola vietata:
 *   - strstr() dice subito se la parola compare nel commento;
 *   - in caso affermativo cerca_da() trova tutte le posizioni e
 *     oscura() sostituisce i caratteri con '*'.
 *
 * Il programma legge un commento per riga finché non riceve una riga vuota.
 */

#include <stdio.h>
#include <string.h>

#define DIM     100
#define VIETATE 4
#define LUNG    16

int leggi_riga(char s[], int dim);
void in_minuscolo(char dest[], const char sorg[]);
int combacia(const char s[], const char parola[], int i);
int cerca_da(const char s[], const char parola[], int da);
void oscura(char s[], int inizio, int n);

int main(void)
{
    char vietate[VIETATE][LUNG] = {"stupido", "idiota", "schifo", "cretino"};
    char commento[DIM];
    char minuscolo[DIM];
    int letta;
    int v;
    int posizione;
    int sostituzioni;

    printf("=== FORUM DELLA CLASSE ===\n");
    printf("Commento (riga vuota per terminare): ");
    letta = leggi_riga(commento, DIM);

    while (letta && commento[0] != '\0') {
        in_minuscolo(minuscolo, commento);
        sostituzioni = 0;

        for (v = 0; v < VIETATE; v++) {
            if (strstr(minuscolo, vietate[v]) != NULL) {
                posizione = cerca_da(minuscolo, vietate[v], 0);
                while (posizione != -1) {
                    oscura(commento, posizione, (int) strlen(vietate[v]));
                    sostituzioni++;
                    posizione = cerca_da(minuscolo, vietate[v], posizione + 1);
                }
            }
        }

        if (sostituzioni == 0) {
            printf("  Pubblicato: %s\n", commento);
        } else {
            printf("  Pubblicato con %d %s: %s\n", sostituzioni,
                   sostituzioni == 1 ? "parola oscurata" : "parole oscurate", commento);
        }
        printf("Commento (riga vuota per terminare): ");
        letta = leggi_riga(commento, DIM);
    }
    printf("Fine moderazione.\n");

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

/* Copia sorg in dest convertendo le lettere maiuscole in minuscole. */
void in_minuscolo(char dest[], const char sorg[])
{
    int i = 0;

    while (sorg[i] != '\0') {
        if (sorg[i] >= 'A' && sorg[i] <= 'Z') {
            dest[i] = sorg[i] + ('a' - 'A');
        } else {
            dest[i] = sorg[i];
        }
        i++;
    }
    dest[i] = '\0';
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

/* Sostituisce con '*' gli n caratteri di s che partono da inizio. */
void oscura(char s[], int inizio, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        s[inizio + i] = '*';
    }
}
