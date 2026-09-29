#pragma once

#include <frc2/command/CommandPtr.h>
#include <stan/StanXboxController.h>
#include "../01_roller_intake/SubIntake.hpp"
#include "../02_flywheel_shooter/SubShooter.hpp"
#include "../03_pivot_arm/SubPivotArm.hpp"
#include "../05_swerve_drive/SubDrivetrain.hpp"

class RobotContainer {
 public:
  RobotContainer();

  frc2::CommandPtr getAutonomousCommand();

 private:
  void configureBindings();

  stan::StanXboxController mDriverController{0, 0.1};
  stan::StanXboxController mOperatorController{1, 0.1};

  SubDrivetrain mDrivetrain;
  SubIntake mIntake;
  SubShooter mShooter;
  SubPivotArm mPivot;
};
