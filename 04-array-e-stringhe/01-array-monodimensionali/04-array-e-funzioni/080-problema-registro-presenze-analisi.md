# Analisi – 080-problema-registro-presenze.c

## 1. Problema

Un ufficio HR monitora le presenze di 6 dipendenti su 22 giorni lavorativi.
Il programma deve stampare un prospetto con percentuale e stato, identificare
il più e meno presente e contare quanti dipendenti sono sotto la soglia dell'80%.

---

## 2. Analisi generale e struttura dati

| Variabile             | Tipo         | Dimensione | Motivazione                                          |
|-----------------------|--------------|------------|------------------------------------------------------|
| `nomi`                | `char[][]`   | 6 × 20     | Nome di ogni dipendente                              |
| `presenze`            | `int[]`      | 6          | Giorni di presenza; parallelo a `nomi`               |
| `GIORNI_LAVORATIVI`   | `#define`    | 22         | Denominatore per il calcolo della percentuale        |
| `SOGLIA_PRESENZA`     | `#define`    | 80.0       | Soglia minima accettabile                            |
| `DIPENDENTI`          | `#define`    | 6          | Dimensione degli array e limite dei cicli            |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Prospetto con stato

**a) Input** — Array `nomi`, `presenze`, costanti `GIORNI_LAVORATIVI`, `SOGLIA_PRESENZA`.
**b) Output**
```
  Dipendente       | Giorni | Perc.  | Stato
  -----------------|--------|--------|----------
  Rossi Anna       |   22   | 100.0% | REGOLARE
  Bianchi Carlo    |   18   |  81.8% | REGOLARE
  Ferrari Marco    |   15   |  68.2% | ATTENZIONE
```
**c) Funzione coinvolta**
`stampa_prospetto`: chiama `percentuale_presenza` per ogni dipendente.
**d) Vincoli**
- `percentuale_presenza` è una funzione a sé per evitare duplicazione
  tra `stampa_prospetto` e `conta_sotto_soglia`.
- La stringa `avviso` è costruita manualmente senza `strcpy`.

---

### Caso d'uso 2 – Dipendente più e meno presente

**a) Input** — Array `presenze`.
**b) Output**
```
Piu' presente   : Rossi Anna (22 gg - 100.0%)
Meno presente   : Ferrari Marco (15 gg - 68.2%)
```
**c) Funzioni coinvolte**
`dipendente_piu_presente` e `dipendente_meno_presente`: entrambe restituiscono
un indice; il `main` usa l'indice per accedere a `nomi[]` e chiama
`percentuale_presenza` per la stampa.

**d) Vincoli**
- Le funzioni restituiscono l'indice, non il valore: il `main` accede ai dati
  tramite indice, mantenendo la separazione tra logica e presentazione.

---

### Caso d'uso 3 – Conteggio sotto soglia

**a) Input** — Array `presenze`, costanti `GIORNI_LAVORATIVI`, `SOGLIA_PRESENZA`.
**b) Output**
```
Sotto soglia    : 2 dipendenti su 6
```
**c) Funzione coinvolta**
`conta_sotto_soglia`: chiama `percentuale_presenza` internamente per ogni
elemento, evitando di duplicare la formula.

**d) Vincoli**
- La soglia è `SOGLIA_PRESENZA` (80.0); il confronto usa `<` (non `<=`).
- `percentuale_presenza` è la stessa funzione usata in `stampa_prospetto`:
  un solo punto di definizione della formula garantisce coerenza.

**f) Algoritmo in linguaggio naturale**
```
contatore = 0.
Per i da 0 a n-1:
  Se percentuale_presenza(presenze[i], giorni_totali) < soglia:
    contatore++.
return contatore.
```
