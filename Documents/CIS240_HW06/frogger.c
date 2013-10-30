/*
 * frogger.c : Camillo J. Taylor - Sept. 25, 2013
 */

#include "lc4libc.h"

/*
 * #############  SPRITE PATTERNS ######################
 */

/* Define the frog sprite pattern - Northward Facing */
unsigned int frog_sprite_N[8] = { 0x18, 0xBD, 0xBD, 0xFF, 0x3C, 0xBD, 0xBD, 0xFF };
unsigned int frog_sprite_S[8] = { 0xFF, 0xBD, 0xBD, 0x3C, 0xFF, 0xBD, 0xBD, 0x18 };
unsigned int frog_sprite_E[8] = { 0xEE, 0x88, 0xFE, 0xFF, 0xFF, 0xFE, 0x88, 0xEE };
unsigned int frog_sprite_W[8] = { 0x77, 0x17, 0x7F, 0xFF, 0xFF, 0x7F, 0x17, 0x77 };
/* Define the X pattern */
unsigned int X_sprite[8] = { 0xC3, 0xE7, 0x7E, 0x3C, 0x3C, 0x7E, 0xE7, 0xC3 };

/*
 * #############  DATA STRUCTURES THAT STORE THE GAME STATE ######################
 */

// Game Modes
#define PLAYING_MODE       1
#define DEAD_FROG_MODE     2
#define FROG_MADE_IT_MODE  3
#define END_MODE           10

// Global game mode
int mode;

/* frog_rank : rank of frog on screen - The screen is broken into 14 ranks each 8 pixels tall
 * rank = 0   - start row
 * rank = 1-5 - highway section
 * rank = 6   - safe zone
 * rank = 7-11 - river
 * rank = 12   - end row, froggy heaven
 * rank = 13   - A buffer row at the top of the screen for decoration - frog can't get here
 */
lc4int frog_rank;

/* frog_x : coordinates of left hand side of frog sprite in pixels */
lc4int frog_x;

#define NORTH 0
#define SOUTH 1
#define EAST  2
#define WEST  3

/* frog_orientation indicates which way the frog is pointing based on its last jump */
lc4int frog_orientation;

#define NUMBER_OF_LIVES    3

/* nfrogs : number of frog lives remaining */
lc4int nfrogs;

lc4int delay_counter;

/*
 * ############# CODE FOR DEALING WITH ALTERNATING PATTERNS ######################
 */

/* N_ELEMENTS number of cars, logs, lily_pads on each rank */
#define N_ELEMENTS 5

/*
 * This structure helps us to keep track of the logs and cars and other periodic structures
 * that are part of the game play.
 * The endpoints field should be an array of monotonically increasing +ve values that 
 * define the endpoints of the structures. These endpoints are grouped into pairs so the first
 * and second define the endpoints of the first element, the third and fourth the endpoints
 * of the next element and so on. There are 5 elements in each pattern corresponding to 10
 * endpoints.
 * The offset field is updated on every timer tick and is used to advance the pattern over
 * the screen.
 * The velocity field contains the value that is used to update the offset. Hence this value
 * controls the speed that the pattern moves in the game
 */
typedef struct {
  int endpoints[2*N_ELEMENTS];
  int offset, velocity;
} alternating_pattern;

alternating_pattern traffic[5]; // 5 rows of traffic traffic[0] corresponds to rank 1
alternating_pattern logs[5];    // 5 rows of logs logs[0] corresponds to rank 7
alternating_pattern lily_pads;  // the home row at the top of the screen

/*
 * init_pattern : create a pattern where the interval lengths are specified by the s parameters
 */
void init_pattern (alternating_pattern *out,
		   int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int s9,
		   int offset, int velocity)
{
  out->endpoints[0] = s0;
  out->endpoints[1] = out->endpoints[0] + s1;
  out->endpoints[2] = out->endpoints[1] + s2;
  out->endpoints[3] = out->endpoints[2] + s3;
  out->endpoints[4] = out->endpoints[3] + s4;
  out->endpoints[5] = out->endpoints[4] + s5;
  out->endpoints[6] = out->endpoints[5] + s6;
  out->endpoints[7] = out->endpoints[6] + s7;
  out->endpoints[8] = out->endpoints[7] + s8;
  out->endpoints[9] = out->endpoints[8] + s9;

  out->offset = offset;
  out->velocity = velocity;
}

int abs (int x) {
  if (x < 0) return (-x); else return x;
}

/*
 * The highway section and the river section and the lily pads are composed of various alternating patterns
 * that the frog must either avoid or jump onto. These patterns are composed of elements which may represent 
 * logs or cars or lily pads. Each rank contains exactly 5 such elements, specified by the N_ELEMENTS constant.
 * Note that as the pattern moves some of these elements will appear on screen and some won't. The following 
 * routine allows you to determine the start and end column, in screen coordinates of each of the elements
 * on the rank. You can use this routine to help draw the elements in the correct place or to check for
 * collisions with the frog. Note again that the elements may be either partially or fully off screen so the
 * values in start_col and end_col need not be in the range 0-128.
 */

