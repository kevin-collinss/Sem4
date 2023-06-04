package ElRobotoKC;
import robocode.*;
import robocode.Robot;
import robocode.util.Utils;

import java.awt.*;

import static java.lang.Math.PI;

public class ElRoboto extends  AdvancedRobot {

    // static final double infin = Double.POSITIVE_INFINITY;
    // static final double GUN_FACTOR = 30;
	// static final int AIM_START = 10;
	// static final double AIM_FACTOR = 1.008;
	// static final int FIRE_FACTOR = 7;
					
	// static double xForce;
	// static double yForce;
	// static double lastDistance;

    double x, y;
    final int border = getSentryBorderSize();
            // stay this far in from teh edge
    final double offset = 100;
    final double h = getBattleFieldHeight();
    final double w = getBattleFieldWidth();
    final double edge = border + offset;
    


    public void run() {
        setBodyColor(Color.WHITE);
        setRadarColor(Color.WHITE);
        setScanColor(Color.WHITE);
        
		turnRadarRightRadians(infin);
        setAdjustGunForRobotTurn(true);
    }
    

    private void goTo(double x, double y) {
        
        double x_dest = x - getX();
        double y_dest = y - getY();

        double goAngle = 0;

        double distance = Math.hypot(x_dest, y_dest);
        if (x_dest >= 0 && y_dest >= 0) {
            goAngle = Math.asin(x_dest / distance);
        }
        if (x_dest >= 0 && y_dest < 0) {
            goAngle = PI - Math.asin(x_dest / distance);
        }
        if (x_dest < 0 && y_dest < 0) {
            goAngle = PI + Math.asin(-x_dest / distance);
        }
        if (x_dest < 0 && y_dest >= 0) {
            goAngle = 2.0 * PI - Math.asin(-x_dest / distance);
        }

        // convert to degrees
        goAngle *= 57.2958;

        // compensate for teh current heading
        goAngle -= getHeading();

        // reduce turns if its possible
        if(goAngle < 0){
            goAngle += 360;
        }

        // easier to go teh other way if its turning right 3 times to go left
        if(goAngle > 270){
            goAngle -= 270;
            turnLeft(goAngle);
        }else {
            turnRight(goAngle);
        }

        ahead(distance);
    }

    // this is whenever teh scanner picks up something
    @Override
    /*public void onScannedRobot(ScannedRobotEvent e) {
        
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

        move();
    }*/

    public void move(){
        
        x = edge + ((w-(2*edge)) * Math.random());
        y = edge + ((h-(2*edge)) * Math.random());
        goTo(x,y);
    }

}