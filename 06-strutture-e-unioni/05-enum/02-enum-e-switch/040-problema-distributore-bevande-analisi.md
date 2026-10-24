# Analisi – 040-problema-distributore-bevande.c

## 1. Problema

Il distributore di bevande calde ha quattro bevande e accetta monete da 5
a 200 centesimi. `prezzo` e `nome` sono `switch` sulla `Bevanda`; `eroga`
controlla scorte e credito e restituisce un `Esito`, il cui messaggio è un
altro `switch`. Tutti gli importi sono in centesimi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `M centesimi` moneta, `B 1-4` bevanda, `R` resto, `Q` fine (anche minuscoli) |
| `valore` | `int` | Moneta o numero della bevanda |
| scorte | nel sorgente | caffè 10, cappuccino 5, tè 0, cioccolata 3 |

### Output

- Il credito prima di ogni comando.
- `nome (P euro): erogata, buona pausa` / `credito insufficiente` /
  `esaurita`.
- `Moneta rifiutata.`, `Scelta non valida.`, `Valore non valido.`,
  `Resto: R euro`, `Comando sconosciuto.`

### Vincoli

- Monete ammesse: 5, 10, 20, 50, 100, 200 centesimi.
- Prezzi: caffè 50, cappuccino 70, tè 60, cioccolata 80.
- La bevanda `n` scritta dall'utente è la costante `n - 1` dell'enum.
- `eroga` controlla prima le scorte, poi il credito; se eroga scala il
  credito (tramite puntatore) e la scorta.
- Gli `switch` trattano tutte le costanti, anche `NUM_BEVANDE`, così il
  compilatore non segnala casi mancanti.
- Un comando per riga; un valore non numerico non interrompe il
  programma. A fine input termina come con `Q`.

### Assunzioni

- Con `Q` il credito residuo non viene restituito: serve `R`.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Bevanda` | `typedef enum { CAFFE, CAPPUCCINO, TE, CIOCCOLATA, NUM_BEVANDE } Bevanda;` | Le bevande |
| `Esito` | `typedef enum { EROGATA, CREDITO_INSUFFICIENTE, ESAURITA } Esito;` | Risultato dell'erogazione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `scorte` | `int[4]` | Porzioni per bevanda |
| `credito` | `int` | Centesimi inseriti |
| `scelta`, `esito` | `Bevanda`, `Esito` | Bevanda richiesta e risultato |

| Funzione | Compito |
|----------|---------|
| `prezzo(b)`, `nome(b)` | Prezzo e nome con `switch` |
| `eroga(b, credito, scorte)` | Controlli ed erogazione |
| `messaggio(e)` | Testo dell'esito |
| `moneta_valida(centesimi)` | Monete accettate |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. stampare il credito e leggere il comando in maiuscolo;
   2. `M`: se la moneta è valida aggiungerla, altrimenti rifiutarla;
   3. `B`: se la scelta è tra 1 e 4 chiamare `eroga` e stampare nome,
      prezzo e messaggio;
   4. `R`: restituire il credito e azzerarlo;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe); le righe con il
credito sono omesse.

### Test 1 – Pausa caffè

- **Input:** `M 50`, `B 1`, `B 2`, `m 20`, `B 2`, `M 3`, `B 3`, `M 200`,
  `B 5`, `B 4`, `M x`, `X`, `R`, `Q`
- **Valori intermedi attesi:** 50 − 50 = 0; 20 < 70; 20 + 200 − 80 = 140.
- **Output atteso:**
  ```
    caffe' (0.50 euro): erogata, buona pausa
    cappuccino (0.70 euro): credito insufficiente
    cappuccino (0.70 euro): credito insufficiente
    Moneta rifiutata.
    te' (0.60 euro): esaurita
    Scelta non valida.
    cioccolata (0.80 euro): erogata, buona pausa
    Valore non valido.
    Comando sconosciuto.
    Resto: 1.40 euro
  ```
