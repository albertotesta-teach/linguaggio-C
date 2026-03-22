# Analisi – 060-problema-registro-voti.c

## 1. Problema

Un insegnante ha bisogno di un programma che memorizzi i voti di matematica
di 8 studenti, li visualizzi in un registro formattato e produca statistiche
di classe: media, voto più alto, voto più basso, numero di promossi e bocciati.

---

## 2. Analisi generale e struttura dati

Il programma gestisce dati paralleli: per ogni studente esistono un nome e un voto.
Si usano due array con lo stesso numero di elementi (`NUMERO_STUDENTI`), in cui
l'indice `i` identifica sempre lo stesso studente in entrambi gli array.

| Variabile        | Tipo       | Dimensione           | Motivazione                                         |
|------------------|------------|----------------------|-----------------------------------------------------|
| `nomi`           | `char[][]` | 8 × 20               | 8 studenti, nome+cognome max 19 caratteri + `'\0'`  |
| `voti`           | `int[]`    | 8                    | Un voto intero per ogni studente                    |
| `somma`          | `int`      | —                    | Accumulatore per il calcolo della media             |
| `minimo`         | `int`      | —                    | Voto più basso trovato finora                       |
| `massimo`        | `int`      | —                    | Voto più alto trovato finora                        |
| `indice_min`     | `int`      | —                    | Indice dello studente con voto minimo               |
| `indice_max`     | `int`      | —                    | Indice dello studente con voto massimo              |
| `promossi`       | `int`      | —                    | Contatore studenti con voto >= 6                    |
| `bocciati`       | `int`      | —                    | Contatore studenti con voto < 6                     |
| `NUMERO_STUDENTI`| `#define`  | 8                    | Costante per dimensione array e limiti cicli        |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Stampa del registro formattato

**a) Input**
Array `nomi` e `voti` inizializzati staticamente nel codice.

**b) Output**
```
============================================
      REGISTRO VOTI - MATEMATICA
============================================
  N.  | Nome               | Voto
------|--------------------|------
   1  | Rossi Marco        |    7
  ...
============================================
```

**c) Variabili di supporto**
- `i` (`int`): indice del ciclo for.

**d) Vincoli**
- Gli array `nomi` e `voti` devono avere la stessa dimensione (`NUMERO_STUDENTI`).
- Il numero progressivo stampato è `i + 1` (gli indici partono da 0).

**e) Assunzioni**
- I dati sono statici e validi (nessun controllo di input).
- I nomi non superano 19 caratteri.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare intestazione e separatori.
2. Per i da 0 a NUMERO_STUDENTI - 1:
   a. Stampare i+1, nomi[i] e voti[i] in colonne allineate.
3. Stampare la riga di chiusura.
```

---

### Caso d'uso 2 – Calcolo di media, minimo e massimo

**a) Input**
Array `voti`.

**b) Output**
```
Media della classe : 7.5
Voto più basso     : 5 (Russo Pietro)
Voto più alto      : 10 (Greco Elena)
```

**c) Variabili di supporto**
- `somma` (`int`): somma accumulata.
- `minimo`, `massimo` (`int`): valori estremi correnti.
- `indice_min`, `indice_max` (`int`): posizioni degli estremi.

**d) Vincoli**
- `minimo` e `massimo` devono essere inizializzati al primo elemento (`voti[0]`),
  non a valori arbitrari come 0 o 100.
- Il ciclo per minimo e massimo parte da `i = 1` perché `i = 0` è già considerato.

**e) Assunzioni**
- L'array contiene almeno un elemento.
- I voti sono compresi tra 1 e 10.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare somma = 0.
2. Per i da 0 a NUMERO_STUDENTI - 1: somma += voti[i].
3. media = somma / NUMERO_STUDENTI (divisione floating point).
4. Inizializzare minimo = massimo = voti[0]; indice_min = indice_max = 0.
5. Per i da 1 a NUMERO_STUDENTI - 1:
   a. Se voti[i] < minimo: aggiorna minimo e indice_min.
   b. Se voti[i] > massimo: aggiorna massimo e indice_max.
6. Stampare media, minimo con nome, massimo con nome.
```

---

### Caso d'uso 3 – Conteggio promossi e bocciati

**a) Input**
Array `voti`.

**b) Output**
```
Studenti promossi  : 7 su 8
Studenti bocciati  : 1 su 8
```

**c) Variabili di supporto**
- `promossi` (`int`): contatore studenti con voto >= 6.
- `bocciati` (`int`): contatore studenti con voto < 6.

**d) Vincoli**
- `promossi + bocciati` deve essere sempre uguale a `NUMERO_STUDENTI`.
- La soglia di sufficienza è 6 (inclusa).

**e) Assunzioni**
- Non esistono voti nulli o non assegnati.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare promossi = 0, bocciati = 0.
2. Per i da 0 a NUMERO_STUDENTI - 1:
   a. Se voti[i] >= 6: promossi += 1.
   b. Altrimenti: bocciati += 1.
3. Stampare promossi e bocciati con il totale.
```
