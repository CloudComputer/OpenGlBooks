const char* fp_str_update_position_only_by_vel=
"!!FP1.0\n"\
"# cgc version 1.3.0001, build date Aug  4 2004 10:01:10\n"\
"# command line args: -profile fp30\n"\
"# source file: update_position_only_by_vel.cg\n"\
"# source file: ./sph.cg\n"\
"#vendor NVIDIA Corporation\n"\
"#version 1.0.02\n"\
"#profile fp30\n"\
"#program main\n"\
"#semantic main.attr_rect : TEXUNIT0\n"\
"#semantic main.timestep\n"\
"#semantic MASS\n"\
"#semantic SMOOTHING_LENGTH\n"\
"#semantic VISCOSITY\n"\
"#var fixed index : $vin.TEX0 : TEX0 : 0 : 1\n"\
"#var samplerRECT attr_rect : TEXUNIT0 : texunit 0 : 1 : 1\n"\
"#var float timestep :  :  : 2 : 1\n"\
"#var float3 result : $vout.COL : COL : 3 : 1\n"\
"#var float MASS :  :  : -1 : 0\n"\
"#var float SMOOTHING_LENGTH :  :  : -1 : 0\n"\
"#var float VISCOSITY :  :  : -1 : 0\n"\
"#default MASS = 0.00020543\n"\
"#default SMOOTHING_LENGTH = 0.01\n"\
"#default VISCOSITY = 0.1\n"\
"DECLARE timestep;\n"\
"MOVH  H0.x, f[TEX0];\n"\
"MOVH  H0.y, {1}.x;\n"\
"TEX   R0.xyz, H0, TEX0, RECT;\n"\
"MOVH  H0.x, f[TEX0];\n"\
"MOVH  H0.y, {0}.x;\n"\
"TEX   R1.xyz, H0, TEX0, RECT;\n"\
"MADR  o[COLR].xyz, R0, timestep.x, R1;\n"\
"END\n"\
"# 7 instructions, 2 R-regs, 1 H-regs\n"\
"";
