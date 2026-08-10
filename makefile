# CC macro = GNU C compiler.
CC=gcc
# Strict ANSI C23 standard with all warnings on.
CFLAGS= -std=c23 -Wpedantic -Wall -O2
# Linking with mathematical library libm.a
LDFLAGS= -lm
# User-defined location of binaries:
BINDIR= ../bin/

sum1: sum1.o
	$(CC) $(CFLAGS) -o sum1.bin sum1.o $(LDFLAGS)

sum1-install: sum1
	install sum1.bin $(BINDIR)

sum2: sum2.o
	$(CC) $(CFLAGS) -o sum2.bin sum2.o $(LDFLAGS)

sum2-install: sum2
	install sum2.bin $(BINDIR)

lgmain: sf_log_gamma.o main_sf_log_gamma.o
	$(CC) $(CFLAGS) -o lgmain.bin sf_log_gamma.o main_sf_log_gamma.o $(LDFLAGS)

lgmain-install: lgmain
	install lgmain.bin $(BINDIR)

pmain: sf_log_gamma.o sf_poisson.o poisson_main.o
	$(CC) $(CFLAGS) -o pmain.bin sf_log_gamma.o sf_poisson.o poisson_main.o $(LDFLAGS)

pmain-install: pmain
	install pmain.bin $(BINDIR)

bbmain: sf_log_gamma.o sf_bico.o sf_beta.o main_sf_bibe.o
	$(CC) $(CFLAGS) -o bbmain.bin sf_log_gamma.o sf_bico.o sf_beta.o main_sf_bibe.o $(LDFLAGS)

bbmain-install: bbmain
	install bbmain.bin $(BINDIR)

h1main: sf_hermite1.o main_sf_hermite1.o
	$(CC) $(CFLAGS) -o h1main.bin sf_hermite1.o main_sf_hermite1.o $(LDFLAGS)

h1main-install: h1main
	install h1main.bin $(BINDIR)

h2main: sf_hermite2.o main_sf_hermite2.o
	$(CC) $(CFLAGS) -o h2main.bin sf_hermite2.o main_sf_hermite2.o $(LDFLAGS)

h2main-install: h2main
	install h2main.bin $(BINDIR)

hmain: sf_hermite.o sf_hermite2.o sf_hermite1.o main_sf_hermite.o
	$(CC) $(CFLAGS) -o hmain.bin sf_hermite.o sf_hermite2.o sf_hermite1.o main_sf_hermite.o $(LDFLAGS)

hmain-install: hmain
	install hmain.bin $(BINDIR)

hamain: sf_hermite_array.o main_sf_hermite_array.o
	$(CC) $(CFLAGS) -o hamain.bin sf_hermite_array.o main_sf_hermite_array.o $(LDFLAGS)

hamain-install: hamain
	install hamain.bin $(BINDIR)

lmain: main_sf_laguerre.o sf_laguerre.o sf_log_gamma.o
	$(CC) $(CFLAGS) -o lmain.bin main_sf_laguerre.o sf_laguerre.o sf_log_gamma.o $(LDFLAGS)

lmain-install: lmain
	install lmain.bin $(BINDIR)

lfmain: main_sf_laguerre_fast.o sf_laguerre_fast.o sf_bico.o sf_log_gamma.o
	$(CC) $(CFLAGS) -o lfmain.bin main_sf_laguerre_fast.o sf_laguerre_fast.o sf_bico.o sf_log_gamma.o $(LDFLAGS)

lfmain-install: lfmain
	install lfmain.bin $(BINDIR)

gimain: main_sf_gamma_incomplete.o sf_gamma_incomplete.o sf_log_gamma.o
	$(CC) $(CFLAGS) -o gimain.bin main_sf_gamma_incomplete.o sf_gamma_incomplete.o sf_log_gamma.o $(LDFLAGS)

gimain-install: gimain
	install gimain.bin $(BINDIR)

