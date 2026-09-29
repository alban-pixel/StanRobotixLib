#include <gtest/gtest.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/voltage.h>
#include "stan/StanFeedforward.h"

using namespace stan;

TEST(FeedforwardTest, SimpleMotorForwardAndReverse) {
  auto ff = StanFeedforward::Simple(0.2_V, 0.1, 0.01);

  auto vPositive = ff.calculate(10_tps);
  EXPECT_NEAR(vPositive.value(), 0.2 + 0.1 * 10.0, 1e-6);

  auto vNegative = ff.calculate(-10_tps);
  EXPECT_NEAR(vNegative.value(), -0.2 - 0.1 * 10.0, 1e-6);

  auto vZero = ff.calculate(0_tps);
  EXPECT_NEAR(vZero.value(), 0.0, 1e-6);
}

TEST(FeedforwardTest, SimpleMotorAcceleration) {
  auto ff = StanFeedforward::Simple(0.1_V, 0.05, 0.02);

  auto vAcc = ff.calculate(5_tps, 10_tr_per_s_sq);
  EXPECT_NEAR(vAcc.value(), 0.1 + 0.05 * 5.0 + 0.02 * 10.0, 1e-6);
}

TEST(FeedforwardTest, ArmCosineGravityTerm) {
  auto ff = StanFeedforward::Arm(0.1_V, 0.5_V, 0.05);

  // Horizontal (0 deg) -> cos(0) = 1.0 -> full gravity compensation
  auto vHorizontal = ff.calculate(0_deg, 0_tps);
  EXPECT_NEAR(vHorizontal.value(), 0.5, 1e-6);

  // Vertical (90 deg) -> cos(90) = 0.0 -> 0 gravity compensation
  auto vVertical = ff.calculate(90_deg, 0_tps);
  EXPECT_NEAR(vVertical.value(), 0.0, 1e-4);

  // Inverted horizontal (180 deg) -> cos(180) = -1.0
  auto vInverted = ff.calculate(180_deg, 0_tps);
  EXPECT_NEAR(vInverted.value(), -0.5, 1e-4);
}

TEST(FeedforwardTest, ElevatorConstantGravityTerm) {
  auto ff = StanFeedforward::Elevator(0.15_V, 0.4_V, 0.08);

  // Zero velocity -> only constant gravity compensation
  auto vZero = ff.calculate(0_tps);
  EXPECT_NEAR(vZero.value(), 0.4, 1e-6);

  // Upward velocity -> kS + kV*v + kG
  auto vUp = ff.calculate(2_tps);
  EXPECT_NEAR(vUp.value(), 0.15 + 0.08 * 2.0 + 0.4, 1e-6);

  // Downward velocity -> -kS + kV*v + kG
  auto vDown = ff.calculate(-2_tps);
  EXPECT_NEAR(vDown.value(), -0.15 - 0.08 * 2.0 + 0.4, 1e-6);
}

TEST(FeedforwardTest, DynamicGainUpdates) {
  StanFeedforward ff;
  ff.setGains(0.1_V, 0.2, 0.0, 0.0_V);
  auto vOut = ff.calculate(5_tps);
  EXPECT_NEAR(vOut.value(), 0.1 + 0.2 * 5.0, 1e-6);

  ff.setGains(0.3_V, 0.4, 0.05, 0.0_V);
  auto vUpdated = ff.calculate(5_tps, 2_tr_per_s_sq);
  EXPECT_NEAR(vUpdated.value(), 0.3 + 0.4 * 5.0 + 0.05 * 2.0, 1e-6);
}
