/*
 * 060-problema-registro-degli-errori.c
 *
 * Dati validi in un file, errori a video e in un registro
 *
 * La segreteria riceve i voti della verifica di recupero, una riga
 * "cognome voto" per studente, e li deve caricare nel registro. Prima
 * li controlla: il voto deve essere un numero da 1 a 10.
 *
 *     righe valide   ->  recupero.txt        aperto in "w": il file del giorno
 *     righe errate   ->  stderr               per chi sta inserendo
 *                    ->  errori.txt           aperto in "a": lo storico
 *
 * Lo stesso messaggio d'errore va su due flussi; una funzione con il
 * flusso come parametro lo scrive su entrambi:
 *
 *     segnala(stderr, riga, cognome, motivo);
 *     segnala(errori, riga, cognome, motivo);
 *
 * Sono aperti due file insieme: se il secondo non si apre, il primo va
 * chiuso prima di terminare.
 */

#include <stdio.h>
#include <string.h>

void segnala(FILE *f, int riga, const char *cognome, const char *motivo);

int main(void)
{
    FILE *validi = NULL;
    FILE *errori = NULL;
    char cognome[30];
    char testo_voto[16];
    char dopo;
    int voto;
    int riga = 0;
    int caricati = 0;
    int scartati = 0;
    int finito = 0;

    validi = fopen("recupero.txt", "w");
    if (validi == NULL) {
        fprintf(stderr, "Impossibile creare recupero.txt\n");
        finito = 1;
    } else {
        errori = fopen("errori.txt", "a");
        if (errori == NULL) {
            fprintf(stderr, "Impossibile aprire errori.txt\n");
            fclose(validi);
            validi = NULL;
            finito = 1;
        }
    }
    if (!finito) {
        printf("Voti (cognome voto, FINE per terminare):\n");
    }
    while (!finito) {
        if (scanf("%29s", cognome) != 1 || strcmp(cognome, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%15s", testo_voto) != 1) {
            finito = 1;
        } else {
            riga++;
            if (sscanf(testo_voto, "%d%c", &voto, &dopo) != 1) {
                segnala(stderr, riga, cognome, "il voto non e' un numero intero");
                segnala(errori, riga, cognome, "il voto non e' un numero intero");
                scartati++;
            } else if (voto < 1 || voto > 10) {
                segnala(stderr, riga, cognome, "voto fuori dall'intervallo 1-10");
                segnala(errori, riga, cognome, "voto fuori dall'intervallo 1-10");
                scartati++;
            } else {
                fprintf(validi, "%s %d\n", cognome, voto);
                caricati++;
            }
        }
    }
    if (validi != NULL) {
        fclose(validi);
        fclose(errori);
        printf("Voti caricati in recupero.txt: %d\n", caricati);
        printf("Righe scartate (vedi errori.txt): %d\n", scartati);
    }

    return 0;
}

void segnala(FILE *f, int riga, const char *cognome, const char *motivo)
{
    fprintf(f, "riga %d (%s): %s\n", riga, cognome, motivo);
}
