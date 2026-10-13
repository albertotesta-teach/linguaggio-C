# Analisi – 040-problema-rubrica-della-classe.c

## 1. Problema

Il rappresentante di classe tiene i contatti dei compagni in una rubrica, vettore dinamico di `Contatto`. Le quattro operazioni classiche: aggiunta (rifiutata se il nome c'è già), ricerca per inizio del nome, modifica del telefono tramite il puntatore restituito da trova, cancellazione con spostamento dei successivi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Contatto` | `nome[20], telefono[16]` | un compagno |
| `Rubrica` | `dati (Contatto *), n, capacita` | vettore dinamico di contatti |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `rubrica` | `Rubrica *` | struct + blocco di n Contatto (heap) | Contatti in ordine di inserimento |
| `c` | `Contatto` | — | Dati letti |
| `p` | `Contatto *` | — | Contatto nel vettore, usato subito |
| `testo` | `char[]` | 20 | Inizio del nome o nome da cancellare |
| `trovati` | `int` | — | Risultati della ricerca |

| Funzione | Compito |
|----------|---------|
| `trova(r, nome)` | Puntatore al contatto o NULL; valido fino alla prossima aggiunta |
| `elemento(r, i)` | Puntatore al contatto i |
| `rimuovi(r, posizione)` | Sposta a sinistra i successivi |
| `telefono_valido(telefono)` | Solo cifre, da 6 a 15 |
| `inizia_con(nome, testo)` | strncmp sulla lunghezza di testo |
| `crea_rubrica, aggiungi, lunghezza, cerca, distruggi_rubrica` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Aggiunte

**a) Input** – `A Rossi 3331234567`, `A Russo 3479876543`, `A Bianchi 3201112223`

**b) Output** – 3 contatti

**c) Variabili di supporto** – —

**d) Vincoli** – nome fino a 19 caratteri

**e) Assunzioni** – un nome per persona

**f) Algoritmo in linguaggio naturale** – trova == NULL, poi aggiungi.

### Caso d'uso 2 – Rifiuti

**a) Input** – `A Rossi 3330000000`, `A Verdi 12ab`

**b) Output** – "Rossi e' gia' in rubrica.", "Dati non validi."

**c) Variabili di supporto** – —

**d) Vincoli** – telefono valido

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controlli prima dell'aggiunta.

### Caso d'uso 3 – Ricerca

**a) Input** – `C Ru`

**b) Output** – Russo (Rossi non inizia con Ru)

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – —

**e) Assunzioni** – maiuscole distinte

**f) Algoritmo in linguaggio naturale** – inizia_con su ogni elemento.

### Caso d'uso 4 – Modifica

**a) Input** – `M Russo 3470000001`

**b) Output** – "Russo: 3479876543 -> 3470000001"

**c) Variabili di supporto** – `p`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – strcpy in p->telefono: il vettore cambia direttamente.

### Caso d'uso 5 – Cancellazione

**a) Input** – `D Rossi`, `D Gialli`, `E`

**b) Output** – 2 contatti: Russo, Bianchi; "Contatto non trovato."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca, poi rimuovi.
