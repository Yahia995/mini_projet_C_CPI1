# 🛫 Gestion de Trafic Aéroportuaire — Projet C

![C Language](https://img.shields.io/badge/language-C-blue)
![Status](https://img.shields.io/badge/status-stable-green)
![Platform](https://img.shields.io/badge/platform-linux%20%7C%20windows%20%7C%20macos-lightgrey)

Ce projet implémente un **système robuste de gestion de trafic aérien** pour un **aéroport à piste unique**. Il permet de piloter l'ensemble des opérations aéroportuaires — de la gestion des compagnies à la planification des décollages — en s'appuyant sur des **structures de données dynamiques en langage C**.

---

## 🚀 Fonctionnalités clés

### ✈️ Gestion des vols & avions

* **Identifiants stricts** : validation automatique du format (ex. `AFR123` — 3 lettres + 3 chiffres).
* **Planification** : contrôle rigoureux des horaires de décollage.
* **Cycle de vie complet** : création, modification et suppression des fiches avions.

### 🧠 Logique de données

* **Listes chaînées** : manipulation dynamique (insertion et suppression en tête, en queue ou à une position spécifique).
* **Algorithmes** : fonctions de recherche optimisées et algorithmes de tri.

### 💾 Persistance & interface

* **Sauvegarde** : exportation et importation via fichiers texte (`.txt`).
* **Menu interactif** : interface console ergonomique avec gestion robuste des erreurs de saisie.

---

## 📂 Organisation du projet

```text
.
├── src/                  # Code source
│   ├── main.c            # Point d'entrée et menu principal
│   ├── aeroport.h        # Structures de données et prototypes
│   └── aeroport.c        # Implémentation de la logique métier
├── data/                 # Stockage des données
│   └── rep.txt           # Base de données des avions (exemple)
├── docs/                 # Documentation technique
│   └── projet-avion-1.pdf# Énoncé détaillé
└── README.md
```

---

## 🛠️ Installation et utilisation

### Prérequis

* Un compilateur C (**GCC recommandé**).
* Un environnement compatible **POSIX** (Linux, macOS) ou **MinGW** pour Windows.

### 1️⃣ Compilation

```bash
gcc src/main.c src/aeroport.c -o aeroport_manager
```

### 2️⃣ Exécution

```bash
./aeroport_manager
```

---

## 🖥️ Aperçu du menu principal

L'application est pilotée par un **menu interactif** structuré comme suit :

1️⃣ **Répertoire** — Initialisation de la base de données
2️⃣ **Mise à jour** — Ajouter, modifier ou retirer un avion
3️⃣ **Consultation** — Recherche multicritère, affichage et tri des vols
4️⃣ **Export** — Sauvegarder l'état actuel dans un fichier externe
5️⃣ **Import** — Charger les données depuis un fichier existant
0️⃣ **Quitter** — Fermeture sécurisée de l'application

---

## 📝 Format des données

Le fichier de sauvegarde utilise une structure simple pour une lecture et un traitement faciles :

```text
ID_AVION | COMPAGNIE | DESTINATION | HEURE_DECOLLAGE
```

---

## 🎓 Contexte académique

Projet développé dans le cadre du **module de Programmation en Langage C**.

---

✨ *Ce projet met l'accent sur la rigueur algorithmique, la gestion mémoire et la structuration modulaire du code en C.*
