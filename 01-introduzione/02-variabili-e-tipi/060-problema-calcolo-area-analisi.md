# Analisi – 060-problema-calcolo-area.c

## 1. Problema
L'utente sceglie una figura piana (quadrato, rettangolo, cerchio) e inserisce
le misure necessarie. Il programma calcola area e perimetro e li stampa
con quattro cifre decimali. La selezione avviene con `if/else` perché `switch`
non è ancora stato introdotto.

## 2. Analisi generale e struttura dati

| Variabile    | Tipo     | Significato                                  |
|--------------|----------|----------------------------------------------|
| `figura`     | `int`    | Scelta dell'utente: 1=quadrato, 2=rett., 3=cerchio |
| `lato`       | `double` | Lato del quadrato (m)                        |
| `base`       | `double` | Base del rettangolo (m)                      |
| `altezza`    | `double` | Altezza del rettangolo (m)                   |
| `raggio`     | `double` | Raggio del cerchio (m)                       |
| `area`       | `double` | Area calcolata (m²)                          |
| `perimetro`  | `double` | Perimetro calcolato (m)                      |

Costante: `PI_GRECO = 3.14159265358979`

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Quadrato

**a) Input**
- figura = 1, lato = 4.0

**b) Output**
```
--- Quadrato ---
Area:       16.0000 m^2
Perimetro:  16.0000 m
```

**c) Variabili di supporto**
- area = 4.0 * 4.0 = 16.0
- perimetro = 4.0 * 4.0 = 16.0

**d) Vincoli**
- lato > 0 (non validato in questo esempio)

**e) Assunzioni**
- L'utente inserisce valori positivi e coerenti

**f) Algoritmo in linguaggio naturale**
1. Acquisire la scelta della figura
2. Se figura == 1: acquisire lato, calcolare area = lato², perimetro = 4*lato
3. Stampare area e perimetro

---

### Caso d'uso 2 – Rettangolo

**a) Input**
- figura = 2, base = 6.0, altezza = 3.5

**b) Output**
```
--- Rettangolo ---
Area:       21.0000 m^2
Perimetro:  19.0000 m
```

**c) Variabili di supporto**
- area = 6.0 * 3.5 = 21.0
- perimetro = 2.0 * (6.0 + 3.5) = 19.0

**d) Vincoli**
- base > 0 e altezza > 0 (non validati)

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
1. Acquisire la scelta della figura
2. Se figura == 2: acquisire base e altezza
3. Calcolare area = base * altezza, perimetro = 2*(base+altezza)
4. Stampare area e perimetro

---

### Caso d'uso 3 – Cerchio

**a) Input**
- figura = 3, raggio = 5.0

**b) Output**
```
--- Cerchio ---
Area:       78.5398 m^2
Perimetro:  31.4159 m
```

**c) Variabili di supporto**
- area = PI_GRECO * 5.0 * 5.0 = 78.5398...
- perimetro = 2 * PI_GRECO * 5.0 = 31.4159...

**d) Vincoli**
- raggio > 0 (non validato)

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
1. Acquisire la scelta della figura
2. Se figura == 3: acquisire raggio
3. Calcolare area = π*r², perimetro = 2*π*r
4. Stampare area e perimetro
