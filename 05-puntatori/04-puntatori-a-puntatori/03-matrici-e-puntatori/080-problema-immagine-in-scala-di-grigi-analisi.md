# Analisi – 080-problema-immagine-in-scala-di-grigi.c

## 1. Problema

Nel laboratorio di grafica una piccola immagine in scala di grigi è una matrice di livelli da 0 a 9, mostrata a terminale con un carattere per livello. Il programma la capovolge in verticale e poi ne calcola il negativo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `immagine` | `int[][]` | 6 × 10 | Livelli di grigio |
| `alto`, `basso` | `int (*)[COLONNE]` | — | Righe da scambiare |
| `a`, `b` | `int *` | — | Elementi delle due righe |
| `LIVELLI` | letterale | 11 | Carattere per ogni livello |

| Funzione | Compito |
|----------|---------|
| `stampa(img, righe)` | Disegna l'immagine riga per riga |
| `capovolgi(img, righe)` | Scambia le righe dagli estremi verso il centro |
| `negativo(p, n)` | 9 − v per n elementi consecutivi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Capovolgimento

**a) Input** – immagine a freccia verso l'alto

**b) Output** – freccia verso il basso

**c) Variabili di supporto** – `alto`, `basso`

**d) Vincoli** – si ferma quando `alto` non è più minore di `basso`

**e) Assunzioni** – numero di righe qualsiasi

**f) Algoritmo in linguaggio naturale** – scambiare elemento per elemento la riga `*alto` con la riga `*basso`, poi `alto++` e `basso--`.

### Caso d'uso 2 – Negativo

**a) Input** – livello 0

**b) Output** – livello 9 ('@')

**c) Variabili di supporto** – `p`

**d) Vincoli** – la riga non conta: blocco unico

**e) Assunzioni** – livelli da 0 a 9

**f) Algoritmo in linguaggio naturale** – per ogni elemento `*p = 9 - *p`.

### Caso d'uso 3 – Stampa

**a) Input** – livello 3

**b) Output** – carattere '-'

**c) Variabili di supporto** – `LIVELLI[(*riga)[c]]`

**d) Vincoli** – il livello è l'indice nella stringa dei caratteri

**e) Assunzioni** – valori sempre tra 0 e 9

**f) Algoritmo in linguaggio naturale** – per ogni elemento stampare il carattere corrispondente.
