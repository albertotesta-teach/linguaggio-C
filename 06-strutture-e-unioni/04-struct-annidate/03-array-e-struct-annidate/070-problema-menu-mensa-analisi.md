# Analisi – 070-problema-menu-mensa.c

## 1. Problema

Il menu settimanale della mensa ha cinque giorni con tre portate
ciascuno. Il programma legge il limite di calorie fissato dal dietista e
stampa le calorie di ogni giorno segnalando quelli oltre il limite, il
giorno più calorico, la media e i piatti che compaiono in più giorni,
ognuno una volta sola. La `Settimana` contiene un array di `Menu`, che
contiene un array di `Piatto`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `limite` | `int` | Calorie massime per un pranzo, positivo |
| `menu` | `Settimana` | Settimana 12 (nel sorgente), tre portate al giorno con le calorie |

### Output

- `Settimana N` e una riga per giorno con le tre portate, le calorie e
  `OLTRE` se superano il limite.
- `Piu' calorico: G (C kcal); media M kcal` (media intera).
- `Piatti ripetuti:` con i piatti presenti più volte e quante volte.
- `Limite non valido.`

### Vincoli

- Oltre il limite: calorie strettamente maggiori.
- A parità di calorie il giorno più calorico è il primo.
- Un piatto ripetuto si stampa solo alla sua prima comparsa (`gia_visto`
  controlla i giorni precedenti).
- I nomi dei piatti si confrontano con `strcmp`.

### Assunzioni

- Un piatto non compare due volte nello stesso giorno.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Piatto` | `typedef struct { char nome[20]; int calorie; } Piatto;` | Una portata |
| `Menu` | `typedef struct { char giorno[4]; Piatto portate[3]; } Menu;` | Il menu di un giorno |
| `Settimana` | `typedef struct { int numero; Menu giorni[5]; } Settimana;` | Il menu della settimana |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `massimo` | `const Menu *` | Giorno più calorico |
| `calorie`, `totale` | `int` | Calorie del giorno e della settimana |
| `volte` | `int` | Comparse di un piatto |

| Funzione | Compito |
|----------|---------|
| `calorie_menu(m)` | Somma delle calorie delle portate |
| `piu_calorico(s)` | Puntatore al menu più calorico |
| `conta_piatto(s, nome)` | Quante volte il piatto compare |
| `gia_visto(s, giorno, portata)` | 1 se il piatto compare in un giorno precedente |

### Algoritmo in linguaggio naturale

1. Leggere il limite; se non valido segnalarlo.
2. Per ogni giorno calcolare e stampare le calorie con l'eventuale
   `OLTRE`, sommandole al totale.
3. Stampare il giorno più calorico e la media.
4. Per ogni portata di ogni giorno: se il piatto compare più di una volta
   e non è già stato visto in un giorno precedente, stamparlo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Limite alto

- **Input:** `1000`
- **Valori intermedi attesi:** totale 3660 kcal, media 732.
- **Output atteso:**
  ```
  Limite di calorie per il pranzo: 
  Settimana 12
    Lun  Pasta al pomodoro  Petto di pollo    Insalata          640 kcal
    Mar  Risotto            Frittata          Carote            720 kcal
    Mer  Lasagne            Arrosto           Patate al forno  1000 kcal
    Gio  Pasta al pomodoro  Merluzzo          Insalata          600 kcal
    Ven  Minestrone         Pizza margherita  Insalata          700 kcal
  Piu' calorico: Mer (1000 kcal); media 732 kcal
  Piatti ripetuti:
    Pasta al pomodoro: 2 volte
    Insalata: 3 volte
  ```
  (con il limite uguale alle calorie di mercoledì, nessun `OLTRE`).

### Test 2 – Limite più basso

- **Input:** `700`
- **Output atteso:** `OLTRE` su martedì (720) e mercoledì (1000), non su
  venerdì (700).

### Test 3 – Limite non valido

- **Input:** `0`
- **Output atteso:** `Limite non valido.`
