#pragma once

#include <cmath>
#include <units/acceleration.h>
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/math.h>
#include <units/velocity.h>
#include <units/voltage.h>

namespace stan {

enum class FeedforwardType {
  kSimple,
  kArm,
  kElevator
};

struct FeedforwardConfig {
  units::voltage::volt_t kS{0_V};
  units::voltage::volt_t kG{0_V};
  double kV{0.0};
  double kA{0.0};
  FeedforwardType kType{FeedforwardType::kSimple};
};

class StanFeedforward {
 public:
  constexpr StanFeedforward() = default;

  constexpr explicit StanFeedforward(const FeedforwardConfig& iConfig)
      : mConfig{iConfig} {}

  constexpr StanFeedforward(units::voltage::volt_t iKs, double iKv, double iKa = 0.0,
                            units::voltage::volt_t iKg = 0_V,
                            FeedforwardType iType = FeedforwardType::kSimple)
      : mConfig{.kS = iKs, .kG = iKg, .kV = iKv, .kA = iKa, .kType = iType} {}

  static StanFeedforward Simple(units::voltage::volt_t iKs, double iKv, double iKa = 0.0) {
    return StanFeedforward{iKs, iKv, iKa, 0_V, FeedforwardType::kSimple};
  }

  static StanFeedforward Arm(units::voltage::volt_t iKs, units::voltage::volt_t iKg, double iKv, double iKa = 0.0) {
    return StanFeedforward{iKs, iKv, iKa, iKg, FeedforwardType::kArm};
  }

  static StanFeedforward Elevator(units::voltage::volt_t iKs, units::voltage::volt_t iKg, double iKv, double iKa = 0.0) {
    return StanFeedforward{iKs, iKv, iKa, iKg, FeedforwardType::kElevator};
  }

  units::voltage::volt_t calculate(
      units::angular_velocity::turns_per_second_t iVelocity,
      units::angular_acceleration::turns_per_second_squared_t iAcceleration = 0_tr_per_s_sq) const {
    double sgn = (iVelocity.value() > 0.0) ? 1.0 : ((iVelocity.value() < 0.0) ? -1.0 : 0.0);
    double ff = (mConfig.kS.value() * sgn) + (mConfig.kV * iVelocity.value()) +
                (mConfig.kA * iAcceleration.value());
    if (mConfig.kType == FeedforwardType::kElevator) {
      ff += mConfig.kG.value();
    }
    return units::voltage::volt_t{ff};
  }

  units::voltage::volt_t calculate(
      units::velocity::meters_per_second_t iVelocity,
      units::acceleration::meters_per_second_squared_t iAcceleration = 0_mps_sq) const {
    double sgn = (iVelocity.value() > 0.0) ? 1.0 : ((iVelocity.value() < 0.0) ? -1.0 : 0.0);
    double ff = (mConfig.kS.value() * sgn) + (mConfig.kV * iVelocity.value()) +
                (mConfig.kA * iAcceleration.value());
    if (mConfig.kType == FeedforwardType::kElevator) {
      ff += mConfig.kG.value();
    }
    return units::voltage::volt_t{ff};
  }

  units::voltage::volt_t calculate(
      units::angle::degree_t iAngle,
      units::angular_velocity::turns_per_second_t iVelocity,
      units::angular_acceleration::turns_per_second_squared_t iAcceleration = 0_tr_per_s_sq) const {
    double sgn = (iVelocity.value() > 0.0) ? 1.0 : ((iVelocity.value() < 0.0) ? -1.0 : 0.0);
    double ff = (mConfig.kS.value() * sgn) + (mConfig.kV * iVelocity.value()) +
                (mConfig.kA * iAcceleration.value());
    if (mConfig.kType == FeedforwardType::kArm) {
      ff += mConfig.kG.value() * units::math::cos(iAngle).value();
    } else if (mConfig.kType == FeedforwardType::kElevator) {
      ff += mConfig.kG.value();
    }
    return units::voltage::volt_t{ff};
  }

  void setGains(units::voltage::volt_t iKs, double iKv, double iKa = 0.0,
                units::voltage::volt_t iKg = 0_V) {
    mConfig.kS = iKs;
    mConfig.kV = iKv;
    mConfig.kA = iKa;
    mConfig.kG = iKg;
  }

  void setType(FeedforwardType iType) {
    mConfig.kType = iType;
  }

  const FeedforwardConfig& getConfig() const {
    return mConfig;
  }

  FeedforwardType getType() const {
    return mConfig.kType;
  }

 private:
  FeedforwardConfig mConfig;
};

} // namespace stan
