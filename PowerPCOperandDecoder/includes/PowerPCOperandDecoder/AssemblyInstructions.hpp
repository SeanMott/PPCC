#pragma once

//the big fuck list of assembly instruciotns

#include <BTDSTD/Types.hpp>
#include <string>

namespace PPC::Decoder::ASM
{
	//the big fuck enum list of instructions
	enum EInstruction
	{
		eInstruction_nop = 0,

		// move register (with move to/from special registers)
		InstructionGroup_MoveRegister_Start,
		eInstruction_mr = InstructionGroup_MoveRegister_Start,
		eInstruction_mfspr,
		eInstruction_mfsprg,
		eInstruction_mfsrr0,
		eInstruction_mfsrr1,
		eInstruction_mtspr,
		eInstruction_mfmsr,
		eInstruction_mtsrr0,
		eInstruction_mtsrr1,
		eInstruction_mtsprg,
		eInstruction_mfmsrg,
		eInstruction_mtmsr,
		eInstruction_mtdar,
		eInstruction_mtdsisr,
		eInstruction_mtmsrd,
		eInstruction_mtmsree,
		eInstruction_mtxer,
		eInstruction_mfcr,
		eInstruction_mtcrf,
		eInstruction_mfocrf,
		eInstruction_mtocrf,
		eInstruction_mcrf,
		eInstruction_mftb,
		eInstruction_mflr,
		eInstruction_mtctr,
		eInstruction_mfdar,
		InstructionGroup_MoveRegister_End = eInstruction_mfdar,

		// load memory
		InstructionGroup_LoadMemory_Start,
		eInstruction_lbz = InstructionGroup_LoadMemory_Start,
		eInstruction_lhz,
		eInstruction_lwz,
		eInstruction_lbzu,
		eInstruction_lhzu,
		eInstruction_lwzu,
		eInstruction_lba,
		eInstruction_lha,
		eInstruction_lwa,
		eInstruction_lbau,
		eInstruction_lhau,
		eInstruction_lwau,
		eInstruction_ld,
		eInstruction_ldu,
		eInstruction_lmw,
		InstructionGroup_LoadMemory_End = eInstruction_lmw,

		// load memory indexed
		InstructionGroup_LoadMemoryIndexed_Start,
		eInstruction_lbzx = InstructionGroup_LoadMemoryIndexed_Start,
		eInstruction_lhzx,
		eInstruction_lwzx,
		eInstruction_lbzux,
		eInstruction_lhzux,
		eInstruction_lwzux,
		eInstruction_lbax,
		eInstruction_lhax,
		eInstruction_lwax,
		eInstruction_lbaux,
		eInstruction_lhaux,
		eInstruction_lwaux,
		eInstruction_ldx,
		eInstruction_ldux,
		InstructionGroup_LoadMemoryIndexed_End = eInstruction_ldux,

		// store memory
		InstructionGroup_StoreMemory_Start,
		eInstruction_stb = InstructionGroup_StoreMemory_Start,
		eInstruction_sth,
		eInstruction_stw,
		eInstruction_std,
		eInstruction_slwi,
		eInstruction_stbu,
		eInstruction_sthu,
		eInstruction_stwu,
		eInstruction_stdu,
		InstructionGroup_StoreMemory_End = eInstruction_stdu,

		// store memory indexed
		InstructionGroup_StoreMemoryIndexed_Start,
		eInstruction_stbx = InstructionGroup_StoreMemoryIndexed_Start,
		eInstruction_sthx,
		eInstruction_stwx,
		eInstruction_stdx,
		eInstruction_stbux,
		eInstruction_sthux,
		eInstruction_stwux,
		eInstruction_stdux,
		InstructionGroup_StoreMemoryIndexed_End = eInstruction_stdux,

		//quantized store
		eInstruction_psq_stx,
		eInstruction_psq_lx,
		eInstruction_psq_st,
		eInstruction_psq_l,

		//idk
		eInstruction_twui,

		// branch instructions
		InstructionGroup_Branch_Start,
		eInstruction_b = InstructionGroup_Branch_Start,
		eInstruction_bdnz,
		eInstruction_ba,
		eInstruction_bl,
		eInstruction_blt,
		eInstruction_bla,
		eInstruction_bc,
		eInstruction_bcl,
		eInstruction_bca,
		eInstruction_bcla,
		eInstruction_bclr,
		eInstruction_bclrl,
		eInstruction_bcctr,
		eInstruction_bcctrl,
		eInstruction_beq,
		eInstruction_beq_plus,
		eInstruction_beqlr,
		eInstruction_blr,
		eInstruction_bltlr,
		eInstruction_bne,
		eInstruction_bnelr,
		eInstruction_bge,
		eInstruction_bgelr,
		eInstruction_bgt,
		eInstruction_bctr,
		eInstruction_bctrl,
		InstructionGroup_Branch_End = eInstruction_bctrl,

		// lwarx/stwcx
		eInstruction_lwarx,
		eInstruction_ldarx,
		eInstruction_stwcxRC, //.
		eInstruction_stdcxRC, //.

