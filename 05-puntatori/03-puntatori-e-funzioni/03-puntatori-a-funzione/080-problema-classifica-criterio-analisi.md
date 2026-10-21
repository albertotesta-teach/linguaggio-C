# Analisi – 080-problema-classifica-criterio.c

## 1. Problema

Al triathlon scolastico ogni atleta ha un punteggio in corsa, salto e
lancio del peso. La giuria assegna tre premi: assoluto (totale più alto),
specialista (prova singola migliore) e regolarità (prova peggiore più
alta). Il programma stampa la tabella dei punteggi e i tre vincitori.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `nomi` | `char[5][12]` | Elena, Davide, Sara, Omar, Giulia |
| `punti` | `int[5][3]` | Una riga per atleta (corsa, salto, peso): {72, 65, 80}, {95, 40, 70}, {68, 74, 71}, {60, 88, 79}, {81, 70, 62} |

### Output

- La tabella dei punteggi con il totale di ogni atleta.
- Il vincitore di ciascun premio con il valore che l'ha fatto vincere.

### Vincoli

- `vincitore` è unica per i tre premi: riceve il criterio come puntatore a
  funzione `int (*)(const int *)` e cerca l'atleta con il valore più alto.
- `punti[i]` è una riga di 3 interi e arriva al criterio come
  `const int *`.
- Per la regolarità si cerca il valore più alto della prova peggiore di
  ciascun atleta.
- A parità vince l'atleta che compare prima (confronto con `>`).

### Assunzioni

- Ogni atleta ha esattamente 3 prove.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `i` | `int` | Indice dell'atleta |
| `migliore` | `int` | In `vincitore`: indice del migliore finora |
| `p`, `max`, `min` | `const int *`, `int` | Nei criteri |

| Funzione | Compito |
|----------|---------|
| `vincitore(punti, n, valuta)` | Indice dell'atleta con il valore più alto |
| `totale`, `prova_migliore`, `prova_peggiore` | Criteri `int (const int *)` sulla riga di un atleta |
| `premia(premio, nomi, punti, valuta)` | Stampa il vincitore di un premio |

### Algoritmo in linguaggio naturale

1. Stampare la tabella con il totale di ogni atleta.
2. Per ogni premio chiamare `premia` con il criterio corrispondente, che
   trova il vincitore con `vincitore` e stampa nome e valore.
3. In `vincitore`: partendo dal primo atleta, sostituire il migliore quando
   `valuta(punti[i])` è maggiore di `valuta(punti[migliore])`.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** lo stesso algoritmo dà vincitori diversi con
  criteri diversi; Davide vince lo specialista pur avendo il totale più
  basso.
- **Input:** nessuno.
- **Valori intermedi attesi:** prove peggiori 65, 40, 68, 60, 62 → massimo
  68 (Sara).
- **Output atteso:**
  ```
  Atleta    corsa  salto   peso  totale
  Elena        72     65     80     217
  Davide       95     40     70     205
  Sara         68     74     71     213
  Omar         60     88     79     227
  Giulia       81     70     62     213

  Premio Assoluto   : Omar    (valore 227)
  Premio Specialista: Davide  (valore 95)
  Premio Regolarita': Sara    (valore 68)
  ```

### Test 2 – Parità

- **Cosa si verifica:** a parità di valore vince l'atleta che compare prima.
- **Procedura:** nel sorgente impostare i punteggi di Giulia a {81, 70,
  68}, ricompilare ed eseguire.
- **Valori intermedi attesi:** la prova peggiore di Giulia diventa 68, come
  quella di Sara.
- **Output atteso:** `Premio Regolarita': Sara    (valore 68)`
