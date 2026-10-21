# Analisi – 050-problema-conta-occorrenze.c

## 1. Problema

Un correttore ortografico di base deve analizzare un testo inserito
dall'utente e contare quante volte compare una determinata lettera,
distinguendo tra maiuscole e minuscole e fornendo anche il totale
case-insensitive.

---

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                                 |
|-----------|----------|------------|---------------------------------------------|
| `testo`   | `char[]` | 201        | Testo con spazi, max 200 caratteri          |
| `lettera` | `char`   | —          | Lettera da cercare                          |

### Output
Il testo, la lettera cercata e quattro conteggi: occorrenze esatte (stesso
carattere inserito), occorrenze della maiuscola, occorrenze della minuscola
e totale senza distinzione tra maiuscole e minuscole.

### Vincoli
- Il testo si legge con `fgets` e si toglie il `'\n'` finale; la lettera con
  `scanf(" %c")`, dove lo spazio scarta i caratteri bianchi rimasti nel
  buffer
- Maiuscola e minuscola di una lettera differiscono di 32 nel codice ASCII:
  la versione mancante si calcola sommando o sottraendo 32
- Per un carattere non alfabetico maiuscola e minuscola coincidono con il
  carattere stesso
- Il totale conta una sola volta ogni carattere che coincide con la
  maiuscola **oppure** con la minuscola: non è la somma dei due contatori,
  che per un carattere non alfabetico conterebbe due volte gli stessi
  caratteri (vedi Test 3)

### Assunzioni
- La codifica è ASCII; le lettere accentate non sono gestite

### Variabili di supporto

| Variabile | Tipo   | Descrizione                                     |
|-----------|--------|-------------------------------------------------|
| `lettera_maiuscola`, `lettera_minuscola` | `char` | Le due versioni della lettera |
| `occorrenze_esatte`, `occorrenze_maiuscola`, `occorrenze_minuscola` | `int` | Contatori |
| `occorrenze_totali` | `int` | Caratteri uguali alla maiuscola o alla minuscola |
| `c`       | `char` | Carattere corrente                              |
| `i`       | `int`  | Indice di scorrimento                           |

### Algoritmo in linguaggio naturale
1. Leggere il testo e rimuovere il `'\n'`; leggere la lettera.
2. Se la lettera è minuscola calcolare la maiuscola (−32); se è maiuscola
   calcolare la minuscola (+32); altrimenti usare il carattere per entrambe.
3. Scorrere il testo fino a `'\0'`: per ogni carattere incrementare il
   contatore esatto se coincide con la lettera, e i contatori di maiuscola e
   minuscola se coincide con l'una o con l'altra; incrementare una sola
   volta il totale se coincide con almeno una delle due.
4. Stampare i risultati e il totale.

---

## 3. Casi di test

Per ogni caso si inseriscono il testo e la lettera indicati.

### Test 1 – Lettera minuscola
- **Input:** `Anna ama la pasta al pomodoro`, `a`
- **Output atteso:**
```
  Occorrenze esatte ('a')   : 7
  Occorrenze maiuscola ('A'): 1
  Occorrenze minuscola ('a'): 7
  Totale (case-insensitive)  : 8
```

### Test 2 – Lettera maiuscola
- **Cosa si verifica:** cambia solo il conteggio esatto
- **Input:** lo stesso testo, `A`
- **Output atteso:** `Occorrenze esatte ('A')   : 1`, gli altri valori come
  nel Test 1

### Test 3 – Carattere non alfabetico
- **Cosa si verifica:** per un carattere senza maiuscola e minuscola il
  totale non conta due volte le stesse occorrenze
- **Input:** `Via Roma 11, int. 1`, `1`
- **Output atteso:**
```
  Occorrenze esatte ('1')   : 3
  Occorrenze maiuscola ('1'): 3
  Occorrenze minuscola ('1'): 3
  Totale (case-insensitive)  : 3
```
