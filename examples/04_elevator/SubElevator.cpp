#include "SubElevator.hpp"

SubElevator::SubElevator() {
  stan::ElevatorConfig config{
      .kMinHeight = 0.0_m,
      .kMaxHeight = 1.6_m,
      .kTolerance = 0.02_m,
      .kMetersPerRotation = 0.045,
      .kP = 35.0,
      .kI = 0.0,
      .kD = 0.3,
      .kG = 0.4,
      .kS = 0.1,
      .kV = 0.0};

  mElevator = new stan::StanElevator{30, stan::MotorType::kTalonFX, config};
}

SubElevator::~SubElevator() {
  delete mElevator;
}

frc2::CommandPtr SubElevator::toGround() {
  return mElevator->goToHeight(0.05_m);
}

frc2::CommandPtr SubElevator::toMid() {
  return mElevator->goToHeight(0.75_m);
}

frc2::CommandPtr SubElevator::toHigh() {
  return mElevator->goToHeight(1.5_m);
}

frc2::CommandPtr SubElevator::holdCommand() {
  return mElevator->holdHeight();
}

units::length::meter_t SubElevator::getHeight() const {
  return mElevator->getHeight();
}
