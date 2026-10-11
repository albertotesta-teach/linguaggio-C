/*
 * 010-valori-di-verita.c
 *
 * Vero e falso in linguaggio C
 *
 * Ogni struttura di controllo (if, switch, while, for) decide cosa fare
 * valutando una CONDIZIONE. Prima di usarle bisogna sapere che cosa il C
 * considera "vero" e che cosa considera "falso".
 *
 * Il C (nella versione C89/C90 usata nel corso) non ha un tipo booleano:
 *   - il valore 0 significa FALSO
 *   - qualunque valore diverso da 0 significa VERO (1, -5, 42, 0.5, ...)
 *
 * Gli operatori relazionali (==, !=, <, >, <=, >=) e logici (&&, ||, !)
 * producono sempre il valore int 1 (vero) oppure 0 (falso).
 * Questi operatori sono già stati presentati nel capitolo 01
 * (01-introduzione/04-operatori/020-operatori-relazionali-e-logici.c):
 * qui li riprendiamo dal punto di vista della logica.
 */

#include <stdio.h>

int main(void)
{
    int temperatura = 23;
    int posti_liberi = 0;
    int saldo = -150;

    int fa_caldo;
    int sala_piena;
    int in_rosso;

    /* ── 1. Un confronto vale 1 oppure 0 ──────────────────────────────── */
    printf("=== Il risultato di un confronto ===\n");
    printf("temperatura = %d\n", temperatura);
    printf("temperatura > 20   vale %d  (vero)\n",  temperatura > 20);
    printf("temperatura > 30   vale %d  (falso)\n", temperatura > 30);
    printf("temperatura == 23  vale %d  (vero)\n",  temperatura == 23);
    printf("\n");

    /* ── 2. Il risultato si può memorizzare in una variabile ───────────── */
    /* Una variabile che contiene solo 0 o 1 si chiama variabile
     * BOOLEANA (o flag). Si sceglie un nome che sia una domanda
     * con risposta sì/no: fa_caldo, sala_piena, in_rosso. */
    fa_caldo   = (temperatura > 25);
    sala_piena = (posti_liberi == 0);
    in_rosso   = (saldo < 0);

    printf("=== Variabili booleane ===\n");
    printf("fa_caldo   = %d\n", fa_caldo);
    printf("sala_piena = %d\n", sala_piena);
    printf("in_rosso   = %d\n", in_rosso);
    printf("\n");

    /* ── 3. Qualsiasi valore diverso da 0 è vero ───────────────────────── */
    /* L'operatore ! (NOT) restituisce 1 se l'operando è 0, altrimenti 0.
     * Applicandolo due volte (!!x) si ottiene la "versione booleana"
     * di un numero qualsiasi: 0 resta 0, tutto il resto diventa 1. */
    printf("=== Che cosa e' vero per il C ===\n");
    printf("valore    0 -> come condizione vale %d (falso)\n", !!0);
    printf("valore    1 -> come condizione vale %d (vero)\n",  !!1);
    printf("valore   42 -> come condizione vale %d (vero)\n",  !!42);
    printf("valore   -7 -> come condizione vale %d (vero)\n",  !!(-7));
    printf("valore saldo (%d) -> vale %d (vero: e' diverso da 0)\n",
           saldo, !!saldo);
    printf("valore posti_liberi (%d) -> vale %d (falso)\n",
           posti_liberi, !!posti_liberi);
    printf("\n");

    /* ── 4. Dal valore di verità a un messaggio ───────────────────────── */
    /* Non abbiamo ancora l'istruzione if: per scegliere il messaggio
     * usiamo l'operatore ternario, visto nel capitolo 01.
     *     condizione ? valore_se_vera : valore_se_falsa                 */
    printf("=== Stampa leggibile ===\n");
    printf("Fa caldo?       %s\n", fa_caldo   ? "si'" : "no");
    printf("Sala piena?     %s\n", sala_piena ? "si'" : "no");
    printf("Conto in rosso? %s\n", in_rosso  ? "si'" : "no");

    /*
     * ERRORE COMUNE: confondere = (assegnazione) con == (confronto).
     *
     *   sala_piena = (posti_liberi = 0);   // ERRATO: assegna 0 a posti_liberi
     *                                      // e l'espressione vale 0 (falso)
     *   sala_piena = (posti_liberi == 0);  // CORRETTO: confronta
     *
     * Con -Wall il compilatore segnala spesso questo errore quando
     * l'assegnazione compare dentro una condizione.
     */

    return 0;
}