		// memory bariers
		eInstruction_isync,
		eInstruction_sync,
		eInstruction_lwsync,
		eInstruction_ptesync,
		eInstruction_eieio,

		// custom
		//eInstruction_cmp,
		eInstruction_fcmpu,
		eInstruction_fcmpo,
		eInstruction_twi,
		eInstruction_tdi,
		eInstruction_tw,
		eInstruction_td,

		// generic instructions
		eInstruction_sc,

		// condition register operators
		eInstruction_crand,
		eInstruction_cror,
		eInstruction_crxor,
		eInstruction_crnand,
		eInstruction_crnor,
		eInstruction_creqv,
		eInstruction_crandc,
		eInstruction_crorc,
		eInstruction_crclr,

		// load immediate
		eInstruction_li,
		eInstruction_lis,

		// math with immediate value
		eInstruction_addic,
		eInstruction_addicRC,
		eInstruction_addi,
		eInstruction_addis,
		eInstruction_subfic,
		eInstruction_mulli,

		// add XO-form
		eInstruction_add,
		eInstruction_addRC,
		eInstruction_addo,
		eInstruction_addoRC,

		// subtract grom XO-form
		eInstruction_subi,
		eInstruction_subic,
		eInstruction_subf,
		eInstruction_subfRC,
		eInstruction_subfo,
		eInstruction_subfoRC,

		// add carrying XO-form
		eInstruction_addc,
		eInstruction_addcRC,
		eInstruction_addco,
		eInstruction_addcoRC,

		// subtract From carrying XO-form
		eInstruction_subfc,
		eInstruction_subfcRC,
		eInstruction_subfco,
		eInstruction_subfcoRC,

		// add extended XO-form
		eInstruction_adde,
		eInstruction_addeRC,
		eInstruction_addeo,
		eInstruction_addeoRC,

		// subtract from extended XO-form
		eInstruction_subfe,
		eInstruction_subfeRC,
		eInstruction_subfeo,
		eInstruction_subfeoRC,
		eInstruction_subis,

		// add to minus one extended XO-form
		eInstruction_addme,
		eInstruction_addmeRC,
		eInstruction_addmeo,
		eInstruction_addmeoRC,

		// subtract from minus one extended XO-form
		eInstruction_subfme,
		eInstruction_subfmeRC,
		eInstruction_subfmeo,
		eInstruction_subfmeoRC,

		// add to zero extended XO-form
		eInstruction_addze,
		eInstruction_addzeRC,
		eInstruction_addzeo,
		eInstruction_addzeoRC,

		// subtract from zero extended XO-form
		eInstruction_subfze,
		eInstruction_subfzeRC,
		eInstruction_subfzeo,
		eInstruction_subfzeoRC,

		// negate
		eInstruction_neg,
		eInstruction_negRC,
		eInstruction_nego,
		eInstruction_negoRC,

		// multiply low doubleword XO-form
		eInstruction_mulld,
		eInstruction_mulldRC,
		eInstruction_mulldo,
		eInstruction_mulldoRC,

		// multiply low word XO-form
		eInstruction_mullw,
		eInstruction_mullwRC,
		eInstruction_mullwo,
		eInstruction_mullwoRC,

		// multiply high doubleword XO-form
		eInstruction_mullhd,
		eInstruction_mullhdRC,

		// multiply High Word XO-form
		eInstruction_mullhw,
		eInstruction_mullhwRC,

		// multiply high doubleword unsigned XO-form
		eInstruction_mulhdu,
		eInstruction_mulhduRC,

		// multiply High Word Unsigned XO-form
		eInstruction_mulhwu,
		eInstruction_mulhwuRC,

		// divide doubleword XO-form
		eInstruction_divd,
		eInstruction_divdRC,
		eInstruction_divdo,
		eInstruction_divdoRC,

		// divide word XO-form
		eInstruction_divw,
		eInstruction_divwRC,
		eInstruction_divwo,
		eInstruction_divwoRC,

		// divide doubleword unsigned XO-form
		eInstruction_divdu,
		eInstruction_divduRC,
		eInstruction_divduo,
		eInstruction_divduoRC,

		// divide word unsigned XO-form
		eInstruction_divwu,
		eInstruction_divwuRC,
		eInstruction_divwuo,
		eInstruction_divwuoRC,

		// compare
		InstructionGroup_Compare_Start,
		eInstruction_cmpwi = InstructionGroup_Compare_Start,
		eInstruction_cmpdi,
		eInstruction_cmplwi,
		eInstruction_cmpldi,
		eInstruction_cmpw,
		eInstruction_cmpd,
		eInstruction_cmplw,
		eInstruction_cmpld,
		InstructionGroup_Compare_End = eInstruction_cmpld,

		// logical instructions with immediate values
		eInstruction_andi,
		eInstruction_andis,
		eInstruction_andiRC,
		eInstruction_andisRC,
		eInstruction_ori,
		eInstruction_oris,
		eInstruction_xori,
		eInstruction_xoris,

