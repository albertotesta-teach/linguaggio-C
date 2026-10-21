# Analisi – 070-problema-parola-piu-lunga.c

## 1. Problema

La redazione del giornalino scolastico vuole controllare che i titoli
stiano nelle colonne: per ogni titolo il programma conta le parole, trova
la parola più lunga con la sua posizione e segnala quelle che superano 12
lettere.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `titoli` | `char[4][80]` | `Torneo di pallavolo: vince la 4B`, `Intervista alla dirigente scolastica`, `Laboratorio di elettrotecnica aperto al pomeriggio`, `Gita a Torino, si parte lunedi` |

### Output

- Per ogni titolo: il titolo, il numero di parole, la parola più lunga con
  il numero di lettere e la posizione in cui inizia, e
  `<- troppo lunga per la colonna` se supera 12 lettere.

### Vincoli

- Una parola è una sequenza di lettere (`isalpha`): le cifre non sono
  lettere, quindi in "4B" la parola è "B".
- `parola_piu_lunga` restituisce la posizione in cui inizia la parola più
  lunga (`migliore − testo`) e scrive la lunghezza in `*lunghezza`
  (parametro di uscita).
- La parola non si copia: si stampa direttamente dal titolo con `%.*s`,
  passando lunghezza e puntatore all'inizio.
- `conta_parole` conta le lettere precedute da un carattere che non è una
  lettera; `*(p − 1)` si legge solo se `p` non è il primo carattere.
- A parità di lunghezza vale la prima parola (confronto con `>`).
- Limite della colonna: 12 lettere (13 o più sono troppe).

### Assunzioni

- I titoli non contengono lettere accentate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `migliore` | `const char *` | Inizio della parola più lunga nel titolo |
| `lunghezza` | `int` | Lettere della parola più lunga |
| `t` | `int` | Indice del titolo |
| `p`, `parola` | `const char *` | Nelle funzioni: carattere esaminato, inizio della parola corrente |
| `LIMITE` | `#define` | 12 |

| Funzione | Compito |
|----------|---------|
| `parola_piu_lunga(testo, &lunghezza)` | Posizione della parola più lunga; lunghezza come parametro di uscita |
| `conta_parole(testo)` | Numero di parole |

### Algoritmo in linguaggio naturale

1. Per ogni titolo:
   1. calcolare `migliore = titolo + parola_piu_lunga(titolo, &lunghezza)`;
   2. stampare titolo, numero di parole, parola più lunga, lunghezza e
      posizione;
   3. se la lunghezza supera 12 aggiungere l'avviso.
2. In `parola_piu_lunga`: scorrendo il testo, a ogni lettera ricordare
   l'inizio della parola, avanzare fino alla sua fine e, se `p − parola` è
   maggiore della lunghezza migliore, aggiornare lunghezza e `migliore`.

## 3. Casi di test

### Test 1 – Titoli del sorgente

- **Cosa si verifica:** parola più lunga, parità ("Intervista" e
  "scolastica" hanno 10 lettere: vale la prima), parola oltre il limite,
  conteggio con punteggiatura e cifre.
- **Input:** nessuno.
- **Output atteso:**
  ```
  === CONTROLLO TITOLI (limite 12 lettere per parola) ===

    "Torneo di pallavolo: vince la 4B"
    parole: 6, la piu' lunga: "pallavolo" (9 lettere, dalla posizione 10)

    "Intervista alla dirigente scolastica"
    parole: 4, la piu' lunga: "Intervista" (10 lettere, dalla posizione 0)

    "Laboratorio di elettrotecnica aperto al pomeriggio"
    parole: 6, la piu' lunga: "elettrotecnica" (14 lettere, dalla posizione 15)  <- troppo lunga per la colonna

    "Gita a Torino, si parte lunedi"
    parole: 6, la piu' lunga: "Torino" (6 lettere, dalla posizione 7)
  ```
