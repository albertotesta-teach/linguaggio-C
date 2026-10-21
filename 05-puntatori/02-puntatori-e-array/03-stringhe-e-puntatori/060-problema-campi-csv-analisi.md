# Analisi – 060-problema-campi-csv.c

## 1. Problema

Il registro elettronico esporta i voti come righe CSV
`cognome;nome;classe;voto`. Il programma scompone ogni riga nei campi,
scarta le righe con un numero di campi diverso da 4 o con un voto non
valido, stampa una tabella dei voti importati e ne calcola la media.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `righe` | `char[6][60]` | `Rossi;Mario;4B;7.5`, `Bianchi;Laura;4B;8`, `Verdi;Paolo;4B`, `Neri;Sara;4B;sei`, `Esposito;Luca;4B;6.25`, `Gallo;Anna;4B;9;assente` |

### Output

- La tabella dei voti importati: cognome, nome, classe, voto con due decimali.
- Per ogni riga scartata il motivo: `N campi invece di 4` (con la riga) o
  `voto non valido "..."`.
- Il numero di righe importate e, se ce ne sono, la media dei voti.

### Vincoli

- `dividi_riga` scorre la riga con il puntatore `p` e copia i caratteri nel
  campo corrente tramite `dest`; a ogni `;` chiude il campo con `'\0'` e
  passa al successivo. Restituisce il numero di campi (separatori + 1).
- Oltre il quarto campo si continua a contare ma non si copia: l'array
  `campi` ha solo 4 righe.
- Un campo contiene al massimo 15 caratteri: quelli in più si ignorano.
- Il voto si converte con `sscanf("%lf")` e deve essere tra 1 e 10.
- La media si calcola solo se è stata importata almeno una riga.

### Assunzioni

- Il separatore è sempre `;`; il voto usa il punto decimale.
- Un voto seguito da altri caratteri (es. `7.5x`) viene accettato perché
  `sscanf` legge la parte numerica.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `campi` | `char[4][16]` | Campi della riga corrente |
| `n` | `int` | Numero di campi trovati |
| `voto`, `somma` | `double` | Voto convertito, somma per la media |
| `importate` | `int` | Righe importate |
| `p`, `dest`, `numero` | `const char *`, `char *`, `int` | In `dividi_riga` |

| Funzione | Compito |
|----------|---------|
| `dividi_riga(riga, campi)` | Copia i campi e restituisce quanti sono |

### Algoritmo in linguaggio naturale

1. Per ogni riga:
   1. dividerla nei campi;
   2. se i campi non sono 4 scartarla indicando quanti sono;
   3. altrimenti, se il quarto campo non è un numero tra 1 e 10 scartarla;
   4. altrimenti stampare la riga della tabella e sommare il voto.
2. Stampare le righe importate e la media.

## 3. Casi di test

### Test 1 – Righe del sorgente

- **Cosa si verifica:** righe corrette, campi in meno, campi in più, voto
  non numerico.
- **Input:** nessuno.
- **Valori intermedi attesi:** media (7.5 + 8 + 6.25) / 3 = 7.25.
- **Output atteso:**
  ```
  === IMPORTAZIONE VOTI ===
    Cognome    Nome     Classe Voto
    Rossi      Mario    4B     7.50
    Bianchi    Laura    4B     8.00
    riga 3 scartata: 3 campi invece di 4  [Verdi;Paolo;4B]
    riga 4 scartata: voto non valido "sei"
    Esposito   Luca     4B     6.25
    riga 6 scartata: 5 campi invece di 4  [Gallo;Anna;4B;9;assente]

  Righe importate: 3 su 6
  Media dei voti: 7.25
  ```
