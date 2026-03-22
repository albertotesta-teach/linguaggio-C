# Analisi – 080-problema-playlist-musicale.c

## 1. Problema

Una playlist gestisce fino a 15 brani con ID e durata in secondi in array
paralleli a tappo. Il programma deve calcolare la durata totale, trovare il
brano più lungo, inserire un brano in una posizione specifica (spostando gli
altri in avanti) e rimuovere un brano per ID (spostando gli altri indietro).

---

## 2. Analisi generale e struttura dati

Il punto tecnico più rilevante è l'**inserimento in posizione intermedia**:
per fare spazio al nuovo elemento si parte dal fondo e si sposta ogni elemento
di una posizione in avanti, includendo il tappo, poi si scrive il nuovo valore
nella posizione liberata.

| Variabile  | Tipo    | Dimensione | Motivazione                                              |
|------------|---------|------------|----------------------------------------------------------|
| `id`       | `int[]` | MAX (18)   | ID brano; terminato da TAPPO (-1)                        |
| `durate`   | `int[]` | MAX (18)   | Durata in secondi; sincronizzato con `id`                |
| `TAPPO`    | `#define`| -1        | Sentinella: ID e durate sono sempre ≥ 0                  |
| `MAX`      | `#define`| 18        | Capacità totale incluso tappo e margine                  |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Inserimento in posizione intermedia

**a) Input** — Array `id`, `durate`, intero `pos`, nuovo ID e durata.
**b) Output** — Restituisce 1=OK, 0=pieno, -1=posizione non valida.

**c) Funzione coinvolta**
`inserisci_in_posizione`: shift in avanti da `i = len` fino a `i = pos`,
poi scrittura del nuovo elemento in `pos`.

**d) Vincoli**
- Il range valido di `pos` è [0, len] (incluso `len` = inserimento in fondo).
- Lo shift parte dal tappo (`i = len`) e procede indietro fino a `i = pos`.
  Questo garantisce che ogni elemento venga spostato prima di essere sovrascritto.
- Il tappo viene spostato nello shift: quando `i = len`, `id[len+1] = id[len] = TAPPO`.
- `len + 1 >= MAX` controlla che ci sia posto per l'elemento e il tappo.
- Lo shift avviene in parallelo su entrambi gli array.

**e) Assunzioni**
- Non ci sono duplicati: la funzione non controlla l'ID già esistente.

**f) Algoritmo**
```
len = conta_brani(id).
Se pos < 0 o pos > len: return -1.
Se len + 1 >= MAX: return 0.
Per i da len a pos (incluso), decrescente:
  id[i+1] = id[i]; durate[i+1] = durate[i].
id[pos] = nuovo_id; durate[pos] = nuova_durata.
return 1.
```

---

### Caso d'uso 2 – Rimozione per ID

**a) Input** — Array `id`, `durate`, intero `id_da_rimuovere`.
**b) Output** — Restituisce 1 (trovato e rimosso) o 0 (non trovato).

**c) Funzione coinvolta**
`rimuovi_per_id`: trova l'indice con `cerca_brano`, poi shift all'indietro
da `idx` fino a `len - 1`, copiando anche il tappo nell'ultima iterazione.

**d) Vincoli**
- Lo shift all'indietro è l'opposto dell'inserimento: si parte dall'elemento
  da rimuovere e si copia ogni elemento dalla posizione successiva.
- Il ciclo fino a `i < len` (non `i <= len`) copia il tappo perché
  `id[len] = TAPPO` viene copiato in `id[len-1]` quando `i = len - 1`.

**f) Algoritmo**
```
idx = cerca_brano(id, id_da_rimuovere).
Se idx == -1: return 0.
len = conta_brani(id).
Per i da idx a len - 1:
  id[i] = id[i+1]; durate[i] = durate[i+1].
return 1.
```

---

### Caso d'uso 3 – Durata totale e brano più lungo

**a) Input** — Array `id`, `durate`.
**b) Output**
```
  Durata totale: 18:24
  Brano piu' lungo: ID 1003 (245 secondi)
```
**d) Vincoli**
- `durata_totale` riceve anche `id[]` per sapere dove si ferma il tappo.
- `brano_piu_lungo` restituisce l'indice; il `main` accede poi a `id[idx]` e `durate[idx]`.
- Conversione: `minuti = secondi / 60`, `sec_resto = secondi % 60`.
