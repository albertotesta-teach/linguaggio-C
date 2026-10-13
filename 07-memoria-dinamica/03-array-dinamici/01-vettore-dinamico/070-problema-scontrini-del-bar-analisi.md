# Analisi – 070-problema-scontrini-del-bar.c

## 1. Problema

Il bar della scuola registra le vendite della giornata, una riga `prodotto prezzo quantità` per scontrino, in un vettore dinamico di `Voce`. A fine giornata il programma costruisce un secondo vettore con una voce per prodotto (quantità sommate, incasso nel campo prezzo) usando le stesse funzioni, poi stampa il riepilogo, l'incasso totale e il prodotto più venduto.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Voce` | `prodotto[20], prezzo, quantita` | una vendita o un totale |
| `Elenco` | `dati (Voce *), n, capacita` | vettore dinamico di voci |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `vendite`, `riepilogo` | `Elenco *` | struct + blocco di n Voce (heap) | Scontrini e totali per prodotto |
| `v` | `Voce` | — | Vendita letta o voce nuova del riepilogo |
| `p` | `Voce *` | — | Voce del riepilogo da aggiornare, valida fino alla prossima aggiunta |
| `incasso` | `double` | — | Totale della giornata |
| `migliore` | `int` | — | Prodotto con più pezzi |

| Funzione | Compito |
|----------|---------|
| `elemento(e, i)` | Puntatore alla voce i dentro il vettore |
| `cerca(e, prodotto)` | Indice della voce del prodotto o -1 |
| `crea_elenco, aggiungi, lunghezza, distruggi_elenco` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Una mattina

**a) Input** – 9 vendite, poi `FINE`

**b) Output** – 8 vendite, 5 prodotti; cornetto 6 pz 7.20 euro; incasso 19.10 euro; più venduto cornetto

**c) Variabili di supporto** – `p`

**d) Vincoli** – prezzo > 0, quantità ≥ 1

**e) Assunzioni** – stesso prezzo per lo stesso prodotto

**f) Algoritmo in linguaggio naturale** – per ogni vendita: cerca nel riepilogo; se c'è si aggiorna tramite p, altrimenti si aggiunge.

### Caso d'uso 2 – Vendita non valida

**a) Input** – `succo 1.50 -1`

**b) Output** – "vendita non valida"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la riga si scarta.

### Caso d'uso 3 – Due elenchi da liberare

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – distruggi_elenco su vendite e riepilogo.
