# Analisi – 040-problema-riga-di-lunghezza-qualsiasi.c

## 1. Problema

Le risposte aperte del questionario di fine anno possono essere lunghe un paragrafo. La funzione leggi_riga legge un carattere alla volta con getchar in un blocco che parte da 16 byte e cresce di 16 quando è pieno, poi riduce il blocco alla lunghezza esatta. Il programma conserva le risposte in un array di puntatori e stampa un'anteprima di ognuna e la più lunga per intero.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `risposte` | `char *[]` | 10 puntatori | Risposte raccolte |
| `riga` | `char *` | strlen + 1 (heap) | Risposta restituita da leggi_riga |
| `ingrandimenti` | `int` | — | realloc di crescita per la riga |
| `piu_lunga` | `int` | — | Indice della risposta più lunga |

| Funzione | Compito |
|----------|---------|
| `leggi_riga(&ingrandimenti)` | Lettura senza limiti di lunghezza; NULL a fine input |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Risposta breve

**a) Input** – `Piu' laboratori.`

**b) Output** – "16 caratteri, ingrandimenti del blocco: 1"

**c) Variabili di supporto** – `capienza`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – quando lunghezza + 1 == capienza, realloc di altri 16 byte.

### Caso d'uso 2 – Risposta lunga

**a) Input** – una riga di 131 caratteri

**b) Output** – "131 caratteri, ingrandimenti del blocco: 8"; anteprima di 30 caratteri con "..."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – alla fine realloc a lunghezza + 1.

### Caso d'uso 3 – Riga vuota e FINE

**a) Input** – invio; `FINE`

**b) Output** – nessuna risposta aggiunta

**c) Variabili di supporto** – —

**d) Vincoli** – al massimo 10 risposte

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il blocco restituito si libera subito.

### Caso d'uso 4 – Fine dell'input senza a capo

**a) Input** – `abc` e fine

**b) Output** – la riga viene comunque restituita

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – NULL solo se l'input finisce senza caratteri.
