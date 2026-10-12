# Analisi – 070-problema-menu-mensa.c

## 1. Problema

Il menu settimanale della mensa ha cinque giorni con tre portate ciascuno. Il programma legge il limite di calorie fissato dal dietista e stampa le calorie di ogni giorno segnalando quelli oltre il limite, il giorno più calorico, la media e i piatti che compaiono in più giorni, ognuno una volta sola.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Piatto` | `nome, calorie` | portata |
| `Menu` | `giorno, portate[3]` | pranzo del giorno |
| `Settimana` | `numero, giorni[5]` | menu della settimana |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `menu` | `Settimana` | — | Cinque Menu da tre Piatto |
| `limite` | `int` | — | Limite letto |
| `massimo` | `const Menu *` | — | Giorno più calorico |
| `volte` | `int` | — | Ripetizioni di un piatto |

| Funzione | Compito |
|----------|---------|
| `calorie_menu(m)` | Somma delle tre portate |
| `piu_calorico(s)` | Puntatore al menu con più calorie |
| `conta_piatto(s, nome)` | Quante volte compare il piatto |
| `gia_visto(s, giorno, portata)` | 1 se il piatto compare in un giorno precedente |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Calorie

**a) Input** – `800`

**b) Output** – Mer 1000 kcal "OLTRE"; "Piu' calorico: Mer (1000 kcal); media 732 kcal"

**c) Variabili di supporto** – `totale`

**d) Vincoli** – —

**e) Assunzioni** – media intera

**f) Algoritmo in linguaggio naturale** – calorie_menu(&menu.giorni[g]) per ogni giorno.

### Caso d'uso 2 – Piatti ripetuti

**a) Input** – stesso input

**b) Output** – "Pasta al pomodoro: 2 volte", "Insalata: 3 volte"

**c) Variabili di supporto** – `volte`

**d) Vincoli** – ogni piatto stampato una volta

**e) Assunzioni** – nomi scritti allo stesso modo

**f) Algoritmo in linguaggio naturale** – per ogni piatto contare le presenze; stamparlo solo se compare più volte e non è già comparso in un giorno precedente.

### Caso d'uso 3 – Limite non valido

**a) Input** – `0`

**b) Output** – "Limite non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – limite positivo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun calcolo.
