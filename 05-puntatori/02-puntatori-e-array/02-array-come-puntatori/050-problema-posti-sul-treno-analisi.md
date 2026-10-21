# Analisi – 050-problema-posti-sul-treno.c

## 1. Problema

Una carrozza ha 20 posti in fila, alcuni già occupati. Per ogni gruppo di
persone che chiede posti vicini il programma cerca il primo blocco di posti
liberi consecutivi abbastanza grande, lo prenota e mostra la carrozza
aggiornata; se il blocco non esiste lo segnala. Con 0 il programma termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `k` | `int` | Persone del gruppo (1-20), letto da tastiera; 0 per finire |
| `posti` | `int[20]` | Stato iniziale (1 occupato, 0 libero), nel sorgente |

### Output

- La mappa della carrozza (`[nn]` posto libero, `[XX]` occupato) e il numero
  di posti liberi, all'inizio e dopo ogni prenotazione.
- `Prenotato il posto N.` oppure `Prenotati i posti dal N al M.`
- `Nessun gruppo di k posti vicini libero.` oppure `Numero non valido.`

### Vincoli

- Le funzioni ricevono il puntatore al primo posto e il numero di posti.
- `cerca_liberi` scorre i posti con un puntatore contando i liberi
  consecutivi; si ferma appena il conteggio arriva a `k` e restituisce la
  posizione del primo posto del blocco (`(p − posti) − k + 1`), -1 se non
  esiste.
- `occupa` riceve l'intervallo `[inizio, fine)`, con `fine` escluso:
  `occupa(posti + i, posti + i + k)`.
- Il numero di persone deve essere tra 1 e 20; un testo non numerico è un
  numero non valido (la riga si scarta); a fine input il programma termina
  come con 0.

### Assunzioni

- Si sceglie il primo blocco da sinistra, anche se più avanti ce n'è uno
  della misura esatta.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `i` | `int` | Posizione del primo posto trovato, -1 se nessuno |
| `letti` | `int` | Valore restituito da `scanf` |
| `p`, `consecutivi`, `trovato` | `const int *`, `int`, `int` | In `cerca_liberi` |

| Funzione | Compito |
|----------|---------|
| `cerca_liberi(posti, n, k)` | Posizione del primo blocco di `k` posti liberi, -1 se non c'è |
| `occupa(inizio, fine)` | Segna occupati i posti in `[inizio, fine)` |
| `stampa_carrozza(posti, n)` | Mappa dei posti e numero di liberi |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non numerico |

### Algoritmo in linguaggio naturale

1. Stampare la carrozza.
2. Finché `k` è diverso da 0:
   1. leggere `k` (a fine input usare 0; se non è un numero scartare la riga
      e considerarlo non valido);
   2. se `k` è fuori da 0-20 segnalarlo;
   3. se `k > 0` cercare il blocco: se non c'è segnalarlo, altrimenti
      occupare i posti, stampare quali e la carrozza aggiornata.

## 3. Casi di test

Nell'output i numeri inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `2`, `3`, `4`, `25`, `abc`, `1`, `0`
- **Valori intermedi attesi:** per 2 il primo blocco è 4-5 (il posto 1 è
  libero ma isolato); per 3 il blocco 13-15; per 4 non resta nessun blocco
  di 4 posti.
- **Output atteso** (risposte nell'ordine):
  ```
    Prenotati i posti dal 4 al 5.
    [ 1][XX][XX][XX][XX][ 6][XX][ 8][ 9][XX][XX][XX][13][14][15][16][XX][18][XX][XX]
    Posti liberi: 9 su 20
    Prenotati i posti dal 13 al 15.
    [ 1][XX][XX][XX][XX][ 6][XX][ 8][ 9][XX][XX][XX][XX][XX][XX][16][XX][18][XX][XX]
    Posti liberi: 6 su 20
    Nessun gruppo di 4 posti vicini libero.
    Numero non valido.
    Numero non valido.
    Prenotato il posto 1.
    [XX][XX][XX][XX][XX][ 6][XX][ 8][ 9][XX][XX][XX][XX][XX][XX][16][XX][18][XX][XX]
    Posti liberi: 5 su 20
  ```

### Test 2 – Fine dell'input

- **Input:** `5`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Valori intermedi attesi:** il blocco libero più lungo è 13-16
  (4 posti).
- **Output atteso:** `Nessun gruppo di 5 posti vicini libero.`, poi il
  programma termina senza ripetere la domanda.
