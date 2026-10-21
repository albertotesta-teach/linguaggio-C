# Analisi – 070-problema-batteria-drone.c

## 1. Problema

Il programma di controllo del drone del laboratorio di robotica tiene la
carica della batteria e i minuti di volo totali. Esegue voli e ricariche
della durata indicata, rifiuta un volo che porterebbe la carica sotto la
riserva del 20% e mostra dopo ogni comando carica e autonomia residua.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `V` (volo), `R` (ricarica), `Q` (fine) |
| `n` | `int` | Minuti del volo o della ricarica, positivo |
| `carica` | `int` | Carica iniziale 64% (nel sorgente) |

### Output

- Carica e autonomia iniziali.
- Per ogni volo: `Volo di n minuti eseguito.` oppure `Volo rifiutato: la
  carica scenderebbe sotto il 20%.`; per ogni ricarica: `Ricaricati N
  punti.`; in entrambi i casi carica e autonomia aggiornate.
- `Numero di minuti non valido.` oppure `Comando sconosciuto.`
- Alla fine: minuti di volo totali e carica finale.

### Vincoli

- Consumo 2% al minuto di volo, ricarica 3% al minuto, riserva 20%.
- `vola` riceve gli indirizzi di carica e minuti di volo e li aggiorna
  entrambi solo se la carica finale resta almeno al 20%; se rifiuta non
  cambia nulla.
- `ricarica` non supera il 100% e restituisce i punti effettivamente
  aggiunti.
- Autonomia = (carica − 20) / 2 minuti con la divisione intera, 0 se la
  carica non supera la riserva.
- Minuti non numerici o non positivi sono rifiutati (la riga si scarta) e
  il programma continua; a fine input si comporta come il comando `Q`.

### Assunzioni

- I comandi sono lettere maiuscole.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `carica` | `int` | Percentuale di carica, modificata da `vola` e `ricarica` |
| `volo` | `int` | Minuti di volo totali, modificati da `vola` |
| `letti` | `int` | Valore restituito da `scanf` per i minuti |
| `CONSUMO`, `RICARICA`, `RISERVA` | `#define` | 2, 3, 20 |

| Funzione | Compito |
|----------|---------|
| `vola(&carica, &volo, n)` | Esegue il volo se possibile; 1 se eseguito |
| `ricarica(&carica, n)` | Ricarica fino a 100; restituisce i punti aggiunti |
| `autonomia(carica)` | Minuti di volo possibili sopra la riserva |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Stampare carica e autonomia.
2. Finché il comando non è `Q`:
   1. leggere il comando (a fine input usare `Q`);
   2. per `V` o `R` leggere i minuti: a fine input terminare; se non sono un
      numero positivo segnalarlo; altrimenti eseguire il volo (o
      segnalarne il rifiuto) o la ricarica e stampare carica e autonomia;
   3. ogni altro comando diverso da `Q` è sconosciuto.
3. Stampare minuti di volo totali e carica finale.

## 3. Casi di test

Nell'output i comandi inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `V 10`, `V 15`, `R 8`, `R 20`, `V abc`, `V 0`, `X`, `V 40`, `Q`
- **Valori intermedi attesi:** 64 − 20 = 44; 44 − 30 = 14 < 20 → rifiuto;
  44 + 24 = 68; 68 + 60 = 128 → 100 (32 punti); 100 − 80 = 20 (ammesso).
- **Output atteso:**
  ```
  Carica 64%, autonomia 22 minuti
    Volo di 10 minuti eseguito. Carica 44%, autonomia 12 minuti
    Volo rifiutato: la carica scenderebbe sotto il 20%. Carica 44%, autonomia 12 minuti
    Ricaricati 24 punti. Carica 68%, autonomia 24 minuti
    Ricaricati 32 punti. Carica 100%, autonomia 40 minuti
    Numero di minuti non valido.
    Numero di minuti non valido.
    Comando sconosciuto.
    Volo di 40 minuti eseguito. Carica 20%, autonomia 0 minuti
  Minuti di volo totali: 50, carica finale 20%
  ```

### Test 2 – Fine dell'input

- **Input:** `V 5`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso** (ultima riga): `Minuti di volo totali: 5, carica finale 54%`
