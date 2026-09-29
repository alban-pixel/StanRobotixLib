#include "RobotContainer.hpp"
#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
  configureBindings();
}

void RobotContainer::configureBindings() {
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

  mDriverController.bindHold(mDriverController.X(), mDrivetrain.xFormationCommand());
  mDriverController.bindPress(mDriverController.Start(), mDrivetrain.zeroHeadingCommand());

  mOperatorController.bindHold(mOperatorController.LeftBumper(), mIntake.intakeCommand());
  mOperatorController.bindHold(mOperatorController.RightTrigger(), mShooter.spinCommand(90_tps));
  mOperatorController.bindPress(mOperatorController.A(), mPivot.toIntakePosition());
  mOperatorController.bindPress(mOperatorController.Y(), mPivot.toScorePosition());
}

frc2::CommandPtr RobotContainer::getAutonomousCommand() {
  return frc2::cmd::Sequence(
      mPivot.toIntakePosition(),
      mIntake.intakeCommand().WithTimeout(1.0_s),
      mPivot.toScorePosition(),
      mShooter.spinCommand(90_tps).WithTimeout(2.0_s));
}
