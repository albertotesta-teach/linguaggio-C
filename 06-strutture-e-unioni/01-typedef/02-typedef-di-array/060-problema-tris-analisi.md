# Analisi – 060-problema-tris.c

## 1. Problema

Due studenti giocano a tris su una griglia 3 × 3. A turno scrivono riga e
colonna della casella; una mossa fuori griglia, su una casella occupata o
non numerica va ripetuta. Dopo ogni mossa il programma ridisegna la
griglia e controlla se c'è un tris o se la griglia è piena. La griglia ha
il tipo `Griglia`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga`, `colonna` | `int` | Casella scelta, da 1 a 3, sulla stessa riga |

### Output

- La griglia vuota all'inizio e la griglia aggiornata dopo ogni mossa
  valida.
- `Fuori dalla griglia, ripetere.`, `Casella occupata, ripetere.` o
  `Mossa non valida, ripetere.` per le mosse da ripetere.
- `Tris! Vince il giocatore X.` (oppure O) o `Griglia piena: pareggio.`
- `Partita interrotta.` se l'input termina prima della fine.

### Vincoli

- `typedef char Griglia[3][3];` con `' '` per la casella libera e `'X'` o
  `'O'` per le occupate.
- Inizia X; il turno passa solo dopo una mossa valida.
- Il controllo del tris si fa dopo ogni mossa, prima di quello della
  griglia piena (un tris con l'ultima casella è una vittoria).
- Una mossa non numerica viene scartata (resto della riga) e ripetuta.

### Assunzioni

- Le coordinate sono numerate da 1 per chi gioca e da 0 nell'array.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Griglia` | `typedef char Griglia[LATO][LATO];` | Le nove caselle |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `g` | `Griglia` | Stato della partita |
| `giocatore` | `char` | Simbolo di turno |
| `letti` | `int` | Valore restituito da `scanf` |
| `finita` | `int` | Flag di fine partita |

| Funzione | Compito |
|----------|---------|
| `stampa(g)` | Disegna la griglia |
| `ha_vinto(g, simbolo)` | 1 se il simbolo occupa una riga, una colonna o una diagonale |
| `piena(g)` | 1 se non ci sono caselle libere |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Svuotare la griglia e stamparla.
2. Finché la partita non è finita:
   1. leggere riga e colonna (a fine input interrompere la partita);
   2. se non sono numeri, fuori griglia o la casella è occupata, segnalare
      e ripetere;
   3. altrimenti scrivere il simbolo, ridisegnare la griglia e controllare
      il tris, poi la griglia piena; se nessuno dei due, cambiare turno.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Vittoria sulla diagonale con mosse da ripetere

- **Cosa si verifica:** i tre messaggi di errore (il turno non passa) e il
  tris in diagonale.
- **Input:** `2 2` (X), `2 2`, `4 1`, `ab`, `1 1` (O), `1 3` (X), `3 3`
  (O), `3 1` (X)
- **Output atteso** (dopo la prima griglia con X al centro):
  ```
    Casella occupata, ripetere.
    Fuori dalla griglia, ripetere.
    Mossa non valida, ripetere.
  ```
  e alla fine
  ```
     O |   | X
    ---+---+---
       | X |  
    ---+---+---
     X |   | O
  Tris! Vince il giocatore X.
  ```

### Test 2 – Pareggio

- **Cosa si verifica:** griglia piena senza tris.
- **Input:** `1 1`, `2 2`, `1 2`, `1 3`, `2 3`, `2 1`, `3 1`, `3 2`, `3 3`
- **Output atteso:**
  ```
     X | X | O
    ---+---+---
     O | O | X
    ---+---+---
     X | O | X
  Griglia piena: pareggio.
  ```

### Test 3 – Partita interrotta

- **Cosa si verifica:** la fine dell'input chiude la partita.
- **Input:** `1 1`, poi fine input.
- **Output atteso:** `Partita interrotta.`
