# RISC_V-SECURITY_ALARM_SYSTEM


In this project, we are going to design Laser Light Security System Using RISCV with Alarm with the application of Laser Diode Module KY-008. The project idea revolves around creating a security system. Whenever any object will obstruct the LASER ray the buzzer alarm will start ringing.

This project can be implemented anywhere, not only buildings or premises but many precious things like jewelry, diamonds, precious antique items in the museum, etc many other things are also secured using such an invisible LASER beam. Many people secure their home, office, shops, warehouses, etc with the LASER beam security system.


# Circuit Diagram
![alarmsystem](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/ce64a096-e601-49e6-afb8-408ac385ec39)

# Block Diagram

![Slide1](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/61f43221-77c9-4820-983e-25adcf84f518)


# Working Principle

The project basically works on the principle of interruption. If by any means the LASER light is interrupted the alarm will start unless it is reset with push-button. The laser is a concentrated light source that puts out a straight beam of light of a single color

The LDR is sensitive to light and puts out a voltage when the laser light hits it. When the laser beam is interrupted and can’t reach LDR, its voltage output changes, and eventually the alarm will ring


# C Code 

```

int laserPin;
int sensorPin;
int buttonPin;
int buzzerPin;

int laserThreshold=100;

int alarmState = 0; // Define alarmState as a bit of P1

unsigned int startTime = 0;
unsigned int sensorValue = 0;

void main() {
    laserPin = 0;  // Configure laserPin as output
    buzzerPin = 0; // Configure buzzerPin as output

    buttonPin = 1; // Enable the pull-up resistor for buttonPin
    alarmState = 0; // Initialize alarmState as 0

    while (1) {
        switch (alarmState) {
            case 0:
                if (startTime == 0) {
                    startTime = 1; // Start the 1-second timer
                    laserPin = 1;
                } else if (startTime < 1000) {
                    // Increment the timer
                    startTime++;
                } else {
                    sensorValue = sensorPin; // Read the sensor (assuming it's an analog sensor)
                    // we need an ADC to read the analog sensor value

                    if (sensorValue > laserThreshold) {
                        alarmState = 1;
                    }
                    laserPin = 0;
                    startTime = 0; // Reset the timer
                }
                break;
            
            case 1:
                // Activate the buzzer (you may need to implement a function to generate tone)
                // ...
                if (!buttonPin) {
                    alarmState = 0;
                    // Turn off the buzzer (you may need to implement a function to stop the tone)
                    // ...
                }
                break;
        }
    }
}
```

# Converting C code into Assembly Language

```
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o alar2.o alar1.c load.S
riscv64-unknown-elf-objdump -d alar2.o
```




# Assembly Code

