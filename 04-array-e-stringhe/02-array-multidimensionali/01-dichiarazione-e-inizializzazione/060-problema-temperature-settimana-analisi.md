# Analisi – 060-problema-temperature-settimana.c

## 1. Problema

Una stazione meteo registra la temperatura in quattro fasce orarie (notte,
mattina, pomeriggio, sera) per sette giorni. Il programma deve stampare la
tabella con la media giornaliera, individuare la rilevazione più alta e più
bassa con giorno e fascia, e calcolare la media settimanale di ogni fascia.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `temp` | `double[][]` | 7 × 4 | Riga = giorno, colonna = fascia oraria |
| `giorni` | `char[][]` | 7 × 12 | Nome del giorno: parallelo alle **righe** |
| `fasce` | `char[][]` | 4 × 12 | Nome della fascia: parallelo alle **colonne** |
| `somma` | `double` | — | Accumulatore riutilizzato per righe e colonne |
| `g_max`, `f_max`, `g_min`, `f_min` | `int` | — | Indici degli estremi |

Novità rispetto agli array monodimensionali: gli array paralleli possono
descrivere sia le righe sia le colonne della matrice.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabella con media giornaliera

**a) Input** – matrici `temp`, `giorni`, `fasce`

**b) Output** – intestazione con i nomi delle fasce, una riga per giorno con
le quattro temperature e la media

**c) Variabili di supporto** – `somma`

**d) Vincoli** – la media di un giorno è la somma della sua riga divisa per `FASCE`

**e) Assunzioni** – una rilevazione per ogni fascia

**f) Algoritmo in linguaggio naturale**
1. Stampare l'intestazione scorrendo `fasce`.
2. Per ogni giorno: azzerare `somma`, stampare il nome, poi ogni temperatura
   della riga sommandola; stampare `somma / FASCE`.

### Caso d'uso 2 – Massimo e minimo con posizione

**a) Input** – matrice `temp`

**b) Output** – "Temperatura massima: 21.0 (Domenica, Pomeriggio)" e
"Temperatura minima : 6.5 (Venerdi', Notte)"

**c) Variabili di supporto** – `g_max`, `f_max`, `g_min`, `f_min`

**d) Vincoli** – si memorizzano due indici per ogni estremo; partono da
(0, 0), cioè dall'ipotesi che il primo elemento sia l'estremo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Porre tutti gli indici a 0.
2. Per ogni cella: se è maggiore di `temp[g_max][f_max]` aggiornare `g_max`,
   `f_max`; se è minore di `temp[g_min][f_min]` aggiornare `g_min`, `f_min`.
3. Stampare valori e nomi ricavati dagli indici.

### Caso d'uso 3 – Media per fascia

**a) Input** – matrice `temp`

**b) Output** – media settimanale delle quattro fasce (es. Pomeriggio 17.9)

**c) Variabili di supporto** – `somma`

**d) Vincoli** – il ciclo esterno scorre le colonne, quello interno le righe

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Per ogni fascia: azzerare `somma`, sommare la colonna su tutti i giorni.
2. Stampare il nome della fascia e `somma / GIORNI`.
