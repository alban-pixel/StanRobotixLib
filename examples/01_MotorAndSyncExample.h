#pragma once

#include <ctre/phoenix6/CANcoder.hpp>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/current.h>
#include <units/time.h>
#include <units/voltage.h>
#include "stan/KrakenSync.h"
#include "stan/StanMotor.h"

namespace examples {

class MotorAndSyncExample {
 public:
  MotorAndSyncExample() {
    mMotorDrive = new stan::StanMotor{1, stan::MotorType::kTalonFX, "rio"};
    mMotorSteer = new stan::StanMotor{2, stan::MotorType::kTalonFX, "rio"};
    mSteerEncoder = new ctre::phoenix6::hardware::CANcoder{3};

    mMotorDrive->setCurrentLimit(40_A);
    mMotorDrive->setIdleMode(stan::IdleMode::kBrake);

    syncSteerWithCANcoder();
  }

  ~MotorAndSyncExample() {
    delete mMotorDrive;
    delete mMotorSteer;
    delete mSteerEncoder;
  }

  void syncSteerWithCANcoder() {
    if (auto* talon = mMotorSteer->getTalonFX()) {
      stan::KrakenSync::sync(talon, mSteerEncoder, 250_ms);
    }
  }

  void runOpenLoop(double iSpeed) {
    mMotorDrive->set(iSpeed);
  }

  void runVoltage(units::voltage::volt_t iVoltage) {
    mMotorDrive->setVoltage(iVoltage);
  }

  void runClosedLoopVelocity(units::angular_velocity::turns_per_second_t iTargetVelocity) {
    mMotorDrive->setVelocity(iTargetVelocity);
  }

  void setSteerPosition(units::angle::turn_t iTargetTurn) {
    mMotorSteer->setPosition(iTargetTurn);
  }

  void stop() {
    mMotorDrive->stopMotor();
    mMotorSteer->stopMotor();
  }

 private:
  stan::StanMotor* mMotorDrive;
  stan::StanMotor* mMotorSteer;
  ctre::phoenix6::hardware::CANcoder* mSteerEncoder;
};

} // namespace examples
