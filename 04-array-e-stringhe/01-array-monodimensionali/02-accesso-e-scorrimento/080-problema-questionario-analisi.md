# Analisi – 080-problema-questionario.c

## 1. Problema

Un sistema di correzione automatica gestisce un questionario a risposta multipla
di 10 domande (opzioni A/B/C/D). Il programma raccoglie le risposte dello
studente con validazione, le confronta con la chiave, mostra il dettaglio
domanda per domanda e calcola il punteggio finale.

---

## 2. Analisi generale e struttura dati

| Variabile     | Tipo      | Dimensione | Motivazione                                              |
|---------------|-----------|------------|----------------------------------------------------------|
| `chiave`      | `char[]`  | 10         | Risposta corretta per ogni domanda                       |
| `risposte`    | `char[]`  | 10         | Risposta inserita dallo studente per ogni domanda        |
| `valido`      | `int`     | —          | Flag per il ciclo di validazione dell'input              |
| `corrette`    | `int`     | —          | Contatore risposte corrette                              |
| `errate`      | `int`     | —          | Contatore risposte errate                                |
| `punteggio`   | `double`  | —          | Percentuale di risposte corrette                         |
| `esito`       | `char[]`  | 10         | Stringa "OK" o "ERRATA" per ogni riga del riepilogo      |
| `NUM_DOMANDE` | `#define` | 10         | Dimensione degli array e limite dei cicli                |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Raccolta e validazione delle risposte

**a) Input** — Caratteri da tastiera, uno per domanda.
**b) Output** — Prompt per ogni domanda; messaggio di errore se input non valido.
**d) Vincoli** — `" %c"` con spazio consuma newline residui. Conversione minuscolo→maiuscolo con `- 32`. Nessun `break`.
**f) Algoritmo**
```
Per i da 0 a NUM_DOMANDE - 1:
  valido = 0.
  Mentre !valido:
    Leggere risposte[i].
    Se minuscolo: convertire in maiuscolo.
    Se A/B/C/D: valido = 1. Altrimenti: stampare errore.
```

---

### Caso d'uso 2 – Correzione e riepilogo

**a) Input** — Array `risposte` e `chiave`.
**b) Output**
```
=== CORREZIONE ===
  Dom. | Risposta | Corretta | Esito
     1 |    A     |    A     | OK
     2 |    B     |    C     | ERRATA
```
**d) Vincoli** — `corrette + errate == NUM_DOMANDE`. `esito` costruita manualmente con `'\0'` finale.
**f) Algoritmo**
```
Per i da 0 a NUM_DOMANDE - 1:
  Se risposte[i] == chiave[i]: esito = "OK", corrette++.
  Altrimenti: esito = "ERRATA", errate++.
  Stampare riga.
```

---

### Caso d'uso 3 – Punteggio e verdetto

**a) Input** — `corrette`, `NUM_DOMANDE`.
**b) Output**
```
  Punteggio : 70%
  Esito     : PROMOSSO
```
**d) Vincoli** — Divisione floating point: `(double)corrette / NUM_DOMANDE`. Soglia promozione: 60%.
**f) Algoritmo**
```
punteggio = (double)corrette / NUM_DOMANDE * 100.0.
Se punteggio >= 60.0: PROMOSSO. Altrimenti: NON PROMOSSO.
```
