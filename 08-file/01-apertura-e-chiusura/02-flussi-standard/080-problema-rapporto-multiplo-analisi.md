# Analisi – 080-problema-rapporto-multiplo.c

## 1. Problema

Ogni venerdì le classi pesano la carta raccolta. Il referente inserisce la
settimana e i chili di ogni classe. Il rapporto va a video e nel file
`carta-settimana-NN.txt` (stessa funzione, due flussi), mentre una riga di
riepilogo si aggiunge in fondo a `storico-carta.txt`. Alla fine il
programma ristampa lo storico.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `settimana` | `int` | Settimana dell'anno, da 1 a 53 |
| `classi[i]` | testo | Nome della classe, fino a 7 caratteri, fino a `FINE` |
| `kg[i]` | `double` | Chili raccolti dalla classe, non negativi |

### Output

- Il rapporto `Raccolta della carta - settimana S`, una riga per classe
  (nome in 6 colonne, chili con un decimale) e la riga `Totale` con la
  media per classe; uguale a video e in `carta-settimana-NN.txt`.
- `Rapporto salvato in NOME`, `Storico aggiornato:` e tutto lo storico,
  la cui ultima riga è `settimana S: N classi, T kg, migliore C`
  (`1 classe` al singolare).
- `  chili non validi per C: classe scartata`, `  mancano i chili di C`,
  `  raggiunto il massimo di 10 classi`.
- `Settimana non valida.`, `Nessuna classe inserita.`; errori di apertura
  su `stderr`.

### Vincoli

- `stampa_rapporto(f, ...)` scrive solo su `f`: si chiama con `stdout` e
  con il file aperto in `"w"`.
- Il rapporto settimanale si apre in `"w"` (si rifà da capo), lo storico
  in `"a"` (si aggiunge in fondo); ogni `fopen` si controlla e ogni file
  si chiude.
- Il nome si costruisce con `sprintf` e `%02d` in 40 caratteri.
- Al massimo 10 classi; i chili non numerici o negativi scartano la
  classe senza interrompere l'inserimento.
- La migliore è la prima classe con il massimo dei chili.

### Assunzioni

- Ogni classe compare una sola volta nella settimana.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `classi`, `kg` | `char[10][8]`, `double[10]` | Dati della settimana |
| `n` | `int` | Classi valide inserite |
| `letti` | `int` | Risultato di `scanf` per i chili |
| `totale`, `migliore` | `double`, `int` | Riepilogo per lo storico |
| `nome_file` | `char[40]` | Nome del rapporto |
| `rapporto`, `storico` | `FILE *` | I due file |
| `CLASSI` | `#define` | 10 |

| Funzione | Compito |
|----------|---------|
| `stampa_rapporto(f, settimana, classi, kg, n)` | Scrive il rapporto sul flusso `f` |
| `ricopia(nome)` | Stampa a video il contenuto di un file |

### Algoritmo in linguaggio naturale

1. Leggere la settimana; se non è valida, terminare.
2. Leggere classe e chili fino a `FINE`, alla fine dell'input o a 10
   classi; scartare le classi con chili non validi.
3. Senza classi stampare `Nessuna classe inserita.`.
4. Altrimenti calcolare totale e migliore, stampare il rapporto a video,
   salvarlo in `carta-settimana-NN.txt`, aggiungere la riga di riepilogo
   allo storico e ristamparlo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si parte senza
`storico-carta.txt`; i test vanno eseguiti in ordine.

### Test 1 – Settimana 7

- **Input:** `7`, `3A 6.5 3B 11 4A 8.5 5C 5.5 FINE`
- **Valori intermedi attesi:** totale 31.5, media 7.875 (stampata 7.9),
  migliore 3B.
- **Output atteso:**
  ```
  Settimana: Classe e chili di carta (FINE per terminare):

  Raccolta della carta - settimana 7
    3A        6.5 kg
    3B       11.0 kg
    4A        8.5 kg
    5C        5.5 kg
    Totale   31.5 kg (media 7.9 kg per classe)

  Rapporto salvato in carta-settimana-07.txt
  Storico aggiornato:
  settimana 7: 4 classi, 31.5 kg, migliore 3B
  ```

### Test 2 – Settimana 8: lo storico cresce

- **Input:** `8`, `3A 7 3B 9.5 4A 10 FINE`
- **Output atteso:** il rapporto con `Totale   26.5 kg (media 8.8 kg per
  classe)`, poi
  ```
  Storico aggiornato:
  settimana 7: 4 classi, 31.5 kg, migliore 3B
  settimana 8: 3 classi, 26.5 kg, migliore 4A
  ```

### Test 3 – Chili non validi

- **Cosa si verifica:** le classi errate si scartano e l'inserimento
  continua; singolare nello storico.
- **Input:** `9`, `3A tanti 3B -2 4A 3`, `5B`, poi fine input
- **Output atteso:**
  ```
  Settimana: Classe e chili di carta (FINE per terminare):
    chili non validi per 3A: classe scartata
    chili non validi per 3B: classe scartata
    mancano i chili di 5B

  Raccolta della carta - settimana 9
    4A        3.0 kg
    Totale    3.0 kg (media 3.0 kg per classe)
  ```
  e in fondo allo storico `settimana 9: 1 classe, 3.0 kg, migliore 4A`.

### Test 4 – Casi limite

- **Input:** `54`; poi `10`, `FINE`; poi `11` seguito da 11 coppie
  `C1 1 ... C11 11`
- **Output atteso:** `Settimana non valida.`; poi
  `Nessuna classe inserita.`; poi `  raggiunto il massimo di 10 classi` e
  il rapporto delle prime 10 classi.
