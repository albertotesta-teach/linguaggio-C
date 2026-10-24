# Analisi – 080-problema-confronto-di-due-file.c

## 1. Problema

Il docente vuole verificare che nessuno abbia modificato il file di dati
consegnato. Il programma apre due file insieme e li legge in parallelo, un
carattere da ciascuno, tenendo il conto di riga e colonna. Si ferma alla
prima differenza o alla fine dei file e dice se sono identici, se uno è
più corto o dove differiscono.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nome_primo`, `nome_secondo` | testo | Nomi dei due file, senza spazi, fino a 59 caratteri |
| i due file | file di testo | Contenuti da confrontare |

### Output

- `I file sono identici. Righe confrontate: R`.
- Oppure `Prima differenza alla riga R, colonna C:` seguito, per ogni
  file, dal nome (in 20 colonne) e dal carattere trovato: `'x'`,
  `a capo` o `fine del file` (il file più corto).
- Su `stderr`: `Impossibile leggere il primo file` o
  `Impossibile leggere SECONDO`.

### Vincoli

- I due file sono aperti contemporaneamente in `"r"`; se il secondo non si
  apre, il primo si chiude subito.
- Il ciclo avanza finché i due caratteri sono uguali e diversi da `EOF`:
  alla fine `a == b` vuol dire che entrambi i file sono finiti insieme.
- Riga e colonna partono da 1; dopo un a capo la riga aumenta e la colonna
  torna a 1.
- Le righe confrontate contano anche l'ultima riga senza a capo.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `primo`, `secondo` | `FILE *` | I due file; `NULL` se non aperti |
| `a`, `b` | `int` | Carattere corrente di ciascun file, può valere `EOF` |
| `riga`, `colonna` | `int` | Posizione del carattere corrente |

| Funzione | Compito |
|----------|---------|
| `descrivi(c)` | Stampa il carattere in forma leggibile |

### Algoritmo in linguaggio naturale

1. Leggere i due nomi e aprire i file; se uno non si apre, segnalarlo e
   chiudere l'altro.
2. Leggere un carattere da ciascun file finché sono uguali e non è finito
   il file, aggiornando riga e colonna.
3. Chiudere i due file.
4. Se i caratteri finali sono uguali (entrambi `EOF`) i file sono
   identici: stampare le righe confrontate. Altrimenti stampare la
   posizione e i due caratteri diversi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si usano i file
prodotti da `040`, `050` e `060`.

### Test 1 – Il diario e la sua copia

- **Input:** `diario.txt`, `diario-copia.txt`
- **Output atteso:**
  ```
  Primo file: Secondo file: I file sono identici. Righe confrontate: 3
  ```

### Test 2 – Due file diversi

- **Input:** `diario.txt`, `presenze-16-10.txt`
- **Output atteso:**
  ```
  Primo file: Secondo file: Prima differenza alla riga 1, colonna 1:
    diario.txt           '1'
    presenze-16-10.txt   'a'
  ```

### Test 3 – Un file più corto

- **Input:** `corto.txt` (`riga uno` e a capo), `senza-a-capo.txt`
- **Output atteso:**
  ```
  Primo file: Secondo file: Prima differenza alla riga 2, colonna 1:
    corto.txt            fine del file
    senza-a-capo.txt     'r'
  ```

### Test 4 – Ultima riga senza a capo

- **Input:** `senza-a-capo.txt`, `copia2.txt` (la sua copia fatta da `050`)
- **Output atteso:** `I file sono identici. Righe confrontate: 2`

### Test 5 – File mancanti

- **Input:** `nessuno.txt`, `corto.txt`; poi `corto.txt`, `nessuno.txt`
- **Output atteso:** `Impossibile leggere il primo file`; poi
  `Impossibile leggere nessuno.txt` (su `stderr`).
