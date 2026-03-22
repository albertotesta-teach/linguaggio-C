# Analisi – 080-problema-temperature-settimanali.c

## 1. Problema

Una centralina meteo registra la temperatura massima giornaliera per 7 giorni.
Il programma deve visualizzare il riepilogo settimanale, calcolare la media,
identificare i giorni con temperatura sopra media e mostrare la variazione
rispetto al giorno precedente per evidenziare le tendenze climatiche.

---

## 2. Analisi generale e struttura dati

Le temperature sono valori in virgola mobile (`double`) che richiedono precisione
decimale. I nomi dei giorni sono array parallelo di stringhe. La variazione
giornaliera è calcolata come differenza tra elementi consecutivi dell'array.

| Variabile          | Tipo         | Dimensione | Motivazione                                        |
|--------------------|--------------|------------|----------------------------------------------------|
| `giorni`           | `char[][]`   | 7 × 12     | Nomi dei giorni, max 11 caratteri + `'\0'`         |
| `temperature`      | `double[]`   | 7          | Temperatura in °C con decimali                     |
| `somma`            | `double`     | —          | Accumulatore per il calcolo della media            |
| `media`            | `double`     | —          | Temperatura media settimanale                      |
| `sopra_media`      | `int`        | —          | Contatore giorni con temperatura > media           |
| `variazione`       | `double`     | —          | Differenza temperature tra giorno i e i-1          |
| `GIORNI_SETTIMANA` | `#define`    | 7          | Dimensione degli array e limite dei cicli          |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Riepilogo settimanale

**a) Input**
Array `giorni` e `temperature` inizializzati staticamente.

**b) Output**
```
=================================
  TEMPERATURE SETTIMANA CORRENTE
=================================
  Lunedi'     :  18.5 °C
  Martedi'    :  21.0 °C
  ...
=================================
```

**c) Variabili di supporto**
- `i` (`int`): indice del ciclo.

**d) Vincoli**
- Gli array `giorni` e `temperature` devono avere la stessa dimensione.
- Il formato `%5.1f` garantisce allineamento colonne con un decimale.

**e) Assunzioni**
- I dati sono statici e formalmente corretti.
- Le temperature sono espresse in gradi Celsius.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare intestazione con bordi.
2. Per i da 0 a GIORNI_SETTIMANA - 1:
   a. Stampare giorni[i] e temperature[i] allineati.
3. Stampare riga di chiusura.
```

---

### Caso d'uso 2 – Media e giorni sopra media

**a) Input**
Array `temperature`.

**b) Output**
```
Temperatura media : 19.8 °C

Giorni sopra la media (> 19.8 °C):
  Martedi': 21.0 °C (+1.2 rispetto alla media)
  ...
Totale: 3 giorni su 7
```

**c) Variabili di supporto**
- `somma` (`double`): accumulatore per la media.
- `media` (`double`): risultato della divisione.
- `sopra_media` (`int`): contatore giorni sopra soglia.

**d) Vincoli**
- La media deve essere calcolata prima del ciclo di confronto.
- Il confronto usa `>` (non `>=`).

**e) Assunzioni**
- L'array contiene esattamente `GIORNI_SETTIMANA` elementi validi.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare somma = 0.0.
2. Per i da 0 a GIORNI_SETTIMANA - 1: somma += temperature[i].
3. media = somma / GIORNI_SETTIMANA.
4. Per i da 0 a GIORNI_SETTIMANA - 1:
   a. Se temperature[i] > media: stampare e incrementare sopra_media.
5. Stampare totale.
```

---

### Caso d'uso 3 – Variazione giornaliera

**a) Input**
Array `temperature`.

**b) Output**
```
Variazione giornaliera:
  giorno 1 -> giorno 2: +2.5 °C (in salita)
  giorno 2 -> giorno 3: +2.4 °C (in salita)
  giorno 3 -> giorno 4: -1.3 °C (in discesa)
  ...
```

**c) Variabili di supporto**
- `variazione` (`double`): differenza `temperature[i] - temperature[i-1]`.

**d) Vincoli**
- Il ciclo parte da `i = 1` perché il giorno 0 non ha un predecessore.
- I tre casi (positivo, negativo, zero) sono gestiti con `if/else if/else`.

**e) Assunzioni**
- Le temperature consecutive possono essere uguali (variazione = 0.0).

**f) Algoritmo in linguaggio naturale**
```
1. Per i da 1 a GIORNI_SETTIMANA - 1:
   a. variazione = temperature[i] - temperature[i - 1].
   b. Se > 0.0: stampare "(in salita)".
   c. Altrimenti se < 0.0: stampare "(in discesa)".
   d. Altrimenti: stampare "stabile".
```
