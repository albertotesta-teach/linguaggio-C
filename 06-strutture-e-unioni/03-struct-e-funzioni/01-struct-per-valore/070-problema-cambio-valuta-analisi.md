# Analisi – 070-problema-cambio-valuta.c

## 1. Problema

Durante lo scambio culturale gli studenti annotano le spese in valuta
locale. Il programma converte ogni spesa in euro con una tabella di cambi
e stampa il totale del viaggio. Un importo è una struct `Importo` con
valore e valuta; `converti` la riceve per valore e restituisce un
`Importo` nuovo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `valore` | `double` | Importo della spesa; 0 termina |
| `valuta` | `char[8]` | Sigla di tre lettere: `EUR`, `GBP`, `CHF`, `USD` |

### Output

- Per ogni spesa: `V SIGLA = E EUR` con due decimali, oppure
  `Valuta X non in tabella.`, `Valuta non valida.`, `Importo non valido.`
- Alla fine: `Totale del viaggio: T EUR`.

### Vincoli

- Cambi (unità per 1 euro): EUR 1.0, GBP 0.86, CHF 0.95, USD 1.08.
- Conversione passando per l'euro: valore / cambio(da) × cambio(verso).
- `converti` segnala con il parametro di uscita `ok` se una valuta non è
  in tabella.
- La sigla deve avere esattamente 3 caratteri; maiuscole e minuscole
  contano.
- Una spesa per riga: il resto della riga viene scartato; un errore non
  interrompe l'inserimento. A fine input il programma termina come con 0.

### Assunzioni

- I cambi sono indicativi e fissi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Importo` | `typedef struct { double valore; char valuta[4]; } Importo;` | Una somma di denaro con la sua valuta |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `spesa`, `in_euro` | `Importo` | Spesa letta e convertita |
| `totale` | `Importo` | Somma in euro |
| `ok` | `int` | Esito della conversione |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `crea_importo(valore, valuta)` | Costruisce un `Importo` |
| `converti(i, verso, &ok)` | Restituisce l'importo convertito nella valuta `verso` |
| `cambio(valuta, &ok)` | Unità di valuta per 1 euro, cercata nella tabella |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché l'importo non è 0:
   1. leggere l'importo (fine input → 0; testo → non valido);
   2. se diverso da 0 leggere la valuta e scartare il resto della riga;
   3. se la sigla non ha 3 caratteri segnalarla;
   4. altrimenti convertire in euro: se la valuta è in tabella stampare e
      sommare al totale, altrimenti segnalarla.
2. Stampare il totale.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Spese del viaggio

- **Cosa si verifica:** conversioni, valute sconosciute o non valide,
  importo non numerico, sigla minuscola.
- **Input:** `25.80 GBP`, `12 CHF`, `15 USD`, `9.50 EUR`, `100 JPY`,
  `5 EURO`, `abc`, `3 gbp`, `0`
- **Valori intermedi attesi:** 25.80 / 0.86 = 30.00; 12 / 0.95 = 12.63;
  15 / 1.08 = 13.89; totale 66.02.
- **Output atteso:**
  ```
    25.80 GBP = 30.00 EUR
    12.00 CHF = 12.63 EUR
    15.00 USD = 13.89 EUR
    9.50 EUR = 9.50 EUR
    Valuta JPY non in tabella.
    Valuta non valida.
    Importo non valido.
    Valuta gbp non in tabella.
  Totale del viaggio: 66.02 EUR
  ```

### Test 2 – Nessuna spesa

- **Input:** `0`
- **Output atteso:** `Totale del viaggio: 0.00 EUR`.

### Test 3 – Fine input

- **Input:** `10 GBP`, poi fine input.
- **Output atteso:** `Totale del viaggio: 11.63 EUR`.
