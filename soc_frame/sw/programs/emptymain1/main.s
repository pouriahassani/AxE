
main:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <_start>:
   10074:	00002197          	auipc	gp,0x2
   10078:	2f418193          	addi	gp,gp,756 # 12368 <__global_pointer$>
   1007c:	c3418513          	addi	a0,gp,-972 # 11f9c <_edata>
   10080:	c5018613          	addi	a2,gp,-944 # 11fb8 <__BSS_END__>
   10084:	40a60633          	sub	a2,a2,a0
   10088:	00000593          	li	a1,0
   1008c:	718000ef          	jal	ra,107a4 <memset>
   10090:	00000517          	auipc	a0,0x0
   10094:	61050513          	addi	a0,a0,1552 # 106a0 <__libc_fini_array>
   10098:	5c4000ef          	jal	ra,1065c <atexit>
   1009c:	660000ef          	jal	ra,106fc <__libc_init_array>
   100a0:	00012503          	lw	a0,0(sp)
   100a4:	00410593          	addi	a1,sp,4
   100a8:	00000613          	li	a2,0
   100ac:	0ec000ef          	jal	ra,10198 <main>
   100b0:	5c00006f          	j	10670 <exit>

000100b4 <_fini>:
   100b4:	00008067          	ret

000100b8 <deregister_tm_clones>:
   100b8:	c2818713          	addi	a4,gp,-984 # 11f90 <_global_impure_ptr>
   100bc:	c2818793          	addi	a5,gp,-984 # 11f90 <_global_impure_ptr>
   100c0:	00e78c63          	beq	a5,a4,100d8 <deregister_tm_clones+0x20>
   100c4:	00000337          	lui	t1,0x0
   100c8:	00030313          	mv	t1,t1
   100cc:	00030663          	beqz	t1,100d8 <deregister_tm_clones+0x20>
   100d0:	c2818513          	addi	a0,gp,-984 # 11f90 <_global_impure_ptr>
   100d4:	00030067          	jr	t1 # 0 <_start-0x10074>
   100d8:	00008067          	ret

000100dc <register_tm_clones>:
   100dc:	c2818593          	addi	a1,gp,-984 # 11f90 <_global_impure_ptr>
   100e0:	c2818793          	addi	a5,gp,-984 # 11f90 <_global_impure_ptr>
   100e4:	40f585b3          	sub	a1,a1,a5
   100e8:	4025d593          	srai	a1,a1,0x2
   100ec:	00200793          	li	a5,2
   100f0:	02f5c5b3          	div	a1,a1,a5
   100f4:	00058c63          	beqz	a1,1010c <register_tm_clones+0x30>
   100f8:	00000337          	lui	t1,0x0
   100fc:	00030313          	mv	t1,t1
   10100:	00030663          	beqz	t1,1010c <register_tm_clones+0x30>
   10104:	c2818513          	addi	a0,gp,-984 # 11f90 <_global_impure_ptr>
   10108:	00030067          	jr	t1 # 0 <_start-0x10074>
   1010c:	00008067          	ret

00010110 <__do_global_dtors_aux>:
   10110:	c341c703          	lbu	a4,-972(gp) # 11f9c <_edata>
   10114:	04071663          	bnez	a4,10160 <__do_global_dtors_aux+0x50>
   10118:	ff010113          	addi	sp,sp,-16
   1011c:	00812423          	sw	s0,8(sp)
   10120:	00112623          	sw	ra,12(sp)
   10124:	00078413          	mv	s0,a5
   10128:	f91ff0ef          	jal	ra,100b8 <deregister_tm_clones>
   1012c:	000007b7          	lui	a5,0x0
   10130:	00078793          	mv	a5,a5
   10134:	00078a63          	beqz	a5,10148 <__do_global_dtors_aux+0x38>
   10138:	00012537          	lui	a0,0x12
   1013c:	b5850513          	addi	a0,a0,-1192 # 11b58 <__FRAME_END__>
   10140:	00000097          	auipc	ra,0x0
   10144:	000000e7          	jalr	zero # 0 <_start-0x10074>
   10148:	00100793          	li	a5,1
   1014c:	c2f18a23          	sb	a5,-972(gp) # 11f9c <_edata>
   10150:	00c12083          	lw	ra,12(sp)
   10154:	00812403          	lw	s0,8(sp)
   10158:	01010113          	addi	sp,sp,16
   1015c:	00008067          	ret
   10160:	00008067          	ret

00010164 <frame_dummy>:
   10164:	000007b7          	lui	a5,0x0
   10168:	00078793          	mv	a5,a5
   1016c:	02078463          	beqz	a5,10194 <frame_dummy+0x30>
   10170:	00012537          	lui	a0,0x12
   10174:	ff010113          	addi	sp,sp,-16
   10178:	c3818593          	addi	a1,gp,-968 # 11fa0 <object.5435>
   1017c:	b5850513          	addi	a0,a0,-1192 # 11b58 <__FRAME_END__>
   10180:	00112623          	sw	ra,12(sp)
   10184:	00000097          	auipc	ra,0x0
   10188:	000000e7          	jalr	zero # 0 <_start-0x10074>
   1018c:	00c12083          	lw	ra,12(sp)
   10190:	01010113          	addi	sp,sp,16
   10194:	f49ff06f          	j	100dc <register_tm_clones>