		// logical instructions
		InstructionGroup_Bitshift_Start,
		eInstruction_and = InstructionGroup_Bitshift_Start,
		eInstruction_andRC,
		eInstruction_or,
		eInstruction_orRC,
		eInstruction_xor,
		eInstruction_xorRC,
		eInstruction_nand,
		eInstruction_nandRC,
		eInstruction_nor,
		eInstruction_norRC,
		eInstruction_eqv,
		eInstruction_eqvRC,
		eInstruction_andc,
		eInstruction_andcRC,
		eInstruction_orc,
		eInstruction_orcRC,
		InstructionGroup_Bitshift_End = eInstruction_orcRC,

		// byte extend
		eInstruction_extsb,
		eInstruction_extsbRC,
		eInstruction_extsh,
		eInstruction_extshRC,
		eInstruction_extsw,
		eInstruction_extswRC,
		eInstruction_extrwi,

		// population count
		eInstruction_popcntb,
		eInstruction_cntlzw,
		eInstruction_cntlzwRC,
		eInstruction_cntlzd,
		eInstruction_cntlzdRC,

		// Shift instructions with immediate params -->
		// REG,REG,IMM,IMM
		eInstruction_rldicl,
		eInstruction_rldiclRC,
		eInstruction_rldicr,
		eInstruction_rldicrRC,
		eInstruction_rldic,
		eInstruction_rldicRC,
		eInstruction_rldimi,
		eInstruction_rldimiRC,
		eInstruction_clrlwi,
		eInstruction_clrrwi,
		eInstruction_clrlslwi,

		// REG,REG,IMM,IMM,IMM
		eInstruction_rlwinm,
		eInstruction_rlwinmRC,
		eInstruction_rlwimi,
		eInstruction_rlwimiRC,

		// REG,REG,REG,IMM
		eInstruction_rldcl,
		eInstruction_rldclRC,
		eInstruction_rldcr,
		eInstruction_rldcrRC,

		// REG,REG,REG,IMM,IMM
		eInstruction_rlwnm,
		eInstruction_rlwnmRC,

		// Extended shifts
		eInstruction_sld,
		eInstruction_sldRC,
		eInstruction_slw,
		eInstruction_slwRC,
		eInstruction_srd,
		eInstruction_srdRC,
		eInstruction_srw,
		eInstruction_srwi,
		eInstruction_srwRC,
		eInstruction_srad,
		eInstruction_sradRC,
		eInstruction_sraw,
		eInstruction_srawRC,

		// Extended shifts with immediate... geez..
		eInstruction_srawi,
		eInstruction_srawiRC,
		eInstruction_sradi,
		eInstruction_sradiRC,

		// Cache operation instructions
		eInstruction_dcbi,
		eInstruction_dcbf,
		eInstruction_dcbst,
		eInstruction_dcbt,
		eInstruction_dcbtst,
		eInstruction_dcbz,

		//  Floating point load instructions
		eInstruction_lfs,
		eInstruction_lfsu,
		eInstruction_lfsx,
		eInstruction_lfsux,
		eInstruction_lfd,
		eInstruction_lfdu,
		eInstruction_lfdx,
		eInstruction_lfdux,

		//  Floating point store instructions
		eInstruction_stfs,
		eInstruction_stfsu,
		eInstruction_stfsx,
		eInstruction_stfsux,
		eInstruction_stfd,
		eInstruction_stfdu,
		eInstruction_stfdx,
		eInstruction_stfdux,

		// Store float point as integer word indexed
		eInstruction_stfiwx,

		//store move register
		eInstruction_stmw,

		// Floating point move and single op instructions
		eInstruction_fmr,
		eInstruction_fmrRC,
		eInstruction_fneg,
		eInstruction_fnegRC,
		eInstruction_fabs,
		eInstruction_fabsRC,
		eInstruction_fnabs,
		eInstruction_fnabsRC,

		// Floating point arithmetic instructions
		eInstruction_fadd,
		eInstruction_faddRC,
		eInstruction_fadds,
		eInstruction_faddsRC,
		eInstruction_fsub,
		eInstruction_fsubRC,
		eInstruction_fsubs,
		eInstruction_fsubsRC,
		eInstruction_fmul,
		eInstruction_fmulRC,
		eInstruction_fmuls,
		eInstruction_fmulsRC,
		eInstruction_fdiv,
		eInstruction_fdivRC,
		eInstruction_fdivs,
		eInstruction_fdivsRC,
		eInstruction_fsqrt,
		eInstruction_fsqrtRC,
		eInstruction_frsqrtx,
		eInstruction_frsqrtxRC,
		eInstruction_frsqrte,
		eInstruction_fre,
		eInstruction_freRC,

		// Floating point mad instructions
		eInstruction_fmadd,
		eInstruction_fmaddRC,
		eInstruction_fmadds,
		eInstruction_fmaddsRC,
		eInstruction_fmsub,
		eInstruction_fmsubRC,
		eInstruction_fmsubs,
		eInstruction_fmsubsRC,
		eInstruction_fnmadd,
		eInstruction_fnmaddRC,
		eInstruction_fnmadds,
		eInstruction_fnmaddsRC,
		eInstruction_fnmsub,
		eInstruction_fnmsubRC,
		eInstruction_fnmsubs,
		eInstruction_fnmsubsRC,

