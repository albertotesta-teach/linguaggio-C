# Analisi – 060-problema-calcolo-area.c

## 1. Problema
L'utente sceglie una figura piana (quadrato, rettangolo, cerchio) e inserisce
le misure necessarie. Il programma calcola area e perimetro e li stampa
con quattro cifre decimali. La selezione avviene con `if/else` perché `switch`
non è ancora stato introdotto.

## 2. Analisi

### Input

| Variabile | Tipo     | Significato                                         |
|-----------|----------|-----------------------------------------------------|
| `figura`  | `int`    | Scelta dell'utente: 1=quadrato, 2=rettangolo, 3=cerchio |
| `lato`    | `double` | Lato del quadrato (m), richiesto solo se figura = 1 |
| `base`    | `double` | Base del rettangolo (m), richiesta solo se figura = 2 |
| `altezza` | `double` | Altezza del rettangolo (m), richiesta solo se figura = 2 |
| `raggio`  | `double` | Raggio del cerchio (m), richiesto solo se figura = 3 |

### Output
Il nome della figura scelta, l'area (m²) e il perimetro (m) con quattro
cifre decimali. Se la scelta non è 1, 2 o 3 il programma stampa un messaggio
di errore e i trattini al posto dei risultati.

### Vincoli
- `figura` vale 1, 2 o 3
- Tutte le misure sono maggiori di zero (non verificato dal programma)

### Assunzioni
- L'utente inserisce valori positivi e coerenti con la figura scelta
- Il valore di π è approssimato dalla costante `PI_GRECO`

### Variabili di supporto

| Variabile   | Tipo     | Significato               |
|-------------|----------|---------------------------|
| `area`      | `double` | Area calcolata (m²)       |
| `perimetro` | `double` | Perimetro calcolato (m)   |
| `codice_uscita` | `int` | 0 se la scelta è valida, 1 altrimenti; è il valore restituito da `main` |

Costante: `PI_GRECO = 3.14159265358979`

### Algoritmo in linguaggio naturale
1. Mostrare il menu e acquisire la scelta della figura.
2. Se la figura è 1 (quadrato): acquisire il lato, calcolare
   area = lato² e perimetro = 4 × lato.
3. Altrimenti, se la figura è 2 (rettangolo): acquisire base e altezza,
   calcolare area = base × altezza e perimetro = 2 × (base + altezza).
4. Altrimenti, se la figura è 3 (cerchio): acquisire il raggio, calcolare
   area = π × r² e perimetro = 2 × π × r.
5. Altrimenti: stampare il messaggio di scelta non valida e porre il
   codice di uscita a 1.
6. Se il codice di uscita è 0 stampare area e perimetro con quattro cifre
   decimali, altrimenti stampare i trattini.
7. Restituire il codice di uscita (unico `return` del programma).

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso. Serve almeno un test per ciascun
ramo della scelta.

### Test 1 – Quadrato
- **Input:** figura = 1, lato = 4.0
- **Valori intermedi attesi:** area = 4.0 × 4.0 = 16.0;
  perimetro = 4.0 × 4.0 = 16.0
- **Output atteso:**
```
--- Quadrato ---
Area:       16.0000 m^2
Perimetro:  16.0000 m
```

### Test 2 – Rettangolo
- **Input:** figura = 2, base = 6.0, altezza = 3.5
- **Valori intermedi attesi:** area = 6.0 × 3.5 = 21.0;
  perimetro = 2.0 × (6.0 + 3.5) = 19.0
- **Output atteso:**
```
--- Rettangolo ---
Area:       21.0000 m^2
Perimetro:  19.0000 m
```

### Test 3 – Cerchio
- **Input:** figura = 3, raggio = 5.0
- **Valori intermedi attesi:** area = π × 5.0 × 5.0 = 78.5398…;
  perimetro = 2 × π × 5.0 = 31.4159…
- **Output atteso:**
```
--- Cerchio ---
Area:       78.5398 m^2
Perimetro:  31.4159 m
```

### Test 4 – Scelta non valida
- **Cosa si verifica:** il ramo `else` finale
- **Input:** figura = 7
- **Output atteso:**
```
Errore: scelta non valida.
Area:      ---
Perimetro: ---
```