00010198 <main>:
   10198:	fe010113          	addi	sp,sp,-32
   1019c:	00112e23          	sw	ra,28(sp)
   101a0:	00812c23          	sw	s0,24(sp)
   101a4:	02010413          	addi	s0,sp,32
   101a8:	00000793          	li	a5,0
   101ac:	fef42623          	sw	a5,-20(s0)
   101b0:	000117b7          	lui	a5,0x11
   101b4:	a547a783          	lw	a5,-1452(a5) # 10a54 <__errno+0x8>
   101b8:	fef42423          	sw	a5,-24(s0)
   101bc:	fe842583          	lw	a1,-24(s0)
   101c0:	fec42503          	lw	a0,-20(s0)
   101c4:	020000ef          	jal	ra,101e4 <__addsf3>
   101c8:	00050793          	mv	a5,a0
   101cc:	fef42223          	sw	a5,-28(s0)
   101d0:	00000013          	nop
   101d4:	01c12083          	lw	ra,28(sp)
   101d8:	01812403          	lw	s0,24(sp)
   101dc:	02010113          	addi	sp,sp,32
   101e0:	00008067          	ret

000101e4 <__addsf3>:
   101e4:	00800737          	lui	a4,0x800
   101e8:	ff010113          	addi	sp,sp,-16
   101ec:	fff70713          	addi	a4,a4,-1 # 7fffff <__global_pointer$+0x7edc97>
   101f0:	00a777b3          	and	a5,a4,a0
   101f4:	00912223          	sw	s1,4(sp)
   101f8:	01212023          	sw	s2,0(sp)
   101fc:	01f55493          	srli	s1,a0,0x1f
   10200:	01755913          	srli	s2,a0,0x17
   10204:	0175d513          	srli	a0,a1,0x17
   10208:	00b77733          	and	a4,a4,a1
   1020c:	0ff97913          	andi	s2,s2,255
   10210:	0ff57513          	andi	a0,a0,255
   10214:	00112623          	sw	ra,12(sp)
   10218:	00812423          	sw	s0,8(sp)
   1021c:	01f5d593          	srli	a1,a1,0x1f
   10220:	00379793          	slli	a5,a5,0x3
   10224:	00371713          	slli	a4,a4,0x3
   10228:	40a906b3          	sub	a3,s2,a0
   1022c:	18b49463          	bne	s1,a1,103b4 <__addsf3+0x1d0>
   10230:	08d05c63          	blez	a3,102c8 <__addsf3+0xe4>
   10234:	04051c63          	bnez	a0,1028c <__addsf3+0xa8>
   10238:	34070663          	beqz	a4,10584 <__addsf3+0x3a0>
   1023c:	fff68693          	addi	a3,a3,-1
   10240:	02069e63          	bnez	a3,1027c <__addsf3+0x98>
   10244:	00e787b3          	add	a5,a5,a4
   10248:	00090513          	mv	a0,s2
   1024c:	00579713          	slli	a4,a5,0x5
   10250:	10075c63          	bgez	a4,10368 <__addsf3+0x184>
   10254:	00150513          	addi	a0,a0,1
   10258:	0ff00713          	li	a4,255
   1025c:	32e50e63          	beq	a0,a4,10598 <__addsf3+0x3b4>
   10260:	7e000737          	lui	a4,0x7e000
   10264:	0017f693          	andi	a3,a5,1
   10268:	fff70713          	addi	a4,a4,-1 # 7dffffff <__global_pointer$+0x7dfedc97>
   1026c:	0017d793          	srli	a5,a5,0x1
   10270:	00e7f7b3          	and	a5,a5,a4
   10274:	00d7e7b3          	or	a5,a5,a3
   10278:	0f00006f          	j	10368 <__addsf3+0x184>
   1027c:	0ff00613          	li	a2,255
   10280:	00c91e63          	bne	s2,a2,1029c <__addsf3+0xb8>
   10284:	0ff00513          	li	a0,255
   10288:	0e00006f          	j	10368 <__addsf3+0x184>
   1028c:	0ff00613          	li	a2,255
   10290:	fec90ae3          	beq	s2,a2,10284 <__addsf3+0xa0>
   10294:	04000637          	lui	a2,0x4000
   10298:	00c76733          	or	a4,a4,a2
   1029c:	01b00613          	li	a2,27
   102a0:	00d65663          	bge	a2,a3,102ac <__addsf3+0xc8>
   102a4:	00100713          	li	a4,1
   102a8:	f9dff06f          	j	10244 <__addsf3+0x60>
   102ac:	02000613          	li	a2,32
   102b0:	00d755b3          	srl	a1,a4,a3
   102b4:	40d606b3          	sub	a3,a2,a3
   102b8:	00d71733          	sll	a4,a4,a3
   102bc:	00e03733          	snez	a4,a4
   102c0:	00e5e733          	or	a4,a1,a4
   102c4:	f81ff06f          	j	10244 <__addsf3+0x60>
   102c8:	06068663          	beqz	a3,10334 <__addsf3+0x150>
   102cc:	41250633          	sub	a2,a0,s2
   102d0:	02091463          	bnez	s2,102f8 <__addsf3+0x114>
   102d4:	00078e63          	beqz	a5,102f0 <__addsf3+0x10c>
   102d8:	fff60613          	addi	a2,a2,-1 # 3ffffff <__global_pointer$+0x3fedc97>
   102dc:	00061663          	bnez	a2,102e8 <__addsf3+0x104>
   102e0:	00e787b3          	add	a5,a5,a4
   102e4:	f69ff06f          	j	1024c <__addsf3+0x68>
   102e8:	0ff00693          	li	a3,255
   102ec:	00d51e63          	bne	a0,a3,10308 <__addsf3+0x124>
   102f0:	00070793          	mv	a5,a4
   102f4:	0740006f          	j	10368 <__addsf3+0x184>
   102f8:	0ff00693          	li	a3,255
   102fc:	fed50ae3          	beq	a0,a3,102f0 <__addsf3+0x10c>
   10300:	040006b7          	lui	a3,0x4000
   10304:	00d7e7b3          	or	a5,a5,a3
   10308:	01b00693          	li	a3,27
   1030c:	00c6d663          	bge	a3,a2,10318 <__addsf3+0x134>
   10310:	00100793          	li	a5,1
   10314:	fcdff06f          	j	102e0 <__addsf3+0xfc>
   10318:	02000693          	li	a3,32
   1031c:	40c686b3          	sub	a3,a3,a2
   10320:	00c7d5b3          	srl	a1,a5,a2
   10324:	00d797b3          	sll	a5,a5,a3
   10328:	00f037b3          	snez	a5,a5
   1032c:	00f5e7b3          	or	a5,a1,a5
   10330:	fb1ff06f          	j	102e0 <__addsf3+0xfc>
   10334:	00190693          	addi	a3,s2,1
   10338:	0fe6f513          	andi	a0,a3,254
   1033c:	06051063          	bnez	a0,1039c <__addsf3+0x1b8>
   10340:	04091263          	bnez	s2,10384 <__addsf3+0x1a0>
   10344:	fa0786e3          	beqz	a5,102f0 <__addsf3+0x10c>
   10348:	02070063          	beqz	a4,10368 <__addsf3+0x184>
   1034c:	00e787b3          	add	a5,a5,a4
   10350:	00579713          	slli	a4,a5,0x5
   10354:	00075a63          	bgez	a4,10368 <__addsf3+0x184>
   10358:	fc000737          	lui	a4,0xfc000
   1035c:	fff70713          	addi	a4,a4,-1 # fbffffff <__global_pointer$+0xfbfedc97>
   10360:	00e7f7b3          	and	a5,a5,a4
   10364:	00100513          	li	a0,1
   10368:	0077f713          	andi	a4,a5,7
   1036c:	22070863          	beqz	a4,1059c <__addsf3+0x3b8>
   10370:	00f7f713          	andi	a4,a5,15
   10374:	00400693          	li	a3,4
   10378:	22d70263          	beq	a4,a3,1059c <__addsf3+0x3b8>
   1037c:	00478793          	addi	a5,a5,4
   10380:	21c0006f          	j	1059c <__addsf3+0x3b8>
   10384:	20078463          	beqz	a5,1058c <__addsf3+0x3a8>
   10388:	ee070ee3          	beqz	a4,10284 <__addsf3+0xa0>
   1038c:	00000493          	li	s1,0
   10390:	020007b7          	lui	a5,0x2000
   10394:	0ff00513          	li	a0,255
   10398:	2040006f          	j	1059c <__addsf3+0x3b8>
   1039c:	0ff00613          	li	a2,255
   103a0:	1ec68a63          	beq	a3,a2,10594 <__addsf3+0x3b0>
   103a4:	00e787b3          	add	a5,a5,a4
   103a8:	0017d793          	srli	a5,a5,0x1
   103ac:	00068513          	mv	a0,a3
   103b0:	fb9ff06f          	j	10368 <__addsf3+0x184>
   103b4:	08d05863          	blez	a3,10444 <__addsf3+0x260>
   103b8:	04051863          	bnez	a0,10408 <__addsf3+0x224>
   103bc:	00090513          	mv	a0,s2
   103c0:	fa0704e3          	beqz	a4,10368 <__addsf3+0x184>
   103c4:	fff68693          	addi	a3,a3,-1 # 3ffffff <__global_pointer$+0x3fedc97>
   103c8:	02069263          	bnez	a3,103ec <__addsf3+0x208>
   103cc:	40e787b3          	sub	a5,a5,a4
   103d0:	00579713          	slli	a4,a5,0x5
   103d4:	f8075ae3          	bgez	a4,10368 <__addsf3+0x184>
   103d8:	04000437          	lui	s0,0x4000
   103dc:	fff40413          	addi	s0,s0,-1 # 3ffffff <__global_pointer$+0x3fedc97>
   103e0:	0087f433          	and	s0,a5,s0
   103e4:	00050913          	mv	s2,a0
   103e8:	13c0006f          	j	10524 <__addsf3+0x340>
   103ec:	0ff00613          	li	a2,255
   103f0:	0ff00513          	li	a0,255
   103f4:	f6c90ae3          	beq	s2,a2,10368 <__addsf3+0x184>
   103f8:	01b00613          	li	a2,27
   103fc:	02d65263          	bge	a2,a3,10420 <__addsf3+0x23c>
   10400:	00100713          	li	a4,1
   10404:	0340006f          	j	10438 <__addsf3+0x254>
   10408:	0ff00613          	li	a2,255
   1040c:	0ff00513          	li	a0,255
   10410:	f4c90ce3          	beq	s2,a2,10368 <__addsf3+0x184>
   10414:	04000637          	lui	a2,0x4000
   10418:	00c76733          	or	a4,a4,a2
   1041c:	fddff06f          	j	103f8 <__addsf3+0x214>
   10420:	02000613          	li	a2,32
   10424:	00d755b3          	srl	a1,a4,a3
   10428:	40d606b3          	sub	a3,a2,a3
   1042c:	00d71733          	sll	a4,a4,a3
   10430:	00e03733          	snez	a4,a4
   10434:	00e5e733          	or	a4,a1,a4
   10438:	40e787b3          	sub	a5,a5,a4
   1043c:	00090513          	mv	a0,s2
   10440:	f91ff06f          	j	103d0 <__addsf3+0x1ec>
   10444:	06068a63          	beqz	a3,104b8 <__addsf3+0x2d4>
   10448:	41250633          	sub	a2,a0,s2
   1044c:	02091863          	bnez	s2,1047c <__addsf3+0x298>
   10450:	02078063          	beqz	a5,10470 <__addsf3+0x28c>
   10454:	fff60613          	addi	a2,a2,-1 # 3ffffff <__global_pointer$+0x3fedc97>
   10458:	00061863          	bnez	a2,10468 <__addsf3+0x284>
   1045c:	40f707b3          	sub	a5,a4,a5
   10460:	00058493          	mv	s1,a1
   10464:	f6dff06f          	j	103d0 <__addsf3+0x1ec>
   10468:	0ff00693          	li	a3,255
   1046c:	02d51063          	bne	a0,a3,1048c <__addsf3+0x2a8>
   10470:	00070793          	mv	a5,a4
   10474:	00058493          	mv	s1,a1
   10478:	ef1ff06f          	j	10368 <__addsf3+0x184>
   1047c:	0ff00693          	li	a3,255
   10480:	fed508e3          	beq	a0,a3,10470 <__addsf3+0x28c>
   10484:	040006b7          	lui	a3,0x4000
   10488:	00d7e7b3          	or	a5,a5,a3
   1048c:	01b00693          	li	a3,27
   10490:	00c6d663          	bge	a3,a2,1049c <__addsf3+0x2b8>
   10494:	00100793          	li	a5,1
   10498:	fc5ff06f          	j	1045c <__addsf3+0x278>
   1049c:	02000693          	li	a3,32
   104a0:	40c686b3          	sub	a3,a3,a2
   104a4:	00c7d833          	srl	a6,a5,a2
   104a8:	00d797b3          	sll	a5,a5,a3
   104ac:	00f037b3          	snez	a5,a5
   104b0:	00f867b3          	or	a5,a6,a5
   104b4:	fa9ff06f          	j	1045c <__addsf3+0x278>
   104b8:	00190513          	addi	a0,s2,1
   104bc:	0fe57513          	andi	a0,a0,254
   104c0:	04051863          	bnez	a0,10510 <__addsf3+0x32c>
   104c4:	02091c63          	bnez	s2,104fc <__addsf3+0x318>
   104c8:	00079a63          	bnez	a5,104dc <__addsf3+0x2f8>
   104cc:	fa0712e3          	bnez	a4,10470 <__addsf3+0x28c>
   104d0:	00000793          	li	a5,0
   104d4:	00000493          	li	s1,0
   104d8:	0c40006f          	j	1059c <__addsf3+0x3b8>
   104dc:	e80706e3          	beqz	a4,10368 <__addsf3+0x184>
   104e0:	40e786b3          	sub	a3,a5,a4
   104e4:	00569613          	slli	a2,a3,0x5
   104e8:	40f707b3          	sub	a5,a4,a5
   104ec:	f80644e3          	bltz	a2,10474 <__addsf3+0x290>
   104f0:	fe0680e3          	beqz	a3,104d0 <__addsf3+0x2ec>
   104f4:	00068793          	mv	a5,a3
   104f8:	e71ff06f          	j	10368 <__addsf3+0x184>
   104fc:	e80796e3          	bnez	a5,10388 <__addsf3+0x1a4>
   10500:	e80706e3          	beqz	a4,1038c <__addsf3+0x1a8>
   10504:	00070793          	mv	a5,a4
   10508:	00058493          	mv	s1,a1
   1050c:	d79ff06f          	j	10284 <__addsf3+0xa0>
   10510:	40e78433          	sub	s0,a5,a4
   10514:	00541693          	slli	a3,s0,0x5
   10518:	0406d463          	bgez	a3,10560 <__addsf3+0x37c>
   1051c:	40f70433          	sub	s0,a4,a5
   10520:	00058493          	mv	s1,a1
   10524:	00040513          	mv	a0,s0
   10528:	0e8000ef          	jal	ra,10610 <__clzsi2>
   1052c:	ffb50513          	addi	a0,a0,-5
   10530:	00a41433          	sll	s0,s0,a0
   10534:	03254e63          	blt	a0,s2,10570 <__addsf3+0x38c>
   10538:	41250533          	sub	a0,a0,s2
   1053c:	00150513          	addi	a0,a0,1
   10540:	02000713          	li	a4,32
   10544:	00a457b3          	srl	a5,s0,a0
   10548:	40a70533          	sub	a0,a4,a0
   1054c:	00a41433          	sll	s0,s0,a0
   10550:	00803433          	snez	s0,s0
   10554:	0087e7b3          	or	a5,a5,s0
   10558:	00000513          	li	a0,0
   1055c:	e0dff06f          	j	10368 <__addsf3+0x184>
   10560:	fc0412e3          	bnez	s0,10524 <__addsf3+0x340>
   10564:	00000793          	li	a5,0
   10568:	00000513          	li	a0,0
   1056c:	f69ff06f          	j	104d4 <__addsf3+0x2f0>
   10570:	fc0007b7          	lui	a5,0xfc000
   10574:	fff78793          	addi	a5,a5,-1 # fbffffff <__global_pointer$+0xfbfedc97>
   10578:	40a90533          	sub	a0,s2,a0
   1057c:	00f477b3          	and	a5,s0,a5
   10580:	de9ff06f          	j	10368 <__addsf3+0x184>
   10584:	00090513          	mv	a0,s2
   10588:	de1ff06f          	j	10368 <__addsf3+0x184>
   1058c:	00070793          	mv	a5,a4
   10590:	cf5ff06f          	j	10284 <__addsf3+0xa0>
   10594:	0ff00513          	li	a0,255
   10598:	00000793          	li	a5,0
   1059c:	00579713          	slli	a4,a5,0x5
   105a0:	00075e63          	bgez	a4,105bc <__addsf3+0x3d8>
   105a4:	00150513          	addi	a0,a0,1
   105a8:	0ff00713          	li	a4,255
   105ac:	04e50e63          	beq	a0,a4,10608 <__addsf3+0x424>
   105b0:	fc000737          	lui	a4,0xfc000
   105b4:	fff70713          	addi	a4,a4,-1 # fbffffff <__global_pointer$+0xfbfedc97>
   105b8:	00e7f7b3          	and	a5,a5,a4
   105bc:	0ff00713          	li	a4,255
   105c0:	0037d793          	srli	a5,a5,0x3
   105c4:	00e51863          	bne	a0,a4,105d4 <__addsf3+0x3f0>
   105c8:	00078663          	beqz	a5,105d4 <__addsf3+0x3f0>
   105cc:	004007b7          	lui	a5,0x400
   105d0:	00000493          	li	s1,0
   105d4:	0ff57513          	andi	a0,a0,255
   105d8:	00c12083          	lw	ra,12(sp)
   105dc:	00812403          	lw	s0,8(sp)
   105e0:	00979793          	slli	a5,a5,0x9
   105e4:	01751713          	slli	a4,a0,0x17
   105e8:	0097d513          	srli	a0,a5,0x9
   105ec:	01f49493          	slli	s1,s1,0x1f
   105f0:	00e56533          	or	a0,a0,a4
   105f4:	00956533          	or	a0,a0,s1
   105f8:	00012903          	lw	s2,0(sp)
   105fc:	00412483          	lw	s1,4(sp)
   10600:	01010113          	addi	sp,sp,16
   10604:	00008067          	ret
   10608:	00000793          	li	a5,0
   1060c:	fb1ff06f          	j	105bc <__addsf3+0x3d8>

