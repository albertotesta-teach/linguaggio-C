/*
 * 060-problema-intestazione-documento.c
 *
 * Intestazione di un documento scolastico
 *
 * Il programma chiede all'utente di inserire i dati numerici che
 * identificano un documento scolastico (anno scolastico, numero classe,
 * numero progressivo del documento, data) e produce un'intestazione
 * formattata pronta per essere usata su carta o a schermo.
 *
 * Non si usano stringhe né array: i dati non numerici (nome scuola,
 * materia, tipo documento) sono testo fisso nelle printf, per rispettare
 * i vincoli del capitolo 01-introduzione.
 */

#include <stdio.h>

int main(void)
{
    /* anno scolastico: si inseriscono le due parti separatamente
     * (es. 2024 e 2025 per l'anno 2024/2025) */
    int anno_inizio;
    int anno_fine;

    /* identificativi del documento */
    int numero_classe;      /* es. 3 per "3ª classe" */
    int sezione;            /* lettera della sezione come intero: 1=A, 2=B, ... */
    int numero_documento;   /* numero progressivo del documento nell'anno */

    /* data di emissione */
    int giorno;
    int mese;
    int anno;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Generazione intestazione documento ===\n\n");

    printf("Anno scolastico - anno di inizio (es. 2024): ");
    scanf("%d", &anno_inizio);
    anno_fine = anno_inizio + 1;

    printf("Numero classe (es. 3):                       ");
    scanf("%d", &numero_classe);

    printf("Sezione come numero (1=A, 2=B, 3=C ...):     ");
    scanf("%d", &sezione);

    printf("Numero progressivo documento:                 ");
    scanf("%d", &numero_documento);

    printf("Data - giorno:                                ");
    scanf("%d", &giorno);
    printf("Data - mese:                                  ");
    scanf("%d", &mese);
    printf("Data - anno:                                  ");
    scanf("%d", &anno);

    /* ── output: intestazione formattata ────────────────────────────────── */
    printf("\n");
    printf("====================================================\n");
    printf("  ISTITUTO TECNICO INDUSTRIALE \"G. MARCONI\"\n");
    printf("====================================================\n");
    printf("  Anno scolastico: %d / %d\n", anno_inizio, anno_fine);
    printf("  Classe:          %d^  Sezione: %d\n", numero_classe, sezione);
    printf("  Materia:         Informatica e Sistemi\n");
    printf("  Documento n.:    %03d\n", numero_documento);
    printf("  Data:            %02d / %02d / %d\n", giorno, mese, anno);
    printf("====================================================\n");
    printf("  Verifica scritta - Primo quadrimestre\n");
    printf("====================================================\n");

    return 0;
}
