#include "SubShooter.hpp"

SubShooter::SubShooter() {
  stan::FlywheelConfig config{
      .kMaxVelocity = 100_tps,
      .kTolerance = 2_tps,
      .kP = 0.1,
      .kI = 0.0,
      .kD = 0.0,
      .kS = 0.05,
      .kV = 0.12};

  mFlywheel = new stan::StanFlywheel{11, stan::MotorType::kTalonFX, config};
}

SubShooter::~SubShooter() {
  delete mFlywheel;
}

frc2::CommandPtr SubShooter::spinCommand(units::angular_velocity::turns_per_second_t iVelocity) {
  return mFlywheel->spinVelocity(iVelocity);
}

frc2::CommandPtr SubShooter::stopCommand() {
  return mFlywheel->stopCommand();
}

bool SubShooter::isReady() const {
  return mFlywheel->atDesiredVelocity();
}
