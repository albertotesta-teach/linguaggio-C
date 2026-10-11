# Analisi – 070-problema-figure-ascii.c

## 1. Problema

Disegnare con il carattere `*` quattro figure di altezza scelta dall'utente
(da 2 a 20): triangolo rettangolo, piramide centrata, quadrato vuoto e rombo.
È lo stesso problema di un'insegna a matrice di LED, che accende punti su una
griglia di righe e colonne.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `altezza` | `int` | Numero di righe delle figure |
| `riga`, `colonna` | `int` | Variabili dei cicli esterno e interno |
| `bordo` | `int` (0/1) | Il punto appartiene al bordo del quadrato |

Per ogni figura si ricava, riga per riga, quanti spazi e quanti asterischi
stampare:

| Figura | Spazi nella riga r | Asterischi nella riga r |
|--------|--------------------|-------------------------|
| Triangolo | 0 | r |
| Piramide | altezza − r | 2r − 1 |
| Quadrato vuoto | — | `*` solo se r o la colonna è la prima o l'ultima |
| Rombo | come la piramide, poi le righe da altezza − 1 a 1 | |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Figure di altezza 4

**a) Input** – altezza 4

**b) Output** – triangolo di 4 righe, piramide con base di 7 asterischi,
quadrato 4 × 4 vuoto, rombo di 7 righe

**c) Variabili di supporto** – `bordo`

**d) Vincoli** – l'a capo si stampa alla fine di ogni riga, fuori dai cicli interni

**e) Assunzioni** – il terminale usa un carattere a larghezza fissa

**f) Algoritmo in linguaggio naturale**
1. Leggere l'altezza ripetendo finché non è tra 2 e 20.
2. Triangolo: per ogni riga r stampare r asterischi e andare a capo.
3. Piramide: per ogni riga r stampare `altezza − r` spazi e `2r − 1` asterischi.
4. Quadrato: per ogni riga e ogni colonna stampare `* ` se il punto è sul
   bordo (prima o ultima riga, prima o ultima colonna), altrimenti due spazi.
5. Rombo: stampare la piramide, poi le righe da `altezza − 1` a 1 con le
   stesse formule (piramide capovolta senza ripetere la riga centrale).

### Caso d'uso 2 – Altezza fuori intervallo

**a) Input** – 1 oppure 50

**b) Output** – la richiesta viene ripetuta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – con altezza 1 le figure degenerano in un punto; oltre 20 il
rombo supera la larghezza abituale del terminale

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 1.
