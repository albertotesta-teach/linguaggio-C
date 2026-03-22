# Analisi – 060-problema-coda-prenotazioni.c

## 1. Problema

Uno studio medico gestisce le prenotazioni come due array paralleli a tappo:
ID paziente e orario in minuti. Il programma deve aggiungere prenotazioni in
fondo alla coda, rimuovere la prima (logica FIFO) e stampare la coda corrente
con orari in formato HH:MM.

---

## 2. Analisi generale e struttura dati

Il punto chiave è la **sincronizzazione dei tappi**: entrambi gli array
paralleli hanno il tappo nella stessa posizione; ogni operazione deve
aggiornare il tappo in entrambi gli array contemporaneamente.

| Variabile       | Tipo    | Dimensione | Motivazione                                             |
|-----------------|---------|------------|---------------------------------------------------------|
| `id_pazienti`   | `int[]` | MAX (12)   | ID paziente; terminato da TAPPO (-1)                    |
| `orari_visita`  | `int[]` | MAX (12)   | Orario in minuti; terminato da TAPPO (-1)               |
| `TAPPO`         | `#define`| -1        | Sentinella: gli ID e gli orari sono sempre ≥ 0          |
| `MAX`           | `#define`| 12        | Capacità totale incluso il tappo                        |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Aggiunta in fondo

**a) Input** — Array `id`, `orari`, nuovi valori `nuovo_id`, `nuovo_orario`.
**b) Output** — Restituisce 1 (OK) o 0 (coda piena).

**c) Vincoli**
- Il tappo deve essere aggiornato in entrambi gli array nello stesso punto.
- La condizione `pos + 1 < MAX` garantisce spazio per elemento + tappo.

**f) Algoritmo**
```
pos = conta(id).
Se pos + 1 < MAX:
  id[pos] = nuovo_id; orari[pos] = nuovo_orario.
  id[pos+1] = TAPPO; orari[pos+1] = TAPPO.
  return 1.
Altrimenti: return 0.
```

---

### Caso d'uso 2 – Rimozione della testa (FIFO)

**a) Input** — Array `id`, `orari`.
**b) Output** — Restituisce 1 (OK) o 0 (coda vuota).

**c) Vincoli**
- Lo shift deve avvenire su entrambi gli array in parallelo.
- Il ciclo arriva fino a `i < len` (non `i <= len`): il tappo viene copiato
  da `id[i+1]` a `id[i]` nell'ultima iterazione quando `i = len - 1`,
  poiché `id[len] == TAPPO`.
- Se la coda è vuota (`len == 0`), l'operazione viene rifiutata.

**f) Algoritmo**
```
len = conta(id).
Se len > 0:
  Per i da 0 a len - 1:
    id[i] = id[i+1]; orari[i] = orari[i+1].
  return 1.
Altrimenti: return 0.
```

---

### Caso d'uso 3 – Stampa con orario HH:MM

**a) Input** — Array `id`, `orari`.
**b) Output**
```
  Pos. | ID paz. | Orario
  -----|---------|-------
     1  |   2387  | 09:30
     2  |   1905  | 10:00
  ...
```
**d) Vincoli**
- Conversione: `ore = orari[i] / 60`, `minuti = orari[i] % 60`.
- Il formato `%02d` garantisce due cifre (es. `09:30` non `9:30`).
- Se la coda è vuota (`id[0] == TAPPO`), si stampa un messaggio esplicito.