00010610 <__clzsi2>:
   10610:	000107b7          	lui	a5,0x10
   10614:	02f57a63          	bgeu	a0,a5,10648 <__clzsi2+0x38>
   10618:	0ff00793          	li	a5,255
   1061c:	00a7b7b3          	sltu	a5,a5,a0
   10620:	00379793          	slli	a5,a5,0x3
   10624:	02000713          	li	a4,32
   10628:	40f70733          	sub	a4,a4,a5
   1062c:	00f557b3          	srl	a5,a0,a5
   10630:	00011537          	lui	a0,0x11
   10634:	a5850513          	addi	a0,a0,-1448 # 10a58 <__clz_tab>
   10638:	00a787b3          	add	a5,a5,a0
   1063c:	0007c503          	lbu	a0,0(a5) # 10000 <_start-0x74>
   10640:	40a70533          	sub	a0,a4,a0
   10644:	00008067          	ret
   10648:	01000737          	lui	a4,0x1000
   1064c:	01000793          	li	a5,16
   10650:	fce56ae3          	bltu	a0,a4,10624 <__clzsi2+0x14>
   10654:	01800793          	li	a5,24
   10658:	fcdff06f          	j	10624 <__clzsi2+0x14>

0001065c <atexit>:
   1065c:	00050593          	mv	a1,a0
   10660:	00000693          	li	a3,0
   10664:	00000613          	li	a2,0
   10668:	00000513          	li	a0,0
   1066c:	2140006f          	j	10880 <__register_exitproc>

