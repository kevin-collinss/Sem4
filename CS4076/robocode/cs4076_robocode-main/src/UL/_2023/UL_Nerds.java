package UL._2023;
import robocode.*;
import java.awt.Color;

public class UL_Nerds extends AdvancedRobot {
  int gunDirection = 1;

  public void run() {
    // Mere aesthetic changes
    setBodyColor(Color.red);
    setRadarColor(Color.white);
    setGunColor(Color.blue);
    setBulletColor(Color.yellow);

    // Turns the gun infinitely, looking for enemies
    while (true) {
      turnGunRight(360);
    }
  }

  public void onScannedRobot(ScannedRobotEvent e) {
    // Turn the robot towards the enemy
    setTurnRight(e.getBearing());
    // Shoots always that it's aiming at the enemy
    setFire(3);
    // And move forward
    setAhead(100);
    // Inverts the gun direction on each turn
    gunDirection = -gunDirection;
    // Turn 360 degrees (clockwise or anti clockwise,)
    setTurnGunRight(360 * gunDirection);
    // Execute all the pending actions
    execute();
  }
}