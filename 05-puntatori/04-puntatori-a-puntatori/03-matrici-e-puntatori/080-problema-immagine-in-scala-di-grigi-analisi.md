# Analisi – 080-problema-immagine-in-scala-di-grigi.c

## 1. Problema

Nel laboratorio di grafica una piccola immagine in scala di grigi è una
matrice di livelli da 0 a 9, mostrata a terminale con un carattere per
livello. Il programma la capovolge in verticale e poi ne calcola il
negativo.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `immagine` | `int[6][10]` | Una freccia verso l'alto (livelli 9 e 6) su una base di livello 3 |

### Output

- L'immagine originale, capovolta e in negativo, disegnate con i caratteri
  di `" .:-=+*#%@"` (livello 0 = spazio, 9 = `@`).

### Vincoli

- Il livello è l'indice nella stringa dei caratteri `LIVELLI`.
- `stampa` riceve la matrice come puntatore a righe
  (`const int (*)[COLONNE]`) e la scorre con `riga++`.
- `capovolgi` usa due puntatori a righe, `alto` e `basso`, che si
  avvicinano; per ogni coppia scambia gli elementi con due puntatori a
  `int`; si ferma quando `alto` non è più minore di `basso` (con un numero
  dispari di righe quella centrale resta al suo posto).
- `negativo` tratta la matrice come un blocco unico di 60 interi
  consecutivi (`&immagine[0][0]`) e sostituisce ogni livello `v` con `9 − v`.

### Assunzioni

- I livelli sono sempre tra 0 e 9.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `riga` | `const int (*)[COLONNE]` | In `stampa`: riga corrente |
| `alto`, `basso` | `int (*)[COLONNE]` | In `capovolgi`: righe da scambiare |
| `a`, `b`, `temp` | `int *`, `int *`, `int` | In `capovolgi`: elementi delle due righe |
| `fine` | `int *` | In `negativo`: fine del blocco |
| `LIVELLI` | `#define` | `" .:-=+*#%@"` |

| Funzione | Compito |
|----------|---------|
| `stampa(img, righe)` | Disegna l'immagine riga per riga |
| `capovolgi(img, righe)` | Scambia le righe dagli estremi verso il centro |
| `negativo(p, n)` | `9 − v` per n elementi consecutivi |

### Algoritmo in linguaggio naturale

1. Stampare l'originale.
2. Capovolgere: finché `alto < basso` scambiare elemento per elemento le due
   righe, poi avanzare `alto` e arretrare `basso`; stampare.
3. Calcolare il negativo sul blocco di 60 elementi; stampare.

## 3. Casi di test

### Test 1 – Trasformazioni

- **Input:** nessuno.
- **Valori intermedi attesi:** dopo il negativo la base (livello 3, `-`)
  diventa 6 (`*`), lo sfondo 0 diventa 9 (`@`), il gambo 6 diventa 3.
- **Output atteso:**
  ```
  Originale:
    |    @@    |
    |   @@@@   |
    |  @@@@@@  |
    |    **    |
    |    **    |
    |----------|

  Capovolta:
    |----------|
    |    **    |
    |    **    |
    |  @@@@@@  |
    |   @@@@   |
    |    @@    |

  Negativo:
    |**********|
    |@@@@--@@@@|
    |@@@@--@@@@|
    |@@      @@|
    |@@@    @@@|
    |@@@@  @@@@|
  ```
