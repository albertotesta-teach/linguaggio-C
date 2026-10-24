# Analisi – 050-problema-scontrino-mensa.c

## 1. Problema

Alla cassa della mensa l'operatore inserisce il codice di un prodotto del
listino e la quantità; il codice 0 chiude lo scontrino. Con la tessera
studenti si ha uno sconto del 10% se il totale supera 8 euro. Gli importi
hanno il tipo `Euro`, le quantità il tipo `Quantita`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `codice` | `int` | Codice del prodotto (1-6); 0 chiude lo scontrino |
| `pezzi` | `Quantita` | Quantità, positiva |
| `tessera` | `char` | Risposta `S`/`N` alla domanda sulla tessera |
| `nomi`, `listino` | `const char *[6]`, `Euro[6]` | Listino (nel sorgente): Primo piatto 3.20, Secondo piatto 3.90, Contorno 1.50, Frutta 0.80, Acqua 0.5 l 0.50, Yogurt 1.10 |

### Output

- Il listino.
- Per ogni prodotto aggiunto: quantità, nome e subtotale; oppure
  `Codice inesistente.` o `Quantita' non valida, prodotto non aggiunto.`
- Lo scontrino finale: totale, eventuale sconto (con il segno meno) e
  importo da pagare.

### Vincoli

- Gli importi hanno il tipo `Euro` (`typedef double Euro;`), le quantità
  `Quantita` (`typedef int Quantita;`).
- Il codice è l'indice del listino + 1; deve essere tra 1 e 6, la quantità
  positiva. Un errore non chiude lo scontrino.
- Un codice o una quantità non numerici vengono scartati (resto della riga)
  e trattati come non validi; a fine input lo scontrino si chiude.
- Sconto del 10% solo con tessera (`S` o `s`) e totale strettamente
  maggiore di 8 euro; lo sconto è arrotondato al centesimo.

### Assunzioni

- La risposta sulla tessera è una sola lettera.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Euro` | `typedef double Euro;` | Prezzi e importi |
| `Quantita` | `typedef int Quantita;` | Pezzi acquistati |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `totale`, `riduzione` | `Euro` | Importo dello scontrino e dello sconto |
| `letti` | `int` | Valore restituito da `scanf` |
| `k` | `int` | Indice del listino |
| `SOGLIA_SCONTO`, `PERCENTUALE` | `#define` | 8.0 euro, 10% |

| Funzione | Compito |
|----------|---------|
| `subtotale(prezzo, pezzi)` | Prezzo per quantità |
| `sconto(totale, percentuale)` | Importo dello sconto arrotondato al centesimo |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Stampare il listino.
2. Finché il codice non è 0:
   1. leggere il codice (a fine input 0; testo → inesistente);
   2. se è tra 1 e 6 leggere la quantità: se valida aggiungere il
      subtotale al totale e stampare la riga, altrimenti segnalarla;
   3. altrimenti, se non è 0, segnalare il codice inesistente.
3. Chiedere la tessera: con `S`/`s` e totale oltre 8 euro calcolare lo
   sconto.
4. Stampare totale, sconto (se c'è) e importo da pagare.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Scontrino con sconto

- **Input:** `1`, `2`, `2`, `1`, `3`, `1`, `0`, `S`
- **Valori intermedi attesi:** totale 6.40 + 3.90 + 1.50 = 11.80;
  sconto 1.18.
- **Output atteso** (fine):
  ```
    Totale             11.80
    Sconto 10%         -1.18
    Da pagare          10.62 euro
  ```

### Test 2 – Dati non validi

- **Input:** `1`, `2`, `9`, `2`, `0`, `3`, `1`, `4`, `2`, `0`, `S`
- **Output atteso:**
  ```
     2 x Primo piatto      6.40
    Codice inesistente.
    Quantita' non valida, prodotto non aggiunto.
     1 x Contorno          1.50
     2 x Frutta            1.60
  ...
    Totale              9.50
    Sconto 10%         -0.95
    Da pagare           8.55 euro
  ```
  (il codice 2 seguito dalla quantità 0 non aggiunge nulla).

### Test 3 – Testo al posto dei numeri

- **Input:** `1`, `abc`, `2`, `1`, `xyz`, `0`, `s`
- **Output atteso:** `Quantita' non valida, prodotto non aggiunto.`,
  `1 x Secondo piatto 3.90`, `Codice inesistente.`; totale 3.90 senza
  sconto (sotto gli 8 euro).

### Test 4 – Totale sotto la soglia

- **Input:** `1`, `1`, `0`, `S`
- **Output atteso:** totale 3.20, da pagare 3.20 (nessuno sconto sotto
  gli 8 euro).
