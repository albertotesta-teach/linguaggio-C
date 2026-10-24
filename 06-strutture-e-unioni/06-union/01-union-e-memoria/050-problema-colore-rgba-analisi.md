# Analisi – 050-problema-colore-rgba.c

## 1. Problema

Per il sito della scuola si schiariscono, scuriscono e trasformano in
grigio i colori RGBA. Il colore è una `union`: un codice a 32 bit
`0xRRGGBBAA` e un array di quattro canali indicizzato da un `enum`.
L'enum elenca i canali nell'ordine in memoria di una macchina
little-endian (ALFA, BLU, VERDE, ROSSO).

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `S RRGGBB p` schiarisci, `D RRGGBB p` scurisci, `G RRGGBB` grigio, `Q` fine (anche minuscoli) |
| `rgb` | `unsigned long` | Colore in esadecimale, sei cifre |
| `percento` | `int` | Da 0 a 100 |

### Output

- Due righe `nome #RRGGBBAA R r G g B b A a`: il colore originale (alfa
  255) e quello trasformato.
- `Dati non validi.`, `Comando sconosciuto.`

### Vincoli

- Codice = `(rgb << 8) | 0xFF`; i canali si leggono e si scrivono
  nell'array della union.
- Schiarire: canale + (255 − canale) × p / 100; scurire: canale − canale
  × p / 100 (divisione intera); alfa non cambia.
- Grigio: luminosità 0.299 R + 0.587 G + 0.114 B arrotondata, copiata nei
  tre canali.
- Le funzioni ricevono e restituiscono `Colore` per valore.
- Un comando per riga; i dati non validi non interrompono il programma. A
  fine input termina come con `Q`.

### Assunzioni

- Macchina little-endian.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Canale` | `typedef enum { ALFA, BLU, VERDE, ROSSO, NUM_CANALI } Canale;` | Posizione del canale in memoria |
| `Colore` | `typedef union { uint32_t codice; uint8_t canale[NUM_CANALI]; } Colore;` | Colore visto in due modi |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `rgb` | `unsigned long` | Valore letto con `%6lx` |
| `percento` | `int` | Intensità |
| `c` | `Colore` | Colore originale |

| Funzione | Compito |
|----------|---------|
| `schiarisci(c, p)`, `scurisci(c, p)`, `grigio(c)` | Trasformazioni |
| `stampa(nome, c)` | Codice e canali |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `S`/`D`/`G`: leggere il colore (e la percentuale) e controllarli;
      costruire il codice, stampare l'originale e la trasformazione;
   3. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Trasformazioni

- **Input:** `S 3366CC 50`, `d 3366CC 50`, `G 3366CC`, `S 3366CC 120`,
  `G zz`, `X`, `G FFFFFF`, `Q`
- **Valori intermedi attesi:** schiarito rosso 51 + 204 × 50 / 100 = 153;
  scurito 51 − 25 = 26; grigio 0.299·51 + 0.587·102 + 0.114·204 ≈ 98.
- **Output atteso:**
  ```
    originale  #3366CCFF   R  51  G 102  B 204  A 255
    schiarito  #99B2E5FF   R 153  G 178  B 229  A 255
    originale  #3366CCFF   R  51  G 102  B 204  A 255
    scurito    #1A3366FF   R  26  G  51  B 102  A 255
    originale  #3366CCFF   R  51  G 102  B 204  A 255
    grigio     #626262FF   R  98  G  98  B  98  A 255
    Dati non validi.
    Dati non validi.
    Comando sconosciuto.
    originale  #FFFFFFFF   R 255  G 255  B 255  A 255
    grigio     #FFFFFFFF   R 255  G 255  B 255  A 255
  ```
