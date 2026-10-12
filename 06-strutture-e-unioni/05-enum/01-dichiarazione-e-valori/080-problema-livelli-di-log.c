/*
 * 080-problema-livelli-di-log.c
 *
 * Server del laboratorio: filtrare i messaggi del registro per livello
 *
 * Il server del laboratorio scrive nel registro (log) messaggi di
 * gravità diversa. Il livello è un enum ordinato dal meno al più grave,
 * così due livelli si confrontano con < e >=:
 *
 *     typedef enum { DEBUG, INFO, AVVISO, ERRORE, NUM_LIVELLI } Livello;
 *
 *     typedef struct {
 *         char ora[6];
 *         Livello livello;
 *         char testo[40];
 *     } Messaggio;
 *
 * Il programma legge la soglia (da 0 a 3) e stampa solo i messaggi con
 * livello >= soglia, preceduti dal nome del livello; poi conta i
 * messaggi di ogni livello con un array indicizzato dall'enum.
 */

#include <stdio.h>

#define MESSAGGI 8

typedef enum {
    DEBUG, INFO, AVVISO, ERRORE, NUM_LIVELLI
} Livello;

typedef struct {
    char ora[6];
    Livello livello;
    char testo[40];
} Messaggio;

int main(void)
{
    const char *nomi[NUM_LIVELLI] = {[DEBUG] = "DEBUG", [INFO] = "INFO", [AVVISO] = "AVVISO",
                                     [ERRORE] = "ERRORE"};
    Messaggio registro[MESSAGGI] = {
        {"08:00", INFO, "avvio del server"},
        {"08:01", DEBUG, "configurazione letta"},
        {"08:15", INFO, "accesso utente 3b-pc07"},
        {"09:02", AVVISO, "disco al 85%"},
        {"09:40", INFO, "pulizia file temporanei"},
        {"10:12", ERRORE, "stampante lab non risponde"},
        {"10:13", AVVISO, "nuovo tentativo di stampa"},
        {"11:30", ERRORE, "backup notturno non trovato"}
    };
    int conteggi[NUM_LIVELLI] = {0};
    int soglia;
    int mostrati = 0;
    int i;
    Livello l;

    printf("Soglia (0 DEBUG, 1 INFO, 2 AVVISO, 3 ERRORE): ");
    if (scanf("%d", &soglia) != 1 || soglia < DEBUG || soglia > ERRORE) {
        printf("Soglia non valida.\n");
    } else {
        for (i = 0; i < MESSAGGI; i++) {
            conteggi[registro[i].livello]++;
            if (registro[i].livello >= (Livello) soglia) {
                printf("  %s [%-6s] %s\n", registro[i].ora, nomi[registro[i].livello],
                       registro[i].testo);
                mostrati++;
            }
        }
        printf("Mostrati %d messaggi su %d\n", mostrati, MESSAGGI);
        for (l = DEBUG; l < NUM_LIVELLI; l++) {
            printf("  %-6s %d\n", nomi[l], conteggi[l]);
        }
    }

    return 0;
}
