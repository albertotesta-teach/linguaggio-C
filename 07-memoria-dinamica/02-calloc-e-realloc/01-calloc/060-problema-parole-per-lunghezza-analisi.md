# Analisi – 060-problema-parole-per-lunghezza.c

## 1. Problema

Per valutare la leggibilità di un testo il programma conta le parole per
lunghezza. L'insegnante sceglie la lunghezza massima da distinguere:
`calloc` alloca massimo + 1 contatori e le parole più lunghe finiscono
nell'ultimo. Alla fine stampa la distribuzione con le percentuali, la
lunghezza media e la parola più lunga.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `massimo` | `int` | Lunghezza massima distinta, da 2 a 30 |
| testo | righe | Testo; `FINE` da solo su una riga termina |

### Output

- `Parole: N`.
- Per ogni lunghezza presente: `L lettere: K (P%)`, con `+` sull'ultima
  (lunghezza massima o più).
- `Lunghezza media: M lettere` e `Parola piu' lunga: ...` se ci sono
  parole.
- `Valore non valido.`, `Memoria insufficiente.`

### Vincoli

- `conta = calloc(massimo + 1, sizeof *conta)`: indice = lunghezza, con
  le parole più lunghe nell'ultimo contatore; l'indice 0 non si usa.
- Una parola è una sequenza di lettere: cifre, apostrofi e punteggiatura
  la separano.
- A parità di lunghezza resta la prima parola più lunga trovata.
- A fine input il conteggio termina come con `FINE`.

### Assunzioni

- Righe al massimo di 199 caratteri; testo senza lettere accentate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `conta` | `int *` | Contatori per lunghezza |
| `riga` | `char[200]` | Riga letta |
| `parole`, `lettere_totali` | `int` | Per la media |
| `piu_lunga` | `char[40]` | Parola più lunga |
| `inizio`, `lunghezza` | `int` | Posizione e lunghezza della parola corrente |

### Algoritmo in linguaggio naturale

1. Leggere il massimo, allocare i contatori, scartare il resto della riga.
2. Per ogni riga fino a `FINE`: scorrere i caratteri; a ogni sequenza di
   lettere contare la parola nel contatore della sua lunghezza (o
   nell'ultimo) e aggiornare totale e parola più lunga.
3. Stampare la distribuzione, la media e la parola più lunga; liberare i
   contatori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Due frasi

- **Input:** `4`, `Il gatto dorme sul divano rosso.`,
  `La professoressa spiega la fotosintesi!`, `FINE`
- **Valori intermedi attesi:** 11 parole, 60 lettere; tre di 2 lettere,
  una di 3, sette di 4 o più.
- **Output atteso:**
  ```
  Testo (FINE per terminare):

  Parole: 11
     2  lettere:   3  (27.3%)
     3  lettere:   1  ( 9.1%)
     4+ lettere:   7  (63.6%)
  Lunghezza media: 5.5 lettere
  Parola piu' lunga: professoressa
  ```

### Test 2 – Testo vuoto

- **Input:** `5`, `FINE`
- **Output atteso:** `Parole: 0` e nient'altro.
