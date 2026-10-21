# Analisi – 050-problema-distribuzione-voti.c

## 1. Problema

Il coordinatore di classe vuole analizzare la distribuzione dei voti di un test
tra 20 studenti, suddividendoli in fasce di rendimento. Il programma legge i
voti da tastiera, conta quanti cadono in ciascuna fascia, mostra la distribuzione
con percentuali e istogramma e produce un riepilogo sui sufficienti e insufficienti.

---

## 2. Analisi

### Input

| Variabile | Tipo  | Descrizione                               |
|-----------|-------|-------------------------------------------|
| `voto`    | `int` | Voto di uno studente (1–10), letto 20 volte |

### Output
- Una tabella con, per ogni fascia, il numero di studenti, la percentuale
  (un decimale) e un istogramma di asterischi;
- il numero e la percentuale di studenti insufficienti (voto 1–5) e
  sufficienti (voto 6–10).

| Fascia | Voti | Indice |
|--------|------|--------|
| Insufficiente | 1–4 | 0 |
| Mediocre | 5 | 1 |
| Sufficiente | 6 | 2 |
| Discreto | 7 | 3 |
| Buono | 8 | 4 |
| Ottimo | 9–10 | 5 |

### Vincoli
- Ogni voto è compreso tra 1 e 10: un valore fuori intervallo viene
  segnalato e richiesto di nuovo
- La mappatura voto → fascia copre tutti i voti validi, senza sovrapposizioni
  e senza vuoti
- La somma dei contatori è sempre 20, e insufficienti + sufficienti = 20
- La soglia di sufficienza è 6 inclusa: gli insufficienti sono le fasce 0 e 1
- Le percentuali si calcolano con una divisione reale
- Il valore restituito da `scanf` si controlla: un testo non numerico è un
  voto non valido e il resto della riga si scarta con `getchar`; se
  l'input termina prima dei 20 voti (EOF) l'analisi viene annullata

### Assunzioni
- Le fasce sono fissate a priori

### Variabili di supporto

Il punto chiave è la **mappatura voto → indice di fascia** con una catena
`if/else if`: il voto viene classificato e si incrementa direttamente la cella
corrispondente dell'array dei contatori.

| Variabile       | Tipo       | Dimensione | Descrizione                                   |
|-----------------|------------|------------|-----------------------------------------------|
| `contatori`     | `int[]`    | 6          | Un contatore per ciascuna fascia              |
| `indice_fascia` | `int`      | —          | Fascia determinata dalla mappatura            |
| `valido`        | `int`      | —          | Flag del ciclo di validazione                 |
| `percentuale`   | `double`   | —          | Percentuale della fascia sul totale           |
| `insufficienti`, `sufficienti` | `int` | — | Riepilogo finale                           |
| `NUM_STUDENTI`  | `#define`  | 20         | Numero di voti da inserire                    |
| `NUM_FASCE`     | `#define`  | 6          | Numero di fasce                               |

### Algoritmo in linguaggio naturale
1. Inizializzare tutti i contatori a 0.
2. Per ciascuno dei 20 studenti:
   a. leggere il voto ripetendo finché non è compreso tra 1 e 10;
   b. determinare l'indice di fascia con la catena `if/else if`;
   c. incrementare `contatori[indice_fascia]`.
3. Per ogni fascia calcolare la percentuale `contatori[i] / 20 × 100` e
   stampare l'etichetta della fascia (scelta con `if/else if`), il
   contatore, la percentuale e gli asterischi.
4. Calcolare `insufficienti = contatori[0] + contatori[1]` e
   `sufficienti = 20 − insufficienti`, e stamparli con le percentuali.

---

## 3. Casi di test

Per ogni caso si esegue il programma con i 20 voti indicati e si confronta
quanto stampato con l'output atteso.

### Test 1 – Classe con tutte le fasce
- **Input:** 3 4 2 5 5 6 6 6 6 6 7 7 7 7 8 8 8 8 9 10
- **Output atteso:**
```
  Insuff. (1-4) |   3 | 15.0% | ***
  Mediocre (5)  |   2 | 10.0% | **
  Suffic.  (6)  |   5 | 25.0% | *****
  Discreto (7)  |   4 | 20.0% | ****
  Buono    (8)  |   4 | 20.0% | ****
  Ottimo (9-10) |   2 | 10.0% | **

Studenti con voto insufficiente: 5 su 20 (25%)
Studenti con voto sufficiente  : 15 su 20 (75%)
```

### Test 2 – Voti ai confini delle fasce
- **Cosa si verifica:** 4 è insufficiente, 5 mediocre, 6 sufficiente
- **Input:** sette volte 4, sei volte 5, sette volte 6
- **Output atteso:** Insuff. 7 (35.0%), Mediocre 6 (30.0%), Suffic. 7
  (35.0%), le altre fasce a 0 senza asterischi;
  `Studenti con voto insufficiente: 13 su 20 (65%)` e
  `Studenti con voto sufficiente  : 7 su 20 (35%)`

### Test 3 – Voti non validi e una sola fascia
- **Cosa si verifica:** la validazione e una fascia al 100%
- **Input:** 0, 11 (rifiutati), poi 20 volte il voto 10
- **Output atteso:** due volte
  `Voto non valido. Inserire un valore da 1 a 10.` al primo studente;
  la fascia Ottimo con 20 studenti, `100.0%` e 20 asterischi;
  `Studenti con voto insufficiente: 0 su 20 (0%)`

### Test 4 – Testo non numerico e fine dell'input
- **Cosa si verifica:** la validazione di un testo al posto del voto e la chiusura senza ciclo infinito
- **Input:** `otto`, `8`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
  Studente  1:   Voto non valido. Inserire un valore da 1 a 10.
  Studente  1:   Studente  2: 

Input terminato prima di 20 voti: analisi annullata.
```
