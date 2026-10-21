# Analisi – 060-problema-primo-giorno-di-gelo.c

## 1. Problema

Un'azienda agricola conserva le temperature minime dei 30 giorni di
novembre. Per un periodo scelto dall'utente (dal giorno `a` al giorno `b`)
il programma indica la minima più bassa, il primo giorno sotto zero e il
numero di giorni di gelo. Con `0 0` termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `a`, `b` | `int` | Primo e ultimo giorno del periodo, letti da tastiera; `0 0` per finire |
| `minime` | `int[30]` | Minima di ogni giorno (nel sorgente); il giorno 1 ha indice 0 |

### Output

- Per un periodo valido: giorni del periodo, numero di giorni e minima più
  bassa; poi il primo giorno di gelo con la sua temperatura e il numero di
  giorni di gelo, oppure `Nessun giorno di gelo.`
- Per un periodo non valido: `Periodo non valido: servono 1 <= a <= b <= 30.`

### Vincoli

- Il periodo è un sottoarray: inizia a `minime + a − 1` e contiene
  `n = b − a + 1` elementi; le funzioni ricevono puntatore iniziale e
  numero di elementi e non escono mai dal sottoarray.
- La posizione restituita da `primo_sotto_zero` è relativa al periodo: il
  giorno di novembre è `a + posizione`.
- Il periodo deve rispettare 1 ≤ a ≤ b ≤ 30, altrimenti il sottoarray
  uscirebbe dall'array.
- Gelo significa temperatura negativa: 0 gradi non è gelo.
- Un input che non contiene due numeri è un periodo non valido (la riga si
  scarta); a fine input il programma termina come con `0 0`.

### Assunzioni

- Con `a` = 0 il programma termina qualunque sia `b`.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `inizio` | `const int *` | `minime + a − 1`, inizio del sottoarray |
| `n` | `int` | `b − a + 1`, giorni del periodo |
| `primo` | `int` | Posizione del primo gelo nel periodo, -1 se nessuno |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `primo_sotto_zero(t, n)` | Posizione della prima temperatura negativa, -1 se non c'è |
| `conta_sotto_zero(t, n)` | Numero di temperature negative |
| `minima(t, n)` | Temperatura più bassa |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché `a` è diverso da 0:
   1. leggere `a` e `b` (a fine input porre `a = 0`; se non sono due numeri
      scartare la riga e considerare il periodo non valido);
   2. se `a` è 0 terminare;
   3. se il periodo non è valido segnalarlo;
   4. altrimenti calcolare `inizio` e `n`, stampare la minima più bassa e il
      primo gelo (giorno `a + primo`) con il numero di giorni di gelo, oppure
      che non ci sono gelate.

## 3. Casi di test

Nell'output i periodi inseriti non compaiono (input da pipe).

### Test 1 – Periodo con gelo

- **Input:** `20 25`
- **Valori intermedi attesi:** `inizio` = `minime + 19`, `n` = 6;
  `primo_sotto_zero` restituisce 3 → giorno 20 + 3 = 23.
- **Output atteso:**
  ```
    Giorni 20-25 (6 giorni), minima piu' bassa -5 gradi
    Primo gelo: giorno 23 (-1 gradi), giorni di gelo: 3
  ```

### Test 2 – Periodo senza gelo

- **Cosa si verifica:** 0 gradi non è gelo.
- **Input:** `1 10`
- **Output atteso:**
  ```
    Giorni 1-10 (10 giorni), minima piu' bassa 0 gradi
    Nessun giorno di gelo.
  ```

### Test 3 – Periodo di un solo giorno

- **Input:** `30 30`
- **Output atteso:**
  ```
    Giorni 30-30 (1 giorno), minima piu' bassa -3 gradi
    Primo gelo: giorno 30 (-3 gradi), giorni di gelo: 1
  ```

### Test 4 – Periodi non validi e fine

- **Input:** `25 20`, `xx`, `0 0`
- **Output atteso:** due volte
  `  Periodo non valido: servono 1 <= a <= b <= 30.`, poi il programma
  termina.
