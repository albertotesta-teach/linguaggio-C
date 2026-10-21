# Analisi – 080-problema-playlist-musicale.c

## 1. Problema

Una playlist gestisce fino a 15 brani con ID e durata in secondi in array
paralleli a tappo. Il programma deve calcolare la durata totale, trovare il
brano più lungo, inserire un brano in una posizione specifica (spostando gli
altri in avanti) e rimuovere un brano per ID (spostando gli altri indietro).

---

## 2. Analisi

### Input
Nessun input da tastiera: la playlist e le operazioni sono fisse nel codice.

| Variabile | Tipo    | Dimensione | Descrizione                                       |
|-----------|---------|------------|---------------------------------------------------|
| `id`      | `int[]` | `MAX` (18) | ID del brano, terminati da `TAPPO` (-1)           |
| `durate`  | `int[]` | `MAX` (18) | Durata in secondi, tappo nella stessa posizione   |

Playlist iniziale: 1001–1005 con durate 213, 187, 245, 198, 221 secondi.
Operazioni: inserimento del brano 1006 (230 s) all'indice 2, rimozione del
brano 1003.

### Output
- La playlist: numero, ID e durata `MM:SS` di ogni brano, con la durata
  totale;
- il brano più lungo;
- l'esito dell'inserimento ("OK" con il numero di brani, "POSIZIONE NON
  VALIDA" o "PLAYLIST PIENA") e la playlist aggiornata;
- l'esito della rimozione ("OK" oppure "BRANO NON TROVATO") e la playlist
  finale.

### Vincoli
- I due array hanno il tappo nella stessa posizione e ogni operazione li
  aggiorna entrambi
- La posizione di inserimento (0-based) è valida da 0 (in testa) fino al
  numero di brani (in coda); oltre è rifiutata
- Per inserire si sposta ogni elemento di una posizione in avanti
  **partendo dal fondo** (dal tappo fino alla posizione), altrimenti si
  sovrascriverebbero dati non ancora copiati
- L'inserimento richiede spazio anche per il tappo
- La rimozione sposta a sinistra gli elementi successivi, tappo compreso
- Le funzioni lavorano con indici da 0; la stampa numera i brani da 1
- A parità di durata il brano più lungo è il primo trovato

### Assunzioni
- ID e durate sono ≥ 0, quindi -1 non è un dato valido
- Gli ID sono univoci

### Variabili di supporto

| Variabile | Tipo      | Descrizione                                       |
|-----------|-----------|---------------------------------------------------|
| `esito`   | `int`     | Inserimento: 1 OK, 0 pieno, -1 posizione non valida |
| `min`, `sec`, `tot` | `int` | Durate convertite per la stampa           |
| `TAPPO`   | `#define` | -1                                                |
| `MAX`     | `#define` | 18                                                |

| Funzione | Descrizione |
|---|---|
| `int conta_brani(const int id[])` | Indice del tappo |
| `int durata_totale(const int durate[], const int id[])` | Somma delle durate |
| `int brano_piu_lungo(const int durate[], const int id[])` | Indice del massimo |
| `int cerca_brano(const int id[], int id_cercato)` | Indice o -1 |
| `int inserisci_in_posizione(...)` | 1 OK, 0 piena, -1 posizione non valida |
| `int rimuovi_per_id(...)` | 1 rimosso, 0 non trovato |
| `void stampa_playlist(...)` | Playlist con durata totale |

### Algoritmo in linguaggio naturale
1. Stampare la playlist iniziale e il brano più lungo.
2. Inserimento in posizione `pos`:
   a. se `pos` è negativa o maggiore del numero di brani, rifiutare;
   b. altrimenti, se non c'è spazio, rifiutare per playlist piena;
   c. altrimenti, per i dal tappo fino a `pos`, copiare l'elemento `i` in
      `i + 1`; poi scrivere il nuovo brano in `pos`.
3. Rimozione per ID: cercare l'indice; se esiste spostare a sinistra gli
   elementi successivi.
4. Stampare la playlist finale.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; i test 3–5
richiedono di modificare i parametri delle chiamate e ricompilare.

### Test 1 – Inserimento in posizione intermedia
- **Output atteso:**
```
  OK -> 6 brani in playlist

  N. | ID    | Durata
  ---|-------|-------
   1 |  1001 | 03:33
   2 |  1002 | 03:07
   3 |  1006 | 03:50
   4 |  1003 | 04:05
   5 |  1004 | 03:18
   6 |  1005 | 03:41
  Durata totale: 21:34
```

### Test 2 – Brano più lungo e rimozione
- **Output atteso:** `Brano piu' lungo: ID 1003 (245 secondi)` sulla
  playlist iniziale; dopo la rimozione `OK -> 5 brani rimanenti` e
  `Durata totale: 17:29`

### Test 3 – Inserimento in testa e in coda
- **Cosa si verifica:** le due posizioni estreme ammesse
- **Procedura:** usare come posizione 0, poi 5
- **Output atteso:** con 0 il brano 1006 è il n. 1; con 5 è il n. 6;
  in entrambi i casi `Durata totale: 21:34`

### Test 4 – Posizione non valida
- **Procedura:** usare come posizione 9
- **Output atteso:** `POSIZIONE NON VALIDA`; la playlist non cambia e,
  dopo la rimozione di 1003, restano 4 brani con `Durata totale: 13:39`

### Test 5 – Rimozione di un brano inesistente
- **Procedura:** rimuovere l'ID 9999 invece di 1003
- **Output atteso:** `BRANO NON TROVATO`
