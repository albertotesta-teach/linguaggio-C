# Analisi – 050-problema-tariffa-biglietto.c

## 1. Problema

La biglietteria di un museo civico applica tariffe diverse in base all'età
del visitatore e al possesso della tessera universitaria; il martedì ogni
biglietto a pagamento ha uno sconto di 2 euro. Il programma deve calcolare
il prezzo di un biglietto e indicare la tariffa applicata.

| Tariffa | Condizione | Prezzo |
|---------|------------|--------|
| Bambini | età < 6 | gratis |
| Ragazzi | 6 ≤ età ≤ 17 | 6,00 € |
| Studenti | 18 ≤ età ≤ 26 con tessera | 7,00 € |
| Over 65 | età ≥ 65 | 8,00 € |
| Intero | tutti gli altri | 12,00 € |

## 2. Analisi

### Input

| Variabile  | Tipo        | Significato                                       |
|------------|-------------|---------------------------------------------------|
| `eta`      | `int`       | Età in anni                                       |
| `studente` | `int` (0/1) | Possesso della tessera universitaria              |
| `giorno`   | `int`       | Giorno della settimana, 1 = lunedì ... 7 = domenica |

### Output
La tariffa applicata, l'eventuale sconto del martedì e il prezzo da pagare
in euro con due decimali; oppure il messaggio "Dati non validi: impossibile
calcolare il prezzo."

### Vincoli
- Dati validi: età tra 0 e 120, tessera 0 o 1, giorno tra 1 e 7
- La tariffa studenti richiede sia l'età sia la tessera
- Lo sconto del martedì si applica solo ai biglietti a pagamento, per non
  ottenere un prezzo negativo
- Il prezzo si calcola solo se i dati sono validi

### Assunzioni
- L'utente inserisce numeri interi
- L'età massima plausibile è 120 anni

### Variabili di supporto

| Variabile     | Tipo        | Significato                      |
|---------------|-------------|----------------------------------|
| `prezzo`      | `int`       | Prezzo in centesimi              |
| `dati_validi` | `int` (0/1) | Tutti i dati nei valori ammessi  |

I prezzi sono costanti `#define` espresse in centesimi: con gli interi i
calcoli sono esatti e la stampa in euro si ottiene con `/ 100` e `% 100`.

### Algoritmo in linguaggio naturale
1. Leggere età, tessera e giorno.
2. Calcolare `dati_validi`; se falso stampare un messaggio di errore e terminare.
3. Scegliere la tariffa con una catena di controlli nell'ordine:
   età < 6, età ≤ 17, età ≤ 26 con tessera, età ≥ 65, altrimenti intero.
4. Se il giorno è martedì e il prezzo è maggiore di zero, sottrarre lo sconto.
5. Stampare il prezzo in euro.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Studente universitario di martedì
- **Input:** età 22, tessera 1, giorno 2
- **Output atteso:** "Tariffa: studenti universitari", sconto di 2,00 euro,
  prezzo 5,00 euro

### Test 2 – Ventiduenne senza tessera
- **Cosa si verifica:** senza tessera la condizione degli studenti è falsa
  e la catena prosegue fino all'intero
- **Input:** età 22, tessera 0, giorno 2
- **Output atteso:** "Tariffa: intero", sconto del martedì, prezzo 10,00 euro

### Test 3 – Bambino di martedì
- **Cosa si verifica:** al passo 4 la condizione `prezzo > 0` è falsa e lo
  sconto non viene applicato
- **Input:** età 4, tessera 0, giorno 2
- **Output atteso:** "Tariffa: bambini (gratis)" e prezzo 0,00 euro, senza sconto

### Test 4 – Dati non validi
- **Input:** per esempio età -3, oppure tessera 5, oppure giorno 9
- **Output atteso:** "Dati non validi: impossibile calcolare il prezzo."
