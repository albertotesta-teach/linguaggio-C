# Analisi – 060-problema-prenotazioni-con-indici.c

## 1. Problema

Il laboratorio di informatica riceve nuove postazioni durante l'anno: il
blocco delle postazioni si ingrandisce con `realloc` e può spostarsi in
memoria. Le prenotazioni ricordano la postazione con il suo indice, non
con un puntatore, così restano valide anche dopo lo spostamento. Se una
postazione si guasta, le sue prenotazioni passano alla prima postazione
libera.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `k` | `int` | Postazioni iniziali, da 1 a 40 |
| `comando` | `char` | `N k` nuove postazioni, `G n` guasto, `P studente` prenota, `E` elenco, `Q` fine (anche minuscoli) |

### Output

- `postazioni: N (blocco in <indirizzo>)` dopo un ingrandimento.
- `PC-nn guasta` e per ogni prenotazione coinvolta `prenotazione di X
  spostata su PC-mm` oppure `X resta senza postazione`.
- `studente: PC-nn`, `Nessuna postazione libera.`
- `E`: le prenotazioni con la postazione o `(nessuna)`, e i totali.
- `Numero non valido.`, `Postazione non valida.`, `Nome mancante.`,
  `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- `nuove_postazioni`: `realloc` in un temporaneo, nuove postazioni
  `PC-nn` funzionanti; al massimo 40.
- Le prenotazioni usano l'indice (−1 = nessuna): un puntatore al blocco
  vecchio non sarebbe più valido dopo `realloc`.
- Libera: funzionante e non prenotata; si sceglie la prima.
- Il blocco delle prenotazioni cresce di uno con `realloc` (partendo da
  `NULL`).
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- L'indirizzo stampato cambia a ogni esecuzione.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Postazione` | `typedef struct { char codice[16]; int funzionante; } Postazione;` | Un computer |
| `Prenotazione` | `typedef struct { char studente[20]; int postazione; } Prenotazione;` | Una prenotazione con l'indice della postazione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `pc`, `n_pc` | `Postazione *`, `int` | Blocco delle postazioni |
| `pren`, `n_pren`, `tmp` | `Prenotazione *`, `int`, `Prenotazione *` | Blocco delle prenotazioni |
| `scelta` | `int` | Postazione libera trovata |

| Funzione | Compito |
|----------|---------|
| `nuove_postazioni(&pc, &n_pc, k)` | Ingrandisce il blocco; 0 se fallisce |
| `libera(pc, n_pc, pren, n_pren)` | Indice della prima postazione libera, −1 se nessuna |

### Algoritmo in linguaggio naturale

1. Creare le postazioni iniziali.
2. Finché il comando non è `Q`: leggere il comando in maiuscolo; con `N`
   ingrandire; con `G` segnare il guasto e spostare le prenotazioni; con
   `P` prenotare la prima libera; con `E` stampare; scartare il resto
   della riga.
3. Liberare i due blocchi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe); l'indirizzo è
sostituito da `<indirizzo>`.

### Test 1 – Guasti e nuove postazioni

- **Input:** `2`, `P Rossi`, `p Bianchi`, `P Verdi`, `N 2`, `P Verdi`,
  `G 1`, `G 1`, `G 9`, `E extra`, `G 2`, `G 3`, `E`, `X`, `Q`
- **Output atteso:**
  ```
    Rossi: PC-01
    Bianchi: PC-02
    Nessuna postazione libera.
    postazioni: 4 (blocco in <indirizzo>)
    Verdi: PC-03
    PC-01 guasta
    prenotazione di Rossi spostata su PC-04
    Postazione non valida.
    Postazione non valida.
    Rossi      PC-04
    Bianchi    PC-02
    Verdi      PC-03
    postazioni: 4, prenotazioni: 3
    PC-02 guasta
    Bianchi resta senza postazione
    PC-03 guasta
    Verdi resta senza postazione
    Rossi      PC-04
    Bianchi    (nessuna)
    Verdi      (nessuna)
    postazioni: 4, prenotazioni: 3
    Comando sconosciuto.
  ```
