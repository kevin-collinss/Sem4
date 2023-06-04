package CS4076._2023;
import robocode.*;
import robocode.Robot;


import java.awt.*;

public class _21318204_Benrhama extends Robot {
    public void run() {

        //set colours, obviously has to be clean
        setBodyColor(Color.GREEN);
        setBulletColor(Color.RED);
        setRadarColor(Color.CYAN);

        setAdjustRadarForRobotTurn(true); //turn on radar
        setAdjustGunForRobotTurn(true); //turn on gun

        while (true) {
            // Turn on the radar so it can be able to scan for enemy robots
            turnRadarRight(360);

            //move forwards distance of 100
            ahead(100);
            //turn 180 degrees
            turnRight(180);

        }
    }

    public void onScannedRobot(ScannedRobotEvent e) {
        /**
         * basis of this function is to avoid shooting a sentry robot and
         * if the robot is an enemy robot in range, aim the gun and fire if there is enough energy too
         */
        if (e.isSentryRobot()) {
            return; // if benrhama sees a sentry robot, do nothing
        }
        double absoluteBearing = getHeading() + e.getBearing(); //adds the direction of enemy robot's bearing to benrhama's current heading
        double bearingFromGun = (absoluteBearing - getGunHeading()); //this gets the difference in benrhama's gun heading to what we calculated before, difference in degrees between benrhams and enemy robot
        if (Math.abs(bearingFromGun) <= 10) { //if this distance is < 10 degrees
            turnGunRight(bearingFromGun); //turns the gun to right
            if (getGunHeat() == 0) { //if we have the abilty to fire our gun
                fire(3); //fire
            }
        } else {
            turnGunRight(bearingFromGun); //if > 10, does the same but just doesn't fire
        }

    }

    public void onHitByBullet(HitByBulletEvent e) {
        /**
         * basis of this is the reaction benrhama will take once hit by a bullet from an enemy.
         * basically it has a 50% chance of moving left or right and it moves in that direction perpendicular to the direction of the bullet.
         * I wanted benrhama to be able to try avoid being hit subsenquently by the same robot and move randomly
         */
        if (Math.random() < 0.5) {
            turnLeft(90 - e.getBearing()); //turns benrhama left by an angle of 90 degrees - the angle which the bullet hit the robot relative to benrhama's heading at that time
        } else {
            turnRight(90 - e.getBearing()); //same but it moves right
        }
    }

    public void onHitWall(HitWallEvent e) {
        /**
         * This is more a precautionary has benrhama's movement shouldn't allow this. If he hits a wall,
         * he simply turns around.
         */
        turnRight(180);
    }

    public void onHitRobot(HitRobotEvent e) {
        /**
         * Although ramming could be a useful strategy, I am more interested in survivng while dealing damage.
         * You also loose health when you ram so this just simply backs the robot away and turns left perpendicular.
         *
         */
        back(50);
        turnLeft(90);
    }


}