		// Floating point rounding and conversion
		eInstruction_frsp,
		eInstruction_frspRC,
		eInstruction_fctid,
		eInstruction_fctidRC,
		eInstruction_fctidz,
		eInstruction_fctidzRC,
		eInstruction_fctiw,
		eInstruction_fctiwRC,
		eInstruction_fctiwz,
		eInstruction_fctiwzRC,
		eInstruction_fcfid,
		eInstruction_fcfidRC,

		// Floating point select
		eInstruction_fsel,
		eInstruction_fselRC,

		// Floating point control registers
		eInstruction_mffs,
		eInstruction_mffsRC,
		eInstruction_mcrfs,
		eInstruction_mtfsfi,
		eInstruction_mtfsfiRC,
		eInstruction_mtfsf,
		eInstruction_mtfsfRC,
		eInstruction_mtfsb0,
		eInstruction_mtfsb0RC,
		eInstruction_mtfsb1,
		eInstruction_mtfsb1RC,
		eInstruction_mtlr,

		// VMX instructions
		eInstruction_lvebx,
		eInstruction_lvehx,
		eInstruction_lvewx,		//+
		eInstruction_lvlx,		//+
		eInstruction_lvlxl,		//+
		eInstruction_lvrx,		//+
		eInstruction_lvrxl,		//+
		eInstruction_lvsl,
		eInstruction_lvsr,
		eInstruction_lvx,			//+
		eInstruction_lvxl,		//+
		eInstruction_mfvscr,
		eInstruction_mtvscr,
		eInstruction_stvebx,
		eInstruction_stvehx,
		eInstruction_stvewx,		//+
		eInstruction_stvlx,		//+
		eInstruction_stvlxl,		//+
		eInstruction_stvrx,		//+
		eInstruction_stvrxl,		//+
		eInstruction_stvx,		//+
		eInstruction_stvxl,		//+
		eInstruction_lhbrx,
		eInstruction_lwbrx,
		eInstruction_sthbrx,
		eInstruction_stwbrx,
		eInstruction_lswi,
		eInstruction_lswx,
		eInstruction_stswi,
		eInstruction_stswx,
		eInstruction_vaddcuw,
		eInstruction_vaddfp,		//+
		eInstruction_vaddsbs,
		eInstruction_vaddshs,
		eInstruction_vaddsws,
		eInstruction_vaddubm,
		eInstruction_vaddubs,
		eInstruction_vadduhm,
		eInstruction_vadduhs,
		eInstruction_vadduwm,
		eInstruction_vadduws,
		eInstruction_vand,		//+
		eInstruction_vandc,		//+
		eInstruction_vavgsb,
		eInstruction_vavgsh,
		eInstruction_vavgsw,
		eInstruction_vavgub,
		eInstruction_vavguh,
		eInstruction_vavguw,
		eInstruction_vcfpsxws,	//+
		eInstruction_vcfpuxws,	//+
		eInstruction_vcsxwfp, //+
		eInstruction_vcuxwfp, //+
		eInstruction_vctsxs,	//+
		eInstruction_vctuxs,		//+
		eInstruction_vcfsx,	//+
		eInstruction_vcfux,	//+
		eInstruction_vcmpbfp,
		eInstruction_vcmpbfpRC,
		eInstruction_vcmpeqfp,
		eInstruction_vcmpeqfpRC,
		eInstruction_vcmpequb,
		eInstruction_vcmpequbRC,
		eInstruction_vcmpequh,
		eInstruction_vcmpequhRC,
		eInstruction_vcmpequw,
		eInstruction_vcmpequwRC,
		eInstruction_vcmpgefp,
		eInstruction_vcmpgefpRC,
		eInstruction_vcmpgtfp,
		eInstruction_vcmpgtfpRC,
		eInstruction_vcmpgtsb,
		eInstruction_vcmpgtsbRC,
		eInstruction_vcmpgtsh,
		eInstruction_vcmpgtshRC,
		eInstruction_vcmpgtsw,
		eInstruction_vcmpgtswRC,
		eInstruction_vcmpgtub,
		eInstruction_vcmpgtubRC,
		eInstruction_vcmpgtuh,
		eInstruction_vcmpgtuhRC,
		eInstruction_vcmpgtuw,
		eInstruction_vcmpgtuwRC,
		eInstruction_vexptefp,	//+
		eInstruction_vlogefp,		//+
		eInstruction_vmaddcfp128,
		eInstruction_vmaddfp,		//+
		eInstruction_vmaxfp,		//+
		eInstruction_vmaxsb,
		eInstruction_vmaxsh,
		eInstruction_vmaxsw,
		eInstruction_vmaxub,
		eInstruction_vmaxuh,
		eInstruction_vmaxuw,
		eInstruction_vminfp,		//+
		eInstruction_vminsb,
		eInstruction_vminsh,
		eInstruction_vminsw,
		eInstruction_vminub,
		eInstruction_vminuh,
		eInstruction_vminuw,
		eInstruction_vmrghb,
		eInstruction_vmrghh,
		eInstruction_vmrghw,		//+
		eInstruction_vmrglb,
		eInstruction_vmrglh,
		eInstruction_vmrglw,		//+
		eInstruction_vdot3fp,		//+
		eInstruction_vdot4fp,		//+
		eInstruction_vmulfp128,
		eInstruction_vnmsubfp,	//+
		eInstruction_vnor,		//+
		eInstruction_vor,			//+
		eInstruction_vperm,		//+
		eInstruction_vpermwi128,
		eInstruction_vpkd3d128,
		eInstruction_vpkpx,
		eInstruction_vpkshss,		//+
		eInstruction_vpkshus,		//+
		eInstruction_vpkswss,		//+
		eInstruction_vpkswus,		//+
		eInstruction_vpkuhum,		//+
		eInstruction_vpkuhus,		//+
		eInstruction_vpkuwum,		//+
		eInstruction_vpkuwus,		//+
		eInstruction_vrefp,		//+
		eInstruction_rfi,
		eInstruction_vrfim,		//+
		eInstruction_vrfin,		//+
		eInstruction_vrfip,		//+
		eInstruction_vrfiz,		//+
		eInstruction_vrlb,
		eInstruction_vrlh,
		eInstruction_vrlimi128,
		eInstruction_vrlw,		//+
		eInstruction_vrsqrtefp,	//+
		eInstruction_vsel,		//+
		eInstruction_vsl,
		eInstruction_vslb,
		eInstruction_vsldoi,		//+
		eInstruction_vslh,
		eInstruction_vslo,		//+
		eInstruction_vslw,		//+
		eInstruction_vspltb,
		eInstruction_vsplth,
		eInstruction_vspltisb,
		eInstruction_vspltish,
		eInstruction_vspltisw,	//+
		eInstruction_vspltw,		//+
		eInstruction_vsr,
		eInstruction_vsrab,
		eInstruction_vsrah,
		eInstruction_vsraw,		//+
		eInstruction_vsrb,
		eInstruction_vsrh,
		eInstruction_vsro,		//+
		eInstruction_vsrw,		//+
		eInstruction_vsubcuw,
		eInstruction_vsubfp,		//+
		eInstruction_vsubsbs,
		eInstruction_vsubshs,
		eInstruction_vsubsws,
		eInstruction_vsububm,
		eInstruction_vsububs,
		eInstruction_vsubuhm,
		eInstruction_vsubuhs,
		eInstruction_vsubuwm,
		eInstruction_vsubuws,
		eInstruction_vupkd3d128,
		eInstruction_vupkhpx,
		eInstruction_vupkhsb,		//+
		eInstruction_vupkhsh,	//+
		eInstruction_vupklpx,
		eInstruction_vupklsb,		//+
		eInstruction_vupklsh,		//+
		eInstruction_vxor,		//+

