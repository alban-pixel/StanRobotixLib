#pragma once

#include <frc2/command/SubsystemBase.h>
#include "stan/StanFlywheel.h"
#include "stan/StanTunablePID.h"

namespace examples {

class TunablePIDExample : public frc2::SubsystemBase {
 public:
  TunablePIDExample() {
    stan::FlywheelConfig flywheelConfig{
        .kMaxVelocity = 100_tps,
        .kTolerance = 2_tps,
        .kP = 0.1,
        .kI = 0.0,
        .kD = 0.0,
        .kS = 0.05,
        .kV = 0.12};

    mFlywheel = new stan::StanFlywheel{10, stan::MotorType::kTalonFX, flywheelConfig};
    mTunablePID = new stan::StanTunablePID{"ShooterTuning", stan::TunablePreset::kFlywheel};
  }

  ~TunablePIDExample() override {
    delete mFlywheel;
    delete mTunablePID;
  }

  void Periodic() override {
    if (mTunablePID->hasChanged()) {
      stan::PIDGains gains = mTunablePID->getGains();
      updateGains(gains);
    }
  }

  void updateGains(const stan::PIDGains& iGains) {
    if (auto* talon = mFlywheel->getMotor()->getTalonFX()) {
      ctre::phoenix6::configs::Slot0Configs slot0{};
      talon->GetConfigurator().Refresh(slot0);
      slot0.kP = iGains.kP;
      slot0.kI = iGains.kI;
      slot0.kD = iGains.kD;
      slot0.kS = iGains.kS;
      slot0.kV = iGains.kV;
      talon->GetConfigurator().Apply(slot0);
    }
  }

  stan::StanTunablePID* getTunable() {
    return mTunablePID;
  }

 private:
  stan::StanFlywheel* mFlywheel;
  stan::StanTunablePID* mTunablePID;
};

} // namespace examples
