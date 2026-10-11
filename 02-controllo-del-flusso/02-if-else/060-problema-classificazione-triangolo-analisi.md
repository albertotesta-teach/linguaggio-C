# Analisi – 060-problema-classificazione-triangolo.c

## 1. Problema

Dati tre segmenti di lunghezza intera, stabilire se formano un triangolo e,
in caso affermativo, classificarlo come equilatero, isoscele o scaleno e
verificare se è rettangolo. Il programma stampa anche il perimetro.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `a`, `b`, `c` | `int` | Lunghezze dei lati in cm |
| `lati_positivi` | `int` (0/1) | Tutte le lunghezze maggiori di zero |
| `triangolo_valido` | `int` (0/1) | Disuguaglianza triangolare rispettata |
| `rettangolo` | `int` (0/1) | Teorema di Pitagora verificato |

Le lunghezze sono intere per poter verificare Pitagora con un confronto
esatto (`a*a + b*b == c*c`).

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Triangolo scaleno rettangolo

**a) Input** – lati 3, 4, 5

**b) Output** – "SCALENO", "Il triangolo e' RETTANGOLO.", perimetro 12 cm

**c) Variabili di supporto** – `lati_positivi`, `triangolo_valido`, `rettangolo`

**d) Vincoli** – ogni verifica avviene solo se la precedente è superata

**e) Assunzioni** – l'utente inserisce tre numeri interi

**f) Algoritmo in linguaggio naturale**
1. Leggere `a`, `b`, `c`.
2. Se non sono tutti positivi, stampare un errore e terminare.
3. Calcolare `triangolo_valido`: ogni lato minore della somma degli altri due.
4. Se non è valido, stamparlo e terminare.
5. Classificare: tutti uguali → equilatero; altrimenti almeno una coppia
   uguale → isoscele; altrimenti scaleno.
6. Calcolare `rettangolo` provando ciascun lato come ipotenusa (tre
   confronti uniti da OR) e stampare il risultato.
7. Stampare il perimetro.

### Caso d'uso 2 – Triangolo equilatero

**a) Input** – lati 5, 5, 5

**b) Output** – "EQUILATERO", non rettangolo, perimetro 15 cm

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – il controllo "tutti uguali" precede quello "almeno due
uguali", altrimenti un equilatero verrebbe classificato isoscele

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Segmenti che non formano un triangolo

**a) Input** – lati 10, 2, 3

**b) Output** – messaggio che il triangolo non si può costruire

**c) Variabili di supporto** – `triangolo_valido`

**d) Vincoli** – la disuguaglianza va verificata su tutti e tre i lati:
qui `3 < 10 + 2` è vera ma `10 < 2 + 3` è falsa

**e) Assunzioni** – il caso limite (un lato uguale alla somma degli altri)
è un triangolo degenere e viene scartato

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 4.

### Caso d'uso 4 – Lunghezze non positive

**a) Input** – lati 0, 1, 2

**b) Output** – "Errore: le lunghezze devono essere positive."

**c) Variabili di supporto** – `lati_positivi`

**d) Vincoli** – nessun altro controllo viene eseguito

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 2.
