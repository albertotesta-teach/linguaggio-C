# Analisi – 080-problema-vettore-di-parole.c

## 1. Problema

La classe raccoglie i termini del glossario di informatica, di lunghezza molto diversa e in numero non noto. Il glossario è un vettore dinamico di `char *`: ogni termine sta in un blocco di strlen + 1 byte. Il programma legge i termini fino a FINE senza doppioni, li ordina scambiando i puntatori e stampa il glossario con la memoria usata, confrontata con una matrice di char.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Glossario` | `dati (char **), n, capacita` | vettore dinamico di puntatori a stringhe |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `glossario` | `Glossario *` | struct + blocco di n char * (heap) | Indirizzi dei termini |
| ogni termine | `char *` | strlen + 1 (heap) | Testo copiato con malloc e strcpy |
| `parola` | `char[]` | 40 | Termine letto |
| `byte_testi` | `size_t` | — | Somma di strlen + 1 |

| Funzione | Compito |
|----------|---------|
| `aggiungi(g, termine)` | Copia il termine in un blocco nuovo e salva l'indirizzo; 0 se manca memoria |
| `termine(g, i)` | Termine i (const char *) |
| `cerca(g, parola)` | Indice del termine o -1 |
| `ordina(g)` | Selection sort scambiando i puntatori |
| `distruggi_glossario(g)` | Libera ogni termine, poi l'array di puntatori, poi la struct |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Glossario

**a) Input** – `processore bit compilatore multiprogrammazione RAM byte bit algoritmo FINE`

**b) Output** – 7 termini in ordine (RAM prima delle minuscole); 66 byte di testi + 64 di puntatori contro 280

**c) Variabili di supporto** – `byte_testi`

**d) Vincoli** – termini fino a 39 caratteri

**e) Assunzioni** – ordine di strcmp (ASCII)

**f) Algoritmo in linguaggio naturale** – aggiungi solo se cerca restituisce -1; ordina; stampa.

### Caso d'uso 2 – Doppione

**a) Input** – `bit` due volte

**b) Output** – "bit gia' presente"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – confronto esatto

**f) Algoritmo in linguaggio naturale** – cerca prima di aggiungere.

### Caso d'uso 3 – Distruzione

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima i blocchi dei termini, poi dati, poi la struct: altrimenti i termini restano irraggiungibili.
