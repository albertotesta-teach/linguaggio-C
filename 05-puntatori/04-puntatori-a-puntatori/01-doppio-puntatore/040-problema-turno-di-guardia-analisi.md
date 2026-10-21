# Analisi – 040-problema-turno-di-guardia.c

## 1. Problema

Lo sportello pomeridiano di tutoraggio è coperto a rotazione da cinque
docenti. Il programma indica chi è di turno; con `T` il docente svolge
un'ora e il turno passa al successivo, con `S` il docente è assente e il
turno passa senza ore. Con `Q` stampa le ore svolte da ciascuno.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `T` ora svolta, `S` assente, `Q` fine |
| `nomi` | `char[5][12]` | Rossi, Bianco, Greco, Fontana, Conti (nel sorgente, in ordine di turno) |

### Output

- A ogni passo il docente di turno.
- `<nome> ha svolto la sua Na ora` oppure `<nome> assente, turno al
  successivo`, oppure `Comando sconosciuto.`
- Alla fine le ore svolte da ciascun docente.

### Vincoli

- `turno` punta all'elemento di `ore` del docente di turno; il nome si
  ricava dalla posizione del puntatore (`nomi[turno − ore]`).
- `passa_turno` deve cambiare il puntatore del chiamante, quindi riceve il
  suo indirizzo (`int **`): `*turno` è il puntatore del `main`, `**turno`
  le ore del docente.
- Dopo l'ultimo docente il turno torna al primo.
- Con `S` cambia solo il puntatore, non il valore puntato.
- A fine input il programma si comporta come il comando `Q`.

### Assunzioni

- Cinque docenti in ordine fisso; i comandi sono maiuscoli.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `ore` | `int[5]` | Ore svolte, parallelo a `nomi` |
| `turno` | `int *` | Elemento del docente di turno |
| `i` | `int` | Indice del riepilogo |

| Funzione | Compito |
|----------|---------|
| `passa_turno(&turno, ore, n)` | Sposta il puntatore del `main` all'elemento successivo, con ritorno al primo |

### Algoritmo in linguaggio naturale

1. Far puntare `turno` a `ore[0]`.
2. Finché il comando non è `Q`:
   1. stampare il docente di turno e leggere il comando (a fine input `Q`);
   2. `T`: incrementare `*turno`, stampare l'ora svolta, passare il turno;
   3. `S`: stampare l'assenza e passare il turno;
   4. ogni altro comando diverso da `Q` è sconosciuto.
3. Stampare le ore di tutti.
4. In `passa_turno`: se `*turno` è l'ultimo elemento farlo puntare al
   primo, altrimenti incrementarlo.

## 3. Casi di test

Nell'output i comandi inseriti non compaiono (input da pipe).

### Test 1 – Rotazione completa con un'assenza

- **Input:** `T`, `T`, `S`, `T`, `T`, `T`, `X`, `Q`
- **Output atteso** (risposte):
  ```
    Rossi ha svolto la sua 1a ora
    Bianco ha svolto la sua 1a ora
    Greco assente, turno al successivo
    Fontana ha svolto la sua 1a ora
    Conti ha svolto la sua 1a ora
    Rossi ha svolto la sua 2a ora
    Comando sconosciuto.

  Ore svolte:  Rossi 2  Bianco 1  Greco 0  Fontana 1  Conti 1
  ```
  (dopo Conti il turno torna a Rossi).

### Test 2 – Fine dell'input

- **Input:** `T`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso** (ultima riga):
  `Ore svolte:  Rossi 1  Bianco 0  Greco 0  Fontana 0  Conti 0`
