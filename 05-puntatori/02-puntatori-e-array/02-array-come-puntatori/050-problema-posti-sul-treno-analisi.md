# Analisi – 050-problema-posti-sul-treno.c

## 1. Problema

Una carrozza ha 20 posti in fila, alcuni già occupati. Per ogni gruppo di
persone che chiede posti vicini il programma cerca il primo blocco di posti
liberi consecutivi abbastanza grande, lo prenota e mostra la carrozza
aggiornata; se il blocco non esiste lo segnala. Con 0 il programma termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `posti` | `int[]` | 20 | 1 occupato, 0 libero |
| `k` | `int` | — | Persone del gruppo |
| `i` | `int` | — | Posizione del primo posto trovato, -1 se nessuno |

| Funzione | Compito |
|----------|---------|
| `cerca_liberi(posti, n, k)` | Posizione del primo blocco di `k` posti liberi |
| `occupa(inizio, fine)` | Segna occupati i posti in `[inizio, fine)` |
| `stampa_carrozza(posti, n)` | Mappa dei posti e numero di liberi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Blocco trovato

**a) Input** – `2`

**b) Output** – "Prenotati i posti dal 4 al 5." e mappa aggiornata

**c) Variabili di supporto** – `consecutivi`, `trovato`

**d) Vincoli** – il ciclo si ferma appena `trovato` è diverso da -1

**e) Assunzioni** – si sceglie il primo blocco da sinistra

**f) Algoritmo in linguaggio naturale**
1. Scorrere i posti con `p`, contando quelli liberi consecutivi; un posto
   occupato azzera il conteggio.
2. Quando il conteggio vale `k`, il blocco inizia in `(p - posti) - k + 1`.

### Caso d'uso 2 – Prenotazione di un intervallo

**a) Input** – `i` = 12, `k` = 3

**b) Output** – posti 13, 14, 15 occupati

**c) Variabili di supporto** – `p` dentro `occupa`

**d) Vincoli** – `fine` è escluso: `occupa(posti + 12, posti + 15)`

**e) Assunzioni** – i posti dell'intervallo sono liberi

**f) Algoritmo in linguaggio naturale** – per `p` da `inizio` a `fine`
escluso, `*p = 1`.

### Caso d'uso 3 – Nessun blocco o input non valido

**a) Input** – `4` quando i blocchi liberi sono al massimo di 2; `25`

**b) Output** – "Nessun gruppo di 4 posti vicini libero."; "Numero non valido."

**c) Variabili di supporto** – `i` = -1

**d) Vincoli** – 1 ≤ k ≤ 20

**e) Assunzioni** – un input non numerico termina il programma

**f) Algoritmo in linguaggio naturale** – se `k` è fuori intervallo si
segnala; se la ricerca restituisce -1 non si prenota nulla.
