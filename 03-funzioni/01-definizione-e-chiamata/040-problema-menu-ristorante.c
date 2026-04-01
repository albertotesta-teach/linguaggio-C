/*
 * 040-problema-menu-ristorante.c
 *
 * Menu di un ristorante organizzato con funzioni
 *
 * Un ristorante vuole stampare il proprio menu a schermo in modo
 * ordinato. Ogni sezione del menu (antipasti, primi, secondi, dolci)
 * viene gestita da una funzione dedicata, in modo che il codice sia
 * facile da aggiornare: per cambiare i prezzi dei primi, si modifica
 * solo la funzione stampa_primi().
 */

#include <stdio.h>

/* Prototipi */
void stampa_intestazione_menu(void);
void stampa_antipasti(void);
void stampa_primi(void);
void stampa_secondi(void);
void stampa_dolci(void);
void stampa_piede_menu(void);
void stampa_menu_completo(void);

/* --- Funzioni di sezione --- */

void stampa_intestazione_menu(void)
{
    printf("*******************************************\n");
    printf("*        TRATTORIA DA LUIGI               *\n");
    printf("*          Via Roma 12, Milano            *\n");
    printf("*        Tel. 02-1234567                  *\n");
    printf("*******************************************\n");
    printf("\n");
}

void stampa_antipasti(void)
{
    printf("--- ANTIPASTI ---\n");
    printf("  Bruschetta al pomodoro          4.50 EUR\n");
    printf("  Tagliere di salumi misti         9.00 EUR\n");
    printf("  Burrata con pomodorini          7.50 EUR\n");
    printf("\n");
}

void stampa_primi(void)
{
    printf("--- PRIMI PIATTI ---\n");
    printf("  Spaghetti alla carbonara        10.00 EUR\n");
    printf("  Risotto ai funghi porcini       12.00 EUR\n");
    printf("  Penne all'arrabbiata             8.50 EUR\n");
    printf("  Lasagne al ragu'                11.00 EUR\n");
    printf("\n");
}

void stampa_secondi(void)
{
    printf("--- SECONDI PIATTI ---\n");
    printf("  Tagliata di manzo               16.00 EUR\n");
    printf("  Branzino al forno               14.00 EUR\n");
    printf("  Pollo alla cacciatora           12.50 EUR\n");
    printf("\n");
}

void stampa_dolci(void)
{
    printf("--- DOLCI ---\n");
    printf("  Tiramisu'                        5.00 EUR\n");
    printf("  Panna cotta ai frutti di bosco   4.50 EUR\n");
    printf("  Gelato artigianale (3 gusti)     4.00 EUR\n");
    printf("\n");
}

void stampa_piede_menu(void)
{
    printf("*******************************************\n");
    printf("* Il coperto e' di 2.00 EUR a persona    *\n");
    printf("* Siamo aperti dal martedi' alla domenica*\n");
    printf("* dalle 12:00 alle 15:00 e dalle 19:00  *\n");
    printf("*******************************************\n");
}

/* Funzione principale che compone il menu completo
 * chiamando in sequenza tutte le funzioni di sezione.
 */
void stampa_menu_completo(void)
{
    stampa_intestazione_menu();
    stampa_antipasti();
    stampa_primi();
    stampa_secondi();
    stampa_dolci();
    stampa_piede_menu();
}

int main(void)
{
    stampa_menu_completo();
    return 0;
}
