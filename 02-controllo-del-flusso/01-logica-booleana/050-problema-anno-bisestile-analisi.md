# Analisi – 050-problema-anno-bisestile.c

## 1. Problema

Stabilire se un anno inserito dall'utente è bisestile secondo il calendario
gregoriano. La regola contiene un'eccezione e un'eccezione all'eccezione:

- un anno divisibile per 4 è bisestile,
- ma gli anni divisibili per 100 non lo sono,
- tranne quelli divisibili per 400, che lo sono.

Il programma deve tradurre la regola in un'unica espressione logica e
mostrare i passaggi intermedi.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                          |
|-----------|-------|--------------------------------------|
| `anno`    | `int` | Anno da verificare, letto da tastiera |

### Output
I valori (0/1) delle tre condizioni elementari, l'esito ("e' bisestile" /
"non e' bisestile") e il numero di giorni di febbraio.

### Vincoli
- Ogni variabile booleana vale solo 0 o 1
- La sola divisibilità per 4 non basta: la condizione `!divisibile_100`
  esclude gli anni secolari
- L'eccezione all'eccezione si aggiunge con OR, perché deve rendere vero un
  risultato che la prima parte renderebbe falso

### Assunzioni
- L'utente inserisce un numero intero
- La regola gregoriana viene applicata anche ad anni precedenti al 1582
  (calendario gregoriano "prolettico")
- Non si controlla che l'anno sia positivo: la regola funziona con qualsiasi
  intero

### Variabili di supporto

| Variabile        | Tipo        | Significato                          |
|------------------|-------------|--------------------------------------|
| `divisibile_4`   | `int` (0/1) | Prima condizione elementare          |
| `divisibile_100` | `int` (0/1) | Seconda condizione elementare        |
| `divisibile_400` | `int` (0/1) | Terza condizione elementare          |
| `bisestile`      | `int` (0/1) | Risultato della regola completa      |

Le tre divisibilità sono salvate in variabili separate per poterle stampare
e per rendere la regola finale leggibile come la frase italiana.

### Algoritmo in linguaggio naturale
1. Leggere l'anno.
2. Calcolare `divisibile_4`, `divisibile_100`, `divisibile_400` con il resto
   della divisione (`anno % n == 0`).
3. Calcolare `bisestile = (divisibile_4 && !divisibile_100) || divisibile_400`.
4. Stampare i valori intermedi e il risultato.
5. Stampare il numero di giorni di febbraio come `28 + bisestile`.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso. I tre test coprono la regola e le sue
due eccezioni.

### Test 1 – Anno divisibile per 4 ma non per 100
- **Input:** 2024
- **Valori intermedi attesi:** divisibile_4 = 1, divisibile_100 = 0,
  divisibile_400 = 0 → la prima parte dell'OR vale 1
- **Output atteso:** "Il 2024 e' bisestile: febbraio ha 29 giorni."

### Test 2 – Anno secolare non bisestile
- **Cosa si verifica:** l'eccezione degli anni divisibili per 100
- **Input:** 1900
- **Valori intermedi attesi:** divisibile_4 = 1, divisibile_100 = 1,
  divisibile_400 = 0 → entrambe le parti dell'OR valgono 0
- **Output atteso:** "Il 1900 non e' bisestile: febbraio ha 28 giorni."

### Test 3 – Anno divisibile per 400
- **Cosa si verifica:** l'eccezione all'eccezione
- **Input:** 2000
- **Valori intermedi attesi:** divisibile_4 = 1, divisibile_100 = 1,
  divisibile_400 = 1 → la prima parte dell'OR vale 0, ma `divisibile_400`
  rende vero il risultato
- **Output atteso:** "Il 2000 e' bisestile: febbraio ha 29 giorni."
