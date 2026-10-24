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
    char riga[100];
    char testo_voto[16];
    char dopo;
    char altro;
    int campi;
    int resto;
    int voto;
    int riga_n = 0;     /* numero della riga di dati */
    const char *motivo; /* motivo dello scarto, NULL se valida */
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
        if (fgets(riga, sizeof riga, stdin) == NULL) {
            finito = 1;
        } else {
            if (strchr(riga, '\n') == NULL) {
                /* riga troppo lunga: si scarta il resto */
                resto = getchar();
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            campi = sscanf(riga, "%29s %15s %c", cognome, testo_voto, &altro);
            if (campi >= 1 && strcmp(cognome, "FINE") == 0) {
                finito = 1;
            } else if (campi >= 1) {
                /* riga vuota (campi < 1): ignorata e non numerata */
                riga_n++;
                motivo = NULL;
                if (campi == 1) {
                    motivo = "manca il voto";
                } else if (campi == 3) {
                    motivo = "dati in piu' dopo il voto";
                } else if (sscanf(testo_voto, "%d%c", &voto, &dopo) != 1) {
                    motivo = "il voto non e' un numero intero";
                } else if (voto < 1 || voto > 10) {
                    motivo = "voto fuori dall'intervallo 1-10";
                }
                if (motivo != NULL) {
                    segnala(stderr, riga_n, cognome, motivo);
                    segnala(errori, riga_n, cognome, motivo);
                    scartati++;
                } else {
                    fprintf(validi, "%s %d\n", cognome, voto);
                    caricati++;
                }
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
