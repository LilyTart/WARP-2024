#pragma once

#include <string>
#include <iostream>
#include <fmt/core.h>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/XboxController.h>
#include <rev/CANSparkMax.h>
// #include <ctre
#include <ctre/phoenix.h>
#include <frc/Timer.h>
// #include <ctre/phoenix/motorcontrol/WPI_VictorSPX.h>

class Robot : public frc::TimedRobot {
  public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void TestInit() override;
    void TestPeriodic() override;

  private:
    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;

    WPI_VictorSPX *intakeMotor;

    // VictorSPX *leftDriveMotor1; (controller) 4 = 4 (motor)
    // VictorSPX *leftDriveMotor2; 2 = 1
    // VictorSPX *rightDriveMotor1; 1 = 3
    // VictorSPX *rightDriveMotor2; 3 = 2

    WPI_VictorSPX leftDriveMotor1{4}; 
    //WPI_VictorSPX leftDriveMotor2{2};
    WPI_VictorSPX rightDriveMotor1{1};
    //WPI_VictorSPX rightDriveMotor2{3};

    frc::XboxController *driver;
    frc::XboxController *codriver;

    frc::Timer autoTimer;

    double deadzone = 0.02;
    double intakeSpeed;
    double leftSpeed;
    double rightSpeed;
};