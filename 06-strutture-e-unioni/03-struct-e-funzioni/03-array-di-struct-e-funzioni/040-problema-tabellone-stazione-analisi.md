# Analisi – 040-problema-tabellone-stazione.c

## 1. Problema

Il tabellone della stazione mostra le partenze della mattina. Il
programma registra ritardi e soppressioni tramite una funzione che
modifica l'elemento giusto dell'array di struct `Partenza`, cerca il
prossimo treno per una destinazione con una funzione che restituisce un
puntatore all'elemento e stampa il tabellone.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `R numero min` ritardo, `S numero` soppressione, `P hh:mm destinazione` prossimo treno, `T` tabellone, `Q` fine (anche minuscoli) |
| `numero` | `char[8]` | Numero del treno |
| `minuti` | `int` | Ritardo, non negativo |
| `ore:minuti`, `destinazione` | `int`, `char[16]` | Ora da cui cercare e destinazione |

Tabellone iniziale (nel sorgente): R10220 Genova 7:05 bin. 2, RV2132
Torino 7:12 bin. 1, R10404 Pavia 7:20 bin. 4, R10222 Genova 7:35 bin. 2,
FR9512 Milano 7:41 bin. 3, RV2134 Torino 8:12 bin. 1.

### Output

- `<numero> aggiornato.`, `Treno X non in tabellone.`,
  `Ritardo non valido.`, `Dati non validi.`
- `Prossimo per D: <numero>, binario B, parte alle HH:MM` (orario
  effettivo con il ritardo) oppure `Nessun treno per D.`
- Il tabellone con stato `in orario`, `ritardo N'` o `SOPPRESSO`.

### Vincoli

- La soppressione è registrata come ritardo −1.
- `prossima` restituisce `const Partenza *`: il primo treno non soppresso
  per quella destinazione con partenza effettiva (orario + ritardo) non
  precedente all'ora indicata; `NULL` se non c'è.
- `registra_ritardo` riceve l'array e modifica l'elemento trovato.
- Gli orari sono minuti da mezzanotte; l'ora indicata deve essere valida.
- Un comando per riga (il resto viene scartato); i dati non validi non
  interrompono il programma. A fine input termina come con `Q`.

### Assunzioni

- I treni sono in ordine di orario nell'array.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Partenza` | `typedef struct { char numero[8]; char destinazione[16]; int partenza; int ritardo; int binario; } Partenza;` | Un treno in partenza |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `tabellone` | `Partenza[6]` | Array di struct |
| `treno` | `const Partenza *` | Risultato di `prossima` |
| `comando` | `char` | Comando in maiuscolo |

| Funzione | Compito |
|----------|---------|
| `stampa_tabellone(t, n)` | Stampa tutte le partenze |
| `prossima(t, n, ora, dest)` | Puntatore al prossimo treno utile, o `NULL` |
| `registra_ritardo(t, n, numero, minuti)` | Aggiorna il ritardo; 1 se il treno esiste |
| `stampa_ora(minuti)` | Stampa `HH:MM` |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) in maiuscolo;
   2. `R`/`S`: leggere numero (e minuti per `R`); controllare e chiamare
      `registra_ritardo` (con −1 per `S`);
   3. `P`: leggere ora e destinazione; chiamare `prossima` e stampare il
      risultato;
   4. `T`: stampare il tabellone;
   5. altro diverso da `Q`: comando sconosciuto;
   6. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Mattina in stazione

- **Cosa si verifica:** ritardi, soppressione, ricerca che salta il treno
  soppresso e quelli già partiti, errori.
- **Input:** `T`, `R R10220 12`, `r R10404 5`, `S R10222`, `R XX000 3`,
  `R RV2132 -4`, `R RV2132 abc`, `P 7:00 Genova`, `p 7:20 Genova`,
  `P 7:30 Torino`, `P 8:30 Torino`, `P 7:00 Roma`, `P 25:00 Genova`, `X`,
  `T`, `Q`
- **Valori intermedi attesi:** R10220 parte alle 7:05 + 12 = 7:17; alle
  7:20 l'unico altro treno per Genova è soppresso.
- **Output atteso** (dopo il primo tabellone):
  ```
    R10220 aggiornato.
    R10404 aggiornato.
    R10222 aggiornato.
    Treno XX000 non in tabellone.
    Ritardo non valido.
    Dati non validi.
    Prossimo per Genova: R10220, binario 2, parte alle 07:17
    Nessun treno per Genova.
    Prossimo per Torino: RV2134, binario 1, parte alle 08:12
    Nessun treno per Torino.
    Nessun treno per Roma.
    Dati non validi.
    Comando sconosciuto.
    Ora    Treno   Destinazione  Bin  Stato
    07:05  R10220  Genova          2  ritardo 12'
    07:12  RV2132  Torino          1  in orario
    07:20  R10404  Pavia           4  ritardo 5'
    07:35  R10222  Genova          2  SOPPRESSO
    07:41  FR9512  Milano          3  in orario
    08:12  RV2134  Torino          1  in orario
  ```
