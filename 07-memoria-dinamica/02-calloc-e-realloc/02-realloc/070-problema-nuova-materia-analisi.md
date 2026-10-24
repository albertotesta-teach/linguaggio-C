# Analisi – 070-problema-nuova-materia.c

## 1. Problema

A metà anno il tabellone dei voti riceve una materia in più. Il tabellone
è un blocco con le righe una dopo l'altra: aggiungere una colonna cambia
la lunghezza di ogni riga, quindi dopo la `realloc` i voti si spostano
nelle nuove posizioni, partendo dall'ultimo per non sovrascrivere nulla,
e poi si scrive la nuova colonna.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `righe`, `colonne` | `int` | Studenti 1-10, materie 1-8 |
| materie | parole | Sigle di 3 lettere |
| voti | `double` | Riga per riga |
| `comando` | `char` | `M sigla voto...` nuova materia con un voto per studente, `S` stampa, `Q` fine (anche minuscoli) |

### Output

- `S`: il tabellone con le sigle e la media di ogni studente.
- `M`: `SIGLA aggiunta: tabellone R x C`, oppure
  `Nome della materia: 3 lettere.`, `Al massimo 8 materie.`,
  `Memoria insufficiente.`
- `Dati non validi.`, `Dati mancanti o non validi.`,
  `Comando sconosciuto.`

### Vincoli

- Elemento (r, c) in `tab[r * colonne + c]`.
- `aggiungi_colonna`: `realloc` a righe × (colonne + 1) in un puntatore
  temporaneo; poi ogni voto passa da `r * colonne + c` a
  `r * (colonne + 1) + c`, dall'ultima riga e dall'ultima colonna, perché
  la destinazione non è mai prima della sorgente.
- I voti mancanti della nuova colonna valgono 0.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- I voti iniziali sono validi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `tab` | `double *` | Blocco del tabellone |
| `materie` | `char[8][4]` | Sigle |
| `righe`, `colonne` | `int` | Dimensioni |
| `ok` | `int` | Dati iniziali corretti |

| Funzione | Compito |
|----------|---------|
| `aggiungi_colonna(tab, righe, colonne)` | Ingrandisce e sposta; 0 se `realloc` fallisce |
| `stampa(tab, righe, colonne, materie)` | Tabellone con medie |

### Algoritmo in linguaggio naturale

1. Leggere dimensioni, sigle e voti in un blocco allocato.
2. Finché il comando non è `Q`: con `M` controllare la sigla, aggiungere
   la colonna, aggiornare `colonne`, scrivere sigla e voti della nuova
   colonna; con `S` stampare; scartare il resto della riga.
3. Liberare il blocco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Due materie aggiunte

- **Input:** `3 2`, `ITA MAT`, `6 7`, `8 5`, `7 7`, `S`, `m INF 9 6 8`,
  `S extra`, `M STORIA 1 2 3`, `M ING 5 x`, `S`, `X`, `Q`
- **Output atteso:**
  ```
                ITA  MAT  media
  studente  1   6.0  7.0   6.50
  studente  2   8.0  5.0   6.50
  studente  3   7.0  7.0   7.00
    INF aggiunta: tabellone 3 x 3
                ITA  MAT  INF  media
  studente  1   6.0  7.0  9.0   7.33
  studente  2   8.0  5.0  6.0   6.33
  studente  3   7.0  7.0  8.0   7.33
    Nome della materia: 3 lettere.
    ING aggiunta: tabellone 3 x 4
                ITA  MAT  INF  ING  media
  studente  1   6.0  7.0  9.0  5.0   6.75
  studente  2   8.0  5.0  6.0  0.0   4.75
  studente  3   7.0  7.0  8.0  0.0   5.50
    Comando sconosciuto.
  ```
  (i voti già presenti restano al loro posto dopo lo spostamento).
