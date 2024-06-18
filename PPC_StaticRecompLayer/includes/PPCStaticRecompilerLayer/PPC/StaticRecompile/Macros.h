#pragma once
#include "PPC_ARITHMETIC.h"
#include "PPC_LOGICAL.h"
#include "PPC_SHIFT_ROTATE.h"
#include "PPC_COMPARASON.h"
#include "PPC_BRANCH.h"
#include "PPC_LOAD_STORE.h"
#include "PPC_FLOATING.h"
#include "PPC_CONDITION.h"
#include "PPC_SPECIAL.h"
#include "PPC_SYNC.h"
#include "PPC_SYSTEM_CALLS.h"
#include "PPC_MISC.h"


/*
Arithmetic Instructions
add
addi
addic
addic.
addis
addme
addme.
addze
addze.
subf
subfic
subfme
subfme.
subfze
subfze.
neg
neg.

Logical Instructions
and
andi.
andc
andis.
or
ori
orc
oris
xor
xori
xoris
nand
nor
eqv

Shift and Rotate Instructions
slw
srw
sraw
srawi
rlwimi
rlwinm
rlwnm

Comparison Instructions
cmp
cmpi
cmpl
cmpli
cmpw
cmpwi
cmplw
cmplwi

Branch Instructions
b
ba
bl
bla
bc
bca
bcl
bcla
bcctr
bcctrl
bclr
bclrl
blr
blrl

Load and Store Instructions
lbz
lbzu
lbzx
lbzux
lhz
lhzu
lhzx
lhzux
lha
lhau
lhax
lhaux
lwz
lwzu
lwzx
lwzux
stb
stbu
stbx
stbux
sth
sthu
sthx
sthux
stw
stwu
stwx
stwux
lwa
lwax
lwaux

Floating - Point Instructions
fadd
fadds
fsub
fsubs
fmul
fmuls
fdiv
fdivs
fsqrt
fsqrts
fsel
fmadd
fmadds
fmsub
fmsubs
fnmadd
fnmadds
fnmsub
fnmsubs
fres
frsqrte
fctiw
fctiwz
fctid
fctidz
fcmpu
fcmpo
fmr
fabs
fneg
fmsr
mffs
mffss
mtfsb0
mtfsb1
mtfsf
mtfsfi
frsp

Condition Register Instructions
crand
crandc
creqv
crnand
crnor
cror
crorc
crxor
mcrf
mcrfs
mtcrf
mtocrf

Special - Purpose Register Instructions
mfcr
mfspr
mtspr
mfsr
mtsr
mfsrin
mtsrin
mftb

Synchronization Instructions
sync
lwsync
isync
eieio

System Call Instructions
sc

Miscellaneous Instructions
nop
tw
twi
td
tdi
rfci
rfi
rfid
dcba
dcbf
dcbi
dcbst
dcbt
dcbtst
dcbz
icbi
icbt
icbtls
dcbtls
*/