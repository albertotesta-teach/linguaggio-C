/*
 * 030-funzioni-void.c
 *
 * Funzioni void: effetti senza valori di ritorno
 *
 * Le funzioni void non restituiscono dati al chiamante, ma producono
 * effetti osservabili: stampano a schermo, modificano variabili globali,
 * interagiscono con l'utente. Questo file mostra diversi esempi di
 * funzioni void e come organizzare un programma usando solo funzioni
 * void per separare le responsabilità.
 */

#include <stdio.h>

/* Prototipi */
void stampa_riga_vuota(void);
void stampa_intestazione(void);
void stampa_voce(void);
void stampa_totale(void);
void stampa_documento_completo(void);

/* --- Definizioni --- */

/* Funzione di utilità: stampa una riga vuota per spaziare l'output.
 * Funzioni così semplici sono comunque utili: se vogliamo cambiare
 * il comportamento (es. due righe vuote), lo modifichiamo in un solo punto.
 */
void stampa_riga_vuota(void)
{
    printf("\n");
}

void stampa_intestazione(void)
{
    printf("FATTURA N. 2024-001\n");
    printf("Data: 15/03/2024\n");
    printf("Cliente: Rossi Mario\n");
    printf("-----------------------------------\n");
}

void stampa_voce(void)
{
    /* In questa versione semplificata (senza parametri) i dati sono fissi.
     * Nel capitolo sui parametri impareremo a passare valori alle funzioni.
     */
    printf("Prodotto A        x2     20.00 EUR\n");
    printf("Prodotto B        x1     15.50 EUR\n");
    printf("Servizio extra    x1      5.00 EUR\n");
    printf("-----------------------------------\n");
}

void stampa_totale(void)
{
    printf("Subtotale:               40.50 EUR\n");
    printf("IVA 22%%:                  8.91 EUR\n");
    printf("===================================\n");
    printf("TOTALE:                  49.41 EUR\n");
}

/* Una funzione void può chiamare altre funzioni void.
 * Questo permette di costruire comportamenti complessi
 * componendo funzioni più semplici.
 */
void stampa_documento_completo(void)
{
    stampa_intestazione();
    stampa_riga_vuota();
    stampa_voce();
    stampa_riga_vuota();
    stampa_totale();
}

int main(void)
{
    /* Il main si occupa solo di orchestrare le chiamate.
     * Ogni "responsabilità" è delegata a una funzione dedicata.
     */
    stampa_documento_completo();

    stampa_riga_vuota();
    printf("Grazie per la fiducia!\n");

    return 0;
}
