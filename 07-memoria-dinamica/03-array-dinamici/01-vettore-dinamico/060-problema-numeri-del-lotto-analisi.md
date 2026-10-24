# Analisi – 060-problema-numeri-del-lotto.c

## 1. Problema

La classe raccoglie le estrazioni di una ruota del lotto (5 numeri diversi
da 1 a 90) per un'unità di statistica. Le estrazioni vanno in un vettore
dinamico di struct `Estrazione`. Alla fine si calcolano per ogni numero la
frequenza e il ritardo (estrazioni passate dall'ultima uscita, −1 se mai
uscito) e si stampano i 5 più frequenti e i 5 più in ritardo tra quelli
usciti, con il richiamo all'indipendenza delle estrazioni.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[80]` | Cinque numeri per riga; `FINE` termina |

### Output

- `estrazione non valida` per ogni riga scartata.
- `Estrazioni: N`.
- Se ci sono estrazioni: `Piu' frequenti:` e `Piu' in ritardo tra gli
  usciti:` con 5 numeri e il valore tra parentesi, e la frase
  sull'indipendenza.

### Vincoli

- Vettore `{Estrazione *dati; int n; int capacita;}` con capacità iniziale
  4 e raddoppio; il `main` usa solo le funzioni del vettore.
- Riga valida: esattamente cinque interi da 1 a 90, tutti diversi.
- Ritardo di un numero: n − 1 − indice dell'ultima estrazione in cui è
  uscito.
- Classifica: valore più alto, a parità il numero più piccolo; i numeri
  mai usciti (ritardo −1) sono esclusi.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input il programma termina come con `FINE`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Estrazione` | `typedef struct { int numeri[5]; } Estrazione;` | Un'estrazione |
| `Archivio` | `typedef struct { Estrazione *dati; int n; int capacita; } Archivio;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `archivio` | `Archivio *` | Le estrazioni |
| `frequenza`, `ritardo` | `int[91]` | Statistiche per numero |
| `riga`, `dopo`, `resto` | `char[80]`, `char`, `int` | Lettura della riga |

| Funzione | Compito |
|----------|---------|
| `crea_archivio`, `distruggi_archivio` | Allocazione e liberazione |
| `aggiungi`, `lunghezza`, `elemento` | Uso del vettore |
| `valida(e)` | Numeri nell'intervallo e diversi |
| `stampa_primi(titolo, valore)` | I 5 numeri con il valore più alto |

### Algoritmo in linguaggio naturale

1. Leggere le righe fino a `FINE`; aggiungere le estrazioni valide.
2. Inizializzare i ritardi a −1; scorrere le estrazioni aggiornando
   frequenza e ritardo di ogni numero.
3. Stampare il numero di estrazioni e, se ce ne sono, le due classifiche.
4. Distruggere l'archivio.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Quattro estrazioni valide

- **Input:** `12 45 67 3 90`, `45 12 8 77 21`, `3 45 60 61 62`, `1 2 3 4`,
  `5 6 7 8 99`, `10 10 11 12 13`, `1 2 3 4 5 6`, `33 34 35 36 37`, `FINE`
- **Output atteso:**
  ```
  Estrazioni (5 numeri, FINE per terminare):
    estrazione non valida
    estrazione non valida
    estrazione non valida
    estrazione non valida

  Estrazioni: 4
  Piu' frequenti:  45 (3)  3 (2)  12 (2)  8 (1)  21 (1)
  Piu' in ritardo tra gli usciti:  67 (3)  90 (3)  8 (2)  12 (2)  21 (2)
  Ogni estrazione e' indipendente: il ritardo non aumenta la probabilita'.
  ```
  (righe con quattro o sei numeri, un numero oltre 90 o ripetuto sono
  scartate).

### Test 2 – Nessuna estrazione

- **Input:** `FINE`
- **Output atteso:** `Estrazioni: 0`.
