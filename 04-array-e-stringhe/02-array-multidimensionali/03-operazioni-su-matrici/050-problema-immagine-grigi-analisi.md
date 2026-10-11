# Analisi – 050-problema-immagine-grigi.c

## 1. Problema

Un'immagine in scala di grigi di 6 × 10 pixel (una freccia verso destra)
è rappresentata da una matrice di luminosità da 0 a 255. Il programma deve
mostrarla a schermo con caratteri di diversa "pienezza", calcolarne la
luminosità media e applicare tre operazioni: negativo, soglia (bianco/nero)
e specchio orizzontale.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `originale` | `int[][]` | 6 × 10 | Luminosità dei pixel, non viene modificata |
| `risultato` | `int[][]` | 6 × 10 | Matrice di lavoro per ogni operazione |
| `livello` | `int` | — | Luminosità ridotta a 0-4 (`valore / 52`) per la stampa |
| `somma` | `long` | — | Accumulatore per la media |
| `appoggio` | `int` | — | Variabile per lo scambio |

| Livello | 0 | 1 | 2 | 3 | 4 |
|---------|---|---|---|---|---|
| Carattere | spazio | `..` | `oo` | `OO` | `@@` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Visualizzazione e luminosità media

**a) Input** – matrice `originale`

**b) Output** – la freccia disegnata e "Luminosita' media: 74.0"

**c) Variabili di supporto** – `livello`, `somma`

**d) Vincoli** – ogni pixel occupa due caratteri, per compensare la forma
rettangolare dei caratteri del terminale

**e) Assunzioni** – valori tra 0 e 255

**f) Algoritmo in linguaggio naturale** – per ogni pixel calcolare il livello,
stampare il carattere corrispondente e sommare il valore; dividere la somma
per il numero di pixel.

### Caso d'uso 2 – Negativo e soglia

**a) Input** – matrice `originale`

**b) Output** – la freccia scura su sfondo chiaro; la freccia in bianco e nero
(solo la punta supera la soglia 128)

**c) Variabili di supporto** – `risultato`

**d) Vincoli** – `originale` non cambia: entrambe le operazioni scrivono in
`risultato`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Negativo: per ogni pixel `risultato = 255 - originale`.
2. Soglia: per ogni pixel `risultato = 255` se `originale > 128`, altrimenti 0.

### Caso d'uso 3 – Specchio orizzontale

**a) Input** – matrice `originale`

**b) Output** – la freccia rivolta a sinistra

**c) Variabili di supporto** – `appoggio`

**d) Vincoli** – in ogni riga si scambiano solo le colonne della prima metà
con le simmetriche (`LARGHEZZA - 1 - c`), come nell'inversione di un array

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – copiare `originale` in `risultato`,
poi per ogni riga e per c da 0 a metà larghezza scambiare `[r][c]` e
`[r][LARGHEZZA - 1 - c]`.
