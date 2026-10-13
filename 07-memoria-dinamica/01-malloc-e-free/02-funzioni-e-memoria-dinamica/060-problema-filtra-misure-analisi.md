# Analisi – 060-problema-filtra-misure.c

## 1. Problema

Un sensore misura la CO2 in aula; alcune letture sono errori (sotto 300 o sopra 5000 ppm) e da 1000 ppm in su bisogna aprire le finestre. La funzione filtra restituisce un nuovo array con le sole misure in un intervallo e ne comunica la lunghezza con un parametro di uscita. Il programma filtra due volte e libera i tre blocchi.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `letture` | `double *` | n (heap) | Letture del sensore |
| `valide`, `alte` | `double *` | quante servono (heap) | Risultati dei due filtri, NULL se vuoti |
| `n_valide`, `n_alte` | `int` | — | Lunghezze restituite da filtra |

| Funzione | Compito |
|----------|---------|
| `filtra(misure, n, minimo, massimo, &quante)` | Conta, alloca il blocco giusto, copia; NULL se non resta nessuna misura |
| `stampa(titolo, v, n)` | Valori e media, oppure "nessuna" |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Letture con errori

**a) Input** – `8`, poi `620 845 9999 1020 1180 0 960 1310`

**b) Output** – 6 valide (media 989), 2 scartate, 3 da 1000 in su (1020 1180 1310)

**c) Variabili di supporto** – `n_valide`, `n_alte`

**d) Vincoli** – letture valide da 300 a 5000 ppm

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima passata: contare; malloc(conta × sizeof); seconda passata: copiare.

### Caso d'uso 2 – Aria buona

**a) Input** – `3`, poi `500 600 700`

**b) Output** – "Almeno 1000 ppm (aprire le finestre) (0): nessuna"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – conta = 0: nessuna malloc, risultato NULL e quante = 0.

### Caso d'uso 3 – Solo errori

**a) Input** – `2`, poi `0 9000`

**b) Output** – "Letture valide (0): nessuna"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il secondo filtro riceve un array vuoto e restituisce NULL.

### Caso d'uso 4 – Memoria insufficiente

**a) Input** – —

**b) Output** – "Memoria insufficiente."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – quante > 0 ma risultato NULL.
