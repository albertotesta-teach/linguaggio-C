# Analisi – 040-problema-resto-in-monete.c

## 1. Problema

Il distributore di bevande della scuola ha una scorta limitata di monete
per ogni taglio. Per ogni acquisto (prezzo e importo inserito, in
centesimi) calcola il resto usando prima le monete più grandi, senza
superare quelle disponibili. Se non riesce a dare il resto esatto annulla
la vendita. Dopo ogni operazione mostra la scorta. Con `0 0` termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tagli` | `int[]` | 6 | Valori delle monete in centesimi, dal più grande |
| `scorta` | `int[]` | 6 | Monete disponibili per taglio |
| `usate` | `int[]` | 6 | Monete da dare per taglio (uscita della funzione) |
| `mancante` | `int` | — | Centesimi che non si riescono a dare (uscita) |
| `prezzo`, `inserito` | `int` | — | Dati dell'acquisto |

| Funzione | Compito |
|----------|---------|
| `eroga_resto(resto, tagli, scorta, usate, &mancante)` | Calcola le monete; restituisce 1 se il resto è esatto |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Resto esatto

**a) Input** – `130 500`

**b) Output** – resto 3.70: 1 × 200, 1 × 100, 1 × 50, 1 × 20; scorta aggiornata

**c) Variabili di supporto** – `usate`, `mancante` = 0

**d) Vincoli** – per ogni taglio non si usano più monete di quelle in scorta

**e) Assunzioni** – si usa sempre la moneta più grande possibile

**f) Algoritmo in linguaggio naturale**
1. Per ogni taglio calcolare `resto / taglio`, limitato alla scorta.
2. Scriverlo in `usate[t]` e togliere il valore dal resto.
3. Alla fine `*mancante = resto` e restituire `resto == 0`.
4. Solo se l'esito è 1 il main toglie le monete dalla scorta.

### Caso d'uso 2 – Monete grandi finite

**a) Input** – `120 200` dopo il primo acquisto (nessuna moneta da 50)

**b) Output** – resto 0.80: 3 × 20, 2 × 10

**c) Variabili di supporto** – `n` limitato a `scorta[t]`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – quando un taglio è esaurito si passa
al successivo con il resto ancora da dare.

### Caso d'uso 3 – Resto impossibile

**a) Input** – `30 100` con solo monete da 100, 200 e una da 5

**b) Output** – "Resto non disponibile (mancano 65 cent): vendita annullata."

**c) Variabili di supporto** – `mancante`

**d) Vincoli** – la scorta non deve cambiare

**e) Assunzioni** – l'algoritmo che parte dalle monete grandi può fallire anche
in rari casi in cui una combinazione diversa esisterebbe

**f) Algoritmo in linguaggio naturale** – la funzione legge la scorta come
`const int *` e non la modifica; il main non aggiorna nulla se l'esito è 0.
