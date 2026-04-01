# Analisi – 050-problema-conversione-temperature.c

## 1. Problema
L'utente inserisce una temperatura in gradi Celsius. Il programma applica
le formule di conversione e stampa il valore equivalente in gradi Fahrenheit
e in Kelvin, con due cifre decimali.

## 2. Analisi generale e struttura dati

| Variabile     | Tipo     | Significato                              |
|---------------|----------|------------------------------------------|
| `celsius`     | `double` | Temperatura inserita dall'utente (°C)    |
| `fahrenheit`  | `double` | Risultato conversione in °F              |
| `kelvin`      | `double` | Risultato conversione in K               |

Costanti `#define`:
- `FATTORE_F = 9.0/5.0` — fattore moltiplicativo per la formula Fahrenheit
- `OFFSET_F = 32.0` — offset additivo per la formula Fahrenheit
- `OFFSET_K = 273.15` — offset per la conversione in Kelvin

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Temperatura ambiente

**a) Input**
- celsius = 20.0

**b) Output**
```
--- Risultato ---
Celsius:         20.00 °C
Fahrenheit:      68.00 °F
Kelvin:         293.15 K
```

**c) Variabili di supporto**
- fahrenheit = 20.0 * 1.8 + 32.0 = 68.0
- kelvin     = 20.0 + 273.15 = 293.15

**d) Vincoli**
- `kelvin` non può essere negativo: il valore minimo fisicamente possibile
  è 0 K (zero assoluto = −273.15 °C); il programma non valida questo vincolo
  (argomento dei capitoli successivi)

**e) Assunzioni**
- L'utente inserisce un valore numerico valido
- La precisione di `double` è sufficiente per le temperature di uso comune

**f) Algoritmo in linguaggio naturale**
1. Acquisire la temperatura in Celsius
2. Calcolare Fahrenheit = Celsius * 9/5 + 32
3. Calcolare Kelvin = Celsius + 273.15
4. Stampare i tre valori con due cifre decimali

---

### Caso d'uso 2 – Punto di ebollizione dell'acqua

**a) Input**
- celsius = 100.0

**b) Output**
```
Celsius:        100.00 °C
Fahrenheit:     212.00 °F
Kelvin:         373.15 K
```

**c) Variabili di supporto**
- fahrenheit = 100.0 * 1.8 + 32.0 = 212.0
- kelvin     = 100.0 + 273.15 = 373.15

**d) Vincoli**
- Identici al caso d'uso 1

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1

---

### Caso d'uso 3 – Temperatura sottozero

**a) Input**
- celsius = -40.0

**b) Output**
```
Celsius:        -40.00 °C
Fahrenheit:     -40.00 °F
Kelvin:         233.15 K
```

**c) Variabili di supporto**
- fahrenheit = -40.0 * 1.8 + 32.0 = -40.0
  (curiosità: −40 °C = −40 °F è l'unico valore uguale nelle due scale)
- kelvin = -40.0 + 273.15 = 233.15

**d) Vincoli**
- Identici al caso d'uso 1

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1; i valori negativi sono gestiti correttamente
  dall'aritmetica su `double`
