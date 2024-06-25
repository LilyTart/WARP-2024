#include "Robot.h"

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  leftDriveMotor1.SetInverted(true);
  //leftDriveMotor2.SetInverted(true);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  driver = new frc::XboxController(0);
  codriver = new frc::XboxController(1);

  intakeMotor = new WPI_VictorSPX(5);

  // leftDriveMotor1 = VictorSPX{4};
  // leftDriveMotor2 = VictorSPX(1);
  // rightDriveMotor1 = VictorSPX(3);
  // rightDriveMotor2 = VictorSPX(2);
}

void Robot::RobotPeriodic() {}


void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();

  fmt::print("Auto selected: {}\n", m_autoSelected);

  autoTimer.Reset();
}

void Robot::AutonomousPeriodic() {

  if (m_autoSelected == "Red 1" or "Blue 3") {
    autoTimer.Start(); //start the timer
    if (autoTimer.Get() <= 0.5_s) {
      leftDriveMotor1.Set(ControlMode::PercentOutput, -0.2);
      //leftDriveMotor2.Set(ControlMode::PercentOutput, -0.2);
      rightDriveMotor1.Set(ControlMode::PercentOutput, -0.2);
      //rightDriveMotor2.Set(ControlMode::PercentOutput, -0.2);
    } else if (autoTimer.Get() < 1.5_s && autoTimer.Get() > 1.0_s) {
      leftDriveMotor1.Set(ControlMode::PercentOutput, 0.2);
      //leftDriveMotor2.Set(ControlMode::PercentOutput, 0.2);
      rightDriveMotor1.Set(ControlMode::PercentOutput, 0.2);
      //rightDriveMotor2.Set(ControlMode::PercentOutput, 0.2);
    } else {
      leftDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //leftDriveMotor2.Set(ControlMode::PercentOutput, 0);
      rightDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //rightDriveMotor2.Set(ControlMode::PercentOutput, 0);
      autoTimer.Stop();
      autoTimer.Reset();
    }
  } else if (m_autoSelected =="Red 2" or "Blue 2") {
    
    autoTimer.Start();
    if (autoTimer.Get() < 5_s) {
      leftDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //leftDriveMotor2.Set(ControlMode::PercentOutput, 0);
      rightDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //rightDriveMotor2.Set(ControlMode::PercentOutput, 0);
    } else {
      leftDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //leftDriveMotor2.Set(ControlMode::PercentOutput, 0);
      rightDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //rightDriveMotor2.Set(ControlMode::PercentOutput, 0);
      autoTimer.Stop();
      autoTimer.Reset();
    }
  } else if (m_autoSelected == "Red 3" or "Blue 1") {

    autoTimer.Start();
    if (autoTimer.Get() < 5_s) {

      leftDriveMotor1.Set(ControlMode::PercentOutput, -0.2);
      //leftDriveMotor2.Set(ControlMode::PercentOutput, -0.2);
      rightDriveMotor1.Set(ControlMode::PercentOutput, -0.2);
      //rightDriveMotor2.Set(ControlMode::PercentOutput, -0.2);
    } else {
      leftDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //leftDriveMotor2.Set(ControlMode::PercentOutput, 0);
      rightDriveMotor1.Set(ControlMode::PercentOutput, 0);
      //rightDriveMotor2.Set(ControlMode::PercentOutput, 0);
      autoTimer.Stop();
      autoTimer.Reset();
    }
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {

  if (driver->GetLeftY() / 3) {
    leftSpeed = driver->GetLeftY();
  } else {

    leftSpeed = 0;
  }

  if (driver->GetRightY() / 3) {
    rightSpeed = driver->GetRightY();
  } else {
    rightSpeed = 0;
  }

  leftDriveMotor1.Set(ControlMode::PercentOutput,leftSpeed * (-1));
  leftDriveMotor2.Set(ControlMode::PercentOutput,leftSpeed);
  rightDriveMotor1.Set(ControlMode::PercentOutput,rightSpeed);
  rightDriveMotor2.Set(ControlMode::PercentOutput,rightSpeed);

  if (driver->GetRightTriggerAxis() > deadzone) {
    intakeSpeed = driver->GetRightTriggerAxis();
  } else {
    intakeSpeed = 0;
  }

  if (driver->GetLeftTriggerAxis() > deadzone) {
    intakeSpeed = driver->GetLeftTriggerAxis() * -1;
  } else {
    intakeSpeed = 0;
  }

  intakeMotor->Set(ControlMode::PercentOutput, intakeSpeed);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNiNG_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif