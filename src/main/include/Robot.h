// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include "RobotContainer.h"
#include <frc2/command/WaitCommand.h>

class Robot : public frc::TimedRobot {
  //Set up electronics here
  //Give each motor a name, assign it to a port, and set it as brushed or brushless
  //Then, add motor controllers to groups and the drivetrain

  frc::XboxController Xbox {0};
  static const int ClawDeviceID = 14,VerticalLiftID = 15, AlgaeIntakeID = 3, RotateSensorID = 4;
  rev::CANSparkMax Claw {ClawDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax Algae {AlgaeIntakeID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax Vertical {VerticalLiftID, rev::CANSparkMax::MotorType::kBrushless};



  public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousPeriodic() override {
  
      std::this_thread::sleep_for(std::chrono::seconds(1));
      Claw.Set(-1);  
      Vertical.Set(1);
      std::this_thread::sleep_for(std::chrono::seconds(3));
      // frc2::WaitCommand(3.0_s);
      Claw.Set(-1);  
      Vertical.Set(1);
      Algae.Set(1);
      std::this_thread::sleep_for(std::chrono::seconds(3));
      Claw.Set(0);
      Vertical.Set(0);
      Algae.Set(0);
      std::this_thread::sleep_for(std::chrono::seconds(5));
  
  }

  void AutonomousInit() override{
  }
  void TeleopInit() override;
  void TeleopPeriodic() override {
    bool AButton = Xbox.GetRawButton(1);
    bool BButton = Xbox.GetRawButton(2);
    bool XButton = Xbox.GetRawButton(3);
    bool YButton = Xbox.GetRawButton(4);
    bool LBumper = Xbox.GetRawButton(5);
    bool RBumper = Xbox.GetRawButton(6);
    bool LTrigger = Xbox.GetRawAxis(2);
    bool RTrigger = Xbox.GetRawAxis(4);
    

    if (RBumper) {
      Claw.Set(-1);  
      Vertical.Set(1);
    }

    else if (LBumper) {
      Algae.Set(.45);
    }

    else if (AButton) {
      Algae.Set(-.45);
    }

    else if (XButton) {
      Claw.Set(-1);  
      Vertical.Set(1);
      Algae.Set(.45);
    }

    else {
      Claw.Set(0);
      Algae.Set(0);
      Vertical.Set(0);
    }
  }

  void TestPeriodic() override;
  
 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc2::Command* m_autonomousCommand = nullptr;

  RobotContainer m_container;

  
};



