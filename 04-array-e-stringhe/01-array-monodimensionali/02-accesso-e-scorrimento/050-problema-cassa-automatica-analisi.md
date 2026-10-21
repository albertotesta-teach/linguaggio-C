# Analisi – 050-problema-cassa-automatica.c

## 1. Problema

Una cassa automatica deve restituire il resto a un cliente usando il minor numero
possibile di monete. Il programma legge il prezzo e l'importo pagato, calcola
il resto in centesimi e applica un algoritmo greedy: scorre i tagli disponibili
dal più grande al più piccolo, assegnando quante monete possibile per ogni taglio.

---

## 2. Analisi

### Input

| Variabile          | Tipo  | Descrizione                         |
|--------------------|-------|-------------------------------------|
| `prezzo_centesimi` | `int` | Prezzo dell'articolo in centesimi   |
| `pagato_centesimi` | `int` | Importo pagato in centesimi         |

### Output
- Prezzo, importo pagato e resto in formato euro (`E,CC euro`);
- la composizione del resto: per ogni taglio usato, il valore in centesimi e
  il numero di monete; poi "Resto restituito correttamente.", oppure
  "Nessun resto da restituire." se il resto è zero;
- il numero totale di monete restituite.

### Vincoli
- Il prezzo è positivo: altrimenti viene richiesto di nuovo
- L'importo pagato è almeno pari al prezzo: altrimenti viene richiesto di
  nuovo, indicando il minimo
- Gli importi sono interi in centesimi, per evitare gli errori di
  arrotondamento dei numeri reali; la stampa in euro usa `/ 100` e `% 100`
- I tagli sono in ordine decrescente: è la condizione perché l'algoritmo
  greedy dia il numero minimo di monete con i tagli dell'euro
- Il taglio da 1 centesimo garantisce che il resto si azzeri sempre
- Si stampano solo i tagli effettivamente usati
- Il valore restituito da `scanf` si controlla: un testo non numerico è un
  importo non valido e il resto della riga si scarta con `getchar`; se
  l'input termina (EOF) l'operazione viene annullata

### Assunzioni
- La cassa ha disponibilità illimitata di ogni taglio
- Non si gestiscono importi così grandi da superare la capacità di un `int`

### Variabili di supporto

| Variabile       | Tipo      | Dimensione | Descrizione                                         |
|-----------------|-----------|------------|-----------------------------------------------------|
| `tagli`         | `int[]`   | 8          | 200, 100, 50, 20, 10, 5, 2, 1 centesimi             |
| `monete_usate`  | `int[]`   | 8          | Monete usate per ogni taglio, parallelo a `tagli`   |
| `resto`         | `int`     | —          | Resto ancora da restituire                          |
| `valido`        | `int`     | —          | Flag dei cicli di validazione                       |
| `totale_monete` | `int`     | —          | Somma di `monete_usate`                             |
| `NUM_TAGLI`     | `#define` | 8          | Numero di tagli                                     |

### Algoritmo in linguaggio naturale
1. Leggere il prezzo ripetendo finché non è positivo.
2. Leggere l'importo pagato ripetendo finché è minore del prezzo.
3. Calcolare `resto = pagato − prezzo` e stampare i tre importi in euro.
4. Se il resto è zero stampare che non c'è resto. Altrimenti, per ogni
   taglio dal più grande al più piccolo:
   a. `monete_usate[i] = resto / tagli[i]` (divisione intera);
   b. `resto = resto − monete_usate[i] × tagli[i]`;
   c. se `monete_usate[i] > 0` stampare taglio e numero di monete.
   Alla fine, se il resto è zero, stampare la conferma.
5. Sommare `monete_usate` e stampare il totale delle monete.

---

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Resto tipico
- **Input:** prezzo 135, pagato 200
- **Output atteso:**
```
Prezzo  : 1,35 euro
Pagato  : 2,00 euro
Resto   : 0,65 euro

Composizione del resto:
   50 cent  x 1 moneta/e
   10 cent  x 1 moneta/e
    5 cent  x 1 moneta/e

Resto restituito correttamente.
Totale monete restituite: 3
```

### Test 2 – Resto con monete ripetute
- **Cosa si verifica:** più monete dello stesso taglio
- **Input:** prezzo 1, pagato 500
- **Output atteso:** `Resto   : 4,99 euro`; tagli 200 × 2, 50 × 1, 20 × 2,
  5 × 1, 2 × 2; `Totale monete restituite: 8`

### Test 3 – Importo esatto
- **Cosa si verifica:** il ramo senza resto
- **Input:** prezzo 250, pagato 250
- **Output atteso:** `Resto   : 0,00 euro`, `Nessun resto da restituire.`,
  `Totale monete restituite: 0`

### Test 4 – Dati non validi
- **Cosa si verifica:** le due validazioni
- **Input:** prezzo 0, poi -5, poi 300; pagato 200, poi 500
- **Output atteso:** due volte `Inserire un prezzo positivo.`, poi
  `Importo insufficiente. Inserire almeno 300 centesimi.`; infine resto
  2,00 euro con una moneta da 200 centesimi

### Test 5 – Testo non numerico e fine dell'input
- **Cosa si verifica:** la validazione di un testo al posto dell'importo e la chiusura senza ciclo infinito
- **Input:** `abc`, `135`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Prezzo articolo (in centesimi, es. 135 per 1,35 euro): Inserire un prezzo positivo.
Prezzo articolo (in centesimi, es. 135 per 1,35 euro): Importo pagato  (in centesimi): 

Input terminato: operazione annullata.
```
