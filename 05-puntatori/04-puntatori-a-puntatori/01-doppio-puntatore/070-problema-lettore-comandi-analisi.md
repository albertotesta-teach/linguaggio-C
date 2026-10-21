# Analisi – 070-problema-lettore-comandi.c

## 1. Problema

La scheda programmabile dell'aula riceve righe di comandi separati da `;`:
`SET dispositivo valore` imposta luce, tapparelle o climatizzatore,
`GET dispositivo` ne mostra il valore. Dispositivi sconosciuti e comandi
incompleti vanno segnalati. Una riga vuota termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[100]` | Uno o più comandi separati da `;`, letti con `fgets`; riga vuota per finire |
| `nomi`, `valori` | `char[3][16]`, `int[3]` | Dispositivi `luce` (0), `tapparelle` (100), `aria` (20), nel sorgente |

### Output

- Per ogni comando: `dispositivo -> valore` (SET), `dispositivo = valore`
  (GET), oppure `COMANDO nome: dispositivo sconosciuto` o
  `COMANDO nome: comando non valido`.

### Vincoli

- Le funzioni di lettura ricevono l'indirizzo del puntatore di lettura
  (`const char **p`) e lo spostano: ogni funzione riparte da dove si è
  fermata la precedente.
- `leggi_parola` copia al massimo 15 lettere; le lettere in più si saltano.
- Un comando con un dispositivo sconosciuto o un valore mancante viene
  segnalato e il valore non cambia; il resto della riga viene comunque
  eseguito, ripartendo dopo il `;` successivo.
- I comandi `SET` e `GET` sono in maiuscolo; le parole si confrontano con
  `strcmp`.
- Una riga più lunga del buffer viene troncata e il resto si scarta; la fine
  dell'input termina il programma.

### Assunzioni

- Le parole sono di sole lettere, i valori interi non negativi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `p` | `const char *` | Puntatore di lettura nella riga |
| `comando`, `nome` | `char[16]` | Parole lette |
| `d`, `n` | `int` | Indice del dispositivo, valore letto |
| `a_capo`, `c`, `continua` | `char *`, `int`, `int` | Lettura della riga |

| Funzione | Compito |
|----------|---------|
| `leggi_parola(&p, parola, max)` | Copia una parola e sposta `p` |
| `leggi_numero(&p, &n)` | Legge un numero e sposta `p`; 1 se riuscita |
| `salta_separatori(&p)` | Salta spazi e `;` |
| `cerca_dispositivo(nomi, nome)` | Indice del dispositivo, -1 se non esiste |

### Algoritmo in linguaggio naturale

1. Finché `continua`: leggere una riga (a fine input terminare), togliere il
   `'\n'` o scartare il resto; una riga vuota termina.
2. Partendo dall'inizio della riga, saltati i separatori, finché la riga non
   è finita:
   1. leggere comando e nome, cercare il dispositivo;
   2. dispositivo sconosciuto → segnalarlo; `GET` → stampare il valore;
      `SET` con un numero → impostarlo; altrimenti comando non valido;
   3. avanzare fino al `;` successivo e saltare i separatori.

## 3. Casi di test

Nell'output le righe inserite non compaiono (input da pipe).

### Test 1 – Più comandi e comandi errati

- **Input:** `SET luce 80; SET aria 22; GET luce`;
  `SET forno 200; GET tapparelle`; `SET luce`; `set luce 5;;  GET aria`;
  riga vuota
- **Output atteso:**
  ```
    luce -> 80
    aria -> 22
    luce = 80
    SET forno: dispositivo sconosciuto
    tapparelle = 100
    SET luce: comando non valido
    set luce: comando non valido
    aria = 22
  ```
  (dopo un comando errato il resto della riga viene eseguito; `;;` e spazi
  in più vengono saltati).
