# Analisi – 050-problema-log-eventi.c

## 1. Problema

Un sistema registra codici di eventi in un array a tappo (tappo = 0). I codici
1xx sono INFO, 2xx WARNING, 3xx ERROR. Il programma deve mostrare il log con
le etichette, produrre statistiche per categoria e trovare l'ultimo evento
di un tipo specifico scorrendo l'array al contrario.

---

## 2. Analisi

### Input
Nessun input da tastiera: il log è inizializzato nel codice.

| Variabile    | Tipo    | Dimensione | Descrizione                                 |
|--------------|---------|------------|---------------------------------------------|
| `log_eventi` | `int[]` | `MAX` (25) | Codici degli eventi, terminati da `TAPPO` (0) |

### Output
- Il log: posizione, codice e categoria (INFO, WARNING, ERROR, oppure "???"
  per un codice fuori dalle tre categorie);
- il totale degli eventi e, per ogni categoria, numero e percentuale;
- la posizione e il codice dell'ultimo ERROR e dell'ultimo WARNING, oppure
  il messaggio che non ce ne sono;
- una valutazione finale: "Sistema OK" se non ci sono errori, "Attenzione"
  se gli errori sono meno del 20%, "CRITICO" altrimenti.

### Vincoli
- La categoria si ricava con la divisione intera `codice / 100`: 1 = INFO,
  2 = WARNING, 3 = ERROR, qualsiasi altro valore = sconosciuto
- Il tappo 0 non può essere un codice valido, perché i codici sono > 0
- L'ultimo evento di una categoria si cerca scorrendo **al contrario**, dalla
  posizione prima del tappo verso l'inizio, fermandosi al primo trovato con
  un flag (niente `break`)
- Gli eventi di categoria sconosciuta sono contati nel totale ma non in
  nessuna categoria: in quel caso le percentuali non sommano a 100
- La soglia critica è il 20% di errori: a esattamente il 20% il sistema è
  già CRITICO

### Assunzioni
- Il log non è vuoto (il totale è usato come divisore)

### Variabili di supporto

| Variabile | Tipo      | Descrizione                                   |
|-----------|-----------|-----------------------------------------------|
| `totale`, `n_info`, `n_warn`, `n_err` | `int` | Conteggi              |
| `idx`     | `int`     | Indice dell'ultimo evento trovato (-1 se nessuno) |
| `TAPPO`   | `#define` | 0                                             |
| `MAX`     | `#define` | 25                                            |

| Funzione | Descrizione |
|---|---|
| `int conta_eventi(const int log[])` | Indice del tappo |
| `int categoria(int codice)` | 1, 2, 3 oppure 0 se sconosciuta |
| `int conta_per_categoria(const int log[], int cat)` | Eventi di una categoria |
| `int ultimo_per_categoria(const int log[], int cat)` | Indice dell'ultimo evento, -1 se assente |
| `void stampa_log(const int log[])` | Log con etichette |

### Algoritmo in linguaggio naturale
1. Stampare il log scorrendo fino al tappo, con l'etichetta della categoria.
2. Contare il totale e gli eventi di ogni categoria; stampare numeri e
   percentuali.
3. Per ERROR e WARNING: partire dall'ultimo evento e scorrere all'indietro
   fino a trovare un evento della categoria o fino all'inizio; stampare il
   risultato.
4. Se non ci sono errori stampare "Sistema OK"; altrimenti, se gli errori
   sono meno del 20% del totale stampare un avviso, altrimenti "CRITICO".

---

## 3. Casi di test

Il log è fisso nel codice: i test 2 e 3 richiedono di modificarlo e
ricompilare.

### Test 1 – Log con errori oltre la soglia
- **Input:** 101, 102, 201, 103, 301, 202, 104, 302, 105, 203, 303, 106
- **Output atteso:**
```
Totale eventi : 12
INFO          : 6  (50%)
WARNING       : 3  (25%)
ERROR         : 3  (25%)

Ultimo ERROR  : posizione 11, codice 303
Ultimo WARNING: posizione 10, codice 203

CRITICO: errori superiori al 20% del log.
```

### Test 2 – Errori sotto la soglia
- **Cosa si verifica:** il ramo "Attenzione"
- **Input:** 101, 102, 201, 103, 104, 202, 105, 107, 108, 203, 301, 109
- **Output atteso:** `ERROR         : 1  (8%)`,
  `Ultimo ERROR  : posizione 11, codice 301`,
  `Attenzione: 1 errori presenti (8% del totale).`

### Test 3 – Nessun errore e codice sconosciuto
- **Cosa si verifica:** la ricerca senza risultato, il ramo "Sistema OK" e un
  codice fuori categoria
- **Input:** 101, 102, 201, 103, 450, 202, 104, 107, 105, 203, 108, 106
- **Output atteso:** la riga `5  |  450   | ???`; INFO 8 (67%), WARNING 3
  (25%), ERROR 0 (0%); `Nessun ERROR nel log.` e
  `Sistema OK: nessun errore nel log.`
