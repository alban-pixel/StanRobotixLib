#pragma once

#include <memory>
#include <frc/geometry/Pose2d.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include "stan/StanSwerveBuilder.h"
#include "stan/StanSwerveDrivetrain.h"

namespace examples {

class SwerveDrivetrainExample : public frc2::SubsystemBase {
 public:
  SwerveDrivetrainExample() {
    mDrivetrain = stan::StanSwerveBuilder{}
                      .withDimensions(0.584_m, 0.584_m)
                      .withPreset(stan::SwervePreset::kSDSMK4i_L2)
                      .withMotorTypes(stan::MotorType::kTalonFX, stan::MotorType::kTalonFX)
                      .withCanBus("rio")
                      .withPigeon2(13)
                      .withModuleFL(1, 2, 9, 0.12_tr)
                      .withModuleFR(3, 4, 10, -0.45_tr)
                      .withModuleBL(5, 6, 11, 0.33_tr)
                      .withModuleBR(7, 8, 12, -0.18_tr)
                      .build();
  }

  ~SwerveDrivetrainExample() override {
    delete mDrivetrain;
  }

  void drive(units::velocity::meters_per_second_t iVx,
             units::velocity::meters_per_second_t iVy,
             units::angular_velocity::radians_per_second_t iOmega,
             bool iFieldRelative = true) {
    if (mDrivetrain) {
      mDrivetrain->drive(iVx, iVy, iOmega, iFieldRelative);
    }
  }

  frc::Pose2d getPose() const {
    if (mDrivetrain) {
      return mDrivetrain->getPose();
    }
    return frc::Pose2d{};
  }

  void resetPose(const frc::Pose2d& iPose) {
    if (mDrivetrain) {
      mDrivetrain->resetPose(iPose);
    }
  }

  void addVisionMeasurement(const frc::Pose2d& iVisionPose, units::time::second_t iTimestamp) {
    if (mDrivetrain) {
      mDrivetrain->addVisionMeasurement(iVisionPose, iTimestamp);
    }
  }

  frc2::CommandPtr lockWheelsCommand() {
    if (mDrivetrain) {
      return mDrivetrain->getXFormationCommand();
    }
    return frc2::cmd::None();
  }

  stan::StanSwerveDrivetrain* getDrivetrain() {
    return mDrivetrain;
  }

 private:
  stan::StanSwerveDrivetrain* mDrivetrain;
};

} // namespace examples
