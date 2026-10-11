# Analisi – 040-problema-prenotazione-teatro.c

## 1. Problema

Un teatro ha 5 file (A-E) da 8 posti, alcuni già venduti. L'operatore
inserisce richieste nella forma "fila posto" (es. `C 4`). Il programma deve
prenotare il posto se è libero, segnalare i posti inesistenti e, se il posto
è occupato, proporre il primo posto libero della stessa fila. Alla fine
stampa la mappa aggiornata e il numero di prenotazioni.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `sala` | `int[][]` | 5 × 8 | 0 = libero, 1 = occupato |
| `lettera` | `char` | — | Fila indicata dall'operatore |
| `numero_posto` | `int` | — | Posto da 1 a 8 |
| `riga`, `colonna` | `int` | — | Indici ricavati: `lettera - 'A'`, `numero_posto - 1` |
| `alternativo` | `int` | — | Primo posto libero della fila, -1 se nessuno |
| `prenotati` | `int` | — | Contatore della sessione |

La fila `'Z'` è la sentinella che termina l'inserimento.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prenotazione di un posto libero

**a) Input** – `C 4`

**b) Output** – "Prenotato: fila C, posto 4."

**c) Variabili di supporto** – `riga`, `colonna`, `prenotati`

**d) Vincoli** – la cella diventa 1 e il contatore aumenta

**e) Assunzioni** – fila in maiuscolo

**f) Algoritmo in linguaggio naturale**
1. Leggere la fila; finché non è `'Z'`: leggere il posto.
2. Calcolare `riga` e `colonna`.
3. Se uno dei due indici è fuori dai limiti, segnalare posto inesistente.
4. Altrimenti, se la cella è libera, prenotarla e contarla.
5. Altrimenti cercare il primo posto libero della riga (caso d'uso 2).
6. Leggere la fila successiva.

### Caso d'uso 2 – Posto occupato

**a) Input** – `C 2` (occupato) oppure `B 3` (fila piena)

**b) Output** – "Occupato. Primo posto libero nella fila C: 1" oppure
"Occupato. La fila B e' completa."

**c) Variabili di supporto** – `alternativo`

**d) Vincoli** – la ricerca scorre una sola riga e si ferma al primo posto
libero (condizione `alternativo == -1` nel ciclo)

**e) Assunzioni** – si propone il posto, non lo si prenota automaticamente

**f) Algoritmo in linguaggio naturale**
1. Porre `alternativo = -1`.
2. Per ogni colonna della riga, finché non è trovato: se libero, memorizzarlo.
3. Stampare il posto trovato (numerato da 1) o che la fila è completa.

### Caso d'uso 3 – Posto inesistente

**a) Input** – `A 9`, `F 1` o una fila minuscola

**b) Output** – "Posto inesistente."

**c) Variabili di supporto** – `riga`, `colonna`

**d) Vincoli** – entrambi gli indici vanno controllati prima di accedere a `sala`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 3.
