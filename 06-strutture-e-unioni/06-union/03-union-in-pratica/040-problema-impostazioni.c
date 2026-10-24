/*
 * 040-problema-impostazioni.c
 *
 * Il server del registro di classe: leggere il file delle impostazioni
 *
 * Il file di configurazione ha una impostazione per riga, nella forma
 * chiave=valore. Ogni chiave ha un tipo previsto, scritto in una tabella:
 *
 *     porta=8080            intero (da 1 a 65535)
 *     timeout=2.5           reale (secondi, maggiore di 0)
 *     registro=si           si/no
 *     server=registro.lan   testo
 *
 * Ogni impostazione letta è una union etichettata (con union anonima):
 *
 *     typedef struct {
 *         char chiave[16];
 *         TipoValore tipo;
 *         union {
 *             int intero;
 *             double reale;
 *             int si_no;
 *             char testo[24];
 *         };
 *     } Impostazione;
 *
 * La funzione leggi_valore converte il testo dopo = secondo il tipo
 * previsto per la chiave, e restituisce 0 se il valore non è valido.
 * Righe vuote e righe che iniziano con # (commenti) si ignorano; una
 * chiave sconosciuta o un valore non valido si segnalano con il numero
 * di riga. FINE chiude il file; poi si stampa la configurazione.
 */

#include <stdio.h>
#include <string.h>

#define CHIAVI 4
#define LUNG 64

typedef enum {
    INTERO, REALE, SI_NO, TESTO
} TipoValore;

typedef struct {
    char chiave[16];
    TipoValore tipo;
    union {
        int intero;
        double reale;
        int si_no;
        char testo[24];
    };
} Impostazione;

int leggi_valore(Impostazione *imp, const char *testo);
void stampa(const Impostazione *imp);

int main(void)
{
    Impostazione config[CHIAVI] = {
        {.chiave = "porta", .tipo = INTERO, .intero = 80},
        {.chiave = "timeout", .tipo = REALE, .reale = 1.0},
        {.chiave = "registro", .tipo = SI_NO, .si_no = 0},
        {.chiave = "server", .tipo = TESTO, .testo = "localhost"}
    };
    char riga[LUNG];
    char *uguale;
    int numero_riga = 0;
    int trovata;
    int finito = 0;
    int resto;
    int k;

    printf("File delle impostazioni (FINE per terminare):\n");
    while (!finito) {
        if (fgets(riga, LUNG, stdin) == NULL) {
            finito = 1;
        } else {
            if (strchr(riga, '\n') == NULL) {
                resto = getchar();      /* riga troppo lunga: scarta il resto */
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            riga[strcspn(riga, "\n")] = '\0';
            numero_riga++;
            uguale = strchr(riga, '=');
            if (strcmp(riga, "FINE") == 0) {
                finito = 1;
            } else if (riga[0] == '\0' || riga[0] == '#') {
                /* riga vuota o commento: si ignora */
            } else if (uguale == NULL) {
                printf("  riga %d: manca '='\n", numero_riga);
            } else {
                *uguale = '\0';
                trovata = -1;
                for (k = 0; k < CHIAVI; k++) {
                    if (strcmp(config[k].chiave, riga) == 0) {
                        trovata = k;
                    }
                }
                if (trovata == -1) {
                    printf("  riga %d: chiave sconosciuta \"%s\"\n", numero_riga, riga);
                } else if (!leggi_valore(&config[trovata], uguale + 1)) {
                    printf("  riga %d: valore non valido per %s\n", numero_riga, riga);
                }
            }
        }
    }

    printf("\nConfigurazione:\n");
    for (k = 0; k < CHIAVI; k++) {
        stampa(&config[k]);
    }

    return 0;
}

/* Converte il testo secondo il tipo della chiave; 0 se non è valido. */
int leggi_valore(Impostazione *imp, const char *testo)
{
    int intero;
    double reale;
    char dopo;
    int ok = 0;

    switch (imp->tipo) {
    case INTERO:
        ok = sscanf(testo, "%d %c", &intero, &dopo) == 1 && intero >= 1 && intero <= 65535;
        if (ok) {
            imp->intero = intero;
        }
        break;
    case REALE:
        ok = sscanf(testo, "%lf %c", &reale, &dopo) == 1 && reale > 0;
        if (ok) {
            imp->reale = reale;
        }
        break;
    case SI_NO:
        ok = strcmp(testo, "si") == 0 || strcmp(testo, "no") == 0;
        if (ok) {
            imp->si_no = strcmp(testo, "si") == 0;
        }
        break;
    case TESTO:
        ok = testo[0] != '\0' && strlen(testo) < sizeof(imp->testo);
        if (ok) {
            strcpy(imp->testo, testo);
        }
        break;
    }
    return ok;
}

void stampa(const Impostazione *imp)
{
    printf("  %-9s = ", imp->chiave);
    switch (imp->tipo) {
    case INTERO:
        printf("%d\n", imp->intero);
        break;
    case REALE:
        printf("%.1f s\n", imp->reale);
        break;
    case SI_NO:
        printf("%s\n", imp->si_no ? "si" : "no");
        break;
    case TESTO:
        printf("\"%s\"\n", imp->testo);
        break;
    }
}
