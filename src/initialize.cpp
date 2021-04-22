#include "main.h"
#include "globals.hpp"

static lv_obj_t *g_btn_region; //tab view region of the screen
static lv_obj_t *g_sb_region; //status bar region of the screen
static lv_obj_t *g_sb_label;  // sb text label

int auton_sel = 0;

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt) {

  int btnm_num = atoi(txt);

  switch (btnm_num) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Right Auton");
    auton_sel = 1;
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Left Auton");
    auton_sel = 2;
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Right Auton");
    auton_sel = 3;
break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Left Auton");
    auton_sel = 4;
break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    auton_sel = 5;
break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    auton_sel = 6;
break;
  }

  lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

void gui_btnm(void) {
  // Create a button descriptor string array w/ no repeat "\224"
  static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
                                     "\2244", "\2245", "\2246", "" };

  // Create a default button matrix* no repeat
  lv_obj_t *btnm = lv_btnm_create(g_btn_region, NULL);
  lv_obj_set_size(btnm, lv_obj_get_width(g_btn_region),
      lv_obj_get_height(g_btn_region) - 32);

  lv_btnm_set_map(btnm, btnm_map);
  lv_btnm_set_action(btnm, btnm_action);
}


static lv_res_t btn_click_action(lv_obj_t * btn) {
   uint8_t id = lv_obj_get_free_num(btn);
   static char buffer[32];
   auton_sel = id;

   snprintf(buffer, 32, "Selection is %d \n", id);
   lv_label_set_text(g_sb_label, buffer);
   lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

   return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void gui_3btn(void) {

 /*Create a title label*/
 lv_obj_t * label = lv_label_create(g_btn_region, NULL);
 lv_label_set_text(label, "Selection Buttons");
 lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

 /*Create a normal button*/
 lv_obj_t * btn1 = lv_btn_create(g_btn_region, NULL);
 lv_btn_set_style(btn1,LV_BTN_STYLE_REL,&lv_style_btn_rel);
 lv_btn_set_style(btn1,LV_BTN_STYLE_PR,&lv_style_btn_pr);
 lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 30, 0);
 lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
 lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the button*/
 label = lv_label_create(btn1, NULL);
 lv_label_set_text(label, "Sel 1");

 /*Copy the button and set toggled state. (The release action is copied too)*/
 lv_obj_t * btn2 = lv_btn_create(g_btn_region, btn1);
 lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
 lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
 lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the toggled button*/
 label = lv_label_create(btn2, NULL);
 lv_label_set_text(label, "Sel 2");

 /*Copy the button and set inactive state.*/
 lv_obj_t * btn3 = lv_btn_create(g_btn_region, btn1);
 lv_obj_align(btn3, NULL, LV_ALIGN_IN_RIGHT_MID, -30, 0);
 lv_obj_set_free_num(btn3, 3);                  /*Set a unique number for the button*/
 lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the inactive button*/
 label = lv_label_create(btn3, NULL);
 lv_label_set_text(label, "Sel 3");
}

