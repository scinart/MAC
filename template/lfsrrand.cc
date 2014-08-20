/*
 产生0-int范围内的随机数，每次产生的都一样。
 实际也产生2^31/32这么多数。ACM够用了。
 */
unsigned lfsrrand(void)
{
    static unsigned lfsr = 0xDeaDBeeFu;  // my favorite music player.
    REP(i,31)
        if(lfsr&1) lfsr>>1,lfsr^=0x48000000u;
        else lfsr>>1;
    return lfsr;
}