		//extra
		eInstruction_icbi,
		eInstruction_rotlwi,
		eInstruction_rotrwi,

		eInstruction_MAX
	};

	//the big fuck string version
	static const char* POWER_PC_ASSEMBLY_INSTRUCTIONS_KEYWORD_STRS[eInstruction_MAX] = {
		"nop",

		// move register (with move to/from special registers)
		"mr",
		"mfspr",
		"mfsprg",
		"mfsrr0",
		"mfsrr1",
		"mtspr",
		"mfmsr",
		"mtsrr0",
		"mtsrr1",
		"mtsprg",
		"mfmsrg",
		"mtmsr",
		"mtdar",
		"mtdsisr",
		"mtmsrd",
		"mtmsree",
		"mtxer",
		"mfcr",
		"mtcrf",
		"mfocrf",
		"mtocrf",
		"mcrf",
		"mftb",
		"mflr",
		"mtctr",
		"mfdar",

		// load memory
		"lbz",
		"lhz",
		"lwz",
		"lbzu",
		"lhzu",
		"lwzu",
		"lba",
		"lha",
		"lwa",
		"lbau",
		"lhau",
		"lwau",
		"ld",
		"ldu",
		"lmw",

		// load memory indexed
		"lbzx",
		"lhzx",
		"lwzx",
		"lbzux",
		"lhzux",
		"lwzux",
		"lbax",
		"lhax",
		"lwax",
		"lbaux",
		"lhaux",
		"lwaux",
		"ldx",
		"ldux",

		// store memory
		"stb",
		"sth",
		"stw",
		"std",
		"slwi",
		"stbu",
		"sthu",
		"stwu",
		"stdu",

		// store memory indexed
		"stbx",
		"sthx",
		"stwx",
		"stdx",
		"stbux",
		"sthux",
		"stwux",
		"stdux",

		//quantized store
		"psq_stx",
		"psq_lx",
		"psq_st",
		"psq_l",

		//idk
		"twui",

		// branch instructions
		"b",
		"bdnz",
		"ba",
		"bl",
		"blt",
		"bla",
		"bc",
		"bcl",
		"bca",
		"bcla",
		"bclr",
		"bclrl",
		"bcctr",
		"bcctrl",
		"beq",
		"beq_plus",
		"beqlr",
		"blr",
		"bltlr",
		"bne",
		"bnelr",
		"bge",
		"bgelr",
		"bgt",
		"bctr",
		"bctrl",

		// lwarx/stwcx
		"lwarx",
		"ldarx",
		"stwcxRC", //.
		"stdcxRC", //.

		// memory bariers
		"isync",
		"sync",
		"lwsync",
		"ptesync",
		"eieio",

		// custom
		//"cmp",
		"fcmpu",
		"fcmpo",
		"twi",
		"tdi",
		"tw",
		"td",

		// generic instructions
		"sc",

		// condition register operators
		"crand",
		"cror",
		"crxor",
		"crnand",
		"crnor",
		"creqv",
		"crandc",
		"crorc",
		"crclr",

		// load immediate
		"li",
		"lis",

		// math with immediate value
		"addic",
		"addicRC",
		"addi",
		"addis",
		"subfic",
		"mulli",

		// add XO-form
		"add",
		"addRC",
		"addo",
		"addoRC",

		// subtract grom XO-form
		"subi",
		"subic",
		"subf",
		"subfRC",
		"subfo",
		"subfoRC",

		// add carrying XO-form
		"addc",
		"addcRC",
		"addco",
		"addcoRC",

		// subtract From carrying XO-form
		"subfc",
		"subfcRC",
		"subfco",
		"subfcoRC",

		// add extended XO-form
		"adde",
		"addeRC",
		"addeo",
		"addeoRC",

		// subtract from extended XO-form
		"subfe",
		"subfeRC",
		"subfeo",
		"subfeoRC",
		"subis",

		// add to minus one extended XO-form
		"addme",
		"addmeRC",
		"addmeo",
		"addmeoRC",

		// subtract from minus one extended XO-form
		"subfme",
		"subfmeRC",
		"subfmeo",
		"subfmeoRC",

		// add to zero extended XO-form
		"addze",
		"addzeRC",
		"addzeo",
		"addzeoRC",

		// subtract from zero extended XO-form
		"subfze",
		"subfzeRC",
		"subfzeo",
		"subfzeoRC",

		// negate
		"neg",
		"negRC",
		"nego",
		"negoRC",

		// multiply low doubleword XO-form
		"mulld",
		"mulldRC",
		"mulldo",
		"mulldoRC",

		// multiply low word XO-form
		"mullw",
		"mullwRC",
		"mullwo",
		"mullwoRC",

		// multiply high doubleword XO-form
		"mullhd",
		"mullhdRC",

		// multiply High Word XO-form
		"mullhw",
		"mullhwRC",

		// multiply high doubleword unsigned XO-form
		"mulhdu",
		"mulhduRC",

		// multiply High Word Unsigned XO-form
		"mulhwu",
		"mulhwuRC",

		// divide doubleword XO-form
		"divd",
		"divdRC",
		"divdo",
		"divdoRC",

		// divide word XO-form
		"divw",
		"divwRC",
		"divwo",
		"divwoRC",

		// divide doubleword unsigned XO-form
		"divdu",
		"divduRC",
		"divduo",
		"divduoRC",

		// divide word unsigned XO-form
		"divwu",
		"divwuRC",
		"divwuo",
		"divwuoRC",

		// compare
		"cmpwi",
		"cmpdi",
		"cmplwi",
		"cmpldi",
		"cmpw",
		"cmpd",
		"cmplw",
		"cmpld",

		// logical instructions with immediate values
		"andi",
		"andis",
		"andiRC",
		"andisRC",
		"ori",
		"oris",
		"xori",
		"xoris",

		// logical instructions
		"and",
		"andRC",
		"or",
		"orRC",
		"xor",
		"xorRC",
		"nand",
		"nandRC",
		"nor",
		"norRC",
		"eqv",
		"eqvRC",
		"andc",
		"andcRC",
		"orc",
		"orcRC",

		// byte extend
		"extsb",
		"extsbRC",
		"extsh",
		"extshRC",
		"extsw",
		"extswRC",
		"extrwi",

		// population count
		"popcntb",
		"cntlzw",
		"cntlzwRC",
		"cntlzd",
		"cntlzdRC",

		// Shift instructions with immediate params -->
		// REG",REG",IMM",IMM
		"rldicl",
		"rldiclRC",
		"rldicr",
		"rldicrRC",
		"rldic",
		"rldicRC",
		"rldimi",
		"rldimiRC",
		"clrlwi",
		"clrrwi",
		"clrlslwi",

		// REG",REG",IMM",IMM",IMM
		"rlwinm",
		"rlwinmRC",
		"rlwimi",
		"rlwimiRC",

		// REG",REG",REG",IMM
		"rldcl",
		"rldclRC",
		"rldcr",
		"rldcrRC",

		// REG",REG",REG",IMM",IMM
		"rlwnm",
		"rlwnmRC",

		// Extended shifts
		"sld",
		"sldRC",
		"slw",
		"slwRC",
		"srd",
		"srdRC",
		"srw",
		"srwi",
		"srwRC",
		"srad",
		"sradRC",
		"sraw",
		"srawRC",

		// Extended shifts with immediate... geez..
		"srawi",
		"srawiRC",
		"sradi",
		"sradiRC",

		// Cache operation instructions
		"dcbi",
		"dcbf",
		"dcbst",
		"dcbt",
		"dcbtst",
		"dcbz",

		//  Floating point load instructions
		"lfs",
		"lfsu",
		"lfsx",
		"lfsux",
		"lfd",
		"lfdu",
		"lfdx",
		"lfdux",

		//  Floating point store instructions
		"stfs",
		"stfsu",
		"stfsx",
		"stfsux",
		"stfd",
		"stfdu",
		"stfdx",
		"stfdux",

		// Store float point as integer word indexed
		"stfiwx",

		//store move register
		"stmw",

		// Floating point move and single op instructions
		"fmr",
		"fmrRC",
		"fneg",
		"fnegRC",
		"fabs",
		"fabsRC",
		"fnabs",
		"fnabsRC",

		// Floating point arithmetic instructions
		"fadd",
		"faddRC",
		"fadds",
		"faddsRC",
		"fsub",
		"fsubRC",
		"fsubs",
		"fsubsRC",
		"fmul",
		"fmulRC",
		"fmuls",
		"fmulsRC",
		"fdiv",
		"fdivRC",
		"fdivs",
		"fdivsRC",
		"fsqrt",
		"fsqrtRC",
		"frsqrtx",
		"frsqrtxRC",
		"frsqrte",
		"fre",
		"freRC",

		// Floating point mad instructions
		"fmadd",
		"fmaddRC",
		"fmadds",
		"fmaddsRC",
		"fmsub",
		"fmsubRC",
		"fmsubs",
		"fmsubsRC",
		"fnmadd",
		"fnmaddRC",
		"fnmadds",
		"fnmaddsRC",
		"fnmsub",
		"fnmsubRC",
		"fnmsubs",
		"fnmsubsRC",

		// Floating point rounding and conversion
		"frsp",
		"frspRC",
		"fctid",
		"fctidRC",
		"fctidz",
		"fctidzRC",
		"fctiw",
		"fctiwRC",
		"fctiwz",
		"fctiwzRC",
		"fcfid",
		"fcfidRC",

		// Floating point select
		"fsel",
		"fselRC",

		// Floating point control registers
		"mffs",
		"mffsRC",
		"mcrfs",
		"mtfsfi",
		"mtfsfiRC",
		"mtfsf",
		"mtfsfRC",
		"mtfsb0",
		"mtfsb0RC",
		"mtfsb1",
		"mtfsb1RC",
		"mtlr",

		// VMX instructions
		"lvebx",
		"lvehx",
		"lvewx",		//+
		"lvlx",		//+
		"lvlxl",		//+
		"lvrx",		//+
		"lvrxl",		//+
		"lvsl",
		"lvsr",
		"lvx",			//+
		"lvxl",		//+
		"mfvscr",
		"mtvscr",
		"stvebx",
		"stvehx",
		"stvewx",		//+
		"stvlx",		//+
		"stvlxl",		//+
		"stvrx",		//+
		"stvrxl",		//+
		"stvx",		//+
		"stvxl",		//+
		"lhbrx",
		"lwbrx",
		"sthbrx",
		"stwbrx",
		"lswi",
		"lswx",
		"stswi",
		"stswx",
		"vaddcuw",
		"vaddfp",		//+
		"vaddsbs",
		"vaddshs",
		"vaddsws",
		"vaddubm",
		"vaddubs",
		"vadduhm",
		"vadduhs",
		"vadduwm",
		"vadduws",
		"vand",		//+
		"vandc",		//+
		"vavgsb",
		"vavgsh",
		"vavgsw",
		"vavgub",
		"vavguh",
		"vavguw",
		"vcfpsxws",	//+
		"vcfpuxws",	//+
		"vcsxwfp", //+
		"vcuxwfp", //+
		"vctsxs",	//+
		"vctuxs",		//+
		"vcfsx",	//+
		"vcfux",	//+
		"vcmpbfp",
		"vcmpbfpRC",
		"vcmpeqfp",
		"vcmpeqfpRC",
		"vcmpequb",
		"vcmpequbRC",
		"vcmpequh",
		"vcmpequhRC",
		"vcmpequw",
		"vcmpequwRC",
		"vcmpgefp",
		"vcmpgefpRC",
		"vcmpgtfp",
		"vcmpgtfpRC",
		"vcmpgtsb",
		"vcmpgtsbRC",
		"vcmpgtsh",
		"vcmpgtshRC",
		"vcmpgtsw",
		"vcmpgtswRC",
		"vcmpgtub",
		"vcmpgtubRC",
		"vcmpgtuh",
		"vcmpgtuhRC",
		"vcmpgtuw",
		"vcmpgtuwRC",
		"vexptefp",	//+
		"vlogefp",		//+
		"vmaddcfp128",
		"vmaddfp",		//+
		"vmaxfp",		//+
		"vmaxsb",
		"vmaxsh",
		"vmaxsw",
		"vmaxub",
		"vmaxuh",
		"vmaxuw",
		"vminfp",		//+
		"vminsb",
		"vminsh",
		"vminsw",
		"vminub",
		"vminuh",
		"vminuw",
		"vmrghb",
		"vmrghh",
		"vmrghw",		//+
		"vmrglb",
		"vmrglh",
		"vmrglw",		//+
		"vdot3fp",		//+
		"vdot4fp",		//+
		"vmulfp128",
		"vnmsubfp",	//+
		"vnor",		//+
		"vor",			//+
		"vperm",		//+
		"vpermwi128",
		"vpkd3d128",
		"vpkpx",
		"vpkshss",		//+
		"vpkshus",		//+
		"vpkswss",		//+
		"vpkswus",		//+
		"vpkuhum",		//+
		"vpkuhus",		//+
		"vpkuwum",		//+
		"vpkuwus",		//+
		"vrefp",		//+
		"rfi",
		"vrfim",		//+
		"vrfin",		//+
		"vrfip",		//+
		"vrfiz",		//+
		"vrlb",
		"vrlh",
		"vrlimi128",
		"vrlw",		//+
		"vrsqrtefp",	//+
		"vsel",		//+
		"vsl",
		"vslb",
		"vsldoi",		//+
		"vslh",
		"vslo",		//+
		"vslw",		//+
		"vspltb",
		"vsplth",
		"vspltisb",
		"vspltish",
		"vspltisw",	//+
		"vspltw",		//+
		"vsr",
		"vsrab",
		"vsrah",
		"vsraw",		//+
		"vsrb",
		"vsrh",
		"vsro",		//+
		"vsrw",		//+
		"vsubcuw",
		"vsubfp",		//+
		"vsubsbs",
		"vsubshs",
		"vsubsws",
		"vsububm",
		"vsububs",
		"vsubuhm",
		"vsubuhs",
		"vsubuwm",
		"vsubuws",
		"vupkd3d128",
		"vupkhpx",
		"vupkhsb",		//+
		"vupkhsh",	//+
		"vupklpx",
		"vupklsb",		//+
		"vupklsh",		//+
		"vxor",		//+

		//extra
		"icbi",
		"rotlwi",
		"rotrwi"
	};

