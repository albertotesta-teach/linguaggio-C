# Analisi – 070-problema-magazzino-del-laboratorio.c

## 1. Problema

Il tecnico del laboratorio di elettronica tiene il conto del materiale: ogni articolo ha quantità e scorta minima. Il magazzino è un vettore dinamico di `Articolo`; carico e scarico modificano l'articolo tramite il puntatore restituito da trova. L'elenco da riordinare è un secondo vettore, creato da sotto_scorta con le copie degli articoli sotto la scorta: una fotografia del momento, distrutta dopo la stampa.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Articolo` | `nome[20], quantita, scorta` | un materiale |
| `Magazzino` | `dati (Articolo *), n, capacita` | vettore dinamico di articoli |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `magazzino` | `Magazzino *` | struct + blocco di n Articolo (heap) | Tutti gli articoli |
| `riordino` | `Magazzino *` | creato da sotto_scorta | Copie da riordinare |
| `a` | `Articolo` | — | Dati letti |
| `p` | `Articolo *` | — | Articolo da caricare o scaricare |
| `quantita` | `int` | — | Pezzi del movimento |

| Funzione | Compito |
|----------|---------|
| `trova(m, nome)` | Puntatore all'articolo o NULL |
| `sotto_scorta(m)` | Vettore nuovo con le copie degli articoli sotto scorta |
| `stampa(m)` | Tabella articolo, quantità, scorta |
| `crea_magazzino, aggiungi, lunghezza, elemento, distruggi_magazzino` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Nuovi articoli

**a) Input** – `N resistenze 200 50`, `N LED 40 30`, `N breadboard 12 10`, `N Arduino 6 4`

**b) Output** – 4 articoli; `N LED 5 5` rifiutato

**c) Variabili di supporto** – —

**d) Vincoli** – quantità e scorta ≥ 0

**e) Assunzioni** – nomi unici

**f) Algoritmo in linguaggio naturale** – trova == NULL, poi aggiungi.

### Caso d'uso 2 – Scarichi

**a) Input** – `S LED 15`, `S breadboard 20`, `S breadboard 3`

**b) Output** – LED 25 (sotto scorta); "disponibili solo 12"; breadboard 9 (sotto scorta)

**c) Variabili di supporto** – `p`

**d) Vincoli** – scarico ≤ disponibile

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – p->quantita -= quantita.

### Caso d'uso 3 – Riordino

**a) Input** – `R`

**b) Output** – 3 articoli: LED, breadboard, Arduino

**c) Variabili di supporto** – `riordino`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sotto_scorta, stampa, distruggi.

### Caso d'uso 4 – Carico

**a) Input** – `C LED 50`, `R`

**b) Output** – LED 75; ora da riordinare 2 articoli

**c) Variabili di supporto** – —

**d) Vincoli** – quantità > 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il vecchio elenco non si aggiorna: se ne crea uno nuovo.

### Caso d'uso 5 – Articolo inesistente

**a) Input** – `C transistor 10`

**b) Output** – "Articolo inesistente o quantita non valida."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – trova restituisce NULL.
