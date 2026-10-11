/*
 * 020-strstr.c
 *
 * Cercare una parola (sottostringa) dentro una stringa
 *
 *   strstr(s, parola)   cerca la prima occorrenza di parola dentro s;
 *                       restituisce NULL se non c'è
 *
 * Come strchr, restituisce un puntatore: qui lo si usa solo per sapere se
 * la parola è presente.
 *
 *     if (strstr(descrizione, "USB") != NULL)
 *
 * Per conoscere la POSIZIONE si scrive la funzione cerca_da(s, parola, da),
 * che restituisce l'indice della prima occorrenza a partire dall'indice da
 * (oppure -1). Per ogni posizione i si controlla se la parola "combacia"
 * con i caratteri di s che partono da i:
 *
 *     s      = "cavo USB-C 2 metri"
 *     parola =      "USB"            combacia in i = 5
 *
 * La ricerca distingue maiuscole e minuscole: "usb" non trova "USB".
 *
 * Esempio: ricerca di parole chiave nelle descrizioni dei prodotti di un
 * negozio di elettronica.
 */

#include <stdio.h>
#include <string.h>

#define PRODOTTI 5
#define LUNG     40

int combacia(const char s[], const char parola[], int i);
int cerca_da(const char s[], const char parola[], int da);

int main(void)
{
    char descrizioni[PRODOTTI][LUNG] = {
        "Cavo USB-C 2 metri",
        "Mouse wireless con ricevitore USB",
        "Cuffie Bluetooth con cavo",
        "Hub USB 4 porte con cavo USB-C",
        "Tastiera wireless italiana"
    };
    char parole[3][LUNG] = {"USB", "wireless", "usb"};
    int p;
    int k;
    int trovati;
    int prima;
    int seconda;

    for (p = 0; p < 3; p++) {
        printf("=== Prodotti che contengono \"%s\" ===\n", parole[p]);
        trovati = 0;
        for (k = 0; k < PRODOTTI; k++) {
            if (strstr(descrizioni[k], parole[p]) != NULL) {
                trovati++;
                printf("  %-34s posizione %d\n", descrizioni[k],
                       cerca_da(descrizioni[k], parole[p], 0));
            }
        }
        if (trovati == 0) {
            printf("  (nessuno: la ricerca distingue maiuscole e minuscole)\n");
        }
        printf("\n");
    }

    /* cerca_da permette di proseguire dopo la prima occorrenza */
    prima = cerca_da(descrizioni[3], "USB", 0);
    seconda = cerca_da(descrizioni[3], "USB", prima + 1);
    printf("In \"%s\":\n", descrizioni[3]);
    printf("  prima occorrenza di USB  : %d\n", prima);
    printf("  seconda occorrenza di USB: %d\n", seconda);
    printf("  terza occorrenza di USB  : %d\n", cerca_da(descrizioni[3], "USB", seconda + 1));

    return 0;
}

/* 1 se i caratteri di s che partono dall'indice i coincidono con parola. */
int combacia(const char s[], const char parola[], int i)
{
    int j = 0;

    while (parola[j] != '\0' && s[i + j] == parola[j]) {
        j++;
    }
    return parola[j] == '\0';
}

/* Indice della prima occorrenza di parola in s a partire da da, oppure -1. */
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
