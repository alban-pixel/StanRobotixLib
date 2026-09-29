#include "SubDrivetrain.hpp"
#include <stan/StanSwerveBuilder.h>

SubDrivetrain::SubDrivetrain() {
  mDrivetrain = stan::StanSwerveBuilder{}
                    .withDimensions(0.584_m, 0.584_m)
                    .withPreset(stan::SwervePreset::kSDSMK4i_L2)
                    .withMotorTypes(stan::MotorType::kTalonFX, stan::MotorType::kTalonFX)
                    .withPigeon2(13)
                    .withModuleFL(1, 2, 9, 0.12_tr)
                    .withModuleFR(3, 4, 10, -0.45_tr)
                    .withModuleBL(5, 6, 11, 0.33_tr)
                    .withModuleBR(7, 8, 12, -0.18_tr)
                    .build();
}

SubDrivetrain::~SubDrivetrain() {
  delete mDrivetrain;
}

void SubDrivetrain::drive(units::velocity::meters_per_second_t iVx,
                          units::velocity::meters_per_second_t iVy,
                          units::angular_velocity::radians_per_second_t iOmega,
                          bool iFieldRelative) {
  mDrivetrain->drive(iVx, iVy, iOmega, iFieldRelative);
}

frc2::CommandPtr SubDrivetrain::xFormationCommand() {
  return mDrivetrain->getXFormationCommand();
}

frc2::CommandPtr SubDrivetrain::zeroHeadingCommand() {
  return mDrivetrain->getZeroHeadingCommand();
}

frc::Pose2d SubDrivetrain::getPose() const {
  return mDrivetrain->getPose();
}
