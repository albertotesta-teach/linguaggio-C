# Analisi – 070-problema-lettore-comandi.c

## 1. Problema

La scheda programmabile dell'aula riceve righe di comandi separati da `;`: `SET dispositivo valore` imposta luce, tapparelle o climatizzatore, `GET dispositivo` ne mostra il valore. Dispositivi sconosciuti e comandi incompleti vanno segnalati. Una riga vuota termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 3 × 16 | Nomi dei dispositivi |
| `valori` | `int[]` | 3 | Valori attuali |
| `p` | `const char *` | — | Puntatore di lettura nella riga |
| `comando`, `nome` | `char[]` | 16 | Parole lette |

| Funzione | Compito |
|----------|---------|
| `leggi_parola(&p, parola, max)` | Copia una parola e sposta `p` |
| `leggi_numero(&p, &n)` | Legge un numero e sposta `p` |
| `salta_separatori(&p)` | Salta spazi e `;` |
| `cerca_dispositivo(nomi, nome)` | Indice del dispositivo, -1 se non esiste |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Più comandi in una riga

**a) Input** – `SET luce 80; SET aria 22; GET luce`

**b) Output** – luce -> 80, aria -> 22, luce = 80

**c) Variabili di supporto** – `p`

**d) Vincoli** – ogni funzione riparte da dove si è fermata la precedente

**e) Assunzioni** – parole di sole lettere, valori interi

**f) Algoritmo in linguaggio naturale** – finché la riga non è finita: leggere comando e nome, eseguire, saltare fino al `;` e ai separatori.

### Caso d'uso 2 – Dispositivo sconosciuto

**a) Input** – `SET forno 200`

**b) Output** – "SET forno: dispositivo sconosciuto"

**c) Variabili di supporto** – `d` = -1

**d) Vincoli** – il resto della riga viene comunque eseguito

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dopo l'errore si salta al `;` successivo.

### Caso d'uso 3 – Valore mancante

**a) Input** – `SET luce`

**b) Output** – "SET luce: comando non valido"

**c) Variabili di supporto** – `leggi_numero` restituisce 0

**d) Vincoli** – il valore non cambia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – SET si esegue solo se il numero è stato letto.
