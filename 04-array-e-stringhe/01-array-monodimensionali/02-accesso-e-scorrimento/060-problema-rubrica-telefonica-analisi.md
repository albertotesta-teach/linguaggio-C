# Analisi – 060-problema-rubrica-telefonica.c

## 1. Problema

Un'applicazione gestisce una rubrica telefonica con 6 contatti. Il programma
deve visualizzare la rubrica completa, cercare un contatto per prefisso del
nome (senza usare `strcmp`) e filtrare i contatti con numero di cellulare
(prefisso telefonico '3').

---

## 2. Analisi generale e struttura dati

I dati sono organizzati in array paralleli: `nomi[i]` e `telefoni[i]`
appartengono sempre allo stesso contatto. La ricerca per nome viene svolta
con confronto manuale carattere per carattere per mostrare il meccanismo
sottostante alla funzione `strcmp`.

| Variabile         | Tipo         | Dimensione   | Motivazione                                            |
|-------------------|--------------|--------------|--------------------------------------------------------|
| `nomi`            | `char[][]`   | 6 × 25       | Max 24 caratteri per nome+cognome + `'\0'`             |
| `telefoni`        | `char[][]`   | 6 × 13       | Numeri fino a 12 cifre/simboli + `'\0'`                |
| `ricerca`         | `char[]`     | 25           | Stringa da cercare nella rubrica                       |
| `trovato`         | `int`        | —            | Flag booleano: 1 se il contatto è stato trovato        |
| `indice_trovato`  | `int`        | —            | Posizione del contatto trovato nell'array              |
| `len_ricerca`     | `int`        | —            | Lunghezza della stringa di ricerca (calcolata)         |
| `uguale`          | `int`        | —            | Flag interno al ciclo di confronto caratteri           |
| `num_cellulari`   | `int`        | —            | Contatore contatti con prefisso '3'                    |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Stampa della rubrica completa

**a) Input**
Array `nomi` e `telefoni` inizializzati staticamente.

**b) Output**
```
======================================
           RUBRICA TELEFONICA
======================================
  Rossi Marco          3471234567
  Bianchi Sara         0212345678
  ...
======================================
```

**c) Variabili di supporto**
- `i` (`int`): indice del ciclo.

**d) Vincoli**
- Il formato `%-20s` allinea i nomi a sinistra su 20 caratteri.
- I due array devono avere la stessa dimensione `NUM_CONTATTI`.

**e) Assunzioni**
- I dati sono statici e validi. I nomi non superano 24 caratteri.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare intestazione.
2. Per i da 0 a NUM_CONTATTI - 1: stampare nomi[i] e telefoni[i].
3. Stampare separatore finale.
```

---

### Caso d'uso 2 – Ricerca per prefisso del nome

**a) Input**
Stringa `ricerca` inizializzata nel codice (es. `"Rossi"`).

**b) Output**
```
Ricerca 'Rossi':
  Trovato: Rossi Marco - Tel: 3471234567
```

**c) Variabili di supporto**
- `len_ricerca`, `trovato`, `indice_trovato`, `uguale`.

**d) Vincoli**
- Ciclo esterno con `&& !trovato`; ciclo interno con `&& uguale`. Nessun `break`.

**e) Assunzioni**
- Confronto case-sensitive; ricerca per prefisso (primi `len_ricerca` caratteri).

**f) Algoritmo in linguaggio naturale**
```
1. Calcolare len_ricerca fino a '\0'.
2. Per i da 0 a NUM_CONTATTI - 1, finché !trovato:
   a. uguale = 1.
   b. Per j da 0 a len_ricerca - 1, finché uguale:
      - Se nomi[i][j] != ricerca[j]: uguale = 0.
   c. Se uguale: trovato = 1, indice_trovato = i.
3. Stampare risultato.
```

---

### Caso d'uso 3 – Filtro per prefisso telefonico

**a) Input**
Array `telefoni`.

**b) Output**
```
Contatti con numero di cellulare (prefisso '3'):
  Rossi Marco: 3471234567
  Verdi Luca: 3389876543
  Russo Pietro: 3201112233
Totale cellulari in rubrica: 3 su 6
```

**c) Variabili di supporto**
- `num_cellulari` (`int`): contatore.

**d) Vincoli**
- Controllo su `telefoni[i][0] == '3'` (carattere, non intero).

**f) Algoritmo in linguaggio naturale**
```
1. Per i da 0 a NUM_CONTATTI - 1:
   a. Se telefoni[i][0] == '3': stampare e incrementare num_cellulari.
2. Stampare il totale.
```
