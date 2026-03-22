# Analisi – 050-problema-log-eventi.c

## 1. Problema

Un sistema registra codici di eventi in un array a tappo (tappo = 0). I codici
1xx sono INFO, 2xx WARNING, 3xx ERROR. Il programma deve mostrare il log con
le etichette, produrre statistiche per categoria e trovare l'ultimo evento
di un tipo specifico scorrendo l'array al contrario.

---

## 2. Analisi generale e struttura dati

| Variabile    | Tipo      | Dimensione | Motivazione                                              |
|--------------|-----------|------------|----------------------------------------------------------|
| `log_eventi` | `int[]`   | MAX (25)   | Codici eventi > 0; terminato da TAPPO (0)                |
| `TAPPO`      | `#define` | 0          | Sentinella: 0 è illegale come codice (i codici sono > 0) |
| `MAX`        | `#define` | 25         | Capacità totale incluso il tappo                         |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Classificazione per categoria

**a) Input** — Array `log_eventi`.
**b) Output**
```
Totale eventi : 12
INFO          : 6  (50%)
WARNING       : 3  (25%)
ERROR         : 3  (25%)
```
**c) Funzioni coinvolte**
- `categoria(codice)`: restituisce `codice / 100` se in [1,3], altrimenti 0.
  La divisione intera per 100 classifica automaticamente: 101/100=1, 250/100=2, 305/100=3.
- `conta_per_categoria`: scorre il log chiamando `categoria()` per ogni evento.

**d) Vincoli**
- `categoria()` restituisce 0 per codici fuori range [100, 399]: gestito con `if`.
- Le percentuali usano divisione floating point.

**f) Algoritmo — `categoria`**
```
cat = codice / 100.
Se cat in [1, 3]: return cat.
Altrimenti: return 0.
```

---

### Caso d'uso 2 – Ultimo evento per categoria

**a) Input** — Array `log_eventi`, intero `cat`.
**b) Output**
```
Ultimo ERROR  : posizione 11, codice 303
Ultimo WARNING: posizione 10, codice 203
```
**c) Funzione coinvolta**
`ultimo_per_categoria`: trova prima la posizione dell'ultimo elemento valido
(`conta_eventi() - 1`), poi scorre all'indietro con `i--` finché non trova
un evento della categoria cercata o arriva a `i = 0`.

**d) Vincoli**
- Il ciclo parte dall'ultimo elemento valido (`fine`), non dal tappo.
- Usa `i >= 0 && !trovato` come condizione: nessun `break`.
- Restituisce -1 come sentinella se nessun evento della categoria è presente.

**f) Algoritmo**
```
fine = conta_eventi(log) - 1.
i = fine, trovato = 0, risultato = -1.
Mentre i >= 0 && !trovato:
  Se categoria(log[i]) == cat: trovato = 1, risultato = i.
  i--.
return risultato.
```

---

### Caso d'uso 3 – Valutazione stato del sistema

**a) Input** — Contatori `n_err`, `totale`.
**b) Output**
```
Attenzione: 3 errori presenti (25% del totale).
```
**d) Vincoli**
- Tre livelli: nessun errore → OK; errori < 20% → ATTENZIONE; errori ≥ 20% → CRITICO.
- Il confronto `(double)n_err / totale < 0.20` evita la divisione intera.
