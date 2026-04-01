# Analisi – 060-problema-disegno-forme.c

## 1. Problema
Un programma didattico deve disegnare tre forme geometriche usando caratteri
ASCII: un rettangolo pieno, un triangolo rettangolo e una cornice (rettangolo
vuoto). Le dimensioni sono definite come costanti e condivise da tutte le
funzioni. L'obiettivo è mostrare come le funzioni void possano incapsulare
algoritmi di disegno autonomi e richiamabili in qualunque ordine.

## 2. Analisi generale e struttura dati

| Costante | Valore | Descrizione |
|---|---|---|
| `LARGHEZZA` | 8 | Numero di colonne (usato da rettangolo e cornice) |
| `ALTEZZA` | 5 | Numero di righe (usato da tutte e tre le forme) |

| Funzione | Tipo | Descrizione |
|---|---|---|
| `disegna_rettangolo` | void | Rettangolo pieno di asterischi |
| `disegna_triangolo` | void | Triangolo rettangolo con base in basso |
| `disegna_cornice` | void | Solo bordo esterno del rettangolo |
| `disegna_tutte_le_forme` | void | Chiama le tre funzioni con spaziatura |

Variabili locali comuni a tutte le funzioni di disegno:

| Variabile | Tipo | Ruolo |
|---|---|---|
| `riga` | int | Contatore riga corrente (loop esterno) |
| `colonna` | int | Contatore colonna corrente (loop interno) |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Disegno del rettangolo pieno

**a) Input** – nessuno (dimensioni da `#define`)

**b) Output**
```
Rettangolo (8x5):
********
********
********
********
********
```

**c) Variabili di supporto** – `riga` (0..ALTEZZA-1), `colonna` (0..LARGHEZZA-1)

**d) Vincoli** – ogni riga deve contenere esattamente `LARGHEZZA` asterischi

**e) Assunzioni** – `LARGHEZZA` e `ALTEZZA` sono maggiori di 0

**f) Algoritmo in linguaggio naturale**
1. Per ogni riga da 0 a ALTEZZA-1:
   1. Per ogni colonna da 0 a LARGHEZZA-1: stampa `*`
   2. Vai a capo

### Caso d'uso 2 – Disegno del triangolo rettangolo

**a) Input** – nessuno

**b) Output**
```
Triangolo rettangolo (base 5):
*
**
***
****
*****
```

**c) Variabili di supporto** – `riga` (1..ALTEZZA), `colonna` (1..riga)

**d) Vincoli** – la riga i deve contenere esattamente i asterischi

**e) Assunzioni** – `ALTEZZA` ≥ 1

**f) Algoritmo in linguaggio naturale**
1. Per ogni riga da 1 a ALTEZZA:
   1. Per ogni colonna da 1 a riga: stampa `*`
   2. Vai a capo

### Caso d'uso 3 – Disegno della cornice

**a) Input** – nessuno

**b) Output**
```
Cornice (8x5):
********
*      *
*      *
*      *
********
```

**c) Variabili di supporto** – `riga` (0..ALTEZZA-1), `colonna` (0..LARGHEZZA-1)

**d) Vincoli**
- Prima e ultima riga: solo asterischi
- Righe intermedie: asterisco in colonna 0 e LARGHEZZA-1, spazio negli altri

**e) Assunzioni** – `ALTEZZA` ≥ 2 e `LARGHEZZA` ≥ 2 per avere una cornice visibile

**f) Algoritmo in linguaggio naturale**
1. Per ogni riga da 0 a ALTEZZA-1:
   1. Per ogni colonna da 0 a LARGHEZZA-1:
      - Se riga==0 o riga==ALTEZZA-1: stampa `*`
      - Altrimenti se colonna==0 o colonna==LARGHEZZA-1: stampa `*`
      - Altrimenti: stampa spazio
   2. Vai a capo