00010670 <exit>:
   10670:	ff010113          	addi	sp,sp,-16
   10674:	00000593          	li	a1,0
   10678:	00812423          	sw	s0,8(sp)
   1067c:	00112623          	sw	ra,12(sp)
   10680:	00050413          	mv	s0,a0
   10684:	278000ef          	jal	ra,108fc <__call_exitprocs>
   10688:	c281a503          	lw	a0,-984(gp) # 11f90 <_global_impure_ptr>
   1068c:	03c52783          	lw	a5,60(a0)
   10690:	00078463          	beqz	a5,10698 <exit+0x28>
   10694:	000780e7          	jalr	a5
   10698:	00040513          	mv	a0,s0
   1069c:	36c000ef          	jal	ra,10a08 <_exit>

000106a0 <__libc_fini_array>:
   106a0:	ff010113          	addi	sp,sp,-16
   106a4:	000127b7          	lui	a5,0x12
   106a8:	00812423          	sw	s0,8(sp)
   106ac:	00012437          	lui	s0,0x12
   106b0:	b6078713          	addi	a4,a5,-1184 # 11b60 <__init_array_end>
   106b4:	b6440413          	addi	s0,s0,-1180 # 11b64 <__fini_array_end>
   106b8:	40e40433          	sub	s0,s0,a4
   106bc:	00912223          	sw	s1,4(sp)
   106c0:	00112623          	sw	ra,12(sp)
   106c4:	40245413          	srai	s0,s0,0x2
   106c8:	b6078493          	addi	s1,a5,-1184
   106cc:	00041c63          	bnez	s0,106e4 <__libc_fini_array+0x44>
   106d0:	00812403          	lw	s0,8(sp)
   106d4:	00c12083          	lw	ra,12(sp)
   106d8:	00412483          	lw	s1,4(sp)
   106dc:	01010113          	addi	sp,sp,16
   106e0:	9d5ff06f          	j	100b4 <_fini>
   106e4:	fff40413          	addi	s0,s0,-1
   106e8:	00241793          	slli	a5,s0,0x2
   106ec:	00f487b3          	add	a5,s1,a5
   106f0:	0007a783          	lw	a5,0(a5)
   106f4:	000780e7          	jalr	a5
   106f8:	fd5ff06f          	j	106cc <__libc_fini_array+0x2c>

