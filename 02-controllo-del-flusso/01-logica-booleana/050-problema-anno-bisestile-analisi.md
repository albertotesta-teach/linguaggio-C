# Analisi – 050-problema-anno-bisestile.c

## 1. Problema

Stabilire se un anno inserito dall'utente è bisestile secondo il calendario
gregoriano. La regola contiene un'eccezione e un'eccezione all'eccezione:

- un anno divisibile per 4 è bisestile,
- ma gli anni divisibili per 100 non lo sono,
- tranne quelli divisibili per 400, che lo sono.

Il programma deve tradurre la regola in un'unica espressione logica e
mostrare i passaggi intermedi.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `anno` | `int` | Anno da verificare, letto da tastiera |
| `divisibile_4` | `int` (0/1) | Prima condizione elementare |
| `divisibile_100` | `int` (0/1) | Seconda condizione elementare |
| `divisibile_400` | `int` (0/1) | Terza condizione elementare |
| `bisestile` | `int` (0/1) | Risultato della regola completa |

Le tre divisibilità sono salvate in variabili separate per poterle stampare
e per rendere la regola finale leggibile come la frase italiana.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Anno divisibile per 4 ma non per 100

**a) Input** – un anno come 2024

**b) Output** – i valori delle condizioni elementari e il messaggio
"Il 2024 e' bisestile: febbraio ha 29 giorni."

**c) Variabili di supporto** – le tre variabili `divisibile_*`

**d) Vincoli** – ogni variabile booleana vale solo 0 o 1

**e) Assunzioni** – l'utente inserisce un numero intero

**f) Algoritmo in linguaggio naturale**
1. Leggere l'anno.
2. Calcolare `divisibile_4`, `divisibile_100`, `divisibile_400` con il resto
   della divisione (`anno % n == 0`).
3. Calcolare `bisestile = (divisibile_4 && !divisibile_100) || divisibile_400`.
4. Stampare i valori intermedi e il risultato.
5. Stampare il numero di giorni di febbraio come `28 + bisestile`.

### Caso d'uso 2 – Anno secolare non bisestile

**a) Input** – un anno come 1900

**b) Output** – "Il 1900 non e' bisestile: febbraio ha 28 giorni."

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – la sola divisibilità per 4 non basta: la condizione
`!divisibile_100` rende falsa la prima parte della regola

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1; la prima parte
dell'OR vale 0 e anche `divisibile_400` vale 0, quindi il risultato è 0.

### Caso d'uso 3 – Anno divisibile per 400

**a) Input** – un anno come 2000

**b) Output** – "Il 2000 e' bisestile: febbraio ha 29 giorni."

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – l'eccezione all'eccezione si aggiunge con OR, perché deve
rendere vero un risultato che la prima parte renderebbe falso

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1; la prima parte
dell'OR vale 0, ma `divisibile_400` vale 1 e rende vero il risultato.

### Assunzioni generali

- La regola gregoriana viene applicata anche ad anni precedenti al 1582
  (calendario gregoriano "prolettico").
- Non si controlla che l'anno sia positivo: la regola funziona con qualsiasi
  intero.