void get_element_endpoints (alternating_pattern *pattern, int element_index, int *start_col, int *end_col)
{
  int period, start, end, temp;
  
  if ((element_index >= 0) && (element_index < N_ELEMENTS)) {
    period = pattern->endpoints[2*N_ELEMENTS - 1];
    start = pattern->endpoints[2*element_index];
    end = pattern->endpoints[2*element_index + 1];

    *start_col = start - pattern->offset;
    temp = (start + period - pattern->offset) % period;

    if (temp < abs(*start_col)) *start_col = temp;

    *end_col = *start_col + (end - start);
  }
}

/* update_pattern : shift the pattern by the requisite velocity by updating the offset */
void update_pattern (alternating_pattern *pattern) {
  int period = pattern->endpoints[2*N_ELEMENTS - 1];
  pattern->offset = (pattern->offset + pattern->velocity + period) % period;
}

/*
 * #############  CODE THAT DRAWS THE SCENE ######################
 */

void draw_lily_pads ()
{
  // YOUR CODE HERE
  // remember to draw the top most decoration bar in yellow
  lc4_draw_rect(0, 0, 128, 8, YELLOW);
  for(int n = 0; n < N_ELEMENTS; n++) {
    //*start and *end will be set when get_element_endpoints is called (?)
    int *start, *end;
    get_element_endpoints(lily_pads, n, *start, *end);
    lc4_draw_rect(*start, 8, *end-*start, 8, YELLOW);
  }

}

void draw_logs ()
{
  // YOUR CODE HERE
  // Use lc4_draw_rect and get_element_endpoints
  // remember that rank 7 corresponds to logs[0]
  // remember to draw the river in blue
  lc4_draw_rect(0, 16, 128, 40, BLUE);
  for(int r = 0; r < 5; r++){
    for(int e = 0; e < N_ELEMENTS, e++){
      int *start, *end;
      get_element_endpoints(logs + r, e, *start, *end);
      lc4_draw_rect(*start, (6-r)*8+1, *end-*start, 6, RED);
    }
  }
}

void draw_safe_zone ()
{
  // YOUR CODE HERE
  lc4_draw_rect(0, 56, 8, 128, GRAY8);
}

void draw_traffic ()
{
  // YOUR CODE HERE
  // Use lc4_draw_rect and get_element_endpoints
  // remember that rank 1 corresponds to traffic[0]
  for(int r = 0; r < 5; r++){
    for(int e = 0; e < N_ELEMENTS, e++){
      int *start, *end;
      get_element_endpoints(traffic + r, e, *start, *end);
      lc4_draw_rect(*start, (12-r)*8+1, *end-*start, 6, WHITE);
    }
  }
}

void draw_home_row ()
{
  // YOUR CODE HERE
  lc4_draw_rect(0, 104, 8, 128, GRAY8);

}

void draw_frog ()
{
  // YOUR CODE HERE
  // Remember to take into account the frog orientation when drawing it
  // frogs that make it to rank 12 should get a special color like yellow
  // in DEAD_FROG_MODE draw the frog as a red X
  if(mode==DEAD_FROG_MODE) {
    lc4_draw_sprite(frog_x, (13 - frog_rank)*8, RED, *X_sprite);
  }
  else if(mode==FROG_MADE_IT_MODE) {
    lc4_draw_sprite(frog_x, (13 - frog_rank)*8, YELLOW, *frog_sprite_N);
  }
  else
    switch (frog_orientation){
      case NORTH {
        lc4_draw_sprite(frog_x, (13 - frog_rank)*8, GREEN, *frog_sprite_N);
      }
      case SOUTH {
        lc4_draw_sprite(frog_x, (13 - frog_rank)*8, GREEN, *frog_sprite_S);
      }
      case EAST {
        lc4_draw_sprite(frog_x, (13 - frog_rank)*8, GREEN, *frog_sprite_E);
      }
      case WEST {
        lc4_draw_sprite(frog_x, (13 - frog_rank)*8, GREEN, *frog_sprite_W);
      }
    }
}


void redraw ()
{
  // This function assumes that PennSim is being run in double buffered mode
  // In this mode we first clear the video memory buffer with lc4_reset_vmem,
  // then draw the scene, then call lc4_blt_vmem to swap the buffer to the screen
  // NOTE that you need to run PennSim with the following command:
  // java -jar PennSim.jar -d

  lc4_reset_vmem();

  draw_lily_pads ();
  draw_logs ();
  draw_safe_zone ();
  draw_traffic ();
  draw_home_row ();

  draw_frog ();

  lc4_blt_vmem();
}


