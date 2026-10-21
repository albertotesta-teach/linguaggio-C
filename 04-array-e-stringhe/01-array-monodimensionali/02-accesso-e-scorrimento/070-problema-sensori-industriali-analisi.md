# Analisi – 070-problema-sensori-industriali.c

## 1. Problema

Un impianto industriale dispone di 8 sensori di temperatura. Il sistema deve
acquisire le letture, mostrarle in una dashboard con indicatore di stato,
segnalare i sensori fuori dalla soglia operativa e calcolare la temperatura
media dell'impianto.

---

## 2. Analisi

### Input

| Variabile | Tipo       | Dimensione | Descrizione                                |
|-----------|------------|------------|--------------------------------------------|
| `letture` | `double[]` | 8          | Temperatura rilevata da ogni sensore (°C)  |

### Output
- La dashboard: per ogni sensore il codice (S01…S08), la temperatura con un
  decimale e lo stato "OK" o "ALLARME";
- l'elenco dei sensori fuori soglia, ciascuno con l'indicazione
  "TROPPO BASSA" o "TROPPO ALTA", oppure "Tutti i sensori nella norma.";
- la temperatura media dell'impianto e il numero di sensori in allarme.

### Vincoli
- Una lettura è in allarme se è minore di `SOGLIA_MIN` (10 °C) o maggiore di
  `SOGLIA_MAX` (80 °C): i valori uguali alle soglie sono OK
- Lo stato si costruisce carattere per carattere, con il terminatore
  `'\0'`, senza funzioni di libreria
- La media si calcola su tutti i sensori, anche quelli in allarme

### Assunzioni
- L'utente inserisce numeri; il valore delle letture non viene validato in
  ingresso (un valore fuori soglia è un dato legittimo da segnalare)

### Variabili di supporto

| Variabile     | Tipo      | Dimensione | Descrizione                             |
|---------------|-----------|------------|-----------------------------------------|
| `stato`       | `char[]`  | 10         | "OK" o "ALLARME"                        |
| `num_allarmi` | `int`     | —          | Numero di sensori fuori soglia          |
| `somma`       | `double`  | —          | Accumulatore per la media               |
| `SOGLIA_MIN`, `SOGLIA_MAX` | `#define` | — | 10.0 e 80.0 °C                    |
| `NUM_SENSORI` | `#define` | 8          | Numero di sensori                       |

### Algoritmo in linguaggio naturale
1. Leggere la temperatura di ciascuno degli 8 sensori.
2. Per ogni sensore costruire lo stato ("ALLARME" se fuori dall'intervallo
   [10, 80], altrimenti "OK") e stampare la riga della dashboard.
3. Per ogni sensore: se la lettura è sotto la soglia minima segnalarla come
   troppo bassa, altrimenti se è sopra la massima come troppo alta; contare
   gli allarmi. Se non ce ne sono stampare che tutti sono nella norma.
4. Calcolare la media e stamparla con il numero di allarmi.

---

## 3. Casi di test

Per ogni caso si esegue il programma con le 8 letture indicate e si
confronta quanto stampato con l'output atteso.

### Test 1 – Allarmi e valori sulle soglie
- **Cosa si verifica:** 10.0 e 80.0 sono OK, 5.0 e 81.0 sono in allarme
- **Input:** 65, 5, 42.5, 81, 10, 80, 55, 30
- **Output atteso:**
```
  S01        |     65.0 °C | OK
  S02        |      5.0 °C | ALLARME
  S03        |     42.5 °C | OK
  S04        |     81.0 °C | ALLARME
  S05        |     10.0 °C | OK
  S06        |     80.0 °C | OK
  S07        |     55.0 °C | OK
  S08        |     30.0 °C | OK

Sensori fuori soglia [10°C - 80°C]:
  [!] S02: 5.0°C - TEMPERATURA TROPPO BASSA
  [!] S04: 81.0°C - TEMPERATURA TROPPO ALTA

Temperatura media impianto: 46.1°C
Sensori in allarme: 2 su 8
```

### Test 2 – Impianto nella norma
- **Cosa si verifica:** il messaggio alternativo
- **Input:** 20, 30, 40, 50, 60, 70, 25, 35
- **Output atteso:** tutti gli stati OK, `Tutti i sensori nella norma.`,
  `Temperatura media impianto: 41.2°C`, `Sensori in allarme: 0 su 8`
