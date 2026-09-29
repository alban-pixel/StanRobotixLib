#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/length.h>
#include <stan/StanElevator.h>

class SubElevator : public frc2::SubsystemBase {
 public:
  SubElevator();
  ~SubElevator() override;

  frc2::CommandPtr toGround();
  frc2::CommandPtr toMid();
  frc2::CommandPtr toHigh();
  frc2::CommandPtr holdCommand();

  units::length::meter_t getHeight() const;

 private:
  stan::StanElevator* mElevator;
};