dgmain: sf_digamma.o main_sf_digamma.o
	$(CC) $(CFLAGS) -o dgmain.bin sf_digamma.o main_sf_digamma.o $(LDFLAGS)

dgmain-install: dgmain
	install dgmain.bin $(BINDIR)

eximain: sf_exp_integral.o sf_digamma.o main_sf_exp_integral.o
	$(CC) $(CFLAGS) -o eximain.bin sf_exp_integral.o sf_digamma.o main_sf_exp_integral.o $(LDFLAGS)

eximain-install: eximain
	install eximain.bin $(BINDIR)

ipmain: ip_neville.o main_ip_neville.o
	$(CC) $(CFLAGS) -o ipmain.bin ip_neville.o main_ip_neville.o $(LDFLAGS)

ipmain-install: ipmain
	install ipmain.bin $(BINDIR)

iplmain: ip_neville.o ip_searchidx.o ip_polylocal.o main_ip_polylocal.o
	$(CC) $(CFLAGS) -o iplmain.bin ip_neville.o ip_searchidx.o ip_polylocal.o main_ip_polylocal.o $(LDFLAGS)

iplmain-install: iplmain
	install iplmain.bin $(BINDIR)

irmain: ip_burlischstoer.o ip_neville.o main_ip_burlischstoer.o
	$(CC) $(CFLAGS) -o irmain.bin ip_burlischstoer.o ip_neville.o main_ip_burlischstoer.o $(LDFLAGS)

irmain-install: irmain
	install irmain.bin $(BINDIR)

irlmain: ip_searchidx.o ip_polylocal.o ip_neville.o ip_ratlocal.o ip_burlischstoer.o main_ip_ratlocal.o
	$(CC) $(CFLAGS) -o irlmain.bin ip_searchidx.o ip_polylocal.o ip_neville.o ip_ratlocal.o ip_burlischstoer.o main_ip_ratlocal.o $(LDFLAGS)

irlmain-install: irlmain
	install irlmain.bin $(BINDIR)

intmain: ig_simpsonext.o main_ig_simpsonext.o
	$(CC) $(CFLAGS) -o intmain.bin ig_simpsonext.o main_ig_simpsonext.o $(LDFLAGS)

intmain-install: intmain
	install intmain.bin $(BINDIR)

intrmain: ig_simpsonext.o ig_romberg.o ig_romberg_simpsonext.o main_ig_romberg.o
	$(CC) $(CFLAGS) -o intrmain.bin ig_simpsonext.o ig_romberg.o ig_romberg_simpsonext.o main_ig_romberg.o $(LDFLAGS)

intrmain-install: intrmain
	install intrmain.bin $(BINDIR)

igimain: ig_romberg.o sf_log_gamma.o main_ig_gammainc.o
	$(CC) $(CFLAGS) -o igimain.bin ig_romberg.o sf_log_gamma.o main_ig_gammainc.o $(LDFLAGS)

igimain-install: igimain
	install igimain.bin $(BINDIR)

igipmain: ig_romberg.o ig_improper.o main_ig_improper.o
	$(CC) $(CFLAGS) -o igipmain.bin ig_romberg.o ig_improper.o main_ig_improper.o $(LDFLAGS)

igipmain-install: igipmain
	install igipmain.bin $(BINDIR)


ftmain: ft_bitrev.o ft_fft.o main_ft_fft.o
	$(CC) $(CFLAGS) -o ftmain.bin ft_bitrev.o ft_fft.o main_ft_fft.o $(LDFLAGS)

ftmain-install: ftmain
	install ftmain.bin $(BINDIR)

chmain: ch_coef.o ch_approx.o main_ch_approx.o
	$(CC) $(CFLAGS) -o chmain.bin ch_coef.o ch_approx.o main_ch_approx.o $(LDFLAGS)

chmain-install: chmain
	install chmain.bin $(BINDIR)

