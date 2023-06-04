package ElRobotoKC;
import robocode.*;
import java.awt.Color;
import java.awt.geom.*;
import robocode.util.Utils;

// --------------------------------------------------------------------------------------
// DustBunny
//
// By Michael Dorgan
//
// Version 1.0 - Proof of Anti-gravity in a Nano-bot with room to spare for other stuff.
//
// Here's my entry into the Anti-gravity arena - with a Nano bot.  It's also uses
// somewhat smart targetting to always aim for the nearest competitor (slightly in-effective
// in some cases, but better than without!)  I didn't have room for fancy targetting, so
// just basic see and shoot.  This guy consistently is coming in 1st/2nd on my machine in
// 1000x1000 melee.  The circling in corner behavior was an accident, but it turns out to
// be very effective in Nano-bot land.  Here's hoping for luck.  Comments welcome :)
//
// Codesize 248
//
// Version 1.1
//
// Dropped averaging code to work over 10 scans instead of 20.  Way improved targetting,
// especially at close range by adding radar lock to the mix.  That really helps in 
// tight situations agaisnt other bots that don't realize I'm pounding them :)
// Other misc. optimizations to codesize.  Removed Radar adjust to get under
// 250.  Doesn't seem to hurt at all.  This guy is pretty darn good.
//
// Codesize 247
//
// Version 2.0!
//
// New major version with this upgrade.  Used Infinite style radar for better code space.
// Changed forces to be added every tick then cleared when we fire.  Added bullet firepower
// management (Infinity style w/o getOthers()).  Also added Infinity lead routine.  This
// works really well on most targets though it isn't 1v1 quality - I'll leave Moebius for
// that task.  Finally, my radar lock code now uses enemy range tracking.  It does a MUCH
// better job of locking onto the closest target.  Wish I had room for turn management,
// but I guess I'll have to leave that to Graviton - so I'll hit the walls hard every now
// and then ;) An excellent Nano Melee bot that should be competative in higher leagues.
// Alas, for a few more bytes, I could have colors as well.  Sigh.
//
// Codesize 246 
//
// Version 3.0
//
// Been a few years.  This is a fairly drastic change in this bots abilities.  I've 
// Improved the anit-grav movement a whole bunch.  The walls are no longer my enemy :)
// I've removed the leading target gun for a 0-lead gun.  I took the extra space and
// ported across Infinity's tracking system with some minor space inprovements.  This
// bot currently beats Moebius handily in 1 on 1 battles which means it is hard to pattern match.
// It also is now a contender for the melee championship.  This bot just got STRONG.
//
// Version 3.4
//
// Versions 3.2 and 3.3 sucked.  I went back to 3.1 for a base model.
// Here's what's different - shoot less hard.  Do special case velocity code against 1 opponnent.
// to remove small circle behavior which gets stomped 1v1.  The rest is the same.  Just managed
// to get 12 bytes back from some misc. changse I learned from 3.2 and 3.3.  I do waste 1 shot
// at the beginning of the first match.  That's worth 7 bytes.
// Code size:249
//
// Version 3.5
//
// Added some random movement and removed 1v1 code.  Seems to do better!
// Code size:244
//
// Version 3.6
//
// Tuned from roboresearch.  Guns fires 1/3 less powerful.  Hopefully that is enough to get
// the 25 basis points or so it needs for first.  
// Code size:244
//
// Version 3.7
//
// Wow - I fit a much superior gun in here with some major code crunching.  Local testing
// shows a nice improvement.  Some tuning is still required, but this is a major upgrade
// to the series.
// Code Size:249 - no colors and 1000x1000 board only for now.
//
// Version 3.8
//
// Mostly a space saving version, though marginal improvements are possible.  I did manage
// to get the battleField Size methods back in though so now I'm a rumble contender as well.
// Code Size:248 - no colors
// 
// --------------------------------------------------------------------------------------

public class DustBunny extends AdvancedRobot
{
	static final double GUN_FACTOR = 30;
	static final int AIM_START = 10;
	static final double AIM_FACTOR = 1.008;
	static final int FIRE_FACTOR = 7;
					
	static double xForce;
	static double yForce;
	static double lastDistance;
		
	public void run() 
	{
		// do this to hit stationary targets
		setAdjustGunForRobotTurn(true);

		//This costs 6 bytes or so and 1 bad shot at the beginning of each round.
		// Reset range finder
//		lastDistance = Double.POSITIVE_INFINITY;
						
		// Do infinite radar.  Saves much space (thanks Dr. Loco!)
		turnRadarRightRadians(Double.POSITIVE_INFINITY);
	}
	
	public void onScannedRobot(ScannedRobotEvent e) 
	{
		// Get Abs bearing for aiming routines (and A-Grav)
		// and distance for just about everything else :)
		double	absoluteBearing = e.getBearingRadians() + getHeadingRadians();
		double  distance = e.getDistance();
		
		// Use a very simple running average system.  /2 is as cheap as I can get this
		xForce = xForce *.9 - Math.sin(absoluteBearing) / distance;
		yForce = yForce *.9 - Math.cos(absoluteBearing) / distance;
		
		// Get our turn angle - factor in distance from each wall every time so we get
		// pushed towards the center when close to the walls.  This took a long time to come up with.
		setTurnRightRadians(Utils.normalRelativeAngle(
			Math.atan2(xForce + 1/getX() - 1/(getBattleFieldWidth() - getX()), 
					   yForce + 1/getY() - 1/(getBattleFieldHeight() - getY()))
						- getHeadingRadians()) );

		// Move ahead depending on how much turn is needed.
		setAhead(120 - Math.abs(getTurnRemaining()));
					
		// If we're at 0 and pointed at a target, fire.
//		if(setFireBullet(Math.min(2.49999,getEnergy() * GUN_FACTOR / distance)) != null)
		if(setFireBullet(Math.min(2.49999,getEnergy() / FIRE_FACTOR)) != null)
		{
			lastDistance = Double.POSITIVE_INFINITY;
		}

		// Lock onto closest bots																
		if(lastDistance+100 > distance)
		{
			lastDistance = distance;
	
		// and only the closest bot
			// Radar lock as we approach shooting time
			// Lowering this value causes us to turn more often do to better data.
			if(getGunHeat() < 1)
			{
				// Let this var be equal the the absolute bearing now...
				// and set the radar.
				setTurnRadarLeft(getRadarTurnRemaining());
				// This would be nice to prevent the occasional long shot.				
				//clearAllEvents();
			}
													// Infinity style gun fits!!!!  
			setTurnGunRightRadians(robocode.util.Utils.normalRelativeAngle(absoluteBearing - getGunHeadingRadians() + 
//				Math.random() *
				 
//				Math.max(1 - distance / (400), 0) * 
				(e.getVelocity() / (AIM_START + Math.pow(AIM_FACTOR, distance))) * Math.sin(e.getHeadingRadians() - absoluteBearing) ));		

		}
	}
}
