# Analisi – 040-problema-andamento-borsa.c

## 1. Problema

Un investitore vuole analizzare i prezzi di chiusura di un titolo azionario
registrati in 10 giorni consecutivi. Il programma deve mostrare la variazione
giornaliera assoluta e percentuale, calcolare la media del periodo, identificare
il giorno con il guadagno e la perdita massima e segnalare i giorni sotto media.

---

## 2. Analisi

### Input
Nessun input da tastiera: i prezzi sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                     |
|-----------|------------|------------|-------------------------------------------------|
| `prezzi`  | `double[]` | 10         | Prezzo di chiusura; indice `i` = giorno `i+1`   |

### Output
- Per ogni giorno il prezzo e la variazione rispetto al giorno precedente,
  in euro e in percentuale ("--" per il primo giorno, "invariato" se la
  variazione è nulla);
- il prezzo medio del periodo;
- il giorno con il guadagno massimo e quello con la perdita massima;
- l'elenco dei giorni con prezzo sotto la media, con lo scarto, e il loro
  numero.

### Vincoli
- La variazione esiste dal secondo giorno: `prezzi[i] − prezzi[i − 1]`; la
  percentuale è calcolata sul prezzo del giorno precedente
- Le variazioni non vengono memorizzate: si calcolano durante lo scorrimento
  e si confrontano subito con il massimo e il minimo correnti
- Guadagno e perdita massimi partono dalla prima variazione disponibile
  (giorno 2), non da zero; in caso di parità resta il primo giorno trovato
- Un giorno è sotto la media se il suo prezzo è **strettamente** minore
- La media va calcolata prima del confronto

### Assunzioni
- I prezzi sono positivi (servono da divisore per la percentuale)

### Variabili di supporto

Tutte le elaborazioni partono da **un solo array**: le variazioni giornaliere
si ricavano scorrendolo, senza un secondo array.

| Variabile      | Tipo      | Descrizione                                          |
|----------------|-----------|------------------------------------------------------|
| `variazione`, `perc` | `double` | Variazione assoluta e percentuale del giorno     |
| `somma`, `media`     | `double` | Accumulatore e media del periodo                 |
| `guadagno_max`, `perdita_max` | `double` | Variazione più alta e più bassa         |
| `giorno_max`, `giorno_min`    | `int`    | Giorni corrispondenti                   |
| `sotto_media`  | `int`     | Numero di giorni sotto la media                      |
| `GIORNI`       | `#define` | 10                                                   |

### Algoritmo in linguaggio naturale
1. Stampare il prezzo del giorno 1 senza variazione.
2. Per i giorni da 2 a 10 calcolare variazione e percentuale e stampare
   la riga con il segno "+" se positiva, così com'è se negativa, oppure
   "invariato".
3. Sommare i prezzi e stampare la media.
4. Porre guadagno e perdita massimi uguali alla variazione del giorno 2;
   per i giorni da 3 a 10 aggiornarli quando la variazione è maggiore o
   minore. Stampare i due giorni.
5. Per ogni giorno con prezzo minore della media stamparlo con lo scarto e
   contarlo; stampare il totale.

---

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Variazioni giornaliere
- **Cosa si verifica:** il segno e la percentuale sul giorno precedente
- **Output atteso:**
```
     1   |  142.50€ | --
     2   |  145.20€ | +2.70€ (+1.89%)
     3   |  143.80€ | -1.40€ (-0.96%)
     4   |  148.60€ | +4.80€ (+3.34%)
     5   |  151.30€ | +2.70€ (+1.82%)
     6   |  149.70€ | -1.60€ (-1.06%)
     7   |  147.20€ | -2.50€ (-1.67%)
     8   |  152.40€ | +5.20€ (+3.53%)
     9   |  155.10€ | +2.70€ (+1.77%)
     10  |  153.80€ | -1.30€ (-0.84%)
```

### Test 2 – Media ed estremi
- **Output atteso:**
```
Prezzo medio del periodo: 148.96€

Giorno con guadagno massimo: giorno 8 (+5.20€)
Giorno con perdita massima : giorno 7 (-2.50€)
```

### Test 3 – Giorni sotto la media
- **Cosa si verifica:** il giorno 4 (148.60) è sotto la media di soli 0.36
- **Output atteso:**
```
  Giorno  1: 142.50€ (-6.46€ dalla media)
  Giorno  2: 145.20€ (-3.76€ dalla media)
  Giorno  3: 143.80€ (-5.16€ dalla media)
  Giorno  4: 148.60€ (-0.36€ dalla media)
  Giorno  7: 147.20€ (-1.76€ dalla media)
Totale giorni sotto media: 5 su 10
```
