# Analisi – 040-problema-tabella-conversione.c

## 1. Problema

Stampare una tabella di conversione delle temperature da gradi Celsius a
Fahrenheit e Kelvin, per un intervallo e un passo scelti dall'utente
(es. da -20 a 100 ogni 20 gradi). Le righe di 0 °C e 100 °C vanno
evidenziate.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                              |
|-----------|-------|------------------------------------------|
| `inizio`  | `int` | Temperatura iniziale della tabella (°C)  |
| `fine`    | `int` | Temperatura finale della tabella (°C)    |
| `passo`   | `int` | Incremento tra una riga e la successiva  |

### Output
Un'intestazione e una riga per ogni temperatura con i valori in Celsius,
Fahrenheit e Kelvin; la riga di 0 °C è annotata con "l'acqua gela", quella
di 100 °C con "l'acqua bolle". In fondo il numero di righe stampate.

### Vincoli
- `fine >= inizio`: la richiesta si ripete finché non è rispettato
- `passo > 0`: con passo 0 il ciclo non terminerebbe mai, con passo negativo
  la condizione `celsius <= fine` resterebbe sempre vera
- La temperatura finale è inclusa solo se il passo la raggiunge esattamente
  (condizione `<=`)

### Assunzioni
- Le temperature sono intere
- L'utente inserisce numeri interi

### Variabili di supporto

| Variabile    | Tipo     | Significato                       |
|--------------|----------|-----------------------------------|
| `celsius`    | `int`    | Variabile di controllo del for    |
| `fahrenheit` | `double` | Valore convertito in °F           |
| `kelvin`     | `double` | Valore convertito in K            |
| `righe`      | `int`    | Contatore delle righe stampate    |

Formule: `F = C * 9 / 5 + 32` (con `9.0` per la divisione reale) e
`K = C + 273.15`.

Una volta letti i tre parametri il numero di righe è determinato: si usa il
`for`. I parametri si validano con `do-while`.

### Algoritmo in linguaggio naturale
1. Leggere la temperatura iniziale.
2. Leggere la finale ripetendo finché è minore dell'iniziale.
3. Leggere il passo ripetendo finché non è positivo.
4. Stampare l'intestazione.
5. Per `celsius` da `inizio` a `fine` con incremento `passo`: calcolare
   Fahrenheit e Kelvin, stampare la riga, aggiungere l'annotazione se
   `celsius` vale 0 o 100, contare la riga.
6. Stampare il numero di righe.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Tabella da -20 a 100 ogni 20 gradi
- **Input:** inizio -20, fine 100, passo 20
- **Output atteso:** 7 righe (-20, 0, 20, 40, 60, 80, 100); la riga di 0 °C
  con "l'acqua gela", quella di 100 °C con "l'acqua bolle"

### Test 2 – Fine non raggiunta esattamente dal passo
- **Cosa si verifica:** il valore che supera la fine non viene stampato
- **Input:** inizio 0, fine 50, passo 15
- **Output atteso:** 4 righe (0, 15, 30, 45); il valore 60 supera la fine
  e non compare

### Test 3 – Temperatura finale minore dell'iniziale
- **Input:** inizio -20, poi fine -30
- **Output atteso:** la richiesta della temperatura finale viene ripetuta

### Test 4 – Passo non positivo
- **Input:** passo 0 oppure -5
- **Output atteso:** la richiesta del passo viene ripetuta
