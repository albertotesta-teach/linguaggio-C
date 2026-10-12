# Analisi – 070-problema-visite-museo.c

## 1. Problema

Il museo civico ha una sola guida: le visite delle classi nello stesso giorno non possono sovrapporsi. Il programma legge le richieste (classe, docente, data, ora di inizio, durata), controlla durata, orario di apertura e sovrapposizioni, registra le visite accettate e alla fine stampa il calendario.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Data` | `giorno, mese, anno` | data del calendario |
| `Orario` | `ore, minuti` | ora del giorno |
| `Visita` | `classe, docente, giorno, inizio, durata` | visita guidata |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `visite` | `Visita[]` | 8 | Visite prenotate |
| `n_visite` | `int` | — | Visite usate |
| `nuova` | `Visita` | — | Richiesta letta |
| `parola` | `char[]` | 8 | Classe o FINE |
| `inizio`, `fine` | `int` | — | Minuti dalla mezzanotte |
| `conflitto` | `int` | — | Visita sovrapposta, -1 se nessuna |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prenotazione

**a) Input** – `2C Bruni 12/03/2026 11:00 90`

**b) Output** – "Prenotata: 2C con Bruni, fine alle 12:30."

**c) Variabili di supporto** – `n_visite`

**d) Vincoli** – 9:00-17:00, da 30 a 180 minuti

**e) Assunzioni** – una sola guida

**f) Algoritmo in linguaggio naturale** – se tutti i controlli passano, copiare nuova in visite[n_visite].

### Caso d'uso 2 – Sovrapposizione

**a) Input** – `4A Sala 12/03/2026 10:30 60`

**b) Output** – "Sovrapposta alla visita della 2C (11:00, 90 min)."

**c) Variabili di supporto** – `conflitto`

**d) Vincoli** – stesso giorno: confronto di giorno, mese e anno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – due intervalli si sovrappongono se inizio < altra_fine e altro_inizio < fine.

### Caso d'uso 3 – Fuori orario e durata

**a) Input** – `5B Riva ... 16:00 90`; `... 200`

**b) Output** – "Fuori dall'orario del museo"; "Durata non ammessa"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima la durata, poi l'orario, poi le sovrapposizioni.

### Caso d'uso 4 – Calendario

**a) Input** – `FINE`

**b) Output** – le visite nell'ordine di prenotazione

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampare ogni visita con data, ora, durata, classe e docente.
