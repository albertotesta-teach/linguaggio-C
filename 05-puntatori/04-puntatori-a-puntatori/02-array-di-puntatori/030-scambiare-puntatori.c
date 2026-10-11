/*
 * 030-scambiare-puntatori.c
 *
 * Riordinare scambiando i puntatori, non i testi
 *
 * Con una matrice di char, scambiare due nomi significa copiare tutti i
 * loro caratteri (con un array di appoggio). Con un array di puntatori
 * basta scambiare due INDIRIZZI: i testi restano dove sono, cambia solo
 * l'ordine in cui l'array li indica.
 *
 *     void scambia(const char **a, const char **b);
 *     scambia(&ordine[0], &ordine[2]);
 *
 * Gli elementi dell'array sono const char *: per scambiarli la funzione
 * riceve i loro indirizzi, quindi parametri const char ** (sezione 01).
 *
 * Esempio: l'ordine di intervento in un'assemblea di classe cambia
 * perché due studenti si scambiano il turno.
 */

#include <stdio.h>

#define INTERVENTI 4

void scambia(const char **a, const char **b);
void stampa(const char *ordine[], int n);

int main(void)
{
    const char *ordine[INTERVENTI] = {"Martina", "Luca", "Giorgia", "Samuele"};

    printf("Ordine iniziale:\n");
    stampa(ordine, INTERVENTI);

    scambia(&ordine[0], &ordine[2]);
    printf("\nDopo scambia(&ordine[0], &ordine[2]):\n");
    stampa(ordine, INTERVENTI);

    scambia(&ordine[1], &ordine[3]);
    printf("\nDopo scambia(&ordine[1], &ordine[3]):\n");
    stampa(ordine, INTERVENTI);

    printf("\nGli indirizzi dei testi non sono cambiati: e' cambiato solo\n"
           "quale elemento dell'array punta a ciascun testo.\n");

    return 0;
}

/* Scambia i due puntatori di cui riceve gli indirizzi. */
void scambia(const char **a, const char **b)
{
    const char *temp = *a;

    *a = *b;
    *b = temp;
}

/* Riceve l'array di puntatori: il parametro equivale a const char **. */
void stampa(const char *ordine[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("  %d. %-8s (testo all'indirizzo %p)\n", i + 1, ordine[i], (void *) ordine[i]);
    }
}
