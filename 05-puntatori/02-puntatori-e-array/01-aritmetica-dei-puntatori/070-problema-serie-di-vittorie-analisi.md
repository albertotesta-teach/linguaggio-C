# Analisi – 070-problema-serie-di-vittorie.c

## 1. Problema

I risultati di una squadra di pallavolo sono memorizzati giornata per
giornata come caratteri `V`, `P`, `S`. Si vogliono i punti in classifica
(3 per vittoria, 1 per pareggio) e la serie più lunga di vittorie
consecutive, con la prima e l'ultima giornata.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `risultati` | `char[15]` | V V P V V V S V V V V P S V V (un carattere per giornata, non è una stringa) |

### Output

- I risultati delle 15 giornate.
- I punti in classifica.
- La serie più lunga di vittorie con la prima e l'ultima giornata, oppure
  `Nessuna vittoria.`

### Vincoli

- L'array si scorre con un puntatore `p` fino a `fine` (escluso).
- `inizio_serie` punta alla prima vittoria della serie in corso ed è `NULL`
  quando non c'è una serie.
- Quando la serie si interrompe, la sua lunghezza è `p − inizio_serie`
  (con `p` sulla prima giornata non vinta).
- Una serie ancora aperta dopo l'ultima giornata si misura dopo il ciclo
  con `fine − inizio_serie`.
- La giornata si ricava come `migliore − inizio + 1`.
- A parità di lunghezza vale la serie più vecchia (confronto con `>`).

### Assunzioni

- Nell'array ci sono solo i caratteri `V`, `P`, `S`.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `inizio`, `fine` | `const char *` | Estremi dell'array |
| `p` | `const char *` | Giornata esaminata |
| `inizio_serie` | `const char *` | Prima giornata della serie in corso, `NULL` se non c'è |
| `migliore` | `const char *` | Inizio della serie più lunga, `NULL` se nessuna vittoria |
| `lunghezza_max`, `punti` | `int` | Lunghezza della serie migliore, punti |

### Algoritmo in linguaggio naturale

1. Per ogni giornata `p`:
   1. stampare il risultato;
   2. se è `V`: aggiungere 3 punti e, se non c'è una serie in corso, porre
      `inizio_serie = p`;
   3. altrimenti: aggiungere 1 punto se è `P`; se c'era una serie,
      confrontare `p − inizio_serie` con la migliore, aggiornarla e porre
      `inizio_serie = NULL`.
2. Se una serie è ancora aperta, confrontare `fine − inizio_serie` con la
   migliore.
3. Stampare punti e serie migliore (o `Nessuna vittoria.`).

## 3. Casi di test

### Test 1 – Risultati del sorgente

- **Cosa si verifica:** punti e serie che si interrompe.
- **Input:** nessuno.
- **Valori intermedi attesi:** 11 vittorie × 3 + 2 pareggi = 35; la serie
  dalle giornate 8-11 si interrompe con il pareggio della 12
  (`p − inizio_serie` = 11 − 7 = 4).
- **Output atteso:**
  ```
  === RISULTATI ===
    V V P V V V S V V V V P S V V 

  Punti in classifica: 35 in 15 giornate
  Serie piu' lunga: 4 vittorie consecutive, dalla giornata 8 alla 11
  ```

### Test 2 – Serie aperta all'ultima giornata

- **Cosa si verifica:** la serie che arriva alla fine viene misurata dopo
  il ciclo.
- **Procedura:** nel sorgente sostituire le giornate 12 e 13 (`P`, `S`) con
  `V`, `V`, ricompilare ed eseguire.
- **Output atteso:**
  ```
  Punti in classifica: 40 in 15 giornate
  Serie piu' lunga: 8 vittorie consecutive, dalla giornata 8 alla 15
  ```

### Test 3 – Nessuna vittoria

- **Procedura:** nel sorgente sostituire tutte le `V` con `S`, ricompilare
  ed eseguire.
- **Output atteso:**
  ```
  Punti in classifica: 2 in 15 giornate
  Nessuna vittoria.
  ```
