# Analisi – 060-problema-scontrino.c

## 1. Problema

Alla cassa si dichiara il numero di articoli diversi nel carrello e, per
ciascuno, prezzo unitario e quantità. Il programma stampa le righe dello
scontrino, il numero di pezzi, il subtotale, lo sconto del 5% per spese oltre
100 euro, il totale e la riga con l'importo più alto.

## 2. Analisi

### Input

| Variabile         | Tipo     | Significato                                       |
|-------------------|----------|---------------------------------------------------|
| `numero_articoli` | `int`    | Righe dello scontrino, determina le iterazioni    |
| `prezzo`          | `double` | Prezzo unitario, letto per ogni riga              |
| `quantita`        | `int`    | Pezzi dell'articolo, letti per ogni riga          |

### Output
Una riga per articolo con prezzo, quantità e importo; poi il riepilogo con
il numero di pezzi, il subtotale, la riga dello sconto (solo se applicato)
e il totale; infine il numero della riga più costosa.

### Vincoli
- `numero_articoli`, `prezzo` e `quantita` sono positivi: ogni richiesta si
  ripete finché il valore non è valido
- Lo sconto del 5% si applica solo se il subtotale supera 100 euro: la
  soglia è esclusa, quindi a 100,00 euro esatti non c'è sconto
- Lo sconto si calcola dopo il ciclo, sul subtotale completo

### Assunzioni
- Gli importi in `double` sono sufficienti per un esempio didattico (un
  gestionale userebbe i centesimi interi)
- Gli articoli non vengono memorizzati (gli array arrivano nel capitolo 04):
  ogni riga viene elaborata appena inserita

### Variabili di supporto

| Variabile         | Tipo     | Significato                                        |
|-------------------|----------|----------------------------------------------------|
| `riga`            | `int`    | Variabile di controllo del for                     |
| `importo_riga`    | `double` | `prezzo * quantita`                                |
| `subtotale`       | `double` | Accumulatore degli importi                         |
| `pezzi`           | `int`    | Accumulatore delle quantità                        |
| `sconto`          | `double` | 5% del subtotale se supera 100 euro, altrimenti 0  |
| `importo_massimo` | `double` | Importo della riga più costosa                     |
| `riga_massima`    | `int`    | Numero della riga più costosa                      |

### Algoritmo in linguaggio naturale
1. Leggere il numero di articoli ripetendo finché non è positivo.
2. Per ogni riga da 1 al numero di articoli:
   a. leggere prezzo (positivo) e quantità (positiva), ripetendo se non
      validi (`do-while` annidati nel `for`);
   b. calcolare l'importo della riga e aggiornare subtotale e pezzi;
   c. se è la prima riga o l'importo supera il massimo, aggiornare il massimo;
   d. stampare la riga.
3. Se il subtotale supera 100 euro, calcolare lo sconto del 5%.
4. Stampare il riepilogo; la riga dello sconto solo se lo sconto è presente.
5. Stampare la riga più costosa.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Spesa con sconto
- **Input:** 3 articoli: 2,49 × 4; 15,90 × 2; 69,00 × 1
- **Valori intermedi attesi:** importi delle righe 9,96, 31,80, 69,00
- **Output atteso:** le tre righe, 7 pezzi, subtotale 110,76, sconto -5,54,
  totale 105,22, riga più costosa n. 3

### Test 2 – Spesa senza sconto
- **Cosa si verifica:** sotto la soglia la riga dello sconto non compare
- **Input:** 2 articoli: 10,00 × 3; 20,00 × 1
- **Output atteso:** 4 pezzi, subtotale 50,00, nessuna riga di sconto,
  totale 50,00, riga più costosa n. 1

### Test 3 – Subtotale esattamente di 100 euro
- **Cosa si verifica:** la soglia è esclusa
- **Input:** 1 articolo: 25,00 × 4
- **Output atteso:** subtotale 100,00, nessuna riga di sconto, totale 100,00

### Test 4 – Dati non validi
- **Input:** numero di articoli 0, oppure prezzo 0 o negativo, oppure
  quantità 0
- **Output atteso:** la domanda corrispondente viene ripetuta
