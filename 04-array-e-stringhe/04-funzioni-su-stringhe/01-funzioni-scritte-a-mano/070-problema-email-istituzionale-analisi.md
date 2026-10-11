# Analisi – 070-problema-email-istituzionale.c

## 1. Problema

La scuola assegna a studenti e docenti un indirizzo email della forma
`nome.cognome@dominio`, tutto in minuscolo e senza spazi né apostrofi. Il
dominio dipende dal ruolo (`studenti.scuola.edu.it` oppure `scuola.edu.it`).
Se la parte prima della `@` supera 25 caratteri, il nome viene ridotto
all'iniziale. Il programma stampa gli indirizzi e le liste di distribuzione
di docenti e studenti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 7 × 30 | Nomi (anche composti) |
| `cognomi` | `char[][]` | 7 × 30 | Cognomi (parallelo) |
| `ruoli` | `char[]` | 7 | `'S'` studente, `'D'` docente (parallelo) |
| `email` | `char[][]` | 7 × 60 | Indirizzi costruiti (parallelo) |

| Funzione | Compito |
|----------|---------|
| `crea_email` | Applica le regole e compone l'indirizzo |
| `solo_lettere` | Tiene solo le lettere, in minuscolo |
| `copia`, `concatena`, `lunghezza` | Funzioni di base scritte a mano |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Nome composto e apostrofo

**a) Input** – `Maria Grazia`, `D'Angelo`, `'D'`

**b) Output** – `mariagrazia.dangelo@scuola.edu.it`

**c) Variabili di supporto** – `parte_nome`, `parte_cognome`

**d) Vincoli** – `email` deve contenere tutto l'indirizzo più `'\0'` (60 celle)

**e) Assunzioni** – lettere senza accenti

**f) Algoritmo in linguaggio naturale**
1. Ridurre nome e cognome alle sole lettere minuscole.
2. Comporre: nome, `"."`, cognome, dominio scelto in base al ruolo.

### Caso d'uso 2 – Parte locale troppo lunga

**a) Input** – `Maria Vittoria`, `Dell'Acqua Bianchi`, `'S'`

**b) Output** – `m.dellacquabianchi@studenti.scuola.edu.it`

**c) Variabili di supporto** – lunghezze delle due parti

**d) Vincoli** – la parte locale (nome + punto + cognome) non supera 25 caratteri

**e) Assunzioni** – il cognome da solo sta nel limite

**f) Algoritmo in linguaggio naturale** – se la somma delle lunghezze più il
punto supera il limite, si tronca `parte_nome` dopo la prima lettera
scrivendo `'\0'` nella cella 1.

### Caso d'uso 3 – Liste di distribuzione

**a) Input** – array `ruoli`

**b) Output** – elenco docenti e elenco studenti

**c) Variabili di supporto** – `k`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – due scorrimenti dell'array parallelo:
il primo stampa gli indirizzi con ruolo `'D'`, il secondo quelli con `'S'`.
