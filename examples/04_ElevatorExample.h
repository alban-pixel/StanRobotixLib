#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/SubsystemBase.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include "stan/StanElevator.h"
#include "stan/StanFeedforward.h"

namespace examples {

class ElevatorExample : public frc2::SubsystemBase {
 public:
  ElevatorExample() {
    stan::ElevatorConfig config{
        .kMinHeight = 0.0_m,
        .kMaxHeight = 1.6_m,
        .kTolerance = 0.02_m,
        .kMetersPerRotation = 0.045,
        .kP = 35.0,
        .kI = 0.0,
        .kD = 0.3,
        .kG = 0.45,
        .kS = 0.1,
        .kV = 0.0};

    mElevator = new stan::StanElevator{25, stan::MotorType::kTalonFX, config};
    mFeedforward = stan::StanFeedforward::Elevator(0.1_V, 0.45_V, 0.08);
  }

  ~ElevatorExample() override {
    delete mElevator;
  }

  units::length::meter_t getCurrentHeight() const {
    return mElevator->getHeight();
  }

  bool isAtTarget() const {
    return mElevator->atTargetHeight();
  }

  units::voltage::volt_t calculateGravityCompensation(units::velocity::meters_per_second_t iVelocity = 0_mps) const {
    return mFeedforward.calculate(iVelocity);
  }

  frc2::CommandPtr toHome() {
    return mElevator->goToHeight(0.05_m);
  }

  frc2::CommandPtr toMidStage() {
    return mElevator->goToHeight(0.8_m);
  }

  frc2::CommandPtr toMaxStage() {
    return mElevator->goToHeight(1.5_m);
  }

  frc2::CommandPtr holdPosition() {
    return mElevator->holdHeight();
  }

 private:
  stan::StanElevator* mElevator;
  stan::StanFeedforward mFeedforward;
};

} // namespace examples
