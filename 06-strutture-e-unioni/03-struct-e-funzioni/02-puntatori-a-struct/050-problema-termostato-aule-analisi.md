# Analisi – 050-problema-termostato-aule.c

## 1. Problema

Ogni aula ha un termostato che riceve una misura ogni 15 minuti e accende
o spegne il termosifone con un'isteresi di mezzo grado. La stessa funzione
`aggiorna` lavora sui termostati di due aule ricevendone l'indirizzo;
`riepilogo` li legge tramite `const Termostato *`.

## 2. Analisi

### Input

Nessun input da tastiera: i dati sono nel sorgente.

| Termostato | Obiettivo | Misure dalle 8:00 alle 9:45 |
|------------|-----------|------------------------------|
| A1-12 | 20.0 | 17.8, 18.6, 19.4, 20.1, 20.6, 20.2, 19.6, 19.3 |
| Lab-B | 19.0 | 18.9, 18.7, 18.4, 18.8, 19.3, 19.6, 19.1, 18.6 |

### Output

- Una tabella con l'ora e, per ogni aula, la misura e lo stato
  (`acceso`/`spento`).
- Per ogni aula: obiettivo, minima, massima e numero di accensioni.

### Vincoli

- Il termosifone si accende se è spento e la misura è sotto
  obiettivo − 0.5; si spegne se è acceso e la misura è sopra
  obiettivo + 0.5; altrimenti resta com'è.
- Minima e massima partono da 100 e −100, così la prima misura le
  aggiorna.
- `aggiorna` modifica la struct del chiamante tramite il puntatore;
  `riepilogo` non può modificarla (`const`).

### Assunzioni

- All'inizio i termosifoni sono spenti.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Termostato` | `typedef struct { char aula[8]; double obiettivo; double ultima; double minima; double massima; int acceso; int accensioni; } Termostato;` | Stato del termostato di un'aula |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `a12`, `lab` | `Termostato` | I due termostati |
| `misure_a12`, `misure_lab` | `double[8]` | Misure della mattina |
| `m` | `int` | Indice della misura (ora = 8 + m / 4, minuti = m % 4 × 15) |
| `ISTERESI` | `#define` | 0.5 gradi |

| Funzione | Compito |
|----------|---------|
| `aggiorna(t, misura)` | Registra la misura, aggiorna minima e massima, decide lo stato |
| `riepilogo(t)` | Stampa il riepilogo del termostato |

### Algoritmo in linguaggio naturale

1. Stampare l'intestazione.
2. Per ogni misura: chiamare `aggiorna(&a12, ...)` e `aggiorna(&lab, ...)`
   e stampare l'ora con misure e stati.
3. Stampare il riepilogo delle due aule.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** isteresi (A1-12 a 20.1 resta acceso, si spegne a
  20.6, si riaccende a 19.3), minima, massima, accensioni.
- **Input:** nessuno.
- **Output atteso:**
  ```
    Ora    A1-12          Lab-B         
    08:00  17.8 acceso    18.9 spento   
    08:15  18.6 acceso    18.7 spento   
    08:30  19.4 acceso    18.4 acceso   
    08:45  20.1 acceso    18.8 acceso   
    09:00  20.6 spento    19.3 acceso   
    09:15  20.2 spento    19.6 spento   
    09:30  19.6 spento    19.1 spento   
    09:45  19.3 acceso    18.6 spento   

    A1-12: obiettivo 20.0, minima 17.8, massima 20.6, accensioni 2
    Lab-B: obiettivo 19.0, minima 18.4, massima 19.6, accensioni 1
  ```

### Test 2 – Termosifone mai acceso

- **Procedura:** portare l'obiettivo di Lab-B a 18.0.
- **Output atteso:** Lab-B sempre `spento` e
  `Lab-B: obiettivo 18.0, minima 18.4, massima 19.6, accensioni 0`.
