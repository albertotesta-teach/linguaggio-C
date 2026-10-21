# Analisi – 050-problema-prossimo-treno.c

## 1. Problema

Gli orari dei treni per il capoluogo sono in ordine crescente. Lo studente
pendolare inserisce l'ora attuale e il programma mostra il prossimo treno e
i due successivi con l'attesa in minuti; dopo l'ultimo treno indica il
primo del giorno dopo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `ore`, `minuti` | `int` | Ora attuale `hh:mm`; un testo che non è un orario (es. `q`) termina |
| `orari` | `int[9]` | Partenze in minuti dalla mezzanotte, crescenti (nel sorgente): 06:12, 06:47, 07:15, 07:40, 08:25, 12:05, 13:35, 17:50, 21:10 |

### Output

- `Dalle hh:mm:` seguito da al massimo 3 treni con l'attesa
  (`tra N min` o `in partenza`).
- Dopo l'ultimo treno: `nessun treno fino a domani, primo alle 06:12`.
- `Ora non valida.` per ore fuori da 0-23 o minuti fuori da 0-59.

### Vincoli

- `prossimo` restituisce un puntatore al primo orario non precedente
  all'ora attuale (`*p >= adesso`), oppure `NULL` se i treni sono finiti;
  con `NULL` non si scorre nulla.
- I treni da mostrare si scorrono con `q` da `p`; `p + 1` e `p + 2` possono
  essere oltre la fine dell'array, quindi il ciclo controlla sia
  `q < fine` sia `q < p + 3`.
- Un treno con orario uguale all'ora attuale è "in partenza".

### Assunzioni

- Gli orari sono già ordinati.
- Il primo treno del giorno dopo è uguale a quello di oggi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `fine` | `const int *` | Subito dopo l'ultimo orario |
| `p` | `const int *` | Prossimo treno, `NULL` se finiti |
| `q` | `const int *` | Scorre i treni da mostrare |
| `adesso` | `int` | Ora attuale in minuti |
| `MOSTRATI` | `#define` | 3 |

| Funzione | Compito |
|----------|---------|
| `prossimo(orari, n, adesso)` | Puntatore al primo orario non precedente all'ora attuale, `NULL` se nessuno |
| `stampa_orario(minuti)` | Stampa `hh:mm` |

### Algoritmo in linguaggio naturale

1. Finché si legge un orario `hh:mm`:
   1. se l'ora non è valida segnalarlo;
   2. altrimenti calcolare `adesso`, trovare `p = prossimo(...)`;
   3. se `p` è `NULL` stampare il primo treno del giorno dopo;
   4. altrimenti stampare al massimo 3 treni da `p`, fermandosi alla fine
      dell'array, con l'attesa.
2. Alla prima riga che non è un orario terminare.

## 3. Casi di test

Nell'output le ore inserite non compaiono (input da pipe).

### Test 1 – Ore del giorno

- **Input:** `7:20`, `18:00`, `22:15`, `7:40`, `25:10`, `q`
- **Output atteso:**
  ```
    Dalle 07:20:  07:40 (tra 20 min)  08:25 (tra 65 min)  12:05 (tra 285 min)
    Dalle 18:00:  21:10 (tra 190 min)
    Dalle 22:15: nessun treno fino a domani, primo alle 06:12
    Dalle 07:40:  07:40 (in partenza)  08:25 (tra 45 min)  12:05 (tra 265 min)
    Ora non valida.
  ```
