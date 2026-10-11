/*
 * 030-combinazione-di-operatori.c
 *
 * Come si combinano gli operatori in una condizione
 *
 * Una condizione reale contiene quasi sempre più operatori:
 *     (eta < 6 || residente) && feriale
 * Per scriverla (e leggerla) correttamente servono quattro strumenti:
 *
 *   1. la PRECEDENZA degli operatori e l'uso delle parentesi
 *   2. le condizioni "dentro" e "fuori" da un intervallo
 *   3. le leggi di DE MORGAN, per negare una condizione composta
 *   4. la valutazione a CORTO CIRCUITO
 */

#include <stdio.h>

int main(void)
{
    int eta = 4;
    int residente = 0;
    int feriale = 0;      /* 0 = oggi è domenica */
    int ora = 21;
    int voto = 5;
    int divisore = 0;
    int dividendo = 10;

    int come_la_legge_il_c;
    int come_volevamo;

    /* ── 1. Precedenza ─────────────────────────────────────────────────
     *
     *   più alta    !                    (NOT, unario)
     *               <  >  <=  >=
     *               ==  !=
     *               &&                   (AND)
     *   più bassa   ||                   (OR)
     *
     * Quindi && "lega" più di ||, come in aritmetica * lega più di +.
     *     a || b && c   si legge   a || (b && c)
     *
     * Regola del museo: ingresso gratuito per i bambini sotto i 6 anni
     * oppure per i residenti, ma SOLO nei giorni feriali.
     * Scritta senza parentesi:
     *     eta < 6 || residente && feriale
     * il C la legge come  eta < 6 || (residente && feriale)
     * e così la limitazione ai giorni feriali vale solo per i residenti.
     *
     * gcc con -Wall segnala proprio questa situazione con il warning
     * "suggest parentheses around '&&' within '||'": il codice del corso
     * deve compilare senza warning, quindi le parentesi si scrivono sempre.
     */
    printf("=== 1. Precedenza: && prima di || ===\n");
    printf("eta = %d, residente = %d, feriale = %d\n", eta, residente, feriale);

    come_la_legge_il_c = eta < 6 || (residente && feriale);
    come_volevamo      = (eta < 6 || residente) && feriale;

    printf("eta < 6 || (residente && feriale)   -> %d  (gratis anche di domenica)\n",
           come_la_legge_il_c);
    printf("(eta < 6 || residente) && feriale   -> %d  (regola corretta)\n",
           come_volevamo);
    printf("Regola pratica: quando && e || compaiono insieme, usare le parentesi.\n");
    printf("\n");

    /* ── 2. Intervalli ──────────────────────────────────────────────────
     *
     *   DENTRO [min, max]   valore >= min && valore <= max
     *   FUORI  [min, max]   valore <  min || valore >  max
     *
     * Notare che "dentro" usa && mentre "fuori" usa ||:
     * un valore non può essere contemporaneamente minore di min
     * e maggiore di max.
     */
    printf("=== 2. Intervalli ===\n");
    printf("ora = %d\n", ora);
    printf("orario d'ufficio [9, 18]:       %d\n", ora >= 9 && ora <= 18);
    printf("fuori dall'orario d'ufficio:    %d\n", ora < 9 || ora > 18);
    printf("voto = %d\n", voto);
    printf("voto valido [1, 10]:            %d\n", voto >= 1 && voto <= 10);
    printf("voto sufficiente [6, 10]:       %d\n", voto >= 6 && voto <= 10);
    printf("\n");

    /* ── 3. Leggi di De Morgan ──────────────────────────────────────────
     *
     *   !(a && b)  equivale a  !a || !b
     *   !(a || b)  equivale a  !a && !b
     *
     * In pratica: per negare una condizione composta si negano le
     * singole parti e si scambia && con ||. Si usa spesso per scrivere
     * la condizione con cui un ciclo deve CONTINUARE a partire da
     * quella con cui deve FERMARSI.
     *
     * Esempio: "fuori dall'intervallo" è la negazione di "dentro":
     *   !(ora >= 9 && ora <= 18)
     *   = !(ora >= 9) || !(ora <= 18)
     *   = ora < 9 || ora > 18
     * Attenzione: la negazione di >= è <, non <=.
     */
    printf("=== 3. De Morgan ===\n");
    printf("!(ora >= 9 && ora <= 18)  -> %d\n", !(ora >= 9 && ora <= 18));
    printf("ora < 9 || ora > 18       -> %d  (stesso valore)\n", ora < 9 || ora > 18);
    printf("!(eta < 6 || residente)   -> %d\n", !(eta < 6 || residente));
    printf("eta >= 6 && !residente    -> %d  (stesso valore)\n", eta >= 6 && !residente);
    printf("\n");

    /* ── 4. Corto circuito ──────────────────────────────────────────────
     *
     * && e || valutano le espressioni da sinistra a destra e si fermano
     * appena il risultato è certo:
     *   - in  a && b  se a è falso, b NON viene valutato (il risultato è 0)
     *   - in  a || b  se a è vero,  b NON viene valutato (il risultato è 1)
     *
     * Si sfrutta per mettere prima il controllo che "protegge" il
     * secondo: qui la divisione avviene solo se il divisore non è zero.
     */
    printf("=== 4. Corto circuito ===\n");
    printf("divisore = %d\n", divisore);
    printf("divisore != 0 && dividendo / divisore > 2  -> %d\n",
           divisore != 0 && dividendo / divisore > 2);
    printf("La divisione per zero non avviene: la prima condizione e' falsa.\n");

    /*
     * ERRORE COMUNE: invertire l'ordine dei due controlli.
     *
     *   dividendo / divisore > 2 && divisore != 0
     *
     * Qui la divisione viene eseguita PRIMA del controllo: se divisore
     * vale 0 il programma termina con un errore a runtime.
     */

    return 0;
}
