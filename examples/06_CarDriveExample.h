#pragma once

#include <functional>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <units/current.h>
#include "stan/StanCarDrive.h"

namespace examples {

class CarDriveExample : public frc2::SubsystemBase {
 public:
  CarDriveExample() {
    stan::StanCarDriveConfig config{
        .kFLDriveId = 1,
        .kFRDriveId = 2,
        .kFLSteerId = 3,
        .kFRSteerId = 4,
        .kFLEncoderId = 5,
        .kFREncoderId = 6,
        .kCanBus = "rio",
        .kSteerGearRatio = 12.8,
        .kMaxSteerAngle = 60.0_deg,
        .kSpeedScale = 0.8,
        .kFLMagnetOffset = 0.15_tr,
        .kFRMagnetOffset = -0.22_tr,
        .kSteerP = 40.0,
        .kSteerD = 0.5,
        .kSupplyCurrentLimit = 40.0_A,
        .kStatorCurrentLimit = 60.0_A};

    mCarDrive = new stan::StanCarDrive{config};
  }

  ~CarDriveExample() override {
    delete mCarDrive;
  }

  void drive(double iThrottle, double iBrake, double iSteer, bool iReverse = false) {
    mCarDrive->drive(iThrottle, iBrake, iSteer, iReverse);
  }

  void setSteerAngle(units::angle::degree_t iAngle) {
    mCarDrive->setSteerAngle(iAngle);
  }

  frc2::CommandPtr getTeleopDriveCommand(
      std::function<double()> iThrottle,
      std::function<double()> iBrake,
      std::function<double()> iSteer,
      std::function<bool()> iReverse) {
    return mCarDrive->getDriveCommand(iThrottle, iBrake, iSteer, iReverse);
  }

  frc2::CommandPtr zeroSteeringCommand() {
    return mCarDrive->getZeroFLCommand();
  }

 private:
  stan::StanCarDrive* mCarDrive;
};

} // namespace examples
