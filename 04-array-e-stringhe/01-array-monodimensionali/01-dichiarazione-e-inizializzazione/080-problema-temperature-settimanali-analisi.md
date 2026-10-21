# Analisi – 080-problema-temperature-settimanali.c

## 1. Problema

Una centralina meteo registra la temperatura massima giornaliera per 7 giorni.
Il programma deve visualizzare il riepilogo settimanale, calcolare la media,
identificare i giorni con temperatura sopra media e mostrare la variazione
rispetto al giorno precedente per evidenziare le tendenze climatiche.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile     | Tipo       | Dimensione | Descrizione                                   |
|---------------|------------|------------|-----------------------------------------------|
| `giorni`      | `char[][]` | 7 × 12     | Nomi dei giorni (max 11 caratteri)            |
| `temperature` | `double[]` | 7          | Temperatura massima del giorno in °C          |

### Output
- Il riepilogo: nome del giorno e temperatura con un decimale;
- la temperatura media;
- l'elenco dei giorni sopra la media, con lo scarto, e il loro numero;
- per ogni coppia di giorni consecutivi la variazione, con l'indicazione
  "in salita", "in discesa" o "stabile".

### Vincoli
- `giorni` e `temperature` hanno la stessa dimensione
- La media va calcolata prima del ciclo di confronto
- Un giorno è sopra la media se la sua temperatura è **strettamente**
  maggiore (`>`) della media
- Il confronto avviene con la media esatta, non con il valore arrotondato
  stampato: un giorno può risultare sopra una media stampata uguale alla
  sua temperatura
- La variazione si calcola dal secondo giorno in poi, perché il primo non
  ha un predecessore
- I tre casi della variazione (positiva, negativa, nulla) si escludono a
  vicenda

### Assunzioni
- Le temperature sono in gradi Celsius e i dati sono corretti

### Variabili di supporto

| Variabile          | Tipo      | Descrizione                                     |
|--------------------|-----------|-------------------------------------------------|
| `somma`            | `double`  | Accumulatore per la media                       |
| `media`            | `double`  | Temperatura media settimanale                   |
| `sopra_media`      | `int`     | Numero di giorni sopra la media                 |
| `variazione`       | `double`  | `temperature[i] − temperature[i − 1]`           |
| `GIORNI_SETTIMANA` | `#define` | 7                                               |

### Algoritmo in linguaggio naturale
1. Stampare nome e temperatura di ogni giorno.
2. Sommare le temperature e calcolare `media = somma / 7`; stamparla.
3. Per ogni giorno con temperatura maggiore della media stampare nome,
   temperatura e scarto, e contarlo; stampare il totale.
4. Per i da 1 a 6 calcolare la variazione rispetto al giorno precedente:
   se positiva stampare "in salita", se negativa "in discesa", altrimenti
   "stabile".

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il test 3
richiede di modificare l'array e ricompilare.

### Test 1 – Media e giorni sopra la media
- **Input:** 18.5, 21.0, 23.4, 22.1, 19.8, 17.5, 16.2
- **Valori intermedi attesi:** somma 138.5; media 19.7857… (stampata 19.8)
- **Output atteso:**
```
Temperatura media : 19.8 °C

Giorni sopra la media (> 19.8 °C):
  Martedi': 21.0 °C (+1.2 rispetto alla media)
  Mercoledi': 23.4 °C (+3.6 rispetto alla media)
  Giovedi': 22.1 °C (+2.3 rispetto alla media)
  Venerdi': 19.8 °C (+0.0 rispetto alla media)
Totale: 4 giorni su 7
```
- **Osservazione:** venerdì (19.8) è sopra la media vera 19.7857 di 0.014,
  ma con un decimale la media e lo scarto appaiono come 19.8 e +0.0

### Test 2 – Variazioni giornaliere
- **Input:** come nel Test 1
- **Output atteso:**
```
  giorno 1 -> giorno 2: +2.5 °C (in salita)
  giorno 2 -> giorno 3: +2.4 °C (in salita)
  giorno 3 -> giorno 4: -1.3 °C (in discesa)
  giorno 4 -> giorno 5: -2.3 °C (in discesa)
  giorno 5 -> giorno 6: -2.3 °C (in discesa)
  giorno 6 -> giorno 7: -1.3 °C (in discesa)
```

### Test 3 – Temperature tutte uguali
- **Cosa si verifica:** il ramo "stabile" e il confronto stretto con la media
- **Procedura:** porre tutte le temperature a 20.0
- **Output atteso:** media 20.0, `Totale: 0 giorni su 7`, e sei righe
  `giorno N -> giorno N+1: stabile`
