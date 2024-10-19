// Generated with https://github.com/kiwiyou/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

// SOLUTION BEGIN
/*
use alloc::vec;
use basm::platform::io::{Reader, ReaderTrait, Writer};
pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();

    let n = reader.usize();
    let mut arr = vec![1000000; n + 1];
    arr[0] = 0;
    arr[2] = 1;
    arr[4] = 2;
    arr[5] = 1;

    for i in 6..=n {
        let min = arr[i].min(arr[i - 2] + 1).min(arr[i - 5] + 1);
        arr[i] = min;
    }

    if arr[n] >= 1000000 {
        writer.i32(-1);
    } else {
        writer.i32(arr[n]);
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
"00008Xg&Y{^tNsQ&<PSAbP\?PG(uu|\?hEFlL%c4400#7H<-&aDHw24~P@Z4a77o)c#3)P)4Wi\?F*JD)^-%`U*r-i3MKM^<=C=m\?e0r%G(j_PsXJzJ3m+N&!nvs88U(pBA+l|4#hR{r%btepteb<Yv-LWy\?+zRgi2iilj}%=^wVS`mLISn%;uqLGn!)is3-l2bJ==PJB-9pvUaFFl+6=f1DV8D@JlD*`8Qpg0\?1QJq%RXV)iP>9Ry!=z4Q*X(U5(}+7}36wzDf#jd4Uo9WLj1fLPY=cG(O<|E+6X+nN|+^bfty>\?HJ-bn;svsU1}^LoV37KW932p6h7z6ly\?V9g$&)M=%PJ(Zivf)B*(r!J>\?&C;gR@9hXc+l{5K`mIlpyJAHaaKQn(3+=F38\?v^wfnBnHl^gTE4KJLv$0wfV+GsP-2g@c0q7x9>ga|6fE#}RtiL{O!usYKJ$u<CZa&3A;=!lb;{x;cvy>(IxXFvQ~g+Le{6ve3Qz-_FXf7=G}dpN;x`ONTJBPRW6-)*6C\?LWcVLCtIc&V=VjQteglj4x!coC0A8*S`10B$~gcLJtO-JR!n^ZrL|\?JoI_+^+E7K-;c=$m{pA+Q)Cv960G;vZB^\?%)IPnG`|6Y>=vO39Qnm<=yddvRVqY0c-j{HvCpNBkF{z5n)>R{Ls-h&DsD7YnjK*FBXFv(EY|CvE8Jp_6&;pk0}0)aXG5GdFolH;$w{T&7q%qw}C3`W_VUFvUl4}xt0L{ca\?4_f15>8G$AX86U54T`_9yB+KG6mitf&an#TWQtYD=End^01Sh+RgqpPY}7(0L3clT!fdU7<AP@@qJl{vC6@Co^c}~&qE>HPi15>;#\?k+avp6qfywFA3OSYK7ZEG{^R`YC2k|-l_XQz%Vj9ugS>+TBDS9KWDNm<RkNFI@Tzg>^yh++R%;>i&);P~nDp;DY787)QK+F=0hlX9t#R%Ynks7E<X*ZT\?YEmmhe#LO%mvV8>!L*i=9HM4Nz42Vh8B(`50`R=\?m<mLTms<^(Y0mzyXc66|vcY|=R%F*<9BQK0Q8wpRPl|bo9+1%jtLmZ`^7S#6|-W)hNKBz&87OSuZLP4nCQW^0^<}1Z(3`V*jGFEJAoh5OL0G2zfY7GsrC}w@tEkKRfhIBG>K4`3l{go189%@;dN^^Uubg!NMKtjt%h`5+Oy*Wmjo5T;kEd!0}GlYk8f7mFs+cvbLY-lTkqfG;(hboywe_4w|peMW)g\?D-{53;|81%MP`+RAv0AR@NQhII}m{6ui9k8I~Gg3yWezAzJU@{5\?uxs\?\?Yu4yO%^IR-X#lWg&bb<DvigpJKK8|Y}jwScs-Lq1PZ=~86D_dbV%){mBH\?6O\?vjy)\?ENQuWDjf3q)I2$mi7vE@A\?_`1yU`^r>SINCQ0ZZjez35Ch;k6t=07r<oK$RRqqaP57IHm4)P6vE0sFL5N~uX3Pkco!vc|m4I$x`tBU0I51K~6L5j8rX5y\?+X0QaB1w=WL76\?Z39!@=YUlsyUD_+5^ETW_Jv>mC2QL5&3OTM!qx06xb-sJ8_$K3Ln(;XAPXFw>9zM69I-x#Gz*BoX&!M;u2wk&fInL~;@@Vt-@~c=ogIhL`oh>8X8VYw+UtNDT2O))s5<X^+;*!w\?4\?fx!=fKj*iw_;9au_)j&<=>)xZ3a7E<c-A7DE@U@uwoy;cnejmb87NUizdLtvO4&|c*b*J>mK_7=wxhq>VQx-FhHp5Tw9{mLc|HHlCHNJ1\?HX6W%|i8Y)+BVuZ_KEuAg$mdr7vvn36|-eSL(WyL|v*H>^GO>u7C31O6mASE8={Q%Gh1g-6;XB${XZ70%{)K&3<}K#MUKgX{|8Qm}R}#<{o0V;TprOp=r*4=N^ek+;RYNcISm\?7h~emV0QsUL`j}94P<(u<J*(L@GlY@zGE`o`*(RkZt+Fqg-G\?XCIGZ0xMAJNV8izp+9(_KnkI5=f!uYhge0u{(k\?}aMOc~^AotTMwaWsNSz`}JN!^WJSB&_Y2=<lY(3J|oYCY+eABEhw8z==@14Kx23Aiv244pK*+;k{|=>%|dU5~seWv!DfCyHz>_E-1OJEc`M<(X@5Mb_`ZDT^FBYvYCe3T=f&@L2Q+^oxPM+k7YNW_z>_atb~Ric)|}9Wy*y5@\?a}Vo));c\?iSB&IY>5vxZk1D%vDe2Ycq0BofWqI3-c(F>~SqLM6Sk$nq_da+1RO7=oflM0zfg7byimJVwSc^FR|*$TG>Z-PdfO<Tbg5<pI>l)hIq<XiDXuG\?f++qTh7h>75Y^_|hG!hL`9ylUqsGjG%GXzF|uGHM%K|B253ZM#jyKGLIV`AT|E+1|mGYA`9Reks<SE(JW{Rm$D+xiRZRQZo{uV1mM5R{pa*%Fre9h8<5k=Gv`sUt9WEK3aV2di)CHS$qEjPab`FnmQ{fPO~M0(iSi!Hz\?ZfdtUZ3Sn{@goRLsw&zK\?@uy{A;tipy^6=O={8;uSFwYwo7<9LJ9$urb`-f)Y<bTDOuvK;{>)V7kczpemB6RY4>fAxF>f%J-M(G6xS*XJJHY-xv+7gom{5#O2rSv7c;}H5ueem1lZpo{aEd`%boTsRnE{G|+YS-fsbdkWok{K(NEy*}!hA&HV(d>;X{uV7PLlOb-$PIic}I7t_g{H6x$3*}*K)M`k;zjaBv{|L|^n@&af09gQvW\?AlcB@u-%>(7phg&tK-Mr$i$Q>o4k#kTAqW5)r6&N#b-z=$vws-3PNOfoMg)Y$|#<%!aRFtWWehU~>Wd2VU>=4^Vn}eWavZg=r|RDbhvf=1u=8>f0H*om8x&=>~ozuLn!((Nj5+ogO`\?50>IV<mGR}JZx~m1RT034ef<rf!lOk!(E3)lQw)AGj1|)XWG3W0inKbH#%0o7bogmF-L^NvenQH9-&O%FJ<H6E8Y`Dan3#upvOpb_BIeM5u)pq4Q4thZbSCFn|6yPJxE4GW11lPuHEN_kJfoP3bf\?^{Fi>+-<7{H0X{M=VRHO#sJM#1Mi%d(2FsC0CJo5r>Ohn#jzWTT<6q+zdZH#MoJbR2eBl`&IuAYo@54xO^y(67otaXJZc`O=^)Ecj0DyxvD4kVdv+pCYw7Klm5neLQViC#)Rqb;U*^q@\?K=YT5F22\?xglmxlLqt7yCBZTyNa-#HqLP)rK;hD24E0%S5%2{*Ymad>M*-E)#u!S!4eIG1\?=j*|)q&X!m5j!|W)*}JGn~LfjXXS(&KDAQT}!)lWDwFk;=3zk>PIL<5$L%2xYK&PY}kkesamP=ITX%kheNydO~A>0ZyYhGVrRviO0cUwRUy)8zWKVHg+V#8P6STL^dEQBtCL#+k6$Rmo!pf{IjC2JxMZZ!6yNLnuExL9S2tk}Mg%<sqZJ-MlDU+qafKg0DR0NK-UGq!jzV09VG+Aw(R(LT*ijQu#NS4@spsNci\?h$s>qp7|ifXDU*A89duSeMfkMvj-sq;bQQE{&e1ArO*)P_Ye0h$Hz6GRz`(O7l_a8bziU>FfB@+6O-eURX2fbExoE&}-MAtQHfwN)P`U=Uw|Cq{++);j|dkxaCahwY`&\?VPWjg6R&#5G;9pA\?X@R$L#bnZE\?Kf6=keh%|8SSa=PMn-}P<hW%ABC8we@O)HpiDSvnd2BM`*aP-5AKeWDAwT|gl`#(qRx8h=d1B(GuzOi(^;w9wk)7rOO8!J{#`^Fr2#(%J_IBkq-APVT)iPI5&tJ$HILYBD3mI={^2N3<`}(=t\?b21{RLpL26+r+\?pM-a%1J2~wnXhrT2GQug)Hbj<Qqi>}HsNvo7ZF48Gb^R`2ZUu*P`Lz<k}7\?kF(S2@>BX1N$0dTQy8yFA+SX;pJKiIHa+rqogwhHi_#&B)$`doNs2LaOae=bg|`%b0Cu6WT-k{|t8}zjv(rsGRhRdjlXEoZOjL*aaqH4v&*J5QP<xtUVF\?Uf7ckWe+#Amah_ydj`E=ZJ*u<9ifCm$Y8;7u\?R@X38eU7JEj{sp*`o~szgV9*>`bkSTbS=@`88BFP8trhHf3i@^PRw(gLLiS~b{_*&zx0r48A6LQ%p03z$q}zKHJ64>;Uv_t72FSavK|5lHm#TR2N^0#lB\?jhVju4vNw`6w41{RoO7n!F*|41N%*Epa`wflF^QXiqgvc@Z)bozs}7id9Bq^Ha71gLfR*W",
"Oh4q1<S;^NA3ydJ%d$j!qhqKaj^!Hh#{ybXQYgOPJ#ZM5$k0s~&{x;YErzj@kK<G0`<E@hr~R9BRcoGS#>{I{DZEQ$(0qP8+j|s&a&@0W8%Xuo\?uM{cHg3wpi|A^~<)q&8zdSt&xb#%o8*H<YWYo{cVr+At1nMXC2_ab3bH{J;LXP0+nUK;<!4&3Gfsv)!rz4w%yjIz7>++w\?0i!l}auxtlxa%2gzT$J0F{3Aioz=wy2Xlg-6gU(c7oN{\?4YLo%6E=9{S_Ty\?kwP`9-KtkC!W8frg+nINzY\?bG6{rAa#Tr_7DU_y;RtMy;gtIF!q_3b*@o;=<8u_%6Ko+S|;CsfuNgg$}qzzJF_76b3k*6Y~bTp_R&MJUY`Hyw_)Ki0mtQ}O@xk<f9HYT940A33<un~hEAp}X>*XoZfMoAHyf+&YU@kx$agFH)viR6eR*@DD=Co&X<c7$h8HM_$pp$P~CaK~%H5s5WZM&9I<Cw;;KqM`1akdzx>kR`vTUJ^1RLl}OL`09n4Y^RU>5JRvf*UToBfTxtThhatts(@GlzVf-}i3*<A$+{I;sNF^MKISJwMvn4)Oj<mqE=ro!Y_;&pYuq%m5PZFtRKG0QKT}y`G8cFj_8OX2OddwhJ<-&x{WvtWN<`Moy#;g=k_7^IVfM=1j*Le1TIs1SrM_6#W;uKq;3I70b<^9jYC7s}%k*IJq_3ovzaEmXvH}2RCbX>cwf*H|4^rjZ^nJzne<K9@YJbUV=f%NdI;c$5pJ^^s*I24(Wh9s(qjKb<VgC4R5bBHTEb&y|IB}nTp=NyF02}86aFE-oYKVfx3{8IKzq\?#kqt{+JNS#rBIn8)fM;mp>b=$9Qu;DHvkTBgFKb@CBxDkcugsaUGOvs;xxZE<wEs-sOtnPh1v6k^|$<fhRN=gr*cFfNoiBQRoiMqIUNCmD2zXbp9aDyrXdL\?iy5&WhJ<#_5@q0p*AX|e3<`4GlxiFE`tR&dm}Gze3SrIwXaQX^UMD;C6(3w6B11huymE\?sR=p@g5H#t\?DFP~Fd7qWGV2N*)=Add>KdpJQYL0tMYEqyd6bYFZr{`_Gdy3!HA|<6FusUDy&0WH~uHniUS5D_B9bBb|$b7lDSkSzf=F(HBTD7S6$0pNJf-DDiQQPfj*5!Fh9B9eE<Eeuv%QfNsQc)<Qfvam~bKfhb!Pz&1`Bi_s\?0gNH|0oxXAHz`4JE2Vt0gST%DE<#0|s_p-u%3rdw--|4I#04<-`|AG}RYZMeW{X\?Uyg6^z6^I`NYp__5teRo7=#krCpTo(\?iRF6KG7jB3w^DY&`A6FUk*\?YwtBb1orr66=NL|DT\?I_B#}Q*!GzZ-}iSYTY;Nq2MWal&ryJJKETXs@#6E{{KN4XG^H>d_;xQ{Xh{-r4H#Y=a)bqQ9=3EjvfZ_v`oHB1jYnEUyxO<sf(7zg8mp7*%fTfpZ|wwmGK3p&YYbdb~dcQXgV0cdgPULY>{%>En@W(|8vh3k{^v$EaC3{&&*+v0I4DyXJAD1$f<O9hKCNwPw{a\?Q9}LV)zW8A@#w#ksZ{uQ!cM0|x}a4+Jk\?pa&;u}x$2fufXBhUq0Fp$}KeE<sA0f|IxU&J|!J;A57`pB-|0Nr0y;g_v\?$WASiGupVMrcPORD+#F)YQx_fvVJNpwK-FK31qAouTwiuzHcG@K*gz{b_qSl}sj4Rv#zj)hTt!\?)3\?H)={X1XiQ-d&ocJBN%%IL57P8U\?4EfS{vr=NO3teS#Jb6xxj5j5u|%QAIR`q!$Wu`UUaQxef)lO;bj-Q)4=*Rn|AB^Js5Tsj3E_fQl=f4L4R0(bhikkl!P_6w4ekqQ`pF~XtXqWp{BypU>\?Ku1a587k+b7dYuXaHzS;rI{u`2zu+;v-=nmlONSJUv{BXlb#{2`$nC<#<k=gW&75pVcapBTt}3lj*H\?2TjAmu<YeiFT!E^l4tjI1y>UGv-oEs>jkC)b*)d@CLD;HUi1!65Gs%61$T6`)I!QCXsxwE^{Fe%;Spe%I}zOHY^k>r0{N1NS5M8QN@Ppba|rhnRak@df3^nh~`QpX9TH#Y7%Fzq<E_lCX(Ap9<X7m2;Gm_c>\?hZ&3R*jwj&a7>%s=9qV<^cy!2u9Kp~fp)Ap8%$=q3;F}v!M3&M8PuYE58B6s$Qq~!m21d6r|W3`sPai)f&J4Tzzyc|CB6UA)!S6p;`U;e)(IWEHrr9!WGg0WWNa7>t)Uw_c\?;AX_3x{zgY40R3ykg58TO)gSbnAKc1*{\?BHD2Tu|dI5o(v3JeX)pFG(qUf&DgbH9{TCfWU*SS9P*qtWK5Q{&<$ySJOuY`88T2IPeZQq%^rhOE9v!RndbgV1LN_@FxtP50p<8}p_B$Jxo&t\?Y5;_K7sl3J1DBq9wB^`!<+P\?@Mk&cW$6+e>P@)>IJv$s4t!^%$2LvUqU7yfZR`fbq`bG~(7nXm986H%7pHZNpz+{!Bi8^lNTThaNOPx{(_Vn_fTr6IxwapsOZBu*z`t<PbbMy7w=H#<h(dU}nM4xdTKuw>BZGuYd4Fg2T>r;JDr\?cH*plK^Y0F3cBo=_!WiiX2JiL(>>Bz-;0`*ZMTj{$AXCfY)HX!<tGKx(A94LLwS~rCs+UbyzfS+1B9I6JBnS=@j2WuhAz#!aMgvKeaN>JM(3r6!W>wFZ<2Ip_C)53sfl=C*\?=Zqz2ZgOM+HGGot(-cw!`;kmM~zt6%9>NtZthnl6r&vl@AXu%*XYRgI;i+v+pg5VrOzC+y&C9YNW10_<(*WH{7!wI+9(&h9o&0^x|pDIw0a}2(p4+LpkhMC6a_*LnQ4|xroAh%`9PF1$#wl!R&z$\?z{|sWWUeJ5xfdLQ|}wsRH1v5N^fQc$ZJ=x*>bXMM^1%PuMj3JUq25dr9;ae71W@8JdOO}{P_Z#_2u{5U8_jl)N!haO8D!b33ibFb=_MJm5J&TMv6LfLoJdc<35i>da+EnZ9u9pw1cBR>9U96F;KrLbkIg%2{0b<J5);l|IL_`#sB~S]",
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
