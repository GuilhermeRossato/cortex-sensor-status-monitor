
#define SLIDER_COUNT 5

typedef struct {
	unsigned char selected;
	unsigned char state;
	enum {
		DESACTIVATED_SLIDER,
		SINGLE_SLIDER,
		DOUBLE_SLIDER
	} type;
	int x, y;
	int v[3];
	int selection;
} slider_component;

int selected_slider = -1;

int absolute_value(int i) {
	return (i < 0)?-i:i;
}

slider_component sliders[SLIDER_COUNT];

int get_slider_on_mouse(int x, int y) {
	int i, id = -1;
	for (i = 0; i < SLIDER_COUNT; i++) {
		if (sliders[i].type != DESACTIVATED_SLIDER &&
		    (x > sliders[i].x-5) &&
			(x < sliders[i].x+220+5) &&
			(y > sliders[i].y-5) &&
			(y < sliders[i].y+40+5)) {
			id = i;
			break;
		}
	}
	return id;
}

void init_slider(int id, int x, int y, int type) {
	sliders[id].type = (type == 1) ? SINGLE_SLIDER : ((type == 2) ? (DOUBLE_SLIDER) : (DESACTIVATED_SLIDER));
	sliders[id].x = x;
	sliders[id].y = y;
}

void set_slider_values(int id, int v0, int v1, int v2) {
	sliders[id].v[0] = v0;
	sliders[id].v[1] = v1;
	sliders[id].v[2] = v2;
}
const unsigned char control_middle[294]= { 0x42,0x4d,0x26,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00, 0x00,0x00,0x0a,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x03,0x00, 0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x9e,0xf7,0x7d,0xef,0x18,0xc6,0xf3,0x9c,0x31,0x8c, 0x10,0x84,0xf4,0xa4,0xf8,0xc5,0x7e,0xf7,0x7e,0xf7,0x1c,0xe7,0xb3,0x9c,0x71,0x8c,0xb3,0x9c,0xf3,0x9c,0xf4,0xa4,0xb2,0x94,0x72,0x94,0xb2,0x94,0x1c,0xe7,0xb3,0x9c, 0xd3,0x9c,0x96,0xb5,0x76,0xb5,0x96,0xb5,0x76,0xb5,0x96,0xb5,0x76,0xb5,0xd3,0x9c,0xb2,0x94,0x92,0x94,0x18,0xc6,0xf8,0xc5,0xdb,0xde,0x9e,0xf7,0x9e,0xf7,0xdb,0xde,0x18,0xc6,0xf7,0xbd,0xb3,0x8c,0xf8,0xc5,0x9a,0xd6,0x9a,0xd6,0xfc,0xe6,0x9a,0xd6,0x7a,0xd6,0x1c,0xe7,0x9a,0xd6,0x9a,0xd6,0xd8,0xb5,0xfb,0xde,0x1c,0xe7,0xfb,0xde,0x55,0xad,0xf4,0xa4,0x14,0xa5,0x55,0xad,0x1c,0xe7,0xfc,0xe6,0xdb,0xde,0x5d,0xef,0x7d,0xef,0x7e,0xf7,0xef,0x7b,0xaf,0x7b,0xae,0x73,0x10,0x84,0x7d,0xef,0x7e,0xf7,0x5d,0xef,0x9a,0xd6,0xbf,0xff,0xbe,0xf7,0xb7,0xbd,0x28,0x42,0x29,0x4a,0xb6,0xb5,0xbf,0xff,0xbe,0xf7,0x9a,0xd6,0xb7,0xbd,0xdf,0xff,0xff,0xff,0xdf,0xff,0xff,0xff,0xdf,0xff,0xff,0xff,0xdf,0xff,0xff,0xff,0xb6,0xb5,0xb2,0x94,0x18,0xc6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x18,0xc6,0xb3,0x9c,0x3c,0xe7,0xb2,0x94,0xd7,0xbd,0x1c,0xe7,0xff,0xff,0xff,0xff,0x1c,0xe7,0xb7,0xbd,0xd3,0x9c,0x1c,0xe7,0x7d,0xef,0x7d,0xef,0x18,0xc6,0xf4,0xa4,0x10,0x84,0x30,0x84,0xd3,0x9c,0x18,0xc6,0x5d,0xef,0x9e,0xf7 };
const unsigned char left_background[94]= { 0x42,0x4d,0x5e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x03,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0xce,0x14,0xa5,0x34,0xa5,0x55,0xad,0xd3,0x9c,0x55,0xad,0xb7,0xbd,0xb6,0xb5,0x51,0x8c,0x55,0xad,0x95,0xb5,0xb6,0xb5,0xcf,0x7b,0x51,0x8c,0xf3,0xa4,0xf3,0xa4,0x38,0xc6,0xcf,0x7b,0x2c,0x63,0x4d,0x6b };
const unsigned char right_background[94]= {0x42,0x4d,0x5e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x03,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x34,0xa5,0x14,0xa5,0x71,0x94,0x39,0xce,0xd7,0xbd,0x96,0xb5,0xf4,0xa4,0xef,0x7b,0x96,0xb5,0x75,0xad,0xb2,0x94,0x4d,0x6b,0xf4,0xa4,0x92,0x94,0xcf,0x7b,0x0c,0x63,0x2c,0x63,0x0c,0x63,0x8e,0x73,0x39,0xce};

