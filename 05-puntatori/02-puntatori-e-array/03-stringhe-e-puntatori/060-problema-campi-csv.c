/*
 * 060-problema-campi-csv.c
 *
 * Importazione dei voti da un file CSV
 *
 * Il registro elettronico esporta i voti in righe di testo nel formato CSV
 * (valori separati da punto e virgola):
 *
 *     cognome;nome;classe;voto
 *
 * Il programma scompone ogni riga nei suoi campi, scarta le righe con un
 * numero di campi sbagliato o un voto non valido, stampa una tabella e
 * calcola la media dei voti importati.
 *
 * La scomposizione usa un puntatore p che scorre la riga: i caratteri si
 * copiano nel campo corrente finché non si incontra ';' (si passa al campo
 * successivo) o '\0' (la riga è finita). Ogni campo è una riga di
 * campi[CAMPI][LUNG_CAMPO].
 */

#include <stdio.h>

#define RIGHE      6
#define LUNG_RIGA  60
#define CAMPI      4
#define LUNG_CAMPO 16

int dividi_riga(const char *riga, char campi[][LUNG_CAMPO]);

int main(void)
{
    char righe[RIGHE][LUNG_RIGA] = {
        "Rossi;Mario;4B;7.5",
        "Bianchi;Laura;4B;8",
        "Verdi;Paolo;4B",
        "Neri;Sara;4B;sei",
        "Esposito;Luca;4B;6.25",
        "Gallo;Anna;4B;9;assente"
    };
    char campi[CAMPI][LUNG_CAMPO];
    int r;
    int n;
    double voto;
    double somma = 0;
    int importate = 0;

    printf("=== IMPORTAZIONE VOTI ===\n");
    printf("  %-10s %-8s %-6s %s\n", "Cognome", "Nome", "Classe", "Voto");
    for (r = 0; r < RIGHE; r++) {
        n = dividi_riga(righe[r], campi);
        if (n != CAMPI) {
            printf("  riga %d scartata: %d campi invece di %d  [%s]\n",
                   r + 1, n, CAMPI, righe[r]);
        } else if (sscanf(campi[3], "%lf", &voto) != 1 || voto < 1 || voto > 10) {
            printf("  riga %d scartata: voto non valido \"%s\"\n", r + 1, campi[3]);
        } else {
            printf("  %-10s %-8s %-6s %4.2f\n", campi[0], campi[1], campi[2], voto);
            somma = somma + voto;
            importate++;
        }
    }

    printf("\nRighe importate: %d su %d\n", importate, RIGHE);
    if (importate > 0) {
        printf("Media dei voti: %.2f\n", somma / importate);
    }

    return 0;
}

/* Copia i campi di riga in campi[0], campi[1], ... e restituisce quanti
 * campi ha trovato. Oltre CAMPI campi continua a contarli senza copiarli;
 * i caratteri oltre LUNG_CAMPO - 1 vengono ignorati. */
int dividi_riga(const char *riga, char campi[][LUNG_CAMPO])
{
    const char *p = riga;
    char *dest = campi[0];
    int numero = 0;

    while (*p != '\0') {
        if (*p == ';') {
            if (numero < CAMPI) {
                *dest = '\0';
            }
            numero++;
            if (numero < CAMPI) {
                dest = campi[numero];
            }
        } else if (numero < CAMPI && dest < campi[numero] + LUNG_CAMPO - 1) {
            *dest = *p;
            dest++;
        }
        p++;
    }
    if (numero < CAMPI) {
        *dest = '\0';
    }
    return numero + 1;
}
