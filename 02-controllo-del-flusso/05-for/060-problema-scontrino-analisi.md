# Analisi – 060-problema-scontrino.c

## 1. Problema

Alla cassa si dichiara il numero di articoli diversi nel carrello e, per
ciascuno, prezzo unitario e quantità. Il programma stampa le righe dello
scontrino, il numero di pezzi, il subtotale, lo sconto del 5% per spese oltre
100 euro, il totale e la riga con l'importo più alto.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `numero_articoli` | `int` | Righe dello scontrino, determina le iterazioni |
| `riga` | `int` | Variabile di controllo del for |
| `prezzo` | `double` | Prezzo unitario |
| `quantita` | `int` | Pezzi dell'articolo |
| `importo_riga` | `double` | `prezzo * quantita` |
| `subtotale` | `double` | Accumulatore degli importi |
| `pezzi` | `int` | Accumulatore delle quantità |
| `sconto` | `double` | 5% del subtotale se supera 100 euro, altrimenti 0 |
| `importo_massimo`, `riga_massima` | `double`, `int` | Ricerca del massimo |

Gli articoli non vengono memorizzati (gli array arrivano nel capitolo 04):
ogni riga viene elaborata appena inserita.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Spesa con sconto

**a) Input** – 3 articoli: 2,49 × 4; 15,90 × 2; 69,00 × 1

**b) Output** – le tre righe, 7 pezzi, subtotale 110,76, sconto -5,54,
totale 105,22, riga più costosa n. 3

**c) Variabili di supporto** – accumulatori e massimo

**d) Vincoli** – lo sconto si calcola dopo il ciclo, sul subtotale completo

**e) Assunzioni** – gli importi in `double` sono sufficienti per un esempio
didattico (un gestionale userebbe i centesimi interi)

**f) Algoritmo in linguaggio naturale**
1. Leggere il numero di articoli ripetendo finché non è positivo.
2. Per ogni riga da 1 al numero di articoli:
   a. leggere prezzo (positivo) e quantità (positiva), ripetendo se non validi;
   b. calcolare l'importo della riga e aggiornare subtotale e pezzi;
   c. se è la prima riga o l'importo supera il massimo, aggiornare il massimo;
   d. stampare la riga.
3. Se il subtotale supera 100 euro, calcolare lo sconto del 5%.
4. Stampare il riepilogo; la riga dello sconto solo se lo sconto è presente.
5. Stampare la riga più costosa.

### Caso d'uso 2 – Spesa senza sconto

**a) Input** – un subtotale fino a 100 euro

**b) Output** – riepilogo senza la riga dello sconto; totale uguale al subtotale

**c) Variabili di supporto** – `sconto` resta 0

**d) Vincoli** – la soglia è esclusa: a 100,00 euro esatti non c'è sconto

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Dati non validi

**a) Input** – numero di articoli 0, prezzo 0 o negativo, quantità 0

**b) Output** – la domanda viene ripetuta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – le validazioni sono `do-while` annidati nel `for`

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passi 1 e 2a.
