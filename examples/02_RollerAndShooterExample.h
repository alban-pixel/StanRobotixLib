#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/button/Trigger.h>
#include <units/angular_velocity.h>
#include <units/voltage.h>
#include "stan/StanFlywheel.h"
#include "stan/StanRoller.h"

namespace examples {

class RollerAndShooterExample : public frc2::SubsystemBase {
 public:
  RollerAndShooterExample() {
    stan::FlywheelConfig flywheelConfig{
        .kMaxVelocity = 100_tps,
        .kTolerance = 2_tps,
        .kP = 0.1,
        .kI = 0.0,
        .kD = 0.0,
        .kS = 0.05,
        .kV = 0.12};

    mFlywheel = new stan::StanFlywheel{10, stan::MotorType::kTalonFX, flywheelConfig};
    mFeederRoller = new stan::StanRoller{11, stan::MotorType::kTalonFX};
  }

  ~RollerAndShooterExample() override {
    delete mFlywheel;
    delete mFeederRoller;
  }

  stan::StanFlywheel* getFlywheel() {
    return mFlywheel;
  }

  stan::StanRoller* getFeeder() {
    return mFeederRoller;
  }

  frc2::CommandPtr spinUpCommand(units::angular_velocity::turns_per_second_t iTargetVelocity) {
    return mFlywheel->spinVelocity(iTargetVelocity);
  }

  frc2::CommandPtr feedCommand(double iSpeed = 0.8) {
    return mFeederRoller->runRoller(iSpeed);
  }

  frc2::CommandPtr shootWhenReadyCommand(units::angular_velocity::turns_per_second_t iTargetVelocity) {
    return mFlywheel->spinVelocity(iTargetVelocity)
        .AlongWith(frc2::cmd::WaitUntil([this] { return mFlywheel->atDesiredVelocity(); })
                       .AndThen(mFeederRoller->runRoller(1.0)));
  }

  frc2::CommandPtr stopAllCommand() {
    return mFlywheel->stopCommand().AlongWith(mFeederRoller->stopCommand());
  }

 private:
  stan::StanFlywheel* mFlywheel;
  stan::StanRoller* mFeederRoller;
};

} // namespace examples
