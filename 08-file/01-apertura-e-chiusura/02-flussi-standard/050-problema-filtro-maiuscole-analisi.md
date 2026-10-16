# Analisi – 050-problema-filtro-maiuscole.c

## 1. Problema

I cartelli dell'open day si stampano in maiuscolo. Il filtro legge stdin carattere per carattere, converte le minuscole con toupper e scrive su stdout; non apre file, quindi si usa con la redirezione. Il resoconto e l'avviso sulle lettere accentate vanno su stderr, così su stdout esce solo il testo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `c` | `int` | — | Carattere letto o EOF |
| `letti`, `convertite` | `int` | — | Conteggi |
| `non_ascii` | `int` | — | Byte oltre 127 (lettere accentate) |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Da tastiera

**a) Input** – due righe, poi Ctrl+D

**b) Output** – le righe in maiuscolo; "[filtro] caratteri letti: 79, lettere convertite: 56"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – fine dati con Ctrl+D

**f) Algoritmo in linguaggio naturale** – fgetc(stdin) fino a EOF; fputc(toupper(c), stdout).

### Caso d'uso 2 – Con redirezione

**a) Input** – `< diario.txt > stampa.txt`

**b) Output** – stampa.txt in maiuscolo; a video solo il resoconto

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stderr non è rediretto da >.

### Caso d'uso 3 – Lettere accentate

**a) Input** – testo con à, è

**b) Output** – avviso su stderr

**c) Variabili di supporto** – `non_ascii`

**d) Vincoli** – —

**e) Assunzioni** – codifica UTF-8 o Latin-1

**f) Algoritmo in linguaggio naturale** – toupper non converte i byte non ASCII.
