# StanRobotixLib

Bibliothèque C++20 et Vendordep officielle pour l'équipe FRC **Stan Robotix 6622**.

---

## Vue d'Ensemble

StanRobotixLib simplifie et accélère le développement logiciel des robots de compétition en fournissant des abstractions matérielles directes, des sous-systèmes préconfigurés et des utilitaires de contrôle temps-réel, dans le respect strict des standards de programmation de l'équipe (`rules.md`).

### Modules Principaux

| Module | Fichiers | Description |
|---|---|---|
| **Matériel** | `StanMotor.h`, `KrakenSync.h` | Abstraction unifiée CTRE Phoenix 6 / REVLib, mode Brake et limite 40 A par défaut, synchronisation absolue 1-ligne sans licence Pro. |
| **Mécanismes** | `StanRoller.h`, `StanFlywheel.h`, `StanPivot.h`, `StanElevator.h` | Sous-systèmes prêts à l'emploi (admission, lanceur, bras angulaire, ascenseur) avec fabriques de `frc2::CommandPtr`. |
| **Châssis** | `StanSwerveBuilder.h`, `StanSwerveDrivetrain.h`, `StanCarDrive.h`, `SwervePresets.h` | Propulsion holonomique 4 modules (SDS MK4/MK4i, MAXSwerve) avec odométrie et X-pattern, plus support de châssis directionnel type voiture. |
| **Contrôle & PID** | `StanTunablePID.h`, `StanFeedforward.h` | Live-tuning dynamique via NetworkTables 4 et calculs feedforward (Simple, Arm cosine, Elevator static). |
| **Entrées Pilote** | `StanXboxController.h` | Manette Xbox avec deadband automatique (`0.1`), limitation de rampe et méthodes de liaison (`bindHold`, `bindToggle`, `bindPress`). |

---

## Documentation

La documentation complète est disponible dans le dossier [`docs/`](docs/) :

- [**Démarrage Rapide (`docs/QUICKSTART.md`)**](docs/QUICKSTART.md) : Installation de la vendordep, configuration Gradle et premier programme.
- [**Architecture (`docs/ARCHITECTURE.md`)**](docs/ARCHITECTURE.md) : Conception en couches, asservissement 1 kHz, gestion mémoire et modèle Command-Based.
- [**Mécanismes (`docs/SUBSYSTEMS.md`)**](docs/SUBSYSTEMS.md) : Guide d'utilisation et exemples de code pour chaque mécanisme et châssis.
- [**Référence API (`docs/API_REFERENCE.md`)**](docs/API_REFERENCE.md) : Spécification détaillée des classes, méthodes et structures.
- [**Guide de Migration (`docs/MIGRATION_GUIDE.md`)**](docs/MIGRATION_GUIDE.md) : Exemples avant/après pour convertir du code existant vers StanRobotixLib.

---

## Compilation et Tests

Pour exécuter les 237 tests unitaires C++20 sur machine de développement :
```bash
./gradlew test
```

Pour installer automatiquement la vendordep dans un projet robot :
```bash
./install_vendordep.sh /chemin/vers/votre/projet
```

Pour générer et publier l'archive d'en-têtes de la vendordep :
```bash
./gradlew headersZip publishToMavenLocal publish
```
