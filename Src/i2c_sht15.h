#ifndef P
	#define P(l,i,v)	GPIO##l->BSRR = 1<<(i+((!v)*16))
	#define R(l,i)		((GPIO##l->IDR & (1<<i))>0)
#endif

#define SDA 2
#define SCL 3
#define DELAY HAL_Delay(1)

void start_i2c_SHT(void) {
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
	P(G, SDA, bit);
	DELAY;
	P(G, SCL, 1);
	DELAY;
	P(G, SCL, 0);
	DELAY;
}

void set_SDA_as_input() {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_2; // SDA => PG.2
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; //FAZ SDA COMO ENTRADA
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}
void set_SDA_as_output() {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_2; // SDA => PG.2
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
	DELAY;
	return accum;
}

void envia_byte_i2c(int dado) {
	for (int i=0;i<8;i++) {
		envia_bit_i2c(dado%2);
		dado = dado >> 1;
	}
}

int SHT_read_humid() {
	unsigned char b1, b2;
	start_i2c_SHT();
	envia_byte_i2c(0x05);
	if (read_ack_i2c()) { return 0; }
	HAL_Delay(80);
	b1 = le_byte_i2c();
	b2 = le_byte_i2c();
	le_byte_i2c();
	return (b1 << 16) + b2;
}
