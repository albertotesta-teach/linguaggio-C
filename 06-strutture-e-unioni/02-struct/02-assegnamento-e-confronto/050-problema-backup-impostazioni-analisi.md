# Analisi – 050-problema-backup-impostazioni.c

## 1. Problema

La LIM dell'aula ha luminosità, volume, ingresso e tempo di spegnimento. Il programma permette di modificarli, salvarne un backup, ripristinarlo o tornare ai valori di fabbrica con un solo assegnamento tra struct. All'uscita confronta le impostazioni in uso con il backup e avvisa delle modifiche non salvate.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Impostazioni` | `luminosita, volume, ingresso, spegnimento` | configurazione della LIM |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `predefinite` | `const Impostazioni` | — | Valori di fabbrica |
| `corrente` | `Impostazioni` | — | Valori in uso |
| `salvate` | `Impostazioni` | — | Ultimo backup |
| `uguali` | `int` | — | Esito del confronto finale |

| Funzione | Compito |
|----------|---------|
| `main` | Comandi L, V, I, B, R, F, S, Q |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Backup e ripristino

**a) Input** – `L 90`, `I PC`, `B`, `V 10`, `R`

**b) Output** – dopo R il volume torna a 40, luminosità 90 e ingresso PC restano

**c) Variabili di supporto** – `salvate`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – B: salvate = corrente; R: corrente = salvate.

### Caso d'uso 2 – Valori non ammessi

**a) Input** – `V 120`, `I VGA`

**b) Output** – "Valore tra 0 e 100."; "Ingressi: HDMI1, HDMI2, PC."

**c) Variabili di supporto** – —

**d) Vincoli** – volume e luminosità 0-100

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il campo non cambia.

### Caso d'uso 3 – Uscita

**a) Input** – `Q` dopo modifiche non salvate

**b) Output** – "Attenzione: ci sono modifiche non salvate."

**c) Variabili di supporto** – `uguali`

**d) Vincoli** – il confronto è campo per campo, ingresso con strcmp

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – non si può scrivere corrente == salvate.
