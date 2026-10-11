# Analisi – 050-problema-ora-di-punta.c

## 1. Problema

Il contatore della scuola registra i kWh consumati in ognuna delle 24 ore.
Si vogliono il consumo totale, l'ora di punta (consumo massimo) e la fascia
di alto consumo, dalla prima all'ultima ora con consumo almeno pari all'80%
del massimo. I consumi si mostrano anche con un grafico a barre di `#`.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `consumi` | `int[]` | 24 | kWh per ora, l'indice è l'ora |
| `inizio`, `fine` | `const int *` | — | Estremi dell'array |
| `picco` | `const int *` | — | Elemento con il consumo massimo |
| `prima`, `ultima` | `const int *` | — | Prima e ultima ora oltre la soglia |
| `soglia`, `totale` | `int` | — | 80% del massimo, somma dei consumi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ora di punta

**a) Input** – i 24 consumi

**b) Output** – "Ora di punta: 11:00-12:00 con 70 kWh"

**c) Variabili di supporto** – `picco`, `p`

**d) Vincoli** – l'ora è `picco - inizio`, non un indice salvato a parte

**e) Assunzioni** – a parità di consumo vale la prima ora

**f) Algoritmo in linguaggio naturale**
1. Porre `picco = inizio`.
2. Scorrere con `p`: se `*p > *picco`, porre `picco = p`.

### Caso d'uso 2 – Fascia di alto consumo

**a) Input** – soglia 56 kWh (80% di 70)

**b) Output** – dalle 09:00 alle 16:00, 7 ore

**c) Variabili di supporto** – `prima`, `ultima`

**d) Vincoli** – la fascia comprende anche ore intermedie sotto soglia
(le 13:00 con 52 kWh)

**e) Assunzioni** – esiste almeno un'ora oltre soglia (l'ora di punta)

**f) Algoritmo in linguaggio naturale** – per ogni ora con consumo ≥ soglia:
se `prima` è `NULL` le si assegna `p`; `ultima` riceve sempre `p`. La durata
è `ultima - prima + 1`.

### Caso d'uso 3 – Grafico a barre

**a) Input** – consumo di un'ora, ad esempio 62

**b) Output** – `09:00  62 ############`

**c) Variabili di supporto** – `k`

**d) Vincoli** – un `#` ogni 5 kWh

**e) Assunzioni** – divisione intera

**f) Algoritmo in linguaggio naturale** – stampare `*p / 5` caratteri `#` e,
se `p == picco`, l'indicazione dell'ora di punta.
