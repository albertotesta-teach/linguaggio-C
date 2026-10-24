# Analisi – 080-problema-carta-imbarco.c

## 1. Problema

Al gate del viaggio d'istruzione un accompagnatore controlla la carta
d'imbarco di ogni studente: il volo deve essere quello della classe e
l'imbarco non deve essere chiuso. Due tipi struct diversi descrivono il
volo (`Volo`) e la carta (`CartaImbarco`). Il cognome `FINE` termina e il
programma stampa quanti studenti sono stati imbarcati.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `carta.cognome` | `char[20]` | Cognome dello studente; `FINE` termina |
| `ore`, `minuti` | `int` | Ora attuale |
| `carta.volo`, `carta.posto` | `char[8]`, `char[4]` | Volo e posto scritti sulla carta |
| `classe` | `Volo` | Volo della classe (nel sorgente): FR1452, gate 14, chiusura 09:35 |

### Output

- L'intestazione con volo, gate e ora di chiusura.
- Per ogni studente: `<cognome>: passa, posto <posto>.`,
  `<cognome>: volo sbagliato (X invece di FR1452).`,
  `<cognome>: imbarco chiuso.` oppure
  `<cognome>: dati non validi, ripetere.`
- Alla fine: `Studenti imbarcati: N`.

### Vincoli

- Le due struct hanno campi con lo stesso significato (`codice` del volo e
  `volo` della carta) confrontati con `strcmp`.
- L'imbarco è chiuso dall'ora di chiusura in poi (09:35 è già chiuso).
- Un cognome per riga e una riga di dati per studente: il resto della
  riga viene scartato.
- Dati non validi non interrompono il controllo; a fine input il programma
  termina.

### Assunzioni

- L'ora attuale è un orario valido della stessa giornata.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Volo` | `typedef struct { char codice[8]; int gate; int chiusura_ore; int chiusura_minuti; } Volo;` | Il volo della classe |
| `CartaImbarco` | `typedef struct { char cognome[20]; char volo[8]; char posto[4]; } CartaImbarco;` | La carta di uno studente |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `carta` | `CartaImbarco` | Carta in esame |
| `letti` | `int` | Valore restituito da `scanf` |
| `passati` | `int` | Studenti imbarcati |
| `fine` | `int` | Flag di uscita |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Stampare i dati del volo.
2. Finché non si termina:
   1. leggere il cognome; con `FINE` o a fine input terminare;
   2. leggere ora, minuti, volo e posto (fine input → dati incompleti e
      fine);
   3. se i dati non sono quattro, segnalarlo;
   4. se il volo è diverso, volo sbagliato; se l'ora non è prima della
      chiusura, imbarco chiuso; altrimenti lo studente passa e si conta.
3. Stampare gli studenti imbarcati.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Controllo al gate

- **Cosa si verifica:** i quattro esiti, il confine dell'ora di chiusura e
  la ripetizione dopo dati non validi.
- **Input:** `Rossi` `9 10 FR1452 12A`, `Bianchi` `9 12 FR1425 3C`,
  `Verdi` `9 35 FR1452 7B`, `Neri` `nove e venti`, `Neri`
  `9 20 FR1452 7B`, `FINE`
- **Output atteso:**
  ```
  Volo FR1452, gate 14, chiusura imbarco 09:35
    Rossi: passa, posto 12A.
    Bianchi: volo sbagliato (FR1425 invece di FR1452).
    Verdi: imbarco chiuso.
    Neri: dati non validi, ripetere.
    Neri: passa, posto 7B.
  Studenti imbarcati: 2
  ```

### Test 2 – Input interrotto

- **Input:** `Rossi`, poi fine input.
- **Output atteso:**
  ```
    Dati incompleti.
  Studenti imbarcati: 0
  ```