	//checks if a string keyword is a assembly instruction
	static inline bool IsASMInstructionStr(const char* keyword, uint32& arrayIndex, EInstruction& instruction)
	{
		for (uint32 i = 0; i < eInstruction_MAX; ++i)
		{
			if (!strcmp(keyword, POWER_PC_ASSEMBLY_INSTRUCTIONS_KEYWORD_STRS[i]))
			{
				arrayIndex = i;
				instruction = (EInstruction)i;
				return true;
			}
		}

		return false;
	}

	//defines specific ASM instruction types
	enum class ASMInstructionKind
	{
		MoveSpecialRegister = 0, //move special register
		
		Store,
		Load,

		Compare,
		Brach,

		Bitshift,

		Max
	};

	//maps specfic assembly instructions to branch variant
	static inline bool IsASMInstructionKind_Branch(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_Branch_Start && inst <= InstructionGroup_Branch_End);
	}

	//maps specfic assembly instructions to move special regsiter variant
	static inline bool IsASMInstructionKind_MoveSpecialRegister(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_MoveRegister_Start && inst <= InstructionGroup_MoveRegister_End);
	}

	//maps specfic assembly instructions to load variant

	//maps specfic assembly instructions to store variant

	//maps specfic assembly instructions to compare variant
	static inline bool IsASMInstructionKind_Compare(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_Compare_Start && inst <= InstructionGroup_Compare_End);
	}

	//maps specfic assembly instructions to bitshift
	static inline bool IsASMInstructionKind_Bitshift(const EInstruction& inst)
	{
		//if it's within the specified, it is one of thoses so we return it
		return (inst >= InstructionGroup_Bitshift_Start && inst <= InstructionGroup_Bitshift_End);
	}

	//gets the specific kind of ASM instruction it is
	static inline void GetASMInstructionKind(const EInstruction& inst, ASMInstructionKind& kind)
	{
		if (IsASMInstructionKind_MoveSpecialRegister(inst))
			kind = ASMInstructionKind::MoveSpecialRegister;
		else if (IsASMInstructionKind_Branch(inst))
			kind = ASMInstructionKind::Brach;
		else if (IsASMInstructionKind_Compare(inst))
			kind = ASMInstructionKind::Compare;
		else if (IsASMInstructionKind_Bitshift(inst))
			kind = ASMInstructionKind::Bitshift;
		else
			kind = ASMInstructionKind::Max;
	}
}