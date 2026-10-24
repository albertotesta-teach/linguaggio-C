# Analisi – 050-problema-magazzino-laboratorio.c

## 1. Problema

Il tecnico del laboratorio di elettronica registra carichi e prelievi di
componenti identificati da un codice e stampa gli articoli sotto la
scorta minima con la quantità da ordinare per tornare al doppio della
scorta. Il magazzino è un array di 6 struct `Articolo`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `P codice n` prelievo, `C codice n` carico, `S` sottoscorta, `Q` fine (anche minuscoli) |
| `codice` | `char[8]` | Codice dell'articolo |
| `pezzi` | `int` | Quantità, positiva |
| `magazzino` | `Articolo[6]` | Situazione iniziale (nel sorgente) |

Situazione iniziale:

| Codice | Descrizione | Quantità | Scorta minima |
|--------|-------------|----------|---------------|
| R220 | Resistenza 220 ohm | 180 | 50 |
| LED-R | LED rosso 5 mm | 64 | 40 |
| LED-V | LED verde 5 mm | 35 | 40 |
| C100U | Condensatore 100 uF | 22 | 20 |
| BB400 | Breadboard 400 punti | 9 | 10 |
| ARDU | Scheda Arduino Uno | 12 | 8 |

### Output

- Per carichi e prelievi: `<descrizione>: ora N pezzi.` con l'eventuale
  `Attenzione: sotto la scorta minima (M).`, oppure
  `<descrizione>: disponibili solo N pezzi.`, `Codice X sconosciuto.`,
  `Dati non validi.`
- Per `S`: gli articoli sottoscorta con la quantità da ordinare e
  `Articoli sottoscorta: N`.
- `Comando sconosciuto.`

### Vincoli

- Un prelievo non può superare la quantità disponibile.
- Sottoscorta: quantità strettamente minore della scorta minima; da
  ordinare `2 * scorta_minima - quantita`.
- Il codice si cerca con `strcmp` (ricerca lineare).
- Dati non validi (codice o quantità mancanti, quantità non positiva o non
  numerica) non interrompono il programma.
- Un comando per riga: il resto della riga viene scartato. A fine input il
  programma termina come con `Q`.

### Assunzioni

- Il carico non ha un limite massimo.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Articolo` | `typedef struct { char codice[8]; char descrizione[28]; int quantita; int scorta_minima; } Articolo;` | Un componente del magazzino |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `magazzino` | `Articolo[6]` | Array di struct |
| `a` | `int` | Indice dell'articolo trovato (6 = non trovato) |
| `sottoscorta` | `int` | Contatore del rapporto |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) e convertirlo in maiuscolo;
   2. `P`/`C`: leggere codice e pezzi; se non validi segnalarlo; cercare il
      codice; con `C` aggiungere i pezzi; con `P` toglierli se bastano e
      avvisare se si scende sotto la scorta;
   3. `S`: stampare gli articoli sottoscorta e contarli;
   4. altro diverso da `Q`: comando sconosciuto;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Movimenti e rapporto

- **Cosa si verifica:** rapporto iniziale, prelievi con avviso, prelievo
  eccessivo, carico, dati non validi e rapporto finale.
- **Input:** `S`, `P LED-V 10`, `p BB400 2`, `P ARDU 20`, `C LED-V 50`,
  `P XXX 3`, `P R220 abc`, `P R220 -5`, `P R220 140`, `S`, `Q`
- **Valori intermedi attesi:** LED-V 35 − 10 + 50 = 75; R220 180 − 140 =
  40, da ordinare 100 − 40 = 60.
- **Output atteso:**
  ```
    LED-V  LED verde 5 mm          35 (minimo 40): ordinare 45
    BB400  Breadboard 400 punti     9 (minimo 10): ordinare 11
    Articoli sottoscorta: 2
    LED verde 5 mm: ora 25 pezzi.
    Attenzione: sotto la scorta minima (40).
    Breadboard 400 punti: ora 7 pezzi.
    Attenzione: sotto la scorta minima (10).
    Scheda Arduino Uno: disponibili solo 12 pezzi.
    LED verde 5 mm: ora 75 pezzi.
    Codice XXX sconosciuto.
    Dati non validi.
    Dati non validi.
    Resistenza 220 ohm: ora 40 pezzi.
    Attenzione: sotto la scorta minima (50).
    R220   Resistenza 220 ohm      40 (minimo 50): ordinare 60
    BB400  Breadboard 400 punti     7 (minimo 10): ordinare 13
    Articoli sottoscorta: 2
  ```

### Test 2 – Prelievo di tutto

- **Cosa si verifica:** si può prelevare esattamente la quantità
  disponibile.
- **Input:** `P ARDU 12`, `Q`
- **Output atteso:** `Scheda Arduino Uno: ora 0 pezzi.` e
  `Attenzione: sotto la scorta minima (8).`
