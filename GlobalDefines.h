/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : .h
* Modified: Oct 24, 3003
********************************************************************/

#ifndef GLOBAL_DEFINES
#define GLOBAL_DEFINES

#define FPS 60 // How many frames to draw in a second

#define MAX_VERTICES 255 /* The maximum number of vertices in a polygon */

#define SIZ_X       800
#define SIZ_Y       600
#define MIN_X		-399.0
#define MAX_X        400.0
#define MIN_Y        -299.0
#define MAX_Y       300.0
#define PI 			3.14159
#define DEGINRAD 	57.2957795
#define TRUE 		1
#define FALSE 		0
#define LARGESCORE	20
#define MEDIUMSCORE	40
#define SMALLSCORE	80
#define FIRE_DELAY 	4
#define RANGE_SIZE 	80	/* How large of an asteroid free zone to have around the ship*/

#define INFINITE 	999999 /* Close enough to infinite for our purposes */
#define MAX_LETTERS	40

/* Alien defines */
#define ALIEN_EDGESPACE 20

/* Number of asteroids starting at each level */
#define ASTEROIDS_ONE	4
#define ASTEROIDS_TWO	8
#define ASTEROIDS_OTHER	10

/* bullet Defines */

#define MAX_STORE_BULLETS 255
#define MAX_BULLETS 4
#define MAX_LIFE  1.5
#define REMOVE_LIFE 1
#define BULLET_SPEED 340


/* Asteroid defines */
#define  SHIP_VERTEX       6               /* Number of vertices a ship has */
#define  ROCK_VERTEX      16       /* Max. number of vertices for each rock */
#define  MAX_ROCKS       140                     /* Maximum number of rocks */
#define  ACCEL_STEPS      14                 /* Acceleration steps for ship */
#define AS_SPEED_RATIO 200 /* The amount to multiply size by to get max speed */
#define MAX_EXPLODE_SPEED 1
#define EXPLOSION_LIFE 2

/* Game defines */
#define MAX_SCORES 10
#define MAX_MESSAGES 5
#define	MESSAGE_DELAY	30	

/* Ship defines */
#define ACCEL 50 /* The acceleraton factor of the ship */
#define DRAG .999 /* How much the ship slows down due to drag */

#define SM_ROTATE 0.00047 /* How much to rotate when tapping the key */
#define LG_ROTATE 0.3  /* How much to rotate the ship in one step */
#define RANGE 0.2 /* how close to a 90 degree to round */
#define MAX_SHIP_SPEED 500
#define SPAWN_TIME 	3 /* How many seconds until the ship can come back to life*/
#define HYPERSPACE_TIME	0.5 /* how many seconds before the ship reapears from hyperspace */

/* Alien defines */
#define NUM_ALIENS 2

/* Player defines */
#define START_LIVES 3
#define NEXT_LIFE 10000
#define NUM_INITIALS 3
/* Locations and sizes of text */
#define LIVES_X -260
#define LIVES_Y 220
#define SCORE_SIZE .5
#define SCORE_X -270
#define SCORE_Y 260
#define HI_X -15
#define HI_Y 260
#define HI_SIZE		0.7
#define	COPY_SIZE	0.7
#define	COPY_X		-76
#define	COPY_Y		-250
#define INFO_SIZE 	.4	/* The size of high score, insert coin etc. */
#define COIN_X		-100
#define COIN_Y		-200
#define	MESSAGE_X	-90
#define	MESSAGE_Y	200
#define HELP_MAX_Y	200
#define	HELP_X		-200
#define GAME_OVER_X	-70
#define GAME_OVER_Y	100
#define INITIAL_INFO_X	-250
#define INITIAL_INFO_MAX_Y 200

#define HISCORE_MAX_Y 	120
#define HISCORE_Y 	160
#define	HISCORE_X	-90

/* Font defines */
#define FONT_DOT 	37
#define FONT_UNDERSCORE	36
#define	ASCII_UNDERSCORE 95
#define FONT_SPACING	4
#define INFO_SPACING_Y 	30
#define INITIALS_X 	-30
#define INITIALS_Y 	-180
#define INITIALS_SIZE 	.2
#define HELP_DELAY	100
#define	GAME_OVER_DELAY	50
#define SCORE_TABLE_DELAY	300
#define COIN_MODE_DELAY		500

#define GAME_START_TIME		20
#define LEVEL_DELAY_TIME	30	/* how long after the last asteroid is hit till the asteroids should be shown */

#endif
