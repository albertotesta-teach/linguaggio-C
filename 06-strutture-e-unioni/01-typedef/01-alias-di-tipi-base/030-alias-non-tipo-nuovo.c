/*
 * 030-alias-non-tipo-nuovo.c
 *
 * Il limite di typedef: un nome nuovo, non un tipo nuovo
 *
 * typedef dà un NOME a un tipo esistente, ma non crea un tipo diverso:
 *
 *     typedef double Euro;
 *     typedef double Chilometri;
 *
 * Euro, Chilometri e double sono lo STESSO tipo. Il compilatore accetta
 * di assegnare dei Chilometri a una variabile Euro e di passare i
 * parametri di una funzione nell'ordine sbagliato: non c'è nessun errore
 * e nessun avviso, anche con -Wall -Wextra.
 *
 * Esempio: il costo del carburante per la gita di classe. La funzione
 * riceve chilometri, consumo e prezzo al litro; se il chiamante scambia
 * i chilometri con il consumo, il programma compila e dà un risultato
 * sbagliato.
 *
 * Un tipo davvero nuovo, che il compilatore distingue dagli altri, si
 * costruisce con struct (sottocapitolo 02-struct): lì typedef servirà a
 * dargli un nome comodo.
 */

#include <stdio.h>

typedef double Euro;
typedef double Chilometri;
typedef double KmPerLitro;

Euro costo_carburante(Chilometri distanza, KmPerLitro consumo, Euro prezzo_litro);

int main(void)
{
    Chilometri andata_e_ritorno = 2 * 145.0;
    KmPerLitro pullman = 3.5;
    Euro gasolio = 1.79;
    Euro stranezza;

    printf("Gita a Genova: %.0f km, %.1f km/l, gasolio a %.2f euro/l\n\n",
           andata_e_ritorno, pullman, gasolio);

    /* chiamata corretta */
    printf("Costo corretto:            %8.2f euro\n",
           costo_carburante(andata_e_ritorno, pullman, gasolio));

    /* chiamata con distanza e consumo scambiati: Chilometri e KmPerLitro
     * sono entrambi double, quindi il compilatore non se ne accorge */
    printf("Parametri scambiati:       %8.2f euro   <- nessun errore di compilazione\n",
           costo_carburante(pullman, andata_e_ritorno, gasolio));

    /* anche l'assegnamento tra "tipi" diversi è accettato */
    stranezza = andata_e_ritorno;
    printf("Euro stranezza = km:       %8.2f euro   <- accettato\n", stranezza);

    printf("\nEuro e Chilometri sono due nomi dello stesso tipo double.\n");

    return 0;
}

/* Litri necessari = distanza / consumo; costo = litri * prezzo. */
Euro costo_carburante(Chilometri distanza, KmPerLitro consumo, Euro prezzo_litro)
{
    return distanza / consumo * prezzo_litro;
}
