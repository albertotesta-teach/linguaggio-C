# Analisi – 080-problema-media-pesata.c

## 1. Problema

Nel registro di informatica ogni voto ha un peso percentuale (100 la verifica, 50 l'interrogazione, 25 il laboratorio). Il programma legge coppie voto e peso fino a `0 0`, scarta quelle non valide e stampa la media pesata, la media semplice per confronto e l'esito.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Voto` | `typedef double Voto;` | voto da 1 a 10, anche con il mezzo voto |
| `Peso` | `typedef int Peso;` | peso percentuale |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voti` | `Voto[]` | 20 | Voti validi |
| `pesi` | `Peso[]` | 20 | Pesi paralleli ai voti |
| `voto`, `peso` | `Voto`, `Peso` | — | Coppia letta |
| `n` | `int` | — | Voti memorizzati |
| `finale` | `Voto` | — | Media pesata |

| Funzione | Compito |
|----------|---------|
| `media_pesata(voti, pesi, n)` | Somma di voto × peso divisa per la somma dei pesi |
| `media_semplice(voti, n)` | Media aritmetica |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Inserimento

**a) Input** – `7 100`, `5.5 50`, `8 25`, `9 25`

**b) Output** – 4 voti memorizzati

**c) Variabili di supporto** – `n`

**d) Vincoli** – voto 1-10, peso 1-100

**e) Assunzioni** – il voto si legge con `%lf` perché `Voto` è un double

**f) Algoritmo in linguaggio naturale** – memorizzare la coppia se valida; `0 0` termina.

### Caso d'uso 2 – Coppia non valida

**a) Input** – `11 50`

**b) Output** – "Coppia non valida, scartata."

**c) Variabili di supporto** – —

**d) Vincoli** – la coppia non entra negli array

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare gli intervalli prima di memorizzare.

### Caso d'uso 3 – Risultato

**a) Input** – i quattro voti del caso 1

**b) Output** – media semplice 7.38, media pesata 7.00, sufficiente

**c) Variabili di supporto** – `finale`

**d) Vincoli** – sufficiente da 6 in su

**e) Assunzioni** – almeno un voto inserito

**f) Algoritmo in linguaggio naturale** – calcolare le due medie; se non ci sono voti stampare "Nessun voto inserito."
