# 01 – Definizione e chiamata di funzioni

## Concetto

Una **funzione** è un blocco di codice con un nome, che può essere richiamato
(chiamato) da qualsiasi punto del programma. Le funzioni permettono di:

- **Suddividere** un programma complesso in parti più piccole e gestibili
- **Riutilizzare** lo stesso codice senza riscriverlo
- **Isolare** le responsabilità: ogni funzione fa una cosa sola

### Struttura di una funzione

```
tipo_ritorno nome_funzione(tipo param1, tipo param2, ...) {
    /* corpo della funzione */
    istruzioni;
}
```

- **tipo_ritorno**: il tipo del valore restituito (`int`, `double`, `void`, ...)
- **nome_funzione**: identificatore descrittivo in italiano
- **parametri**: dati forniti al momento della chiamata (possono mancare)
- **corpo**: le istruzioni da eseguire

### Funzioni void

Le funzioni di tipo `void` non restituiscono alcun valore. Sono utili quando
la funzione produce effetti (stampa a schermo, modifica variabili globali)
senza dover comunicare un risultato al chiamante.

```c
void stampa_titolo(void) {
    printf("=== Report ===\n");
}
```

La chiamata non usa un valore di ritorno:

```c
stampa_titolo();   /* corretto */
```

### Il prototipo

Se una funzione è definita **dopo** il punto in cui viene chiamata, il
compilatore non la conosce ancora e segnala un errore. Il **prototipo**
risolve questo problema: è una dichiarazione anticipata che termina con `;`
al posto del corpo.

```c
void stampa_titolo(void);   /* prototipo: il corpo viene dopo */

int main(void) {
    stampa_titolo();        /* chiamata: il compilatore conosce già la firma */
    return 0;
}

void stampa_titolo(void) {  /* definizione completa */
    printf("=== Report ===\n");
}
```

### Schema di chiamata

```
main()
  │
  ├──► stampa_intestazione()   esegue il corpo, poi torna
  │
  ├──► stampa_corpo()          esegue il corpo, poi torna
  │
  └──► stampa_piede()          esegue il corpo, poi torna
```

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-prima-funzione.c` | Concetto base | Sintassi di base: definizione, chiamata, funzioni void senza parametri |
| `020-prototipo.c` | Concetto base | Separazione prototipo/definizione, main prima delle funzioni |
| `030-funzioni-void.c` | Concetto base | Organizzare un documento complesso con funzioni void composte |
| `040-problema-menu-ristorante.c` | Problema specifico | Menu di un ristorante con funzioni per sezione |
| `040-problema-menu-ristorante-analisi.md` | Analisi | Analisi del problema menu ristorante |
| `050-problema-ricevuta-cassa.c` | Problema specifico | Ricevuta fiscale con tabella prodotti e riepilogo IVA |
| `050-problema-ricevuta-cassa-analisi.md` | Analisi | Analisi del problema ricevuta cassa |
| `060-problema-disegno-forme.c` | Problema specifico | Disegno di rettangolo, triangolo e cornice in ASCII art |
| `060-problema-disegno-forme-analisi.md` | Analisi | Analisi del problema disegno forme |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-prima-funzione 010-prima-funzione.c
./010-prima-funzione

gcc -Wall -Wextra -o 020-prototipo 020-prototipo.c
./020-prototipo

gcc -Wall -Wextra -o 030-funzioni-void 030-funzioni-void.c
./030-funzioni-void

gcc -Wall -Wextra -o 040-problema-menu-ristorante 040-problema-menu-ristorante.c
./040-problema-menu-ristorante

gcc -Wall -Wextra -o 050-problema-ricevuta-cassa 050-problema-ricevuta-cassa.c
./050-problema-ricevuta-cassa

gcc -Wall -Wextra -o 060-problema-disegno-forme 060-problema-disegno-forme.c
./060-problema-disegno-forme
```

---

## Output atteso

### 010-prima-funzione
```
==============================
  Benvenuto nel programma C!  
==============================
------------------------------
Questo testo è nel main.
------------------------------
Anche questo testo è nel main.
------------------------------
==============================
  Arrivederci!                
==============================
```

### 020-prototipo
```
+---------------------------+
|   REPORT SETTIMANALE      |
+---------------------------+
| Lunedi    : attivita A    |
| Martedi   : attivita B    |
| Mercoledi : attivita C    |
| Giovedi   : attivita D    |
| Venerdi   : attivita E    |
+---------------------------+
|   Fine report             |
+---------------------------+
```

### 030-funzioni-void
```
FATTURA N. 2024-001
Data: 15/03/2024
Cliente: Rossi Mario
-----------------------------------
Prodotto A        x2     20.00 EUR
Prodotto B        x1     15.50 EUR
Servizio extra    x1      5.00 EUR
-----------------------------------

Subtotale (IVA escl.):      40.50
IVA 22%:                     8.91
===================================
TOTALE:                     49.41

Grazie per la fiducia!
```

