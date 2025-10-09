<h1 align="center">🌀 MySH — Un mini shell en C</h1>

<p align="center">
  <img src="https://img.shields.io/github/actions/workflow/status/Nicolassmn/My-shell/build.yml?branch=main&label=Build&logo=github&color=blue" alt="build status" />
  <img src="https://img.shields.io/github/license/Nicolassmn/My-shell?color=yellow" alt="license" />
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="C Language" />
</p>

---

## 🧠 Présentation

**MySH** est un mini interpréteur de commandes inspiré de `bash`, développé en **C**. Il permet d’exécuter des commandes Unix, de gérer les processus, les redirections, les pipes et les opérateurs logiques (`&&`, `||`, `&`).  
C’est un projet réalisé dans le cadre de ma formation, dans le but de comprendre le fonctionnement interne d’un shell Unix.

---

### 🎬 Démo du shell

<p align="center">
  <img src="assets/demo.gif" alt="Démonstration de MySH" width="600">
</p>

---

## ⚙️ Fonctionnalités principales

- ✅ Exécution des commandes système (`ls`, `cat`, `grep`, etc.)
- ✅ Gestion des commandes **builtin** (`cd`, `exit`, `env`, …)  
- ✅ Support des **pipes** (`|`) et des **redirections** (`>`, `>>`, `<`)  
- ✅ Support des opérateurs **logiques** (`&&`, `||`)  
- ✅ Exécution en **arrière-plan** (`&`)  
- ✅ Gestion de l’environnement (`PWD`, `OLDPWD`, etc.)  
- ✅ Gestion des **signaux** (`Ctrl+C`, `SIGSEGV`, etc.)  
- ✅ Interface interactive (design affiché si tty)  

---

## 🛠️ Compilation & Exécution

<p align="center">

| Étape | Commande | Description |
|-------|----------|-------------|
| 🔹 Compiler le projet | <code>make</code> | Compile tous les fichiers source et génère l’exécutable `mysh` |
| 🧹 Nettoyer les fichiers objets | <code>make clean</code> | Supprime les fichiers temporaires (`*.o`, `*~`) |
| ❌ Supprimer tout | <code>make fclean</code> | Supprime les fichiers objets et l’exécutable |
| 🔄 Recompiler | <code>make re</code> | Nettoie puis compile à nouveau le projet |
| ▶️ Exécuter le shell | <code>./mysh</code> | Lance ton mini shell interactif |

</p>

## Structure du projet:
.
├── include
└── src
    ├── gestion_cmd
    ├── gestion_env
    ├── gestion_separators
    └── str_function

---

## ⬇️ Téléchargement (version compilée)

<p align="center">
🔹 **Dernière version prête à l’emploi** :<br>
[👉 Télécharger mysh (release latest)](https://github.com/Nicolassmn/My-shell/releases/download/latest/mysh)<br>
*(exécutable déjà compilé, prêt à être lancé !)*
</p>

<p align="center">
Ou cloner le projet depuis GitHub :<br>
<code>git clone git@github.com:Nicolassmn/My-shell.git</code>
</p>

---

## 🧪 Workflow CI/CD

Chaque push sur la branche `main` :

<p align="center">
- 🔨 Compile automatiquement le projet <br>
- 🚀 Publie le binaire dans la release “latest” <br>
*(voir <code>.github/workflows/build.yml</code>)*
</p>