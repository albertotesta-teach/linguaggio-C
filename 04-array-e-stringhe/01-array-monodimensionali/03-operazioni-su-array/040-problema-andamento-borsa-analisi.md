# Analisi – 040-problema-andamento-borsa.c

## 1. Problema

Un investitore vuole analizzare i prezzi di chiusura di un titolo azionario
registrati in 10 giorni consecutivi. Il programma deve mostrare la variazione
giornaliera assoluta e percentuale, calcolare la media del periodo, identificare
il giorno con il guadagno e la perdita massima e segnalare i giorni sotto media.

---

## 2. Analisi generale e struttura dati

Tutte le elaborazioni partono da **un solo array** (`prezzi`). Le variazioni
giornaliere non vengono memorizzate in un secondo array: vengono calcolate
al volo durante lo scorrimento e confrontate direttamente con il massimo/minimo
corrente. Questo mostra che non è sempre necessario conservare i valori intermedi.

| Variabile      | Tipo      | Dimensione | Motivazione                                              |
|----------------|-----------|------------|----------------------------------------------------------|
| `prezzi`       | `double[]`| 10         | Prezzo di chiusura per ogni giorno; indice = giorno - 1  |
| `somma`        | `double`  | —          | Accumulatore per la media del periodo                    |
| `media`        | `double`  | —          | Media calcolata prima del ciclo di confronto             |
| `guadagno_max` | `double`  | —          | Variazione positiva massima trovata finora               |
| `perdita_max`  | `double`  | —          | Variazione negativa minima (più negativa) trovata finora |
| `giorno_max`   | `int`     | —          | Numero del giorno con guadagno massimo                   |
| `giorno_min`   | `int`     | —          | Numero del giorno con perdita massima                    |
| `sotto_media`  | `int`     | —          | Contatore giorni con prezzo < media                      |
| `GIORNI`       | `#define` | 10         | Dimensione dell'array e limite dei cicli                 |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Andamento giornaliero con variazione

**a) Input**
Array `prezzi` inizializzato staticamente.

**b) Output**
```
=== ANDAMENTO TITOLO ===
  Giorno | Prezzo   | Variazione
  -------|----------|------------
     1   |  142.50€ | --
     2   |  145.20€ | +2.70€ (+1.89%)
     3   |  143.80€ | -1.40€ (-0.96%)
  ...
```

**c) Variabili di supporto**
- `variazione` (`double`): `prezzi[i] - prezzi[i-1]`, calcolata al volo.
- `perc` (`double`): variazione percentuale rispetto al giorno precedente.

**d) Vincoli**
- Il ciclo parte da `i = 1` perché il giorno 0 non ha un giorno precedente.
- I tre casi (positivo, negativo, zero) producono output distinti.
- Il giorno 1 viene stampato separatamente prima del ciclo.

**e) Assunzioni**
- I prezzi sono sempre positivi (non si gestisce il caso prezzo = 0).
- La variazione percentuale usa `prezzi[i-1]` come base (mai zero).

**f) Algoritmo in linguaggio naturale**
```
1. Stampare il giorno 1 senza variazione.
2. Per i da 1 a GIORNI - 1:
   a. variazione = prezzi[i] - prezzi[i-1].
   b. perc = variazione / prezzi[i-1] * 100.
   c. Se variazione > 0: stampare con segno +.
      Se variazione < 0: stampare con segno -.
      Altrimenti: stampare "invariato".
```

---

### Caso d'uso 2 – Media del periodo

**a) Input**
Array `prezzi`.

**b) Output**
```
Prezzo medio del periodo: 148.96€
```

**c) Variabili di supporto**
- `somma` (`double`): accumulatore.
- `media` (`double`): somma / GIORNI.

**d) Vincoli**
- La media va calcolata prima del ciclo di confronto (caso d'uso 3).
- Divisione floating point: `double / int` produce `double`.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare somma = 0.0.
2. Per i da 0 a GIORNI - 1: somma += prezzi[i].
3. media = somma / GIORNI.
```

---

### Caso d'uso 3 – Giorno con guadagno e perdita massima

**a) Input**
Array `prezzi`.

**b) Output**
```
Giorno con guadagno massimo: giorno 8 (+5.20€)
Giorno con perdita massima : giorno 3 (-1.40€)
```

**c) Variabili di supporto**
- `guadagno_max`, `perdita_max` (`double`): estremi delle variazioni.
- `giorno_max`, `giorno_min` (`int`): giorni corrispondenti agli estremi.

**d) Vincoli**
- L'inizializzazione usa la prima variazione disponibile (`prezzi[1] - prezzi[0]`),
  non 0, per evitare di escludere variazioni negative o positive piccole.
- Il ciclo parte da `i = 2` perché `i = 1` è già considerato nell'inizializzazione.
- Le variazioni non vengono memorizzate in un array separato: vengono calcolate
  al volo e confrontate direttamente con il massimo/minimo corrente.

**e) Assunzioni**
- Ci sono almeno 2 giorni di dati (garantito da `GIORNI = 10`).

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare guadagno_max = perdita_max = prezzi[1] - prezzi[0].
2. Inizializzare giorno_max = giorno_min = 2.
3. Per i da 2 a GIORNI - 1:
   a. var = prezzi[i] - prezzi[i-1].
   b. Se var > guadagno_max: aggiornare guadagno_max e giorno_max.
   c. Se var < perdita_max: aggiornare perdita_max e giorno_min.
4. Stampare i risultati.
```

---

### Caso d'uso 4 – Giorni sotto la media

**a) Input**
Array `prezzi`, variabile `media` (già calcolata).

**b) Output**
```
Giorni con prezzo sotto la media (148.96€):
  Giorno  1: 142.50€ (-6.46€ dalla media)
  Giorno  2: 145.20€ (-3.76€ dalla media)
  Giorno  3: 143.80€ (-5.16€ dalla media)
  Giorno  6: 149.70€ ...
Totale giorni sotto media: 4 su 10
```

**c) Variabili di supporto**
- `sotto_media` (`int`): contatore dei giorni con prezzo inferiore alla media.

**d) Vincoli**
- La media deve essere disponibile prima di questo ciclo (calcolata nel caso d'uso 2).
- Il confronto usa `<` (non `<=`): un prezzo esattamente uguale alla media non conta.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare sotto_media = 0.
2. Per i da 0 a GIORNI - 1:
   a. Se prezzi[i] < media:
      - Stampare giorno, prezzo e distanza dalla media.
      - Incrementare sotto_media.
3. Stampare totale.
```
