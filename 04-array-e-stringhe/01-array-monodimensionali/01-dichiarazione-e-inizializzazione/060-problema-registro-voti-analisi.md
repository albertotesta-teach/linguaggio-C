# Analisi – 060-problema-registro-voti.c

## 1. Problema

Un insegnante ha bisogno di un programma che memorizzi i voti di matematica
di 8 studenti, li visualizzi in un registro formattato e produca statistiche
di classe: media, voto più alto, voto più basso, numero di promossi e bocciati.

---

## 2. Analisi

### Input
Nessun input da tastiera: nomi e voti sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                       |
|-----------|------------|------------|---------------------------------------------------|
| `nomi`    | `char[][]` | 8 × 20     | Cognome e nome di ogni studente                   |
| `voti`    | `int[]`    | 8          | Voto di ogni studente, parallelo a `nomi`         |

### Output
- Il registro: numero progressivo, nome e voto di ogni studente in colonne
  allineate;
- la media della classe (un decimale), il voto più basso e quello più alto
  con il nome dello studente;
- il numero di promossi (voto ≥ 6) e di bocciati.

### Vincoli
- `nomi` e `voti` hanno la stessa dimensione: l'indice `i` identifica lo
  stesso studente in entrambi gli array
- Il numero progressivo stampato è `i + 1`, perché gli indici partono da 0
- Minimo e massimo partono dal primo elemento, non da valori arbitrari
- La media si calcola con una divisione reale
- promossi + bocciati = 8; la soglia di sufficienza è 6 inclusa
- In caso di parità per il minimo o il massimo si riporta il primo studente
  trovato

### Assunzioni
- I dati sono validi: voti tra 1 e 10, nomi di al massimo 19 caratteri
- L'array contiene almeno un elemento

### Variabili di supporto

| Variabile        | Tipo      | Descrizione                                 |
|------------------|-----------|---------------------------------------------|
| `somma`          | `int`     | Accumulatore per la media                   |
| `minimo`, `massimo`        | `int` | Voti estremi trovati                  |
| `indice_min`, `indice_max` | `int` | Posizioni degli estremi negli array   |
| `promossi`, `bocciati`     | `int` | Contatori                             |
| `NUMERO_STUDENTI`| `#define` | 8: dimensione degli array e limite dei cicli |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione e, per ogni studente, `i + 1`, `nomi[i]` e
   `voti[i]`.
2. Sommare tutti i voti e stampare la media `somma / NUMERO_STUDENTI`.
3. Porre minimo e massimo uguali a `voti[0]` e i loro indici a 0; per gli
   studenti da 1 in poi aggiornare minimo o massimo e il relativo indice
   quando si trova un voto più piccolo o più grande.
4. Stampare voto minimo e massimo con il nome corrispondente.
5. Contare promossi (voto ≥ 6) e bocciati e stamparli.

---

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Registro e statistiche con i dati del programma
- **Input:** voti 7, 8, 6, 9, 5, 8, 7, 10
- **Valori intermedi attesi:** somma 60, media 60 / 8 = 7.5
- **Output atteso:**
```
   1  | Rossi Marco        |    7
   2  | Bianchi Sara       |    8
   3  | Verdi Luca         |    6
   4  | Ferrari Anna       |    9
   5  | Russo Pietro       |    5
   6  | Colombo Giulia     |    8
   7  | Marino Davide      |    7
   8  | Greco Elena        |   10
============================================

Media della classe : 7.5
Voto più basso     : 5 (Russo Pietro)
Voto più alto      : 10 (Greco Elena)

Studenti promossi  : 7 su 8
Studenti bocciati  : 1 su 8
```

### Test 2 – Massimo nel primo elemento
- **Cosa si verifica:** l'inizializzazione con `voti[0]` non perde il primo
  studente
- **Procedura:** cambiare i voti in `{10, 8, 6, 9, 5, 8, 7, 4}`, ricompilare
  ed eseguire
- **Output atteso:** `Voto più alto      : 10 (Rossi Marco)`,
  `Voto più basso     : 4 (Greco Elena)`, promossi 6, bocciati 2

### Test 3 – Voto al limite della sufficienza
- **Cosa si verifica:** il voto 6 conta come promosso
- **Procedura:** nei dati del Test 1 controllare Verdi Luca (voto 6)
- **Output atteso:** è incluso nei 7 promossi