000106fc <__libc_init_array>:
   106fc:	ff010113          	addi	sp,sp,-16
   10700:	000127b7          	lui	a5,0x12
   10704:	00812423          	sw	s0,8(sp)
   10708:	00012437          	lui	s0,0x12
   1070c:	b5c78713          	addi	a4,a5,-1188 # 11b5c <__frame_dummy_init_array_entry>
   10710:	b5c40413          	addi	s0,s0,-1188 # 11b5c <__frame_dummy_init_array_entry>
   10714:	40e40433          	sub	s0,s0,a4
   10718:	00912223          	sw	s1,4(sp)
   1071c:	01212023          	sw	s2,0(sp)
   10720:	00112623          	sw	ra,12(sp)
   10724:	40245413          	srai	s0,s0,0x2
   10728:	00000493          	li	s1,0
   1072c:	b5c78913          	addi	s2,a5,-1188
   10730:	04849263          	bne	s1,s0,10774 <__libc_init_array+0x78>
   10734:	981ff0ef          	jal	ra,100b4 <_fini>
   10738:	000127b7          	lui	a5,0x12
   1073c:	00012437          	lui	s0,0x12
   10740:	b5c78713          	addi	a4,a5,-1188 # 11b5c <__frame_dummy_init_array_entry>
   10744:	b6040413          	addi	s0,s0,-1184 # 11b60 <__init_array_end>
   10748:	40e40433          	sub	s0,s0,a4
   1074c:	40245413          	srai	s0,s0,0x2
   10750:	00000493          	li	s1,0
   10754:	b5c78913          	addi	s2,a5,-1188
   10758:	02849a63          	bne	s1,s0,1078c <__libc_init_array+0x90>
   1075c:	00c12083          	lw	ra,12(sp)
   10760:	00812403          	lw	s0,8(sp)
   10764:	00412483          	lw	s1,4(sp)
   10768:	00012903          	lw	s2,0(sp)
   1076c:	01010113          	addi	sp,sp,16
   10770:	00008067          	ret
   10774:	00249793          	slli	a5,s1,0x2
   10778:	00f907b3          	add	a5,s2,a5
   1077c:	0007a783          	lw	a5,0(a5)
   10780:	00148493          	addi	s1,s1,1
   10784:	000780e7          	jalr	a5
   10788:	fa9ff06f          	j	10730 <__libc_init_array+0x34>
   1078c:	00249793          	slli	a5,s1,0x2
   10790:	00f907b3          	add	a5,s2,a5
   10794:	0007a783          	lw	a5,0(a5)
   10798:	00148493          	addi	s1,s1,1
   1079c:	000780e7          	jalr	a5
   107a0:	fb9ff06f          	j	10758 <__libc_init_array+0x5c>

