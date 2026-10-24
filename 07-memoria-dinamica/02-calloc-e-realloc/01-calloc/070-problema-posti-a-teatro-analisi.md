# Analisi – 070-problema-posti-a-teatro.c

## 1. Problema

Per lo spettacolo di fine anno la sala ha righe e posti per riga letti
all'avvio. La sala è una matrice in un solo blocco allocato con `calloc`
(tutti i posti liberi, cioè 0); ogni posto prenotato contiene il codice
della prenotazione. Il programma gestisce prenotazioni di posti vicini
nella stessa riga, cancellazioni e la mappa della sala.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `righe`, `posti` | `int` | Righe 1-26 (lettere A-Z), posti per riga 1-40 |
| `comando` | `char` | `P riga primo quanti` prenota, `C codice` cancella, `M` mappa, `Q` fine (anche minuscoli) |

### Output

- `prenotazione K: A3-A6`, `Alcuni posti sono gia' occupati.`,
  `Posti non validi.`
- `prenotazione K cancellata: liberati N posti` (`liberato 1 posto`),
  `Prenotazione inesistente.`
- `M`: la mappa con `.` libero e `#` occupato, e `occupati O su T`.
- `Sala non valida (...)`, `Memoria insufficiente.`,
  `Comando sconosciuto.`

### Vincoli

- `sala = calloc(righe * posti, sizeof *sala)`: tutti i posti a 0 senza
  un ciclo; il posto (r, p) sta in `sala[r * posti + p]`.
- Una prenotazione occupa posti consecutivi della stessa riga, tutti
  liberi; il codice cresce di 1 a ogni prenotazione riuscita.
- La cancellazione libera tutti i posti con quel codice.
- La lettera della riga può essere minuscola.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sala` | `int *` | Matrice in un blocco: 0 libero, altrimenti codice |
| `codice`, `occupati` | `int` | Ultimo codice e posti occupati |
| `lettera`, `numero`, `quanti` | `char`, `int`, `int` | Dati della prenotazione |
| `liberi` | `int` | Tutti i posti richiesti sono liberi |

| Funzione | Compito |
|----------|---------|
| `mappa(sala, righe, posti)` | Disegna la sala |

### Algoritmo in linguaggio naturale

1. Leggere le dimensioni e allocare la sala con `calloc`.
2. Finché il comando non è `Q`: con `P` controllare i dati e i posti e
   scrivere il nuovo codice; con `C` azzerare i posti del codice; con `M`
   stampare la mappa; scartare il resto della riga.
3. Liberare la sala.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Sala 3 × 8

- **Input:** `3 8`, `P A 3 4`, `p b 1 2`, `P A 5 2`, `P C 7 3`, `P D 1 1`,
  `P B 8 1`, `M`, `C 1`, `C 9`, `c 3`, `M extra`, `X`, `Q`
- **Output atteso:**
  ```
    prenotazione 1: A3-A6
    prenotazione 2: B1-B2
    Alcuni posti sono gia' occupati.
    Posti non validi.
    Posti non validi.
    prenotazione 3: B8-B8
     palco
    A ..####..
    B ##.....#
    C ........
    occupati 7 su 24
    prenotazione 1 cancellata: liberati 4 posti
    Prenotazione inesistente.
    prenotazione 3 cancellata: liberato 1 posto
     palco
    A ........
    B ##......
    C ........
    occupati 2 su 24
    Comando sconosciuto.
  ```
