#!/bin/bash
set -e

echo "=== StanRobotixLib — Installation Automatique (macOS / Linux FRC 6622) ==="

# 1. Chemins globaux WPILib
WPILIB_USER="$HOME/wpilib/2026"
MAVEN_USER="$WPILIB_USER/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
VENDOR_USER="$WPILIB_USER/vendordeps"

mkdir -p "$MAVEN_USER"
mkdir -p "$VENDOR_USER"

# 2. URLs distantes
RAW_REPO="https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main"
JSON_URL="$RAW_REPO/StanRobotixLib.json"
RAW_MAVEN="$RAW_REPO/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
ZIP_URL="$RAW_MAVEN/StanRobotixLib-cpp-1.0.0-headers.zip"
POM_URL="$RAW_MAVEN/StanRobotixLib-cpp-1.0.0.pom"

# 3. Téléchargement dans le cache global WPILib
echo "-> Téléchargement de StanRobotixLib.json..."
curl -fsSL "$JSON_URL" -o "$VENDOR_USER/StanRobotixLib.json"
echo "   [✓] StanRobotixLib.json installé dans $VENDOR_USER"

echo "-> Téléchargement des en-têtes C++ (support hors-ligne)..."
curl -fsSL "$ZIP_URL" -o "$MAVEN_USER/StanRobotixLib-cpp-1.0.0-headers.zip"
curl -fsSL "$POM_URL" -o "$MAVEN_USER/StanRobotixLib-cpp-1.0.0.pom"
echo "   [✓] En-têtes C++ mis en cache dans $MAVEN_USER"

if [ -d "/Users/Shared/wpilib/2026" ]; then
  mkdir -p "/Users/Shared/wpilib/2026/vendordeps"
  mkdir -p "/Users/Shared/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
  cp -f "$VENDOR_USER/StanRobotixLib.json" "/Users/Shared/wpilib/2026/vendordeps/"
  cp -f "$MAVEN_USER/StanRobotixLib-cpp-1.0.0-headers.zip" "/Users/Shared/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0/"
  cp -f "$MAVEN_USER/StanRobotixLib-cpp-1.0.0.pom" "/Users/Shared/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0/"
fi

# 4. Injection dans un projet robot cible si spécifié ou détecté
TARGET_DIR=""

if [ -n "$1" ]; then
  TARGET_DIR="$1"
elif [ -f "build.gradle" ]; then
  TARGET_DIR="$(pwd)"
fi

if [ -n "$TARGET_DIR" ] && [ -d "$TARGET_DIR" ]; then
  echo "-> Injection de la vendordep dans le projet : $TARGET_DIR"
  mkdir -p "$TARGET_DIR/vendordeps"
  cp -f "$VENDOR_USER/StanRobotixLib.json" "$TARGET_DIR/vendordeps/StanRobotixLib.json"
  echo "   [✓] vendordeps/StanRobotixLib.json injecté dans le projet."
else
  echo ""
  echo "[*] Exécuté en dehors d'un projet robot spécifique."
  echo "    La vendordep est désormais disponible partout sur cet ordinateur !"
  echo "    Dans VS Code : WPILib -> Manage Vendor Libraries -> Install new library (offline) -> StanRobotixLib."
fi

echo ""
echo "=== StanRobotixLib est prête à l'emploi sur cette machine ! ==="
