#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "=== Installation de StanRobotixLib Vendordep (macOS / Linux) ==="

# 1. Compilation des headers et publication Maven Local
echo "-> Génération des headers et publication Maven..."
./gradlew headersZip publishToMavenLocal publish

# 2. Installation dans le cache WPILib Maven local
WPILIB_MAVEN_DIR="$HOME/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
mkdir -p "$WPILIB_MAVEN_DIR"
cp -f build/libs/StanRobotixLib-cpp-1.0.0-headers.zip "$WPILIB_MAVEN_DIR/"
cp -f build/publications/stanRobotixLib/pom-default.xml "$WPILIB_MAVEN_DIR/StanRobotixLib-cpp-1.0.0.pom"
echo "-> Installé dans $WPILIB_MAVEN_DIR"

if [ -d "/Users/Shared/wpilib/2026/maven" ]; then
  mkdir -p "/Users/Shared/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0"
  cp -f build/libs/StanRobotixLib-cpp-1.0.0-headers.zip "/Users/Shared/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0/"
  cp -f build/publications/stanRobotixLib/pom-default.xml "/Users/Shared/wpilib/2026/maven/com/stanrobotix/StanRobotixLib-cpp/1.0.0/StanRobotixLib-cpp-1.0.0.pom"
fi

# 3. Installation dans un projet robot cible
TARGET_PROJECT="$1"

if [ -z "$TARGET_PROJECT" ]; then
  if [ -d "$SCRIPT_DIR/../2026-StanRobotix-OffSeason/Mid-Robot" ]; then
    TARGET_PROJECT="$SCRIPT_DIR/../2026-StanRobotix-OffSeason/Mid-Robot"
  elif [ -d "$SCRIPT_DIR/../2026-StanRobotix-FRC" ]; then
    TARGET_PROJECT="$SCRIPT_DIR/../2026-StanRobotix-FRC"
  fi
fi

if [ -n "$TARGET_PROJECT" ] && [ -d "$TARGET_PROJECT" ]; then
  TARGET_PROJECT="$(cd "$TARGET_PROJECT" && pwd)"
  echo "-> Installation dans le projet robot : $TARGET_PROJECT"
  
  mkdir -p "$TARGET_PROJECT/vendordeps"
  cp -f "$SCRIPT_DIR/StanRobotixLib.json" "$TARGET_PROJECT/vendordeps/StanRobotixLib.json"
  echo "   [✓] StanRobotixLib.json copié dans $TARGET_PROJECT/vendordeps/"
  
  if [ -f "$TARGET_PROJECT/build.gradle" ]; then
    if ! grep -q "mavenLocal()" "$TARGET_PROJECT/build.gradle"; then
      echo "   [!] Note : Ajoutez mavenLocal() dans le bloc repositories {} de $TARGET_PROJECT/build.gradle si ce n'est pas déjà fait."
    else
      echo "   [✓] mavenLocal() détecté dans build.gradle"
    fi
  fi
else
  echo ""
  echo "Pour installer le fichier vendordep dans un projet robot spécifique :"
  echo "  ./install_vendordep.sh /chemin/vers/votre/projet"
fi

echo ""
echo "=== Vendordep StanRobotixLib installée avec succès ! ==="
