# Analisi – 040-problema-tabella-conversione.c

## 1. Problema

Stampare una tabella di conversione delle temperature da gradi Celsius a
Fahrenheit e Kelvin, per un intervallo e un passo scelti dall'utente
(es. da -20 a 100 ogni 20 gradi). Le righe di 0 °C e 100 °C vanno
evidenziate.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `inizio`, `fine`, `passo` | `int` | Parametri della tabella |
| `celsius` | `int` | Variabile di controllo del for |
| `fahrenheit`, `kelvin` | `double` | Valori convertiti |
| `righe` | `int` | Contatore delle righe stampate |

Formule: `F = C * 9 / 5 + 32` (con `9.0` per la divisione reale) e
`K = C + 273.15`.

Una volta letti i tre parametri il numero di righe è determinato: si usa il
`for`. I parametri si validano con `do-while`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabella da -20 a 100 ogni 20 gradi

**a) Input** – inizio -20, fine 100, passo 20

**b) Output** – 7 righe; la riga di 0 °C con "l'acqua gela", quella di 100 °C
con "l'acqua bolle"

**c) Variabili di supporto** – `righe`

**d) Vincoli** – la temperatura finale è inclusa se raggiunta esattamente dal
passo (condizione `<=`)

**e) Assunzioni** – le temperature sono intere

**f) Algoritmo in linguaggio naturale**
1. Leggere la temperatura iniziale.
2. Leggere la finale ripetendo finché è minore dell'iniziale.
3. Leggere il passo ripetendo finché non è positivo.
4. Stampare l'intestazione.
5. Per `celsius` da `inizio` a `fine` con incremento `passo`: calcolare
   Fahrenheit e Kelvin, stampare la riga, aggiungere l'annotazione se
   `celsius` vale 0 o 100, contare la riga.
6. Stampare il numero di righe.

### Caso d'uso 2 – Dati non validi

**a) Input** – finale -30 con iniziale -20, oppure passo 0

**b) Output** – la richiesta viene ripetuta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – con passo 0 il ciclo non terminerebbe mai; con passo
negativo la condizione `celsius <= fine` resterebbe sempre vera

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passi 2 e 3.

### Caso d'uso 3 – Fine non raggiunta esattamente dal passo

**a) Input** – da 0 a 50 ogni 15

**b) Output** – righe 0, 15, 30, 45: il valore 60 supera la fine e non viene
stampato

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – nessuno in più

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.
