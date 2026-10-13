# Analisi – 070-problema-elenco-senza-doppioni.c

## 1. Problema

Gli studenti si offrono volontari per l'open day; qualcuno si iscrive due volte, qualcuno si ritira. L'elenco è un vettore dinamico di `Nome` con due operazioni in più: aggiungi_se_manca e rimuovi_valore. I nomi si normalizzano (iniziale maiuscola, resto minuscolo) così "rossi" e "ROSSI" sono la stessa persona.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Nome` | `testo[20]` | un volontario |
| `Elenco` | `dati (Nome *), n, capacita` | vettore senza doppioni |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `volontari` | `Elenco *` | struct + blocco di n Nome (heap) | Volontari in ordine di iscrizione |
| `nome` | `char[]` | 20 | Nome letto e normalizzato |
| `esito` | `int` | — | 1 aggiunto, 0 già presente, -1 memoria |

| Funzione | Compito |
|----------|---------|
| `aggiungi_se_manca(e, nome)` | Cerca; se manca aggiunge (raddoppio); 1, 0 o -1 |
| `rimuovi_valore(e, nome)` | Cerca e rimuove spostando i successivi; 0 se manca |
| `sistema(nome)` | Iniziale maiuscola, resto minuscolo |
| `cerca, lunghezza, elemento, crea_elenco, distruggi_elenco` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Iscrizioni

**a) Input** – `I rossi`, `I Bianchi`, `I ROSSI`, `I verdi`, `I Neri`

**b) Output** – 4 volontari; "Rossi e' gia' nell'elenco"

**c) Variabili di supporto** – `esito`

**d) Vincoli** – nomi fino a 19 caratteri

**e) Assunzioni** – un nome identifica una persona

**f) Algoritmo in linguaggio naturale** – sistema, poi aggiungi_se_manca.

### Caso d'uso 2 – Ritiro e reiscrizione

**a) Input** – `R bianchi`, `R Gialli`, `I bianchi`, `E`

**b) Output** – Bianchi esce e rientra in fondo: Rossi, Verdi, Neri, Bianchi; "Gialli non e' nell'elenco"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – rimuovi_valore sposta indietro i successivi.

### Caso d'uso 3 – Fine dell'input

**a) Input** – EOF

**b) Output** – uscita come Q

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scanf != 1 imposta Q.
