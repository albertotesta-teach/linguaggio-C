/*
 * 020-parametri-in-out.c
 *
 * Parametri di ingresso e uscita insieme
 *
 * Un parametro puntatore può essere:
 *   - di sola USCITA: la funzione ci scrive un risultato (*risultato = ...);
 *   - di INGRESSO E USCITA: la funzione legge il valore attuale e lo
 *     aggiorna (*saldo = *saldo - importo).
 *
 * Una convenzione molto usata: la funzione restituisce con return se
 * l'operazione è riuscita (1) o no (0), e modifica la variabile del
 * chiamante solo in caso di successo. Il chiamante controlla il valore di
 * ritorno:
 *
 *     if (preleva(&saldo, 50)) { ... riuscito ... }
 *
 * Esempio: la tessera prepagata della mensa scolastica.
 */

#include <stdio.h>

#define PASTO   550                     /* centesimi */
#define MASSIMO 5000

int preleva(int *saldo, int importo);
int ricarica(int *saldo, int importo);
void stampa_saldo(int saldo);

int main(void)
{
    int saldo = 1200;
    int giorno;

    stampa_saldo(saldo);

    for (giorno = 1; giorno <= 3; giorno++) {
        printf("Giorno %d, pasto da %.2f euro: ", giorno, PASTO / 100.0);
        if (preleva(&saldo, PASTO)) {
            printf("pagato. ");
        } else {
            printf("credito insufficiente. ");
        }
        stampa_saldo(saldo);
    }

    printf("Ricarica di 20 euro: ");
    if (ricarica(&saldo, 2000)) {
        printf("eseguita. ");
    }
    stampa_saldo(saldo);

    printf("Ricarica di 40 euro: ");
    if (!ricarica(&saldo, 4000)) {
        printf("rifiutata, il massimo e' %.2f euro. ", MASSIMO / 100.0);
    }
    stampa_saldo(saldo);

    return 0;
}

/* Toglie importo da *saldo se il credito basta; restituisce 1 se ci è
 * riuscita, 0 altrimenti (in quel caso *saldo non cambia). */
int preleva(int *saldo, int importo)
{
    int riuscito = 0;

    if (*saldo >= importo) {
        *saldo = *saldo - importo;
        riuscito = 1;
    }
    return riuscito;
}

/* Aggiunge importo a *saldo se non si supera MASSIMO. */
int ricarica(int *saldo, int importo)
{
    int riuscito = 0;

    if (*saldo + importo <= MASSIMO) {
        *saldo = *saldo + importo;
        riuscito = 1;
    }
    return riuscito;
}

void stampa_saldo(int saldo)
{
    printf("Saldo: %.2f euro\n", saldo / 100.0);
}
