// Generated with https://github.com/kiwiyou/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

// SOLUTION BEGIN
/*
use alloc::format;
use alloc::vec::Vec;
use basm::platform::io::{Print, Reader, ReaderTrait, Writer};

pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();

    let t = reader.usize();
    for _ in 0..t {
        let n = reader.i32();
        let mut interview_first = n;
        let mut people: Vec<(i32, i32)> = Vec::with_capacity(n as usize);
        for _ in 0..n {
            let document = reader.i32();
            let interview = reader.i32();
            people.push((document, interview));
        }

        people.sort_unstable();
        let mut result = 0;

        for i in 0..n {
            if interview_first >= people[i as usize].1 {
                result += 1;
            }
            interview_first = interview_first.min(people[i as usize].1);
        }

        writer.println(format!("{}", result));
    }
}
*/
// SOLUTION END

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
"00008_+<b9^tNsQ&<PSAbTK`Nb2TO\?HbXZUhyhdaW*)w5EVp;HzT;d=ACwTwWXYiSh2<(d$ii\?X&CA7e^ltGZAB`u7$1^H(OMs(IdK4FAM9(obKc`AM^6Pp{8dbL&W%RbVgA01LF4i\?F{t7o3%B5{Lo{>}D!}5s%Zhhxh^!1Ms5ur\?QmycRvr`ElR!yi!)y%k)wM~VCA;M)!Dl$a=q788^q1jyeWQOcTN*KH|!U~87vPtyzD*MlR(4w4ad<rkTd9^U;Z_OdC0DdPG$pN)U&j)LTK0+}v0H}77TR)*I6WT`&Bf3XOMag2g;y+hPy<Zr*uK9MrF9Q#`P35Eeog|mH6@>on0#|M3ZWp1MxQx)r26aqk(IHb{8-<Jn0NjAH}>7r6GHD3!Y3yvxo_753ab@jPv`CGJ8O_F$OdCZzY+)e}&G-fLuMJ3kJG^lI}8+0GrdxfVDM&GdY88Lw~mtvd538EHLH<Vo&fbsvsR-tB29BmMFlu;|V6rKs)DB@cfPwMx_vv${naOsm-rHHn#Db*v^t^G@XdtivnsmS2E=`*v;EET)krJ$pRGeXU1kyi~SGeP*D#6rTVNxmb|4aLH3ASdCbtK6jq$W=pq^50\?YemiOwNzxF~X@n)f\?7e+TrEL~kT<~}Z=e&Q%J{T8}_Y<I=yS}4JdKm-L`5EEN^&WaPOo(-rFKKxbx`k}7KPzC-IVX6X`nxoD1B>s~iXhfI#z^T$pHcCD{-bO\?Tj2|EaXK7Np5)C8ibhW_w^;=HZeQA~_a`HFGCCPzg;F2~m!fzC)vB;*D1!EQE_FE)bi~xZvstareLXxQNbTiPwjcr1LS=4DJFJ+|**ayF+_kF)%gI=grA2xS=9$4rs1M#H387w|<O)-P;-0)w7HCpf9)!SbWl`pdbOO{0=+-VihYCHr8z(MdM@^Ag9jJE+z>Ev-ad*9#p3vgniu^feUhonE3fthV$+bH0SQmO>O%HjY*J&rWanL7xbtCBHV<K;7Aij^0LqlEWy;dk|hSxW{Zcs_+U~}h$e^|}fBzxcpvVt&0Sb}tFxNDN7f#;bQCK0\?N^ejT`pH3X)&18>loScI3f0mi!kn(PTfbNGCzKZsvMQVr1d7g\?wPUu7VuWejcD}8RiM)}lCu7=&3zAy<0!k6Y!28+R2-1Z_SNt<}Uf<<vQ!j}y=PJXf7xKj66sreIYcF|IiH*M@3hyJ6HwOvnw=A%Pzdn1z|e~U2{92Sy~NJ6m6N+H<gSlhGzw\?{dNSiald{V^^)p)YaHoXgl__jqNB;;6u6F^2xu1\?0fi-vbAxvc%|BP{{2;jL#IV_Rm}#H{y7i^bClyw`FAoO1E|XuOyxsaP86W^_bY@J\?cD}W!Yqo{8-$XIwFZVE<gOvy\?jN+@5W*u58XAk#)xJ(<;bk2xN!IgjCm6>=MrZgDr`T~vY9fH$&Qe8=o\?$@\?PLS};`UF7fba=3Di)%xyHvZ\?LuGc1tWAb#<bb-aQJZwEsR~gTI{q$`Nj5M4Y>-n*jcpl$E\?7&Ps1j#ahVZM<L\?Cl((N_vae~sDOHL%`D>3V@Aa<Udc)NV^_lJ0Ez*(E78%u-%*dr-5sw)a&Ww4IgmOiT6(vM5KKxz3~+`~klwg}9HtggPZ*h5em2k2GUK&F!JOF+ogY$bh0QgWIAg)WJ#~oS2)i$YzyPOpKBMu@|t_2V_uK!0eM`OQErwayaSy1op=zVH_d{da1jL<i~slWxEglUS1wAp|gCM<Qm;8`w!;RVr5v}KL+qL$~*odavY#a$8f5U5T&sjN*oKmFN8o~4fNC8l4<r\?ZL4$6eDZ4R*3mXr)epe4!u4Vym}FD>{R_nVzB&`v8nWEEP=@Q-(v#UpP0_w)(((iwy@;Z6_W~6MyFh}QD&lOx>0v9$Sq8eRznda_5b7PLbAJ6#SnRHAr(JIhGOKAd#9*j(\?d5#oqeoKaWI+K9<s;PP<ipRRj{60qvc<&I6XBX`({t*XFy4#eZj%49DQ%uaDv7m=6*)_8{WwSEphR}32qMS#B0&W^FCU}DE$G8Vdgq_{9RO5t%As8jH%^P0He+yxWJg63o>ZrB-FEk}z%QH8\?d%|VUV=iKJDTBu6T<^bMu2&|PTJlO2EAXY+hCVuGvt8g@5n%%585UFq>gl#-b{$a_rm%cVLWLs6J5#djk7WD38PLQf&kRQPrAjvW|*=J4xZ`^83d^@N|U-#%uSG{N2(!la>%hvvplk}L$APO;1v<umR9YVp00i;UlBSHCoL5|4$0u6Ecc;5*e^6ABM0GE@n`qUq&#Fydw3-yro{l@NW_@9SMWzsg\?7uK21Wx5HtL*Xyn*8ow%p5#C*+Y~MXOTB>b4=)5SzeC{tzqyrVgw|8@zmv7M4WN-2r>YnodzPogd+a0-b7IGy!V8XRsQktI$%3d3z-Q7d6bFfv#p5KJlfZlpnip8B\?{;h)An+bEejiS^yBs9pbYRjq^zQ_Q{OpT<PfT5Z~6)b|`>5&qd_OlXG6OfEzKllloiZS49gDajnmtV6ax#jomfHJTi_V1Cxo{99*z&@\?W{U2FahlFne9>F}t8xr>JseqMbOP`b8E<zE24C>hra+^Ox^GA}8Jgnf5%no!CA&{Hz~8yq9r39a=n#&(+u<!v#b!k2=wett*JT@O^i{bYy-9&oJ{XR0TnR0`il8MCxO%NQefw9qM|GcKX#73K-mCZcVk}nQ0KV@(-<l!!tMM1MkwPEvmsb=\?se848y+yy0smDKAHK$rvhc=Y#Ky_QH%Srr4I*KznZz*2ikd}U3#A+a4>kQnoo1~8}e@bd4\?pw-HF#+FOnDNqr(zWbj}V^Yt6!0JP`uB4@~No&)B3PB#XFs>0|F\?ozp-3rqF=JLQd}jQ!fFq8D+J5^e-OfdW6fj+R~T0w>x%pHV*\?yb=lavVT;@WrvXzS&tFFi1fFsPJw_ZxHBvQ4{Dou2jsPY;ItIn$J1O()WEH-0hee@)-;GXKff)Ef\?bK$pMl\?z}KV*y7^jB*#m{Rk>tM)s4\?(H0IoqFLCETNfk(af@-<c(sF%ba@&X`^Hv(B@!V&00k|_ygB3s9!2Pw5+k;om#0KWjx7<pHzx_kk@`Bfw(om83$4i)>-nKhN-e&356y9YHiSjaF+}ks0g@MAo}ww-=}7{>MvT);+xutJcdlO587W0RU{kJpzZ6Ekw`XqsIth3Ln2OGWLfQNsF4v=S5(Ogfwvi<B5hPYoG-0S4*9A_yz!A_OB_6z6m\?@l@>6{QhF-bye\?RDBO6$WTM(s^n\?SHDXUZV>Kv4Q5*-;6bz3(nJPRIn@Q1fcpfzc#8rXF{ohe@EGjly7iKH+qbTrV$FC-F~;@J*#iR$\?0RWOmfe0k(~roa<$vMmgcL8S%-jZO!M2f3a3*B(<aU6y$n+-eugIK^rbc*b{F=~JL|Fy_(rQn=axOyq)7MglTpAnVn2Sc^3Q!V_djoiHk`WDks5~L1db2+^>@>;Ug>|Xf{ah8BbK_<K*UeTe`}v\?r$Rgtwam%{_6(Y5vA8lq^y`bb<Hjh4-ZkYSsO(bNKUx7Ucw^+S*GK(vfPb^*FcF>$jD!Z16~NsC&o4zX>~gLjY*5+{gOkbCQ7s80Gf2NIFJa51{pzy2LQL6Q@4*->MtZ>cb&RRgF;ZqtJGxi1EA!i5XQd-Rr%pP5E^DugJ8~\?p!e\?TLT|}QQki-Y|&KxLO&874\?FX0tN^8$XTU8LrZ=c@9ACLo(F0xzipE5NMZd2%o07@_Kx;|X|Tb=PL*G7TRwjn|>e8O^ib(0EZ1!1O5EmKwXQcM\?2XF>V*Uco%x28W(rBaWFC`F&^addOu6~@$73@=h`ni\?E=1zR&u&=9Ld@s#XLp+&w9<WsGThtEXM64D^zbpKYG1->v0~>XxYBfsOzitta1{D!j2{{|7q1~tH^$S&-832ST;)L=qBO7&yKHU|GUHpW~f)9R6;P;x&Aloj}>RgV2K=BZopB-UoQ*t;m{v2L!Y|w43O~uH_cvRZA)f#yb;IzF`7`o$j+&1hd^u!yT-zJ55~a$R>PbhO\?;7c@3+Baxc|9q8b>w^nw2y#dr2zC;D2*7XI5C$!r!DOeMdq$*P%NB((|=Dfp;F)^+zJG3$U-zq\?)2wMP<4;UxS_c*l\?->i@*|lIMMbO%J{+kv^yXk(>+g^^}cvctz)={*_|h~K_o0a",
")Kc;q7z$|={9$IlYqk8k&-+MFYV222^qvrT;av|OZ=3>Y4}iIVl%<^Gd>Q#euE)eV;Zbk77whMH<`D\?E_E>)}i&*{R1dOIzkSvO53a6P9co~VGyt3rSHjUNzUw`clYlz>{-HDkEgudLtJX4SJLXMp&ckkg!7X;NK0r(LsP811e<Fz08nKfm^os6EO{z})90BhP*D-o_w6!8OaQj@;85k;Gc>S@UOatRUjOh}dto*`)doj}g!IEae-RtE@`jo{2gz~\?EZ!^v9Z-}HoHjmB~wEHI0n_F$7&nDgA*LaTPxjCu4G1tnD%LL{Xf$kOKHV>mXi19zbLQT<Tl8otq$4GFWo)~0-nftpvn!D(c+(U{symMKglZ2i-;NKc~iyx=LN)|rqd4TX@N6jq&y^y!+_3do$%eN&XX_xYr87qt|i5xz)ZMkl6DT5-DwBhNT}HIV(7EI$c*1{Q6zQi1+-Tx^sc\?byGmEUFub%N2f=Irjls8Z`k(o9#YZCco|V4PkH\?FmfZ_6F4ayPUa|)vQg(!w`DJEc75dzLeYLZch#Xat4SOwU8Y%RglOW1R}r<${;Gu0Llk#rv|6(wbzG=GChsmH)P<umxk{Eu4cdA7o)!utv2aMRsT5E\?%S_$k`k-xjr_T=ew1*w)&L<Nc=t5*xhIF!xWKK>FrFiz2;H4C9b|V\?wE&v0IaTOk2\?xC5t%V(Iso`q7ADff~l0Le3+E-<ZZsfb+uo}@\?WRn)N6{aR;G7T>um1%|YWX~rey&^##fhpQX0>I4)ltBt+$O`vA~Fdu@BQ9k>UHcG9(^p6`^z2-MDGSl}mLa!(!k`!7Al5{J6>d_KUF*{I3\?bnY+&1prhAzyz1T63Q*WcJ1HEdE@DqvL\?xHAlomMv9v;0Xz6iw4xTCf+YV-w+Q&z<mlowt=q%-`QB_GhbXA=6B2y$b#zzV13OtQa`K}4a1#b%zGK}HFadOqWh+Uwpf#s!z28)@\?h2btqOMF^%iM^3#Pq)Z>Q~97hzPnQo08$Z)QDutr}<f1Ty)T3>Wqm;fh(U*Vg-xfW{PRE)$$f$j7*0Ix&%@*LZ+%$@N!\?WySb|Tl8nO_D@4O+6AU2>3wkYw4T^ot|1@ahm\?\?!~R!Aaiq=jb2&y=zZAsbZu@e3}(w`FxruW!4qFr\?u9@SRxZV+B1%L(L`+j\?#1AC-o{JQdntcglL*<#NE-EQ8}ATz-orLjoa!XVvkK=opru6Qq;M_9O(xdOEuSlt$KrP%(F2IV|kmJd#6}7R4{MFq<3&kApVCN=8)}_%Q&vWa741^ro8+tgPD15A#ff`FWs3psqcbsu%8ch4$6~GsVBhK)Km+^LHf3!cuM!r%=3RY)\?k<1m@cr{gc~QY3wfT6-=5g`U+wD|(J#C8ypZQ;yY5^J>SRf>^0p!kDl6BG0`-H-TWoN6<3W({3=<6ltL0-`*4;m(N5%Jw(tX`2RAWgXH3_sC>2@{DA42jF2AJJ2CUmehQ5@bn)7s0cVJ\?}i0ivH{HfIzy2ir7_k{%*<y0k)G;tc_aGh|*6A0EfS{AIHlp|R)JRiP%bl0kHdCSZkv*U~Gmc`c^v<)`yHwI|!Yy6(#pGLh;6A#j_#zyF9Tc1p|o9P|@KN|0M{gQem#Pr<wNCX2(ao^6\?l_LmM^a!Q3<QpG4G2ok{WcoYi(Xc)qwx&%A)Mv21iY!_fQu|o^zX*+Gz#q7ahY`vt^UaOC|Dqh)8iRs)#{_x|(by4T|f)F|KW@L3$vk%O80bErAi^Zem;FZ}gIkvU`n~Kp5q`EV#W0`xXZ3~rq;7&TKt_X6~e0J<2$S<qy+mDz+GF*LYfyBZD)bWcw$-mK#NIp^~GsD(Xu2+^}3!>I5U>cG1sx1lTzO(y9z+p+MdR\?J=-3CPG1l8yD\?u-CKB\?HW^p5|}Sx6zlJt#P;^_5pdDv8P~p(AO{2-^84ek6ZC;(7Io_;sz~706y4!rP!_&kBx#gS)p(a@soSOTjz<`\?%xIOzKWVOi==(*ktYD>+%ct9_(@GNa`0X-A1nsQ2TEF8<f}r}aiZ+-2Ev7DxfZNt-#ZO_V\?i$_Rp_rI(*HPhA6l@41$~LZGYYp$su~pm(TR9^\?=A0QW|~Hr3_IJT=<39x^JswQU-{;$U4HZKX)3S*Z99F+nYE$u8!4O^HA}iJ6cre\?_TY`d)^IOorIBP5v%-|I)UQDRBK=%p)$8wGf*eX(M8N)&*uLltnNLFiOJKcZ@Aj(DA#pD\?mqRele;y$LF8mp*_8mwnVjex9(5wz~UtfYECf7qc7^J_o0G~k4&^V@)(R6A4jN!+0DZ;tZ&a^_Xdn2xabi0L$j|Jdv<95ge3eUGldliPSp($QM;<-|W3}IEF3\?>q4)N_YCNTGx1W5l-Vg-y#yjAy(G\?`01Rn7hK)8K85n*v(roUEN0laE{D06(<xZpoL8jw0v3<5^OHLJg&nOFXM4{TyOqymP3;n_oSXj&&peH-TpQOE`pe3&)J<~+AqW&Z80#Z@l)|^vBccmItdTEn)6CaW<4~$MP+Xq{sba^BGGc}IX8M{Lcg)1\?;U(pIw7MyRMf&&%{*hI>eO$|IY;dvr!{-W(ZO6R\?v=HSF76Hh;Dlkm^kN=PSlMB|5UqWX+*EYCctw`Z-CL^;!dZ#<r;AzM=ngl$#J&+T9W@g|9hEcfu6e$-vCiE\?Z>I\?75<u=!pibI1Xn&@RF>KZ$IXS7G9<2dyR%m6sm}v4~foPB6T\?<^3vaTHG;Wd|g*9ke)+yUTOm{I^+TdW$40Z=6df1JkPn\?{*%jNOCv<X\?I\?xw!~e`{_;UJFS|17E(qSAvzWg@$MbcC}Q)3gU20ywk9=FzCE(<PsB9J<GoS7\?>t2CfmA><LUD@SAcLKv14ogjPtHPk61kkZo$;B;A;_bZ*LU~UX76Yc(r6>4oW3wkcyyp8a_q3I-v4HO2_7qzawOk^XinNCT_~}CRvHUbq_M7vRS_b^lI@>eOVw08j6$oA*2$Osgl;FsgccDlI>G%b#!$DccLM;8{yu0^bHsm-Kglv%5!7zWhp^H\?rSQ5c=U7edCb84<4xVj\?YgB_rcLu6dG>Le`D3>\?W^_62*2mC@47}U#nGx9wbdV6WSmgKwS62N_YK2amtdFcBRz$+e;yC^3waqHlq8;BZ{#vICQ_y&IwuVZHFjuaxH7He{z`HuF!$0E;GY`ni~zM#pnS>Ey%Z;XAnZnQl>f3^Wv*-MUJB!F$s&J7yzPc;MLJ@C~1Si&JEH)!2e7O_3%B\?D{@<\?#NXm_d{`)9Brhv;RIwg(aoQadoVf)!N(jdt=#Lb!$Ohr$}WeG}d{xYW$}eKZo7@z0jFm`I(}QB1qIZN%(o7geb5ThL5%_%8ws==HZ!rDhgnr=e!^CWp2&ph~nX$3dps6fk!oS)MX;}m{hU%EFnIEW65Rbmi4GISikoGT4c#DzH7daoZ+hsDKQq*VM*{|IR)3Y24AQ2|9WS_=p*j#l;f+$_17Si&Y4%t9z\?RWWtnRT8|;kUlP0N0RrZiBp%~Ei0wTxhfC`BWAIV#GfYpPoOC>MyPoVCpev5Y>A#|~St2ucFs(4aomKf+nB{z8oj9#3|VwP{@(zq)nwuu<t;a<7q$0p8TyU(OPUi$%(rAck%VdCH0C#5$AC4~9rDiGgOrv4q(wKt;lDE*4G6a^EM$T90%Ex1sZbeF%>=Tg9T<y3rJ%vPtv-nu9%=6#cQneQb4;2#}gI|;-RRRExUiu_y@oPaoG3Z$^jxn@5EeD-1M=%P>E_>PVSI77n2@V-f|rID|2*%*jkNrbaRBduqhQ=;L5%Y#hY2p0i0oiB|V-{IW@N>`2Ymh|tCuH9J*O(Vn_2Ku3|1l6J$@ALfIhO1@Z##FA^)%-l<%utJ;\?JkLX\?gW2jxbjmFZ${ft0VII5(Vpm94}N<=63AAtd+)tY^iXx0x\?2coYF6!qm>Zl90+Dhr0>^uIpaIM1M+7ub6VJ_aNmgmm@DYWoR\?qpLt@Ng&)ou(GaXj(#!hv8hKr~hH(ZMq(D|ut%Bv\?;dpG^4l%#QQX3mN6}k5{KQH4Bkjo`8uOGc~9v9v2*DfB(-vgYd^&N+USOTS5E5umm>=;!QulmVQhcpux!qT*i<v+>%@@|E(=Q&_)M7X<Dn;iTJRh1b-e0C3ZK7=Jv\?o!LyN+F`QFKWLZwg^17v=PuOn4",
"XaIII(F$J!C++U<t_TLOgkkwWW!$eqF2{E;c6_CX@R)^OSMlV!3ibbag7Dbl&L`Nll`de2&twEdH!QE>oY8{dGX84fno%LlHl*#I#)$tA2#h6oF8Km*-JgP&8V)skU@xRwnmsJ*07aFv>y5p+XiqzwID(<Pv#BDl(Bx%T#CWK2eGu{!TW6Ls)hW%fDy~*YR@h5;r7rxt0AZcnPpf\?;e&^}S;rWnDyNNBT8r`03Rol6Pcg!0hHFCc7jym28vhBu0Z=!>>6cJJ13IKwcRDuTPldEuUBh-dWy`6Y&Je1r+ztO6DFS>>zrL|aM`k+fI1snEmA`K~jb5XF9ym;EST@#u}&4`N57(5DI=n%#VrALzheuVN&$>^Bm&#|)EgH6Jmo{sIOZIW>Z(0Zkj4{ndgJ<y24N1j)fT9>9V3tK5QmT*(KI4npWKe<=7$kgo3_o#mmbxE#lZ3=&u-@(AL=!lw8Iv$N~p}s&^GQdg#h#zlWZ#FahE5p%Dsh-ULa!WR#Y&nZ(3z`;zpnILH5ID0tdeAPk0JxaFp)G%XXNa8NqvL6rPohoiKM_z_\?DI)Mn+`N<)j|0{\?ZL$mXdXP96b0Q3d1^_d_kI=Gj6*m$0N}gR{+Z{dAy$*q{9Ae=5umv*VW-KlV!\?v=ES(t9@6$jsQLC(T{=U@oKjis9p$rvG4H(3edv!E1Xp#R;aOT+Go8mJnz=Vv&o7xMlTRw|3>9P3=92IOd%mF)5S@i&VkM_3q;<Nh<%(}nMg\?_tN%T8Hf{PZ*KG5=&d%U1-^W=W0hT`ISSk2f\?Uj=c6KFz$Vv5}kpCRkuhU@<Dd|)7g`;OI-HhgaHQY*O|x>V>>4nJi40hP!RNWEq!IDDqS(<I;^X0<>_^!59UPmB(L~zW&9aLK\?`-t&wTSa+Iq\?v+0nkssQ!1nZD@w0R-#UYU<{y_Tf57HrW&4JipTTK`y7}-FP!XWv)-rB1Nz~6p@3bkrT&|xB;$m4r+jkAH$7(bRuCJ&Ouj==!uvsH-T8uFSfAC%*roG1=g=V&3dHj^EQV_iHs_vJOlGx\?6}!#=frLH>Am$aC_ky0\?tPS*t1GjC$fubmx!VFXBHw70j+_ZMoJHQf~EMiK);Q&`o_81Iw-frFYON|5Nhwh>6eqiRTLj=vE#Np5roa-O_4#fo%QFMhO0(-phI3*x}J44PJ-w22vni)Fi{>y*}Sl|%iTgYIX3&llb!\?gCTp%ZCdC~+o)+;G>c!qM#QW41}#xziDu7itlGn&r=rg^f0Y2eP=BW7@OQk;NZnB+T0I2xyM!X;OLi<Z+=dAx=K*4LgsPJCZArH#)hlCRt\?#6A7(xBn8gcC333#ZFcj~`>bc7G-$C0`e0#B@g+syH;B$LI(sT6B0z@*SmO>&JBx\?QltV^D_C!^owy47py#gEm=;#cL+zChI%C)JLKhqp\?43nY*+r*!-v|qN\?#P5k7)W(hSn@N-z7n(7o|ND}AXEMIx6oDBTov\?NEmn_^`THaHmN\?%26Y-CnqJMd%x6=pm=#0lAfX!t^sAjpfi8pxK)rDgvIV$Qc\?PX0G!-sYE9N<cK7F>D2&9>&X~3M#z_v1#ziioEqTVC2L8a-pyyxXkgWypR9hlO4)+NLzG;_@e0uXEl6DrlgF#x}<hFpj27oWN4y=2&f}P-(~li5z8=3p@<{WxmS5^U9TJpvShli8zFDq=`>k`w6d4^VjiEwSnabKv#WS7eH0Fwoz6^fFu>p{O*2%(jiEIqs59n`jU=qN4;N+ea5fEo0D5j{VlnD;4<FVdjr1_@6\?EWN\?hMG8-MGrdf{TBa>BSX`xd$Sky5Y}s=7)*o`yO<sRb5nd4%}8epM$kk=cn8|gOVT+n%(8--9(d`np2<^uj#X\?nX7C$*U4Hjvg=W*PZCihyM#)@zR`2c*u6L9^jqg~nK5^vIacC3ft*NK#ZL2FqaTQYm(LXt+WFAcPr98s0`v%enT&>RBMSwGh3xqdEt4e_g_T=6@eq*cr<oy3%pn6e*PGbpoZYNTi8QYu<(J3YYIR){C+jnbrQ2}TSzt(yxr7|_XU4V4a\?eIj-ESr|NQKfN3z%K;KsOqir(YWj-Rjwfc{\?>{\?mdMY`nk>s{e`;5oad&fI\?CJ}djxRHtU@Gfz)23;#Th$srVSNgrG7YDz-I!Z@NAZnk~A;v;IIbP4*1C<z%3hYl+S>El<kJLD@aeoh}N)\?YSDo0F<1@gE^<ZoEyhAqJv=Je)E>sJ!qR#(ou#l7duSNN5X\?xyXnofhM5H+LI0w7^Wq~hzRsS!3tvS;JZSW(w<@^8h-0k=D#F~=CC-+&uP|{JTNQyXi5uaDjaIW_U>T^5\?*aLR@dmH3;Ht#~cv-^O-Yi-5_<+Z3qrob$zRchw=+lUBYD&UB$;Q|TdBryEXv}XIfvW1Ho%aA+cU4qk3ma~|lOapen-\?vLPfUVTW8**i&Yt85IwLp;tc_rDQ3!P^;ClKkwNAdq~o@;s=6W}#pG\?BO&NOxbQbmP6<;IKt$cLEf#uGvkukxNGOWgrW^%jUFzZg$*L=6X|0EZ#g<CN5)QG8-bU>Fibn=~>T&=LX}+@rwjI2ch)wJZbF&ymOTOXsbjKwSDIMEaTzJL>^NTR)nGDHgNS\?u!{5Q$Q*A<O!5sC!;2~#juzryh7kNm51v|(DJ&*a*<n1f-6nh#48&QM_kcbO9mgGL06F4\?-(vf|A_4H~+eb@GK}1X#F\?&r$lDF1+i_YMX^~2*gVSQY<%TQz3M7o~pe(opp@hQGYo>$jV2M>Jp=%bvnwXVQ2JX@0_EyTnyxXCA^fkG=J9G;(|S~yfHP92os5g4*Db8y{C;c0l(PZjZv@sY#R@`5cj3ZA~OzX@!Uvyk!|qQ*h#(ZPAvO$YS){_%oi(hh5}o4s*%=Ruxy;8bu_{FaR`K_-}*{mgOk`+(Csv#<A5%u%aOpuZ{oCwGjdJ<s~C>8Zjqmh}qlzU`u395>L3XhFmb+}}_w!JAzcBk(*C9Yl3L)zc9=!el~1b!(QB)k*a|8c\?OcszU{O8{{VE0A@VqYXU;<qvh+L^ofO@w^^BkJf+I!d!1XGvBm<LbA8a5ux_&qOx{TYpPoB`1V2*MXih~TDs~Pk9Sb+A*~9YMF}I\?RVidZ;eM2gs!~Q!16sMNwP@*@EFIH9bfx)BL(8J-Wbr>>7)Fa#!cEp}^;KhjxenNaREX;`*9KAmBCbDOsb#o4ZPJGRGTux9d0}&v$_H$-r%Z94PYtb2}b4;OL{wP=N0{LH0*@&K;R4@8BJ$;NK!S<HA*@+85RB_mMG7NAaDOyOj=;Fr<^#1D^W\?)YO2dVhBm!KZ4Ap2m;j|tC3xmIM!`09dWP^C(4>jAz(00-Q&-w3+aN)J&CC+lP|8g>OGXkv`){<k4bTx!ue*8)#bzFAk}a*wNBY@|N+k8W!I@-T<x#%D~A89YHJ1SzJ59pKm\?mhyMQOk4WPmSq=(4A(TDrHAhG{ctg`*VUCb1t_(+zS)^p\?Y+^@0=QLJHYT7tP3D%!AL&F{\?MpitM}SE<4*#-#%FFoTZ8uY^7Ke\?\?2D*u4^hQcFpT}8{bVZMmJ\?+LnIrZQl;zVDrfdT~J66JS83Hfynk{x==9AA0Mri_03Op`MFH|1Dc>RY#MofX_I6C&rotID!19nUXYhr(!*N;4p=BK|6;bEc=}hx@DhiwMS0jG<k`LC$KhrKu3<0y>UHhE;\?3rJWfK=zy4x!gGqJ17sLIkRW7aNJnM$QrJ4e!WmT-xZgX>9N1_V8s>RQcjMKir3q+N6Uc@rD7z!^6JtRp\?=-kxGnYYhHFxOp4OE<=Vt>@7dS!=FGm+3t!-|kozz=hRYIQW5X-uHg=@C1g1mK#|ZH3m%reYod+x}>N+*E6n$BVbOUmB#TyV*Ziw{tFT1rG|EJ8!6b%UJC@Tx1A<4P1lc{MhUEv^88wG$~9fdy$>S1_y^pQTCZOx)mcskivCaJNR6pTrC44\?b7uk_vce&BvdmpSi9z;>FHYo$^2h6MO\?yNYBddoz4&^\?W>j_as@=K;J(Ju\?h10HLPn!czwL9C!M*iZ3++EnJ7{K*Qj\?bs5=MkK50EqvaN|\?6z%4UA;<nF^QD0=rouYh38NS03wg|%1+$)SsM|LJHRC;$Ke]",
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
