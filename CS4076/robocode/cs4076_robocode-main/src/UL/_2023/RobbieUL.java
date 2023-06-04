package UL._2023;
import robocode.*;
import java.awt.Color;

// API help : https://robocode.sourceforge.io/docs/robocode/robocode/Robot.html

/**
 * RobbieUl - By, Irene Lopez(22299475),Elliot Vowles(22299211) Conor Gray(22353518)
 */
public class RobbieUL extends Robot{

	public void run() {
		// basic setup
		setBodyColor(Color.yellow);
		setRadarColor(Color.green);
		setBulletColor(Color.red);
		setAdjustRadarForGunTurn(true);
		setAdjustGunForRobotTurn(true);
		setAdjustRadarForRobotTurn(true);


	while(getEnergy() > 0){
		
		while(Position() == false){
		if ( getTime() % 2 == 0){
		ahead(100);

		}else{
			turnRadarLeft(360);
			scan();		
			}
		} 
		while(Position() == true){
			if ( positionCorner() == false){
				turnRight((double) Math.random()*10 + 90);
				ahead(400);
			
			} else{
				turnRight(90);
				ahead(200);
			}
			}
			
		}
	}
	public 	boolean Position(){
	// looking for the border
		double width = getBattleFieldWidth(); // 100
		double height = getBattleFieldHeight(); // 100
		double border = getSentryBorderSize(); // 10
		double RobotX = getX(); // 80 x 80
		double RobotY = getY();
		boolean bad = false;
		// turning when hit red
		if( (double) RobotX <= border + 100 || (double) RobotX >= height - border - 100 || (double) RobotY <= border + 100 || (double) RobotY >= height - border - 100){
			bad = true;
		}
		return bad;
	}
	public 	boolean positionCorner(){
	// looking for the border
		double width = getBattleFieldWidth(); // 100
		double height = getBattleFieldHeight(); // 100
		double border = getSentryBorderSize(); // 10
		double RobotX = getX(); // 80 x 80
		double RobotY = getY();
		boolean corner = false;
		// turning when hit red
		if( (double) RobotX < (double) (width / 4) || (double) RobotX > (double) 3*(width / 4)){
			corner = true;
		}
		if ( (double)RobotY < (double) height / 4 ||(double) RobotY > (double) 3* (height / 4)){
			corner = true;
		}
		return corner;
	}


	public void onScannedRobot(ScannedRobotEvent e) {

		double angle = getRadarHeading();
		double gun =  getGunHeading();
	
	
			
				while( getGunHeading() > angle + 8 || (getGunHeading() < angle - 8)){
					turnGunLeft(8);
				}
		
		fire(1);
		}	
/*	public void onBullet(BulletHitEvent e, long time1, double v, double d){
		long time2 = getTime();
		long time3 = time2 * time1;
		double distance1 = ((double) time3 * ((double) v);
		
	}*/
	public void onHitByBullet(HitByBulletEvent e){
		ahead(30);
		
	}
	public void onHitRobot(HitRobotEvent e){
			fire(1);
	}
	
}