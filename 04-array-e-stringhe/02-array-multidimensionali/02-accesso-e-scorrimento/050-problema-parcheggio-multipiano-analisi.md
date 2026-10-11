# Analisi – 050-problema-parcheggio-multipiano.c

## 1. Problema

Un parcheggio di 3 piani da 6 posti registra in ogni posto il numero di
tessera dell'auto, oppure 0 se il posto è libero. Da un menu ripetuto si
gestiscono ingressi (assegnazione del primo posto libero), uscite (ricerca
della tessera e liberazione del posto) e la visualizzazione dello stato.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `parcheggio` | `int[][]` | 3 × 6 | Tessera dell'auto o 0 (`LIBERO`) |
| `scelta` | `int` | — | Voce del menu |
| `tessera` | `int` | — | Tessera in ingresso o in uscita |
| `trovato` | `int` (0/1) | — | Flag che ferma le ricerche |
| `piano_trovato`, `posto_trovato` | `int` | — | Posizione individuata |
| `liberi_piano` | `int` | — | Contatore per la visualizzazione |

La matrice contiene dati (le tessere) e non solo uno stato 0/1: lo stesso
valore 0 indica il posto libero, quindi la tessera 0 non è ammessa.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ingresso

**a) Input** – scelta 1, tessera 1500

**b) Output** – "Tessera 1500: piano 0, posto 3."

**c) Variabili di supporto** – `trovato`, `piano_trovato`, `posto_trovato`

**d) Vincoli** – il primo posto libero si cerca per righe (piano 0, poi 1,
poi 2) e la ricerca si ferma al primo trovato grazie al flag nelle
condizioni di entrambi i cicli

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Leggere la tessera; porre `trovato = 0`.
2. Per ogni piano e ogni posto, finché non trovato: se la cella vale 0,
   memorizzare la posizione e porre `trovato = 1`.
3. Se trovato, scrivere la tessera nella cella e stampare la posizione;
   altrimenti segnalare che il parcheggio è completo.

### Caso d'uso 2 – Uscita

**a) Input** – scelta 2, tessera 1302 (presente) oppure 999 (assente)

**b) Output** – "Uscita registrata: liberato piano 1, posto 3." oppure
"Tessera 999 non presente nel parcheggio."

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – la tessera 0 non libera alcun posto

**e) Assunzioni** – ogni tessera compare al più una volta

**f) Algoritmo in linguaggio naturale**
1. Leggere la tessera e cercarla con lo stesso schema del caso 1.
2. Se trovata (e diversa da 0), porre la cella a 0 e stampare la posizione;
   altrimenti segnalare l'assenza.

### Caso d'uso 3 – Stato

**a) Input** – scelta 3

**b) Output** – una riga per piano, dall'alto in basso, con tessere o `----`
e posti liberi

**c) Variabili di supporto** – `liberi_piano`

**d) Vincoli** – i piani si stampano in ordine inverso, come in un edificio

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni piano dal più alto: stampare
le celle contando quelle libere, poi il conteggio.
