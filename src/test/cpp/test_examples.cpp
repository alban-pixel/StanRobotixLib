#include <gtest/gtest.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>
#include "01_roller_intake/SubIntake.hpp"
#include "02_flywheel_shooter/SubShooter.hpp"
#include "03_pivot_arm/SubPivotArm.hpp"
#include "04_elevator/SubElevator.hpp"
#include "05_swerve_drive/SubDrivetrain.hpp"
#include "06_robot_container/RobotContainer.hpp"

TEST(SubsystemExamplesTest, SubIntakeCommandsWork) {
  SubIntake intake;
  auto cmdIn = intake.intakeCommand();
  auto cmdOut = intake.ejectCommand();
  auto cmdStop = intake.stopCommand();
  EXPECT_TRUE(cmdIn.get() != nullptr);
  EXPECT_TRUE(cmdOut.get() != nullptr);
  EXPECT_TRUE(cmdStop.get() != nullptr);
}

TEST(SubsystemExamplesTest, SubShooterCommandsWork) {
  SubShooter shooter;
  auto cmdSpin = shooter.spinCommand(90_tps);
  auto cmdStop = shooter.stopCommand();
  EXPECT_TRUE(cmdSpin.get() != nullptr);
  EXPECT_TRUE(cmdStop.get() != nullptr);
}

TEST(SubsystemExamplesTest, SubPivotArmCommandsWork) {
  SubPivotArm arm;
  auto cmdIntake = arm.toIntakePosition();
  auto cmdScore = arm.toScorePosition();
  auto cmdStow = arm.toStowPosition();
  auto cmdHold = arm.holdCommand();
  EXPECT_TRUE(cmdIntake.get() != nullptr);
  EXPECT_TRUE(cmdScore.get() != nullptr);
  EXPECT_TRUE(cmdStow.get() != nullptr);
  EXPECT_TRUE(cmdHold.get() != nullptr);
}

TEST(SubsystemExamplesTest, StanPivotResetAndZeroCommandsWork) {
  stan::PivotConfig config{};
  stan::StanMotor motor{25, stan::MotorType::kTalonFX};
  stan::StanPivot pivot{motor, config};
  pivot.resetPosition(10_deg);
  EXPECT_EQ(pivot.getTargetAngle(), 10_deg);
  pivot.zeroPosition();
  EXPECT_EQ(pivot.getTargetAngle(), 0_deg);
  auto cmdZero = pivot.zeroPositionCommand(45_deg);
  EXPECT_TRUE(cmdZero.get() != nullptr);
}

TEST(SubsystemExamplesTest, StanPivotWithStanMotorConstructors) {
  stan::StanMotor motor{26, stan::MotorType::kTalonFX};
  stan::PivotConfig config{.kStartingAngle = 15_deg};

  stan::StanPivot pivotPtr{&motor, config};
  EXPECT_EQ(pivotPtr.getTargetAngle(), 15_deg);

  stan::StanPivot pivotRef{motor, config};
  EXPECT_EQ(pivotRef.getTargetAngle(), 15_deg);
}

TEST(SubsystemExamplesTest, SubElevatorCommandsWork) {
  SubElevator elevator;
  auto cmdGround = elevator.toGround();
  auto cmdMid = elevator.toMid();
  auto cmdHigh = elevator.toHigh();
  auto cmdHold = elevator.holdCommand();
  EXPECT_TRUE(cmdGround.get() != nullptr);
  EXPECT_TRUE(cmdMid.get() != nullptr);
  EXPECT_TRUE(cmdHigh.get() != nullptr);
  EXPECT_TRUE(cmdHold.get() != nullptr);
}

TEST(SubsystemExamplesTest, SubDrivetrainCommandsWork) {
  SubDrivetrain drivetrain;
  drivetrain.drive(1.0_mps, 0.5_mps, 1.0_rad_per_s, true);
  auto cmdX = drivetrain.xFormationCommand();
  auto cmdZero = drivetrain.zeroHeadingCommand();
  EXPECT_TRUE(cmdX.get() != nullptr);
  EXPECT_TRUE(cmdZero.get() != nullptr);
}

TEST(SubsystemExamplesTest, RobotContainerOrchestrationWorks) {
  RobotContainer container;
  auto autoCmd = container.getAutonomousCommand();
  EXPECT_TRUE(autoCmd.get() != nullptr);
}
