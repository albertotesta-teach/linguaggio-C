# Analisi – 060-problema-temperature-settimana.c

## 1. Problema

Una stazione meteo registra la temperatura in quattro fasce orarie (notte,
mattina, pomeriggio, sera) per sette giorni. Il programma deve stampare la
tabella con la media giornaliera, individuare la rilevazione più alta e più
bassa con giorno e fascia, e calcolare la media settimanale di ogni fascia.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile | Tipo         | Dimensione | Descrizione                                   |
|-----------|--------------|------------|-----------------------------------------------|
| `temp`    | `double[][]` | 7 × 4      | Riga = giorno, colonna = fascia oraria (°C)   |
| `giorni`  | `char[][]`   | 7 × 12     | Nome del giorno: parallelo alle **righe**     |
| `fasce`   | `char[][]`   | 4 × 12     | Nome della fascia: parallelo alle **colonne** |

### Output
- La tabella delle rilevazioni con, per ogni giorno, la media delle quattro
  fasce;
- la temperatura massima e la minima della settimana con giorno e fascia;
- la media settimanale di ogni fascia oraria.

### Vincoli
- La media di un giorno si calcola sommando una **riga**; la media di una
  fascia sommando una **colonna** (ciclo esterno sulle colonne)
- Per massimo e minimo si memorizzano gli **indici** di riga e colonna, da
  cui si ricavano valore, giorno e fascia
- Massimo e minimo partono dalla cella [0][0]; a parità resta la prima
  cella trovata scorrendo per righe
- Le medie si stampano con un decimale

### Assunzioni
- Le temperature sono in gradi Celsius e i dati sono corretti

### Variabili di supporto

| Variabile | Tipo     | Descrizione                                   |
|-----------|----------|-----------------------------------------------|
| `somma`   | `double` | Accumulatore riusato per righe e colonne      |
| `g_max`, `f_max`, `g_min`, `f_min` | `int` | Indici degli estremi  |
| `GIORNI`, `FASCE`, `LUNG` | `#define` | 7, 4, 12                  |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione con i nomi delle fasce.
2. Per ogni giorno stampare il nome e le quattro temperature, sommarle e
   stampare la media.
3. Scorrere tutta la matrice aggiornando gli indici del massimo e del
   minimo; stampare i due valori con giorno e fascia.
4. Per ogni fascia sommare la colonna su tutti i giorni e stampare la media.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Tabella con medie giornaliere
- **Output atteso:**
```
  Giorno           Notte    Mattina Pomeriggio       Sera    Media
  Lunedi'            8.5       13.0       17.5       12.0     12.8
  Martedi'           9.0       14.5       18.0       13.5     13.8
  Mercoledi'        10.5       15.0       19.5       14.0     14.8
  Giovedi'           7.0       11.5       15.0       10.5     11.0
  Venerdi'           6.5       10.0       13.5        9.0      9.8
  Sabato             8.0       14.0       20.5       15.5     14.5
  Domenica          11.0       16.5       21.0       16.0     16.1
```

### Test 2 – Estremi della settimana
- **Output atteso:**
```
Temperatura massima: 21.0 (Domenica, Pomeriggio)
Temperatura minima : 6.5 (Venerdi', Notte)
```

### Test 3 – Medie per fascia
- **Cosa si verifica:** la somma per colonne
- **Output atteso:**
```
  Notte      :   8.6
  Mattina    :  13.5
  Pomeriggio :  17.9
  Sera       :  12.9
```
