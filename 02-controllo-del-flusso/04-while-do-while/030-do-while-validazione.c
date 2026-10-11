/*
 * 030-do-while-validazione.c
 *
 * Il ciclo do-while: eseguire il corpo almeno una volta
 *
 * Il do-while controlla la condizione DOPO il corpo:
 *
 *     do {
 *         corpo del ciclo
 *     } while (condizione);      <- notare il punto e virgola finale
 *
 * Il corpo viene quindi eseguito sempre almeno una volta. È la scelta
 * naturale quando bisogna FARE qualcosa prima di poter decidere se
 * ripeterlo, come:
 *   - chiedere un dato e ripetere la domanda finché non è valido;
 *   - mostrare un menu e ripeterlo finché l'utente non sceglie di uscire.
 *
 *   while:     controlla -> esegue -> controlla -> ...   (0 o più volte)
 *   do-while:  esegue -> controlla -> esegue -> ...      (1 o più volte)
 */

#include <stdio.h>

int main(void)
{
    int voto;
    int tentativi = 0;
    char risposta;
    int studenti = 0;
    int somma_voti = 0;

    printf("=== REGISTRO VOTI ===\n");

    do {
        /* ── Validazione dell'input ───────────────────────────────────
         * La domanda va posta almeno una volta: il do-while è perfetto.
         * La condizione di ripetizione è la NEGAZIONE della condizione
         * di validità (De Morgan, vedi 01-logica-booleana):
         *     valido:      voto >= 1 && voto <= 10
         *     da ripetere: voto <  1 || voto >  10                       */
        tentativi = 0;
        do {
            printf("Voto dello studente %d (1-10): ", studenti + 1);
            scanf("%d", &voto);
            tentativi++;

            if (voto < 1 || voto > 10) {
                printf("  Voto non valido, riprova.\n");
            }
        } while (voto < 1 || voto > 10);

        if (tentativi > 1) {
            printf("  (voto accettato dopo %d tentativi)\n", tentativi);
        }

        studenti++;
        somma_voti = somma_voti + voto;

        /* ── Ripetizione su richiesta ──────────────────────────────── */
        printf("Inserire un altro voto? (s/n): ");
        scanf(" %c", &risposta);

    } while (risposta == 's' || risposta == 'S');

    printf("\nStudenti: %d, media dei voti: %.2f\n",
           studenti, (double)somma_voti / studenti);

    /*
     * ERRORI COMUNI
     *
     * 1) Dimenticare il punto e virgola dopo while (...) nel do-while:
     *    errore di compilazione.
     *
     * 2) Scrivere la condizione di VALIDITÀ invece di quella di RIPETIZIONE:
     *        } while (voto >= 1 && voto <= 10);
     *    il ciclo ripeterebbe la domanda proprio quando il voto è giusto.
     *
     * 3) Leggere un carattere con "%c" senza lo spazio: verrebbe letto
     *    l'invio rimasto dopo il numero precedente.
     */

    return 0;
}
