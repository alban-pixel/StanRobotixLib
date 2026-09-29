#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angular_velocity.h>
#include <stan/StanFlywheel.h>

class SubShooter : public frc2::SubsystemBase {
 public:
  SubShooter();
  ~SubShooter() override;

  frc2::CommandPtr spinCommand(units::angular_velocity::turns_per_second_t iVelocity);
  frc2::CommandPtr stopCommand();
  bool isReady() const;

 private:
  stan::StanFlywheel* mFlywheel;
};
