/*
 * 040-problema-configurazione-sola-lettura.c
 *
 * Applicare i limiti di configurazione di una cassa audio
 *
 * Una cassa audio per le aule ha tre impostazioni regolabili (volume,
 * bassi, luminosità del display) e una configurazione con i valori
 * massimi decisi dall'istituto. La configurazione non deve mai essere
 * modificata dal programma: le funzioni la ricevono con puntatori a const.
 *
 *     int limita(int *valore, const int *massimo)
 *        - valore   puntatore normale: la funzione può correggere il valore
 *        - massimo  puntatore a const: la funzione può solo leggerlo
 *        restituisce 1 se il valore è stato ridotto, 0 altrimenti
 *
 * Se per errore la funzione scrivesse *massimo = ..., il compilatore
 * rifiuterebbe il programma: const trasforma un errore di logica in un
 * errore di compilazione.
 *
 * Le richieste degli utenti sono in un elenco di coppie (impostazione,
 * valore); il programma le applica una alla volta.
 */

#include <stdio.h>

#define RICHIESTE 6

int limita(int *valore, const int *massimo);
void stampa_impostazioni(const int *volume, const int *bassi, const int *luce);

int main(void)
{
    const int max_volume = 70;
    const int max_bassi = 8;
    const int max_luce = 100;
    int volume = 40;
    int bassi = 5;
    int luce = 60;

    char tipi[RICHIESTE] = {'V', 'B', 'V', 'L', 'B', 'X'};
    int valori[RICHIESTE] = {65, 12, 90, 80, 3, 50};
    int *impostazione;
    const int *massimo;
    int k;

    printf("Limiti dell'istituto: volume %d, bassi %d, luce %d\n", max_volume,
           max_bassi, max_luce);
    stampa_impostazioni(&volume, &bassi, &luce);

    for (k = 0; k < RICHIESTE; k++) {
        impostazione = NULL;
        massimo = NULL;
        if (tipi[k] == 'V') {
            impostazione = &volume;
            massimo = &max_volume;
        } else if (tipi[k] == 'B') {
            impostazione = &bassi;
            massimo = &max_bassi;
        } else if (tipi[k] == 'L') {
            impostazione = &luce;
            massimo = &max_luce;
        }

        printf("Richiesta %c = %d: ", tipi[k], valori[k]);
        if (impostazione == NULL) {
            printf("impostazione sconosciuta, ignorata\n");
        } else {
            *impostazione = valori[k];
            if (limita(impostazione, massimo)) {
                printf("ridotta al massimo consentito (%d)\n", *impostazione);
            } else {
                printf("applicata\n");
            }
        }
    }

    stampa_impostazioni(&volume, &bassi, &luce);

    return 0;
}

int limita(int *valore, const int *massimo)
{
    int ridotto = 0;

    if (*valore > *massimo) {
        *valore = *massimo;
        ridotto = 1;
    }
    /* *massimo = *valore;      ERRORE di compilazione: massimo è di sola lettura */
    return ridotto;
}

void stampa_impostazioni(const int *volume, const int *bassi, const int *luce)
{
    printf("Impostazioni attuali: volume %d, bassi %d, luce %d%%\n", *volume, *bassi, *luce);
}
