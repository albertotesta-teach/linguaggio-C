/*
 * 010-stdin-stdout-stderr.c
 *
 * I tre flussi già aperti: stdin, stdout e stderr
 *
 * Ogni programma C parte con tre FILE * già aperti, dichiarati in
 * <stdio.h>, che non si aprono e non si chiudono:
 *
 *     stdin    ingresso standard     di solito la tastiera
 *     stdout   uscita standard       di solito lo schermo
 *     stderr   uscita degli errori   di solito lo schermo
 *
 * Le funzioni già note sono scorciatoie che li usano:
 *
 *     printf(...)        equivale a  fprintf(stdout, ...)
 *     putchar(c)         equivale a  fputc(c, stdout)
 *     scanf(...)         equivale a  fscanf(stdin, ...)
 *     getchar()          equivale a  fgetc(stdin)
 *
 * stdout e stderr finiscono entrambi sullo schermo, ma sono due canali
 * distinti: con la redirezione (030-redirezione) si possono separare,
 * mandando i risultati in un file e lasciando i messaggi di errore a
 * video. Per questo gli errori si scrivono sempre su stderr.
 *
 * C'è anche una differenza di buffer: stderr non ha buffer e scrive
 * subito; stdout verso un file scrive a blocchi (020-buffer-e-fflush in
 * 03-file-in-pratica).
 *
 * Il programma legge le età dei partecipanti a un torneo per ragazzi
 * (da 11 a 14 anni) fino a 0: le età valide vanno su stdout, gli
 * scarti su stderr.
 */

#include <stdio.h>

#define MINIMA 11
#define MASSIMA 14

int main(void)
{
    int eta = -1;
    int valide = 0;
    int scartate = 0;

    fprintf(stdout, "Eta' dei partecipanti (0 per finire):\n");
    while (eta != 0) {
        if (scanf("%d", &eta) != 1) {
            eta = 0;
        } else if (eta != 0 && (eta < MINIMA || eta > MASSIMA)) {
            fprintf(stderr, "  scarto: %d anni non e' tra %d e %d\n", eta, MINIMA, MASSIMA);
            scartate++;
        } else if (eta != 0) {
            fprintf(stdout, "  iscritto: %d anni\n", eta);
            valide++;
        }
    }
    fprintf(stdout, "Iscritti: %d\n", valide);
    fputs("Fine dell'elaborazione.\n", stdout);
    if (scartate > 0) {
        fprintf(stderr, "Eta' scartate: %d\n", scartate);
    }

    return 0;
}
