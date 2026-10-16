/*
 * 030-rimuovere-e-rinominare.c
 *
 * remove e rename: cancellare e rinominare un file
 *
 * Due funzioni di <stdio.h> lavorano sui file senza aprirli:
 *
 *     remove(nome)             cancella il file
 *     rename(vecchio, nuovo)   cambia il nome del file
 *
 * Entrambe restituiscono 0 se riescono e un valore diverso da 0 se
 * falliscono (file inesistente, permessi, file aperto su Windows). Il
 * file non deve essere aperto quando lo si rimuove o rinomina.
 *
 * Se il nuovo nome di rename esiste già, il comportamento dipende dal
 * sistema: Linux e macOS lo sostituiscono, Windows rifiuta. Per un
 * programma portabile si rimuove prima la destinazione.
 *
 * Salvataggio sicuro. Riscrivere un file importante con "w" lo svuota
 * subito: se il programma si interrompe a metà, il vecchio contenuto è
 * perso e il nuovo è incompleto. Si scrive invece un file temporaneo e
 * solo alla fine lo si mette al posto dell'originale:
 *
 *     scrivi tutto in  dati.tmp
 *     fclose           (i dati sono davvero nel file)
 *     remove("dati.txt")
 *     rename("dati.tmp", "dati.txt")
 *
 * Fino alla rename il file originale resta intatto.
 *
 * Il programma crea bozza.txt, lo rinomina, prova operazioni che
 * falliscono e infine lo rimuove, stampando l'esito di ogni passo.
 */

#include <stdio.h>

void esito(const char *operazione, int risultato);
int esiste(const char *nome);

int main(void)
{
    FILE *f;

    f = fopen("bozza.txt", "w");
    if (f == NULL) {
        fprintf(stderr, "Impossibile creare bozza.txt\n");
    } else {
        fputs("Circolare n. 42: uscita anticipata venerdi'\n", f);
        fclose(f);
        printf("creato bozza.txt\n");

        esito("rename(\"bozza.txt\", \"circolare.txt\")", rename("bozza.txt", "circolare.txt"));
        printf("  bozza.txt esiste: %s, circolare.txt esiste: %s\n",
               esiste("bozza.txt") ? "si'" : "no", esiste("circolare.txt") ? "si'" : "no");

        esito("rename(\"bozza.txt\", \"altro.txt\")", rename("bozza.txt", "altro.txt"));

        esito("remove(\"circolare.txt\")", remove("circolare.txt"));
        printf("  circolare.txt esiste: %s\n", esiste("circolare.txt") ? "si'" : "no");

        esito("remove(\"circolare.txt\")", remove("circolare.txt"));
    }

    return 0;
}

void esito(const char *operazione, int risultato)
{
    if (risultato == 0) {
        printf("%-40s riuscita\n", operazione);
    } else {
        printf("%-40s fallita (il file non c'e')\n", operazione);
    }
}

int esiste(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int trovato = f != NULL;

    if (trovato) {
        fclose(f);
    }
    return trovato;
}
