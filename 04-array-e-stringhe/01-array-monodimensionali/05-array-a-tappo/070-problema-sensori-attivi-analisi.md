# Analisi – 070-problema-sensori-attivi.c

## 1. Problema

Un sistema di monitoraggio registra solo i sensori attivi in due array paralleli
a tappo (ID e lettura). Il programma deve aggiungere sensori (rifiutando i
duplicati), rimuoverli per ID con shift, calcolare la media delle letture e
mantenere i due array sempre sincronizzati.

---

## 2. Analisi generale e struttura dati

| Variabile  | Tipo        | Dimensione | Motivazione                                              |
|------------|-------------|------------|----------------------------------------------------------|
| `id`       | `int[]`     | MAX (22)   | ID sensore; terminato da TAPPO (-1)                      |
| `letture`  | `double[]`  | MAX (22)   | Lettura in °C; posizione del tappo sincronizzata con `id`|
| `TAPPO`    | `#define`   | -1         | Sentinella: ID e letture sono sempre ≥ 0                 |
| `MAX`      | `#define`   | 22         | Capacità totale incluso il tappo                         |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Aggiunta con controllo duplicati

**a) Input** — Array `id`, `letture`, nuovi valori.
**b) Output** — Restituisce 1=OK, 0=pieno, -1=duplicato.

**c) Funzione coinvolta**
`aggiungi_sensore`: chiama `cerca_sensore` prima di aggiungere.
Se il sensore è già presente, restituisce -1 senza modificare l'array.

**d) Vincoli**
- La ricerca preventiva dei duplicati usa `cerca_sensore`, che riusa la
  logica già definita (nessuna duplicazione di codice).
- Il tappo va aggiornato in entrambi gli array nella stessa operazione.

**f) Algoritmo**
```
Se cerca_sensore(id, nuovo_id) != -1: return -1 (duplicato).
pos = conta_sensori(id).
Se pos + 1 >= MAX: return 0 (pieno).
id[pos] = nuovo_id; letture[pos] = lettura.
id[pos+1] = TAPPO; letture[pos+1] = TAPPO.
return 1.
```

---

### Caso d'uso 2 – Rimozione per ID con shift

**a) Input** — Array `id`, `letture`, intero `id_da_rimuovere`.
**b) Output** — Restituisce 1 (trovato e rimosso) o 0 (non trovato).

**c) Funzione coinvolta**
`rimuovi_sensore`: trova l'indice con `cerca_sensore`, poi sposta tutti gli
elementi successivi di una posizione a sinistra su entrambi gli array.

**d) Vincoli**
- Lo shift deve avvenire in parallelo su `id[]` e `letture[]`.
- Il ciclo fino a `i < len` copia anche il tappo nell'ultima iterazione.
- Se l'ID non esiste, l'array non viene modificato.

**f) Algoritmo**
```
idx = cerca_sensore(id, id_da_rimuovere).
Se idx == -1: return 0.
len = conta_sensori(id).
Per i da idx a len - 1:
  id[i] = id[i+1]; letture[i] = letture[i+1].
return 1.
```

---

### Caso d'uso 3 – Media delle letture

**a) Input** — Array `letture`, `id` (per sapere dove si ferma il tappo).
**b) Output** — `double`: media delle letture dei sensori attivi.

**d) Vincoli**
- Il ciclo si ferma al tappo di `id[]` (non di `letture[]`) per coerenza.
- Se non ci sono sensori (`n == 0`), la funzione restituisce 0.0 per
  evitare la divisione per zero.
