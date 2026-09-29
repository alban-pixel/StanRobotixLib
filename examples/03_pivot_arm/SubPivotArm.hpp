#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <stan/StanPivot.h>

class SubPivotArm : public frc2::SubsystemBase {
 public:
  SubPivotArm();
  ~SubPivotArm() override;

  frc2::CommandPtr toIntakePosition();
  frc2::CommandPtr toScorePosition();
  frc2::CommandPtr toStowPosition();
  frc2::CommandPtr holdCommand();

  units::angle::degree_t getAngle() const;

 private:
  stan::StanPivot* mPivot;
};
