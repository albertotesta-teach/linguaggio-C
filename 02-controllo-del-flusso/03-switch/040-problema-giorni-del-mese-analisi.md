# Analisi – 040-problema-giorni-del-mese.c

## 1. Problema

Dati un mese (numero da 1 a 12) e un anno, stampare il nome del mese e il
numero dei suoi giorni, tenendo conto degli anni bisestili per febbraio.
La regola è quella della filastrocca: novembre, aprile, giugno e settembre
hanno 30 giorni, febbraio 28 (29 negli anni bisestili), tutti gli altri 31.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                   |
|-----------|-------|-------------------------------|
| `mese`    | `int` | Mese da 1 a 12                |
| `anno`    | `int` | Anno, serve solo per febbraio |

### Output
Il nome del mese, l'anno e il numero di giorni ("Novembre 2025 ha 30
giorni."), oppure, per un mese fuori intervallo, il messaggio
"Mese N: non e' un mese valido (inserire un numero da 1 a 12)."

### Vincoli
- `mese` è compreso tra 1 e 12
- Febbraio ha 29 giorni solo negli anni bisestili (regola gregoriana)
- Ogni gruppo di `case` termina con `break`, compreso il ramo di febbraio
  che contiene un `if-else`
- Entrambi gli `switch` hanno un ramo `default` per i mesi non validi

### Assunzioni
- L'utente inserisce numeri interi

### Variabili di supporto

| Variabile     | Tipo        | Significato                            |
|---------------|-------------|----------------------------------------|
| `giorni`      | `int`       | Numero di giorni del mese (risultato)  |
| `bisestile`   | `int` (0/1) | Regola gregoriana dell'anno bisestile  |
| `mese_valido` | `int` (0/1) | Diventa 0 nel ramo `default`           |

Il valore del mese è un intero con pochi valori possibili: lo `switch` è la
struttura naturale. I mesi con lo stesso numero di giorni si raggruppano in
`case` consecutivi.

### Algoritmo in linguaggio naturale
1. Leggere mese e anno.
2. Calcolare `bisestile` con la regola gregoriana.
3. Porre `mese_valido = 1`.
4. Primo `switch`: stampare il nome del mese (o "Mese N" se non valido).
5. Secondo `switch`: mesi 4, 6, 9, 11 → 30 giorni; mese 2 → 29 se
   bisestile, altrimenti 28; mesi 1, 3, 5, 7, 8, 10, 12 → 31;
   `default` → `mese_valido = 0`.
6. Se il mese è valido stampare anno e giorni, altrimenti un messaggio di errore.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Mese da 30 giorni
- **Input:** mese 11, anno 2025
- **Output atteso:** "Novembre 2025 ha 30 giorni."

### Test 2 – Febbraio di un anno bisestile
- **Input:** mese 2, anno 2024
- **Output atteso:** "Febbraio 2024 ha 29 giorni."

### Test 3 – Febbraio di un anno secolare
- **Cosa si verifica:** 1900 è divisibile per 4 ma anche per 100, e non
  per 400, quindi non è bisestile
- **Input:** mese 2, anno 1900
- **Output atteso:** "Febbraio 1900 ha 28 giorni."

### Test 4 – Mese non valido
- **Cosa si verifica:** il ramo `default` di entrambi gli `switch`
- **Input:** mese 13 (anno qualsiasi)
- **Output atteso:** "Mese 13: non e' un mese valido (inserire un numero da 1 a 12)."
