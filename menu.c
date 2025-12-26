#include "neslib.h"
#include <stdint.h>

enum {
	MENU_BT,
	MENU_BTDD
};

extern const unsigned char chr_data[1536];

unsigned int cursor_pos = MENU_BT;
static unsigned char pad;

const char text_title[] = "      SELECT GAME:";
const char text_bt[]    = "BATTLETOADS";
const char text_btdd[]  = "BATTLETOADS & DOUBLE DRAGON";

void load_chr_ram(const unsigned char* data, unsigned int size, unsigned int adr) {
	unsigned int i;
	
	vram_adr(adr);

    for (i = 0; i < size; i++) {
        vram_put(data[i]);
    }
}

void put_str(unsigned int adr, const char* str) {

	vram_adr(adr);
	
	while(1) {
		if(!*str) break;
		vram_put((*str++)-0x20);
	}
}

void set_colors(void) {
	pal_col(0,0x0f);
	pal_col(1,0x21);
	pal_col(2,0x31);
	pal_col(3,0x11);
}

void draw_menu(void) {
	set_colors();
	put_str(NTADR_A(4, 8), text_title);
    put_str(NTADR_A(4, 10), text_bt);
    put_str(NTADR_A(4, 12), text_btdd);
}

void set_cursor(unsigned char sprite1, unsigned char sprite2) {
	unsigned char vram_buffer[7];
	unsigned short adr1 = NTADR_A(2, 10);
	unsigned short adr2 = NTADR_A(2, 12);

	vram_buffer[0] = MSB(adr1);
	vram_buffer[1] = LSB(adr1);
	vram_buffer[2] = sprite1;

	vram_buffer[3] = MSB(adr2);
	vram_buffer[4] = LSB(adr2);
	vram_buffer[5] = sprite2;

	vram_buffer[6] = NT_UPD_EOF;

	set_vram_update(vram_buffer);
}

void update_cursor(void) {
	switch(cursor_pos) {
		case MENU_BT: { set_cursor(0x1e, 0x00); break; }
		case MENU_BTDD: { set_cursor(0x00, 0x1e); break; }
	};
}

void cursor_pos_dec() {
	if(cursor_pos <= MENU_BT) return;
	cursor_pos--;
}

void cursor_pos_inc() {
	if (cursor_pos >= MENU_BTDD) return;
	cursor_pos++;
}

void jump_to_game(unsigned char game_number) {
	*((unsigned char*)0x8000) = game_number;
     ((void (*)(void))0x8000)();
}

void main(void) {
	ppu_off();
	load_chr_ram(chr_data, sizeof(chr_data), 0);
    draw_menu();
    update_cursor();
	ppu_on_all();

    while (1) {
		
		pad = pad_trigger(0);

		if(pad & PAD_UP) {
            cursor_pos_dec();
		}
		if(pad & PAD_DOWN) {
            cursor_pos_inc();
		}
		
		update_cursor();
		ppu_wait_nmi();
		
		if(pad & PAD_START) {
			switch(cursor_pos) {
				case MENU_BT: jump_to_game(0x01);
				case MENU_BTDD: jump_to_game(0x05);
			};
		}
    }
}
