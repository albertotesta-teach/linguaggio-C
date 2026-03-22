/*
 * 030-funzioni-che-modificano-array.c
 *
 * Funzioni che modificano il contenuto di un array in-place.
 *
 * Poiché gli array vengono passati per riferimento, una funzione
 * può modificarne i valori direttamente. Le modifiche sono visibili
 * nel chiamante subito dopo il ritorno dalla funzione.
 *
 * Questo file mostra i pattern più comuni di trasformazione:
 *  - azzeramento completo
 *  - applicazione di una formula a ogni elemento
 *  - inversione dell'ordine (swap con variabile d'appoggio)
 *  - copia da un array a un altro
 * ciascuno incapsulato in una funzione riusabile.
 */

#include <stdio.h>

/* Stampa utilitaria */
void stampa(const int arr[], int n, const char etichetta[]) {
    int i;
    printf("%s: [ ", etichetta);
    for (i = 0; i < n; i++) {
        printf("%4d", arr[i]);
    }
    printf(" ]\n");
}

/* Azzera tutti gli elementi */
void azzera(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = 0;
    }
}

/* Applica il valore assoluto a ogni elemento */
void valore_assoluto(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] < 0) {
            arr[i] = -arr[i];
        }
    }
}

/* Inverte l'ordine degli elementi (swap in-place) */
void inverti(int arr[], int n) {
    int i;
    int temp;
    for (i = 0; i < n / 2; i++) {
        temp            = arr[i];
        arr[i]          = arr[n - 1 - i];
        arr[n - 1 - i]  = temp;
    }
}

/* Somma un valore costante a ogni elemento */
void somma_costante(int arr[], int n, int k) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = arr[i] + k;
    }
}

/* Copia src in dst elemento per elemento.
 * ATTENZIONE: dst deve essere già allocato con dimensione >= n. */
void copia(const int src[], int dst[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

/* Sostituisce ogni elemento con la sua distanza dalla media.
 * Richiede di conoscere la media in anticipo (passata come parametro). */
void scarto_dalla_media(int arr[], int n, double med) {
    int i;
    for (i = 0; i < n; i++) {
        /* Lo scarto è intero: si tronca la parte decimale */
        int sc = arr[i] - (int)med;
        arr[i] = (sc >= 0) ? sc : -sc;   /* valore assoluto dello scarto */
    }
}

int main(void) {

    int originale[8] = {3, -5, 8, -2, 11, -7, 4, 6};
    int lavoro[8];
    int copia_arr[8];
    int n = 8;

    stampa(originale, n, "Originale        ");

    /* ---------------------------------------------------------------- */
    /* valore_assoluto */
    copia(originale, lavoro, n);
    valore_assoluto(lavoro, n);
    stampa(lavoro, n, "Valore assoluto  ");

    /* ---------------------------------------------------------------- */
    /* inverti */
    copia(originale, lavoro, n);
    inverti(lavoro, n);
    stampa(lavoro, n, "Invertito        ");

    /* ---------------------------------------------------------------- */
    /* somma_costante */
    copia(originale, lavoro, n);
    somma_costante(lavoro, n, 10);
    stampa(lavoro, n, "Somma +10        ");

    /* ---------------------------------------------------------------- */
    /* azzera */
    copia(originale, lavoro, n);
    azzera(lavoro, n);
    stampa(lavoro, n, "Azzerato         ");

    /* ---------------------------------------------------------------- */
    /* copia: dimostra che copia_arr è indipendente da originale */
    copia(originale, copia_arr, n);
    copia_arr[0] = 999;
    stampa(originale,  n, "Originale (dopo) ");
    stampa(copia_arr,  n, "Copia modificata ");

    /* ---------------------------------------------------------------- */
    /* scarto_dalla_media */
    copia(originale, lavoro, n);
    /* Calcola la media manualmente (solo valori positivi per semplicità) */
    int i;
    int somma = 0;
    for (i = 0; i < n; i++) {
        somma = somma + originale[i];
    }
    double med = (double)somma / n;
    printf("\nMedia originale: %.2f\n", med);
    scarto_dalla_media(lavoro, n, med);
    stampa(lavoro, n, "Scarto da media  ");

    return 0;
}
