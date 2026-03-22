# Analisi – 040-problema-lista-della-spesa.c

## 1. Problema

Un'applicazione gestisce una lista della spesa come array di prezzi in centesimi
terminato da -1. Il programma deve calcolare il totale, contare gli articoli,
trovare il più caro e permettere di aggiungere nuovi articoli prima del tappo.

---

## 2. Analisi generale e struttura dati

Il punto chiave è che la "lunghezza" della lista non è memorizzata esplicitamente:
si ricava ogni volta scorrendo fino al tappo. Aggiungere un articolo significa
scrivere nella posizione del tappo e spostare il tappo di una posizione in avanti.

| Variabile  | Tipo      | Dimensione | Motivazione                                              |
|------------|-----------|------------|----------------------------------------------------------|
| `lista`    | `int[]`   | MAX (20)   | Prezzi in centesimi; terminata da TAPPO (-1)             |
| `TAPPO`    | `#define` | -1         | Sentinella: -1 è illegale come prezzo (i prezzi sono ≥ 0)|
| `MAX`      | `#define` | 20         | Capacità totale incluso il tappo                         |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Statistiche sulla lista

**a) Input** — Array `lista` a tappo.
**b) Output**
```
Articoli     : 5
Totale       : 11,86 euro
Articolo piu' caro: n.4 (4,50 euro)
```
**c) Funzioni coinvolte**
- `conta_articoli`: conta gli elementi prima del tappo.
- `totale`: accumulatore con ciclo `while (prezzi[i] != TAPPO)`.
- `indice_piu_caro`: pattern "ipotesi + smentita" con ciclo a tappo.

**d) Vincoli**
- I prezzi sono in centesimi (interi non negativi): -1 è sicuro come tappo.
- La stampa converte centesimi in euro con `/ 100` e `% 100`.

**f) Algoritmo — `conta_articoli`**
```
i = 0.
Mentre lista[i] != TAPPO: i++.
return i.
```

---

### Caso d'uso 2 – Aggiunta di un articolo

**a) Input** — Array `lista`, intero `prezzo_centesimi`.
**b) Output** — Restituisce 1 (OK) o 0 (lista piena).

**c) Funzione coinvolta**
`aggiungi`: trova la posizione del tappo con `conta_articoli`, verifica che ci
sia spazio (`pos + 1 < MAX`), scrive il nuovo valore e sposta il tappo.

**d) Vincoli**
- Dopo l'inserimento il tappo si trova in `pos + 1`: questa posizione deve
  essere `< MAX` per non uscire dai limiti dell'array.
- La condizione `pos + 1 < MAX` (non `pos < MAX`) garantisce spazio
  sia per il nuovo elemento che per il tappo.

**f) Algoritmo**
```
pos = conta_articoli(lista).
Se pos + 1 < MAX:
  lista[pos] = prezzo_centesimi.
  lista[pos + 1] = TAPPO.
  return 1.
Altrimenti: return 0.
```
