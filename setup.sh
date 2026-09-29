#!/bin/bash
set -e

echo "=== StanRobotixLib — Installation Rapide (FRC 6622) ==="

# 1. Vérification du projet robot cible
if [ ! -f "build.gradle" ]; then
  echo "[!] Attention : aucun fichier build.gradle détecté dans le répertoire courant ($(pwd))."
  echo "    Assurez-vous d'exécuter cette commande à la racine de votre projet robot FRC."
fi

mkdir -p "vendordeps"

# 2. Téléchargement du fichier de vendordep JSON
JSON_URL="https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main/StanRobotixLib.json"
echo "-> Téléchargement de StanRobotixLib.json..."
curl -fsSL "$JSON_URL" -o "vendordeps/StanRobotixLib.json"
echo "   [✓] vendordeps/StanRobotixLib.json installé"

# 3. Installation dans le cache WPILib local pour support hors-ligne
CACHE_DIR="$HOME/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
mkdir -p "$CACHE_DIR"

RAW_BASE="https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
echo "-> Téléchargement des en-têtes C++ (support hors-ligne)..."
curl -fsSL "$RAW_BASE/StanRobotixLib-cpp-1.0.0-headers.zip" -o "$CACHE_DIR/StanRobotixLib-cpp-1.0.0-headers.zip"
curl -fsSL "$RAW_BASE/StanRobotixLib-cpp-1.0.0.pom" -o "$CACHE_DIR/StanRobotixLib-cpp-1.0.0.pom"
echo "   [✓] En-têtes C++ mis en cache dans $CACHE_DIR"

if [ -d "/Users/Shared/wpilib/2026/maven" ]; then
  SHARED_DIR="/Users/Shared/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
  mkdir -p "$SHARED_DIR"
  cp -f "$CACHE_DIR/StanRobotixLib-cpp-1.0.0-headers.zip" "$SHARED_DIR/"
  cp -f "$CACHE_DIR/StanRobotixLib-cpp-1.0.0.pom" "$SHARED_DIR/"
fi

echo ""
echo "=== StanRobotixLib a été installée avec succès ! ==="
echo "Vous pouvez maintenant compiler votre projet :"
echo "  ./gradlew test"
