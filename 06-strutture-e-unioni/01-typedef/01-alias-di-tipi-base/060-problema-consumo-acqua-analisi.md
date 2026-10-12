# Analisi – 060-problema-consumo-acqua.c

## 1. Problema

Una famiglia di 3 persone annota a fine mese la lettura del contatore dell'acqua, in metri cubi. Il consumo del mese è la differenza tra due letture consecutive. Il programma calcola il consumo in m³ e in litri, i litri per persona al giorno, il mese con il consumo più alto e i mesi oltre la soglia di 150 litri per persona al giorno.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `MetriCubi` | `typedef double MetriCubi;` | volume letto sul contatore |
| `Litri` | `typedef double Litri;` | volume in litri |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `letture` | `MetriCubi[]` | 7 | Lettura del 31 dicembre e di fine mese |
| `giorni` | `int[]` | 6 | Giorni di ogni mese |
| `del_mese` | `MetriCubi` | — | Consumo del mese |
| `al_giorno` | `Litri` | — | Litri per persona al giorno |
| `massimo`, `oltre` | `int` | — | Mese più alto e conteggio oltre soglia |

| Funzione | Compito |
|----------|---------|
| `consumo(prima, dopo)` | Differenza tra due letture |
| `in_litri(volume)` | Conversione da m³ a litri |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Consumo mensile

**a) Input** – letture nel programma

**b) Output** – una riga per mese: m³, litri, litri/persona/giorno

**c) Variabili di supporto** – `del_mese`, `al_giorno`

**d) Vincoli** – 1 m³ = 1000 litri; 3 persone

**e) Assunzioni** – le letture sono crescenti

**f) Algoritmo in linguaggio naturale** – consumo = letture[m+1] - letture[m]; litri per persona = consumo * 1000 / giorni / 3.

### Caso d'uso 2 – Riepilogo

**a) Input** – letture nel programma

**b) Output** – totale 68.4 m³; mese più alto giugno; 1 mese oltre soglia

**c) Variabili di supporto** – `massimo`, `oltre`

**d) Vincoli** – a parità vale il primo mese

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – tenere l'indice del mese con il consumo più alto e contare i mesi oltre soglia.
