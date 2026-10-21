# Analisi – 070-problema-figure-ascii.c

## 1. Problema

Disegnare con il carattere `*` quattro figure di altezza scelta dall'utente
(da 2 a 20): triangolo rettangolo, piramide centrata, quadrato vuoto e rombo.
È lo stesso problema di un'insegna a matrice di LED, che accende punti su una
griglia di righe e colonne.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                       |
|-----------|-------|-----------------------------------|
| `altezza` | `int` | Numero di righe delle figure      |

### Output
Le quattro figure disegnate una dopo l'altra:
- triangolo rettangolo di `altezza` righe;
- piramide centrata con base di `2 × altezza − 1` asterischi;
- quadrato vuoto `altezza × altezza`;
- rombo di `2 × altezza − 1` righe.

### Vincoli
- `altezza` è compresa tra 2 e 20: la richiesta si ripete finché non lo è
  (con altezza 1 le figure degenerano in un punto; oltre 20 il rombo supera
  la larghezza abituale del terminale)
- L'a capo si stampa alla fine di ogni riga, fuori dai cicli interni
- Il rombo non ripete la riga centrale

### Assunzioni
- Il terminale usa un carattere a larghezza fissa
- L'utente inserisce un numero intero

### Variabili di supporto

| Variabile          | Tipo        | Significato                               |
|--------------------|-------------|-------------------------------------------|
| `riga`, `colonna`  | `int`       | Variabili dei cicli esterno e interno     |
| `bordo`            | `int` (0/1) | Il punto appartiene al bordo del quadrato |

Per ogni figura si ricava, riga per riga, quanti spazi e quanti asterischi
stampare:

| Figura | Spazi nella riga r | Asterischi nella riga r |
|--------|--------------------|-------------------------|
| Triangolo | 0 | r |
| Piramide | altezza − r | 2r − 1 |
| Quadrato vuoto | — | `*` solo se r o la colonna è la prima o l'ultima |
| Rombo | come la piramide, poi le righe da altezza − 1 a 1 | |

### Algoritmo in linguaggio naturale
1. Leggere l'altezza ripetendo finché non è tra 2 e 20.
2. Triangolo: per ogni riga r stampare r asterischi e andare a capo.
3. Piramide: per ogni riga r stampare `altezza − r` spazi e `2r − 1` asterischi.
4. Quadrato: per ogni riga e ogni colonna stampare `* ` se il punto è sul
   bordo (prima o ultima riga, prima o ultima colonna), altrimenti due spazi.
5. Rombo: stampare la piramide, poi le righe da `altezza − 1` a 1 con le
   stesse formule (piramide capovolta senza ripetere la riga centrale).

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Altezza 4
- **Input:** 4
- **Output atteso:** triangolo di 4 righe, piramide con base di 7 asterischi,
  quadrato 4 × 4 vuoto, rombo di 7 righe

### Test 2 – Altezza minima
- **Cosa si verifica:** il caso limite inferiore dell'intervallo
- **Input:** 2
- **Output atteso:** triangolo di 2 righe, piramide con base di 3 asterischi,
  quadrato 2 × 2 tutto pieno (ogni punto è sul bordo), rombo di 3 righe

### Test 3 – Altezza fuori intervallo
- **Input:** 1 oppure 50
- **Output atteso:** la richiesta viene ripetuta
