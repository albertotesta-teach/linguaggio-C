# Analisi – 060-problema-giudizio-voto.c

## 1. Problema

Nel registro elettronico ogni voto in decimi va accompagnato da un giudizio
sintetico e da un livello di apprendimento. Dato un voto intero da 1 a 10,
il programma stampa giudizio, livello ed esito (sufficiente o insufficiente,
con i punti mancanti).

| Voto | Giudizio | Livello |
|------|----------|---------|
| 1–3 | gravemente insufficiente | non raggiunto |
| 4 | insufficiente | non raggiunto |
| 5 | mediocre | in via di acquisizione |
| 6 | sufficiente | base |
| 7 | discreto | intermedio |
| 8 | buono | intermedio |
| 9 | distinto | avanzato |
| 10 | ottimo | avanzato |

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                        |
|-----------|-------|------------------------------------|
| `voto`    | `int` | Voto in decimi, senza mezzi voti   |

### Output
Il giudizio, il livello di apprendimento e l'esito: "SUFFICIENTE", oppure
"INSUFFICIENTE" con i punti mancanti alla sufficienza (al singolare se manca
un solo punto). Per un voto fuori intervallo: "Voto N non valido."

### Vincoli
- Il voto è compreso tra 1 e 10; se non lo è nessuno `switch` viene eseguito
- Entrambi gli `switch` hanno il `default`, anche se il voto è già stato
  controllato
- La sufficienza è un intervallo (voto ≥ 6): si esprime con un `if`, non
  con lo `switch`

### Assunzioni
- L'utente inserisce un numero intero

### Variabili di supporto

| Variabile     | Tipo        | Significato                     |
|---------------|-------------|---------------------------------|
| `voto_valido` | `int` (0/1) | Voto nell'intervallo [1, 10]    |

Il voto ha dieci valori discreti: due `switch` lo trasformano in giudizio e
livello. I raggruppamenti sono diversi nei due casi (il voto 4 ha un giudizio
proprio ma condivide il livello con 1–3), per questo gli `switch` sono due.

### Algoritmo in linguaggio naturale
1. Leggere il voto.
2. Calcolare `voto_valido`; se falso stampare un errore e terminare.
3. Primo `switch`: stampare il giudizio.
4. Secondo `switch`: stampare il livello di apprendimento.
5. Se il voto è almeno 6 stampare "SUFFICIENTE", altrimenti "INSUFFICIENTE"
   con i punti mancanti (`6 - voto`); la scelta tra "manca/mancano" e
   "punto/punti" si fa con il ternario.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Voto sufficiente
- **Input:** voto 8
- **Output atteso:** "Giudizio: buono", "Livello di apprendimento: intermedio",
  "Esito: SUFFICIENTE"

### Test 2 – Voto insufficiente di un punto
- **Cosa si verifica:** la forma al singolare scelta con il ternario
- **Input:** voto 5
- **Output atteso:** "mediocre", "in via di acquisizione",
  "Esito: INSUFFICIENTE - manca 1 punto alla sufficienza"

### Test 3 – Voto non valido
- **Cosa si verifica:** nessuno `switch` viene eseguito
- **Input:** voto 11 oppure 0
- **Output atteso:** "Voto 11 non valido." (oppure "Voto 0 non valido.")
