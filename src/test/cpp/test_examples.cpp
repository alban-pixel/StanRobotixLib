#include <gtest/gtest.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>
#include "examples/01_MotorAndSyncExample.h"
#include "examples/02_RollerAndShooterExample.h"
#include "examples/03_PivotArmExample.h"
#include "examples/04_ElevatorExample.h"
#include "examples/05_SwerveDrivetrainExample.h"
#include "examples/06_CarDriveExample.h"
#include "examples/07_TunablePIDExample.h"
#include "examples/08_FullRobotContainerExample.h"

using namespace examples;

TEST(ExamplesVerificationTest, MotorAndSyncExampleWorks) {
  MotorAndSyncExample ex;
  ex.runOpenLoop(0.5);
  ex.runVoltage(6.0_V);
  ex.runClosedLoopVelocity(50_tps);
  ex.setSteerPosition(1.5_tr);
  ex.stop();
  SUCCEED();
}

TEST(ExamplesVerificationTest, RollerAndShooterExampleWorks) {
  RollerAndShooterExample ex;
  EXPECT_NE(ex.getFlywheel(), nullptr);
  EXPECT_NE(ex.getFeeder(), nullptr);
  auto cmd = ex.shootWhenReadyCommand(80_tps);
  EXPECT_TRUE(cmd.get() != nullptr);
}

TEST(ExamplesVerificationTest, PivotArmExampleWorks) {
  PivotArmExample ex;
  auto cmdIntake = ex.toIntakePosition();
  auto cmdScore = ex.toScorePosition();
  auto cmdHold = ex.holdPosition();
  EXPECT_TRUE(cmdIntake.get() != nullptr);
  EXPECT_TRUE(cmdScore.get() != nullptr);
  EXPECT_TRUE(cmdHold.get() != nullptr);
}

TEST(ExamplesVerificationTest, ElevatorExampleWorks) {
  ElevatorExample ex;
  auto cmdHome = ex.toHome();
  auto cmdMid = ex.toMidStage();
  auto cmdHold = ex.holdPosition();
  EXPECT_TRUE(cmdHome.get() != nullptr);
  EXPECT_TRUE(cmdMid.get() != nullptr);
  EXPECT_TRUE(cmdHold.get() != nullptr);
}

TEST(ExamplesVerificationTest, SwerveDrivetrainExampleWorks) {
  SwerveDrivetrainExample ex;
  EXPECT_NE(ex.getDrivetrain(), nullptr);
  ex.drive(1.0_mps, 0.5_mps, 1.0_rad_per_s, true);
  auto lockCmd = ex.lockWheelsCommand();
  EXPECT_TRUE(lockCmd.get() != nullptr);
}

TEST(ExamplesVerificationTest, CarDriveExampleWorks) {
  CarDriveExample ex;
  ex.drive(0.8, 0.0, 0.2, false);
  ex.setSteerAngle(30_deg);
  SUCCEED();
}

TEST(ExamplesVerificationTest, TunablePIDExampleWorks) {
  TunablePIDExample ex;
  EXPECT_NE(ex.getTunable(), nullptr);
  ex.Periodic();
  SUCCEED();
}

TEST(ExamplesVerificationTest, FullRobotContainerExampleWorks) {
  FullRobotContainerExample container;
  auto autoCmd = container.getAutonomousCommand();
  EXPECT_TRUE(autoCmd.get() != nullptr);
}
