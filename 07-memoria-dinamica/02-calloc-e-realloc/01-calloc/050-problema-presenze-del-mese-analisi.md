# Analisi – 050-problema-presenze-del-mese.c

## 1. Problema

Il coordinatore riporta le assenze di un mese. Il programma legge il
numero di studenti e di giorni, alloca con `calloc` una matrice giorni ×
studenti in un solo blocco (tutti presenti, cioè 0) e per ogni giorno
segna gli assenti. Stampa la tabella del mese, le assenze di ogni studente
con un avviso oltre il 25% e il giorno con più assenti.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `studenti`, `giorni` | `int` | Da 1 a 30 e da 1 a 25 |
| assenti | `int` | Per ogni giorno i numeri degli studenti assenti, poi 0 |

### Output

- `studente N inesistente`, `numero non valido` per i dati scartati.
- La tabella: una riga per studente con `A` (assente) o `.` per ogni
  giorno, il totale e `oltre il 25%` se serve.
- `Giorno con piu' assenti: G (A su S)`.
- `Dati non validi (...)`, `Memoria insufficiente.`

### Vincoli

- `assente = calloc(giorni * studenti, sizeof *assente)`: tutto a 0;
  l'elemento (g, s) sta in `assente[g * studenti + s]`.
- Oltre il 25%: assenze × 4 > giorni.
- A parità vale il primo giorno.
- Una parola non numerica si scarta e si continua con le successive; a
  fine input i giorni rimasti restano tutti presenti.

### Assunzioni

- Uno studente segnato due volte nello stesso giorno conta una volta sola.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `assente` | `int *` | Matrice in un solo blocco |
| `numero`, `letto` | `int` | Studente letto e risultato di `scanf` |
| `conta` | `int` | Assenze di uno studente o di un giorno |
| `peggiore`, `assenti_peggiore` | `int` | Giorno con più assenti |
| `finito` | `int` | Fine input |

### Algoritmo in linguaggio naturale

1. Leggere le dimensioni e allocare la matrice con `calloc`.
2. Per ogni giorno leggere i numeri fino a 0, segnando 1 nella cella dello
   studente; scartare i valori non validi.
3. Stampare la tabella con i totali per studente.
4. Trovare il giorno con più assenti e stamparlo; liberare la matrice.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Una settimana di 6 giorni

- **Input:** `5 6`, poi `2 4 0`, `0`, `1 2 3 9 0`, `2 x 4 0`, `2 0`,
  `2 5 0`
- **Output atteso:**
  ```
    studente 9 inesistente
    numero non valido

          123456  assenze
  stud  1 ..A...   1
  stud  2 A.AAAA   5  oltre il 25%
  stud  3 ..A...   1
  stud  4 A..A..   2  oltre il 25%
  stud  5 .....A   1
  Giorno con piu' assenti: 3 (3 su 5)
  ```

### Test 2 – Input incompleto

- **Input:** `2 3`, `1 0`, poi fine input
- **Output atteso:** studente 1 con `A..`, 1 assenza oltre il 25%;
  `Giorno con piu' assenti: 1 (1 su 2)`.
