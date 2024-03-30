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
"0000804o3hfg^7Km(32Cs=kaLJQ*Pm96K)Mq$NNiGjxA#BsVS=g@lSbzc+#^=v\?5tv&l4^OtU2uOrHAl<%r>}>@+V6pb7F(vIS6<(Cj@3CyzwqA>&VaBB$!%W2LLk2_JxML|_;&8);x2;WBj^AuccD8;\?L4^{H~ejr\?-w%&B8&FvG\?Qa88dNEi_Gj`BgS+@5U~y(M-ztix#DTU5NP7E+7n_cPS\?21aiUEe700z>ix1v->l1<^INyme0S4leMjraNB<wlNGSe3OPT#SX!Q)F`<)Vc4N46M8WDUf0|a5G{Ltk5JAdJ@<+rl>)JT|m*<ny|sE$&=feM`!zBzox4RELfbk|Kz3{hT>kCwxz\?r5toffq<lg\?pMVZM|WGu3gb>j+F\?{crG81P*YAN+yTp\?2SLqy$m0J\?(WYbPXkw~IK>~!iIEX%>3sBqmspDLxUGyPDsy)@(uC*;&sV7aEcABbicli\?o!>%wU#^)gx!XY!8(%<oXed9Ucn}`wB%&{U7nbAi<CYdO_1PFFAj<DK=%F_aoU^!)wp>T`>fTLoT+LAr7FEd}!-T3Auw6uAIF}FU;d6ugTNE5EVWwec(g`3EtlwFQcDrKu3m9X<0Ym4(Bp}q(4nLY>s%&}3C;)pPYhjb\?4|N9zdO|>C9rW*cVFWB~HcdV>1DvZ$20HpGjCVr`R;aJLVp#{xwP`37Yic_|-V;Ca}#xZ1+YpEA64d{5`RE`ShiI2^R2*)DwK6aQj6@CrKWb7JDu3D8mv3S&3Jw$1{)Hm!L\?9k)+t_D#B#@)hJB>s}T{x6H(>Gn3djatySwWsDI`W(#|B{~^je^B6\?tg}~s{fq940Yb4)pF5UZ+sY&L)r3xMx9=Xiq@A8Fz>u`6v;3dzrH@+N;V\?+s(hb(D0tg|VeoKw%1X^{H=j4*rH-O8$`&I5`=iBUW$M%J~WWrUv_>Dc&uEw90r49OQEU3!^Fyoe=*2A}uH)S0kW+o;V\?|g\?<U<VjS-3yQ-!*i;}U<O^qI*b%\?7s*p}<%n4Zs*mcfV2!fA&yq<AKaU<a3dtfnC_Ew+g}(Zl&B)o2Y5IIzSda*0fVPEFId<l~H7-z!yc\?QOAGFXwC1;3QiK@Y5eoTE1%6JeVr%6-O(505kxUs)6Z}qy01S8u5fABO<=5|b@H5~Xx2A)2!tmSE2Y|QPdAfNO!0u^4mMT=Ok%i5HDK$2WI*HM2JmQV%2oi-%\?hT<&chU_\?wXK8Oe#4KJk)6MeZofy#yLN&sR\?4ctoILZdB#Ee3NEalHH;ucuYKh0Fo2i>DvCj7ntcw7-Y9{@{X>pJ{hB&WbP!TnvisqPO|TmYbz%XRkj;o+9=ih9WtG^ag6A~jqB36(&4<X<v-OovQgoMzivxIwg7pUV##(;+L(mK>t~nAP@aYB!`J%mf@74=yLBbJ9NFC=F@tkL{hen6hs8v;bQmS#Cw!rcuw3j3giI+C=dXoy%%;*g~%1Oh*&mk%Az1T)K@yjPn}7EX^E&s6n`DxQrcKOgs=Y<%@Q;4QgPRkUQwt+B^haj05=KIn)1xsV(\?UTV8&6nMzF(p^Z`r>BTyzEzsbznM1}#J<FqL2n}r6!{es}7^-B_k|2qb9CrURu*uqOwlsQRG*2s_{v}xZ!47(4$a=r`$gt>w{en!JgHm8pHMcxo$6)$*VA|UpW)qa8i=KapYKwP_kSXqu>j+1CH_72bq@dA>w77ek|BmQrLJRzL(TwBScI$Tokcg7THcX`pYQ1xuYPz$B2aic@HzuLvOKw3Kh0%D<P<|<oGjrqOv2BzunvL)2OP`NZ+f|@1>9~FNxndq8@4$3HmRAG)fD<^0N9Jm@T_%%rP8y(q@%Tzo=BWO}F8aN|&VX57)AV0>oO-D0s=TXQo\?e}3U7HE6&Dsf!$rFmaB15&Q3|52k4RVlvJT;!~%Cq}A*u@7G`9^xgogqt4a_#qLSM!qSvqMah)@liF;dF7T{O1Ms0OCo&;B|o)8b62mtc|K^VtW3`XhrZE@+u`5A|0<G)nL>A\?TN40WCtif7VoMhSY>}YsALVL@9}_(&DZ2v0{nBHq^}QaiQYMjoCPG9IKKLOFm-%s7q_iT0Jis!;I0QcyG`PyKD19_;$Xw5y{n27I(O$pm}1s$j~40H!>A>5V#wbl`axFGS\?Z6_5DKl7lc{&{NYAi~yAi+xJ1UL)g=f$%`3b<qaJD~$qYiid_po<gax@{HHlFAo_p(7{ax}UIT$8N$aA7i@eflS43$)G`W7Jr4bv&w(t+}\?CWqCXM59uN3p9&gzUJ%y2{kam4-`ym~j5s7mR`^23VY=-!UBaOj@hH{~$6N>Ppx=k{1bAl8HoV|IPi-EAyr(1cG6qM<7=kx30fV|&>!*0Yh<JK#ehWr}x2jeYWE|LI%E<<xo_O9pj{e$g)g(VcIsi@LjUl*IA$;n(a1z1u)DkVh*jOreQ(G!+QdIS+QnjDr\?S|Yxe\?7~NbJP_L>^}Uwi=i13%rQ}d2o`v\?ZLT@r8aI3`jS*ZU<pG-1Q;oW1@!vB|\?zKmH#huZoo>(phBb;f*i)cWs%!vOMK{{=l>YYpTUi{)`FM;}qty=dG!i5$y_ax4dOxQxAv6G81*n%=>W`|CICBuNl^M^NV%Cb&m#m3B}SU$pWS~\?\?g_mZG~1WWghDsTcPu~<(aP@VeSivlX|\?HF1)ZNaV2ot_Mdtd(0A-icDZe\?+wsoc`\?b\?1Z8zW#=Mlz;|+c>c8AFaQyt5Vp7#jRk9AAq_$A}6>buX&(sET0EeB5R3QlKdk^#)$#~NKf6U4\?zKH$zo)o>nFL558sF)cI7!*8@{UG0&5Vy0a&J9yXxhu4xzy$t_J{\?F6j!&!k1_2VDbX&I3N<ZpfHL)E1e4Se;IR;XO>*v{CvPuW~*3LTC*$2VfS{PkU9AxX\?u%t`i&vXJ^3He*}@sl;rRL}xCl*=L&Wd-bSrYq90iNIrV&3cC}6>Y7}EcGZus4F0sN7zg;AT%n0Nq!>`wxK>yt&d>7ms>Ko_&;CXcN)6crV5zzuqIPeOqHSRvfHktjJHc<gjC^Y)spGZb81q\?Wh5&^cS-}2fEac0(jba8q3@1C<=w8Gi^((KhlX2|m\?O9w8PQ)`X^f&}@~#-O2nzf\?>Y7G4Tq1Y)(izQwG^9YBJ@reTF!M_R9^Vu%$6gZm!e23FhlO$~KCc#0KZ3>I@X94FCMM(>GD%Z%udS*HxjrV734!hF>wk_<VJhIVDS^zu#lNDuI&yu2Q$l\?HJd71AB32LrXg$!3fGCVo{6(jTj8o<Kj(2!QTJSD*(0So6TlyQG(Ba)(#v5PM8%oqKlYBd54\?aVD=K7Q(R6^MG-)uI}3#|kxwu-Wb!+NKNt|sGid7lc6GAdcYu*{n|=b-rUzHdCtD$BCgzHF@$VTb6lcwR=cibtiQ5+tT%ba\?zAO>n&~ew21;x&{~Cr>ja{X539(qWlK\?qKh_COs{p&qQO`PA8-LyRGG@@{4`#k3rlmbCUQl_I<DZt2}(pusOu5$@nSdZ35&)|*L5%>54dMJT50Rbmubcd=1NjU0fnt96)_$}{^5o!-%wwYUpb%qXC5kN=n*q4f)egYMQ*x9_^&OZ1_vck2VFL)rbKUOYNF=La*k&*As9lc>d>I%FVB7olQSCWO$Bm6kXet9b$t`n\?(14I^93t\?>Fq+HI=>s9WFbe{icbjcAz4!1x7-&&C--o\?JG}l~`^eMs1`$jDga1G|Sx*zcO{5qDL=8iP5k>#Mh}}#=5|xpOW(<!1E_i=tM)n$d@}R=}dfDCpynGxXW1a_xkm-x--ng&q&3AZBGbA{9RD*wUgawbSu}Y~QhE%FenRyjh^um<ToK1*x90H9mOb$c#h8Ea#52YlyB;GM$uQyjIMG`W0>\?RM0#|AS^3unn8MCIP_S^m1{b|4;aOx=rC4&e_~qZ)OexRup;)8Ey3B)xJ(1qMe&<qvp<KYbMa->B_5e^!J{8X|a9_fHY4_#m(yf*2|-QCWK7mYTjPado1l6CY>J+1rJU\?buGmO%-n|binu{&5LY;rIHp~`d!ESC4f$S3oRvMwS7`{l5knWV0{FaxM5G_zm7j{hSUEYCnDEIHwO}Xxk>cm1P##D89aa3ngNB>01)#~|LxK5Yq\?^&A=hvS#T8GuVU7X$t!^ntBC5(CmsSq^9fIL^@^w2oOnCG%",
"21-1jOUc|}G&HxrW{>`@vO29m-4}liCBQnq9${L~5_%XT_Gkb6Q2>Hu6nzJDRY~Q^vKP%`unWSL<+9D64^HmFa+j($(5Tv(T\?is<L_Cs4GG=YyQw-D!@$B@5mBN9h2dp+;-fG>5s!%bFy`E+SvTmGO<T=0G6N$Cd=Al_nS1-\?f$N;i7svx()wNyr>u<5kRdPFQ\?Uo7D(peEU*n=Vno*@gdzH=*_a`k7^@*JtyWsht79O|7VLy#a}od0P6\?3cXx^oG%QY%Cn3H!IJ%\?hqC5Tn#mCx!W#CXl5lbHR@-KKn8!m-V0$4rpG1S|W~&GkWJ`H1#32TmI+=0PTlM~vSGcw~Zw~=D86|)\?!CaF8xa1dh1LX!8ot{*o2a29d^AcIddEsqrSU1bIZ5Gk98_g)|y+`A!>3h3K`rperlreHPb6eplU3KcIl6*lq98wj7rF#UyvdYoy16Zircu$\?C\?YwPf{ZM%Zh*s|i!a=@2*>~R3PFiPDD;;*|`r1ZUPKH`IV6Tn$pLb6rdCOO5*7*5j%l{}gh-C%Fl`|||C5NXpArmDE437Jo1_iH(H0)EOer+qjEEz9JFc`cT0eRGo)zN6XyY0`*9gs6_mre2wN~X@QH\?BbqgRiyuHO2M4(1)h(P55iuO6NVc(_rKMc(BnHmgKe4p5c2\?H7T^-f#bu<JH&saL*A3c`u}KjYA(O^VtW`}BlI<Ai|&i(dnGo9ntFt6hXPR3HWlzgTws&A+1X`79Wefq5f7jMtlX+svHyc-Z7)9kx1eQr9OTr<;Q7W`u~>gjm%s89YnXS&9v$Do25v2Qdf7tfIXBM_p9r#&{*HAN(23;$;v~hDMhDl*Vkr8scWm}#t4c9buI+;SU@u4}r8cLZ0%g`<e~WOnkFb;V6eGNES}+Y^kdQ|NS`iL7DV<$m=+l_U|14Hw(PB!#L6vZ6D`ZC`RlThHI%MHhp1*@uI#lO(0z>#{E*-Y1S}C`(WC\?hP48fxMYJniUzCCgF-ZVd}f$ldTfBr6To`d`aIB2|%-^=iHK3P@Ly-1T=;{#(SUDCOWbetD10QuJOJk0#4HRs^CXQ!P|=Sd*>=@Q)hr(T7BP9luml545dQm<z(Z{8|=\?^t70Exg+fo>IJoW!Vgw3v<-3R$ud(x*(-<a%_@Iw2d0bWwgz@7P`ZK+HdXPher9hgp=D7!+ZE=pXP<R*hK16wAeIJ5ttz6&8js=XC`XyHQ-__$0QPs5VaDm9FgW`{Dn@F*l9lo)p`XCLSu=75fF}1\?69Q)d$;Ax;p^d^a3O*eho}<1wsu)IbAs5)2_n4Iy2P_kC)$6)pWPL(N2`WcoQ{7e2+Anq\?(NjJ$t}J_QY9+Z_K2(<)l{E0B&!fAq}g~1J*BQ*rjU\?KKvXK;g(pQj_I!!VYmB4}KywKKSi_jUd*p%~8N^~T2Ux5%ka)6^p9Z}dS>=~fMn}KHEwb0w>J=Y%5_+lg!Bj&J+fXkX;1^^CG|qd>*0pQC$eqs#m|gjZ=Au!)NpqfCZ|5D{Mzh2b3sCQG9fG&NdNd&_xC4Xc$SLiLvy-\?yz4U%1T(n(M>D#>~kXTGV&xVOhgr5l+Fqh@u+4r=pcWLCE&@RUR;W-<`)8NEp$yx5F!{_9pX7zNSRnnQ8)>8%G6rs_+eS4TC0FbtKHFTM^_lA#%_=9oavs4l~xWzWf`kmbl#ur9}DSN*Po~Y$&xgRu~w|I7=KM;|Ui#GuV#~YeU+CP#%Cag$|rfTov>dlJNEZv}f2M13$)Nx\?PA~QxPAA91HcBLlXR4uy2@sRhplR{0$oA1Vkisq}!khkGA4j`ELBd*QkY!>Tu$f%@{!!zZWc$}#@052t4fia%#LvLZjCk!RatxLkDh#A);0H\?7>x=LtKCGe%H5<KiFAsoNA>!f7G-$(<(31EHVs<AbE0@KsR-~1ZZ5SKzS`&Bd&y(=-z6k0-{vE$AdZ$s}uQ`uk~0hrd_9@g5wKq$w$HXqNs2V}t|3ooNHq+~R3T#NK}b(SWOQ>!yXOr06%>aIXRGMqu`*ig6r&%-daDDbxYIKE$$v!DOr;CDJ|2F%7uxV#t<lOO~JPuY+`!b#$0J=!L>y@YH2$|H!xk~s`H{-+KLNEw>U3)<h^W%Ov$+S(!Sm90LUGETl#rVGd;Kaya!ezX^K_;8&`Y}9LMLf$8Bd#YX&-7ib3y56F`>bo>~sffUuJsX5tih897poz4MSi+H15ob~!+-h0{{xbbKL)VcCs#Z^RFT(-)63SZx%RI`\?g~wA>V!7u#JIb3|N3WV8\?quz>bK%=^g)8YG*$S0PJtFlh(vqi|CtjV>DZ)Zt2EKOm(YiI_QUxnCt|yi6l7|90&2;qrJna<b(X=pRl&Xu\?cM}DGX\?)5++=>#r9C_9Jo!N<qS}=G$e#Q6z>a`^mXG+Y75IM=uT|VA59cj>ZRQ$AKD8J#1DV`mn5-f`ib\?!S6An@T0&}pub-!w5&%@>+>{E-LYNVC\?s3\?{+3=L-!xCPA@wLQaT{`Z)wG\?}ci8|B;7MqRw=m=Z|6<J*YJ`uEWh)o-ACAYNG7*Bt#$zQ!rjvgAb{81SmO}9htTq{QDYx$lGb3fQ&7>EN^}H>YW;=+jZmwXr93ZhgM(de^!Jy=xeY=$dy7s1@;U4rqQF}P<Q%Eu#Gw|XK2GcxW;olrg~XRA<3Buuj#$4y3A(0vGu^*=Z#aJwY<O5%{;XPkiI(XeI{+d^PdpYn<%DAvnj<AbPp9~zvjyB&)dOiDD=#lAKyTh=l-y@e*7~SOP}loAcvL!FqU\?xC{#y-qQ9ZdS73(J;+jde7+c>m>xEanj1<3aW\?MbCvTb>>y}SDwDY>s>N+jU%uEl}\?x+d5S2QgRM{zugV\?@&$k8cIr6T5x@X<EsV}QlJ!^rdp^7U4nI)EEfCEMk*;{cHALxcpfB!0GDSR!Lnc4\?e1T&#V`XF4}SyB6$-JDh2bc)MK-CXfw\?f6d7M$d\?JmiyR9aa(-+6w{f!5-\?OrZ~VGTSHHh<6b-roAX4%xArOYSUj99pz~x3i53KXC>6vQLC2r5@pIom;I+o\?wNEk3ZV#ea%G4qYE#>t(+*xUtEI@)8+T4-QUi`Yj0Z503bq<p`~yBkO9k~j;LN^Rm)z}H)ug{+(JRGPL-P+kuDM2ENK0C+r%gssAX#IXS&P=fb-I8I0z(HlsO+CqGS5JB8Os1;kE\?fD;0gp3By^Oqi=eiD<hC#Ys%@+F$QvFK-Z|VKux@pKhbEC!D%S-d@D*~FD>4A#RqQ;>Vn&5=M*1wmRDJIffNcf0y1crQDT$*JAAohvv+2-6M1`%P$f}7X3vwo!73kK;RQu01hXeRaP!V6F$f7#xN=Z@I#R!w-&wK1g(eyHTm06JO5Dj&#-!_@syA`1J!eTb(OaK!mNDAwLylD9uau5r|K-o`y^ukdMda4Cjs2&AnJ`dJhDrMeHhND**G-QQ-chTitm3-Ku3Z\?!ovJ)2$6^wmB5E-)wc9sLBnup@C-`ziaHeElLQRLn=bB<M~GuQ0CU(4+5aiTgF=VNZfT#RG5XJ!Ym#3A&HmMzF^T~Jkwn(XS&UOv6cG{!l|8jPmw@H8~+*%qxrMjBP_0|bpN)+kf>pxO1Es6F(5sd|<SuFRfIbNZM({r}lD5=a05]",
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
