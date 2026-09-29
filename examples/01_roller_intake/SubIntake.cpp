#include "SubIntake.hpp"

SubIntake::SubIntake() {
  mRoller = new stan::StanRoller{10, stan::MotorType::kTalonFX};
}

SubIntake::~SubIntake() {
  delete mRoller;
}

frc2::CommandPtr SubIntake::intakeCommand() {
  return mRoller->runRoller(0.8);
}

frc2::CommandPtr SubIntake::ejectCommand() {
  return mRoller->runRoller(-0.6);
}

frc2::CommandPtr SubIntake::stopCommand() {
  return mRoller->stopCommand();
}
