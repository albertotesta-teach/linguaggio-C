/*
 * 030-input-con-fgets.c
 *
 * Lettura di stringhe da tastiera con fgets.
 *
 * fgets è la funzione preferita per leggere stringhe in C perché:
 *
 *   1. Legge l'intera riga inclusi gli spazi
 *   2. Limita i caratteri letti alla dimensione del buffer (sicurezza)
 *   3. Include il carattere '\n' (invio) nella stringa letta
 *
 * Sintassi:
 *   fgets(buffer, dimensione, stdin)
 *
 *   buffer     → array di char dove salvare la stringa
 *   dimensione → numero massimo di caratteri da leggere (incluso '\0')
 *   stdin      → sorgente di input (tastiera)
 *
 * ATTENZIONE: fgets include '\n' nella stringa. Se non si rimuove,
 * la stringa risultante conterrà un ritorno a capo indesiderato.
 *
 * Esempio con buffer[10]:
 *   Input digitato: "Ciao\n"
 *   Stringa letta:  "Ciao\n\0"   ← '\n' incluso
 *   Dopo rimozione: "Ciao\0"     ← '\n' sostituito con '\0'
 */

#include <stdio.h>

int main(void) {

    /* Buffer per nome completo: 50 caratteri + '\0' */
    char nome_completo[51];

    /* Buffer per indirizzo: 100 caratteri + '\0' */
    char indirizzo[101];

    /* Buffer per una nota libera: 200 caratteri + '\0' */
    char nota[201];

    /* Indice per scorrere la stringa e trovare '\n' */
    int i;

    printf("=== LETTURA DATI CON fgets ===\n\n");

    /* --- LETTURA CON fgets ---
     * fgets(buffer, N, stdin) legge al massimo N-1 caratteri
     * lasciando spazio per il terminatore '\0'.
     * Legge anche gli spazi, a differenza di scanf. */
    printf("Inserisci nome e cognome: ");
    fgets(nome_completo, 51, stdin);

    /* --- RIMOZIONE DEL '\n' FINALE ---
     * fgets include '\n' nella stringa. Dobbiamo trovarlo e
     * sostituirlo con '\0' per eliminarlo.
     * Scorriamo la stringa fino a trovare '\n' oppure '\0'. */
    i = 0;
    while (nome_completo[i] != '\n' && nome_completo[i] != '\0') {
        i++; /* avanza finché non troviamo '\n' o la fine */
    }
    /* Ora nome_completo[i] è '\n' oppure '\0'.
     * In entrambi i casi sostituiamo con '\0': se era '\n' lo eliminiamo,
     * se era già '\0' non cambia nulla. */
    nome_completo[i] = '\0';

    printf("Inserisci il tuo indirizzo: ");
    fgets(indirizzo, 101, stdin);

    /* Rimozione '\n' dall'indirizzo con lo stesso metodo */
    i = 0;
    while (indirizzo[i] != '\n' && indirizzo[i] != '\0') {
        i++;
    }
    indirizzo[i] = '\0';

    printf("Inserisci una nota (max 200 caratteri): ");
    fgets(nota, 201, stdin);

    /* Rimozione '\n' dalla nota */
    i = 0;
    while (nota[i] != '\n' && nota[i] != '\0') {
        i++;
    }
    nota[i] = '\0';

    /* Stampa dei dati raccolti */
    printf("\n");
    printf("========================================\n");
    printf("  RIEPILOGO DATI INSERITI              \n");
    printf("========================================\n");
    printf("Nome completo : %s\n", nome_completo);
    printf("Indirizzo     : %s\n", indirizzo);
    printf("Nota          : %s\n", nota);
    printf("========================================\n");
    printf("\n");

    /* --- CONFRONTO fgets vs scanf ---
     * fgets è preferibile a scanf per le stringhe perché:
     *
     * scanf("%s", s):
     *   - Si ferma al primo spazio → non legge nomi composti
     *   - Senza modificatore di larghezza, rischio buffer overflow
     *
     * fgets(s, N, stdin):
     *   - Legge l'intera riga inclusi gli spazi
     *   - Limita sempre i caratteri a N-1: nessun rischio overflow
     *   - Include '\n': va rimosso manualmente
     *
     * QUANDO usare scanf: codici, username, token senza spazi
     * QUANDO usare fgets: nomi, indirizzi, frasi, testo libero */
    printf("SUGGERIMENTO: usa fgets per input con spazi, scanf per token.\n");

    return 0;
}
