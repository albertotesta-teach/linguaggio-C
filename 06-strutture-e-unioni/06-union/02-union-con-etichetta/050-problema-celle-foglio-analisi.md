# Analisi – 050-problema-celle-foglio.c

## 1. Problema

Il foglio delle spese della gita ha 6 righe e 3 colonne; ogni cella è
vuota, un numero o un testo. `scrivi` decide il tipo: numero se tutto il
contenuto è un numero, altrimenti testo. La somma di una colonna usa uno
`switch` sull'etichetta: somma i numeri e conta i testi ignorati. La cella
è una struct con l'etichetta e una `union` tra numero e testo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `P` stampa, `M cella contenuto` modifica, `V cella` svuota, `S colonna` somma, `Q` fine (anche minuscoli) |
| cella | testo | Lettera A-C e riga 1-6 (es. `B4`, anche minuscola) |
| `contenuto` | `char[32]` | Il resto della riga |

Foglio iniziale: intestazioni Voce, Euro, Note; Pullman 1450; Museo 156;
Pranzo "da definire" "chiedere".

### Output

- `P`: il foglio, con i numeri allineati a destra e `.` per le celle
  vuote.
- `M`: `B4: numero` oppure `C2: testo`; `Cella non valida.`
- `S`: `Somma colonna X: S (celle di testo ignorate: N)`;
  `Colonna non valida.`
- `Comando sconosciuto.`

### Vincoli

- Numero: `sscanf(contenuto, "%lf %c")` legge esattamente un numero e
  nient'altro.
- Il testo è troncato a 11 caratteri.
- La somma legge `v.numero` solo per le celle con etichetta `NUMERO`.
- Un comando per riga (il resto viene scartato). A fine input il
  programma termina come con `Q`.

### Assunzioni

- Il contenuto di `M` sta sulla stessa riga della cella.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `TipoCella` | `typedef enum { VUOTA, NUMERO, TESTO } TipoCella;` | Etichetta |
| `Cella` | `typedef struct { TipoCella tipo; union { double numero; char testo[12]; } v; } Cella;` | Una cella |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `foglio` | `Cella[6][3]` | Il foglio |
| `riga`, `colonna` | `int` | Cella letta |
| `somma`, `testi` | `double`, `int` | Risultato di `S` |

| Funzione | Compito |
|----------|---------|
| `scrivi(c, contenuto)` | Imposta tipo e valore della cella |
| `stampa_foglio(foglio)` | Stampa con uno `switch` sul tipo |
| `leggi_cella(&riga, &colonna)` | Legge una cella come `B3`; 0 se fuori dal foglio |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Scrivere il foglio iniziale.
2. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `P`: stampare; `M`/`V`: leggere la cella e scriverla o svuotarla;
      `S`: leggere la colonna e sommare i numeri contando i testi;
   3. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Modifiche e somme

- **Input:** `P`, `M B4 35.50`, `m c2 da pagare`, `M D1 x`, `M B9 3`,
  `S B`, `s c`, `S Z`, `V B3`, `S B`, `X`, `P`, `Q`
- **Valori intermedi attesi:** colonna B: 1450 + 156 + 35.50 = 1641.50,
  testo "Euro"; dopo aver svuotato B3: 1485.50.
- **Output atteso:**
  ```
       A            B            C
    1  Voce         Euro         Note        
    2  Pullman           1450.00 .           
    3  Museo              156.00 .           
    4  Pranzo       da definire  chiedere    
    5  .            .            .           
    6  .            .            .           
    B4: numero
    C2: testo
    Cella non valida.
    Cella non valida.
    Somma colonna B: 1641.50 (celle di testo ignorate: 1)
    Somma colonna C: 0.00 (celle di testo ignorate: 3)
    Colonna non valida.
    Somma colonna B: 1485.50 (celle di testo ignorate: 1)
    Comando sconosciuto.
       A            B            C
    1  Voce         Euro         Note        
    2  Pullman           1450.00 da pagare   
    3  Museo        .            .           
    4  Pranzo              35.50 chiedere    
    5  .            .            .           
    6  .            .            .           
  ```
