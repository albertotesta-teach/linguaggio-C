# Analisi – 060-problema-indice-massa-corporea.c

## 1. Problema
L'utente inserisce peso (kg) e altezza (m). Il programma calcola l'IMC,
determina la categoria con operatori relazionali e logici salvati in
variabili int (0/1) e stampa la categoria con l'operatore ternario annidato.

## 2. Analisi

### Input

| Variabile | Tipo     | Significato   |
|-----------|----------|---------------|
| `peso`    | `double` | Peso in kg    |
| `altezza` | `double` | Altezza in m  |

### Output
Il valore dell'IMC con due decimali, i quattro flag di classificazione
(1 = sì, 0 = no) e il nome della categoria.

### Vincoli
- `altezza > 0`, per evitare la divisione per zero (non verificato dal
  programma)
- Esattamente uno dei quattro flag vale 1, gli altri valgono 0

### Assunzioni
- L'utente inserisce valori positivi e realistici
- Le soglie delle categorie sono quelle standard: 18.5, 25.0, 30.0

### Variabili di supporto

| Variabile    | Tipo     | Significato                                  |
|--------------|----------|----------------------------------------------|
| `imc`        | `double` | Indice di Massa Corporea = peso / altezza²   |
| `sottopeso`  | `int`    | 1 se IMC < 18.5, altrimenti 0                |
| `normopeso`  | `int`    | 1 se 18.5 ≤ IMC < 25.0, altrimenti 0         |
| `sovrappeso` | `int`    | 1 se 25.0 ≤ IMC < 30.0, altrimenti 0         |
| `obesita`    | `int`    | 1 se IMC ≥ 30.0, altrimenti 0                |

Costanti: `SOGLIA_SOTTOPESO=18.5`, `SOGLIA_NORMOPESO=25.0`,
`SOGLIA_SOVRAPPESO=30.0`

### Algoritmo in linguaggio naturale
1. Acquisire peso e altezza.
2. Calcolare `imc = peso / (altezza × altezza)`.
3. Calcolare i quattro flag con operatori relazionali e logici.
4. Stampare i flag e la categoria, scelta con l'operatore ternario annidato.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Normopeso
- **Input:** peso = 70.0, altezza = 1.75
- **Valori intermedi attesi:** imc = 70.0 / 3.0625 = 22.857…;
  normopeso = (imc >= 18.5) && (imc < 25.0) = 1
- **Output atteso:**
```
IMC:     22.86

Classificazione (1=si', 0=no)
Sottopeso  (IMC < 18.5):        0
Normopeso  (18.5 <= IMC < 25):  1
Sovrappeso (25 <= IMC < 30):    0
Obesita'   (IMC >= 30):         0

Categoria: Normopeso
```

### Test 2 – Sottopeso
- **Input:** peso = 50.0, altezza = 1.72
- **Valori intermedi attesi:** imc = 50.0 / 2.9584 = 16.90…;
  sottopeso = (imc < 18.5) = 1
- **Output atteso (righe significative):**
```
IMC:     16.91
Sottopeso  (IMC < 18.5):        1
Normopeso  (18.5 <= IMC < 25):  0
Categoria: Sottopeso
```

### Test 3 – Obesità
- **Input:** peso = 100.0, altezza = 1.70
- **Valori intermedi attesi:** imc = 100.0 / 2.89 = 34.60…;
  obesita = (imc >= 30.0) = 1
- **Output atteso (righe significative):**
```
IMC:     34.60
Sottopeso  (IMC < 18.5):        0
Normopeso  (18.5 <= IMC < 25):  0
Sovrappeso (25 <= IMC < 30):    0
Obesita'   (IMC >= 30):         1

Categoria: Obesita'
```
