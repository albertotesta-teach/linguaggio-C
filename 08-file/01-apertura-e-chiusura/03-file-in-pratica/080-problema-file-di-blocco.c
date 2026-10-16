/*
 * 080-problema-file-di-blocco.c
 *
 * L'aula informatica: un file di blocco per dire "occupato"
 *
 * Più docenti usano lo stesso programma per prenotare l'aula
 * informatica. Per evitare due prenotazioni insieme si usa un file di
 * blocco (lock): la sua sola esistenza dice che l'aula è occupata, e il
 * suo contenuto dice da chi.
 *
 *     P cognome    prenota: se aula.lock esiste, l'aula è occupata;
 *                  altrimenti si crea aula.lock con il cognome e si
 *                  aggiunge una riga a prenotazioni.txt ("a")
 *     L cognome    libera: solo chi ha prenotato può rimuovere aula.lock
 *     S            stato dell'aula
 *     R            registro delle prenotazioni
 *     Q            fine
 *
 * Il cognome scritto nel file di blocco si rilegge carattere per
 * carattere. Il file di blocco viene chiuso subito dopo averlo creato:
 * conta la sua presenza sul disco, non un FILE * aperto.
 *
 * (Tra il controllo "esiste?" e la creazione un altro programma
 * potrebbe creare il file: i sistemi operativi offrono funzioni apposta
 * per un controllo e una creazione indivisibili, fuori dal C standard.)
 */

#include <stdio.h>
#include <string.h>

#define BLOCCO "aula.lock"
#define REGISTRO "prenotazioni.txt"

int leggi_occupante(char occupante[], int dimensione);
int prenota(const char *cognome);
void ricopia(const char *nome);

int main(void)
{
    char comando = ' ';
    char cognome[30];
    char occupante[30];

    while (comando != 'Q') {
        printf("Comando (P, L, S, R, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'P' || comando == 'L') {
            if (scanf("%29s", cognome) != 1) {
                comando = 'Q';
            } else if (comando == 'P' && leggi_occupante(occupante, sizeof occupante)) {
                printf("  aula occupata da %s\n", occupante);
            } else if (comando == 'P') {
                if (prenota(cognome)) {
                    printf("  aula prenotata da %s\n", cognome);
                } else {
                    fprintf(stderr, "  prenotazione non riuscita\n");
                }
            } else if (!leggi_occupante(occupante, sizeof occupante)) {
                printf("  l'aula e' gia' libera\n");
            } else if (strcmp(occupante, cognome) != 0) {
                printf("  solo %s puo' liberare l'aula\n", occupante);
            } else if (remove(BLOCCO) == 0) {
                printf("  aula liberata da %s\n", cognome);
            } else {
                fprintf(stderr, "  impossibile rimuovere %s\n", BLOCCO);
            }
        } else if (comando == 'S') {
            if (leggi_occupante(occupante, sizeof occupante)) {
                printf("  occupata da %s\n", occupante);
            } else {
                printf("  libera\n");
            }
        } else if (comando == 'R') {
            ricopia(REGISTRO);
        } else if (comando != 'Q') {
            printf("  comando sconosciuto\n");
        }
    }

    return 0;
}

/* 1 se il file di blocco esiste; il cognome letto va in occupante. */
int leggi_occupante(char occupante[], int dimensione)
{
    FILE *f = fopen(BLOCCO, "r");
    int esiste = f != NULL;
    int n = 0;
    int c;

    if (esiste) {
        c = fgetc(f);
        while (c != EOF && c != '\n' && n < dimensione - 1) {
            occupante[n] = (char) c;
            n++;
            c = fgetc(f);
        }
        fclose(f);
    }
    occupante[n] = '\0';
    return esiste;
}

/* Crea il file di blocco e registra la prenotazione; 0 se non riesce. */
int prenota(const char *cognome)
{
    FILE *blocco = fopen(BLOCCO, "w");
    FILE *registro;
    int ok = blocco != NULL;

    if (ok) {
        fprintf(blocco, "%s\n", cognome);
        fclose(blocco);
        registro = fopen(REGISTRO, "a");
        if (registro != NULL) {
            fprintf(registro, "prenotazione di %s\n", cognome);
            fclose(registro);
        }
    }
    return ok;
}

void ricopia(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int c;

    if (f == NULL) {
        printf("  registro vuoto\n");
    } else {
        c = fgetc(f);
        while (c != EOF) {
            putchar(c);
            c = fgetc(f);
        }
        fclose(f);
    }
}
