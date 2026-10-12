# Analisi – 040-problema-scheda-libro.c

## 1. Problema

La biblioteca apre la scheda di un libro (titolo, autore, anno, copie possedute, copie in prestito) e registra prestiti e restituzioni. Un prestito è possibile solo se c'è una copia disponibile, una restituzione solo se c'è una copia in prestito. Alla fine il programma stampa i prestiti della sessione.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Libro` | `titolo, autore, anno, copie, in_prestito` | scheda di un titolo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `libro` | `Libro` | — | Scheda del libro |
| `comando` | `char` | — | P, R, S o Q |
| `prestiti_oggi` | `int` | — | Prestiti registrati nella sessione |

| Funzione | Compito |
|----------|---------|
| `main` | Ciclo dei comandi sui campi di `libro` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prestito

**a) Input** – `P` con 2 copie disponibili

**b) Output** – "Prestito registrato. Copie disponibili: 1"

**c) Variabili di supporto** – `libro.in_prestito`

**d) Vincoli** – disponibili = copie - in_prestito > 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – incrementare il campo in_prestito.

### Caso d'uso 2 – Prestito impossibile

**a) Input** – `P` con 0 copie disponibili

**b) Output** – "Nessuna copia disponibile."

**c) Variabili di supporto** – —

**d) Vincoli** – il campo non cambia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare la differenza tra i due campi prima di modificare.

### Caso d'uso 3 – Scheda

**a) Input** – `S`

**b) Output** – titolo, autore (anno), copie, in prestito, disponibili

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampare i campi con l'operatore punto.