cho2main: de_rkembedded.o de_solve.o main_de_cho2.o
	$(CC) $(CFLAGS) -o cho2main.bin de_rkembedded.o de_solve.o main_de_cho2.o $(LDFLAGS)

cho2main-install: cho2main
	install cho2main.bin $(BINDIR)

molmain: de_rkembedded.o de_solve.o main_de_mol.o
	$(CC) $(CFLAGS) -o molmain.bin de_rkembedded.o de_solve.o main_de_mol.o $(LDFLAGS)

molmain-install: molmain
	install molmain.bin $(BINDIR)

poolmain: de_rkembedded.o de_solve.o main_de_pool.o
	$(CC) $(CFLAGS) -o poolmain.bin de_rkembedded.o de_solve.o main_de_pool.o $(LDFLAGS)

poolmain-install: poolmain
	install poolmain.bin $(BINDIR)

poolwatermain: main_de_poolwater.o
	$(CC) $(CFLAGS) -o poolwatermain.bin main_de_poolwater.o $(LDFLAGS)

poolwatermain-install: poolwatermain
	install poolwatermain.bin $(BINDIR)

husimimain: de_husimi.o sf_poisson.o sf_log_gamma.o main_de_husimi.o
	$(CC) $(CFLAGS) -o husimimain.bin de_husimi.o sf_poisson.o sf_log_gamma.o main_de_husimi.o $(LDFLAGS)

husimimain-install: husimimain
	install husimimain.bin $(BINDIR)

oscimain: de_solve.o de_rkembedded.o de_husimi.o sf_poisson.o sf_log_gamma.o main_de_osci.o
	$(CC) $(CFLAGS) -o oscimain.bin de_solve.o de_rkembedded.o de_husimi.o sf_poisson.o sf_log_gamma.o main_de_osci.o $(LDFLAGS)

oscimain-install: oscimain
	install oscimain.bin $(BINDIR)

oscimain-anim: 
	-gnuplot de_osci_anim.gnu

wavefuncmain: de_solve.o de_rkembedded.o sf_poisson.o sf_log_gamma.o de_wavefunc.o main_de_wavefunc.o
	$(CC) $(CFLAGS) -o wavefuncmain.bin de_solve.o de_rkembedded.o sf_poisson.o sf_log_gamma.o de_wavefunc.o main_de_wavefunc.o $(LDFLAGS)

wavefuncmain-install: wavefuncmain
	install wavefuncmain.bin $(BINDIR)

wavefuncmain-anim: 
	-gnuplot de_wavefunc_anim.gnu

corrmain: main_rn_corr.o
	$(CC) $(CFLAGS) -o corrmain.bin main_rn_corr.o $(LDFLAGS)

corrmain-install: corrmain
	install corrmain.bin $(BINDIR)

pmmain: main_rn_pm.o rn_parkmiller.o ip_searchidx.o
	$(CC) $(CFLAGS) -o pmmain.bin main_rn_pm.o rn_parkmiller.o ip_searchidx.o $(LDFLAGS)

pmmain-install: pmmain
	install pmmain.bin $(BINDIR)

shufflemain: rn_parkmiller.o rn_shuffle.o main_rn_shuffle.o ip_searchidx.o
	$(CC) $(CFLAGS) -o shufflemain.bin rn_parkmiller.o rn_shuffle.o main_rn_shuffle.o ip_searchidx.o $(LDFLAGS)

shufflemain-install: shufflemain
	install shufflemain.bin $(BINDIR)

qtmain: de_rkembedded.o de_solve.o qt_solve.o main_qt_oscidamped.o sf_log_gamma.o rn_shuffle.o
	$(CC) $(CFLAGS) -o qtmain.bin de_rkembedded.o de_solve.o qt_solve.o main_qt_oscidamped.o sf_log_gamma.o rn_shuffle.o $(LDFLAGS)

qtmain-install: qtmain
	install qtmain.bin $(BINDIR)

doc:
	doxygen

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.bin
