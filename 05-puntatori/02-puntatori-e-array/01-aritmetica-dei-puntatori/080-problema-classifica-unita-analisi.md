# Analisi – 080-problema-classifica-unita.c

## 1. Problema

I 100 metri si sono corsi in due batterie, ciascuna con i tempi già in
ordine crescente. Bisogna costruire la classifica finale unendo i due
elenchi in un solo elenco ordinato, indicando per ogni tempo la batteria di
provenienza e le tre medaglie.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `batteria_a`, `batteria_b` | `int[]` | 5, 4 | Tempi ordinati in centesimi di secondo |
| `classifica` | `int[]` | 9 | Tempi uniti |
| `provenienza` | `char[]` | 9 | `'A'` o `'B'`, parallelo a `classifica` |
| `pa`, `pb` | `const int *` | — | Primo tempo non ancora usato di ogni batteria |
| `fine_a`, `fine_b` | `const int *` | — | Fine delle due batterie |
| `pc`, `pv` | `int *`, `char *` | — | Prossima posizione libera in `classifica` e `provenienza` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Fusione

**a) Input** – A = 11.85, 12.12, …; B = 11.79, 12.26, …

**b) Output** – 11.79 (B), 11.85 (A), 12.12 (A), …

**c) Variabili di supporto** – `pa`, `pb`, `pc`, `pv`

**d) Vincoli** – ogni tempo si copia una sola volta; i puntatori avanzano
solo in avanti

**e) Assunzioni** – le batterie sono già ordinate; a parità vince la A

**f) Algoritmo in linguaggio naturale**
1. Finché entrambe le batterie hanno tempi, copiare in `*pc` il minore tra
   `*pa` e `*pb`, scrivere la batteria in `*pv` e far avanzare il puntatore
   usato insieme a `pc` e `pv`.

### Caso d'uso 2 – Tempi rimasti

**a) Input** – la batteria B finisce dopo 12.90; restano 13.01 e 13.55 di A

**b) Output** – i due tempi in coda alla classifica

**c) Variabili di supporto** – `pa`, `fine_a`

**d) Vincoli** – al massimo uno dei due cicli finali viene eseguito

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – copiare i tempi da `pa` a `fine_a`
escluso, poi da `pb` a `fine_b` escluso.

### Caso d'uso 3 – Controllo finale

**a) Input** – classifica completa

**b) Output** – "Posizioni scritte: pc - &classifica[0] = 9"

**c) Variabili di supporto** – `pc`

**d) Vincoli** – il numero deve essere 5 + 4

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la differenza tra `pc` e l'inizio
dell'array dice quante posizioni sono state scritte.
