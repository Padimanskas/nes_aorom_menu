#include "neslib.h"
#include <stdint.h>

enum {MENU_BT, MENU_BTDD};
enum {BT = 0x01, BTDD = 0x05};

extern const unsigned char chr_data[0x2000];
extern const unsigned char nametable[0x400];
extern const unsigned char palette[0x10];

unsigned char oam_id = 0;
unsigned char sprite_y = 0;
unsigned char tile = 0;
unsigned char cursor_pos = MENU_BT;
unsigned char pad;

const char TEXT_TITLE[] = "";
const char TEXT_BT[]    = "BATTLETOADS";
const char TEXT_BTDD[]  = "BATTLETOADS & DOUBLE DRAGON";

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
		vram_put((*str++)+0xA2);
	}
}

void draw_menu(void) {
	put_str(NTADR_A(4, 18), TEXT_TITLE);
    put_str(NTADR_A(4, 20), TEXT_BT);
    put_str(NTADR_A(4, 22), TEXT_BTDD);
}

void update_cursor(void) {
	switch(cursor_pos) {
		case MENU_BT:     {sprite_y = 157; break;}
		case MENU_BTDD:   {sprite_y = 173; break;}
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

void draw_logo() {
	vram_adr(NTADR_A(3, 1));
	vram_write(nametable, sizeof(nametable));
}

void jump_to_game(unsigned char game_number) {
	*((unsigned char*)0x8000) = game_number;
     ((void (*)(void))0x8000)();
}

void main(void) {
	
	ppu_off();
	load_chr_ram(chr_data, sizeof(chr_data), 0);
	pal_bg(palette);
	pal_spr(palette);
	draw_logo();
	draw_menu();
	update_cursor();
	bank_spr(1);
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
		ppu_wait_nmi();
		ppu_wait_nmi();
		ppu_wait_nmi();
		
		oam_clear();
		tile = !tile;
		oam_spr(16, sprite_y, tile, 1, oam_id);


		if(pad & PAD_START) {
			switch(cursor_pos) {
				case MENU_BT:   jump_to_game(BT);
				case MENU_BTDD: jump_to_game(BTDD);
			};
		}
    }
}
