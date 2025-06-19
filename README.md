# 🛫 Gestion d'Aéroport - Projet C

Ce projet implémente un système de gestion de trafic aérien pour un aéroport avec une seule piste. Développé en C, il permet de gérer les avions, les compagnies aériennes et les opérations associées via une interface menu.

## ✨ Fonctionnalités

- **Gestion des avions**:
  - Création/suppression/modification d'avions
  - Validation des identifiants (3 lettres + 3 chiffres)
  - Contrôle des heures de décollage
- **Opérations sur liste chaînée**:
  - Insertion/suppression en tête/queue/position
  - Recherche et tri
- **Persistance des données**:
  - Sauvegarde/chargement depuis un fichier
- **Interface utilisateur**:
  - Menus interactifs avec validation des entrées
  - Affichage structuré des données

## 📁 Structure des fichiers

📁 projet-aeroport-gestion

├── 📁 src/ # Source Code

│ ├── 📄 main.c # Main program flow

│ ├── 📄 aeroport.h # Data structures declarations

│ ├── 📄 aeroport.c # Business logic implementation

│ └── 📄 rep.txt # Sample aircraft data

│

├── 📁 docs/ # Documentation

│ └── 📄 projet-avion-1.pdf# Project statement (PDF)

│

└── 📄 README.md # Project documentation

## 🛠️ Compilation et exécution

1. Compiler le projet:
  ```bash
  gcc src/main.c src/aeroport.c -o bin/aeroport
  ```
2. Exécuter:
  ```bash
  ./bin/aeroport
  ```
3. Utiliser le menu principal:
  Menu Général
  1 - Création du répertoire Avion
  2 - Mise à jour des Avions
  3 - Recherche, affichage et Tri
  4 - Enregistrement dans un fichier
  5 - Chargement d'un fichier
  6 - Quitter
