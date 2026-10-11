# Analisi – 040-problema-sigle.c

## 1. Problema

La segreteria di una scuola deve scrivere la sigla di molti enti. Il
programma legge il nome completo di un ente e costruisce la sigla con le
iniziali maiuscole delle parole, saltando le parole di 3 lettere o meno
(articoli e preposizioni). Una riga vuota termina il programma.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `riga` | `char[]` | 100 | Nome letto con `fgets` |
| `sigla` | `char[]` | 20 | Sigla costruita |
| `a_capo` | `char *` | — | Posizione del `'\n'` trovato da `strchr` |
| `p` | `const char *` | — | Carattere esaminato |
| `inizio` | `const char *` | — | Prima lettera della parola corrente |
| `s` | `char *` | — | Prossima posizione libera in `sigla` |

| Funzione | Compito |
|----------|---------|
| `crea_sigla(nome, sigla)` | Scrive in `sigla` le iniziali delle parole lunghe |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Parole tutte lunghe

**a) Input** – `Istituto Tecnico Industriale Statale`

**b) Output** – `ITIS`

**c) Variabili di supporto** – `inizio`, `p`, `s`

**d) Vincoli** – la sigla non supera 19 caratteri più `'\0'`

**e) Assunzioni** – lettere senza accento

**f) Algoritmo in linguaggio naturale**
1. Se `*p` è una lettera, salvare `inizio = p` e avanzare fino alla prima
   non-lettera.
2. Se `p - inizio > 3`, scrivere in `*s` la maiuscola di `*inizio` e
   avanzare `s`.
3. Altrimenti avanzare `p` di un carattere.

### Caso d'uso 2 – Parole brevi e apostrofo

**a) Input** – `Ente Nazionale per l'Aviazione Civile`

**b) Output** – `ENAC`

**c) Variabili di supporto** – lunghezza `p - inizio`

**d) Vincoli** – "per" (3) e "l" (1) si saltano

**e) Assunzioni** – l'apostrofo separa le parole

**f) Algoritmo in linguaggio naturale** – lo stesso del caso 1: ogni carattere
che non è una lettera chiude la parola.

### Caso d'uso 3 – Fine dell'input

**a) Input** – riga vuota

**b) Output** – il programma termina

**c) Variabili di supporto** – `a_capo`, `continua`

**d) Vincoli** – il `'\n'` di `fgets` va tolto prima del controllo

**e) Assunzioni** – una riga più lunga di 99 caratteri viene spezzata

**f) Algoritmo in linguaggio naturale** – `strchr` trova il `'\n'`; se il
puntatore non è `NULL` si scrive `'\0'` al suo posto con `*a_capo = '\0'`.
