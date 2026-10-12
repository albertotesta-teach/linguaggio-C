# Analisi – 070-problema-cifratura-messaggi.c

## 1. Problema

Il club di crittografia confronta tre cifrari che agiscono su una lettera alla volta: Cesare (+3), ROT13 (+13) e Atbash (alfabeto rovesciato). Per ogni messaggio il programma mostra il testo cifrato con i tre metodi e controlla che decifrandolo si torni all'originale. Una riga vuota termina.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Trasforma` | `typedef char (*Trasforma)(char c);` | funzione che trasforma un carattere |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `cifra`, `decifra` | `Trasforma[]` | 3 | Funzioni per cifrare e decifrare |
| `nomi` | `const char *[]` | 3 | Nomi dei metodi |
| `messaggio`, `copia` | `char[]` | 100 | Testo originale e testo lavorato |

| Funzione | Compito |
|----------|---------|
| `sposta(c, passo)` | Sposta una lettera nel suo alfabeto, ricominciando dopo la Z |
| `cesare, cesare_inverso, rot13` | Spostamenti di 3, 23 e 13 |
| `atbash(c)` | A diventa Z, B diventa Y, ... |
| `applica(testo, t)` | Applica t a ogni carattere del testo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Cifratura

**a) Input** – `Zebra xyz`

**b) Output** – Cesare "Cheud abc", ROT13 "Mroen klm", Atbash "Avyiz cba"

**c) Variabili di supporto** – `copia`

**d) Vincoli** – maiuscole e minuscole restano tali; gli altri caratteri non cambiano

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – copiare il messaggio e applicare cifra[m] a ogni carattere.

### Caso d'uso 2 – Controllo

**a) Input** – qualsiasi messaggio

**b) Output** – "-> decifrato ok"

**c) Variabili di supporto** – `copia`

**d) Vincoli** – ROT13 e Atbash sono il proprio inverso

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – applicare decifra[m] e confrontare con strcmp.

### Caso d'uso 3 – Fine

**a) Input** – riga vuota

**b) Output** – il programma termina

**c) Variabili di supporto** – `continua`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – una riga vuota azzera continua prima dei cicli.
