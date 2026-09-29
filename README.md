# StanRobotixLib

Bibliothèque C++20 et Vendordep officielle pour l'équipe FRC **Stan Robotix 6622**.

---

## Installation Rapide en 1 Ligne

Pour installer et configurer automatiquement la vendordep dans n'importe quel projet robot FRC, lancez la commande suivante **à la racine de votre projet robot** :

### macOS / Linux (Terminal)
```bash
curl -sSL https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main/setup.sh | bash
```

### Windows (PowerShell)
```powershell
irm https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main/setup.ps1 | iex
```

Cette commande télécharge le fichier `StanRobotixLib.json` dans votre dossier `vendordeps/` et installe les en-têtes C++ dans le cache WPILib pour une utilisation immédiate, même hors-ligne.

---

## Méthodes d'Installation Alternatives

### Option A : Depuis le dépôt local
Si vous clonez ou modifiez directement `StanRobotixLib` sur votre machine :

- **macOS / Linux** :
  ```bash
  ./install_vendordep.sh /chemin/vers/votre/projet-robot
  ```
- **Windows** :
  ```cmd
  install_vendordep.bat C:\chemin\vers\votre\projet-robot
  ```

*(Si aucun chemin n'est spécifié, les scripts détectent automatiquement les projets frères comme `Mid-Robot`)*

### Option B : Via VS Code (WPILib Online Install)
1. Ouvrez votre projet robot dans **VS Code**.
2. `Ctrl+Shift+P` (ou `Cmd+Shift+P` sur macOS) -> **WPILib: Manage Vendor Libraries**.
3. Choisissez **Install new library (online)**.
4. Collez l'URL suivante :
   ```
   https://raw.githubusercontent.com/alban-pixel/StanRobotixLib/main/StanRobotixLib.json
   ```

---

## Vue d'Ensemble & Modules

**StanRobotixLib** est conçue pour éliminer le code répétitif tout en garantissant des performances maximales (asservissement onboard à 1 kHz) et une sécurité matérielle stricte :

| Module | Fichiers d'En-Tête | Description |
|---|---|---|
| **Matériel** | `<stan/StanMotor.h>`<br>`<stan/KrakenSync.h>` | Contrôleur unifié CTRE Phoenix 6 (Talon FX) et REVLib (SparkMax, SparkFlex). Mode Brake et limite 40 A par défaut. Synchronisation absolue 1-ligne Falcon/Kraken avec CANcoder. |
| **Mécanismes** | `<stan/StanRoller.h>`<br>`<stan/StanFlywheel.h>`<br>`<stan/StanPivot.h>`<br>`<stan/StanElevator.h>` | Sous-systèmes complets (rouleaux/intake, lanceur volant d'inertie, bras angulaire, ascenseur linéaire) avec régulation matérielle à 1 kHz et fabriques de `frc2::CommandPtr`. |
| **Feedforward** | `<stan/StanFeedforward.h>` | Calculs de feedforward fortement typés (`Simple`, `Arm` avec compensation $\cos(\theta)$, `Elevator` statique). |
| **Châssis** | `<stan/StanSwerveBuilder.h>`<br>`<stan/StanSwerveDrivetrain.h>`<br>`<stan/StanCarDrive.h>`<br>`<stan/SwervePresets.h>` | Propulsion holonomique 4 modules (SDS MK4/MK4i, MAXSwerve) avec odométrie, vision MegaTag2 et verrouillage défensif en X, plus support de châssis directionnel type voiture (Mid-Robot). |
| **Contrôle & PID** | `<stan/StanTunablePID.h>` | Live-tuning dynamique des gains (kP, kI, kD, kS, kV, kG) via NetworkTables 4 sans redéploiement du code. |
| **Entrées Pilote** | `<stan/StanXboxController.h>` | Manette Xbox avec deadband automatique (`0.1`), réponse au carré et liaisons ergonomiques (`bindHold`, `bindToggle`, `bindPress`). |

---

## Exemples de Code

### 1. Contrôleur Moteur & Synchronisation KrakenSync
```cpp
#include <stan/KrakenSync.h>
#include <stan/StanMotor.h>

// Initialisation d'un Talon FX (ou SparkMax) avec Brake et limite 40 A automatiques
stan::StanMotor motor{CANid::kDriveMotor, stan::MotorType::kTalonFX};
ctre::phoenix6::hardware::CANcoder encoder{CANid::kCanCoder};

// Synchronisation absolue 1-ligne au démarrage (250 ms timeout)
stan::KrakenSync::sync(motor.getTalonFX(), &encoder);

// Pilotage direct
motor.set(0.5);
motor.setVelocity(50_tps); // Régulation onboard 1 kHz
```

### 2. Bras / Pivot avec Feedforward
```cpp
#include <stan/StanFeedforward.h>
#include <stan/StanPivot.h>

stan::PivotConfig config{
    .kMinAngle = 0_deg,
    .kMaxAngle = 110_deg,
    .kTolerance = 1_deg,
    .kP = 40.0,
    .kG = 0.3};

stan::StanPivot pivot{CANid::kPivotMotor, stan::MotorType::kTalonFX, CANid::kPivotEncoder, config};

// Calcul direct de feedforward gravitationnel
auto ff = stan::StanFeedforward::Arm(0.1_V, 0.4_V, 0.05);
units::voltage::volt_t vOut = ff.calculate(45_deg, 2_tps);

// Commande de positionnement angulaire
frc2::CommandPtr moveCmd = pivot.goToAngle(45_deg);
```

### 3. Manette Xbox avec Deadband Intégré
```cpp
#include <stan/StanXboxController.h>

stan::StanXboxController driver{0, 0.1}; // Port 0, deadband 0.1

// Lecture directe filtrée avec deadband
double forward = driver.getLeftY();
double rotate = driver.getRightX();

// Liaisons de commandes en 1 ligne
driver.bindHold(driver.A(), roller.runRoller(0.8));
driver.bindPress(driver.B(), shooter.spinVelocity(80_tps));
```

---

## Tests Unitaires

StanRobotixLib comprend une suite exhaustive de **237 tests unitaires** vérifiant le filtrage des deadbands, les conversions d'unités, la cinématique, les réjections de vision MegaTag2 et les calculs de feedforward :

```bash
# macOS / Linux
./gradlew test

# Windows
gradlew.bat test
```

---

## Structure de la Documentation

Pour une exploration approfondie de la bibliothèque, consultez les guides du dossier [`docs/`](docs/) :

- [**Démarrage Rapide (`docs/QUICKSTART.md`)**](docs/QUICKSTART.md) : Premier programme et configuration du projet.
- [**Architecture (`docs/ARCHITECTURE.md`)**](docs/ARCHITECTURE.md) : Modèle de conception sans wrapper, boucles 1 kHz et gestion mémoire.
- [**Sous-Systèmes & Mécanismes (`docs/SUBSYSTEMS.md`)**](docs/SUBSYSTEMS.md) : Guide d'implémentation de chaque mécanisme et châssis.
- [**Référence API (`docs/API_REFERENCE.md`)**](docs/API_REFERENCE.md) : Spécification complète des classes et méthodes.
- [**Guide de Migration (`docs/MIGRATION_GUIDE.md`)**](docs/MIGRATION_GUIDE.md) : Exemples avant/après pour migrer du code FRC existant.
