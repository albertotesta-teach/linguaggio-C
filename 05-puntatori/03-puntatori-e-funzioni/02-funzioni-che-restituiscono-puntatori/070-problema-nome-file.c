/*
 * 070-problema-nome-file.c
 *
 * Archivio dei compiti: cartella, nome ed estensione
 *
 * Sulla piattaforma della scuola i compiti consegnati hanno un percorso
 * come "4B/informatica/verifica-3.c". Per l'archivio servono, separati, la
 * cartella, il nome del file e l'estensione; i file senza estensione o
 * senza cartella vanno segnalati.
 *
 * Il programma usa una propria versione di strrchr:
 *
 *     const char *ultimo(const char *s, char c);
 *
 * che restituisce il puntatore all'ULTIMA occorrenza di c, NULL se c non
 * compare. Con i due puntatori restituiti si ricavano le tre parti:
 *   - barra = ultimo(percorso, '/')   la cartella finisce prima di barra;
 *   - punto = ultimo(nome, '.')       cercato solo nel nome, dopo la barra,
 *                                     perché anche una cartella può avere un
 *                                     punto nel nome.
 */

#include <stdio.h>

#define FILE_CONSEGNATI 5
#define LUNG            40

const char *ultimo(const char *s, char c);

int main(void)
{
    char percorsi[FILE_CONSEGNATI][LUNG] = {
        "4B/informatica/verifica-3.c",
        "4B/informatica/relazione.lab.pdf",
        "5A/sistemi/v1.2/schema",
        "appunti.txt",
        "4B/storia/.nascosto"
    };
    const char *percorso;
    const char *barra;
    const char *nome;
    const char *punto;
    int i;

    for (i = 0; i < FILE_CONSEGNATI; i++) {
        percorso = percorsi[i];
        barra = ultimo(percorso, '/');
        if (barra == NULL) {
            nome = percorso;
        } else {
            nome = barra + 1;
        }
        punto = ultimo(nome, '.');

        printf("%s\n", percorso);
        if (barra == NULL) {
            printf("  cartella:   (nessuna)\n");
        } else {
            printf("  cartella:   %.*s\n", (int) (barra - percorso), percorso);
        }
        if (punto == NULL || punto == nome) {
            printf("  nome:       %s\n  estensione: (nessuna)\n", nome);
        } else {
            printf("  nome:       %.*s\n", (int) (punto - nome), nome);
            printf("  estensione: %s\n", punto + 1);
        }
    }

    return 0;
}

/* Puntatore all'ultima occorrenza di c in s, NULL se non compare. */
const char *ultimo(const char *s, char c)
{
    const char *trovato = NULL;
    const char *p;

    for (p = s; *p != '\0'; p++) {
        if (*p == c) {
            trovato = p;
        }
    }
    return trovato;
}
