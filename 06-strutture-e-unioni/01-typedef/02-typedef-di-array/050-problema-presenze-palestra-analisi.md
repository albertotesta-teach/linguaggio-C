# Analisi – 050-problema-presenze-palestra.c

## 1. Problema

Il custode della palestra registra le presenze di ogni pomeriggio, dal
lunedì al sabato, per quattro settimane. Il programma stampa la tabella del
mese con il totale di ogni settimana e di ogni giorno della settimana, la
settimana più frequentata, il giorno della settimana con più presenze nel
mese e il singolo giorno più affollato. Una settimana ha il tipo
`Settimana`, il mese il tipo `Mese`.

## 2. Analisi

### Input

Nessun input da tastiera: le presenze sono nel sorgente.

| Dato | Tipo | Valore |
|------|------|--------|
| `presenze` | `Mese` | settimana 1: 34 41 28 39 45 18; settimana 2: 31 44 30 42 47 22; settimana 3: 29 39 33 40 51 15; settimana 4: 36 46 27 43 49 20 |
| `nomi` | `const char *[6]` | lun, mar, mer, gio, ven, sab |

### Output

- La tabella: una riga per settimana con le presenze e il totale, più la
  riga `Mese` con i totali per giorno della settimana e il totale del mese.
- La settimana più frequentata.
- Il giorno della settimana con più presenze nel mese.
- Il giorno più affollato del mese (giorno e settimana).

### Vincoli

- `typedef int Settimana[6];` e `typedef Settimana Mese[4];`.
- I totali per giorno formano una `Settimana`: le funzioni `totale` e
  `giorno_massimo` valgono sia per una riga del mese sia per i totali.
- A parità vale il primo (settimana o giorno) trovato.

### Assunzioni

- Le presenze sono numeri non negativi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Settimana` | `typedef int Settimana[GIORNI];` | Presenze di sei giorni |
| `Mese` | `typedef Settimana Mese[SETTIMANE];` | Quattro settimane |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `per_giorno` | `Settimana` | Totali del mese per giorno della settimana |
| `migliore` | `int` | Settimana più frequentata |
| `max_s`, `max_g` | `int` | Coordinate del giorno più affollato |

| Funzione | Compito |
|----------|---------|
| `totale(s)` | Somma delle presenze di una settimana |
| `giorno_massimo(s)` | Indice del giorno con più presenze |

### Algoritmo in linguaggio naturale

1. Stampare l'intestazione con i nomi dei giorni.
2. Per ogni settimana:
   1. stampare le presenze e sommarle in `per_giorno`;
   2. stampare il totale della settimana e aggiornare la settimana
      migliore;
   3. confrontare il giorno massimo della settimana con il record del mese.
3. Stampare la riga `Mese` con `per_giorno` e il suo totale.
4. Stampare settimana migliore, giorno della settimana migliore e giorno
   più affollato.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** totali di riga e di colonna, massimi.
- **Input:** nessuno.
- **Valori intermedi attesi:** venerdì 45 + 47 + 51 + 49 = 192; il record
  51 è il venerdì della settimana 3.
- **Output atteso:**
  ```
    Settimana   lun  mar  mer  gio  ven  sab  Totale
            1    34   41   28   39   45   18     205
            2    31   44   30   42   47   22     216
            3    29   39   33   40   51   15     207
            4    36   46   27   43   49   20     221
         Mese   130  170  118  164  192   75     849

  Settimana piu' frequentata: la 4 (221 presenze)
  Giorno della settimana con piu' presenze nel mese: ven (192)
  Giorno piu' affollato del mese: ven della settimana 3 (51 presenze)
  ```

### Test 2 – Record nella prima settimana

- **Cosa si verifica:** il record resta nella posizione iniziale (0, 0).
- **Procedura:** cambiare il primo valore (lunedì della settimana 1) in
  `60`.
- **Output atteso:** `Giorno piu' affollato del mese: lun della settimana
  1 (60 presenze)`; la riga `Mese` ha 156 sotto `lun` e totale 875.

### Test 3 – Settimane a pari merito

- **Cosa si verifica:** a parità vale la prima settimana.
- **Procedura:** rendere la settimana 1 uguale alla settimana 4.
- **Output atteso:** `Settimana piu' frequentata: la 1 (221 presenze)`.
