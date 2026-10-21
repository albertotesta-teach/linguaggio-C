/*
 * 060-problema-lettura-con-scanf.c
 *
 * Perché scanf vuole gli indirizzi
 *
 * Un modulo di iscrizione a un torneo di scacchi chiede età, punteggio
 * ELO, categoria (una lettera) e nickname. Il programma legge i dati con
 * scanf e mostra, per ciascuno, l'indirizzo passato a scanf.
 *
 * scanf deve SCRIVERE nelle variabili del chiamante: per farlo le serve
 * sapere dove si trovano, cioè il loro indirizzo.
 *
 *     scanf("%d", &eta);         passa l'indirizzo di eta
 *     scanf("%19s", nickname);   nickname è un array: il suo nome indica
 *                                già l'indirizzo del primo elemento, quindi
 *                                non serve & (si vedrà meglio nel capitolo
 *                                "puntatori e array")
 *
 * L'errore scanf("%d", eta) passa il VALORE di eta al posto dell'indirizzo:
 * scanf scriverebbe in una posizione di memoria casuale. Il compilatore con
 * -Wall lo segnala con un avviso.
 *
 * Il programma usa anche il valore restituito da scanf (numero di dati
 * letti) per accorgersi degli errori di inserimento: 0 se l'input non è
 * del tipo richiesto, EOF se l'input è terminato.
 */

#include <stdio.h>
#include <ctype.h>

#define LUNG_NICK 20

void svuota_riga(void);

int main(void)
{
    int eta;
    int elo;
    char categoria = ' ';
    char nickname[LUNG_NICK];
    int letti;
    int fine_input = 0;     /* 1 se l'input termina prima della fine */

    printf("=== ISCRIZIONE AL TORNEO ===\n");

    printf("Eta': ");
    letti = scanf("%d", &eta);
    while (!fine_input && (letti != 1 || eta < 6 || eta > 99)) {
        if (letti == EOF) {
            fine_input = 1;
        } else {
            svuota_riga();
            printf("  Valore non valido. Eta': ");
            letti = scanf("%d", &eta);
        }
    }

    if (!fine_input) {
        printf("Punteggio ELO: ");
        letti = scanf("%d", &elo);
        while (!fine_input && (letti != 1 || elo < 0)) {
            if (letti == EOF) {
                fine_input = 1;
            } else {
                svuota_riga();
                printf("  Valore non valido. Punteggio ELO: ");
                letti = scanf("%d", &elo);
            }
        }
    }

    if (!fine_input) {
        printf("Categoria (U = under 18, A = adulti): ");
        letti = scanf(" %c", &categoria);
        categoria = (char) toupper((unsigned char) categoria);
        while (!fine_input && (letti != 1 || (categoria != 'U' && categoria != 'A'))) {
            if (letti == EOF) {
                fine_input = 1;
            } else {
                svuota_riga();
                printf("  Categoria non valida. Categoria (U/A): ");
                letti = scanf(" %c", &categoria);
                categoria = (char) toupper((unsigned char) categoria);
            }
        }
    }

    if (!fine_input) {
        printf("Nickname: ");
        if (scanf("%19s", nickname) != 1) {
            fine_input = 1;
        }
    }

    if (fine_input) {
        printf("\n\nInput terminato: iscrizione annullata.\n");
    } else {
        printf("\n=== DATI REGISTRATI ===\n");
        printf("  %-10s %-13s scritto da scanf all'indirizzo\n", "Dato", "Valore");
        printf("  %-10s %-13d %p\n", "eta", eta, (void *) &eta);
        printf("  %-10s %-13d %p\n", "elo", elo, (void *) &elo);
        printf("  %-10s %-13c %p\n", "categoria", categoria, (void *) &categoria);
        printf("  %-10s %-13s %p  (= &nickname[0])\n", "nickname", nickname,
               (void *) &nickname[0]);

        if ((categoria == 'U' && eta >= 18) || (categoria == 'A' && eta < 18)) {
            printf("Attenzione: la categoria non corrisponde all'eta'.\n");
        }
    }

    return 0;
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
