# Analisi – 050-problema-misure-continue.c

## 1. Problema

Una centralina misura il rumore della mensa ogni minuto finché il responsabile scrive STOP. Le letture vanno in un vettore dinamico di double. Alla fine il programma stampa il massimo con il suo minuto, la media mobile su 5 minuti (dal quinto minuto in poi) e quanti minuti hanno media mobile sopra 80 dB.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Serie` | `dati (double *), n, capacita` | vettore dinamico di letture |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `rumore` | `Serie *` | struct + blocco di n double (heap) | Letture in ordine di tempo |
| `parola` | `char[]` | 16 | Lettura come testo, per riconoscere STOP |
| `valore`, `media` | `double` | — | Lettura convertita e media della finestra |
| `massimo`, `sopra` | `int` | — | Indice del massimo e minuti oltre soglia |

| Funzione | Compito |
|----------|---------|
| `crea_serie, aggiungi, lunghezza, elemento, distruggi_serie` | Funzioni del vettore di double |
| `media_mobile(s, fine)` | Media degli elementi da fine - 4 a fine |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Un pranzo

**a) Input** – `72 75 78 81 84 79 86 90 88 -3 85 rumore 76 74 70 68 STOP`

**b) Output** – 14 letture; massimo 90.0 al minuto 8; 6 minuti sopra 80 dB

**c) Variabili di supporto** – `media`

**d) Vincoli** – lettura ≥ 0

**e) Assunzioni** – una lettura al minuto

**f) Algoritmo in linguaggio naturale** – la media mobile parte dall'indice FINESTRA - 1.

### Caso d'uso 2 – Letture scartate

**a) Input** – `-3`, `rumore`

**b) Output** – "-3 scartata", "rumore scartata"

**c) Variabili di supporto** – —

**d) Vincoli** – numero non negativo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sscanf sul testo letto; se non è STOP e non è un numero valido si scarta.

### Caso d'uso 3 – Meno di 5 letture

**a) Input** – `70 72 STOP`

**b) Output** – messaggio: servono almeno 5 letture per la media mobile

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo della media non parte.
