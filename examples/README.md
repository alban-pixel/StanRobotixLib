# Exemples StanRobotixLib (FRC 6622)

Ce dossier rassemble des exemples de code complets, autonomes et directement exploitables pour chaque module majeur de la bibliothèque **StanRobotixLib**.

---

## Index des Exemples

| # | Fichier | Description | Modules Illustrés |
|---|---|---|---|
| **01** | [`01_MotorAndSyncExample.h`](01_MotorAndSyncExample.h) | Contrôle direct de moteur et synchronisation absolue Kraken/Falcon avec CANcoder en 1 ligne. | `StanMotor`, `KrakenSync` |
| **02** | [`02_RollerAndShooterExample.h`](02_RollerAndShooterExample.h) | Système d'admission et lanceur à volant d'inertie avec composition de commande conditionnelle (`atDesiredVelocity`). | `StanRoller`, `StanFlywheel` |
| **03** | [`03_PivotArmExample.h`](03_PivotArmExample.h) | Bras articulé angulaire avec soft limits, synchronisation d'encodeur absolu et feedforward de gravité $\cos(\theta)$. | `StanPivot`, `StanFeedforward::Arm` |
| **04** | [`04_ElevatorExample.h`](04_ElevatorExample.h) | Ascenseur vertical linéaire avec soft limits, contrôle métrique et compensation statique de gravité. | `StanElevator`, `StanFeedforward::Elevator` |
| **05** | [`05_SwerveDrivetrainExample.h`](05_SwerveDrivetrainExample.h) | Châssis swerve 4 modules configuré avec `StanSwerveBuilder`, odométrie, vision et verrouillage en X. | `StanSwerveBuilder`, `StanSwerveDrivetrain`, `SwervePresets` |
| **06** | [`06_CarDriveExample.h`](06_CarDriveExample.h) | Châssis directionnel type voiture (2 roues directrices avant + traction arrière) tel qu'utilisé sur Mid-Robot. | `StanCarDrive` |
| **07** | [`07_TunablePIDExample.h`](07_TunablePIDExample.h) | Live-tuning dynamique des gains de régulation (PID + Feedforward) via NetworkTables 4 sans redéploiement. | `StanTunablePID` |
| **08** | [`08_FullRobotContainerExample.h`](08_FullRobotContainerExample.h) | Architecture complète d'un `RobotContainer` intégrant swerve, pivot, shooter, manettes Xbox et séquence autonome. | `StanXboxController`, composition Command-Based complète |

---

## Directives d'Utilisation

1. **Intégration dans un projet** : Ces exemples sont écrits sous forme de classes C++20 modulaires. Vous pouvez les importer ou adapter directement leurs méthodes dans vos sous-systèmes.
2. **Conformité aux règles de l'équipe** : Tous les exemples respectent strictement la matrice de nommage (`i` pour les paramètres, `m` pour les membres privés, `k` pour les constantes), le typage physique fort `<units>`, et le modèle sans wrapper.
