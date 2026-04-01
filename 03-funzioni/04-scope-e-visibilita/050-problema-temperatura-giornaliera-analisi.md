# Analisi – 050-problema-temperatura-giornaliera.c

## 1. Problema
Una stazione meteorologica registra le temperature rilevate ogni due ore
durante una giornata. Il sistema deve calcolare e stampare al termine il
valore minimo, massimo, medio e l'escursione termica. Le variabili globali
conservano lo stato accumulato tra una rilevazione e la successiva, senza
dover passare strutture dati complesse tra le funzioni.

## 2. Analisi generale e struttura dati

| Costante | Valore | Descrizione |
|---|---|---|
| `NESSUNA_RILEVAZIONE` | -999.0 | Sentinella per indicare assenza di rilevazioni |

| Variabile globale | Tipo | Descrizione |
|---|---|---|
| `temp_minima` | double | Minima rilevata finora (-999.0 se nessuna) |
| `temp_massima` | double | Massima rilevata finora (-999.0 se nessuna) |
| `temp_somma` | double | Somma di tutte le temperature (per calcolare la media) |
| `num_rilevazioni` | int | Numero di rilevazioni effettuate |

| Funzione | Firma | Descrizione |
|---|---|---|
| `registra_temperatura` | `void(double)` | Aggiorna min, max, somma e contatore |
| `stampa_rilevazione` | `void(int, double)` | Stampa ora e temperatura, poi chiama `registra_temperatura` |
| `stampa_report` | `void(void)` | Calcola media e stampa il report finale |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prima rilevazione della giornata

**a) Input** – `ora = 0`, `temp = 4.2`

**b) Output** – `00:00  +4.2 C`; min e max vengono impostati a 4.2

**c) Variabili di supporto** – nessuna aggiuntiva

**d) Vincoli** – il confronto con `NESSUNA_RILEVAZIONE` deve avvenire prima del confronto con min/max

**e) Assunzioni** – la prima temperatura è sempre un valore fisicamente valido

**f) Algoritmo in linguaggio naturale**
1. `temp_minima == NESSUNA_RILEVAZIONE` → assegnare `temp_minima = 4.2`
2. `temp_massima == NESSUNA_RILEVAZIONE` → assegnare `temp_massima = 4.2`
3. Incrementare `num_rilevazioni`, aggiungere a `temp_somma`

### Caso d'uso 2 – Rilevazione che aggiorna il massimo

**a) Input** – `ora = 14`, `temp = 15.6` (massimo della giornata)

**b) Output** – `14:00  +15.6 C`; `temp_massima` viene aggiornata a 15.6

**c) Variabili di supporto** – nessuna

**d) Vincoli** – il controllo `temp > temp_massima` deve usare `>` e non `>=` (indifferente sul risultato, ma semanticamente corretto)

**e) Assunzioni** – in caso di parità si mantiene il valore già registrato

**f) Algoritmo in linguaggio naturale**
1. `15.6 > temp_massima` (es. 14.2) → `temp_massima = 15.6`
2. `15.6 < temp_minima` (es. 3.1) → condizione falsa, min invariato

### Caso d'uso 3 – Report finale

**a) Input** – nessuno (legge le variabili globali)

**b) Output**
```
--- Report giornaliero ---
Rilevazioni:   12
Temperatura minima:   +3.1 C
Temperatura massima: +15.6 C
Temperatura media:    +7.7 C
Escursione termica:   12.5 C
```

**c) Variabili di supporto** – `media` (double, locale a `stampa_report`)

**d) Vincoli** – la media è calcolata solo se `num_rilevazioni > 0`

**e) Assunzioni** – almeno una rilevazione è disponibile prima di chiamare `stampa_report`

**f) Algoritmo in linguaggio naturale**
1. Se `num_rilevazioni == 0`: stampare messaggio di assenza dati
2. Altrimenti: `media = temp_somma / num_rilevazioni`
3. Stampare min, max, media, escursione termica
