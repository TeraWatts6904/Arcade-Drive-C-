/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//#include <DoubleSolenoid.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <Solenoid.h>
#include <CameraServer.h>
#include <drive/DifferentialDrive.h>
#include <SpeedControllerGroup.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include "ctre/Phoenix.h"
#include <robotdrive.h>




/**
 * This is a sample program showing the use of the solenoid classes during
 *   operator control.
 * Three buttons from a joystick will be used to control two solenoids:
 *   One button to control the position of a single solenoid and the other
 *   two buttons to control a double solenoid.
 * Single solenoids can either be on or off, such that the air diverted through
 *   them goes through either one channel or the other.
 * Double solenoids have three states: Off, Forward, and Reverse. Forward and
 *   Reverse divert the air through the two channels and correspond to the
 *   on and off of a single solenoid, but a double solenoid can also be "off",
 *   where both channels are diverted to exhaust such that there is no pressure
 *   in either channel.
 * Additionally, double solenoids take up two channels on your PCM whereas
 *   single solenoids only take a single channel.
 */






class Robot : public frc::IterativeRobot {

	WPI_TalonSRX m_FLMotor{21};
	WPI_TalonSRX m_FRMotor{23};
	WPI_TalonSRX m_BLMotor{22};
	WPI_TalonSRX m_BRMotor{24};
	frc::SpeedControllerGroup m_right{m_FRMotor, m_BRMotor};
	frc::SpeedControllerGroup m_left{m_FLMotor, m_BLMotor};
	frc::DifferentialDrive m_robotDrive{m_left, m_right};
	int autoLoopCounter;

public:
	void AutonomousInit() //This method is called once each time the robot enters Autonomous
		{
			autoLoopCounter = 0;
		}

		void AutonomousPeriodic() /* This method is called each time the robot receives a
		* packet instructing the robot to be in Autonomous Enabled mode (approximately every 20ms)
		* This means that code in this method should return in 20 ms or less (no delays or loops)
		*/
		{
			/* This example checks if the loop counter has reached 100
			* (approximately 2 seconds) THis is a fairly simple example and is not recommended for actual
			* autonomous routines, because delayed or missed packets will significantly affect the timing
			* of this program
			*/
			if(autoLoopCounter < 100)
			{
			m_robotDrive.ArcadeDrive(-0.5, 0.0); /* If autoLoopCounter has not yet reached 100,
				* this instructs the robot to drive forward at half speed, and increment the counter
				**/
				autoLoopCounter++;
			} else {
				m_robotDrive.ArcadeDrive(0.0, 0.0); // If autoLoopCounter has reached 100, this stops the robot
			}
		}


	void RobotInit() {
			CameraServer::GetInstance()->StartAutomaticCapture();
			CameraServer::GetInstance()->StartAutomaticCapture();
		}
	void TeleopPeriodic() override {
		m_robotDrive.ArcadeDrive(m_stick1.GetY()*-1, m_stick2.GetX());
		/* The output of GetRawButton is true/false depending on whether
		 * the button is pressed; Set takes a boolean for for whether to
		 * use the default (false) channel or the other (true).
		 */
	//	m_solenoid.Set(m_stick.GetRawButton(2));
		/* In order to set the double solenoid, we will say that if
		 * neither
		 * button is pressed, it is off, if just one button is pressed,
		 * set the solenoid to correspond to that button, and if both
		 * are pressed, set the solenoid to Forwards.
		 */

		if (m_stick.GetRawButton(6)) {
			m_led2.Set(true);
			m_led1.Set(true);

		} else {
			m_led2.Set(false);
			m_led1.Set(false);
               		}
		if (m_stick.GetRawButton(5)) {
					m_led3.Set(true);
				} else {
					m_led3.Set(false);
		               		}

	}

private:
	frc::Joystick m_stick{0};
	frc::Joystick m_stick1{1};
	frc::Joystick m_stick2{2};

	// Solenoid corresponds to a single solenoid.
	frc::Solenoid m_solenoid{0};
	frc::Solenoid m_led1{1};
	frc::Solenoid m_led2{2};
	frc::Solenoid m_led3{3};
	frc::Solenoid m_led4{4};

	// DoubleSolenoid corresponds to a double solenoid.

	static constexpr int  kyellow = 1;
	static constexpr int  kDoubleSolenoidgreend = 2;
	static constexpr int  kDoubleSolenoidblue = 3;
	static constexpr int  kDoubleSolenoidred = 4;

};

START_ROBOT_CLASS(Robot)


