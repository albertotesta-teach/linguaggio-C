# Analisi – 040-problema-diario-delle-uscite.c

## 1. Problema

Il coordinatore annota le uscite didattiche della classe man mano che si svolgono, una riga "gg/mm meta" per uscita, nel file diario.txt. Ogni esecuzione deve aggiungere le nuove voci senza cancellare quelle già scritte: il file si apre in modalità "a". Alla fine il programma rilegge il diario e lo stampa con le righe numerate.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `diario` | `FILE *` | — | File aperto in "a": scrittura sempre in fondo |
| `data` | `char[]` | 16 | Data letta come testo, o FINE |
| `meta` | `char[]` | 60 | Resto della riga, spazi compresi |
| `giorno`, `mese` | `int` | — | Data convertita con sscanf |
| `aggiunte` | `int` | — | Voci scritte in questa esecuzione |

| Funzione | Compito |
|----------|---------|
| `data_valida(giorno, mese)` | Giorno esistente nel mese |
| `stampa_numerata(nome)` | Riapre il file in "r" e stampa le righe numerate; 0 se non si apre |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prima esecuzione

**a) Input** – `12/10 Museo Egizio di Torino`, `31/11 Gita sul Po`, `03/11 Laboratorio di chimica all'universita'`, `FINE`

**b) Output** – "data non valida: 31/11"; 2 voci aggiunte; diario di 2 righe

**c) Variabili di supporto** – `aggiunte`

**d) Vincoli** – meta fino a 59 caratteri

**e) Assunzioni** – le voci arrivano in ordine di data

**f) Algoritmo in linguaggio naturale** – fopen "a" crea il file; per ogni voce valida fprintf in fondo; fclose; stampa_numerata.

### Caso d'uso 2 – Seconda esecuzione

**a) Input** – `20/11 Biblioteca civica`, `FINE`

**b) Output** – 1 voce aggiunta; il diario ha 3 righe

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – il file esiste già

**f) Algoritmo in linguaggio naturale** – "a" non cancella: la nuova voce va dopo le precedenti.

### Caso d'uso 3 – File non apribile

**a) Input** – cartella senza permessi

**b) Output** – "Impossibile aprire diario.txt" su stderr

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – con diario == NULL non si legge nessuna voce.
