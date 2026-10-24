# Analisi – 060-problema-banchi-laboratorio.c

## 1. Problema

Il tecnico del laboratorio di chimica posiziona un nuovo banco sulla
pianta della stanza (900 × 600 cm). Il programma controlla che il banco
stia nella stanza e che non si sovrapponga ai tre banchi esistenti; in
caso di sovrapposizione stampa l'area in comune con ogni banco. I
rettangoli sono struct `Rettangolo` passate per valore.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nuovo` | `Rettangolo` | x, y (angolo in alto a sinistra), larghezza e profondità in cm |
| banchi | nel sorgente | 1: (50, 50) 300 × 80; 2: (50, 250) 300 × 80; 3: (500, 50) 120 × 400 |

### Output

- L'intestazione con le misure della stanza.
- `Si sovrappone al banco N per A cm2.` per ogni banco in conflitto,
  oppure `Posizione libera: banco di A cm2 sistemato.`
- `Il banco esce dalla stanza.` o `Dati non validi.`

### Vincoli

- Due rettangoli si sovrappongono se si sovrappongono sia lungo x sia
  lungo y (bordi che si toccano non contano).
- Intersezione: da max(x) a min(x + larghezza), da max(y) a
  min(y + profondità).
- Larghezza e profondità positive.

### Assunzioni

- I banchi sono allineati alle pareti (nessuna rotazione).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Rettangolo` | `typedef struct { int x; int y; int larghezza; int profondita; } Rettangolo;` | Ingombro di un banco o della stanza |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `stanza` | `Rettangolo` | (0, 0) 900 × 600 |
| `banchi` | `Rettangolo[3]` | Banchi esistenti |
| `conflitti` | `int` | Banchi sovrapposti |

| Funzione | Compito |
|----------|---------|
| `area(r)` | Larghezza per profondità |
| `sovrapposti(a, b)` | 1 se i rettangoli hanno una parte comune |
| `intersezione(a, b)` | Restituisce la parte comune |
| `dentro(stanza, r)` | 1 se `r` è tutto nella stanza |
| `minimo`, `massimo` | Minimo e massimo di due interi |

### Algoritmo in linguaggio naturale

1. Leggere il nuovo banco; se i dati mancano o le misure non sono
   positive, stampare `Dati non validi.`
2. Se il banco non è dentro la stanza, segnalarlo.
3. Altrimenti, per ogni banco esistente sovrapposto stampare l'area
   dell'intersezione e contare il conflitto.
4. Senza conflitti stampare la posizione libera con l'area del banco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Posizione libera

- **Input:** `650 300 200 80`
- **Output atteso:**
  ```
  Stanza 900 x 600 cm, banchi esistenti: 3
  Nuovo banco (x y larghezza profondita'): Posizione libera: banco di 16000 cm2 sistemato.
  ```

### Test 2 – Una sovrapposizione

- **Input:** `400 400 200 100`
- **Valori intermedi attesi:** con il banco 3 la parte comune va da x 500
  a 600 e da y 400 a 450: 100 × 50.
- **Output atteso:** `Si sovrappone al banco 3 per 5000 cm2.`

### Test 3 – Più sovrapposizioni

- **Input:** `300 280 250 100`
- **Output atteso:**
  ```
  Si sovrappone al banco 2 per 2500 cm2.
  Si sovrappone al banco 3 per 5000 cm2.
  ```

### Test 4 – Fuori stanza e dati non validi

- **Input:** `800 100 200 80`; poi `0 0 -5 10`; poi `abc`
- **Output atteso:** `Il banco esce dalla stanza.`; `Dati non validi.`;
  `Dati non validi.`
