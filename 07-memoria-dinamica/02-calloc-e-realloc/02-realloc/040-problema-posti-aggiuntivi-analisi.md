# Analisi – 040-problema-posti-aggiuntivi.c

## 1. Problema

Il corso pomeridiano di fotografia parte con un certo numero di posti; la
segreteria può aggiungerne o toglierne. Il blocco degli iscritti cambia
dimensione con `realloc` dentro `cambia_capienza`, che aggiorna puntatore
e capienza solo se `realloc` riesce. Non si possono togliere posti già
occupati.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `capienza` | `int` | Posti iniziali, da 1 a 60 |
| `comando` | `char` | `I nome classe` iscrivi, `A k` aggiungi posti, `T k` togli posti, `E` elenco, `Q` fine (anche minuscoli) |

### Output

- `iscrizione di nome (n/capienza)`, `Corso pieno (C posti): nome in
  attesa.`, `Dati non validi.`
- `Nuova capienza: C posti (B byte)`, `Al massimo 60 posti.`,
  `Posti liberi solo L: non se ne possono togliere k.`,
  `Il corso deve avere almeno un posto.`, `Numero non valido.`,
  `Memoria insufficiente: capienza invariata.`
- `E`: gli iscritti e `posti liberi: L su C`.

### Vincoli

- `cambia_capienza(&iscritti, &capienza, nuova)`: il risultato di
  `realloc` va in un puntatore temporaneo; se è `NULL` il blocco vecchio
  resta valido e nulla cambia.
- Capienza tra il numero di iscritti (e almeno 1) e 60.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Il nome è una sola parola; classe al massimo 3 caratteri.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Iscritto` | `typedef struct { char nome[20]; char classe[4]; } Iscritto;` | Uno studente |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `iscritti` | `Iscritto *` | Blocco ridimensionabile |
| `capienza`, `n` | `int` | Posti e iscritti |
| `k` | `int` | Posti da aggiungere o togliere |

| Funzione | Compito |
|----------|---------|
| `cambia_capienza(iscritti, capienza, nuova)` | `realloc` sicura; 0 se fallisce |

### Algoritmo in linguaggio naturale

1. Leggere la capienza e allocare il blocco.
2. Finché il comando non è `Q`: leggere il comando in maiuscolo; iscrivere
   se c'è posto; aggiungere o togliere posti dopo i controlli; stampare
   l'elenco; scartare il resto della riga.
3. Liberare il blocco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Capienza che cambia

- **Input:** `2`, `I Rossi 3A`, `i Bianchi 2B`, `I Verdi 1C`, `A 2`,
  `I Verdi 1C`, `T 3`, `T 1`, `E extra`, `A 70`, `A x`, `I Neri QUARTA`,
  `X`, `Q`
- **Valori intermedi attesi:** `Iscritto` di 24 byte: 4 posti = 96 byte,
  3 posti = 72 byte.
- **Output atteso:**
  ```
    iscrizione di Rossi (1/2)
    iscrizione di Bianchi (2/2)
    Corso pieno (2 posti): Verdi in attesa.
    Nuova capienza: 4 posti (96 byte)
    iscrizione di Verdi (3/4)
    Posti liberi solo 1: non se ne possono togliere 3.
    Nuova capienza: 3 posti (72 byte)
     1. Rossi        3A
     2. Bianchi      2B
     3. Verdi        1C
    posti liberi: 0 su 3
    Al massimo 60 posti.
    Numero non valido.
    Dati non validi.
    Comando sconosciuto.
  ```
