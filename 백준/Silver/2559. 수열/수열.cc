// LOADER BEGIN
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <io.h>
#elif defined(__linux__)
#include <unistd.h>
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20
#endif
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
#ifdef DEBUG
#include <stdio.h>
#endif

#ifndef UINT32_MAX
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#endif

// Use cdecl on x86 (32bit), Microsoft x64 calling convention on amd64 (64bit)
#if defined(__LP64__) // LP64 machine, OS X or Linux
#define BASMCALL __attribute__((ms_abi))
#elif defined(_WIN64) // LLP64 machine, Windows
#if defined(_MSC_VER)
#define BASMCALL
#else
#define BASMCALL __attribute__((ms_abi))
#endif
#else // 32-bit machine, Windows or Linux or OS X -> forbid compilation
#error "The current file can only be compiled for amd64."
#define BASMCALL
#endif

// Base85 decoder. Code adapted from:
//     https://github.com/rafagafe/base85/blob/master/base85.c
const char *b85 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>\?@^_`{|}~";
void b85tobin(void *dest, char const *src) {
    uint32_t *p = (uint32_t *)dest;
    uint8_t digittobin[256];
    for (uint8_t i=0; i<85; i++) digittobin[(uint8_t)b85[i]] = i;
    while (1) {
        while (*src == '\0') src++;
        if (*src == ']') break;
        uint32_t value = 0;
        for (uint32_t i=0; i<5; i++) {
            value *= 85;
            value += digittobin[(uint8_t)*src++];
        }
        *p++ = (value >> 24) | ((value >> 8) & 0xff00) | ((value << 8) & 0xff0000) | (value << 24);
    }
}

#pragma pack(push, 1)
typedef struct {
    uint64_t    env_id;
    uint64_t    env_flags;
    uint64_t    win_kernel32;       // handle of kernel32.dll
    uint64_t    win_GetProcAddress; // pointer to kernel32!GetProcAddress
    void       *ptr_alloc_rwx;      // pointer to function
    void       *ptr_alloc;          // pointer to function
    void       *ptr_alloc_zeroed;   // pointer to function
    void       *ptr_dealloc;        // pointer to function
    void       *ptr_realloc;        // pointer to function
    void       *ptr_read_stdio;     // pointer to function
    void       *ptr_write_stdio;    // pointer to function
} PLATFORM_DATA;
#pragma pack(pop)

#define ENV_ID_UNKNOWN              0
#define ENV_ID_WINDOWS              1
#define ENV_ID_LINUX                2
#define ENV_ID_WASM                 3
#define ENV_ID_MACOS                4
#define ENV_FLAGS_LINUX_STYLE_CHKSTK    0x0001  // disables __chkstk in binaries compiled with Windows target
#define ENV_FLAGS_NATIVE                0x0002  // indicates the binary is running without the loader
#define ENV_FLAGS_NO_EXIT               0x0004  // do not call SYS_exitgroup on Linux (support fn-impl scenarios)

#if !defined(_WIN32) && !defined(__linux__)
BASMCALL void *svc_alloc(size_t size, size_t align) {
    return malloc(size);
}
BASMCALL void *svc_alloc_zeroed(size_t size, size_t align) {
    return calloc(1, size);
}
BASMCALL void svc_free(void *ptr, size_t size, size_t align) {
    free(ptr);
}
BASMCALL void *svc_realloc(void* memblock, size_t old_size, size_t old_align, size_t new_size) {
    // This won't be called in loader stub.
    // Also, the main executable will directly call OS APIs/syscalls
    return realloc(memblock, new_size);
}
BASMCALL size_t svc_read_stdio(size_t fd, void *buf, size_t count) {
    if (fd != 0) return 0;
    return fread(buf, 1, count, stdin);
}
BASMCALL size_t svc_write_stdio(size_t fd, void *buf, size_t count) {
    if (fd != 1 && fd != 2) return 0;
    return fwrite(buf, 1, count, (fd == 1) ? stdout : stderr);
}
#endif

BASMCALL void *svc_alloc_rwx(size_t size) {
#ifdef _WIN32
    size_t ret = (size_t) VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    size_t ret = (size_t) syscall(9, NULL, size, 0x7, 0x22, -1, 0);
    if (ret == (size_t)-1) ret = 0;
#endif
    return (void *) ret;
}

typedef int (BASMCALL *stub_ptr)(void *, void *);

#define STUB_RAW "\x57\x56\x53\x41\x54\x41\x55\x41\x56\x41\x57\xc8\x28\x00\x00\x52\x5e\x51\x5b\x31\xc0\xac\x49\x89\xc5\xac\x49\x89\xc6\xac\x49\x89\xc7\xac\x89\xc1\xb0\x03\xd3\xe0\x05\x00\x08\x00\x00\x49\x94\xad\x91\xff\x53\x20\x50\x49\x91\xad\x49\x89\xf0\x96\x53\x55\x48\x8d\x7c\x24\xfe\x4c\x29\xe4\x4c\x29\xe4\x44\x89\xe1\x66\xb8\x00\x04\xfd\xf3\x66\xab\xfc\x54\x5d\x83\xc8\xff\x48\x83\xc0\x02\x50\x50\x56\x6a\xff\x51\x93\xe8\x49\x00\x00\x00\x52\xe8\x2e\x00\x00\x00\x0f\xb7\x44\x75\x00\x8b\x55\xe4\xc1\xea\x0b\x0f\xaf\xd0\x29\x55\xe4\x29\x55\xe8\x73\x0c\x89\x55\xe4\x01\x55\xe8\x99\x2d\xe1\x07\x00\x00\xc1\xe8\x05\x66\x29\x44\x75\x00\xf7\xda\x5a\xc3\x80\x7d\xe7\x00\x75\x0e\x48\xc1\x65\xe4\x08\x41\x8a\x00\x49\xff\xc0\x88\x45\xe8\xc3\x5f\x4c\x89\xc9\x44\x88\xf0\x88\xc7\x5e\x56\x20\xcf\x44\x21\xe9\xc1\xe6\x05\x8d\x74\x4e\x40\xff\xd7\x99\x58\x72\x46\x44\x89\xf9\xd3\xe3\xb3\x00\x8d\x8c\x5b\x00\x08\x00\x00\x8d\x5a\x01\x04\xfd\x18\xd2\x20\xd0\x3c\x07\x73\xf6\x50\x3c\x04\x72\x10\xb7\x01\x8b\x45\xfc\x48\xf7\xd8\x41\x32\x14\x01\x30\xde\x20\xf7\xd1\xe2\x89\xde\x21\xd6\x01\xde\x01\xce\xff\xd7\x10\xdb\x73\xec\x99\xe9\x03\x01\x00\x00\x89\xf3\x8d\x74\x82\x10\x04\xf9\x18\xc0\x24\x03\x50\xff\xd7\x72\x0c\x0f\x10\x45\xf0\x0f\x11\x45\xec\xb2\x5b\xeb\x32\xff\xc6\xff\xd7\x72\x10\x8d\x73\x01\xff\xd7\x72\x1f\x83\x4d\xd8\x09\xe9\xc5\x00\x00\x00\xb2\x03\x8b\x5d\xfc\xff\xc6\xff\xca\x87\x5c\x95\xf0\x74\x04\xff\xd7\x72\xf2\x89\x5d\xfc\x83\x4d\xd8\x08\xb2\x94\x8d\x34\xd2\x99\xff\xd7\xff\xc6\x8d\x1c\xce\xb1\x03\x73\x11\xb2\x01\xff\xd7\x73\x08\x8d\x5e\x7f\xb1\x08\x83\xc2\xe2\x83\xeb\x80\x6a\x01\x5e\x56\x56\x01\xde\xff\xd7\x5e\x11\xf6\xe2\xf6\x8d\x5c\xd6\xf9\x83\x7d\xd8\x04\x5a\x53\x73\x6e\x83\x45\xd8\x07\x83\xeb\x04\x19\xc0\x21\xc3\x8d\x5c\xda\x4f\x52\x8d\x34\xda\xff\xd7\x11\xd2\x89\xd1\x83\xe9\x40\x72\xf2\x5b\x83\xf9\x04\x72\x43\x89\xde\xd1\xe9\xd3\xd3\xff\xc9\xf6\xd2\xb6\x02\x01\xda\x83\xf9\x06\x72\x1e\xff\xc9\xe8\xc1\xfe\xff\xff\xd1\x6d\xe4\x8b\x55\xe4\x39\x55\xe8\x72\x06\x29\x55\xe8\x0f\xab\xcb\x83\xf9\x04\x75\xe3\x99\x56\x01\xd6\xff\xd7\x5e\x11\xf6\xe2\xf6\x11\xc9\xd1\xee\x75\xfa\x01\xd9\xff\xc1\x89\x4d\xfc\x74\x1b\x5a\x8b\x4d\xfc\x48\xf7\xd9\x41\x0f\xb6\x1c\x09\x41\x88\x19\x49\xff\xc1\xff\xca\x79\xeb\xe9\x8c\xfe\xff\xff\x4a\x8d\x64\x64\x30\x5d\x59\x58\x49\x03\x41\xf8\xff\xd0\xc9\x41\x5f\x41\x5e\x41\x5d\x41\x5c\x5b\x5e\x5f\xc3\x00"
#if defined(__GNUC__)
__attribute__ ((section (".text#"))) const char stub_raw[] = STUB_RAW;
stub_ptr get_stub() {
    return (stub_ptr) stub_raw;
}
#else
const char stub_raw[] = STUB_RAW;
stub_ptr get_stub() {
    char *stub = (char *) svc_alloc_rwx(4096);
    for (size_t i = 0; i < sizeof(stub_raw); i++) stub[i] = stub_raw[i];
    return (stub_ptr) stub;
}
#endif
char payload[][4096] = {
"00008I8^`u^tNsQ&<PSAbgT*4SOLU\?)mI7`Ay(`X^)>r=n;3yij)`@SPibUV*t7k&5a~G9^)oSQ^m(#SmL|f#Vr&oIuL$RF7LTCNp|Q4V%O*PYGcR`L6j}^-DaGf5f!S8n|L-dE`Z>r%ifX%=>^f*l)9XPlZ)rC>21UMnuSo9~9dm-{2;8Us)KzNmb{q;Ox*ZY{UQ^n_Vx8yGU||jB9r_7k2Z*tu{;;yuv#@kw2ZnkzXi)k5Wi2Lo)rZ!5;Q<RK5NiBps+~AY$qL-Zx1gA>tdbE%UmH0tGa+W&p19kfzJc!uPg8W6L5tP_&+eQTL_Hve%B4&>kJ{w)juv<}l`HnfkbkU*zH5Bwi$Oor*_qQy51JZVpfm67T+99gkQ(nJ^a*DC$+MRCZF(u\?7ptgh7p7s_slzYuw%FNP$8LL%a1>>34t)F3{1LR+-&`{^@3dpRR-X10+6~_L(bXFtm+_^)qtzHCp74jvK`UyJvc*@+MMoZZE+id~HpX%f$kn6D&>XtxcuvpTVBb_7*HjUW)oN5E\?F6+CrEt$gr7Ak2WI-e*-1iAwyqh4v\?9ZZ8F!bviFAU{7Jfelc9L%NJ48~;oy`l9f<jz0>)(Nv14PkP1SacG\?\?hYd4$)Lhrt`RZ&2pUn3cxS5PPpT&6U!$uxJzGWUMvu>n;\?Rm0`-^cluQsHVgopW$!X%w5UeU=$s(`&!Yq<D6TN7Sh!FO(EkGg9>9}f5hwbmEM@HqO~w=xjS7|+7N8lRP\?lH%7usq4#D7sm9woKa_oN;34XxcP17;|ZGl%R0D-*&!NaJ(!sFTEp;dXMhI3WuGz-qD6LeWEgNtOX|X6MEeOCY{<W44E\?jiEmq04GE)jwFsHdhCmhiOn0aX~=<;zu;wJlf`P+QKO)$P<5n*$a_ZgO!Lo\?axKuK#5^Q\?y27xe425k6<G!xfmKUgU6\?`wSFodixKuGi>S_OnTU$#{@\?}>pS+$qVOB$r1g4VV8%LEM~e#hR@-#@tZ8aDgHZHiY*S)Z5kNB^4~U87)8!YdbLETNfP@00Rfofyk{Y_%FTvliYHrG|-}Q{+ChBqb*}n(!<_JSq-EAW*UXa)=e;g7AIUn_2G6@ZZ!d6>T@^e}H#OO58z5bRj#n|nOCg_^&QZi*lPc*ID{qtUWY)f*_*`1ExVi0(}J@rKSL@6gM-**lP(Iq@KHPsG%^z4O{yt3CU&(|fJ7zl\?{giBp9b@T(3MUj8~dwQFSY4<{ns<+{=g5pfA0K5\?&i7b-R=xZyps{u|&T$Qg!7Letoe`9U~7CgxdROO~H1Dte(\?X_tb;an#qVu0-Fx*K;#C-SQDaTKmoQwvB51qXs@\?9+8qDtiZc)G_*H!1GTD$8lIR5TC=C_k||FmEe!mGs%keY$ua5)&q$+d5fv^>i@Gj7elI~`xor2X0t3fKto`o\?=4OMdXpw1VHR*T%pL@e@xxSb9&tB!&J\?_do0{enR4s0XB5vruf*OlM>-aW|oAN(@K~eDir2LWBd=ZuM<J>HQFBUg)+=sEW8{1rJZGoW4p148`-FXD^SXbsr\?8;<8q7&\?608WC=fsHLlyT)E|l~Hvx>N^#<*1nNkAgX9>vl3$p=|XwG-PB+GK5pq)\?cjkr9+0dJ+FZvLMlvb|KbUs+S\?zduU~vED9}ay-j=X;*XbtMRa`+&1{`\?>RHr4n=3832QP)`{H99VM)+MQ-1YnWL5$r95`rLO6zQqqo7wWTCRcP4N5#%AD;UwQ\?_x2bdr70zfHSyY<bpcvt<i;U5)_h-dDns}qCTzHr8ZV(U$aBr$qe%5tczcBT6VuGYb6p3u}m<&L5J+r>@L;R2gMXz#Cj0^^Ii5912=aU=xlwukoKFG}LC6_chTW|Er&8$U&KUz6rHu(|%X;_*o5BmqoqZcFKEt\?UjL(@u5WtVg@2UN1oX!wJ|^N;bCWAnj4nnK8yIS|FMkIam<IM3l{VRyeMZU8n+hI!-gEwGOku*xJ!Bditvo5Xl)E0j$lc6lx~YR$mX;yQ\?In>AzlyF0aqbn\?tD({ee2S$qj+@p}FXJB&+b0eEJRZzQ@t<|)RNuLa-QB3hu|gH=<8y}lK^e&NyAJ3guSSYOSV`;oGRS+_o$ek5kB<$$S1&tSe}vn{\?^a&05rC!D1)lB4)2Mz=-b@(05f{}u>k(gi{+f8r^9x@zO*+_QBxE>XKlMo+}MpeUy`6p!YW;LVqxpHUxV!L\?GP_OkH~9wF4DmFgZZw9Vk%&+uXL)JZVA(=aCQf<%`+bZM(`YtxfsPsTz+E|IvL0Hw_pf!@{ooxRrI9`#Zlf&=FNpMwTrzBH{1U47*^167Knyd<CaG57V{%csg7jg@76J1^}0CyEZ<D5JuFG!J+{2z9JpfG=B^#%fQuski7jd$3Tq{P!o}sARusmO*h0\?YZCmkSMQ\?0X|ZZ%!O8ZQ~qx$_u3F|5fOfl|Gvn0_K9Z;<\?D8X^!{US<EzAm(~v%Gxt3BwhxSO{90!@B;-GB%fcKhbo!w0AUsI-xC5uoT<|f2PMbE3Gh767C`8wY6WiGTEd`J*>2eyV7Zp*(g=|91ebN2*B^V*mt)7IE=<VV)QZT2url)9T8S1M^9h9CSe4#4f+j-9omi8>&-_mW$JIn9`Dp6q4QE(JxSiM(ZVjR(Wo<$!6>mcU|=%UC+x>o(lYT*`0\?Ijo^w0yga+L&w90bGok8Q<3XAakkK^cR3Hnblq_3D*-(9VV_<Y#h$LDqn}hpUM-vSca!LAx\?pJ{L10v=7<\?YBJzFH^Qb7S$*{_Fo%44S$N!=z}3Ztazy$)DKYalzhHKQLkAYoklcu=LAbb8@Jt%1\?^KTFeUTkwJ8kCXjb&!^s~&qOax_fIMd<Te5IOI1}T^A`P2@iRp\?`&y^bs~xAd=jR=AYaf!pL;xNYK-Zc34au5d>boGwEi_Mi4#(V`xL!L7gCUwGyf3ybZnmh|&e%7%#9Dj6XtZ2(T#WBa692ZC\?LY$}!F1Q*ih\?ON7e33tQ1dIIfNUlhIL_@lw)I4~)_5DAPUqv1VGam(OG%vbqLXx`o`nK3pjGSrp)sC9>JJuZut>Ye@mxz~+k1H9rrWgBHEcOXG+7JhciZOq<pBFz\?V}+hLJTCIg`rK!E!_K%c#Pu{Ou*<RD$4v289AR94jkv(cd(4DawNGOmPO*JbiJgEZa!aaSWB}pzX`wNJ@V7iBq2!R1`eh<OPOQ0CwH;F=nm5@nz$8^v~HJaL!\?&`*1W)!2|)HlCq3@wXzU`82lWc2q~!M~41(S`Kj54ic;>rjcco#$H7W`=)gtJXYn;;eh_1&1|FL{rBdIq>C4dZtS1mLmj*iQ~D0%dZ=%3(Sb{QYyf{4_doj62+Ic*3Od=N1Zi(Qy=>c|3J9ku7V9evl|=J%nMX5m<a<}+Ebip74nKnx\?@2U%x3q`(7pBd#{ryma>E_*4U=QXBjL@!jw|Auu8p#St+|k|%w|gN9-MB8koAjPed-*4Qk+qZ}eeRLQegeoNi6p<&v3oOUaNBD1usK)t(e`Vbo~z7<OAJN@zA\?sgfo<z~K^s|O7ZY6b$^(Lm`5RLdB0{Sifd9_gpn7JiQz(H}D@DuXl65n&`VvM@CcjE6\?iLrG>SMy>fU3e#ws;e>w8^$fXSSPIRZ<u!btb~9){9FpXZ`4Fn3>XOZG7^w+2npF43wdAmYAPQu|-2gcn$=rn_{!;bp\?Sg!fKq516CpJC4&eNdZD!B${(zV;kVbSy~OcnmO5g%JRl9RlMjnN\?_v92x@eq3@`w{LaHkUjKIyLiOT3q;xBb5kD><@Q>O*m$T<)4SUbB4+bhGIN`ds|0fi3}102<d`5vyJr+\?{dM<O2M{h1)dhA2!7zU>%wg&(HYKkZ`xPnGqi3ei*}v|D\?&c38d5-7HjS`@bp)ARVGBIJWj_6J=VcU!>q=fnNRlA{}2P|UJ)%ePLOWs@hG=zZ;orJn-M$6N!w5=~GYHtY=T`ei3b0$XGwVRxneoFOITxoW#>#zSsvltny19R|\?`)F^9_`cYF\?H-h~1!;w$(5$i~H;1i0v>I|e9WRC+3Jf3R)_{E#i3RFw1_;ZD)564E;x3u2w\?sTAfe6xvX=Q%SQV!c<6@miRP;kr*_rmSSlIwgx7VNvG;qKV\?*7<>eRIUhQVl(hBD<p4A=~G%k2&IXYfq)xDy2eXzLSv34",
"^E{XI%jiU4&524;W=C^HggW4!\?gogfCQOK#Wd;pc(jdXwSay)EIc(<Bc9bMqTPqhNmj8}VKFXzvhSS+R`\?6J5J)(v+13ExOJIyjQo@g\?ug$~K3HcOCcQ>Xd0jZkXTaIN@gN*r$_2QUp=@@m&EIzZYE(Qo{e8G~a;A\?>;o)6Fe>f7!aW1N!Z*U_zJVg(W~tNILxH=gDdRhha+>&cyeE\?5Z;Tz60Zy4wUVE^N-aOE3Au6e0WN896Xdd7Y)HJRA_a1#cMTr6tFt29xDCrRnE2Au\?NM#z(kK(`k(P%B&5e4PsZqyCJPE`**+66k#0I7\?D!y}n*tWD>R(ok-;{+wqX(5_nK9!ZlXeT\?J98<@YtoH7p>xP%4k4JD8l@6mr#!mo9%ttWLA9@5Y_X>u7_!30Q5IFu@c^X$+*^6+D<$jyXLnGTTdXFxYZ{0Bl<Y9B;Gj>7hBr1o7ZIN5;V&EWKQP1^{<38|ZIxbDb|ldXgxlS3y2VD>RFgRmoxA6nKA4+aV5\?+wbO<X*0g`j#vWY~T$sx4i12wpIE0_)IxX5a|;bVYyDJVPZ(-yVrTQrz<9\?{e)>*U=S#Eme;J~-;3`h^PE-2`H|9F6n`Glcn(RS%(\?ah=zNx34!S\?M#Fgz4&&I(Fk-Fh1mm=A;izFWV&eI7Jhjq{w3$&&EF+_LTxu02!udDpmLpHO&83$n3VH=kMF=pVjH#n0qn#hB-j)%<y;&u#EjOGWXdy*VlBUBy`!*;{LC_R+fR2YtlQ03Rp>AbR_$An6;$!A+K&~Z3A6^\?eOaOk$R;<p8R_Y##16Fw2#hHccSalypo!7&CuAh=mfOJ(DR{PI7PAc`Mcl&`LzSy<bm0yD*pUdZc`{hXqIHtiU3^Hv5DOj=So@z0)xsyV(>BCwSX(Hy=f((aRItf_T}4Zh5Y<2VWAU#2(Z>4&o~yS09q^_AWf6-3<dDu@$ixI&T$pHijv{=QjbUT^$39H_GobGEEzI6BH+wUgjVVhl3@_^85z~(8Vmb)$;)RH1q<TmMdT32Olzpofx_{nNB|*1KR<U^=A>~!l69VjZxUzS&;8W#R@tzf9+s-AJF44$YNmyVp-\?^@3N(Gx\?o<~+~dBmFg->S\?4HIZ>)Kl*5W1g}yrGjpgvy\?^RwNh1Kp!KP5K)6pFlWbw>|Zbejzl|2pkV0nkY9!0GnR5_P06th!GylRIPP&eKul8mJ-qrE=rdvFU6KI2a=TwQ)GVmldGX)CYcv%LB|$87KHMGrm^&nj#qHcI5^e$04WH3IQ9#i}l|tasW2s{r+OxPm^}6NHmWR=26DLhll`t6CoV&6Q`Pzx45Q-IVMNiSSkz-|LhG1-0{k8L@^ZrKp~n<;x{dSmDcHZv}Sp^l5$4By&}y4jN0cDO{PcS*EA=(h#$q9bF|kL!yH;cqJ44Rh!r3N%Ay<@lR`H!4nuNeK\?+u#p8}yeD7H+^f6}yvH$PnE(tsg<LlrYTLk*ktSIF|=IKJoVx3>J+6-%^TCO08KKXAw4$)p#K{E#U=s\?3Cq!~$YecZopmnhTY3l495mob6@^0iKVj1;THHEO*RXY(p{FJsQIeWYOqgW>-XMy7h1xZWXBB^U-3hW4N`D%Y5HJ^sDsKJluqH`4lyhj{KbtcPKZArSwW_8u_;a64sQx52t<HW;gPo>W(0{QvmuDY!Bi^8H%2TO5`$mQyR5FcC8EsHP-g)%u1_#`94zMrk!7HfK$^6F#KIp8d3!CSAj7b+JnH|Le9TpeTCe5%xdYH-X=;sqLxlY&m)ik{K3PbhLK9N;Yd@3d=)y-@40ysXsL!*b-J>PH-4S{LXDu7PMAr1iiZ`(^;7Db1K@emw&BOKP|aUl+^f-3\?M{6@SJFwHgd&8#@tNNAUj@fth\?$5aa&17&Y38oSWA*%ews;jdHbP3g}B{JI8-!s91xU5xK_+Jjd\?EV5P\?U_+o1Q>18an1\?}$XfncKBv@&z#`2X`P{D#nRJw\?<ROk_>~Totc}A{*i!|M=d57oEVT1vj50-#!B@Jp}0ZaT`y!S&=snqCSi(s;%TThAC;=)BuSMVAGAghs)YID|Nl^r2zC0<Z\?Thonovwi#6gc>mjFDNX@UYyo-J3{ilXokXxgKuaVt4c`nBT<6u7=aZl=uAhqa-4w\?~^#NQ4#16a9zl%pH`7r&h&vMVYD$5aI1wBeoFACW-Ipk6OwFBl$(lx)ET7V77Y6%jygwdW@^X+T}%up~qypzvN5*DkyszHI29~n$O-x5HFcX%iEyn>zG49KS2a+S%lz5#c{b5<qpDCs<X+~^8kqKsV%-tU19`$hU&*Uhd6|@xGP<z`oWxtb;7=rKP_1|iSd6\?q!3W^yxFL;O<T_iZ(Jz<H0G)G!Z+b1hb%g+GZ;g-<OW2@K%~YXzzO4Q883dh+|2E!{VhwwDP{VEaD@L=oezf0GxP*q6}_th^z&JFqmf{Wnrhd3EChOyP>R#xC;Sa;>x!R>IBT@XNpjpeXSu17)p_#tVphG-)8T)nX1}EsA*;8od%tw&%zBcj!k(Hlmlcc05C`sGb^MO_xVXeCtWnT=;3A^Ei(!e(2xT%yHUf}1C;\?`*io&;ER^<K%Peh<tbs\?lf%*l=jAeTPuzj=shjZLy80v^1pLL$`t{#O!I)sr}GSyBfW=0%D!7boNVSSK!g78muZ%_`5;$FZy9p~q>aaziB>h#j`x`+Ub|tm7DRvEl{|b3calh\?LV%AvFT#G+%4mCYC5OIi\?1ZChUK;N@l%3<S90x*KYJvo=IxMw\?me%jRib5uS53<L^yRM2Y@a~B;W-~XvID;N;Nn;#!^*$JLFzuo@MdsGbhBC#)1!rVO09TjTEojY*wynQo{wR!s1U-Rp|C(W_4_;xL^p6mSwLXxptq\?W^b%tPfp#1EZX;(&3Z(k)0R;pzI~&2{k=XH#kR_InLA2A`4aKFKu_7#udH|R{_`T(-wx-H;8mhBr-wIh0*XswJ%)E}DQ`Vh_&O$vot8ZW#CDsPQ;`aKRChzs6v4%(SFJ9eocuQP(5>p(J5|}ON`V98%DvI`X~l{}wR{0jYmi$;%Ew29n}b{cD&`#`t{&Wv>$24v<9bNWC_gF%=Hyx_+WCYYBC`)&k8*rz24HgS=*!k1CcN@<$v1{&`XDYL+yu%yIRR=}4n~G8@Kv33$qHMm*y!|q`h+{t<;+5mr{Jz&g9V4h|D$}N0;!}s69-rBa3brlWJ}YDQe|cy&ER{T-N&7y0))>0=gs>@gR%>`>AC!-RZorlE)GSXnf(FdffX@FKh~MgipRW=-3qeygOAyJh5Bty|3`6XqNJ6YN!h$Y-ENxVDLG0)tO0lbT5AY-Fsvw0Bi%lOr;QldobX<QW(Ubr`bmBC#~G62BB~\?(F%H*Qo;L%GK+a=tPfqk>X|mEI9O_$3;E3<P2zyV|<@Z!gk%%KyU4YwCRU6YB&4>!\?c|CuGG|wVb0m<E-Y0yy\?@DPOQp7r(n<QvpfUF$hgqkLnBx8^}VWSH<(EtQ>pm&8^PD=0IR`B0O\?Mnt(`=ncR*A&eBC53ESaR-<7(D-j0BU$e-0g~DjH2oC1-lE%!0c;;ONN`ICFM)~l8-c3cqlTgZ!SXh>Blq6`d+O#O$PCvc&DwPd$U<W0(@U\?DgfZ>w_tM+jDWFb&V+Q1v6h46{nk+ES|qHk%2eOh*V!uo<NMw1o9miHbIW87@GEt4rNY!2{DWTFB`4mi>sy0ug(LX9Xr&z=R%X(D=Gw(U1_3z8%5Xid@;Z#o9%i*s)}`j3B7R3^}nxl2Owt!&ja-Jwo#S|Q_b`4u7~P;A#|z(y5UfK(MK+*~reLavw013YZbsSinrsDr}Ilgz`F^WekVmpXaHP{8wN4K)>w8IaPBvQ;CxXx\?XZrL4@3N@DNUKRv+QZbENO%5+|k;gC\?\?&o_wreg6&wh55#esgKC#)(%*~LQ0j@NgtggDmqXjy$3RwAz#Nhd9NIfwY;UMXd;K{KmvAV<AKXY$$j~KyZJpz%PS<0wHP2#8e*jXvgpbl5)zm`<sn9R$q>D6snXhVcA0=9Y)J$bo*6<uVJf4nS8M8C*Ql!s^ps&V;^Ni%hH#xLBF>fsxeo|Ev5NX8M>e3WhR}P7Eg!Q&3sK$mCWGjxaVXnaYHPxd6<u_OHx8+}D_*H4@kg\?+aM`fWtf=)dhw4xsDB7Ws&vlh^",
"8Z<lVCHlnfm5p5X%8Kb0WgkhGR!D32fuZ@n^%X7<UCaWZ92KormSi@8bn=TVqQ@9AeVlv|Ks$hx\?U7uqanGyI>}J<>>|YnwQ=QaJfD+9T(Q8l0WPu3MEaPiN!eU)Q3VU4joc6u%<xlPvk}WzJRt!e\?#FUJ!w#q}Z*Z|AO6+2^W$r*NmYrX1yW_&GPaxDMc`^BdjluDU0XyI`b*gRp8Ddb3EmiOPZUpy#D$y;~9(#!`Fmi9PZzc^_f*ckX>NpT!R3j6&D!Wo<7heCIOG&c%!2%QUjal~7v3@2QowsS#s@lP5u`hLCmy<dMH+nw\?eit@RK)~v1kHK3GmD+X9;%PrsjKCD8=Vq2GC0q+YSm5IrWlUej%2WD2c9uw>I<8BG<ytaHO>s\?P#@&PCq*t!ZTEfR+6%a+PR`g}^R)HeyDAwBEcpGK}6`mSd;T9FSaJk$-02tkqb<(8=<L#7lSr-dS~X$z7)6lbwTeo|!O0e$_L0@>js\?h*X4@o4Ms(1c#lz)l7@Vf1ntiJQWXqrS-FV%Tbuq2k`3zna{YMn\?LW)5avUA&3I&R3n*4nGCiV|KcFkuH61xFd&MMLO@Q<%%Iz@>w{$o`PzTS%N@ca1vie0lV+3XSuQXDx8K9R)VALum-#3{yM^nkilWd^sWJpE\?L\?wlUfHh%nlb1(8A~3MPp7#GXqP)PJ{Set)ipjX##Qu~wXI-a5<>%u+heXKFO<HOA)VVd`%K06D1(J8Rnr6~t#G}S8{_Q=tqwXkl!GD6w8onc)FfA<$2LX3^b1Dph4I+poQL>XM=\?dBMGa9h6P_5G;}B$a;4%)jXYX*m3ypiJ;9ED;^J94GUy$AWG4+X-O@obZKvoIFIPHt&52_yVvyrO);CPyc=v*>9m|embT\?>mLfxl_*oHSVo-QgjrT+aa1x-0OW-7mS+e}dTqizlDy0{rG|LS$a}*RS!`Z>mn}6ON!mUGJrYWTJ)E3m\?o4E6LK;0=c}^5nJN@lR6XW1IXy(eHaAvt!4fTxrbmj5ZQJ\?>&Z)ePZ}^cjHOMOHQ-s1I#NVUA$Q|qByAHc%zKhr6-`-+tFS\?-m#g0CNAPkY*<pMR3f!OXYMX1ld(=obC%0z&$F3aJ^St(*;dqsz>TEO4\?w|{jqvqpY7>8joACsDAhOIvu\?nl|#Q-pzMp$JK3pS{ByRZ=cscY9){0**\?&aVg{8H76G*P%s>BV8P`%Dqi4&\?|W*sdq2^u=S{4|KpYKq&RO0}(Nxwq4pZi;VH*EHnFgGBy3{98D|^DrYI%u#{lkBjw1-*Ol*_uxgk0&%Fb\?sNbT;xZ*NF|gaRfWSicB3|taV^Jh=177a!MDEcG*cX_aA+%jPmLP#Qbu$u$!b29U0ir!*^qb*~CDsTK+1cwZOy%L9Ou8|8B^g*3z145)hJkqxD8sk#iBHfLGt4=px99V~mXxH%SB{XJbe+Ijfkow4OJ8gV@WCG-B~q|5{E*<RbOGA+^PbsXrdfxQCwRRzWz^Bk0J-Ye`&eWe`pv4N+g)X-xZ3RFiJt@-dLcv%h1R`gw*11SPzRLvvWQCPDa>>U-lmeMYItL7(tme#G9!vurmrHN%37>^RXmg(n6NDMjg6*><eMXsg()!=>T40!f5^j$#nahLJIhvGO%AVk()~2X19ynNbh4TlIvWr!T75ox;gQp|ZerfI=PKp0l_yPjnf^_J0z)FpE14wdP=Xyf`RQt7I8Z(Q-m_E(L+Yn2=nv@hPbOuiqX_Tl-o}GobtgKxu&pgc{;ho1+_R9!gJ}>zq|{t3>|8$^j4Wy5`e^v|*f+h*e=rh!V\?K$@#i^{Df4`%i2+Q#h-nI\?J#TbX2qvPnZ>9h&(Q%BHgRB4Z8;NPe1k6#X$wgq)aQEsi`BkiK2KsehOVt0c!mc{F9#{+Z*q}lp7l}@u>qx-*&qnql=23mhhI$^BceIfJ~PPhqO`)sdp`rsfSY;HM9iTe&V19c*fME5%5TE0cp!9ip4#_q5Q+u0i~rs2nu7oU]",
};

#if defined(__linux__) && (defined(BOJ) || defined(BASM_CI))
int main() {}
#ifdef __cplusplus
extern "C"
#endif
int __libc_start_main(
    void *func_ptr,
    int argc,
    char* argv[],
    void (*init_func)(void),
    void (*fini_func)(void),
    void (*rtld_fini_func)(void),
    void *stack_end) {
#else
int main(int argc, char *argv[]) {
#endif
    PLATFORM_DATA pd;
    if (sizeof(size_t) != 8) {
        // Cannot run amd64 binaries on non-64bit environment
        return 1;
    }
    pd.env_flags            = 0; // necessary since pd is on stack
#if defined(_WIN32)
    pd.env_id               = ENV_ID_WINDOWS;
#elif defined(__linux__)
    pd.env_id               = ENV_ID_LINUX;
    // Linux's stack growth works differently than Windows.
    // Hence, we disable the __chkstk mechanism on Linux.
    pd.env_flags            |= ENV_FLAGS_LINUX_STYLE_CHKSTK;
#else
    pd.env_id               = ENV_ID_UNKNOWN;
#endif
#if defined(_WIN32)
    pd.win_kernel32         = (uint64_t) GetModuleHandleW(L"kernel32");
    pd.win_GetProcAddress   = (uint64_t) GetProcAddress;
#endif
    pd.ptr_alloc_rwx        = (void *) svc_alloc_rwx;
#if !defined(_WIN32) && !defined(__linux__)
    pd.ptr_alloc            = (void *) svc_alloc;
    pd.ptr_alloc_zeroed     = (void *) svc_alloc_zeroed;
    pd.ptr_dealloc          = (void *) svc_free;
    pd.ptr_realloc          = (void *) svc_realloc;
    pd.ptr_read_stdio       = (void *) svc_read_stdio;
    pd.ptr_write_stdio      = (void *) svc_write_stdio;
#endif

    stub_ptr stub = get_stub();
#if defined(__linux__)
    uint8_t stubbuf[68 + 580] = "QMd~L002n8@6D@;XGJ3cz5oya01pLO>naZmS5~+Q0000n|450>x(5IN07=KfA^-pYO)<bp|Hw@-$qxlyU&9Xz]";
    b85tobin(stubbuf, (char const *)stubbuf);
    /* prepend thunk and relocate stub onto stack */
    for (size_t i = 0; i < 580; i++) stubbuf[68 + i] = (uint8_t)stub_raw[i];
    size_t base = ((size_t)stub_raw) & 0xFFFFFFFFFFFFF000ULL; // page-aligned pointer to munmap in thunk
    size_t len = (((size_t)stub_raw) + sizeof(stub_raw)) - base;
    len = ((len + 0xFFF) >> 12) << 12;
    *(uint64_t *)(stubbuf + 0x08) = (uint64_t) base;
    *(uint32_t *)(stubbuf + 0x11) = (uint32_t) len;
    base = ((size_t)stubbuf) & 0xFFFFFFFFFFFFF000ULL;
    len = (((size_t)stubbuf) + 68 + 580) - base;
    len = ((len + 0xFFF) >> 12) << 12;
    syscall(10, base, len, 0x7); // mprotect: make the stub on stack executable
    pd.ptr_alloc_rwx = (void *) (stubbuf + 0x1c); // thunk implements its own svc_alloc_rwx
    stub = (stub_ptr) stubbuf;
#endif
    b85tobin(payload, (char const *)payload);
    return stub(&pd, payload);
}
// LOADER END
