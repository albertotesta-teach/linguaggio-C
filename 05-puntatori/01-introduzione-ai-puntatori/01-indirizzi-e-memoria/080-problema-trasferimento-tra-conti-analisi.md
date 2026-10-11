# Analisi – 080-problema-trasferimento-tra-conti.c

## 1. Problema

Il bar della scuola gestisce tre tessere prepagate. La funzione
`trasferisci` sposta credito da una tessera a un'altra ricevendone gli
indirizzi. Deve rifiutare il trasferimento verso la stessa tessera, gli
importi non positivi e quelli superiori al credito disponibile.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tessera_1`, `tessera_2`, `tessera_3` | `int` | — | Credito in centesimi |
| `esiti` | `char[][]` | 4 × 32 | Testo di ogni codice di esito |
| `esito` | `int` | — | Codice restituito da `trasferisci` |

| Funzione | Compito |
|----------|---------|
| `trasferisci(int *da, int *a, int importo)` | Controlli e spostamento del credito |
| `stampa_tessere` | Stampa i tre crediti in euro |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Stesso valore, variabili diverse

**a) Input** – `tessera_1` e `tessera_3` valgono entrambe 1500

**b) Output** – stesso credito: sì; stessa tessera: no

**c) Variabili di supporto** – nessuna

**d) Vincoli** – `tessera_1 == tessera_3` confronta i valori,
`&tessera_1 == &tessera_3` confronta gli indirizzi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampare i due confronti.

### Caso d'uso 2 – Trasferimento valido

**a) Input** – da tessera 1 a tessera 2, 600 centesimi

**b) Output** – "eseguito"; crediti 9.00 e 10.00

**c) Variabili di supporto** – `*da`, `*a`

**d) Vincoli** – le modifiche avvengono tramite gli indirizzi ricevuti

**e) Assunzioni** – importi in centesimi interi

**f) Algoritmo in linguaggio naturale** – `*da = *da - importo`, `*a = *a + importo`.

### Caso d'uso 3 – Trasferimenti rifiutati

**a) Input** – da 2 a 2; da 2 a 3 per 5000; da 3 a 1 per -100

**b) Output** – "stessa tessera"; "credito insufficiente"; "importo non valido"

**c) Variabili di supporto** – `esito`

**d) Vincoli** – il controllo `da == a` viene per primo; una sola `return`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Se gli indirizzi coincidono: stessa tessera.
2. Altrimenti, se l'importo non è positivo: importo non valido.
3. Altrimenti, se il credito è insufficiente: rifiuto.
4. Altrimenti eseguire lo spostamento.
