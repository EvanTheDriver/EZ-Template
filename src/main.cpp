#include "main.h"
pros::Motor cataMotor(18,1);
pros::Motor intakeMotor(2,1); 
pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Rotation cataRotation(4);

pros::ADIDigitalOut Wings(8);
pros::ADIDigitalOut Lift(7);


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-10, -14, 13}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{1, 11, -12}

  // IMU Port
  ,19

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.66666666667


  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); 
  Wings.set_value(0);
  // Set the drive to your own constants from autons.cpp!
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */  

void defauto(){
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.
  // defense
  chassis.set_drive_pid(25, DRIVE_SPEED, true);
  chassis.wait_drive();
  intakeMotor = 127;
  delay(500);
  intakeMotor = 0;
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  Wings.set_value(1);
  chassis.set_drive_pid(13, DRIVE_SPEED, true);
  chassis.wait_drive();  

}
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

//Auto skills
/*cataMotor = 115;
delay(40000);
cataMotor = 0;
chassis.set_drive_pid(-5, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_turn_pid(30, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(-87, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_turn_pid(90, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(55, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_turn_pid(187, TURN_SPEED);
chassis.wait_drive();
Wings.set_value(1);
chassis.set_drive_pid(32, DRIVE_SPEED, true);
chassis.wait_drive();
Wings.set_value(0);
chassis.set_drive_pid(-24, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_drive_pid(28, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_drive_pid(-12, DRIVE_SPEED, true);*/

//defence
intakeMotor = 127;
chassis.set_drive_pid(50.5, DRIVE_SPEED, true);
chassis.wait_drive();
delay(700);
intakeMotor = 0;
chassis.set_drive_pid(-57, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_turn_pid(-56, TURN_SPEED);
chassis.wait_drive();
Wings.set_value(1);
chassis.set_drive_pid(14, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_turn_pid(15, TURN_SPEED);
chassis.wait_drive();
Wings.set_value(0);
chassis.set_turn_pid(-43, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(26, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_drive_pid(-8, DRIVE_SPEED, true);
chassis.wait_drive();
chassis.set_turn_pid(75, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(35, DRIVE_SPEED, true);
chassis.wait_drive();
intakeMotor = -127;
chassis.set_drive_pid(17, DRIVE_SPEED, true);
chassis.wait_drive();
Wings.set_value(1);
delay(700);
intakeMotor = 0;



// offense
// intakeMotor = 127;
// chassis.set_drive_pid(58, DRIVE_SPEED, true);
// chassis.wait_drive();
// delay(600);
// intakeMotor = 0;
// chassis.set_turn_pid(123, TURN_SPEED);
// chassis.wait_drive();
// Wings.set_value(1);
// intakeMotor = -127;
// delay(500);
// intakeMotor = 0;
// chassis.set_drive_pid(32, DRIVE_SPEED, true);
// chassis.wait_drive();
// Wings.set_value(0);
// chassis.set_drive_pid(-10, DRIVE_SPEED, true);
// chassis.wait_drive();
// chassis.set_turn_pid(270, TURN_SPEED);
// chassis.wait_drive();
// intakeMotor = 127;
// chassis.set_drive_pid(28, TURN_SPEED, true);
// delay(1700);
// intakeMotor = 0;
// chassis.wait_drive();
// chassis.set_drive_pid(-6, DRIVE_SPEED, true);
// chassis.wait_drive();
// chassis.set_turn_pid(175, TURN_SPEED);
// chassis.wait_drive();
// chassis.set_drive_pid(45, DRIVE_SPEED, true);
// chassis.wait_drive();
// chassis.set_turn_pid(80, TURN_SPEED);
// chassis.wait_drive();
// Wings.set_value(1);
// intakeMotor = -127;
// delay(500);
// intakeMotor = 0;
// chassis.set_drive_pid(18, DRIVE_SPEED, true);
// chassis.wait_drive();
// chassis.set_drive_pid(-7, DRIVE_SPEED, true);
// chassis.wait_drive();
// Wings.set_value(0);
// chassis.set_turn_pid(56, TURN_SPEED);
// chassis.wait_drive();
// chassis.set_drive_pid(35, DRIVE_SPEED, true);
// chassis.wait_drive();
// chassis.set_drive_pid(-15, DRIVE_SPEED, true);
// chassis.wait_drive();


}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  bool  wingPosition= false;
  bool  liftPosition = false;
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

    // chassis.tank(); // Tank control
     chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    //chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    if (master.get_digital_new_press(DIGITAL_L2)){
        wingPosition = !wingPosition;
        Wings.set_value(wingPosition);
    }

    if (master.get_digital_new_press(DIGITAL_A)){
        liftPosition = !liftPosition;
        Lift.set_value(liftPosition);
    }

    
    if (master.get_digital(DIGITAL_R1) == 1){
        intakeMotor = 127;
    }
    else if (master.get_digital(DIGITAL_R2) == 1){
        intakeMotor = -127;
    }
    else {
      intakeMotor = 0;
    }
    if(master.get_digital(DIGITAL_L1) == 1){
			cataMotor = 115;
		}
		else{
			if(cataRotation.get_angle() < 4600 || cataRotation.get_angle() > 35000){
				cataMotor = 120;
			}
			else{
				cataMotor = 0;
			}
		}

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}