static lv_res_t switch_action (lv_obj_t * sw) {
  uint8_t id = lv_obj_get_free_num(sw);
  static char buffer[32];

  snprintf(buffer, 32, "SW%d Toggled to %s\n",id,lv_sw_get_state(sw)?"On":"Off");
  lv_label_set_text(g_sb_label, buffer);
  lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void set_switch_style (lv_obj_t * sw) {
  /*Create styles for the switch*/
  static lv_style_t bg_style;
  static lv_style_t indic_style;
  static lv_style_t knob_on_style;
  static lv_style_t knob_off_style;

  lv_style_copy(&bg_style, &lv_style_pretty);
  bg_style.body.radius = LV_RADIUS_CIRCLE;

  lv_style_copy(&indic_style, &lv_style_pretty_color);
  indic_style.body.radius = LV_RADIUS_CIRCLE;
  indic_style.body.main_color = LV_COLOR_HEX(0x9fc8ef);
  indic_style.body.grad_color = LV_COLOR_HEX(0x9fc8ef);
  indic_style.body.padding.hor = 0;
  indic_style.body.padding.ver = 0;

  lv_style_copy(&knob_off_style, &lv_style_pretty);
  knob_off_style.body.radius = LV_RADIUS_CIRCLE;
  knob_off_style.body.main_color = LV_COLOR_RED;
  knob_off_style.body.grad_color = LV_COLOR_MAROON; //misspelled should be MAROON
  knob_off_style.body.shadow.width = 4;
  knob_off_style.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_style_copy(&knob_on_style, &lv_style_pretty_color);
  knob_on_style.body.radius = LV_RADIUS_CIRCLE;
  knob_on_style.body.main_color = LV_COLOR_LIME;
  knob_on_style.body.grad_color = LV_COLOR_GREEN;
  knob_on_style.body.shadow.width = 4;
  knob_on_style.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_sw_set_style(sw, LV_SW_STYLE_BG, &bg_style);
  lv_sw_set_style(sw, LV_SW_STYLE_INDIC, &indic_style);
  lv_sw_set_style(sw, LV_SW_STYLE_KNOB_ON, &knob_on_style);
  lv_sw_set_style(sw, LV_SW_STYLE_KNOB_OFF, &knob_off_style);
}

void gui_switch(void) {
  /*Create a title label*/
  lv_obj_t * label = lv_label_create(g_btn_region, NULL);
  lv_label_set_text(label, "Flip Switches");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

  lv_obj_t * sw1 = lv_sw_create(g_btn_region, NULL);
  lv_obj_set_free_num(sw1, 1);                  /*Set a unique number for the object*/
  set_switch_style(sw1);  // style is in separate function for cleaner code
  lv_obj_align(sw1, NULL, LV_ALIGN_IN_LEFT_MID, 50, 0);

  lv_obj_t * sw2 = lv_sw_create(g_btn_region, sw1); // copy sw1 to sw2
  lv_obj_set_free_num(sw2, 2);                  /*Set a unique number for the object*/
  lv_obj_align(sw2, NULL, LV_ALIGN_IN_RIGHT_MID, -50, 0);

  // both switches use the same call back function
  lv_sw_set_action(sw1, switch_action);
  lv_sw_set_action(sw2, switch_action);
}

lv_obj_t * gauge1;
lv_obj_t * gauge2;
lv_obj_t * gauge3;

void gui_gauges(void) {
  /*Create a style*/
  static lv_style_t style;
  lv_style_copy(&style, &lv_style_pretty_color);
  style.body.main_color = LV_COLOR_HEX3(0x666);     /*Line color at the beginning*/
  style.body.grad_color =  LV_COLOR_HEX3(0x666);    /*Line color at the end*/
  style.body.padding.hor = 10;                      /*Scale line length*/
  style.body.padding.inner = 8 ;                    /*Scale label padding*/
  style.body.border.color = LV_COLOR_HEX3(0x333);   /*Needle middle circle color*/
  style.line.width = 2;
  style.text.color = LV_COLOR_HEX3(0x333);
  style.line.color = LV_COLOR_RED;                  /*Line color after the critical value*/

  /*Describe the color for the needles*/

  /*Create a gauge*/
  lv_coord_t gauge_size =  lv_obj_get_width(lv_scr_act())/3-10;
  gauge1 = lv_gauge_create(lv_scr_act(), NULL);
  lv_gauge_set_style(gauge1, &style);
  lv_obj_set_size(gauge1, gauge_size, gauge_size);
  lv_obj_align(gauge1, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

  /*Create a gauge*/
  gauge2 = lv_gauge_create(lv_scr_act(), NULL);
  lv_gauge_set_style(gauge2, &style);
  lv_obj_set_size(gauge2, gauge_size, gauge_size);
  lv_obj_align(gauge2, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

  /*Create a gauge*/
  gauge3 = lv_gauge_create(lv_scr_act(), NULL);
  lv_gauge_set_style(gauge3, &style);
  lv_obj_set_size(gauge3, gauge_size, gauge_size);
  lv_obj_align(gauge3, NULL, LV_ALIGN_IN_TOP_RIGHT, -5, 10);

}

void gauge_update(void* param) {
  /*Set the values*/
  int i=23;
  while (1) {
    lv_gauge_set_value(gauge1, 0, 1*i%100);
    lv_gauge_set_value(gauge1, 1, i%2?40:50);
    lv_gauge_set_value(gauge2, 0, 2*i%100);
    lv_gauge_set_value(gauge3, 0, 3*i%100);
    pros::Task::delay(1000);
    i++;
  }
}

uint8_t demo_id = 0;



////////////////////////////////////////////////////////////////////////////////////////

lv_obj_t * createLabel(int x, int y, std::string text_, lv_obj_t * parent) {
  lv_obj_t * label = lv_label_create(parent, NULL);
  lv_obj_set_pos(label, x, y);
  lv_label_set_text(label, text_.c_str());

  // if(style != nullptr)
  //   lv_label_set_style(label, style);
  // else
  //   lv_label_set_style(label, &lv_style_plain);

  return label;
}

lv_obj_t * createButton(int id, int x, int y, int width, int height, std::string text, lv_action_t action, lv_style_t * btn_pr, lv_style_t * btn_rel) {
  lv_obj_t * button = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_pos(button, x, y);
  lv_obj_set_size(button, width, height);
  lv_obj_set_free_num(button, id);
  lv_btn_set_action(button, LV_BTN_ACTION_CLICK, action);

  if(btn_pr != nullptr || btn_rel != nullptr) {
    lv_btn_set_style(button, LV_BTN_STYLE_PR, btn_pr);
    lv_btn_set_style(button, LV_BTN_STYLE_REL, btn_rel);
  } else {
    lv_btn_set_style(button, LV_BTN_STYLE_PR, lv_theme_get_current()->btn.pr);
    lv_btn_set_style(button, LV_BTN_STYLE_REL, lv_theme_get_current()->btn.rel);
  }

  lv_obj_t * buttonLabel = createLabel(0, 0, text, button);
  lv_obj_align(buttonLabel, button, LV_ALIGN_CENTER, 0, 0);
  return button;
}

lv_obj_t * createSwitch( int id, int x, int y, int width, int height, lv_action_t action, lv_style_t * sw_on, lv_style_t * sw_off ){
  lv_obj_t * swtch = lv_sw_create( lv_scr_act(), NULL );
  lv_obj_set_pos(swtch, x, y);
  lv_obj_set_size(swtch, width, height);
  lv_obj_set_free_num(swtch, id);
  lv_sw_set_action(swtch, action);

  if(sw_on != nullptr || sw_off != nullptr) {
    lv_sw_set_style(swtch, LV_SW_STYLE_KNOB_ON, sw_on);
    lv_sw_set_style(swtch, LV_SW_STYLE_KNOB_OFF, sw_off);
  } else {
    lv_sw_set_style(swtch, LV_SW_STYLE_KNOB_ON, lv_theme_get_current()->sw.knob_on);
    lv_sw_set_style(swtch, LV_SW_STYLE_KNOB_OFF, lv_theme_get_current()->sw.knob_off);
  }

  return swtch;
}

lv_obj_t * createSlider( int id, int x, int y, int width, int height, int min, int max, lv_action_t action, lv_style_t * style ) {
  lv_obj_t * slider = lv_slider_create( lv_scr_act(), NULL );
  lv_obj_set_pos(slider, x, y);
  lv_obj_set_size(slider, width, height);
  lv_obj_set_free_num(slider, id);
  lv_slider_set_action(slider, action);
  lv_slider_set_range(slider, min, max);

  return slider;
}

////////////////////////////////////////////////////////////////////////

static lv_res_t match_action( lv_obj_t * obj ) {
  switch( lv_obj_get_free_num(obj) ) {
    case 1:
    break;
    case 2:
    break;
  }

  return LV_RES_OK;
}


void matchGUI() {
  lv_style_t st1;
  lv_style_copy (&st1, &lv_style_plain);
  st1.text.color = LV_COLOR_WHITE;
  st1.text.font = &lv_font_symbol_20;

  lv_obj_t * color_label = createLabel ( 30, 60, "R             B", lv_scr_act());
    lv_obj_set_style(color_label, &st1);
  lv_obj_t * color_sw   =  createSwitch( 4, 50, 60, 80, 40, match_action, &lv_style_plain, &lv_style_plain );
  lv_obj_t * side_label =  createLabel ( 30, 120, "L             R", lv_scr_act());
  lv_obj_t * side_sw    =  createSwitch( 5, 50, 120, 80, 40, match_action, &lv_style_plain, &lv_style_plain );
  lv_obj_t * goals_sldr =  createSlider( 6, 30, 200, 50, 20, 1, 6, match_action, &lv_style_pretty );

}

void skillsGUI() {

}

void noAutonGUI() {

}

static lv_res_t matchType_btn_action( lv_obj_t * btn ) {
  switch( lv_obj_get_free_num(btn) ) {
    case 1:
      matchGUI();
    break;
    case 2:
      skillsGUI();
    break;
    case 3:
      noAutonGUI();
    break;
  }

  return LV_RES_OK;
}

void selectionGUI() {
    //                                     id x    y   w    h   label     action                pr style          rel style
    lv_obj_t * match_btn   = createButton( 1, 10,  10, 150, 30, "MATCH",  matchType_btn_action, &lv_style_btn_pr, &lv_style_btn_rel );
    lv_obj_t * skills_btn  = createButton( 2, 165, 10, 150, 30, "SKILLS", matchType_btn_action, &lv_style_btn_pr, &lv_style_btn_rel );
    lv_obj_t * noAuton_btn = createButton( 3, 320, 10, 150, 30, "NONE",   matchType_btn_action, &lv_style_btn_pr, &lv_style_btn_rel );
}

////////////////////////
//   GEORGES STUFF   //
///////////////////////
std::string autons[8] = {"RED single7", "BLUE single7", "RED single6", "BLUE single6", "DEPLOY", "WIP 1pt", "Blue Climb", "Red Climb"};

int state = 0;

lv_res_t stateSet(lv_obj_t * ddlist) {
	std::cout << "ran\n";
	char sel_str[32];
	uint8_t id = lv_obj_get_free_num(ddlist);
	lv_ddlist_get_selected_str(ddlist, sel_str);
	std::string str(sel_str);
	//std::cout << str;
	std::cout << "\n";

	for(int i = 0; i < 8; i++) {
		std::cout << "check loop on pass: " << i << ".\n";
		if(str == autons[i]) {
			state = i;
			std::cout << str << " pressed. " << autons[i] << " selected. State set to " << state << 	".\n";
			break;
		}
	}
	std:std::cout << "\n";
	return LV_RES_OK;
}

void screens() {	//this can actually just be a function i think. this was setup as a task for the speedometer code not included

	std::string buttons = autons[0] + "\n" + autons[1] + "\n" + autons[2] + "\n" + autons[3] + "\n" + autons[4] + "\n" + autons[5] + "\n" + autons[6] + "\n" + autons[7];

	const char *cstr = buttons.c_str();

	/*Create a style*/
	static lv_style_t style_bg;
	lv_style_copy(&style_bg, &lv_style_pretty_color);
	style_bg.body.shadow.width = 4; /*Enable the shadow*/
	style_bg.text.color = LV_COLOR_WHITE;

	lv_obj_t * ddl1 = lv_ddlist_create(lv_scr_act(), NULL);
	lv_ddlist_set_options(ddl1, cstr);
	lv_obj_align(ddl1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_obj_set_drag(ddl1, true);
	lv_obj_set_drag_throw(ddl1, true);
	lv_obj_set_top(ddl1, true);
	lv_obj_set_free_num(ddl1, 1);               /*Set a unique ID*/
	lv_obj_set_style(ddl1, &style_bg);
	lv_ddlist_set_action(ddl1, stateSet);  /*Set a function to call when anew option is chosen*/
}

void initialize()
{
  Inert.reset();
  while(Inert.is_calibrating())
    pros::delay(10);
  Opt.set_led_pwm(100);

  std::cout << "initialized" << std::endl;

  // screens();
  //
  // profileCtrlY->generatePath({
  //   {7.75_ft,0.75_ft,45_deg},
  //   {8.25_ft,1.25_ft,45_deg},
  //   {11.25_ft, 1_ft, -41_deg}
  //   },
  //   "cg1"
  // );
  //
  // // profileCtrlY->generatePath({
  // //   {9.7_ft, 4.3_ft, 45_deg},
  // //   {12.5_ft, 6.5_ft, 0_deg},
  // //   {12.7_ft, 6.5_ft, 0_deg}
  // //   },
  // //   "sg1"
  // // );
  //
  // profileCtrlY->generatePath({
  //   {9_ft, 6_ft, 90_deg},
  //   {9_ft, 9_ft, 90_deg},
  //   {12_ft, 12_ft, 50_deg}
  //   },
  //   "cg2"
  // );
  //
  // profileCtrlY->generatePath({
  //   {10_ft, 1_ft, 90_deg},
  //   {10_ft, 3_ft, 90_deg},
  //   {8_ft, 6_ft, 135_deg}
  //   },
  //   "sg2"
  // );
  //
  // profileCtrlY->generatePath({
  //   {6_ft, 2_ft, 0_deg},
  //   {9_ft, 2_ft, 0_deg},
  //   {11.25_ft, 0.75_ft, -45_deg}
  //   },
  //   "cg3"
  // );
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // while(true) {
  //   for( pros::Motor m : motors ) {
  //     if(m.is_over_temp() || m.is_over_current())
  //      Control.rumble("-");
  //   }
  // }
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
