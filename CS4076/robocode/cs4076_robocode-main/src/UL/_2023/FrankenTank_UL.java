package UL._2023;
import robocode.*;
import robocode.util.Utils;
import java.awt.Color;

public class FrankenTank_UL extends Robot
{
	private double[] boundary;
    private double[] center;

    private final double minimumDistanceFromSentry = 200;

    private boolean flip = false;

	public void run() {
		this.boundary = new double[] {this.getSentryBorderSize(), this.getSentryBorderSize(), this.getBattleFieldWidth() - this.getSentryBorderSize(), this.getBattleFieldHeight() - this.getSentryBorderSize()};
        this.center = new double[] {this.getBattleFieldWidth()/2, this.getBattleFieldHeight()/2};

		setColors(new Color(92, 140, 52), new Color(92, 140, 52), new Color(92, 140, 52), new Color(191, 77, 46), new Color(191, 77, 46));

		while(true) {
			//Get out of 
			turnRadarRight(360);
		}
	}
	
	public void onScannedRobot(ScannedRobotEvent e) {
		double rotate = 0;
		double myHead = getHeading();
		double gunHead = getGunHeading();
		double radarHead = getRadarHeading();
		double myBearing = e.getBearing();
	    double absoluteBearing = myHead + myBearing;
		
		double x = getX();
		double y = getY();
		
		//Avoiding interacting with the sentry bot
		if (e.isSentryRobot()) {
		   	return;
        }


        double distance = 30;
        
        if(e.getDistance() > 300){
            distance = 30 + ((e.getDistance() - 300) / 10);
        }
        else{
            distance = 30;
        }

        rotate = Utils.normalRelativeAngleDegrees(absoluteBearing - gunHead);
        turnGunRight(rotate);
        fire(3);

        if(myBearing >= 0){
            if(myBearing > 90){
                turnRight(myBearing - 90);
            }
            else if(myBearing < 90){
                turnLeft(90 - myBearing);
            }
        }
        else{
            if(myBearing > -90){
                turnRight(90 + myBearing);
            }
            else if(myBearing < - 90){
                turnLeft(-myBearing - 90);
            }
        }

        System.out.println(this.canMove(distance));
        if(this.canMove(distance))
            ahead(distance);
        else{
            this.flip = !this.flip;
            back(distance*1.5);
        }
    }

	public void onHitRobot(HitRobotEvent e){	
		
		double myBearing = e.getBearing();
		double rotate = 0;
		double gunHead = getGunHeading();
		double myHead = getHeading();
		double absoluteBearing = myHead + myBearing;
		
		rotate = Utils.normalRelativeAngleDegrees(absoluteBearing - gunHead);
		turnGunRight(rotate);
		
		ahead(30);
		fire(3);
		fire(3);

	}

    //Turns the robot towards the specified point
    private void turnTowardsPoint(double[] pos){
        double x = this.getX();
        double y = this.getY();
        //This first part finds which quadrant the point is in relation to the robot. This is used for calculation later.
        int quadrant = 0;
        if(pos[0] > x && pos[1] > y)
            quadrant = 0;
        else if(pos[0] < x && pos[1] > y)
            quadrant = 1;
        else if(pos[0] < x && pos[1] < y)
            quadrant = 2;
        else if(pos[0] > x && pos[1] < y)
            quadrant = 3;
        //This line has two parts. The first(although it doesnt look like it) is the Math.abs(...)
        //Here we are getting the angle of the triangle made by the robot and the point(height is point's y-our y, width is point's x - our x)
        //Thus we get the angle. I do absolute value of that because I don't really want negatives. 
        //This is where the quadrants come in. The base of the triangle will always be along positive or negative x. 
        //This means that the full angle(relative to trigonometric 0, rather than the triangle's angle) is going to be the angle we got
        //+ which quadrant we are in * 90(since angles in the second quadrant are > 90, angles in third quadrant are > 180 etc.)
        double triAngle = Math.abs(Math.toDegrees(Math.atan((pos[1] - y) / (pos[0] - x)))); //The angle were getting in the triangle. Pretty good name right?
        double angle = 0;
        if(quadrant % 2 == 0)
            angle = (double) (quadrant * 90) + triAngle; 
        else
            angle = (double) ((quadrant+1)*90) - triAngle;
        //Lastly we find the amount we need to turn by subtracting heading(in normal angle) by the angle we calculated
        turnRight(this.rbAngleToNorm(this.getHeading()) - angle);
    }

    //Converts a robocode angle to a normal angle
    private double rbAngleToNorm(double angle){
        return this.correctAngle(360-angle+90); //360 - the variable makes the angle go from clockwise to counterclockwise. subtracting by 90 sets 0 to be on the right.
    }

    //takes an angle and makes sure it is within 0-359 degrees.
    private double correctAngle(double angle){
        if (angle > 359) 
            return angle - 360; 
        else if (angle < 0)
            return angle + 360;
        return angle;
    }

    private boolean canMove(double distance){
        double heading = this.getHeading();
        double x = this.getX();
        double y = this.getY();

        double angle = 0;

        if(heading < 90){ //First Quadrant
            angle = Math.toRadians(this.rbAngleToNorm(heading));
        }
        else if(heading < 180){ //Second Quadrant
            angle = Math.toRadians(this.rbAngleToNorm(180 - heading));
        }
        else if(heading < 270){ //Third Quadrant
            angle = Math.toRadians(this.rbAngleToNorm(360 - heading));
        }
        else{ //Fourth Quadrant
            angle = Math.toRadians(this.rbAngleToNorm(360 - heading));
        }

        double[] endpoint = new double[] {x + (distance * Math.cos(angle)), 
                                          y + (distance * Math.sin(angle))};

        if(this.inBoundary(endpoint))
            return false;
        else{
            //ahead(distance);
            return true;
        }
    }

    private boolean inBoundary(double[] pos){
        return ((pos[0] < this.boundary[0]) || (pos[1] < this.boundary[1]) || (pos[0] > this.boundary[2]) || (pos[1] > this.boundary[3]));
    }
}