void draw_slider(int id) {
	int pos_x = sliders[id].x;
	int pos_y = sliders[id].y;
	int v0 = sliders[id].v[0];
	int v1 = sliders[id].v[1];
	if (sliders[id].type == SINGLE_SLIDER) {
		
	} else if (sliders[id].type == DOUBLE_SLIDER) {
		/* Clearing */
		BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
		BSP_LCD_FillRect(pos_x, pos_y, 220, 40);
		/* Drawing background lines */
		BSP_LCD_SetTextColor(0xFF686868);
		BSP_LCD_DrawHLine(pos_x, pos_y+18, 220);
		BSP_LCD_SetTextColor(0xFF9D9D9D);
		BSP_LCD_DrawHLine(pos_x, pos_y+19, 220);
		BSP_LCD_SetTextColor(0xFFB2B2B2);
		BSP_LCD_DrawHLine(pos_x, pos_y+20, 220);
		BSP_LCD_SetTextColor(0xFFB6B6B6);
		BSP_LCD_DrawHLine(pos_x, pos_y+21, 220);
		BSP_LCD_SetTextColor(0xFFA7A7A7);
		BSP_LCD_DrawHLine(pos_x, pos_y+22, 220);
		if (v1 - v0 > 11) {
			/* Drawing active section */
			int lx = v1-5-(pos_x+v0);
			BSP_LCD_SetTextColor(0xFF0D6087);
			BSP_LCD_DrawHLine(pos_x+v0+5, pos_y+18, lx);
			BSP_LCD_SetTextColor(0xFF0D91CC);
			BSP_LCD_DrawHLine(pos_x+v0+5, pos_y+18, lx);
			BSP_LCD_SetTextColor(0xFF0EA4E8);
			BSP_LCD_DrawHLine(pos_x+v0+5, pos_y+18, lx);
			BSP_LCD_SetTextColor(0xFF0EA7EC);
			BSP_LCD_DrawHLine(pos_x+v0+5, pos_y+18, lx);
			BSP_LCD_SetTextColor(0xFF0F99D8);
			BSP_LCD_DrawHLine(pos_x+v0+5, pos_y+18, lx);
		}
		/* Drawing images */
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		
		BSP_LCD_DrawBitmap(pos_x+v0, pos_y+15, (uint8_t*)control_middle);
		BSP_LCD_DrawBitmap(pos_x+v1, pos_y+15, (uint8_t*)control_middle);
		
		BSP_LCD_DrawBitmap(pos_x, pos_y+18, (uint8_t*)left_background);
		BSP_LCD_DrawBitmap(pos_x+220-4, pos_y+18, (uint8_t*)right_background);
	}
}

/* handle each specific slider value */

void on_slider_mouse_down(int id, int x) {
	if (sliders[id].type == SINGLE_SLIDER) {
		sliders[id].selection = 0;
	} else if (sliders[id].type == DOUBLE_SLIDER) {
		int dx0 = absolute_value(x - sliders[id].v[0]),
			dx1 = absolute_value(x - sliders[id].v[1]);
		if (dx0 < dx1) {
			sliders[id].selection = 0;
		} else {
			sliders[id].selection = 1;
		}
	} else {
		sliders[id].selection = -1;
	}
	if (sliders[id].selection != -1) {
		if (sliders[id].selection == 0 && sliders[id].type == DOUBLE_SLIDER && x >= sliders[id].v[1]) { x = sliders[id].v[1]-1; }
		if(sliders[id].selection == 1 && sliders[id].type == DOUBLE_SLIDER && x <= sliders[id].v[0] && sliders[id].v[0]+1 > x) { x = sliders[id].v[0]+1; }
		if (x < 1) { x = 0; }
		if (x > 200) { x = 200; }
		on_slider_value_change(id, sliders[id].selection, x);
		sliders[id].v[sliders[id].selection] = x;
	}
}

void on_slider_mouse_move(int id, int x) {
	if (sliders[id].selection != -1) {
		if (sliders[id].selection == 0 && sliders[id].type == DOUBLE_SLIDER && x >= sliders[id].v[1]) { x = sliders[id].v[1]-1; }
		if(sliders[id].selection == 1 && sliders[id].type == DOUBLE_SLIDER && x <= sliders[id].v[0] && sliders[id].v[0]+1 > x) { x = sliders[id].v[0]+1; }
		if (x < 1) { x = 0; }
		if (x > 219) { x = 219; }
		on_slider_value_change(id, sliders[id].selection, x);
		sliders[id].v[sliders[id].selection] = x;
	}
}

void on_slider_mouse_up(int id, int x) {
	if (sliders[id].selection != -1) {
		sliders[id].selection = -1;
	}
}

/* functions and event handlers called by state machine */

void init_sliders() {
	int i;
	for (i = 0; i < SLIDER_COUNT; i++) {
		sliders[i].state = 0;
		sliders[i].type = DESACTIVATED_SLIDER;
		sliders[i].y = -40;
		sliders[i].selection = -1;
	}
}

void slider_handle_mouse_down(int x, int y) {
	selected_slider = get_slider_on_mouse(x, y);
	if (selected_slider >= 0) {
		on_slider_mouse_down(selected_slider, x-sliders[selected_slider].x);
	}
}
void slider_handle_mouse_move(int x, int y) {
	if (selected_slider != -1) {
		on_slider_mouse_move(selected_slider, x-sliders[selected_slider].x);
	}
}
void slider_handle_mouse_up(int x, int y) {
	if (selected_slider != -1) {
		on_slider_mouse_up(selected_slider, x-sliders[selected_slider].x);
	}
}
