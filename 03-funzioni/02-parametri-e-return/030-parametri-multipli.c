/*
 * 030-parametri-multipli.c
 *
 * Funzioni con più parametri
 *
 * Una funzione può ricevere più parametri di tipi anche diversi.
 * I parametri vengono elencati separati da virgola nella firma,
 * ciascuno con il proprio tipo. L'ordine con cui si passa gli argomenti
 * nella chiamata deve corrispondere esattamente all'ordine dei parametri
 * nella definizione. Questo file mostra funzioni con 2, 3 e 4 parametri
 * e come usarle correttamente.
 */

#include <stdio.h>

/* Prototipi */
double area_rettangolo(double base, double altezza);
double area_trapezio(double base_maggiore, double base_minore, double altezza);
int massimo_tra_tre(int a, int b, int c);
void stampa_tabella_moltiplicazione(int riga, int colonne_da, int colonne_a);

/* --- Definizioni --- */

/* Due parametri dello stesso tipo */
double area_rettangolo(double base, double altezza)
{
    double area;
    area = base * altezza;
    return area;
}

/* Tre parametri: formula dell'area del trapezio */
double area_trapezio(double base_maggiore, double base_minore, double altezza)
{
    double area;
    area = (base_maggiore + base_minore) / 2.0 * altezza;
    return area;
}

/* Tre parametri interi: massimo tra tre valori.
 * Usiamo una variabile "max" che aggiorniamo con if/else. */
int massimo_tra_tre(int a, int b, int c)
{
    int max;
    max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

/* Quattro parametri: stampa una riga della tavola pitagorica
 * da colonne_da a colonne_a.
 * Questa funzione è void: il suo scopo è stampare, non restituire dati. */
void stampa_tabella_moltiplicazione(int riga, int colonne_da, int colonne_a)
{
    int col;
    printf("Riga %2d: ", riga);
    col = colonne_da;
    while (col <= colonne_a) {
        printf("%4d", riga * col);
        col++;
    }
    printf("\n");
}

int main(void)
{
    double area;
    int max;

    /* --- Area rettangolo --- */
    printf("=== Area rettangolo ===\n");
    area = area_rettangolo(5.0, 3.0);
    printf("base=5.0, altezza=3.0  -> area = %.2f\n", area);
    printf("base=12.5, altezza=4.0 -> area = %.2f\n",
           area_rettangolo(12.5, 4.0));

    printf("\n");

    /* --- Area trapezio --- */
    printf("=== Area trapezio ===\n");
    /* ATTENZIONE: l'ordine degli argomenti conta!
     * area_trapezio(base_maggiore, base_minore, altezza)
     * Invertire base_maggiore e base_minore dà lo stesso risultato
     * in questo caso, ma invertire altezza darebbe un risultato sbagliato. */
    area = area_trapezio(10.0, 6.0, 4.0);
    printf("basi=10.0 e 6.0, altezza=4.0 -> area = %.2f\n", area);

    printf("\n");

    /* --- Massimo tra tre valori --- */
    printf("=== Massimo tra tre valori ===\n");
    max = massimo_tra_tre(7, 3, 9);
    printf("massimo(7, 3, 9)   = %d\n", max);
    printf("massimo(1, 1, 1)   = %d\n", massimo_tra_tre(1, 1, 1));
    printf("massimo(-5, -2, 0) = %d\n", massimo_tra_tre(-5, -2, 0));

    printf("\n");

    /* --- Tavola pitagorica parziale --- */
    printf("=== Tavola pitagorica (righe 1-5, colonne 1-6) ===\n");
    stampa_tabella_moltiplicazione(1, 1, 6);
    stampa_tabella_moltiplicazione(2, 1, 6);
    stampa_tabella_moltiplicazione(3, 1, 6);
    stampa_tabella_moltiplicazione(4, 1, 6);
    stampa_tabella_moltiplicazione(5, 1, 6);

    return 0;
}
