/*
 * 010-strlen-e-strcpy.c
 *
 * Lunghezza e copia con la libreria <string.h>
 *
 * Le funzioni scritte a mano nella sezione 01 esistono già nella libreria
 * standard. Per usarle si include <string.h>.
 *
 *   strlen(s)              lunghezza di s, '\0' escluso
 *   strcpy(dest, sorg)     copia sorg in dest, '\0' compreso
 *   strncpy(dest, sorg, n) copia AL MASSIMO n caratteri
 *
 * strlen restituisce un valore di tipo size_t (un intero senza segno):
 * per stamparlo si usa %zu, oppure lo si converte in int con un cast.
 *
 * strcpy non conosce la dimensione di dest: se sorg è troppo lunga scrive
 * oltre la fine dell'array. strncpy riceve un limite, ma ha un difetto da
 * conoscere: se sorg ha n caratteri o più, NON aggiunge il '\0'. Dopo
 * strncpy bisogna quindi terminare la stringa a mano:
 *
 *     strncpy(dest, sorg, sizeof(dest) - 1);
 *     dest[sizeof(dest) - 1] = '\0';
 *
 * sizeof(dest) funziona solo dove dest è dichiarato come array (qui nel
 * main); dentro una funzione il parametro char s[] non conosce la propria
 * dimensione.
 */

#include <stdio.h>
#include <string.h>

#define DIM 8

int main(void)
{
    char citta[] = "Alessandria";
    char copia[30];
    char sigla[DIM];
    char breve[DIM];

    /* ── 1. strlen e sizeof sono cose diverse ─────────────────────── */
    printf("=== strlen ===\n");
    printf("strlen(\"%s\") = %zu caratteri\n", citta, strlen(citta));
    printf("sizeof(citta)  = %zu celle (caratteri + '\\0')\n", sizeof(citta));
    printf("sizeof(copia)  = %zu celle, anche se ancora vuoto\n\n", sizeof(copia));

    /* ── 2. strcpy: dest abbastanza grande ────────────────────────── */
    printf("=== strcpy ===\n");
    strcpy(copia, citta);
    printf("copia = \"%s\"\n", copia);
    strcpy(copia, "Asti");              /* sovrascrive: il vecchio testo sparisce */
    printf("dopo strcpy(copia, \"Asti\"): \"%s\" (%d caratteri)\n\n",
           copia, (int) strlen(copia));

    /* ── 3. strncpy con testo corto: il '\0' viene copiato ────────── */
    printf("=== strncpy ===\n");
    strncpy(sigla, "AL", sizeof(sigla) - 1);
    sigla[sizeof(sigla) - 1] = '\0';
    printf("sigla = \"%s\"\n", sigla);

    /* ── 4. strncpy con testo lungo: il '\0' va aggiunto a mano ───── */
    strncpy(breve, citta, sizeof(breve) - 1);
    breve[sizeof(breve) - 1] = '\0';
    printf("breve = \"%s\" (troncata a %zu caratteri)\n", breve, sizeof(breve) - 1);
    printf("Senza breve[%zu] = '\\0' la stringa non avrebbe terminatore.\n",
           sizeof(breve) - 1);

    return 0;
}
