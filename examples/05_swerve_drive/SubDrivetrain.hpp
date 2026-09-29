#pragma once

#include <frc/geometry/Pose2d.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <units/velocity.h>
#include <stan/StanSwerveDrivetrain.h>

class SubDrivetrain : public frc2::SubsystemBase {
 public:
  SubDrivetrain();
  ~SubDrivetrain() override;

  void drive(units::velocity::meters_per_second_t iVx,
             units::velocity::meters_per_second_t iVy,
             units::angular_velocity::radians_per_second_t iOmega,
             bool iFieldRelative = true);

  frc2::CommandPtr xFormationCommand();
  frc2::CommandPtr zeroHeadingCommand();

  frc::Pose2d getPose() const;

 private:
  stan::StanSwerveDrivetrain* mDrivetrain;
};
