# Analisi – 040-problema-lancio-dado.c

## 1. Problema

Un gioco da tavolo vuole verificare statisticamente l'equilibrio di un dado
a sei facce. Il programma legge 30 lanci da tastiera, conta le uscite di
ciascuna faccia, visualizza la distribuzione con un istogramma testuale e
identifica la faccia più e meno frequente.

---

## 2. Analisi generale e struttura dati

Il punto chiave del problema è l'uso di **un solo array come tabella di
frequenze**: il valore letto (1–6) viene trasformato direttamente in un indice
(`lancio - 1`), così ogni cella conta le uscite della faccia corrispondente.
Non servono array paralleli perché il dato numerico stesso funge da indice.

```
  Faccia:      1    2    3    4    5    6
  Indice:     [0]  [1]  [2]  [3]  [4]  [5]
  frequenze:   5    4    6    3    7    5
```

| Variabile    | Tipo      | Dimensione | Motivazione                                            |
|--------------|-----------|------------|--------------------------------------------------------|
| `frequenze`  | `int[]`   | 6          | Contatore per ogni faccia; `frequenze[i]` = uscite faccia i+1 |
| `lancio`     | `int`     | —          | Valore letto da tastiera (1–6), diventa indice         |
| `max_freq`   | `int`     | —          | Frequenza massima trovata                              |
| `min_freq`   | `int`     | —          | Frequenza minima trovata                               |
| `faccia_max` | `int`     | —          | Numero della faccia più frequente                      |
| `faccia_min` | `int`     | —          | Numero della faccia meno frequente                     |
| `valido`     | `int`     | —          | Flag per la validazione dell'input                     |
| `NUM_FACCE`  | `#define` | 6          | Numero di facce del dado                               |
| `NUM_LANCI`  | `#define` | 30         | Numero totale di lanci da inserire                     |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Acquisizione e conteggio dei lanci

**a) Input**
30 valori interi inseriti da tastiera, ciascuno compreso tra 1 e 6.

**b) Output**
Prompt per ogni lancio:
```
  Lancio  1: 
  Lancio  2: 
  ...
```

**c) Variabili di supporto**
- `lancio` (`int`): valore letto, usato come indice dopo la sottrazione di 1.
- `valido` (`int`): flag che controlla il ciclo di validazione.

**d) Vincoli**
- Solo valori nell'intervallo [1, 6] sono accettati.
- L'aggiornamento della frequenza avviene con `frequenze[lancio - 1] + 1`
  per mantenere la corrispondenza tra faccia e indice.

**e) Assunzioni**
- L'utente inserisce valori interi; input non numerici non sono gestiti.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare frequenze[0..5] = 0.
2. Per i da 0 a NUM_LANCI - 1:
   a. Inizializzare valido = 0.
   b. Mentre !valido:
      - Leggere lancio.
      - Se lancio in [1, NUM_FACCE]: valido = 1.
      - Altrimenti: stampare errore.
   c. frequenze[lancio - 1] += 1.
```

---

### Caso d'uso 2 – Istogramma delle frequenze

**a) Input**
Array `frequenze`.

**b) Output**
```
=== RISULTATI ===
  Faccia | Conteggio | Istogramma
  -------|-----------|--------------------
    1    |      5    | *****
    2    |      4    | ****
    3    |      6    | ******
    4    |      3    | ***
    5    |      7    | *******
    6    |      5    | *****
```

**c) Variabili di supporto**
- `i` (`int`): indice della faccia corrente.
- `j` (`int`): contatore per il ciclo di stampa degli asterischi.

**d) Vincoli**
- Il numero di asterischi stampati è esattamente `frequenze[i]`.
- L'indice i corrisponde alla faccia `i + 1`.

**e) Assunzioni**
- Le frequenze sono sempre non negative.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare intestazione della tabella.
2. Per i da 0 a NUM_FACCE - 1:
   a. Stampare i+1 e frequenze[i].
   b. Per j da 0 a frequenze[i] - 1: stampare "*".
   c. Andare a capo.
```

---

### Caso d'uso 3 – Faccia più e meno frequente

**a) Input**
Array `frequenze`.

**b) Output**
```
Faccia uscita piu' spesso : 5 (7 volte)
Faccia uscita meno spesso : 4 (3 volte)

Frequenza attesa per dado equilibrato: 5.0 volte per faccia
```

**c) Variabili di supporto**
- `max_freq`, `min_freq` (`int`): estremi correnti durante la scansione.
- `faccia_max`, `faccia_min` (`int`): faccia corrispondente agli estremi.

**d) Vincoli**
- `max_freq` e `min_freq` sono inizializzati a `frequenze[0]`, non a 0 o a
  un valore arbitrario, per garantire che l'inizializzazione sia sempre valida.
- Il ciclo parte da `i = 1` perché `i = 0` è già incluso nell'inizializzazione.

**e) Assunzioni**
- L'array ha almeno un elemento (garantito da `NUM_FACCE >= 1`).

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare max_freq = min_freq = frequenze[0]; faccia_max = faccia_min = 1.
2. Per i da 1 a NUM_FACCE - 1:
   a. Se frequenze[i] > max_freq: aggiornare max_freq e faccia_max.
   b. Se frequenze[i] < min_freq: aggiornare min_freq e faccia_min.
3. Stampare faccia_max, max_freq, faccia_min, min_freq.
4. Stampare frequenza attesa = NUM_LANCI / NUM_FACCE.
```
