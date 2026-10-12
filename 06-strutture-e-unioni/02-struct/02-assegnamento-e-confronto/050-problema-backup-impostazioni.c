/*
 * 050-problema-backup-impostazioni.c
 *
 * Lavagna interattiva: salvare e ripristinare le impostazioni
 *
 * Le impostazioni della LIM dell'aula sono raccolte in una struct:
 *
 *     typedef struct {
 *         int luminosita;          0-100
 *         int volume;              0-100
 *         char ingresso[8];        HDMI1, HDMI2, PC
 *         int spegnimento;         minuti di inattività prima dello spegnimento
 *     } Impostazioni;
 *
 * Tre variabili dello stesso tipo:
 *   - predefinite: i valori di fabbrica, che non cambiano mai;
 *   - corrente:    le impostazioni in uso;
 *   - salvate:     l'ultimo backup.
 *
 * Con l'assegnamento tra struct backup e ripristino sono una sola
 * istruzione: salvate = corrente; corrente = salvate; corrente = predefinite.
 * Prima di uscire il programma confronta corrente e salvate campo per
 * campo e avvisa se ci sono modifiche non salvate.
 *
 * Comandi: L n (luminosità), V n (volume), I nome (ingresso), B (backup),
 * R (ripristina il backup), F (valori di fabbrica), S (stampa), Q (fine).
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    int luminosita;
    int volume;
    char ingresso[8];
    int spegnimento;
} Impostazioni;

int main(void)
{
    const Impostazioni predefinite = {70, 40, "HDMI1", 30};
    Impostazioni corrente = predefinite;
    Impostazioni salvate = predefinite;
    char comando = ' ';
    int valore;
    char nome[8];
    int uguali;

    while (comando != 'Q') {
        printf("Comando (L n, V n, I nome, B, R, F, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'L' || comando == 'V') {
            if (scanf("%d", &valore) == 1 && valore >= 0 && valore <= 100) {
                if (comando == 'L') {
                    corrente.luminosita = valore;
                    printf("  Luminosita' %d.\n", valore);
                } else {
                    corrente.volume = valore;
                    printf("  Volume %d.\n", valore);
                }
            } else {
                printf("  Valore tra 0 e 100.\n");
            }
        } else if (comando == 'I') {
            if (scanf("%7s", nome) == 1 &&
                (strcmp(nome, "HDMI1") == 0 || strcmp(nome, "HDMI2") == 0 || strcmp(nome, "PC") == 0)) {
                strcpy(corrente.ingresso, nome);
                printf("  Ingresso %s.\n", nome);
            } else {
                printf("  Ingressi: HDMI1, HDMI2, PC.\n");
            }
        } else if (comando == 'B') {
            salvate = corrente;
            printf("  Impostazioni salvate.\n");
        } else if (comando == 'R') {
            corrente = salvate;
            printf("  Backup ripristinato.\n");
        } else if (comando == 'F') {
            corrente = predefinite;
            printf("  Valori di fabbrica.\n");
        } else if (comando == 'S') {
            printf("  luminosita' %d, volume %d, ingresso %s, spegnimento dopo %d min\n",
                   corrente.luminosita, corrente.volume, corrente.ingresso, corrente.spegnimento);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    uguali = corrente.luminosita == salvate.luminosita && corrente.volume == salvate.volume &&
             strcmp(corrente.ingresso, salvate.ingresso) == 0 &&
             corrente.spegnimento == salvate.spegnimento;
    if (uguali) {
        printf("Nessuna modifica da salvare.\n");
    } else {
        printf("Attenzione: ci sono modifiche non salvate.\n");
    }

    return 0;
}
