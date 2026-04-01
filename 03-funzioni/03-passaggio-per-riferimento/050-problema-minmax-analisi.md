# Analisi – 050-problema-minmax.c

## 1. Problema
Un laboratorio raccoglie cinque misurazioni di temperatura durante la giornata
e vuole conoscere il valore minimo, il massimo, la media e l'escursione termica
(differenza tra massimo e minimo). La funzione `calcola_minmax` deve produrre
due risultati (min e max) in una sola chiamata: il passaggio per riferimento
permette di scrivere entrambi i valori direttamente nelle variabili del
chiamante senza dover eseguire due scansioni separate.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Descrizione |
|---|---|---|
| `v1`…`v5` | double (param. IN) | Cinque misurazioni di temperatura |
| `min`, `max` | double* (param. OUT) | Puntatori alle variabili da popolare |
| `media` | double | Media aritmetica calcolata da `calcola_media` |
| `escursione` | double | Differenza massimo - minimo |

| Funzione | Firma | Descrizione |
|---|---|---|
| `calcola_minmax` | `void(double×5, double*, double*)` | Trova min e max tra cinque valori |
| `calcola_media` | `double(double×5)` | Media aritmetica |
| `stampa_report` | `void(double×5)` | Report completo della stazione |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Report stazione con valori distinti

**a) Input** – misurazioni: 18.5, 22.0, 24.3, 21.5, 19.0

**b) Output**
```
Misurazioni: 18.5  22.0  24.3  21.5  19.0
-------------------------------------------
Minimo:      18.5 C
Massimo:     24.3 C
Media:       21.1 C
Escursione:   5.8 C
```

**c) Variabili di supporto** – `min`, `max` locali a `stampa_report`, popolate da `calcola_minmax`

**d) Vincoli** – i puntatori `min` e `max` devono puntare a variabili valide (non NULL)

**e) Assunzioni** – almeno un valore è presente (la funzione non gestisce il caso n=0)

**f) Algoritmo in linguaggio naturale**
1. Inizializzare `*min = *max = v1`
2. Per ciascuno dei valori rimanenti (v2…v5):
   - Se il valore < `*min`: aggiornare `*min`
   - Se il valore > `*max`: aggiornare `*max`
3. Calcolare media con `calcola_media`
4. Calcolare escursione come `max - min`

### Caso d'uso 2 – Tutti i valori uguali

**a) Input** – misurazioni: 20.0, 20.0, 20.0, 20.0, 20.0

**b) Output** – min = 20.0, max = 20.0, escursione = 0.0

**c) Variabili di supporto** – nessuna aggiuntiva

**d) Vincoli** – l'algoritmo deve funzionare anche senza variazioni

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Inizializzare `*min = *max = 20.0`
2. Tutti i confronti risultano falsi: min e max rimangono 20.0
3. Escursione = 20.0 - 20.0 = 0.0

### Caso d'uso 3 – Valori negativi (stazione montana in inverno)

**a) Input** – misurazioni: -8.0, -3.5, 1.0, -1.5, -6.0

**b) Output** – min = -8.0, max = 1.0, escursione = 9.0

**c) Variabili di supporto** – nessuna aggiuntiva

**d) Vincoli** – l'algoritmo usa confronti `<` e `>` che funzionano correttamente anche con negativi

**e) Assunzioni** – i valori sono nel range fisicamente plausibile per temperature atmosferiche

**f) Algoritmo in linguaggio naturale** – identico al caso d'uso 1; la presenza di negativi non richiede modifiche
