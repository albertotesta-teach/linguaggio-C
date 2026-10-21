# Analisi – 080-problema-aula-libera.c

## 1. Problema

Al primo piano della scuola ci sono 10 aule in fila lungo un corridoio.
Quando un docente chiede un'aula, se è libera gli viene assegnata;
altrimenti riceve la libera più vicina (a parità di distanza quella con il
numero più basso). Se sono tutte occupate lo si segnala. Con 0 termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `richiesta` | `int` | Numero dell'aula chiesta (1-10); 0 per finire |
| `occupata` | `int[10]` | Stato iniziale (nel sorgente): libere le aule 2, 6 e 9 |

### Output

- La mappa del corridoio (`[ n X]` occupata, `[ n  ]` libera) all'inizio e
  dopo ogni assegnazione.
- `Assegnata l'aula N.` oppure `Aula N occupata: assegnata l'aula M.`
- `Nessuna aula libera.` oppure `Aula inesistente.`

### Vincoli

- `piu_vicina` restituisce l'indirizzo dell'elemento dell'aula assegnata
  oppure `NULL`; il `main` la segna occupata con `*aula = 1` e ricava il
  numero con `aula − occupata + 1`. Con `NULL` non si scrive nulla.
- La ricerca allarga la distanza da 0 a 9: a ogni distanza si controlla
  prima a sinistra, poi a destra; così a parità vince il numero più basso.
- Le posizioni si controllano come indici prima di costruire il puntatore:
  un indirizzo fuori dall'array non si calcola nemmeno.
- Un input non numerico è un'aula inesistente (la riga si scarta); a fine
  input il programma termina come con 0.

### Assunzioni

- Il corridoio è dritto: la distanza è la differenza dei numeri.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `aula` | `int *` | Elemento dell'aula assegnata, `NULL` se nessuna |
| `letti` | `int` | Valore restituito da `scanf` |
| `centro`, `d`, `trovata` | `int`, `int`, `int *` | In `piu_vicina` |

| Funzione | Compito |
|----------|---------|
| `piu_vicina(occupata, n, richiesta)` | Puntatore all'aula libera più vicina, `NULL` se nessuna |
| `stampa_corridoio(occupata, n)` | Mappa delle aule |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Stampare il corridoio.
2. Finché la richiesta non è 0:
   1. leggere la richiesta (a fine input 0; se non è un numero scartare la
      riga e considerarla inesistente);
   2. se è fuori da 1-10 segnalarlo;
   3. altrimenti cercare la più vicina: se `NULL` segnalarlo; altrimenti
      segnarla occupata, stampare l'assegnazione e il corridoio.
3. In `piu_vicina`: per `d` da 0 finché non si trova un'aula: se l'aula a
   sinistra (`centro − d`) esiste ed è libera prenderla, altrimenti se
   quella a destra (`centro + d`) esiste ed è libera prenderla.

## 3. Casi di test

Nell'output le richieste inserite non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `2`, `5`, `5`, `1`, `10`, `12`, `abc`, `0`
- **Output atteso:**
  ```
    Corridoio: [ 1 X] [ 2  ] [ 3 X] [ 4 X] [ 5 X] [ 6  ] [ 7 X] [ 8 X] [ 9  ] [10 X]
    Assegnata l'aula 2.
    Corridoio: [ 1 X] [ 2 X] [ 3 X] [ 4 X] [ 5 X] [ 6  ] [ 7 X] [ 8 X] [ 9  ] [10 X]
    Aula 5 occupata: assegnata l'aula 6.
    Corridoio: [ 1 X] [ 2 X] [ 3 X] [ 4 X] [ 5 X] [ 6 X] [ 7 X] [ 8 X] [ 9  ] [10 X]
    Aula 5 occupata: assegnata l'aula 9.
    Corridoio: [ 1 X] [ 2 X] [ 3 X] [ 4 X] [ 5 X] [ 6 X] [ 7 X] [ 8 X] [ 9 X] [10 X]
    Nessuna aula libera.
    Nessuna aula libera.
    Aula inesistente.
    Aula inesistente.
  ```

### Test 2 – Parità di distanza

- **Cosa si verifica:** a parità vince l'aula con il numero più basso.
- **Input:** `4`, `0` (stato iniziale)
- **Valori intermedi attesi:** a distanza 1 le aule 3 e 5 sono occupate; a
  distanza 2 sono libere sia la 2 sia la 6: si controlla prima la 2.
- **Output atteso:** `  Aula 4 occupata: assegnata l'aula 2.`