000107a4 <memset>:
   107a4:	00f00313          	li	t1,15
   107a8:	00050713          	mv	a4,a0
   107ac:	02c37e63          	bgeu	t1,a2,107e8 <memset+0x44>
   107b0:	00f77793          	andi	a5,a4,15
   107b4:	0a079063          	bnez	a5,10854 <memset+0xb0>
   107b8:	08059263          	bnez	a1,1083c <memset+0x98>
   107bc:	ff067693          	andi	a3,a2,-16
   107c0:	00f67613          	andi	a2,a2,15
   107c4:	00e686b3          	add	a3,a3,a4
   107c8:	00b72023          	sw	a1,0(a4) # 1000000 <__global_pointer$+0xfedc98>
   107cc:	00b72223          	sw	a1,4(a4)
   107d0:	00b72423          	sw	a1,8(a4)
   107d4:	00b72623          	sw	a1,12(a4)
   107d8:	01070713          	addi	a4,a4,16
   107dc:	fed766e3          	bltu	a4,a3,107c8 <memset+0x24>
   107e0:	00061463          	bnez	a2,107e8 <memset+0x44>
   107e4:	00008067          	ret
   107e8:	40c306b3          	sub	a3,t1,a2
   107ec:	00269693          	slli	a3,a3,0x2
   107f0:	00000297          	auipc	t0,0x0
   107f4:	005686b3          	add	a3,a3,t0
   107f8:	00c68067          	jr	12(a3) # 400000c <__global_pointer$+0x3fedca4>
   107fc:	00b70723          	sb	a1,14(a4)
   10800:	00b706a3          	sb	a1,13(a4)
   10804:	00b70623          	sb	a1,12(a4)
   10808:	00b705a3          	sb	a1,11(a4)
   1080c:	00b70523          	sb	a1,10(a4)
   10810:	00b704a3          	sb	a1,9(a4)
   10814:	00b70423          	sb	a1,8(a4)
   10818:	00b703a3          	sb	a1,7(a4)
   1081c:	00b70323          	sb	a1,6(a4)
   10820:	00b702a3          	sb	a1,5(a4)
   10824:	00b70223          	sb	a1,4(a4)
   10828:	00b701a3          	sb	a1,3(a4)
   1082c:	00b70123          	sb	a1,2(a4)
   10830:	00b700a3          	sb	a1,1(a4)
   10834:	00b70023          	sb	a1,0(a4)
   10838:	00008067          	ret
   1083c:	0ff5f593          	andi	a1,a1,255
   10840:	00859693          	slli	a3,a1,0x8
   10844:	00d5e5b3          	or	a1,a1,a3
   10848:	01059693          	slli	a3,a1,0x10
   1084c:	00d5e5b3          	or	a1,a1,a3
   10850:	f6dff06f          	j	107bc <memset+0x18>
   10854:	00279693          	slli	a3,a5,0x2
   10858:	00000297          	auipc	t0,0x0
   1085c:	005686b3          	add	a3,a3,t0
   10860:	00008293          	mv	t0,ra
   10864:	fa0680e7          	jalr	-96(a3)
   10868:	00028093          	mv	ra,t0
   1086c:	ff078793          	addi	a5,a5,-16
   10870:	40f70733          	sub	a4,a4,a5
   10874:	00f60633          	add	a2,a2,a5
   10878:	f6c378e3          	bgeu	t1,a2,107e8 <memset+0x44>
   1087c:	f3dff06f          	j	107b8 <memset+0x14>

