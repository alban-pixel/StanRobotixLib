#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/velocity.h>

#include "02_RollerAndShooterExample.h"
#include "03_PivotArmExample.h"
#include "05_SwerveDrivetrainExample.h"
#include "stan/StanXboxController.h"

namespace examples {

class FullRobotContainerExample {
 public:
  FullRobotContainerExample()
      : mDriverController{0, 0.1},
        mOperatorController{1, 0.1} {
    configureDefaultCommands();
    configureButtonBindings();
  }

  frc2::CommandPtr getAutonomousCommand() {
    return frc2::cmd::Sequence(
        mPivot.toIntakePosition(),
        mShooter.feedCommand(0.5).WithTimeout(1.0_s),
        mPivot.toScorePosition(),
        mShooter.shootWhenReadyCommand(90_tps).WithTimeout(2.5_s),
        mPivot.toStowPosition());
  }

 private:
  void configureDefaultCommands() {
    mDrivetrain.SetDefaultCommand(mDrivetrain.Run([this] {
      double vx = -mDriverController.getLeftYWithDeadband(true) * 4.5;
      double vy = -mDriverController.getLeftXWithDeadband(true) * 4.5;
      double omega = -mDriverController.getRightXWithDeadband(true) * 5.0;

      mDrivetrain.drive(
          units::velocity::meters_per_second_t{vx},
          units::velocity::meters_per_second_t{vy},
          units::angular_velocity::radians_per_second_t{omega},
          true);
    }));
  }

  void configureButtonBindings() {
    // Driver controls
    mDriverController.bindHold(mDriverController.X(), mDrivetrain.lockWheelsCommand());
    mDriverController.bindPress(mDriverController.Start(), mDrivetrain.RunOnce([this] {
      mDrivetrain.resetPose(frc::Pose2d{});
    }));

    // Operator controls
    mOperatorController.bindHold(mOperatorController.LeftBumper(), mShooter.feedCommand(0.8));
    mOperatorController.bindHold(mOperatorController.RightTrigger(), mShooter.shootWhenReadyCommand(95_tps));
    mOperatorController.bindPress(mOperatorController.A(), mPivot.toIntakePosition());
    mOperatorController.bindPress(mOperatorController.Y(), mPivot.toScorePosition());
    mOperatorController.bindPress(mOperatorController.B(), mPivot.toStowPosition());
  }

  stan::StanXboxController mDriverController;
  stan::StanXboxController mOperatorController;

  SwerveDrivetrainExample mDrivetrain;
  RollerAndShooterExample mShooter;
  PivotArmExample mPivot;
};

} // namespace examples
