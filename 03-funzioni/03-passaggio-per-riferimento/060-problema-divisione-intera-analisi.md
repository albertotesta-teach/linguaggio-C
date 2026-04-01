# Analisi – 060-problema-divisione-intera.c

## 1. Problema
Due conversioni pratiche producono ciascuna due risultati interi che derivano
dalla stessa divisione e non possono essere separati in chiamate distinte senza
inefficienza. Il passaggio per riferimento permette a ciascuna funzione di
scrivere entrambi i risultati direttamente nelle variabili del chiamante.

Conversione 1: secondi totali → ore, minuti e secondi residui (formato HH:MM:SS)
Conversione 2: importo in centesimi → euro e centesimi residui

## 2. Analisi generale e struttura dati

| Funzione | Firma | Descrizione |
|---|---|---|
| `secondi_in_hms` | `void(int, int*, int*, int*)` | Converte secondi in h, min, sec |
| `centesimi_in_euro` | `void(int, int*, int*)` | Converte centesimi in euro e resto |
| `stampa_durata` | `void(int)` | Stampa secondi e forma HH:MM:SS |
| `stampa_importo` | `void(int)` | Stampa centesimi e forma EUR+cent |

| Variabile | Tipo | Ruolo |
|---|---|---|
| `secondi_tot` | int (IN) | Durata totale in secondi |
| `ore`, `minuti`, `sec` | int* (OUT) | Componenti del tempo |
| `centesimi_tot` | int (IN) | Importo totale in centesimi |
| `euro`, `centesimi` | int* (OUT) | Componenti dell'importo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conversione di una durata tipica

**a) Input** – `secondi_tot = 3725`

**b) Output** – `3725 secondi → 1h 02m 05s`

**c) Variabili di supporto** – `ore`, `minuti`, `sec` locali a `stampa_durata`, popolate dalla funzione

**d) Vincoli** – `secondi_tot >= 0`; valori negativi non sono gestiti

**e) Assunzioni** – il valore in input è espresso in secondi interi non negativi

**f) Algoritmo in linguaggio naturale**
1. `*ore    = secondi_tot / 3600`         (divisione intera)
2. `*minuti = (secondi_tot % 3600) / 60`  (resto della prima divisione, poi diviso 60)
3. `*sec    = secondi_tot % 60`           (resto della divisione per 60)

### Caso d'uso 2 – Conversione di un importo

**a) Input** – `centesimi_tot = 1275`

**b) Output** – `1275 centesimi → 12 EUR e 75 cent`

**c) Variabili di supporto** – `euro`, `centesimi` locali a `stampa_importo`

**d) Vincoli** – `centesimi_tot >= 0`

**e) Assunzioni** – l'importo è espresso in centesimi interi non negativi

**f) Algoritmo in linguaggio naturale**
1. `*euro      = centesimi_tot / 100`   (parte intera)
2. `*centesimi = centesimi_tot % 100`   (resto)

### Caso d'uso 3 – Valori limite e casi particolari

**a) Input** – `secondi_tot = 0`, `secondi_tot = 86399`, `centesimi_tot = 99`

**b) Output**
```
    0 secondi  →  0h 00m 00s
86399 secondi  →  23h 59m 59s
   99 centesimi →  0 EUR e 99 cent
```

**c) Variabili di supporto** – nessuna aggiuntiva

**d) Vincoli** – i risultati devono essere esatti ai limiti (0 e valori massimi per un giorno)

**e) Assunzioni** – i valori di input rientrano in intervalli sensati (non vengono validati)

**f) Algoritmo in linguaggio naturale** – identico ai casi precedenti; l'aritmetica intera gestisce correttamente i casi limite
