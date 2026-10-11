# Analisi – 050-problema-durata-allenamento.c

## 1. Problema

Durante un allenamento in pista l'allenatore inserisce il tempo di ogni
giro (minuti:secondi). Il programma mostra dopo ogni giro la durata totale
in ore, minuti e secondi, segnala quando un giro è il più veloce finora e
alla fine stampa numero di giri, durata e giro migliore. `0:00` termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ore`, `minuti`, `secondi` | `int` | — | Durata totale, aggiornata dalle funzioni |
| `migliore` | `int` | — | Giro più veloce in secondi, -1 se nessuno |
| `giri` | `int` | — | Giri validi inseriti |
| `m`, `s` | `int` | — | Tempo del giro letto |

| Funzione | Compito |
|----------|---------|
| `aggiungi_giro(&ore, &minuti, &secondi, m, s)` | Somma un giro alla durata |
| `normalizza(&ore, &minuti, &secondi)` | Riporta secondi e minuti oltre 59 |
| `aggiorna_migliore(&migliore, m, s)` | Aggiorna il giro migliore, 1 se cambiato |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Riporto dei secondi

**a) Input** – `5:42`, poi `5:18`

**b) Output** – totale 0:05:42, poi 0:11:00

**c) Variabili di supporto** – `ore`, `minuti`, `secondi`

**d) Vincoli** – le tre variabili sono parametri di ingresso e uscita

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Sommare minuti e secondi del giro.
2. `normalizza`: minuti += secondi / 60, secondi %= 60; ore += minuti / 60,
   minuti %= 60.

### Caso d'uso 2 – Giro migliore

**a) Input** – 5:42, 5:18, 6:05, 5:09

**b) Output** – "nuovo giro migliore" al 1°, 2° e 4° giro; riepilogo "giro
migliore 5:09"

**c) Variabili di supporto** – `migliore`

**d) Vincoli** – la funzione cambia `*migliore` solo se il giro è più veloce

**e) Assunzioni** – a parità di tempo il record non cambia

**f) Algoritmo in linguaggio naturale** – convertire il giro in secondi; se
`*migliore` vale -1 o il giro è minore, aggiornarlo e restituire 1.

### Caso d'uso 3 – Tempo non valido

**a) Input** – `5:61`

**b) Output** – "Tempo non valido." e il giro non viene contato

**c) Variabili di supporto** – `giri`

**d) Vincoli** – secondi da 0 a 59, valori non negativi

**e) Assunzioni** – un input non numerico termina

**f) Algoritmo in linguaggio naturale** – controllare `m` e `s` prima di
chiamare le funzioni.
