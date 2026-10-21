# Analisi – 040-problema-termostato.c

## 1. Problema

Il termostato di un appartamento regola la temperatura desiderata di tre
zone (soggiorno, camera, bagno) con un solo paio di tasti + e −, che
agiscono sulla zona selezionata. Ogni pressione cambia la temperatura di
mezzo grado, entro i limiti di 16 e 26 gradi. Senza una zona selezionata i
tasti non hanno effetto.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | Tasto premuto: `S`, `C`, `B` (selezione zona), `+`, `-`, `Q` (fine) |
| `soggiorno`, `camera`, `bagno` | `int` | Temperature iniziali in decimi di grado: 205, 190, 220 (nel sorgente) |

### Output

- Lo stato iniziale e finale delle tre zone in gradi.
- Per ogni comando: la zona selezionata, la nuova temperatura impostata,
  oppure un messaggio (`Seleziona prima una zona.`, `Massimo raggiunto`,
  `Minimo raggiunto`, `Comando sconosciuto.`).

### Vincoli

- Le temperature sono in decimi di grado (interi): passo 5, limiti 160 e 260.
- `zona_attiva` contiene l'indirizzo della temperatura selezionata ed è
  `NULL` finché non si sceglie una zona: un puntatore `NULL` non si
  dereferenzia mai.
- La stessa istruzione `*zona_attiva = *zona_attiva ± PASSO` modifica la
  zona selezionata, qualunque essa sia.
- Il limite si controlla prima della modifica: se la supererebbe la
  temperatura non cambia.
- A fine input (EOF) il programma si comporta come il comando `Q`.

### Assunzioni

- I comandi sono lettere maiuscole o i simboli `+`/`-`; una minuscola è un
  comando sconosciuto.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `zona_attiva` | `int *` | Indirizzo della temperatura selezionata, `NULL` all'inizio |
| `PASSO`, `MINIMA`, `MASSIMA` | `#define` | 5, 160, 260 decimi di grado |

| Funzione | Compito |
|----------|---------|
| `stampa_stato` | Stampa le tre temperature in gradi |

### Algoritmo in linguaggio naturale

1. Stampare lo stato iniziale; porre `zona_attiva = NULL`.
2. Finché il comando non è `Q`:
   1. leggere il comando (a fine input usare `Q`);
   2. `S`, `C`, `B`: assegnare a `zona_attiva` l'indirizzo della zona;
   3. `+` o `-`: se `zona_attiva` è `NULL` segnalarlo; altrimenti, se il
      nuovo valore supererebbe il limite, segnalarlo; altrimenti modificare
      `*zona_attiva` e stampare il nuovo valore;
   4. ogni altro comando diverso da `Q` è sconosciuto.
3. Stampare lo stato finale.

## 3. Casi di test

Nell'output i comandi non compaiono (input da pipe); ogni risposta segue il
prompt `Comando (S C B + - Q): `.

### Test 1 – Tasto senza zona, selezione e regolazione

- **Input:** `+`, `S`, `+`, `+`, `C`, `-`, `x`, `Q`
- **Valori intermedi attesi:** `zona_attiva` = `NULL`, poi `&soggiorno`
  (205 → 210 → 215), poi `&camera` (190 → 185).
- **Output atteso** (risposte nell'ordine):
  ```
    Seleziona prima una zona.
    zona: soggiorno
    impostata 21.0 gradi
    impostata 21.5 gradi
    zona: camera
    impostata 18.5 gradi
    Comando sconosciuto.
  Soggiorno 21.5 | Camera 18.5 | Bagno 22.0
  ```

### Test 2 – Limite massimo

- **Cosa si verifica:** il controllo avviene prima della modifica.
- **Input:** `B` e nove volte `+`, poi fine dell'input.
- **Valori intermedi attesi:** 220 → … → 260 dopo otto pressioni; la nona
  porterebbe a 265.
- **Output atteso** (ultime righe):
  ```
    impostata 25.5 gradi
    impostata 26.0 gradi
    Massimo raggiunto (26.0 gradi).
  Soggiorno 20.5 | Camera 19.0 | Bagno 26.0
  ```

### Test 3 – Limite minimo

- **Input:** `C` e sette volte `-`, poi fine dell'input.
- **Output atteso** (ultime righe):
  ```
    impostata 16.0 gradi
    Minimo raggiunto (16.0 gradi).
  Soggiorno 20.5 | Camera 16.0 | Bagno 22.0
  ```
