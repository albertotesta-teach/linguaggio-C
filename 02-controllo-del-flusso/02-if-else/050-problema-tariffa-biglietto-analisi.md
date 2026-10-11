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

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `eta` | `int` | Età in anni |
| `studente` | `int` (0/1) | Possesso della tessera universitaria |
| `giorno` | `int` | Giorno della settimana, 1 = lunedì ... 7 = domenica |
| `prezzo` | `int` | Prezzo in centesimi |
| `dati_validi` | `int` (0/1) | Tutti i dati nei valori ammessi |

I prezzi sono costanti `#define` espresse in centesimi: con gli interi i
calcoli sono esatti e la stampa in euro si ottiene con `/ 100` e `% 100`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Studente universitario di martedì

**a) Input** – età 22, tessera 1, giorno 2

**b) Output** – "Tariffa: studenti universitari", sconto di 2,00 euro,
prezzo 5,00 euro

**c) Variabili di supporto** – `prezzo`

**d) Vincoli** – la tariffa studenti richiede sia l'età sia la tessera

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Leggere età, tessera e giorno.
2. Calcolare `dati_validi`; se falso stampare un messaggio di errore e terminare.
3. Scegliere la tariffa con una catena di controlli nell'ordine:
   età < 6, età ≤ 17, età ≤ 26 con tessera, età ≥ 65, altrimenti intero.
4. Se il giorno è martedì e il prezzo è maggiore di zero, sottrarre lo sconto.
5. Stampare il prezzo in euro.

### Caso d'uso 2 – Ventiduenne senza tessera

**a) Input** – età 22, tessera 0, giorno 2

**b) Output** – "Tariffa: intero", sconto del martedì, prezzo 10,00 euro

**c) Variabili di supporto** – `prezzo`

**d) Vincoli** – se la tessera manca, la condizione degli studenti è falsa e
la catena prosegue fino all'intero

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Bambino di martedì

**a) Input** – età 4, tessera 0, giorno 2

**b) Output** – "Tariffa: bambini (gratis)" e prezzo 0,00 euro, senza sconto

**c) Variabili di supporto** – `prezzo`

**d) Vincoli** – lo sconto si applica solo ai biglietti a pagamento, per non
ottenere un prezzo negativo

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1; al passo 4 la
condizione `prezzo > 0` è falsa.

### Caso d'uso 4 – Dati non validi

**a) Input** – per esempio età -3, oppure tessera 5, oppure giorno 9

**b) Output** – "Dati non validi: impossibile calcolare il prezzo."

**c) Variabili di supporto** – `dati_validi`

**d) Vincoli** – il calcolo del prezzo avviene solo nel ramo else

**e) Assunzioni** – età massima plausibile 120 anni

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 2.