### 040-problema-menu-ristorante
```
*******************************************
*        TRATTORIA DA LUIGI               *
*          Via Roma 12, Milano            *
*        Tel. 02-1234567                  *
*******************************************

--- ANTIPASTI ---
  Bruschetta al pomodoro          4.50 EUR
  Tagliere di salumi misti         9.00 EUR
  Burrata con pomodorini          7.50 EUR

--- PRIMI PIATTI ---
  Spaghetti alla carbonara        10.00 EUR
  Risotto ai funghi porcini       12.00 EUR
  Penne all'arrabbiata             8.50 EUR
  Lasagne al ragu'                11.00 EUR

--- SECONDI PIATTI ---
  Tagliata di manzo               16.00 EUR
  Branzino al forno               14.00 EUR
  Pollo alla cacciatora           12.50 EUR

--- DOLCI ---
  Tiramisu'                        5.00 EUR
  Panna cotta ai frutti di bosco   4.50 EUR
  Gelato artigianale (3 gusti)     4.00 EUR

*******************************************
* Il coperto e' di 2.00 EUR a persona    *
* Siamo aperti dal martedi' alla domenica*
* dalle 12:00 alle 15:00 e dalle 19:00  *
*******************************************
```

### 050-problema-ricevuta-cassa
```
        SUPERMERCATO BIANCHI
       Corso Italia 45 - Torino
       P.IVA 01234567890
       Tel. 011-9876543
------------------------------------
Prodotto             Qta Prezzo  Totale
------------------------------------
Latte intero 1L        2   1.35    2.70
Pane di casa           1   2.20    2.20
Passata pomodoro       3   0.99    2.97
Olio extravergine      1   6.50    6.50
Pasta 500g             4   1.10    4.40
------------------------------------
Subtotale (IVA escl.):      18.77
IVA (5% alimentari):         0.94
------------------------------------
TOTALE:                     19.71
------------------------------------
Pagamento: CARTA            19.71
Resto:                       0.00

  Scontrino N. 00247  Cassa: 03
  Data: 20/03/2024   Ora: 10:42

  Grazie per la visita!
  Conservare lo scontrino.
```

### 060-problema-disegno-forme
```
=== Galleria di forme ASCII ===

Rettangolo (8x5):
********
********
********
********
********

Triangolo rettangolo (base 5):
*
**
***
****
*****

Cornice (8x5):
********
*      *
*      *
*      *
********
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: chiamare una funzione prima del prototipo o della definizione */
int main(void) {
    stampa_titolo();   /* errore: il compilatore non conosce ancora stampa_titolo */
    return 0;
}
void stampa_titolo(void) { printf("Titolo\n"); }

/* SOLUZIONE: aggiungere il prototipo sopra main, oppure spostare
 * la definizione prima di main */
```

```c
/* ERRORE 2: dimenticare le parentesi nella chiamata */
void stampa_titolo(void) { printf("Titolo\n"); }

int main(void) {
    stampa_titolo;   /* ERRATO: non è una chiamata, è solo il nome della funzione */
    stampa_titolo(); /* CORRETTO */
    return 0;
}
```

```c
/* ERRORE 3: usare il valore di ritorno di una funzione void */
void stampa_messaggio(void) { printf("Ciao\n"); }

int main(void) {
    int x = stampa_messaggio();   /* errore: void non ha valore da assegnare */
    return 0;
}
```

```c
/* ERRORE 4: prototipo con firma diversa dalla definizione */
void stampa_dati(int x);          /* prototipo: parametro int */

void stampa_dati(double x) {      /* definizione: parametro double → errore */
    printf("%f\n", x);
}
```

---

## Concetti collegati

- `02-parametri-e-return` – come passare dati a una funzione e ricevere risultati
- `03-ricorsione` – funzioni che chiamano se stesse
- `04-scope-e-visibilita` – dove vive una variabile e chi può vederla

---

## Esercizi proposti

1. **(Facile)** Scrivi una funzione `void stampa_asterischi(void)` che stampa
   una riga di 20 asterischi. Chiamala tre volte dal main per creare un
   separatore decorativo.

2. **(Medio)** Organizza la stampa di una pagella scolastica usando funzioni:
   `stampa_intestazione_pagella()`, `stampa_materia()`, `stampa_media()`.
   I dati (nome studente, materie, voti) sono fissi nel codice.

3. **(Avanzato)** Disegna una scacchiera 8x8 in ASCII art usando due funzioni:
   `stampa_riga_pari()` e `stampa_riga_dispari()`, che stampano righe
   alternate di `# ` e ` #`. Chiamale in alternanza da un ciclo nel main.
