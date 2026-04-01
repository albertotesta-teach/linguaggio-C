# Analisi – 060-problema-indice-massa-corporea.c

## 1. Problema
L'utente inserisce peso (kg) e altezza (m). Il programma calcola l'IMC,
determina la categoria con operatori relazionali e logici salvati in
variabili int (0/1) e stampa la categoria con l'operatore ternario annidato.

## 2. Analisi generale e struttura dati

| Variabile     | Tipo     | Significato                                        |
|---------------|----------|----------------------------------------------------|
| `peso`        | `double` | Peso in kg                                         |
| `altezza`     | `double` | Altezza in m                                       |
| `imc`         | `double` | Indice di Massa Corporea = peso / altezza²         |
| `sottopeso`   | `int`    | 1 se IMC < 18.5, altrimenti 0                      |
| `normopeso`   | `int`    | 1 se 18.5 ≤ IMC < 25.0, altrimenti 0              |
| `sovrappeso`  | `int`    | 1 se 25.0 ≤ IMC < 30.0, altrimenti 0              |
| `obesita`     | `int`    | 1 se IMC ≥ 30.0, altrimenti 0                     |

Costanti: `SOGLIA_SOTTOPESO=18.5`, `SOGLIA_NORMOPESO=25.0`, `SOGLIA_SOVRAPPESO=30.0`

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Normopeso

**a) Input**
- peso = 70.0, altezza = 1.75

**b) Output**
```
IMC:     22.86

Classificazione (1=si', 0=no)
Sottopeso  (IMC < 18.5):        0
Normopeso  (18.5 <= IMC < 25):  1
Sovrappeso (25 <= IMC < 30):    0
Obesita'   (IMC >= 30):         0

Categoria: Normopeso
```

**c) Variabili di supporto**
- imc = 70.0 / (1.75 × 1.75) = 70.0 / 3.0625 = 22.857...
- normopeso = (22.86 >= 18.5) && (22.86 < 25.0) = 1 && 1 = 1

**d) Vincoli**
- `altezza > 0` per evitare divisione per zero (non validato)
- Esattamente uno dei quattro flag vale 1, gli altri 0

**e) Assunzioni**
- L'utente inserisce valori positivi e realistici

**f) Algoritmo in linguaggio naturale**
1. Acquisire peso e altezza
2. Calcolare imc = peso / (altezza × altezza)
3. Calcolare i quattro flag con operatori relazionali e logici
4. Stampare i flag e la categoria con operatore ternario

---

### Caso d'uso 2 – Sottopeso

**a) Input**
- peso = 50.0, altezza = 1.72

**b) Output**
```
IMC:     16.91
Sottopeso  (IMC < 18.5):        1
Normopeso  (18.5 <= IMC < 25):  0
Categoria: Sottopeso
```

**c) Variabili di supporto**
- imc = 50.0 / (1.72 × 1.72) = 50.0 / 2.9584 = 16.90...
- sottopeso = (16.90 < 18.5) = 1

**d) Vincoli** — identici al caso d'uso 1

**e) Assunzioni** — identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale** — identico al caso d'uso 1

---

### Caso d'uso 3 – Obesità

**a) Input**
- peso = 100.0, altezza = 1.70

**b) Output**
```
IMC:     34.60
Sottopeso  (IMC < 18.5):        0
Normopeso  (18.5 <= IMC < 25):  0
Sovrappeso (25 <= IMC < 30):    0
Obesita'   (IMC >= 30):         1

Categoria: Obesita'
```

**c) Variabili di supporto**
- imc = 100.0 / (1.70 × 1.70) = 100.0 / 2.89 = 34.60...
- obesita = (34.60 >= 30.0) = 1

**d) Vincoli** — identici al caso d'uso 1

**e) Assunzioni** — identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale** — identico al caso d'uso 1
