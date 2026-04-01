/*
 * 060-problema-indice-massa-corporea.c
 *
 * Calcolo dell'Indice di Massa Corporea (IMC)
 *
 * L'utente inserisce peso (kg) e altezza (m). Il programma calcola l'IMC
 * secondo la formula standard (peso / altezza^2) e determina la categoria
 * di appartenenza usando operatori relazionali e logici come espressioni
 * intere (0/1), senza if/else. La categoria viene stampata con l'operatore
 * ternario annidato.
 *
 * Categorie OMS:
 *   IMC < 18.5            -> Sottopeso
 *   18.5 <= IMC < 25.0    -> Normopeso
 *   25.0 <= IMC < 30.0    -> Sovrappeso
 *   IMC >= 30.0           -> Obesita'
 */

#include <stdio.h>

/* soglie IMC secondo classificazione OMS */
#define SOGLIA_SOTTOPESO   18.5
#define SOGLIA_NORMOPESO   25.0
#define SOGLIA_SOVRAPPESO  30.0

int main(void)
{
    double peso;
    double altezza;
    double imc;

    /* flag booleani calcolati con operatori relazionali e logici */
    int sottopeso;
    int normopeso;
    int sovrappeso;
    int obesita;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Calcolo Indice di Massa Corporea ===\n\n");

    printf("Peso    (kg): ");
    scanf("%lf", &peso);

    printf("Altezza (m):  ");
    scanf("%lf", &altezza);

    /* ── calcolo IMC ────────────────────────────────────────────────────── */
    imc = peso / (altezza * altezza);

    /* ── classificazione con operatori relazionali e logici ─────────────── */
    /* Ogni variabile vale 1 (vero) o 0 (falso): è la categoria dell'utente.
     * L'operatore && garantisce che i range siano mutuamente esclusivi. */
    sottopeso  = (imc <  SOGLIA_SOTTOPESO);
    normopeso  = (imc >= SOGLIA_SOTTOPESO) && (imc < SOGLIA_NORMOPESO);
    sovrappeso = (imc >= SOGLIA_NORMOPESO) && (imc < SOGLIA_SOVRAPPESO);
    obesita    = (imc >= SOGLIA_SOVRAPPESO);

    /* ── output ─────────────────────────────────────────────────────────── */
    printf("\n=== Risultato ===\n");
    printf("Peso:    %.1f kg\n",   peso);
    printf("Altezza: %.2f m\n",    altezza);
    printf("IMC:     %.2f\n\n",    imc);

    /* stampa dei flag: utile a fini didattici per vedere i valori 0/1 */
    printf("=== Classificazione (1=si', 0=no) ===\n");
    printf("Sottopeso  (IMC < 18.5):        %d\n", sottopeso);
    printf("Normopeso  (18.5 <= IMC < 25):  %d\n", normopeso);
    printf("Sovrappeso (25 <= IMC < 30):    %d\n", sovrappeso);
    printf("Obesita'   (IMC >= 30):         %d\n", obesita);

    /* selezione della stringa di categoria con operatore ternario annidato.
     * Lettura: "se sottopeso stampa 'Sottopeso',
     *           altrimenti se normopeso stampa 'Normopeso', ..." */
    printf("\nCategoria: %s\n",
           sottopeso  ? "Sottopeso"
         : normopeso  ? "Normopeso"
         : sovrappeso ? "Sovrappeso"
         :              "Obesita'");

    return 0;
}
