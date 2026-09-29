#include "SubPivotArm.hpp"

SubPivotArm::SubPivotArm() {
  stan::PivotConfig config{
      .kMinAngle = 0_deg,
      .kMaxAngle = 110_deg,
      .kTolerance = 1_deg,
      .kGearRatio = 50.0,
      .kP = 40.0,
      .kI = 0.0,
      .kD = 0.5,
      .kS = 0.0,
      .kG = 0.3,
      .kV = 0.0};

  mMotor = new stan::StanMotor{20, stan::MotorType::kTalonFX};
  mPivot = new stan::StanPivot{mMotor, config};
}

SubPivotArm::~SubPivotArm() {
  delete mPivot;
  delete mMotor;
}

frc2::CommandPtr SubPivotArm::toIntakePosition() {
  return mPivot->goToAngle(0_deg);
}

frc2::CommandPtr SubPivotArm::toScorePosition() {
  return mPivot->goToAngle(75_deg);
}

frc2::CommandPtr SubPivotArm::toStowPosition() {
  return mPivot->goToAngle(105_deg);
}

frc2::CommandPtr SubPivotArm::holdCommand() {
  return mPivot->holdAngle();
}

units::angle::degree_t SubPivotArm::getAngle() const {
  return mPivot->getAngle();
}
