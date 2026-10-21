# Analisi – 060-problema-classificazione-triangolo.c

## 1. Problema

Dati tre segmenti di lunghezza intera, stabilire se formano un triangolo e,
in caso affermativo, classificarlo come equilatero, isoscele o scaleno e
verificare se è rettangolo. Il programma stampa anche il perimetro.

## 2. Analisi

### Input

| Variabile     | Tipo  | Significato                |
|---------------|-------|----------------------------|
| `a`, `b`, `c` | `int` | Lunghezze dei lati in cm   |

### Output
Se i lati formano un triangolo: la classificazione per lati (EQUILATERO,
ISOSCELE, SCALENO), l'indicazione se è rettangolo e il perimetro in cm.
Altrimenti un messaggio che spiega perché il triangolo non si può costruire,
oppure un errore se le lunghezze non sono positive.

### Vincoli
- Tutte le lunghezze sono maggiori di zero
- Disuguaglianza triangolare: ogni lato è minore della somma degli altri
  due, e va verificata su tutti e tre i lati
- Ogni verifica avviene solo se la precedente è superata
- Il controllo "tutti uguali" precede quello "almeno due uguali",
  altrimenti un equilatero verrebbe classificato isoscele

### Assunzioni
- L'utente inserisce tre numeri interi
- Il caso limite (un lato uguale alla somma degli altri) è un triangolo
  degenere e viene scartato

### Variabili di supporto

| Variabile          | Tipo        | Significato                            |
|--------------------|-------------|----------------------------------------|
| `lati_positivi`    | `int` (0/1) | Tutte le lunghezze maggiori di zero    |
| `triangolo_valido` | `int` (0/1) | Disuguaglianza triangolare rispettata  |
| `rettangolo`       | `int` (0/1) | Teorema di Pitagora verificato         |

Le lunghezze sono intere per poter verificare Pitagora con un confronto
esatto (`a*a + b*b == c*c`).

### Algoritmo in linguaggio naturale
1. Leggere `a`, `b`, `c`.
2. Se non sono tutti positivi, stampare un errore e terminare.
3. Calcolare `triangolo_valido`: ogni lato minore della somma degli altri due.
4. Se non è valido, stamparlo e terminare.
5. Classificare: tutti uguali → equilatero; altrimenti almeno una coppia
   uguale → isoscele; altrimenti scaleno.
6. Calcolare `rettangolo` provando ciascun lato come ipotenusa (tre
   confronti uniti da OR) e stampare il risultato.
7. Stampare il perimetro.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Triangolo scaleno rettangolo
- **Input:** lati 3, 4, 5
- **Output atteso:** "SCALENO", "Il triangolo e' RETTANGOLO.", perimetro 12 cm

### Test 2 – Triangolo equilatero
- **Cosa si verifica:** l'ordine dei controlli nella classificazione
- **Input:** lati 5, 5, 5
- **Output atteso:** "EQUILATERO", non rettangolo, perimetro 15 cm

### Test 3 – Segmenti che non formano un triangolo
- **Cosa si verifica:** la disuguaglianza va controllata su tutti i lati:
  qui `3 < 10 + 2` è vera ma `10 < 2 + 3` è falsa
- **Input:** lati 10, 2, 3
- **Output atteso:** messaggio che il triangolo non si può costruire

### Test 4 – Lunghezze non positive
- **Cosa si verifica:** nessun altro controllo viene eseguito
- **Input:** lati 0, 1, 2
- **Output atteso:** "Errore: le lunghezze devono essere positive."
