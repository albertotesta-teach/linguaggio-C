# Analisi – 050-problema-ora-di-punta.c

## 1. Problema

Il contatore della scuola registra i kWh consumati in ognuna delle 24 ore.
Si vogliono il consumo totale, l'ora di punta (consumo massimo) e la fascia
di alto consumo, dalla prima all'ultima ora con consumo almeno pari all'80%
del massimo. I consumi si mostrano anche con un grafico a barre di `#`.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `consumi` | `int[24]` | 8, 8, 7, 7, 7, 8, 12, 25, 48, 62, 66, 70, 58, 52, 64, 61, 45, 30, 18, 14, 12, 10, 9, 8 kWh (l'indice è l'ora) |

### Output

- Il grafico: per ogni ora l'orario, il consumo e un `#` ogni 5 kWh, con
  `<- ora di punta` accanto al massimo.
- Il consumo totale.
- L'ora di punta e il suo consumo.
- La fascia di alto consumo: soglia, ora di inizio e di fine, numero di ore.

### Vincoli

- L'array si scorre con un puntatore `p` da `inizio` a `fine`
  (`fine = inizio + 24`, che non si dereferenzia).
- L'ora si ricava come differenza `p − inizio`, non da un indice salvato a
  parte.
- Soglia = 80% del massimo con la divisione intera (`*picco * 80 / 100`).
- La fascia va dalla prima all'ultima ora con consumo ≥ soglia e comprende
  le ore intermedie, anche se sotto soglia.
- Grafico: un `#` ogni 5 kWh, con la divisione intera.

### Assunzioni

- A parità di consumo massimo vale la prima ora (confronto con `>`).
- Esiste sempre almeno un'ora oltre soglia: l'ora di punta.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `inizio`, `fine` | `const int *` | Estremi dell'array |
| `p` | `const int *` | Puntatore di scorrimento |
| `picco` | `const int *` | Elemento con il consumo massimo |
| `prima`, `ultima` | `const int *` | Prima e ultima ora oltre la soglia |
| `soglia`, `totale` | `int` | 80% del massimo, somma dei consumi |
| `k` | `int` | Contatore dei `#` |

### Algoritmo in linguaggio naturale

1. Scorrere l'array: aggiornare `picco` se `*p > *picco` e sommare il totale.
2. Calcolare la soglia.
3. Scorrere di nuovo: per ogni ora con consumo ≥ soglia porre `ultima = p`
   e, se è la prima, `prima = p`.
4. Stampare il grafico, marcando l'elemento con `p == picco`.
5. Stampare totale, ora di punta (`picco − inizio`) e fascia di alto
   consumo (da `prima − inizio` a `ultima − inizio + 1`, durata
   `ultima − prima + 1` ore).

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** massimo 70 all'ora 11; soglia
  70 × 80 / 100 = 56; prima ora ≥ 56 = 9 (62), ultima = 15 (61).
- **Output atteso** (riepilogo):
  ```
  Consumo totale: 709 kWh
  Ora di punta: 11:00-12:00 con 70 kWh
  Alto consumo (almeno 56 kWh, 80% del massimo): dalle 09:00 alle 16:00, 7 ore
  ```

### Test 2 – Grafico a barre

- **Cosa si verifica:** un `#` ogni 5 kWh con la divisione intera.
- **Input:** nessuno.
- **Output atteso** (alcune righe):
  ```
    00:00   8 #
    09:00  62 ############
    11:00  70 ##############  <- ora di punta
    12:00  58 ###########
  ```

### Test 3 – Ore intermedie sotto soglia

- **Cosa si verifica:** la fascia comprende le 12 e le 13 (58 e 52 kWh),
  anche se 52 è sotto la soglia di 56.
- **Input:** nessuno.
- **Output atteso:** fascia dalle 09:00 alle 16:00, 7 ore.
