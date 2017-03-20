typedef int24_t fix8_t;


const fix8_t fix8_pi  = 804;
const fix8_t fix8_tau = 1608;
const fix8_t fix8_e   = 696;
const fix8_t fix8_one = 0x000100;

#define int_to_fix8(a) (fix8_t)(a*fix8_one)
#define float_to_fix8(a) (fix8_t)(a*256.0)
#define fix8_floor(x) x&0xFFFF00UL
#define fix8_ceil(x)  x&0xFFFF00UL + (x&0x0000FF? fix8_one :0)
#define fix8_min(x,y) (x < y ? x : y)
#define fix8_max(x,y) (x > y ? x : y)
#define fix8_add(x,y) (x+y)
#define fix8_sub(x,y) (x-y)
#define fix8_clamp(x,lo,hi) fix8_min(fix8_max(x, lo), hi)
#define fix8_abs(x) (x < 0 ? -x : x)

// need fix8_sqrt, fix8_mul

#define fix8_div(x,y) (x<<8)/y

fix8_t fix8_mul(fix8_t x,fix8_t y)
{
asm("
	ld hl,(ix+6)
	ld de,(ix+9)
	ld b, h
	ld c, l
	ld l, d
	mlt hl
	bit 7, (ix+8)
	jr z, $+5
	or a, a
	sbc hl, de
	bit 7, (ix+11)
	jr z, $+5
	or a, a
	sbc hl, bc
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	ld a, c
	ld c, e
	mlt bc
	add hl, bc
	ld c, a
	ld b, d
	mlt bc
	add hl, bc
	ld c, a
	ld b, e
	mlt bc
	ld c, b
	ld b, 0
	add hl, bc
);
}