00010880 <__register_exitproc>:
   10880:	c281a703          	lw	a4,-984(gp) # 11f90 <_global_impure_ptr>
   10884:	00050313          	mv	t1,a0
   10888:	14872783          	lw	a5,328(a4)
   1088c:	00079663          	bnez	a5,10898 <__register_exitproc+0x18>
   10890:	14c70793          	addi	a5,a4,332
   10894:	14f72423          	sw	a5,328(a4)
   10898:	0047a703          	lw	a4,4(a5)
   1089c:	01f00813          	li	a6,31
   108a0:	fff00513          	li	a0,-1
   108a4:	04e84a63          	blt	a6,a4,108f8 <__register_exitproc+0x78>
   108a8:	00271893          	slli	a7,a4,0x2
   108ac:	02030c63          	beqz	t1,108e4 <__register_exitproc+0x64>
   108b0:	01178533          	add	a0,a5,a7
   108b4:	08c52423          	sw	a2,136(a0)
   108b8:	1887a803          	lw	a6,392(a5)
   108bc:	00100613          	li	a2,1
   108c0:	00e61633          	sll	a2,a2,a4
   108c4:	00c86833          	or	a6,a6,a2
   108c8:	1907a423          	sw	a6,392(a5)
   108cc:	10d52423          	sw	a3,264(a0)
   108d0:	00200693          	li	a3,2
   108d4:	00d31863          	bne	t1,a3,108e4 <__register_exitproc+0x64>
   108d8:	18c7a683          	lw	a3,396(a5)
   108dc:	00c6e633          	or	a2,a3,a2
   108e0:	18c7a623          	sw	a2,396(a5)
   108e4:	00170713          	addi	a4,a4,1
   108e8:	00e7a223          	sw	a4,4(a5)
   108ec:	011787b3          	add	a5,a5,a7
   108f0:	00b7a423          	sw	a1,8(a5)
   108f4:	00000513          	li	a0,0
   108f8:	00008067          	ret

