# Analisi – 050-problema-conversione-temperature.c

## 1. Problema
L'utente inserisce una temperatura in gradi Celsius. Il programma applica
le formule di conversione e stampa il valore equivalente in gradi Fahrenheit
e in Kelvin, con due cifre decimali.

## 2. Analisi

### Input

| Variabile | Tipo     | Significato                            |
|-----------|----------|----------------------------------------|
| `celsius` | `double` | Temperatura inserita dall'utente (°C)  |

### Output
La temperatura espressa in Celsius, Fahrenheit e Kelvin, con due cifre
decimali e colonne allineate.

### Vincoli
- La temperatura non può essere inferiore allo zero assoluto
  (−273.15 °C = 0 K); il programma non verifica questo vincolo, perché il
  controllo dei dati è argomento dei capitoli successivi

### Assunzioni
- L'utente inserisce un valore numerico valido
- La precisione di `double` è sufficiente per le temperature di uso comune

### Variabili di supporto

| Variabile    | Tipo     | Significato                    |
|--------------|----------|--------------------------------|
| `fahrenheit` | `double` | Risultato della conversione in °F |
| `kelvin`     | `double` | Risultato della conversione in K  |

Costanti `#define`:
- `FATTORE_F = 9.0/5.0` — fattore moltiplicativo per la formula Fahrenheit
- `OFFSET_F = 32.0` — offset additivo per la formula Fahrenheit
- `OFFSET_K = 273.15` — offset per la conversione in Kelvin

### Algoritmo in linguaggio naturale
1. Acquisire la temperatura in Celsius.
2. Calcolare Fahrenheit = Celsius × 9/5 + 32.
3. Calcolare Kelvin = Celsius + 273.15.
4. Stampare i tre valori con due cifre decimali.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Temperatura ambiente (caso tipico)
- **Input:** celsius = 20.0
- **Valori intermedi attesi:** fahrenheit = 20.0 × 1.8 + 32.0 = 68.0;
  kelvin = 20.0 + 273.15 = 293.15
- **Output atteso:**
```
--- Risultato ---
Celsius:         20.00 °C
Fahrenheit:      68.00 °F
Kelvin:         293.15 K
```

### Test 2 – Punto di ebollizione dell'acqua
- **Cosa si verifica:** un valore di riferimento noto
- **Input:** celsius = 100.0
- **Valori intermedi attesi:** fahrenheit = 212.0; kelvin = 373.15
- **Output atteso:**
```
Celsius:        100.00 °C
Fahrenheit:     212.00 °F
Kelvin:         373.15 K
```

### Test 3 – Temperatura sottozero
- **Cosa si verifica:** i valori negativi sono gestiti correttamente
  dall'aritmetica su `double`
- **Input:** celsius = -40.0
- **Valori intermedi attesi:** fahrenheit = −40.0 × 1.8 + 32.0 = −40.0
  (curiosità: −40 °C = −40 °F è l'unico valore uguale nelle due scale);
  kelvin = 233.15
- **Output atteso:**
```
Celsius:        -40.00 °C
Fahrenheit:     -40.00 °F
Kelvin:         233.15 K
```
