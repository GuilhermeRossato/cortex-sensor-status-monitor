#ifndef P
	#define P(l,i,v)	GPIO##l->BSRR = 1<<(i+((!v)*16))
	#define R(l,i)		((GPIO##l->IDR & (1<<i))>0)
#endif

void delayMicroseconds(int n) {
	long x = 10*n;
	while (x-->0);
}

#define SCL 2
#define SDA 3
#define DELAY delayMicroseconds(500)

enum {
	RESETED,
	READY,
	WAITING_TEMP,
	WAITING_HUMID,
	WAITING_C1,
	WAITING_C2,
	SHT_ERROR
} sht_state = RESETED;

void start_i2c_SHT(void) {
	P(G, SCL, 0);
	P(G, SDA, 1);
	DELAY;
	P(G, SCL, 1);
	DELAY;
	P(G, SDA, 0);
	DELAY;
	P(G, SCL, 0);
	DELAY;
	P(G, SCL, 1);
	DELAY;
	P(G, SDA, 1);
	DELAY;
	P(G, SCL, 0);
	DELAY;
	P(G, SDA, 0);
	DELAY;
}

void stop_i2c(void) {
	P(G, SDA, 0);
	DELAY;
	P(G, SCL, 0);
	DELAY;
	P(G, SCL, 1);
	DELAY;
	P(G, SDA, 1);
}

void envia_bit_i2c(int bit) {
	//
	//  SCL ___/¯\___
	//  SDA xBBBBBBBB
	//
	P(G, SDA, bit);
	DELAY;
	P(G, SCL, 1);
	DELAY;
	P(G, SCL, 0);
	DELAY;
}

void set_SDA_as_input() {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_3; // SDA => PG.2
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; //FAZ SDA COMO ENTRADA
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

void set_SDA_as_output() {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_3; // SDA => PG.2
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; //FAZ SDA COMO SAIDA
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

int read_ack_i2c(void) {
	int x;
	set_SDA_as_input();
	P(G, SCL, 1);
	DELAY;
	x = R(G, SDA);
	DELAY;
	P(G, SCL, 0);
	DELAY;
	set_SDA_as_output();
	return x; //se 0 ok, se 1 erro
}

unsigned char le_byte_i2c() {
	unsigned char accum = 0;
	set_SDA_as_input();
	for (unsigned char i = 0 ; i < 8; i++) {
		P(G, SCL, 1);
		DELAY;
		unsigned char bit = R(G, SDA);
		accum |= bit << (7-i);
		P(G, SCL, 0);
		DELAY;
	}
	set_SDA_as_output();
	DELAY;
	P(G, SDA, 0); // ack
	P(G, SCL, 1);
	DELAY;
	P(G, SCL, 0);
	DELAY;
	return accum;
}

void envia_byte_i2c(int dado) {
	for (int i=0;i<8;i++) {
		envia_bit_i2c((dado >> (7-i)) % 2);
	}
}



int SHT_raw_read() {
	unsigned char b1, b2;
	start_i2c_SHT();
	envia_byte_i2c(0x05);
	int ack = read_ack_i2c();
	if (ack == 1) { return -1; }
	HAL_Delay(20);
	set_SDA_as_input();
	int count = 0;
	while (count < 80 && R(G, SDA)) {
		count++;
		HAL_Delay(1);
	}
	if (count >= 80) { set_SDA_as_output(); return -2; }
	if (count < 1) { set_SDA_as_output(); return -3; }
	set_SDA_as_output();
	b1 = le_byte_i2c();
	b2 = le_byte_i2c();
	return (b1 << 8) + b2;
}

double SHT_read_humid() {
	static unsigned long started_time = 0;
	if (sht_state == SHT_ERROR) {
		return -3;
	}
	if (sht_state == RESETED) {
		start_i2c_SHT();
		sht_state = READY;
	}
	
	if (sht_state == READY) {
		envia_byte_i2c(0x05);
		int ack = read_ack_i2c();
		if (ack == 1) { 
			started_time = HAL_GetTick()+10000;
			sht_state = SHT_ERROR;
		} else {
			started_time = HAL_GetTick();
			sht_state = WAITING_HUMID;
		}
	}
	if (sht_state == WAITING_HUMID) {
		if (HAL_GetTick() - started_time > 80) {
			unsigned char b1, b2;
			b1 = le_byte_i2c();
			b2 = le_byte_i2c();
			sht_state = READY;
			double raw = (b1 << 8) + b2;
			return -2.0468F+0.0367*raw-1.5955E-6*raw*raw;
		} else {
			return -2; // waiting
		}
	}
	return -1; // unhandled state
}