/*
 * #############  CODE THAT ADVANCES GAME STATE ######################
 */

void reset_game_state()
{
  frog_rank = 0;
  frog_x = 60;
  frog_orientation = NORTH;
  nfrogs = NUMBER_OF_LIVES;
  mode = PLAYING_MODE;

  // Initialize traffic pattern
  init_pattern (traffic + 0, 40, 16, 40, 16, 20, 16, 40, 16, 30, 16,   0,  -2);
  init_pattern (traffic + 1, 40, 16, 40, 16, 20, 16, 40, 16, 30, 16,  30,   2);
  init_pattern (traffic + 2, 40, 16, 40, 16, 20, 16, 40, 16, 20, 16,  10,  -2);
  init_pattern (traffic + 3, 40, 16, 40, 16, 20, 16, 40, 16, 50, 16,  50,   2);
  init_pattern (traffic + 4, 40, 16, 40, 16, 20, 16, 40, 16, 30, 16,  103, -2);

  
  // Initialize log pattern
  init_pattern (logs + 0, 40, 50, 40, 50, 40, 50, 40, 50, 40, 50,   0,  3);
  init_pattern (logs + 1, 40, 50, 40, 50, 40, 50, 40, 50, 40, 50,  50, -3);
  init_pattern (logs + 2, 40, 50, 40, 50, 40, 50, 40, 50, 40, 50,  93, -5);
  init_pattern (logs + 3, 40, 50, 40, 30, 40, 50, 20, 50, 40, 30,  20,  5);
  init_pattern (logs + 4, 40, 50, 40, 50, 40, 50, 40, 50, 40, 50,  64, -4);
 
  // Initialize lily pad
  init_pattern (&lily_pads, 0, 15, 14, 14, 14, 14, 14, 14, 14, 15,  0,  0);
}

void update_frog (lc4uint event)
{
  // YOUR CODE HERE
  // remember that when the frog is on a log its position may need to be updated as the log moves
  switch(event) {
    case 
  }
}

void update_highway_and_river ()
{
  // YOUR CODE HERE
  // Update the offsets of the logs and traffic patterns
}

int frog_ok ()
{
  // YOUR CODE HERE

  /* Check if the frog fell off the screen */

  /* Check if the frog got hit by a truck */
   
  /* Check if the frog fell in the river */
 
  /* Check if the frog missed the landing slots */
}

void update_game_state (lc4uint event)
{
  if (mode == PLAYING_MODE) {

    update_frog (event);

    // Handle a timer event
    if (event == 0) {
      update_highway_and_river();
    }

    // Check if our frog is O.K.
    if (frog_ok()) {
      if (frog_rank == 12) {
	lc4_puts ((lc4uint*)"You made it all the way across!!\n");
	delay_counter = 6;
	mode = FROG_MADE_IT_MODE;
      }
    } else {
      lc4_puts ((lc4uint*)"  Your frog is dead, bummer :-( \n");
      delay_counter = 6;
      mode = DEAD_FROG_MODE;
    }

    return;
  }

  /* Mode where we mourn the passing of our dearly beloved frog */
  if (mode == DEAD_FROG_MODE) {
    /* Wait a decent interval */
    if (!(delay_counter--)) {
      if (--nfrogs) {
	/* If you have frogs left keep playing */
	frog_rank = 0;
	frog_x = 60;
	mode = PLAYING_MODE;
      } else {
	mode = END_MODE;
	lc4_puts ((lc4uint*)"All of your frogs are dead\n");
	lc4_puts ((lc4uint*)"Press r to restart\n");
      }
    }
    return; 
  }

  /* Mode where we celebrate the fact that our brave frog has made
   * it safely through all the hazards and acheived frog nirvana
   */
  if (mode == FROG_MADE_IT_MODE) {
    /* Wait a decent interval */
    if (!(delay_counter--)) {
      /* Reset frog and keep playing */
      frog_rank = 0;
      frog_x = 60;
      mode = PLAYING_MODE;
    }
    return;
  }

  if (mode == END_MODE) {
    if (event == 'r') {
      reset_game_state();
    }
    return;
  }
}

/*
 * #############  MAIN PROGRAM ######################
 */

int main ()
{
  lc4uint event;

  lc4_puts ((lc4uint*)"!!! Welcome to Frogger !!!\n");
  lc4_puts ((lc4uint*)"Press j to go left\n");
  lc4_puts ((lc4uint*)"Press k to go up\n");
  lc4_puts ((lc4uint*)"Press l to go right\n");
  lc4_puts ((lc4uint*)"Press m to go down\n");

  reset_game_state();

  redraw ();
  
  while (1) {
    event = lc4_get_event();

    update_game_state(event);

    redraw ();
  }

  return 0;
}