```
Disassembly of section .text:

00000000000100b0 <main>:
   100b0:	fa01ac23          	sw	zero,-72(gp) # 11df0 <laserPin>
   100b4:	00100713          	li	a4,1
   100b8:	fa01ae23          	sw	zero,-68(gp) # 11df4 <buzzerPin>
   100bc:	fae1a823          	sw	a4,-80(gp) # 11de8 <buttonPin>
   100c0:	f601a823          	sw	zero,-144(gp) # 11da8 <alarmState>
   100c4:	fb41a603          	lw	a2,-76(gp) # 11dec <sensorPin>
   100c8:	f581a683          	lw	a3,-168(gp) # 11d90 <laserThreshold>
   100cc:	f6c1a783          	lw	a5,-148(gp) # 11da4 <startTime>
   100d0:	3e700713          	li	a4,999
   100d4:	00079463          	bnez	a5,100dc <main+0x2c>
   100d8:	00200793          	li	a5,2
   100dc:	00f77663          	bgeu	a4,a5,100e8 <main+0x38>
   100e0:	fec6fce3          	bgeu	a3,a2,100d8 <main+0x28>
   100e4:	0000006f          	j	100e4 <main+0x34>
   100e8:	0017879b          	addiw	a5,a5,1
   100ec:	fe0786e3          	beqz	a5,100d8 <main+0x28>
   100f0:	fedff06f          	j	100dc <main+0x2c>

00000000000100f4 <register_fini>:
   100f4:	ffff0797          	auipc	a5,0xffff0
   100f8:	f0c78793          	addi	a5,a5,-244 # 0 <main-0x100b0>
   100fc:	00078863          	beqz	a5,1010c <register_fini+0x18>
   10100:	00000517          	auipc	a0,0x0
   10104:	12c50513          	addi	a0,a0,300 # 1022c <__libc_fini_array>
   10108:	0dc0006f          	j	101e4 <atexit>
   1010c:	00008067          	ret

0000000000010110 <_start>:
   10110:	00002197          	auipc	gp,0x2
   10114:	d2818193          	addi	gp,gp,-728 # 11e38 <__global_pointer$>
   10118:	f6818513          	addi	a0,gp,-152 # 11da0 <_edata>
   1011c:	fc018613          	addi	a2,gp,-64 # 11df8 <__BSS_END__>
   10120:	40a60633          	sub	a2,a2,a0
   10124:	00000593          	li	a1,0
   10128:	1f4000ef          	jal	ra,1031c <memset>
   1012c:	00000517          	auipc	a0,0x0
   10130:	10050513          	addi	a0,a0,256 # 1022c <__libc_fini_array>
   10134:	0b0000ef          	jal	ra,101e4 <atexit>
   10138:	150000ef          	jal	ra,10288 <__libc_init_array>
   1013c:	00012503          	lw	a0,0(sp)
   10140:	00810593          	addi	a1,sp,8
   10144:	00000613          	li	a2,0
   10148:	f69ff0ef          	jal	ra,100b0 <main>
   1014c:	0ac0006f          	j	101f8 <exit>

0000000000010150 <__do_global_dtors_aux>:
   10150:	f781c783          	lbu	a5,-136(gp) # 11db0 <completed.5468>
   10154:	04079463          	bnez	a5,1019c <__do_global_dtors_aux+0x4c>
   10158:	ffff0797          	auipc	a5,0xffff0
   1015c:	ea878793          	addi	a5,a5,-344 # 0 <main-0x100b0>
   10160:	02078863          	beqz	a5,10190 <__do_global_dtors_aux+0x40>
   10164:	ff010113          	addi	sp,sp,-16
   10168:	00001517          	auipc	a0,0x1
   1016c:	4b050513          	addi	a0,a0,1200 # 11618 <__FRAME_END__>
   10170:	00113423          	sd	ra,8(sp)
   10174:	00000097          	auipc	ra,0x0
   10178:	000000e7          	jalr	zero # 0 <main-0x100b0>
   1017c:	00813083          	ld	ra,8(sp)
   10180:	00100793          	li	a5,1
   10184:	f6f18c23          	sb	a5,-136(gp) # 11db0 <completed.5468>
   10188:	01010113          	addi	sp,sp,16
   1018c:	00008067          	ret
   10190:	00100793          	li	a5,1
   10194:	f6f18c23          	sb	a5,-136(gp) # 11db0 <completed.5468>
   10198:	00008067          	ret
   1019c:	00008067          	ret

00000000000101a0 <frame_dummy>:
   101a0:	ffff0797          	auipc	a5,0xffff0
   101a4:	e6078793          	addi	a5,a5,-416 # 0 <main-0x100b0>
   101a8:	00078c63          	beqz	a5,101c0 <frame_dummy+0x20>
   101ac:	f8018593          	addi	a1,gp,-128 # 11db8 <object.5473>
   101b0:	00001517          	auipc	a0,0x1
   101b4:	46850513          	addi	a0,a0,1128 # 11618 <__FRAME_END__>
   101b8:	00000317          	auipc	t1,0x0
   101bc:	00000067          	jr	zero # 0 <main-0x100b0>
   101c0:	00008067          	ret

00000000000101c4 <load>:
   101c4:	00050733          	add	a4,a0,zero
   101c8:	00b50633          	add	a2,a0,a1
   101cc:	000506b3          	add	a3,a0,zero

00000000000101d0 <loop>:
   101d0:	00e68733          	add	a4,a3,a4
   101d4:	00168693          	addi	a3,a3,1
   101d8:	fec6cce3          	blt	a3,a2,101d0 <loop>
   101dc:	00070533          	add	a0,a4,zero
   101e0:	00008067          	ret

00000000000101e4 <atexit>:
   101e4:	00050593          	mv	a1,a0
   101e8:	00000693          	li	a3,0
   101ec:	00000613          	li	a2,0
   101f0:	00000513          	li	a0,0
   101f4:	2040006f          	j	103f8 <__register_exitproc>

00000000000101f8 <exit>:
   101f8:	ff010113          	addi	sp,sp,-16
   101fc:	00000593          	li	a1,0
   10200:	00813023          	sd	s0,0(sp)
   10204:	00113423          	sd	ra,8(sp)
   10208:	00050413          	mv	s0,a0
   1020c:	298000ef          	jal	ra,104a4 <__call_exitprocs>
   10210:	f4818793          	addi	a5,gp,-184 # 11d80 <_global_impure_ptr>
   10214:	0007b503          	ld	a0,0(a5)
   10218:	05853783          	ld	a5,88(a0)
   1021c:	00078463          	beqz	a5,10224 <exit+0x2c>
   10220:	000780e7          	jalr	a5
   10224:	00040513          	mv	a0,s0
   10228:	3a0000ef          	jal	ra,105c8 <_exit>

000000000001022c <__libc_fini_array>:
   1022c:	fe010113          	addi	sp,sp,-32
   10230:	00813823          	sd	s0,16(sp)
   10234:	00001797          	auipc	a5,0x1
   10238:	40478793          	addi	a5,a5,1028 # 11638 <__fini_array_end>
   1023c:	00001417          	auipc	s0,0x1
   10240:	3f440413          	addi	s0,s0,1012 # 11630 <__init_array_end>
   10244:	408787b3          	sub	a5,a5,s0
   10248:	00913423          	sd	s1,8(sp)
   1024c:	00113c23          	sd	ra,24(sp)
   10250:	4037d493          	srai	s1,a5,0x3
   10254:	02048063          	beqz	s1,10274 <__libc_fini_array+0x48>
   10258:	ff878793          	addi	a5,a5,-8
   1025c:	00878433          	add	s0,a5,s0
   10260:	00043783          	ld	a5,0(s0)
   10264:	fff48493          	addi	s1,s1,-1
   10268:	ff840413          	addi	s0,s0,-8
   1026c:	000780e7          	jalr	a5
   10270:	fe0498e3          	bnez	s1,10260 <__libc_fini_array+0x34>
   10274:	01813083          	ld	ra,24(sp)
   10278:	01013403          	ld	s0,16(sp)
   1027c:	00813483          	ld	s1,8(sp)
   10280:	02010113          	addi	sp,sp,32
   10284:	00008067          	ret

0000000000010288 <__libc_init_array>:
   10288:	fe010113          	addi	sp,sp,-32
   1028c:	00813823          	sd	s0,16(sp)
   10290:	01213023          	sd	s2,0(sp)
   10294:	00001417          	auipc	s0,0x1
   10298:	38840413          	addi	s0,s0,904 # 1161c <__preinit_array_end>
   1029c:	00001917          	auipc	s2,0x1
   102a0:	38090913          	addi	s2,s2,896 # 1161c <__preinit_array_end>
   102a4:	40890933          	sub	s2,s2,s0
   102a8:	00113c23          	sd	ra,24(sp)
   102ac:	00913423          	sd	s1,8(sp)
   102b0:	40395913          	srai	s2,s2,0x3
   102b4:	00090e63          	beqz	s2,102d0 <__libc_init_array+0x48>
   102b8:	00000493          	li	s1,0
   102bc:	00043783          	ld	a5,0(s0)
   102c0:	00148493          	addi	s1,s1,1
   102c4:	00840413          	addi	s0,s0,8
   102c8:	000780e7          	jalr	a5
   102cc:	fe9918e3          	bne	s2,s1,102bc <__libc_init_array+0x34>
   102d0:	00001417          	auipc	s0,0x1
   102d4:	35040413          	addi	s0,s0,848 # 11620 <__init_array_start>
   102d8:	00001917          	auipc	s2,0x1
   102dc:	35890913          	addi	s2,s2,856 # 11630 <__init_array_end>
   102e0:	40890933          	sub	s2,s2,s0
   102e4:	40395913          	srai	s2,s2,0x3
   102e8:	00090e63          	beqz	s2,10304 <__libc_init_array+0x7c>
   102ec:	00000493          	li	s1,0
   102f0:	00043783          	ld	a5,0(s0)
   102f4:	00148493          	addi	s1,s1,1
   102f8:	00840413          	addi	s0,s0,8
   102fc:	000780e7          	jalr	a5
   10300:	fe9918e3          	bne	s2,s1,102f0 <__libc_init_array+0x68>
   10304:	01813083          	ld	ra,24(sp)
   10308:	01013403          	ld	s0,16(sp)
   1030c:	00813483          	ld	s1,8(sp)
   10310:	00013903          	ld	s2,0(sp)
   10314:	02010113          	addi	sp,sp,32
   10318:	00008067          	ret

000000000001031c <memset>:
   1031c:	00f00313          	li	t1,15
   10320:	00050713          	mv	a4,a0
   10324:	02c37a63          	bgeu	t1,a2,10358 <memset+0x3c>
   10328:	00f77793          	andi	a5,a4,15
   1032c:	0a079063          	bnez	a5,103cc <memset+0xb0>
   10330:	06059e63          	bnez	a1,103ac <memset+0x90>
   10334:	ff067693          	andi	a3,a2,-16
   10338:	00f67613          	andi	a2,a2,15
   1033c:	00e686b3          	add	a3,a3,a4
   10340:	00b73023          	sd	a1,0(a4)
   10344:	00b73423          	sd	a1,8(a4)
   10348:	01070713          	addi	a4,a4,16
   1034c:	fed76ae3          	bltu	a4,a3,10340 <memset+0x24>
   10350:	00061463          	bnez	a2,10358 <memset+0x3c>
   10354:	00008067          	ret
   10358:	40c306b3          	sub	a3,t1,a2
   1035c:	00269693          	slli	a3,a3,0x2
   10360:	00000297          	auipc	t0,0x0
   10364:	005686b3          	add	a3,a3,t0
   10368:	00c68067          	jr	12(a3)
   1036c:	00b70723          	sb	a1,14(a4)
   10370:	00b706a3          	sb	a1,13(a4)
   10374:	00b70623          	sb	a1,12(a4)
   10378:	00b705a3          	sb	a1,11(a4)
   1037c:	00b70523          	sb	a1,10(a4)
   10380:	00b704a3          	sb	a1,9(a4)
   10384:	00b70423          	sb	a1,8(a4)
   10388:	00b703a3          	sb	a1,7(a4)
   1038c:	00b70323          	sb	a1,6(a4)
   10390:	00b702a3          	sb	a1,5(a4)
   10394:	00b70223          	sb	a1,4(a4)
   10398:	00b701a3          	sb	a1,3(a4)
   1039c:	00b70123          	sb	a1,2(a4)
   103a0:	00b700a3          	sb	a1,1(a4)
   103a4:	00b70023          	sb	a1,0(a4)
   103a8:	00008067          	ret
   103ac:	0ff5f593          	andi	a1,a1,255
   103b0:	00859693          	slli	a3,a1,0x8
   103b4:	00d5e5b3          	or	a1,a1,a3
   103b8:	01059693          	slli	a3,a1,0x10
   103bc:	00d5e5b3          	or	a1,a1,a3
   103c0:	02059693          	slli	a3,a1,0x20
   103c4:	00d5e5b3          	or	a1,a1,a3
   103c8:	f6dff06f          	j	10334 <memset+0x18>
   103cc:	00279693          	slli	a3,a5,0x2
   103d0:	00000297          	auipc	t0,0x0
   103d4:	005686b3          	add	a3,a3,t0
   103d8:	00008293          	mv	t0,ra
   103dc:	f98680e7          	jalr	-104(a3)
   103e0:	00028093          	mv	ra,t0
   103e4:	ff078793          	addi	a5,a5,-16
   103e8:	40f70733          	sub	a4,a4,a5
   103ec:	00f60633          	add	a2,a2,a5
   103f0:	f6c374e3          	bgeu	t1,a2,10358 <memset+0x3c>
   103f4:	f3dff06f          	j	10330 <memset+0x14>

00000000000103f8 <__register_exitproc>:
   103f8:	f4818793          	addi	a5,gp,-184 # 11d80 <_global_impure_ptr>
   103fc:	0007b703          	ld	a4,0(a5)
   10400:	1f873783          	ld	a5,504(a4)
   10404:	06078063          	beqz	a5,10464 <__register_exitproc+0x6c>
   10408:	0087a703          	lw	a4,8(a5)
   1040c:	01f00813          	li	a6,31
   10410:	08e84663          	blt	a6,a4,1049c <__register_exitproc+0xa4>
   10414:	02050863          	beqz	a0,10444 <__register_exitproc+0x4c>
   10418:	00371813          	slli	a6,a4,0x3
   1041c:	01078833          	add	a6,a5,a6
   10420:	10c83823          	sd	a2,272(a6)
   10424:	3107a883          	lw	a7,784(a5)
   10428:	00100613          	li	a2,1
   1042c:	00e6163b          	sllw	a2,a2,a4
   10430:	00c8e8b3          	or	a7,a7,a2
   10434:	3117a823          	sw	a7,784(a5)
   10438:	20d83823          	sd	a3,528(a6)
   1043c:	00200693          	li	a3,2
   10440:	02d50863          	beq	a0,a3,10470 <__register_exitproc+0x78>
   10444:	00270693          	addi	a3,a4,2
   10448:	00369693          	slli	a3,a3,0x3
   1044c:	0017071b          	addiw	a4,a4,1
   10450:	00e7a423          	sw	a4,8(a5)
   10454:	00d787b3          	add	a5,a5,a3
   10458:	00b7b023          	sd	a1,0(a5)
   1045c:	00000513          	li	a0,0
   10460:	00008067          	ret
   10464:	20070793          	addi	a5,a4,512
   10468:	1ef73c23          	sd	a5,504(a4)
   1046c:	f9dff06f          	j	10408 <__register_exitproc+0x10>
   10470:	3147a683          	lw	a3,788(a5)
   10474:	00000513          	li	a0,0
   10478:	00c6e633          	or	a2,a3,a2
   1047c:	00270693          	addi	a3,a4,2
   10480:	00369693          	slli	a3,a3,0x3
   10484:	0017071b          	addiw	a4,a4,1
   10488:	30c7aa23          	sw	a2,788(a5)
   1048c:	00e7a423          	sw	a4,8(a5)
   10490:	00d787b3          	add	a5,a5,a3
   10494:	00b7b023          	sd	a1,0(a5)
   10498:	00008067          	ret
   1049c:	fff00513          	li	a0,-1
   104a0:	00008067          	ret

00000000000104a4 <__call_exitprocs>:
   104a4:	fb010113          	addi	sp,sp,-80
   104a8:	f4818793          	addi	a5,gp,-184 # 11d80 <_global_impure_ptr>
   104ac:	01813023          	sd	s8,0(sp)
   104b0:	0007bc03          	ld	s8,0(a5)
   104b4:	03313423          	sd	s3,40(sp)
   104b8:	03413023          	sd	s4,32(sp)
   104bc:	01513c23          	sd	s5,24(sp)
   104c0:	01613823          	sd	s6,16(sp)
   104c4:	04113423          	sd	ra,72(sp)
   104c8:	04813023          	sd	s0,64(sp)
   104cc:	02913c23          	sd	s1,56(sp)
   104d0:	03213823          	sd	s2,48(sp)
   104d4:	01713423          	sd	s7,8(sp)
   104d8:	00050a93          	mv	s5,a0
   104dc:	00058b13          	mv	s6,a1
   104e0:	00100a13          	li	s4,1
   104e4:	fff00993          	li	s3,-1
   104e8:	1f8c3903          	ld	s2,504(s8)
   104ec:	02090863          	beqz	s2,1051c <__call_exitprocs+0x78>
   104f0:	00892483          	lw	s1,8(s2)
   104f4:	fff4841b          	addiw	s0,s1,-1
   104f8:	02044263          	bltz	s0,1051c <__call_exitprocs+0x78>
   104fc:	00349493          	slli	s1,s1,0x3
   10500:	009904b3          	add	s1,s2,s1
   10504:	040b0463          	beqz	s6,1054c <__call_exitprocs+0xa8>
   10508:	2084b783          	ld	a5,520(s1)
   1050c:	05678063          	beq	a5,s6,1054c <__call_exitprocs+0xa8>
   10510:	fff4041b          	addiw	s0,s0,-1
   10514:	ff848493          	addi	s1,s1,-8
   10518:	ff3416e3          	bne	s0,s3,10504 <__call_exitprocs+0x60>
   1051c:	04813083          	ld	ra,72(sp)
   10520:	04013403          	ld	s0,64(sp)
   10524:	03813483          	ld	s1,56(sp)
   10528:	03013903          	ld	s2,48(sp)
   1052c:	02813983          	ld	s3,40(sp)
   10530:	02013a03          	ld	s4,32(sp)
   10534:	01813a83          	ld	s5,24(sp)
   10538:	01013b03          	ld	s6,16(sp)
   1053c:	00813b83          	ld	s7,8(sp)
   10540:	00013c03          	ld	s8,0(sp)
   10544:	05010113          	addi	sp,sp,80
   10548:	00008067          	ret
   1054c:	00892783          	lw	a5,8(s2)
   10550:	0084b703          	ld	a4,8(s1)
   10554:	fff7879b          	addiw	a5,a5,-1
   10558:	04878e63          	beq	a5,s0,105b4 <__call_exitprocs+0x110>
   1055c:	0004b423          	sd	zero,8(s1)
   10560:	fa0708e3          	beqz	a4,10510 <__call_exitprocs+0x6c>
   10564:	31092783          	lw	a5,784(s2)
   10568:	008a16bb          	sllw	a3,s4,s0
   1056c:	00892b83          	lw	s7,8(s2)
   10570:	00d7f7b3          	and	a5,a5,a3
   10574:	0007879b          	sext.w	a5,a5
   10578:	00079e63          	bnez	a5,10594 <__call_exitprocs+0xf0>
   1057c:	000700e7          	jalr	a4
   10580:	00892783          	lw	a5,8(s2)
   10584:	f77792e3          	bne	a5,s7,104e8 <__call_exitprocs+0x44>
   10588:	1f8c3783          	ld	a5,504(s8)
   1058c:	f92782e3          	beq	a5,s2,10510 <__call_exitprocs+0x6c>
   10590:	f59ff06f          	j	104e8 <__call_exitprocs+0x44>
   10594:	31492783          	lw	a5,788(s2)
   10598:	1084b583          	ld	a1,264(s1)
   1059c:	00d7f7b3          	and	a5,a5,a3
   105a0:	0007879b          	sext.w	a5,a5
   105a4:	00079c63          	bnez	a5,105bc <__call_exitprocs+0x118>
   105a8:	000a8513          	mv	a0,s5
   105ac:	000700e7          	jalr	a4
   105b0:	fd1ff06f          	j	10580 <__call_exitprocs+0xdc>
   105b4:	00892423          	sw	s0,8(s2)
   105b8:	fa9ff06f          	j	10560 <__call_exitprocs+0xbc>
   105bc:	00058513          	mv	a0,a1
   105c0:	000700e7          	jalr	a4
   105c4:	fbdff06f          	j	10580 <__call_exitprocs+0xdc>

00000000000105c8 <_exit>:
   105c8:	00000593          	li	a1,0
   105cc:	00000613          	li	a2,0
   105d0:	00000693          	li	a3,0
   105d4:	00000713          	li	a4,0
   105d8:	00000793          	li	a5,0
   105dc:	05d00893          	li	a7,93
   105e0:	00000073          	ecall
   105e4:	00054463          	bltz	a0,105ec <_exit+0x24>
   105e8:	0000006f          	j	105e8 <_exit+0x20>
   105ec:	ff010113          	addi	sp,sp,-16
   105f0:	00813023          	sd	s0,0(sp)
   105f4:	00050413          	mv	s0,a0
   105f8:	00113423          	sd	ra,8(sp)
   105fc:	4080043b          	negw	s0,s0
   10600:	00c000ef          	jal	ra,1060c <__errno>
   10604:	00852023          	sw	s0,0(a0)
   10608:	0000006f          	j	10608 <_exit+0x40>

000000000001060c <__errno>:
   1060c:	f6018793          	addi	a5,gp,-160 # 11d98 <_impure_ptr>
   10610:	0007b503          	ld	a0,0(a5)
   10614:	00008067          	ret
```


# Unique Instructions


```
Number of different instructions: 35
List of unique instructions:
bne
sb
li
andi
bltu
ret
addi
negw
lw
lbu
slli
bltz
sub
jal
ld
j
blt
addiw
beq
beqz
jr
srai
auipc
bgeu
sw
bnez
or
and
sllw
ecall
mv
jalr
add
sext.w
sd
```
