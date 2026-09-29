#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <stan/StanRoller.h>

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();
  ~SubIntake() override;

  frc2::CommandPtr intakeCommand();
  frc2::CommandPtr ejectCommand();
  frc2::CommandPtr stopCommand();

 private:
  stan::StanRoller* mRoller;
};
