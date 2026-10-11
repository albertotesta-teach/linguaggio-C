# Analisi – 060-problema-username.c

## 1. Problema

La segreteria deve creare gli account della piattaforma scolastica per otto
nuovi iscritti. Lo username è formato dall'iniziale del nome seguita dalle
lettere del cognome, tutto in minuscolo e al massimo 8 caratteri. Se lo
stesso username è già stato assegnato si aggiunge una cifra (2, 3, …).

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 8 × 25 | Nome di ogni iscritto |
| `cognomi` | `char[][]` | 8 × 25 | Cognome (array parallelo a `nomi`) |
| `usernames` | `char[][]` | 8 × 25 | Username assegnati (parallelo) |
| `base` | `char[]` | 25 | Username senza cifra |
| `candidato` | `char[]` | 25 | Username da verificare |
| `numero` | `int` | — | Cifra da aggiungere (1 = nessuna) |

| Funzione | Compito |
|----------|---------|
| `crea_base` | Iniziale del nome + lettere del cognome, minuscolo, max 8 |
| `gia_presente` | Cerca il candidato tra gli username già assegnati |
| `copia`, `lunghezza`, `confronta` | Funzioni di base scritte a mano |
| `minuscola`, `e_lettera` | Operazioni sul singolo carattere |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Username nuovo

**a) Input** – `Giuseppe`, `D'Amico`

**b) Output** – `gdamico`

**c) Variabili di supporto** – `base`

**d) Vincoli** – l'apostrofo non è una lettera e viene scartato

**e) Assunzioni** – il nome inizia con una lettera

**f) Algoritmo in linguaggio naturale**
1. Scrivere in `base` la minuscola della prima lettera del nome.
2. Aggiungere le lettere del cognome in minuscolo finché `base` ha meno di 8 caratteri.
3. Terminare con `'\0'`.

### Caso d'uso 2 – Username già usato

**a) Input** – `Marco Rossi` dopo `Mario Rossi`; poi `Mirko Rossi`

**b) Output** – `mrossi2`, `mrossi3`

**c) Variabili di supporto** – `numero`, `lung_base`

**d) Vincoli** – il confronto avviene solo con i `k` username già assegnati

**e) Assunzioni** – al massimo 9 omonimi (una sola cifra)

**f) Algoritmo in linguaggio naturale**
1. Copiare `base` in `candidato`, `numero = 1`.
2. Finché `candidato` è già presente: incrementare `numero`, ricopiare `base`
   e scrivere la cifra `'0' + numero` dopo l'ultimo carattere, seguita da `'\0'`.
3. Salvare `candidato` in `usernames[k]`.

### Caso d'uso 3 – Cognome lungo

**a) Input** – `Francesca Santangelo`, `Mattia Santangelini`

**b) Output** – `fsantang`, `msantang`

**c) Variabili di supporto** – `j` in `crea_base`

**d) Vincoli** – massimo 8 caratteri

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la copia del cognome si ferma quando
`base` raggiunge 8 caratteri; le due persone ottengono username diversi
grazie all'iniziale del nome.
