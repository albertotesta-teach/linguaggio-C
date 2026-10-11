/*
 * 060-problema-giudizio-voto.c
 *
 * Dal voto numerico al giudizio e al livello di apprendimento
 *
 * Nel registro elettronico ogni voto in decimi è accompagnato da un
 * giudizio sintetico e da un livello di apprendimento:
 *
 *   voto   giudizio                   livello
 *   1-3    gravemente insufficiente   non raggiunto
 *   4      insufficiente              non raggiunto
 *   5      mediocre                   in via di acquisizione
 *   6      sufficiente                base
 *   7      discreto                   intermedio
 *   8      buono                      intermedio
 *   9      distinto                   avanzato
 *   10     ottimo                     avanzato
 *
 * Il programma usa due switch: il primo ha (quasi) un ramo per voto, il
 * secondo raggruppa i voti che corrispondono allo stesso livello.
 * Il voto viene letto come intero (non sono previsti mezzi voti).
 */

#include <stdio.h>

int main(void)
{
    int voto;
    int voto_valido;

    printf("=== REGISTRO - GIUDIZIO DEL VOTO ===\n\n");
    printf("Voto in decimi (1-10): ");
    scanf("%d", &voto);

    voto_valido = (voto >= 1 && voto <= 10);

    if (!voto_valido) {
        printf("\nVoto %d non valido.\n", voto);
    } else {
        /* ── Giudizio sintetico ────────────────────────────────────── */
        printf("\nGiudizio: ");
        switch (voto) {
            case 1:
            case 2:
            case 3:
                printf("gravemente insufficiente\n");
                break;
            case 4:
                printf("insufficiente\n");
                break;
            case 5:
                printf("mediocre\n");
                break;
            case 6:
                printf("sufficiente\n");
                break;
            case 7:
                printf("discreto\n");
                break;
            case 8:
                printf("buono\n");
                break;
            case 9:
                printf("distinto\n");
                break;
            case 10:
                printf("ottimo\n");
                break;
            default:
                printf("-\n");
                break;
        }

        /* ── Livello di apprendimento ─────────────────────────────────
         * Il default non può essere raggiunto perché il voto è già
         * stato controllato, ma va scritto comunque: protegge da
         * modifiche future del codice.                                 */
        printf("Livello di apprendimento: ");
        switch (voto) {
            case 1:
            case 2:
            case 3:
            case 4:
                printf("non raggiunto\n");
                break;
            case 5:
                printf("in via di acquisizione\n");
                break;
            case 6:
                printf("base\n");
                break;
            case 7:
            case 8:
                printf("intermedio\n");
                break;
            case 9:
            case 10:
                printf("avanzato\n");
                break;
            default:
                printf("-\n");
                break;
        }

        /* Sufficienza: una condizione su un intervallo si esprime meglio
         * con un if che con uno switch. */
        if (voto >= 6) {
            printf("Esito: SUFFICIENTE\n");
        } else {
            printf("Esito: INSUFFICIENTE - %s %d %s alla sufficienza\n",
                   6 - voto == 1 ? "manca" : "mancano",
                   6 - voto,
                   6 - voto == 1 ? "punto" : "punti");
        }
    }

    /*
     * switch o catena else-if?
     * Qui i valori possibili sono pochi e discreti (1..10): lo switch li
     * elenca come una tabella. Per il controllo "voto >= 6" serve invece
     * un intervallo, e si torna all'if.
     */

    return 0;
}
