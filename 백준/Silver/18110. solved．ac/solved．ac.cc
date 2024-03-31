#include <unistd.h>
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
#define BASMCALL __attribute__((ms_abi))
// Base85 decoder. Code adapted from:
//     https://github.com/rafagafe/base85/blob/master/base85.c
const char *b85 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>\?@^_`{|}~";
void b85tobin(void *dest, char const *src) {
    u32 *p = (u32 *)dest;
    u8 digittobin[256];
    for (u8 i=0; i<85; i++) digittobin[(u8)b85[i]] = i;
    while (1) {
        while (*src == '\0') src++;
        if (*src == ']') break;
        u32 value = 0;
        for (u32 i=0; i<5; i++) {
            value *= 85;
            value += digittobin[(u8)*src++];
        }
        *p++ = (value >> 24) | ((value >> 8) & 0xff00) | ((value << 8) & 0xff0000) | (value << 24);
    }
}
#pragma pack(push, 1)
typedef struct {
    u64 env_id;
    u64 env_flags;
    u64 win[2];
    void *fn_table[6];
} PLATFORM_DATA;
#pragma pack(pop)
typedef int (BASMCALL *stub_ptr)(void *, void *);
char payload[][4096] = {
"0000805$*sfg^7Km(32Csv)e2*@$efUuYtOX98Ol00f9Sc$vMh(Tu>P9^Ou-e3+}6sR9;vG4yL4=bJR|QfjjLLICia_Vp^5vjPR;p`ppIvnk;|i2eA40nwbMtUo01Gnm*G<=A(V\?=;%OwE+Mh;PypP1omkqJ{wG@qprhUGG3{DJi*T$Rl-J0%ND&!0MfXh3db}87!*TThS#LxCS\?p5;4D@1ZQ0!%9iY=\?m}A\?+04=kROOauj\?K1+2N<>aI\?2sE&B}jc5_X}dTbh6ZJoMu&_4*dMR5X*f-Ai{1P0p4gLK23TrjTawKc$$YSWy~LJhrUb$xo;j40D#n`V=LBLeXt4=Q-_|K#q0|ZQAnq42eliy&r5iIv\?b@zn3D!r+-Sc-+RBAz3@0UiMTTV-T_burcDlk`@DJIK=<@%FO&oHW5Z9mOXr<t6@CtYCs4ehJFu`3kDGj5+Za9I9sk90n\?A5ie&JUGl;^kPR+{HqzpD%w|9V7T3E}hP&B3M<{BjQIy!!&z@9s;Eq<0v+#gpsw9E;AJ!!}x$d+B>DR^|gM)NiR+sM}6Z<&Gn\?IavaS{%)(=3Mr!&f-oKK21fJ=@mU}lm#XQvsJWrkrYo=e}P1Sk7P|4ds4smDeSa5_M;blrkUZ(Icz@!s6nVkIK&=sL=Ym6g0>vM<ktkQSU0qb{GN{bJdkYCmM80O4x)_K8dYLo}30_>6HzX+E)4IL@l&+$@dyi()pcxi8<1VIqkr}C6Ea}Rt$wcssxM#lL*m&>1Vs^HX4\?ZOk24}(83+n9!tC;9\?(!f)sOcIU@eioLzP=B=I$uPebvD$JCM`tu2BRaZ%Xu2Q`\?u>VE(US)X3{GC;Nb)6}m(*h4fW++P@3}&VJF~3t5q$Y#(#+FkV%J0Q}Z_`%}wjAU-M~gw(kPG}|Dg$-m`9Q;jur#uqUGxl1yJZ^RWy3B5YKKVq))c5&&(-<KTQ61\?6QN$s%A*SyJ6qHR9l-}0WAM{aI6xz=*%-5IY{3jxWj_Nga7vt@J1=USx3e0JCjc@l<&GC)w}-}+E>iZrmP_|7r=mivL=o(GI\?u5G)LZ{J&0z9=Z5L=\?D|<(=awvkEc!@f$QV{bQZe4IU4DUE4O|`eN62pNFAf<YW3OpopPygS9)&%;02Edf}6~v<OldNkgNo@|w<U*F-yNp_h<<}het;ST}Zxl{XmRjJFR;=&uUCbWd$j27)%yLqun;en-1ZC5Fn@o%xQK&ZGOA!H!k(h_HZ_<bKyF#z^a3v-nmUjJ!Y5c@5gqE9u0l$7^M3Vgwl2Ih<l>Q|kR`3rl{Ptfv^`U)G(L!;AuqFUH=p=t<EZshyZUSlGx3gc9E$KwWUzHsxrMJjKh0BZ>MaateAbw3${2_}P6yO<9=Zz3E{eJ0mrEdKzqdjQZ@uV_ADS7@vmFR>e%$-)V)Z4*Rw_pL0p\?KwS>nr)Wm@15n3WJ`y^XV0kk8j5DWZ6p7sJJ9|$t8EJWv`UQJr=+6ZweeAM@HFET@HZjdkKGSAc%ho9s*!jBrDmYF3A$>wi+)n8l1>9Eb(@BH(qGYxB4Pop\?^{r|D7ISja|Ot#e5B0Zs()+iF^<Y+!pio%>he^6Y\?;40)WbfX1vS=W}3AoQm-CilHX8Ak^cp(FzM{hZ)\?CqBHO~oF5WAq*^MJfApc;ViOA<@_^%SDl<{A&Hp4gDIK|7#AdlqF1-KWS0&(^aR&Nf2_gcoU$i#GI)-4ipADGD#Gi_%LbhcR*+HQw0Qh1-6P>QHA<WQmHoc<6A7$9\?(1N!Gzpf%DNS<W@C`ayspcoQ{Aj-`PfwNqR~9r)l*D)cAHY}Xf7duXg1^{oK-iRiI!yF$tjSKoc|b$WF>OYK$uqtWGBL<!K)j-v>Lgp%f@sp(l9KjworpBSV$qPy)$#sc5wkXK~U\?By#2;F=IrKu9KH{hvN95-\?;EPUGQ1QD#4eOwi}blnJqn1PgV>nNU8@rCr^3yCg5h\?l1TTki_q+SbYlBN>>yqlYE|o250Gl>`Q<nX^j_q&Y1@2wKu3U_0B%Kn_W#xy(E`q%fE$nMxuiQjdUb8@!N\?{0lT0CpPkC(UT%P3\?Y>d#Yg\?$&Gla&1f10NctR}n0_U\?a)b>_XGB{e|JZw-Z@LT!Bp=u;Z-`aA>wp%WU*gT)eEXl}d_3psXR+r;*6L|{NDi5\?=h%wuP_j&ni76P;pG(HGLMty{ZXszUKs(@_n*p|v7H#_WaD\?aGFs-q7Cm@!KZQy90Vk`33U%ipXBCVuVHs$*Wi)r*##@VR~9T{{;lrTvOg\?vV7$Pq<wdN>(jzTM{BUiKM*^+-<vvBEH!O+%uh2}>!M%YoN49IFTiFNR1~z3ezqZWi_s~a2BGDzfNO@rOA>Pv)*Mm*^0Q}nJ!iRPD#@O1d>rF!9j-t(ZNvj|#^Ny$CtT@L%#%4QvVu3z3U1vG1>(#Sin!2@$(!KA6L)96y`@VaDc$H_izh=#nZf&lQj-5N0<a0Qxvt!j#n+1ksWg@|mQ~tor&G@eOg6S&c)L_|(4dr$m7bCDwDtc+Dbk8n18v}a<`C^Fi}V9d<8U8|FDjY9t#`>{xZZs>ATVwK*b<`@Xg4)+#R$&xyQ33FX8%>c;UFcVlo~Ta|FY+1q*D2VW=Jm+p{@OGgfknbp>|hhu-W$tkw^Vi^HC*HVil%{nJR\?CC7iQc(I)p)fg&Bk&>z=z#Y60A-_&{Cp6}NH|5fg;A<%{MBxP`nJS(ADW+g;y9&4qHo%MF{wTR}ux`E7f8SNKyKu5QDn__<)8d=Sy%l3O<P0_iNDWknHOI+TJ6e0gSD4e;x4t$`}wIlu@WP+)6^\?\?ReQ4Sr;6y%s6\?8ZLwot%lOIC_=IcxDP0x3K$P!fFl8eMOQGXlQ4g<dv(7O53}ugoPm8r6~(\?<@`KiZiN6RDolN}E3hx}3kSdB#YLZ!2UjnF#8-YLkGtj;tMqSQq\?vU|oQ_DXI+)W5NR3y$NCkn}7w|\?^yB9TiH#Raeaa=VbIrkJE7LQ_JT)m=qQ&5frD(!ifq\?jO_js-aJ^F58ij)w*HsU3fSlSMJ}FHX31Dhp$JoD4bH`0{=ZLp_c{eK&%3eHNW!@_$u;vdNS`bM9^FNBbd6*$A`E6i3#{5WMy\?La{$99!o^<Hx71#!;9\?$LHYj`l9Sr-;oAVkN5)Qn7*fnL!}KFP6`YBn#wZ}b4<NGd;||HWvK8x5B-Js5Hg^=6gmvo&KZvh^mMGKP\?8RDN;Rm*Ox%rqC*4(#Um$0aSsN%jSA_6Jg!%S&hBkj4a9UDwzB}i|XV0N-_--I+K=#L|Z$aJvvBS$1B7`W&(d-cfQ4-3~dJhk=capU$TT`7TLw)p-CJRYKRCW%vY-XKOi@r%vbo5BFwl*t_H;ooE;G|A+7CGzMoUZLP3jB^!+Q`_L=l\?_0UyJmSpRzoBA@RDtRjHT70Cj6sxzgSf;X2s-mq*cliFgeUS4{Y\?R`)*L3!9)cb0C*&qkmjiXF!CS2dx_7h%j(TGii)-L&)BGESUbE!dV+H}m>+@L``CS*FMbJxB%pnq;dS#x6!w{0R$n6TT5Paxrzuo%VeNcBvFb&d>*l9&%XNGM(a7ViegIC~\?K$OZJg_<D=Cf*#hiA(\?|10VzFq5|-&-JWxP&Z~4fVM+id\?5GTE$W|a47*7(c*25;4uWR@NsjYry_L}p0G}-FSf$Lkg}=fDz)Qv$zy\?gyrpO+t\?eL{Nhz$-fR`k*X1H{g7Utej7|KJ)57B`7}={Ut{%P^tbVB~laRQD8t=$UgUT`!tQ9Ipjfskg(Blr{=6YUZcmid1NEHwlzELpw^&`Ox8e2wA|GhoEsEyG{KWTNhg2gdP#DfWzI02`I3hvKn_=iJ23Kx9;Jth|MiOJpqF@3gJyocT-c~M;$rgaYwG#YrXA!b!lH2K+7qcT%w0{>6s`j;TE@QljweZ1pNzyQMLZEhSoU9Jg%49z3mU>Ll7blcA!6x4*s<28^)9g5xCUf^<QbynDcXV-yEyP@#1^1Y|)RG@RQao-eg$yoO`w>51Z=Z*22YwP^MskN9MjrwZCUytOue8lo9J~f#%-I\?254DRBSAt0WFC!{CsNOw9n$pn!>}Bgr~hVJ$t@Qn$&Y*8`L4=BSrj%oQW<^Z!<(e_0=|&kMy3OrBt(x_@mGcL>Mo&t;D3v&0Ss4r*(uTN@I&JT<DF4",
"3bC}I{1*pz*a|;IfXb5C\?hyvM;K\?X`{axx@6CHN~S)W_vn%$f*P=kfOLLS=MFN&Xqf>DM^X{b0J(b_KKcb5M{yb3GO47n1R!;AE+e6HyR{<O`K3Ees0_K1i(at_6%Kyro-jHJRf6++sa!nYoY`\?q`YP_~0|xNi$()IaQeirly_y+b;>v!9ZTmGVGFc4aB5(YaU-D\?W1OC3$Nl&>>dNtPaIDU_2rKV1P@+QkuI_-yEB45X\?<(`lEb~H^VbzD*OVKWyW=FcGxqWDJX^wvt41(pAf6rc7SQ8R>J(KxEg5JAaX4=6K3}JlRkTe&)sdx0|KI\?O\?Ec-\?X!-uF&+LFfp^nI4zKeL1cm1~l%wjoc9H*+R2aCPFC|2TgS8_;1kZeEy_u+sDe*BSQ;MFwoMK>d{=M~6Y_x9hu<XSyYNYE45a7keUbs4d2W+(YQOR1P^n@DND2#^|;68PG5-HTZCuVCNxkv<zDa5o(VQqeB_C%2Feu^g#U_&Z-M5$+c>qw%TC;W-D;RYB=(!6uhz883L2*~{5nD{<t)@Toi;+g*9RF6n0FrKwEM}^LK&vGe8zf0qrS-_1tu4uSe>cQR`%;Npja<H1>Kic5W#FbXi^W55&d6Zcd&;MwrZeO>*E=\?%gz&Bn^IJhx@U$~P{XSFlA$g>=>e)xC&&9+w=3-nnLp#NPRCk1*Vp2))c5KcixRr6#du&7I&0%bVJ$@OY-49&i1&9P4l#dbFejQu2m&Q{!Y+\?UjCd=wRw2@52GjNQrURuz3SWbpr5AQDBo^VG_K9tBHpWRZbTJZ)%Z2AgrH+Ekrs@G!&~IAL>^_\?v_q9qb*mkWhD~kO-=zMO\?l\?D2+`T<NKYIty85u%(JVLFjmD(^*a$v<)mYj!P!A1Z+*Yzh;2tSwd4A&V1RU879#g-Xht2Eq<bEW6jW<++6bK2#2zT-+1x)QflzrLCpR8!Y0R_QceHS7_M9I&hLN~ewzQ3ft1h}<A;J~i&6VpFiDzkngSFp&o&9n()5w%T#94\?Wo>QWl9VLQxNBfzLj}=OB%aJ~|_T8^B+njQI9Tp(RWOL0s!=HPXv@Xs<k+gd}h$Zb6FSM|E|D`N^=\?Hu(64NvmVZ^pe0}DuCBJ%KAngx2Oc<eYI>;e`>NXh=jt!4`g;+8dJ`JRe#-~`mlhHv>N)DEb#ff%K\?16}T+3KJ}UDkZn;+$q9G)Z&4Tk#\?yGWV0!RuAeL<Z!K>UctfMRzcz>$lV8y(beDzx*^`vgFPX&>pDNNCxrfKR47F>CG6djyb7#r`oSoj1PURl1jO}vcBueH~sq)FhQ<YLZNF<Jpaa}*FOd`Tl@0n#LaU)PN8S+%2Y|vkIBr~5R6X(ceQ2TZ\?7{F#(\?UC{9O`|#$-A8*oU+Fv\?RK3ilRY4NO=cqBY_Tz^<rkD2PJ*@>F6B{y{xHQsAPW1!i;CXDbCIBN7eZ#kaAVfQeqV*F3Lm2AiRWRq(fez)Kr$yE#918%Q#lnUt!y\?LFTyl8HOPJ;46Z}\?0N4U7Ys^<MS+y5i9B#3peqi7tmozNbcEbAc1!<`m$D~^U<n>qgJm93x9&VB+=lsH=ZNjoS-{\?WQBiyDdiXzRi\?N79DBo3{BE$^q9>n7-M\?3(SF_+M)*ZHLYcy=7L@#q4ijaCLrTKVuGtT^>363z9KRJsR5gw;NLc=H7I-cN0Ad_NQ&+Rlmn)_rQsfWWwBkTJp`)m*qBs^pAk`tXyB*|lXIMMTrNzW$g3K~RGgqxywk!ZT5JSRjEkRpdKLk);CubnAR2$^zcK$3tGX\?15oRC5S)kh%PQgB^gR`XYp{BqX;TRjh%KDA9!HvH7-4O`)enh}q`0`wubpyTV<IXo}i*|p@%!8P*4Is7~fE=IW^=tdn5J2bQ8Vf!<z1z-B;TUu5c))6mnUzt)51=NLXL)b-vjeQ91smot!!|L<<gX=1yt&7=L9)p)1vFN4l2(d;6kO!bz)4#)dy(CO%8LkbeYXmoYzB})h60g1CefMboYd!0r8u0{2f2#H#KZM1^ws>C(9#XVTG;MBue99{-vM(JGd7%87|l&(rixK6Je2O{W{osp\?ic3jK&JIx|Is3VZO1=)X_4c2;#TaqqC&9Ad<9+NUzoAYRcwSs_|EN*f#6k2xFZb-UFmvE<6%7#T7*H-(zxG\?A=JO}nz_kO75om*Uy&P+fT3FUSw30nNLO+;is}{0XSldQr9TU`d;)lqSUS}Y)l}_\?ni{i;xY0|euf1;@UrK`j2zWkho)lH}+DEBR0;LuhfpD\?PfOGWj1vxF{9EDniSIosax>\?_bqfD4PuP6fWWgeBX&S0N^2^PPOM^kL2m8mW2a9O+a1sntqTKyeO2_*IvYj~#!BLCbu10e2\?tapo>(8@*E2dc^AEwjHwh}{>;o@zNAxu`EJ9`q!QvtkT1e0s&2ES8K+csE3s*EpA7DN=22Xwvea$`F$Oc}OJxsDbw1E0C(+JHT!bGs)3Tqhr#JoCiaSCfSlr%#UQQ_Hb+`>PH-8GIwsSjbPNe^QHq%#55Pod{{*@0ZqfQI\?20LG\?oa9_I*IjPX9ZgeXsjiS457=0Xrc#KvLKM>45ZxX1$PeMTG<Vm-Wy1yg>fd-tdv)+91yBoIbRt!E#Qfy(xls8+O=syM1crEB0H<bLQ(^b-O;IDGCQ\?jcZp@;!t%GOHesUu4}zM$Pl@1qs1rEIySb-J=X}pI85s1BW(\?WwQ@g#<ybF%Fa)c&65sQ;xtx{Cn*{HvSGbp>xDHYG-L5MIwv~;F^Wbzk#Dk~M%C<Sy\?y#>C$LBu+#L2>Se`T3$p4jEMBt_DIFOPJ6YaIub@-3eeqr=O%bll+!`$8$X)YrT^w+*YQC@KUG@FQ;nmo=&&^pmdV2F8;@Sr0Y=Zou{dim@F0DoZmP*D\?7Y6i#%6Ua=WXY3phgd(L&cE}F^e@xj2u!\?6FK%80N1QHU;uFMbO&bR$ncne7xtv+DHH=#eD3!nl_g>Tvv)shI#D-BsGTHYx%<zWJX*Ij2{u$Fl9bq|k~-M$}=eVV}XKS`*3V{g8_$!D%$>So5N<;q{}7a2-2(Js&a8D~mC7M9%X=jKBlYTP1*-YnOzgXoxm%w5N44w63#PI`W8)8Kg8\?n-K9}oLOTV1JHuULA{-WwRvx%Zlnrm8c*`Tte}K6VQS<M_U0(~`II;r%M@&;M12O9Irg2_UY`PgB%<*a6l)2y9u^2!H;Y3Hs1w;pD}kjgS\?&M~sbH~o\?%C$yi|~DVIu+H|-+vz}U!>4Z5>pMY=}hZq0w)Fx<Lm_NaV_YR*qt80d|QV\?HVq2^e+@-)I*NF=eDj$y53yIK<*v@=Vp5bQXRGqigxLo*q*~b)Q0i-y0Ln{_XVbm!z1TCG==&f&70+;UZAx|cOLCB5Otk!xr=6MftlCe(TE6S6y3R+#Q=0@~Fzw<2gpT;1gYOf\?Ah^{Hwd)HV7^W6Dxi9`@+MDGi<-N`RU@0Uk9K$<!Hvn#}RhxGrUk^7mMPtdv7Ux^TV-xb7tRHQ)b1UDS2t9PvF8uCb{JS<<DY$lQTy@j2FK|rtzNbvJCh4tZl3#@tZ~YHo%o6>Zx4ygAkpA+IZzz%fFw)FGf6Xlp1NY^=CPEOyu$vI$QkzUaOjWh%FJwk%VoaAT@=0m_MeLZ;>)f;M+FbCs{xqmQh+%|rL;tisbQd\?>-l1|\?;{Ol$LRAV5DVWs_&Ruu05W!CcAI%W~oF*xmP_F8r\?Z1N`T;|4UNab@rqmr<bnx!#AFm(U;py7l7ECpTRq<sxy4ALuHw@sBU\?7>diUa2X79n{<Oh\?r)nR8^zCR@VF%<5V3kN\?B|eCmYfr4>+=8OS6|PY|cJsR<r_R15ZC>TiSQ8uTCb9lXq2L^J\?JZm9VR^S9@Y61s~\?&x&=hz3Mla\?W-mlZX|V)%9trjQ9@XvK(X!%N!=\?jCv1*8e#H0SM3<I~Z1gv}I4IO}HFacoEh3!f*oZfr{ZIl9PKv$UjRLhk(hy)$)b#6OR7|MmVC=*zsSR=`6mvO+`hf4f3B1~ZcEO>%BY\?L~A#p(`(xv+3Z*BwDfy5Zyfq822B*cJ33xt|(bmdx)mYvT$+)9)qOW$PT|_P0}VdO3G87}op|y!_D&HVN2B3w!o0#i*fi{OsgR0C{G>JiHaXxjNh^;$22nM8!Of<H^lvTKNhP*-VX^oKn=HEG7vy",
"q8dgtCdeGaCqe4iV+ryvtw_%=Fm}pllB>jwFwt-CpwKSQgj#~7ICE1TDw;vW8F>ZuRFGT<-(BJSb8n9Z=3smxyo}O&d*zAjRDfY@mE%D&lu6At#8)9;k{2tkB~8f8sNOu7H*Sp&\?eX-lcT$x$r3Ln|x_C2w9a1j(@f^^G-3A!SA>u^1zz8aYN`Gq_S{9gBw!dCo-&=w(-q3vHS;)k(D)nXTL2<6ZVy1=2CGbp_fbd=~>1WDKV^ZJ*MU9$PP@i_=%7Pyn8~|Y}IeTl4\?QEpJ8;;!gZ7za6e%2+_9e=0^N#A{g@YMwU)UbUN657AOeRm^$md|3oH#ZJ`nsm@(#|lck<3W+B&N^}Ci0kTgn4T6KyfZe{>wMCnEQWg{*2M&J>7+)0\?M)fK5o@kqt|8_yo7<@DJO#Ps{&V@aV;<|fyLgg9+vrh;NZ9UOQD\?R7C04GfNpkc2MZuR$cc_8cG+{`XYOfv_K-E~j<rHG(^*5M)sm`RrDT;YmrwwM7GW|A}U~Ab\?T;LQ$j)^{gnaBHn!\?RxnVr9i)Xs3R`<nfVWA*Z`ESnK\?doa;i=D=@&JrG@<z(&kBa!Zt6K_l8~fQ4p&e1=jUgm_dEKnwezJqQFn4$LT7r{TH9Inw%nZey@XGAiJRGty8Kz!2G09`%qxZ1-*=r5f2pqz-MB#-4&B<+IGY(1w#M*qM3Tx<5EQl0X#=cxJw4+dDY-@10ZAYIN6-_yUu#Nqf33iH(#D`E3*\?JSg80Ljdz1Mi2ilD<#M4VJDtBSiPntn@JU^6U@W(mqXP&k+PK)Q>;H^G-D}v2Xb_N*TC6#nbsc+qHFMaeJU3@)1ddm>mskOTtH>0~tMk;c2J^7IVsxWUAum`_Bb6H)*IEsr3ZI~N&8@+k(bJX+ZaIVi&@gjM4yd$6H;`7wsr8%Q=nv_yRcV2G)3Ht8<~+<>d24S1tVeb-0^*R9<_i#WRu`_7fz^93VYZO<WZ^K=DlugL_i=0=cY5J&dDzYKa(u\?g@0RLs{&Tm6r5PG(a$cp$)j|~TDSDs$DgX_;`WA{}S!ihhJ>>EtUJ3KU(n(gk3i>Lp|8_WzPd58tN`ODaf>@iGj=u*4-+7ZrDGz_O=*a%mQsjx*jwX6KM_&u@uLf(IKr4<%die@ypw56(^fqQ-kJhpNf{;bZ{0ijl%Kj<y&cz6>npPq|9bx1e79^e=vlpgJ(J(%lwwHOU=)@NQKX`9sy=Fh7Z9Nk#Koip~6y7zWWo_%v64zqby6Bq3TO\?4lYb6Q%#Y+iwZ)-yVG4wh~CJJIU$ai7s4gga>0_#M`FGcV_5j_S^QQaW49bn2Yz@w9ws5e!xAF-nKR$e^ZE(wRH+MzzI9FT<#hKP;T8&{S>r|7p{C_JZImb#FB_hhNZjq^Jud^ChCI<=#X<pk}zL^q7O#%;xY4_Rwi1RaOFcD&)%%OLe-DwaFHq=JkTwaCin#x)=TapubnaQ\?VyeKm)$AG}+B{>g`OmQY+J<<*OORiA%we8OS*5b_jo9Ws{2R3_zl3iRz*;HDMZ$Gf(Mj9jQ<EOJDPj\?Q>@k8GD^@UPz3uuDhe^1`pndT$Ek&y%8E@F0BW\?*w)t*{@&`@UHHZM{;-8@{G=Z\?u}$QZ{MEq4M-q|VX!C=59Z+=*b!uHxjKwLR{g-*%`1^r2b2H$Nl@GX]",
};
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
    PLATFORM_DATA pd;
    pd.env_id = 2;
    pd.env_flags = 1;
    u8 stubbuf[68 + 580];
    b85tobin(stubbuf, "QMd~L002n8@6D@;XGJ3cz5oya01pLO>naZmS5~+Q0000n|450>x(5IN07=KfA^-pYO)<bp|Hw@-$qxlyU&9Xz]");
    b85tobin(stubbuf + 68, "S5{L&R6$iiRzX+DC;$LbUQt^yz^qA$#jHt*#;i$+$E=CLumjWJ1po*D07;ask^fU5P)U)kNr~{5Q&mWfd\?fx%DdbEk<V1<#X1D+Z{qtt4{8U|o$p1)#zyeTER%-uIljunR002_xE&u=k54S{h0E<=R!RiYSuh1z~<SA9\?a}0@9<N;OanJwW5006=01!gHkbpZF;TEl>S=KysMNWo>~2tkSfN&mozMd-s{Oo_=vi13KVUREH_L\?P+H<^_#(PC)<HnOJg0M2Y#+<Ff#bj9UN*0050z0R;UR(jd@02XppNJOpwOw*iYq{7CoMK{6BpFy0{d(c+2TA=Uxj0nY!|5ZiO\?ndt)o004>ejdX$#1o;@iBm+\?Y*K!OG5Jm705k>5>TkA6a#{buH5RG#I|JQOKgH6~8>BRs50I~y%UHt#X|H_A4mGE=~|JQQziCz4IP1p#sl#Mjfng7@S#*G}#u>*4vvH}0sa|n%If3XOI!s3JLfNB9=R#pMt|JPm-_Tu)9T-N!6eb@wAQ*&;EMc4;}>jW9VA;XPa+D}rAG}`~y5z>j#gXutW@>_%X1ad=(-qGpP)Bnl#(zXHt+JpH9avuN5=)wN~|Iuyai&f+~Rp@dCDOKnXtILD=1a;$\?Rsq)k*Ip6!;`R~A(e8En0onh-iB0@;8(ND^{7CoNK@YYZ2|<V%N&mtB%6aSQjQ;=sN{wV>FkM+#NdrOn|Io=nUqN0$T|r!1USGoi]");
    size_t base = ((size_t)main) & 0xFFFFFFFFFFFFF000ULL;
    *(u64 *)(stubbuf + 0x08) = (u64) base;
    *(u32 *)(stubbuf + 0x11) = (u32) 4096;
    base = ((size_t)stubbuf) & 0xFFFFFFFFFFFFF000ULL;
    size_t len = (((size_t)stubbuf) + 68 + 580) - base;
    len = ((len + 0xFFF) >> 12) << 12;
    syscall(10, base, len, 0x7);
    pd.fn_table[0] = (void *) (stubbuf + 0x1c);
    b85tobin(payload, (char const *)payload);
    return ((stub_ptr) stubbuf)(&pd, payload);
}
