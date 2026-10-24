# Analisi – 080-problema-pianta-sala-esame.c

## 1. Problema

L'aula magna ha 5 file da 8 banchi. Per la prova scritta i candidati si
siedono a scacchiera (un banco è occupabile se fila + banco è pari) e
alcuni banchi sono rotti. Il programma legge il numero di candidati, li
dispone in ordine, stampa la pianta e indica quanti candidati vanno in una
seconda aula. La pianta ha il tipo `Pianta`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `candidati` | `int` | Numero di candidati, non negativo |
| banchi rotti | nel sorgente | fila 2 banco 4, fila 3 banco 5, fila 5 banco 1 (indici [1][3], [2][4], [4][0]) |

### Output

- `Banchi disponibili a scacchiera: 17`.
- La pianta con la cattedra, una riga per fila e la legenda.
- `Candidati sistemati: S` e, se servono altri posti,
  `Serve una seconda aula per K candidati.` (`candidato` al singolare).
- Con un valore negativo o non numerico: `Valore non valido.`

### Vincoli

- `typedef char Pianta[5][8];` con `'.'` libero, `'#'` rotto, `'C'`
  candidato.
- Un banco è occupabile se `(fila + banco) % 2 == 0` e non è rotto: così
  nessun candidato ha un vicino davanti, dietro o di lato.
- I banchi si assegnano in ordine, fila per fila, da sinistra a destra.

### Assunzioni

- I banchi rotti sono fissati nel programma (tutti e tre in posizione a
  scacchiera: la capienza scende da 20 a 17).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Pianta` | `typedef char Pianta[FILE_BANCHI][BANCHI];` | Un carattere per ogni banco |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `aula` | `Pianta` | Stato dei banchi |
| `candidati` | `int` | Numero letto |
| `sistemati` | `int` | Candidati effettivamente disposti |

| Funzione | Compito |
|----------|---------|
| `occupabile(p, f, b)` | 1 se il banco è a scacchiera e non rotto |
| `capienza(p)` | Numero di banchi occupabili |
| `disponi(p, candidati)` | Scrive `'C'` nei banchi e restituisce quanti ne ha usati |
| `stampa(p)` | Disegna la pianta con la legenda |

### Algoritmo in linguaggio naturale

1. Segnare tutti i banchi liberi, poi i tre rotti.
2. Stampare la capienza.
3. Leggere il numero di candidati; se non valido segnalarlo e terminare.
4. Disporre i candidati nei banchi occupabili finché ci sono candidati e
   posti.
5. Stampare la pianta, i sistemati e, se ne mancano, quanti vanno nella
   seconda aula.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Posti sufficienti

- **Cosa si verifica:** disposizione a scacchiera che salta i banchi rotti.
- **Input:** `12`
- **Output atteso:**
  ```
  Banchi disponibili a scacchiera: 17
  Numero di candidati: 
           CATTEDRA
    fila 1 C . C . C . C . 
    fila 2 . C . # . C . C 
    fila 3 C . C . # . C . 
    fila 4 . C . C . . . . 
    fila 5 # . . . . . . . 
    C = candidato, . = libero, # = banco rotto

  Candidati sistemati: 12
  ```

### Test 2 – Posti insufficienti

- **Cosa si verifica:** i candidati in eccesso vanno nella seconda aula.
- **Input:** `20`
- **Output atteso:** tutti i 17 banchi occupabili con `C`;
  `Candidati sistemati: 17` e `Serve una seconda aula per 3 candidati.`

### Test 3 – Un solo candidato in eccesso

- **Cosa si verifica:** il messaggio al singolare.
- **Input:** `18`
- **Output atteso:** `Serve una seconda aula per 1 candidato.`

### Test 4 – Nessun candidato

- **Input:** `0`
- **Output atteso:** pianta senza `C`, `Candidati sistemati: 0`.

### Test 5 – Valore non valido

- **Input:** `-4` (poi `abc`)
- **Output atteso:** `Valore non valido.`
