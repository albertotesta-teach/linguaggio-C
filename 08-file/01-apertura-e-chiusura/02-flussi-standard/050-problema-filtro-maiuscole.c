/*
 * 050-problema-filtro-maiuscole.c
 *
 * Un filtro: da stdin a stdout, trasformando il testo
 *
 * I cartelli per l'open day si stampano tutti in maiuscolo. Un filtro è
 * un programma che legge stdin, trasforma e scrive su stdout, senza
 * aprire file: si combina con la redirezione.
 *
 *     ./050-problema-filtro-maiuscole < cartelli.txt > stampa.txt
 *
 * Il filtro converte le lettere minuscole con toupper e lascia
 * invariato il resto. Le lettere accentate non sono convertite da
 * toupper (non sono caratteri ASCII): il filtro le conta e, alla fine,
 * le segnala su stderr, così l'avviso compare a video anche quando
 * stdout va in un file.
 *
 * Il resoconto finale (caratteri letti, lettere convertite) va anch'esso
 * su stderr: su stdout deve uscire SOLO il testo trasformato, altrimenti
 * il file prodotto conterrebbe anche i messaggi.
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int letti = 0;
    int convertite = 0;
    int non_ascii = 0;
    int c;

    c = fgetc(stdin);
    while (c != EOF) {
        letti++;
        if (islower(c)) {
            c = toupper(c);
            convertite++;
        } else if (c > 127) {
            non_ascii++;
        }
        fputc(c, stdout);
        c = fgetc(stdin);
    }
    fprintf(stderr, "[filtro] caratteri letti: %d, lettere convertite: %d\n", letti, convertite);
    if (non_ascii > 0) {
        fprintf(stderr,
                "[filtro] attenzione: %d byte non ASCII (lettere accentate?) non convertiti\n",
                non_ascii);
    }

    return 0;
}
