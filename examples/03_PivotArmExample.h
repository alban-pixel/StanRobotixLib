#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/voltage.h>
#include "stan/StanFeedforward.h"
#include "stan/StanPivot.h"

namespace examples {

class PivotArmExample : public frc2::SubsystemBase {
 public:
  PivotArmExample() {
    stan::PivotConfig config{
        .kMinAngle = 0_deg,
        .kMaxAngle = 115_deg,
        .kTolerance = 1.0_deg,
        .kGearRatio = 64.0,
        .kP = 40.0,
        .kI = 0.0,
        .kD = 0.5,
        .kS = 0.1,
        .kG = 0.35,
        .kV = 0.0};

    mPivot = new stan::StanPivot{20, stan::MotorType::kTalonFX, 21, config};
    mFeedforward = stan::StanFeedforward::Arm(0.1_V, 0.35_V, 0.05);
  }

  ~PivotArmExample() override {
    delete mPivot;
  }

  units::angle::degree_t getCurrentAngle() const {
    return mPivot->getAngle();
  }

  bool isAtTarget() const {
    return mPivot->atTargetAngle();
  }

  units::voltage::volt_t calculateGravityCompensation(units::angular_velocity::turns_per_second_t iVelocity = 0_tps) const {
    return mFeedforward.calculate(mPivot->getAngle(), iVelocity);
  }

  frc2::CommandPtr toIntakePosition() {
    return mPivot->goToAngle(5_deg);
  }

  frc2::CommandPtr toScorePosition() {
    return mPivot->goToAngle(75_deg);
  }

  frc2::CommandPtr toStowPosition() {
    return mPivot->goToAngle(110_deg);
  }

  frc2::CommandPtr holdPosition() {
    return mPivot->holdAngle();
  }

  frc2::CommandPtr resyncEncoder() {
    return mPivot->syncEncoderCommand();
  }

 private:
  stan::StanPivot* mPivot;
  stan::StanFeedforward mFeedforward;
};

} // namespace examples
