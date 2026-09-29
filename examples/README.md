# Exemples StanRobotixLib (FRC 6622)

Ce dossier contient des exemples de sous-systèmes simples, complets et réalistes au format standard `.hpp` / `.cpp`.
Chaque exemple montre comment encapsuler un mécanisme de robot avec les briques de **StanRobotixLib** en quelques lignes de code propres et directes.

---

## Index des Exemples

| Dossier | Fichiers | Mécanisme | Briques StanRobotixLib |
|---|---|---|---|
| **`01_roller_intake/`** | `SubIntake.hpp`<br>`SubIntake.cpp` | Intake / Rouleaux de convoyeur | `stan::StanRoller` |
| **`02_flywheel_shooter/`** | `SubShooter.hpp`<br>`SubShooter.cpp` | Lanceur à volant d'inertie (1 kHz) | `stan::StanFlywheel` |
| **`03_pivot_arm/`** | `SubPivotArm.hpp`<br>`SubPivotArm.cpp` | Bras articulé angulaire asservi | `stan::StanPivot` |
| **`04_elevator/`** | `SubElevator.hpp`<br>`SubElevator.cpp` | Ascenseur vertical linéaire (hauteur métrique) | `stan::StanElevator` |
| **`05_swerve_drive/`** | `SubDrivetrain.hpp`<br>`SubDrivetrain.cpp` | Châssis swerve 4 modules (MK4i) et X-lock | `stan::StanSwerveBuilder`<br>`stan::StanSwerveDrivetrain` |
| **`06_robot_container/`** | `RobotContainer.hpp`<br>`RobotContainer.cpp` | Orchestration robot & liaisons manette Xbox | `stan::StanXboxController`<br>Command-Based |

---

## Directives d'Intégration

- **Copier-Coller direct** : Vous pouvez copier directement n'importe quel sous-dossier dans le dossier `src/main/include/subsystems/` et `src/main/cpp/subsystems/` de votre robot.
- **Conventions respectées** : Zéro code inutile, préfixes `i` (entrées), `m` (membres privés sans underscore), `k` (constantes) et typage physique `<units>`.
