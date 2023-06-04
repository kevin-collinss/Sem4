/**
 * Copied from MyFirstRobot
 */

// Important to have
package CS4076._2023;

import robocode.AdvancedRobot;
import robocode.HitByBulletEvent;
import robocode.ScannedRobotEvent;

public class _01234567_example extends AdvancedRobot {
  public void run() {

    while (true) {
      ahead(100); // Move ahead 100
      turnGunRight(360); // Spin gun around
      back(100); // Move back 100
      turnGunRight(360); // Spin gun around
    }
  }

  public void onScannedRobot(ScannedRobotEvent e) {
    fire(1);
  }

  public void onHitByBullet(HitByBulletEvent e) {
    turnLeft(90 - e.getBearing());
  }
}