000108fc <__call_exitprocs>:
   108fc:	fd010113          	addi	sp,sp,-48
   10900:	01312e23          	sw	s3,28(sp)
   10904:	c281a983          	lw	s3,-984(gp) # 11f90 <_global_impure_ptr>
   10908:	01412c23          	sw	s4,24(sp)
   1090c:	01512a23          	sw	s5,20(sp)
   10910:	01612823          	sw	s6,16(sp)
   10914:	02112623          	sw	ra,44(sp)
   10918:	02812423          	sw	s0,40(sp)
   1091c:	02912223          	sw	s1,36(sp)
   10920:	03212023          	sw	s2,32(sp)
   10924:	01712623          	sw	s7,12(sp)
   10928:	00050a93          	mv	s5,a0
   1092c:	00058a13          	mv	s4,a1
   10930:	00100b13          	li	s6,1
   10934:	1489a483          	lw	s1,328(s3)
   10938:	00048c63          	beqz	s1,10950 <__call_exitprocs+0x54>
   1093c:	0044a403          	lw	s0,4(s1)
   10940:	fff40913          	addi	s2,s0,-1
   10944:	00241413          	slli	s0,s0,0x2
   10948:	00848433          	add	s0,s1,s0
   1094c:	02095863          	bgez	s2,1097c <__call_exitprocs+0x80>
   10950:	02c12083          	lw	ra,44(sp)
   10954:	02812403          	lw	s0,40(sp)
   10958:	02412483          	lw	s1,36(sp)
   1095c:	02012903          	lw	s2,32(sp)
   10960:	01c12983          	lw	s3,28(sp)
   10964:	01812a03          	lw	s4,24(sp)
   10968:	01412a83          	lw	s5,20(sp)
   1096c:	01012b03          	lw	s6,16(sp)
   10970:	00c12b83          	lw	s7,12(sp)
   10974:	03010113          	addi	sp,sp,48
   10978:	00008067          	ret
   1097c:	000a0c63          	beqz	s4,10994 <__call_exitprocs+0x98>
   10980:	10442783          	lw	a5,260(s0)
   10984:	01478863          	beq	a5,s4,10994 <__call_exitprocs+0x98>
   10988:	fff90913          	addi	s2,s2,-1
   1098c:	ffc40413          	addi	s0,s0,-4
   10990:	fbdff06f          	j	1094c <__call_exitprocs+0x50>
   10994:	0044a703          	lw	a4,4(s1)
   10998:	00442783          	lw	a5,4(s0)
   1099c:	fff70713          	addi	a4,a4,-1
   109a0:	03271c63          	bne	a4,s2,109d8 <__call_exitprocs+0xdc>
   109a4:	0124a223          	sw	s2,4(s1)
   109a8:	fe0780e3          	beqz	a5,10988 <__call_exitprocs+0x8c>
   109ac:	1884a683          	lw	a3,392(s1)
   109b0:	012b1733          	sll	a4,s6,s2
   109b4:	0044ab83          	lw	s7,4(s1)
   109b8:	00d776b3          	and	a3,a4,a3
   109bc:	02069263          	bnez	a3,109e0 <__call_exitprocs+0xe4>
   109c0:	000780e7          	jalr	a5
   109c4:	0044a783          	lw	a5,4(s1)
   109c8:	f77796e3          	bne	a5,s7,10934 <__call_exitprocs+0x38>
   109cc:	1489a783          	lw	a5,328(s3)
   109d0:	fa978ce3          	beq	a5,s1,10988 <__call_exitprocs+0x8c>
   109d4:	f61ff06f          	j	10934 <__call_exitprocs+0x38>
   109d8:	00042223          	sw	zero,4(s0)
   109dc:	fcdff06f          	j	109a8 <__call_exitprocs+0xac>
   109e0:	18c4a683          	lw	a3,396(s1)
   109e4:	08442583          	lw	a1,132(s0)
   109e8:	00d77733          	and	a4,a4,a3
   109ec:	00071863          	bnez	a4,109fc <__call_exitprocs+0x100>
   109f0:	000a8513          	mv	a0,s5
   109f4:	000780e7          	jalr	a5
   109f8:	fcdff06f          	j	109c4 <__call_exitprocs+0xc8>
   109fc:	00058513          	mv	a0,a1
   10a00:	000780e7          	jalr	a5
   10a04:	fc1ff06f          	j	109c4 <__call_exitprocs+0xc8>

00010a08 <_exit>:
   10a08:	00000593          	li	a1,0
   10a0c:	00000613          	li	a2,0
   10a10:	00000693          	li	a3,0
   10a14:	00000713          	li	a4,0
   10a18:	00000793          	li	a5,0
   10a1c:	05d00893          	li	a7,93
   10a20:	00000073          	ecall
   10a24:	02055263          	bgez	a0,10a48 <_exit+0x40>
   10a28:	ff010113          	addi	sp,sp,-16
   10a2c:	00812423          	sw	s0,8(sp)
   10a30:	00050413          	mv	s0,a0
   10a34:	00112623          	sw	ra,12(sp)
   10a38:	40800433          	neg	s0,s0
   10a3c:	010000ef          	jal	ra,10a4c <__errno>
   10a40:	00852023          	sw	s0,0(a0)
   10a44:	0000006f          	j	10a44 <_exit+0x3c>
   10a48:	0000006f          	j	10a48 <_exit+0x40>

00010a4c <__errno>:
   10a4c:	c301a503          	lw	a0,-976(gp) # 11f98 <_impure_ptr>
   10a50:	00008067          	ret
