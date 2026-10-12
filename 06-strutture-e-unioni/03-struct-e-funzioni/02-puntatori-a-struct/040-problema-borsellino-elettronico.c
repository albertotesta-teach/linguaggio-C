/*
 * 040-problema-borsellino-elettronico.c
 *
 * Distributori della scuola: il borsellino elettronico sulla tessera
 *
 * La tessera studente funziona anche come borsellino per i distributori
 * di bevande e snack. Oltre al credito registra la spesa del giorno, che
 * non può superare un limite giornaliero impostato dalla famiglia.
 *
 *     typedef struct {
 *         char intestatario[20];
 *         double credito;
 *         double speso_oggi;
 *         double limite_giornaliero;
 *         int bloccata;
 *     } Borsellino;
 *
 * Le funzioni che MODIFICANO ricevono Borsellino *, quelle che leggono
 * const Borsellino *:
 *     int ricarica(Borsellino *b, double euro);         0 se importo non valido
 *     int acquista(Borsellino *b, double prezzo);       codice di esito
 *     void nuovo_giorno(Borsellino *b);
 *     void stampa(const Borsellino *b);
 *
 * acquista restituisce 0 se l'acquisto riesce, 1 se il credito non basta,
 * 2 se si supera il limite giornaliero, 3 se la tessera è bloccata.
 * Comandi: R euro, A prezzo, G (nuovo giorno), B (blocca/sblocca), S, Q.
 */

#include <stdio.h>

typedef struct {
    char intestatario[20];
    double credito;
    double speso_oggi;
    double limite_giornaliero;
    int bloccata;
} Borsellino;

int ricarica(Borsellino *b, double euro);
int acquista(Borsellino *b, double prezzo);
void nuovo_giorno(Borsellino *b);
void stampa(const Borsellino *b);

int main(void)
{
    const char *esiti[4] = {"acquisto riuscito", "credito insufficiente",
                            "limite giornaliero superato", "tessera bloccata"};
    Borsellino tessera = {"Galli Irene", 4.00, 0, 3.00, 0};
    char comando = ' ';
    double importo;

    stampa(&tessera);
    while (comando != 'Q') {
        printf("Comando (R euro, A prezzo, G, B, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'R' || comando == 'A') {
            if (scanf("%lf", &importo) != 1) {
                comando = 'Q';
            } else if (comando == 'R') {
                if (ricarica(&tessera, importo)) {
                    printf("  Ricarica di %.2f euro.\n", importo);
                } else {
                    printf("  Importo non valido (da 1 a 50 euro).\n");
                }
            } else {
                printf("  %s\n", esiti[acquista(&tessera, importo)]);
            }
        } else if (comando == 'G') {
            nuovo_giorno(&tessera);
            printf("  Nuovo giorno: spesa azzerata.\n");
        } else if (comando == 'B') {
            tessera.bloccata = !tessera.bloccata;
            printf("  Tessera %s.\n", tessera.bloccata ? "bloccata" : "sbloccata");
        } else if (comando == 'S') {
            stampa(&tessera);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

int ricarica(Borsellino *b, double euro)
{
    int valido = euro >= 1 && euro <= 50;

    if (valido) {
        b->credito = b->credito + euro;
    }
    return valido;
}

/* I controlli sono in ordine: tessera, limite, credito. */
int acquista(Borsellino *b, double prezzo)
{
    int esito = 0;

    if (b->bloccata) {
        esito = 3;
    } else if (b->speso_oggi + prezzo > b->limite_giornaliero) {
        esito = 2;
    } else if (b->credito < prezzo) {
        esito = 1;
    } else {
        b->credito = b->credito - prezzo;
        b->speso_oggi = b->speso_oggi + prezzo;
    }
    return esito;
}

void nuovo_giorno(Borsellino *b)
{
    b->speso_oggi = 0;
}

void stampa(const Borsellino *b)
{
    printf("  %s: credito %.2f, speso oggi %.2f su %.2f%s\n", b->intestatario, b->credito,
           b->speso_oggi, b->limite_giornaliero, b->bloccata ? " (BLOCCATA)" : "");
}
