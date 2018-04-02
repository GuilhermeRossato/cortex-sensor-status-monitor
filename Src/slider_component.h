
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
		    (x > sliders[i].x) &&
			(x < sliders[i].x+200) &&
			(y > sliders[i].y) &&
			(y < sliders[i].y+40)) {
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

void draw_slider(int id) {
	int left_x = sliders[id].x;
	if (sliders[id].type == SINGLE_SLIDER) {

	} else if (sliders[id].type == DOUBLE_SLIDER) {

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
		sliders[id].v[sliders[id].selection] = x;
	}
}

void on_slider_mouse_move(int id, int x) {
	if (sliders[id].selection != -1) {
		sliders[id].v[sliders[id].selection] = x;
	}
}

void on_slider_mouse_up(int id, int x) {
	if (sliders[id].selection != -1) {
		sliders[id].v[sliders[id].selection] = x;
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