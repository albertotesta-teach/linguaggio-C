/*
 * 030-redirezione.c
 *
 * Un programma che legge stdin fino alla fine: la redirezione
 *
 * Un programma che legge da stdin e scrive su stdout non sa da dove
 * arrivano i dati né dove vanno: lo decide chi lo esegue, con la
 * redirezione del terminale.
 *
 *     ./030-redirezione                      tastiera -> schermo
 *     ./030-redirezione < saluto.txt         il file al posto della tastiera
 *     ./030-redirezione > conteggio.txt      i risultati in un file
 *     ./030-redirezione 2> errori.txt        i messaggi di stderr in un file
 *     ./030-redirezione < a.txt > b.txt      entrambe
 *
 * Il file viene aperto dal sistema operativo prima che il programma
 * parta: il programma non chiama fopen e funziona uguale.
 *
 * Da tastiera la fine dei dati si segnala con Ctrl+D (Linux e macOS) o
 * Ctrl+Z seguito da Invio (Windows): fgetc(stdin) restituisce EOF.
 *
 * Il programma conta caratteri, righe e parole (sequenze di caratteri
 * che non sono spazi). I risultati vanno su stdout; su stderr va solo il
 * messaggio iniziale, così con > il file contiene solo i risultati.
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int caratteri = 0;
    int righe = 0;
    int parole = 0;
    int in_parola = 0;
    int c;

    fprintf(stderr, "Testo da contare (Ctrl+D per finire):\n");
    c = fgetc(stdin);
    while (c != EOF) {
        caratteri++;
        if (c == '\n') {
            righe++;
        }
        if (isspace(c)) {
            in_parola = 0;
        } else if (!in_parola) {
            in_parola = 1;
            parole++;
        }
        c = fgetc(stdin);
    }
    fprintf(stdout, "caratteri: %d\nparole:    %d\nrighe:     %d\n", caratteri, parole, righe);

    return 0;
}
