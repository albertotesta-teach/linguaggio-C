# Analisi – 040-problema-scambio-valori.c

## 1. Problema
Un algoritmo di ordinamento ha bisogno di scambiare il contenuto di due
variabili intere. La funzione `scambia()` deve modificare entrambe le variabili
del chiamante, operazione impossibile con il solo passaggio per valore. Il
programma dimostra anche come chiamate ripetute a `scambia()` possano ordinare
tre numeri in ordine crescente.

## 2. Analisi

### Input
Nessun input da tastiera: i valori sono assegnati nel `main`.

| Variabile | Tipo | Descrizione |
|---|---|---|
| `primo`, `secondo`, `terzo` | int | Valori da scambiare o ordinare |

### Output
- Per lo scambio: i valori di `primo` e `secondo` prima e dopo la chiamata.
- Per l'ordinamento: le terne prima e dopo `ordina_tre`, in ordine crescente.

### Vincoli
- `scambia` riceve gli indirizzi delle variabili (`int *`): solo così può
  modificare le variabili del chiamante; con il passaggio per valore
  scambierebbe solo copie locali
- I puntatori passati non sono `NULL`
- `ordina_tre` deve funzionare anche con valori uguali e con valori negativi

### Assunzioni
- Le due variabili passate a `scambia` sono distinte
- Con tre elementi bastano tre confronti tra coppie adiacenti

### Variabili di supporto

| Variabile | Tipo | Descrizione |
|---|---|---|
| `temp` | int (locale a `scambia`) | Conserva un valore durante lo scambio |

| Funzione | Firma | Descrizione |
|---|---|---|
| `scambia` | `void(int*, int*)` | Scambia i valori di due variabili int |
| `ordina_tre` | `void(int*, int*, int*)` | Ordina tre interi in ordine crescente |
| `stampa_tre` | `void(int, int, int)` | Stampa tre valori su una riga |

### Algoritmo in linguaggio naturale
Scambio:
1. Salvare `*a` in `temp`.
2. Copiare `*b` in `*a`.
3. Copiare `temp` in `*b`.

Ordinamento di tre valori (bubble sort a tre elementi):
1. Se `*x > *y`: scambiare x e y.
2. Se `*y > *z`: scambiare y e z (il massimo finisce in fondo).
3. Se `*x > *y`: scambiare x e y (sistema i primi due).

## 3. Casi di test

Il programma esegue in sequenza i casi presenti nel `main`: si esegue una
volta e si confronta ogni blocco con l'output atteso.

### Test 1 – Scambio di due variabili
- **Input:** `primo = 42`, `secondo = 7`
- **Output atteso:**
```
Prima dello scambio:  primo=42  secondo=7
Dopo  lo scambio:     primo=7  secondo=42
```

### Test 2 – Ordinamento di tre valori distinti
- **Input:** 9, 3, 6
- **Output atteso:** `Prima:   9  3  6` e `Dopo:    3  6  9`

### Test 3 – Tre valori uguali
- **Cosa si verifica:** nessuno scambio viene eseguito e i valori restano
  invariati
- **Input:** 1, 1, 1
- **Output atteso:** `Dopo:    1  1  1`

### Test 4 – Valori con un negativo
- **Input:** 100, -5, 42
- **Output atteso:** `Dopo:    -5  42  100`

### Test 5 – Versione errata con passaggio per valore
- **Cosa si verifica:** perché il passaggio per riferimento è necessario
- **Procedura:** scrivere la funzione `scambia_sbagliata(int a, int b)`
  riportata nel commento del `main`, chiamarla con `primo = 42` e
  `secondo = 7` e stampare le variabili
- **Output atteso:** `primo=42  secondo=7`: le variabili del chiamante non
  cambiano
