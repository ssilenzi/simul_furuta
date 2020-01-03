#include "keys.h"

// Variabili extern
extern ref_t				ref_pc;
extern pthread_mutex_t 		mux_ref_pc;
extern state_pc_t 			state_pc;
//extern State 				state_board;
extern state_board_t 		state_board;
//extern State 				state_reset;
extern state_board_t 		state_board_reset;
extern pthread_mutex_t 		mux_state_pc;
extern pthread_mutex_t 		mux_state_board;
extern View 				view;
extern pthread_mutex_t 		mux_view;
extern par_ctrl_t 			par_control_pc;
extern par_ctrl_t 			par_control_reset;
extern pthread_mutex_t 		mux_parcontr_pc;
//extern int 					brake;
//extern pthread_mutex_t 		mux_brake;
//extern int 					swingup;
//extern pthread_mutex_t		mux_swingup;
extern dn_t dn;
extern par_dn_t par_dn;


extern int dl_miss_keys;

extern int end;

void* keys(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	char ascii, scan;
	while(!end){
		if (keypressed()) {  		// importante altrimenti readkey blocca l'esecuzione
			get_keycodes(&scan, &ascii);
			
			
			// ESC, end Threads e conseguente chiusura del programma
			if (scan==KEY_ESC) {
				end = 1;
			}
			
			// R, reset state_pc e ref_pc
			if (scan == KEY_R) {
				//Devo resettare per forza state_board, il flusso di update su state e`: board -> buffer -> pc
				
				pthread_mutex_lock(&mux_state_board);
					state_board = state_board_reset;
				pthread_mutex_unlock(&mux_state_board);
				
				pthread_mutex_lock(&mux_ref_pc);
					ref_pc.alpha = ALPHA_0;
					ref_pc.theta = THETA_0;
				pthread_mutex_unlock(&mux_ref_pc);
				
			}
			
			// W, attiva/disattiva il motore
			if (scan == KEY_W){
				/*
				pthread_mutex_lock(&mux_brake);
				if(brake){
					brake = 0;
				}else{
					brake = 1;
				}
				pthread_mutex_unlock(&mux_brake);
				*/
				
			}
			
			// Q, attiva/disattiva controllore di swingup
			if (scan == KEY_Q){
				/*
				pthread_mutex_lock(&mux_swingup);
				if(swingup){
					swingup = 0;
				}else{
					swingup = 1;
				}
				pthread_mutex_unlock(&mux_swingup);
				*/
				pthread_mutex_lock(&mux_ref_pc);
				if(ref_pc.swingup){
					ref_pc.swingup = 0;
				}else{
					ref_pc.swingup = 1;
				}
				pthread_mutex_unlock(&mux_ref_pc);

			}
			
			/*
			 * Par_control
			 */
			
			// alpha kp
			if(scan == KEY_Y){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kp_alpha += INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			if(scan == KEY_U){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kp_alpha += -INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			// alpha kd
			if(scan == KEY_I){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kd_alpha += INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			if(scan == KEY_O){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kd_alpha += -INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			
			// theta kp
			if(scan == KEY_H){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kp_theta += INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			if(scan == KEY_J){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kp_theta += -INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			// theta kd
			if(scan == KEY_K){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kd_theta += INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			if(scan == KEY_L){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.up_kd_theta += -INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			
			// swingup
			/*
			 * if(scan == KEY_N){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.ksu += INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			if(scan == KEY_M){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc.ksu += -INCR_K;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			*/
			
			// E, reset par_control_pc
			if(scan == KEY_E){
				pthread_mutex_lock(&mux_parcontr_pc);
					par_control_pc = par_control_reset;
				pthread_mutex_unlock(&mux_parcontr_pc);
			}
			
			
			/*
			*      RIFERIMENTO
			*/
			// A, incrementa riferimento di alpha
			if (scan==KEY_A) {
				pthread_mutex_lock(&mux_ref_pc);
					ref_pc.alpha += INCR_ANG;
				pthread_mutex_unlock(&mux_ref_pc);
			}
			// S, diminuisce riferimento di alpha
			if (scan==KEY_S) {
				pthread_mutex_lock(&mux_ref_pc);
					ref_pc.alpha += -INCR_ANG;
				pthread_mutex_unlock(&mux_ref_pc);
			}
			
			
			/*
			*      VIEW
			*/ 
			// reset vista
			if (scan==KEY_T) {
				pthread_mutex_lock(&mux_view);
					view.lon = LON_0;
					view.lat = LAT_0;
				pthread_mutex_unlock(&mux_view);
				
			}
			
			//VIEW_LAT up down
			if (scan==KEY_UP) {
				pthread_mutex_lock(&mux_view);
				if (view.lat + INCR_ANG <= LAT_MAX) {
					view.lat += INCR_ANG;
				}
				pthread_mutex_unlock(&mux_view);
				
			}
			if (scan==KEY_DOWN) {
				pthread_mutex_lock(&mux_view);
				if (view.lat + -INCR_ANG >= -LAT_MAX) {
					view.lat += -INCR_ANG;
				}
				pthread_mutex_unlock(&mux_view);

			}
			// VIEW_LON left right
			if (scan==KEY_LEFT) {
				pthread_mutex_lock(&mux_view);
					view.lon += -INCR_ANG;
				pthread_mutex_unlock(&mux_view);			
				
			}
			if (scan==KEY_RIGHT) {
			pthread_mutex_lock(&mux_view);
				view.lon += +INCR_ANG;
			pthread_mutex_unlock(&mux_view);				
			}
		} // end keypressed

	// end of task
	if(deadline_miss(id)){
			dl_miss_keys+=1;
	}
	wait_for_period(id);			// wait to next period
	
	}
	return 0;
}


// get_keycodes
void get_keycodes(char *scan, char *ascii)
{
	// The following function waits for a key pressed and extracts
	// the corresponding ASCII code and scan code:
	int k;
	k = readkey(); // block until a key is pressed
	*ascii = k; // get ASCII code
	*scan = k >> 8; // get scan code
}

/*// get_string
void get_string(char *str, int x, int y, int c, int b)
{
	// The following function reads a string from the keyboard and displays
	// the echo in graphic mode at position (x,y), color c and background b:
	char ascii, scan, s[2];
	int i = 0;
	do {
		get_keycodes(&scan, &ascii);
		if (scan != KEY_ENTER) {
			s[0] = ascii; // put ascii in s for echoing
			s[1] = '\0';
			textout_ex(screen, font, s, x, y, c, b); // echo
			x = x + 8;
			str[i++] = ascii; // insert character in string
		}
	} while (scan != KEY_ENTER);

		str[i] = '\0';
}*/
