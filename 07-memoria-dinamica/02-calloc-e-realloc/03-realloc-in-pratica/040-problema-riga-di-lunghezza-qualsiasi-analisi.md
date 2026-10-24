# Analisi – 040-problema-riga-di-lunghezza-qualsiasi.c

## 1. Problema

Le risposte aperte del questionario di fine anno possono essere lunghe un
paragrafo. La funzione `leggi_riga` legge un carattere alla volta con
`getchar` in un blocco che parte da 16 byte e cresce di 16 quando è
pieno, poi riduce il blocco alla lunghezza esatta. Il programma conserva
le risposte in un array di puntatori e stampa un'anteprima di ognuna e la
più lunga per intero.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| risposte | righe di qualsiasi lunghezza | `FINE` termina, le righe vuote si ignorano |

### Output

- Per ogni risposta: `L caratteri, ingrandimenti del blocco: K`.
- `Risposte raccolte: N` e per ognuna lunghezza e anteprima di 30
  caratteri (con `...` se più lunga).
- `La piu' lunga per intero:` e il testo.

### Vincoli

- Blocco iniziale `malloc(PASSO * sizeof *testo)` con PASSO = 16; quando
  resta solo il posto del terminatore, `realloc` di altri 16 byte in un
  temporaneo; alla fine `realloc` alla lunghezza esatta + 1.
- Se un'allocazione fallisce, `leggi_riga` libera il blocco e restituisce
  `NULL` (come a fine input).
- Al massimo 10 risposte; tutte liberate alla fine.
- A parità vale la prima risposta più lunga.

### Assunzioni

- Nessuna: non c'è un limite alla lunghezza della riga.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `risposte` | `char *[10]` | Risposte raccolte |
| `riga` | `char *` | Blocco restituito da `leggi_riga` |
| `ingrandimenti` | `int` | Quante volte il blocco è cresciuto |
| `piu_lunga` | `int` | Indice della risposta più lunga |
| `capienza`, `lunghezza` (in `leggi_riga`) | `int` | Stato del blocco |

| Funzione | Compito |
|----------|---------|
| `leggi_riga(&ingrandimenti)` | Legge una riga intera in un blocco della lunghezza giusta; `NULL` a fine input |

### Algoritmo in linguaggio naturale

1. Finché non si termina: leggere una riga; a fine input o con `FINE`
   terminare (liberando la riga); ignorare le vuote; altrimenti stamparne
   lunghezza e ingrandimenti e memorizzarla.
2. Stampare le anteprime e la più lunga; liberare tutte le risposte.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Risposte di lunghezze diverse

- **Input:** `Mi e piaciuto il laboratorio.`, riga vuota,
  `Vorrei piu ore di informatica e meno compiti a casa durante le vacanze di Natale.`,
  `Ok`, `FINE`
- **Valori intermedi attesi:** 29 caratteri + terminatore superano i 16
  byte iniziali: un ingrandimento (32 byte); 81 caratteri: cinque
  ingrandimenti (96 byte).
- **Output atteso:**
  ```
  Risposte (FINE per terminare):
    29 caratteri, ingrandimenti del blocco: 1
    81 caratteri, ingrandimenti del blocco: 5
    2 caratteri, ingrandimenti del blocco: 0

  Risposte raccolte: 3
    1. ( 29) Mi e piaciuto il laboratorio.
    2. ( 81) Vorrei piu ore di informatica ...
    3. (  2) Ok
  La piu' lunga per intero:
    Vorrei piu ore di informatica e meno compiti a casa durante le vacanze di Natale.
  ```
