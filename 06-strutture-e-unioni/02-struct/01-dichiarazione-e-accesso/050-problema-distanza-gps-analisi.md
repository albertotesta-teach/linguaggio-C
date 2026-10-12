# Analisi – 050-problema-distanza-gps.c

## 1. Problema

Per l'uscita didattica si leggono le coordinate di partenza e di arrivo (latitudine e longitudine in gradi decimali) e si calcola la distanza in linea d'aria con la formula dell'emisenoverso. Il programma stima anche il tempo a piedi, maggiorando la distanza del 30% e camminando a 4.5 km/h.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Punto` | `latitudine, longitudine` | posizione GPS |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `partenza`, `arrivo` | `Punto` | — | Coordinate lette |
| `dlat`, `dlon`, `a` | `double` | — | Passaggi della formula |
| `km` | `double` | — | Distanza |
| `minuti` | `int` | — | Tempo a piedi arrotondato |

| Funzione | Compito |
|----------|---------|
| `radianti(gradi)` | Conversione da gradi a radianti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Distanza

**a) Input** – `44.9126 8.6157`, `44.9070 8.6040`

**b) Output** – "Distanza in linea d'aria: 1.11 km", tempo 0 h 19 min

**c) Variabili di supporto** – `km`, `minuti`

**d) Vincoli** – raggio terrestre 6371 km

**e) Assunzioni** – la Terra è una sfera

**f) Algoritmo in linguaggio naturale** – applicare la formula ai campi delle due struct.

### Caso d'uso 2 – Coordinate non valide

**a) Input** – `95 10` come latitudine

**b) Output** – "Coordinate non valide."

**c) Variabili di supporto** – —

**d) Vincoli** – latitudine -90..90, longitudine -180..180

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare i quattro campi prima del calcolo.
