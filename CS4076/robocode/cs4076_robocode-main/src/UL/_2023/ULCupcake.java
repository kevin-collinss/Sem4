package UL._2023;

import robocode.Robot;
import robocode.*;

import java.awt.*;

/**
 * ULCupcake - Adam Byrne, Daniel Kenned, and Conor Callanan.
 * 	UL Robocode internal competition 2023
 *
 **/

public class ULCupcake extends Robot{
	public void run() {
		setColors(Color.pink,Color.white,Color.red);

		do {
			// Cupcake is hungry, Cupcake will find you
			turnRadarRight(360);
		} while (getEnergy() > 0);

		// Someone ate Cupcake
		fire(3);
		doNothing();
	}

	public void onScannedRobot(ScannedRobotEvent e) {
		// Cupcake likes sentry bots
		if(e.isSentryRobot()) return;

		// Cupcake will shoot you
		shoot(e.getBearing(), 3);

		// Cupcake likes personal space
		if(e.getDistance() < 100) {
			retreat(e.getBearing());
		}

	}

	public void onHitByBullet(HitByBulletEvent e) {
		// STANDS THERE UNFAZED, [TOURNIER DANS LA VIE plays in the background]
	}


	public void onHitWall(HitWallEvent e) {
		// Cupcake does not like walls but they are inevitable
		retreat(e.getBearing());
	}

	public void onHitRobot(HitRobotEvent e) {
		// Cupcake will shoot you
		shoot(e.getBearing(), 3);

		// Cupcake does not like hugs
		retreat(e.getBearing());
	}

	void retreat(double bearing) {
		// Cupcake will turn the other cheek
		if(bearing >= 0) {
			turnRight(bearing);
		} else {
			turnLeft(bearing);
		}

		// Guess what is hard to hit? A random moving target, that's what.
		if(Math.random() > 0.5) {
			back(75);
		} else {
			ahead(75);
		}
	}

	void shoot(double bearing, int power) {
		// Cupcake will find you and Cupcake will shoot you
		double angle = getHeading() - getGunHeading() + bearing;
		turnGunRight(angle);
		fire(power);
	}
}
