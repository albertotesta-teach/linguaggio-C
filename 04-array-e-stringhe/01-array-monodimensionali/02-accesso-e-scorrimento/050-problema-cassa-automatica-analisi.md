# Analisi – 050-problema-cassa-automatica.c

## 1. Problema

Una cassa automatica deve restituire il resto a un cliente usando il minor numero
possibile di monete. Il programma legge il prezzo e l'importo pagato, calcola
il resto in centesimi e applica un algoritmo greedy: scorre i tagli disponibili
dal più grande al più piccolo, assegnando quante monete possibile per ogni taglio.

---

## 2. Analisi generale e struttura dati

I tagli sono memorizzati in un array di interi **in centesimi** per evitare
gli errori di arrotondamento tipici della virgola mobile. Il secondo array
`monete_usate` è strettamente parallelo: `monete_usate[i]` conta le monete
del taglio `tagli[i]` restituite. L'algoritmo scorre l'array una sola volta,
aggiornando il resto a ogni iterazione.

| Variabile           | Tipo      | Dimensione | Motivazione                                              |
|---------------------|-----------|------------|----------------------------------------------------------|
| `tagli`             | `int[]`   | 8          | Tagli disponibili in centesimi, ordine decrescente       |
| `monete_usate`      | `int[]`   | 8          | Numero di monete usate per ogni taglio; parallelo a `tagli` |
| `prezzo_centesimi`  | `int`     | —          | Prezzo dell'articolo in centesimi (intero)               |
| `pagato_centesimi`  | `int`     | —          | Importo pagato in centesimi (intero)                     |
| `resto`             | `int`     | —          | Resto da restituire, decrementato durante l'algoritmo    |
| `totale_monete`     | `int`     | —          | Somma di tutti gli elementi di `monete_usate`            |
| `valido`            | `int`     | —          | Flag per la validazione dell'input                       |
| `NUM_TAGLI`         | `#define` | 8          | Dimensione degli array e limite dei cicli                |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Acquisizione e validazione dell'input

**a) Input**
Due interi inseriti da tastiera: prezzo e importo pagato, entrambi in centesimi.

**b) Output**
```
Prezzo articolo (in centesimi, es. 135 per 1,35 euro): 135
Importo pagato  (in centesimi): 200

Prezzo  : 1,35 euro
Pagato  : 2,00 euro
Resto   : 0,65 euro
```

**c) Variabili di supporto**
- `valido` (`int`): flag per il ciclo `while` di validazione.

**d) Vincoli**
- Il prezzo deve essere positivo (`> 0`).
- L'importo pagato deve essere `>= prezzo_centesimi`.
- La stampa in formato euro usa divisione e modulo interi: `centesimi / 100` e `centesimi % 100`.

**e) Assunzioni**
- L'utente inserisce valori interi (centesimi interi, senza virgola).
- Non si gestisce il caso di overflow (prezzi molto grandi).

**f) Algoritmo in linguaggio naturale**
```
1. Richiedere prezzo_centesimi; ripetere finché <= 0.
2. Richiedere pagato_centesimi; ripetere finché < prezzo_centesimi.
3. resto = pagato_centesimi - prezzo_centesimi.
4. Stampare prezzo, pagato e resto in formato euro (/ 100 e % 100).
```

---

### Caso d'uso 2 – Algoritmo greedy per il resto

**a) Input**
Array `tagli`, variabile `resto`.

**b) Output**
```
Composizione del resto:
   50 cent  x 1 moneta/e
   10 cent  x 1 moneta/e
    5 cent  x 1 moneta/e

Resto restituito correttamente.
```

**c) Variabili di supporto**
- `monete_usate[i]` (`int`): quante monete del taglio `i` vengono usate.
- `resto` (`int`): aggiornato sottraendo le monete assegnate a ogni iterazione.

**d) Vincoli**
- `tagli` deve essere in ordine decrescente affinché l'algoritmo greedy sia
  corretto per il sistema monetario euro.
- `monete_usate[i] = resto / tagli[i]` usa la divisione intera (quoziente).
- `resto = resto - monete_usate[i] * tagli[i]` equivale a `resto % tagli[i]`.
- Con il taglio da 1 centesimo sempre presente, il resto è sempre azzerabile.
- Si stampano solo i tagli con `monete_usate[i] > 0`.

**e) Assunzioni**
- I tagli sono fissi e includono sempre il centesimo (1), garantendo la soluzione.
- Non si considera la disponibilità fisica limitata delle monete in cassa.

**f) Algoritmo in linguaggio naturale**
```
1. Per i da 0 a NUM_TAGLI - 1:
   a. monete_usate[i] = resto / tagli[i].
   b. resto = resto - monete_usate[i] * tagli[i].
   c. Se monete_usate[i] > 0: stampare taglio e quantità.
2. Se resto == 0: stampare "Resto restituito correttamente".
   Altrimenti: stampare messaggio di errore.
```

---

### Caso d'uso 3 – Conteggio totale delle monete

**a) Input**
Array `monete_usate`.

**b) Output**
```
Totale monete restituite: 3
```

**c) Variabili di supporto**
- `totale_monete` (`int`): somma degli elementi di `monete_usate`.

**d) Vincoli**
- Il ciclo scorre tutto l'array, incluse le celle con valore 0 (nessun impatto sulla somma).

**e) Assunzioni**
- `monete_usate` è stato correttamente popolato dall'algoritmo greedy.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare totale_monete = 0.
2. Per i da 0 a NUM_TAGLI - 1: totale_monete += monete_usate[i].
3. Stampare totale_monete.
```
