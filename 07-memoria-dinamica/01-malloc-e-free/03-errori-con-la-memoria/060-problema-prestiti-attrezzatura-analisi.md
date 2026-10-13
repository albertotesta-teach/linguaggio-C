# Analisi – 060-problema-prestiti-attrezzatura.c

## 1. Problema

Il magazzino di educazione fisica registra i prestiti. Ogni prestito è una struct allocata all'uscita e liberata al rientro; l'array di puntatori usa NULL per lo scaffale libero. Mettere NULL dopo free permette di riusare lo scaffale, di riconoscere un secondo rientro e di liberare a fine programma i prestiti rimasti aperti. Due contatori verificano che nessun blocco resti in memoria.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Prestito` | `oggetto[16], studente[20]` | un oggetto in prestito |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `scaffale` | `Prestito *[]` | 4 puntatori | NULL = scaffale libero |
| `oggetto`, `studente` | `char[]` | 16, 20 | Dati dell'uscita |
| `allocati`, `liberati` | `int` | — | Controllo finale |

| Funzione | Compito |
|----------|---------|
| `primo_libero(scaffale)` | Primo puntatore NULL o -1 |
| `elenco(scaffale)` | Prestiti in corso e scaffali liberi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Uscite

**a) Input** – `U pallone Marta`, `U racchetta Luca`, `U cronometro Sara`

**b) Output** – "pallone a Marta: scaffale 1" ...

**c) Variabili di supporto** – `scaffale[k]`

**d) Vincoli** – 4 scaffali

**e) Assunzioni** – nomi di una parola

**f) Algoritmo in linguaggio naturale** – primo scaffale NULL, malloc, copia dei dati, allocati++.

### Caso d'uso 2 – Rientro e secondo rientro

**a) Input** – `R 2` due volte

**b) Output** – "rientrato racchetta da Luca", poi "Scaffale 2 vuoto: niente da far rientrare."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – free, scaffale = NULL, liberati++; al secondo rientro il puntatore è NULL: nessun doppio free.

### Caso d'uso 3 – Riuso e registro pieno

**a) Input** – `U pallone Paolo`, `U corda Anna`, `U palla Rita`

**b) Output** – Paolo allo scaffale 2; "Registro pieno"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – lo scaffale liberato torna disponibile.

### Caso d'uso 4 – Chiusura

**a) Input** – `Q`

**b) Output** – oggetti da recuperare; "blocchi allocati 5, liberati 5: nessun blocco rimasto in memoria"

**c) Variabili di supporto** – `allocati`, `liberati`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – free di ogni puntatore non NULL e confronto dei contatori.
