# RISC_V-SECURITY_ALARM_SYSTEM


In this project, we are going to design Laser Light Security System Using RISCV with Alarm with the application of Laser Diode Module KY-008. The project idea revolves around creating a security system. Whenever any object will obstruct the LASER ray the buzzer alarm will start ringing.

This project can be implemented anywhere, not only buildings or premises but many precious things like jewelry, diamonds, precious antique items in the museum, etc many other things are also secured using such an invisible LASER beam. Many people secure their home, office, shops, warehouses, etc with the LASER beam security system.


# Circuit Diagram
![alarmsystem](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/ce64a096-e601-49e6-afb8-408ac385ec39)

# Block Diagram

![Slide2](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/d22ac893-b6ab-48b0-aba6-9a505f05f88d)


# Working Principle

The project basically works on the principle of interruption. If by any means the LASER light is interrupted the alarm will start unless it is reset with push-button. The laser is a concentrated light source that puts out a straight beam of light of a single color

The LDR is sensitive to light and puts out a voltage when the laser light hits it. When the laser beam is interrupted and can’t reach LDR, its voltage output changes, and eventually the alarm will ring


# C Code 

```
int main() 
{

	
 int laserPin;
 int laserPin_reg;
 int sensorPin=0;
 int buttonPin=1;
 int buzzerPin=0;
 int buzzerPin_reg;
 int alarmState = 0;

   
    while (1) 
    {
        switch (alarmState) 
        {
            case 0:
                
                    laserPin = 1;
                    laserPin_reg=laserPin*4;
                    
                    asm volatile(
			"or x30, x30, %0\n\t"
			: 
			:"r"(laserPin_reg)//right end
			:"x30"
			);
               
                    asm volatile(
			"andi %0, x30, 0x01\n\t"
			:"=r"(sensorPin)
			:
			);
                    if (!sensorPin) 
                    {
                        alarmState = 1;
                        buzzerPin=1;
                        buzzerPin_reg=buzzerPin*8;
                       asm volatile(
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg)
                    	:"x30"
                    	);
                    }
                    
                            
                
                break;
            
            case 1:
            	
            	

               asm volatile(
			"andi %0, x30, 0x02\n\t"
			: "=r" (buttonPin)
			:
			:);
                if (!buttonPin) 
                {
                    alarmState = 0;
                    buzzerPin=0;
                    buzzerPin_reg = buzzerPin*8;
                    
                    asm volatile(
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg)
                    	:"x30"
                    	);
                    
                    
                }
                break;
        }
    }
}
```






# Assembly Code

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	fe042423          	sw	zero,-24(s0)
   10064:	00100793          	li	a5,1
   10068:	fef42223          	sw	a5,-28(s0)
   1006c:	fe042023          	sw	zero,-32(s0)
   10070:	fe042623          	sw	zero,-20(s0)
   10074:	fec42783          	lw	a5,-20(s0)
   10078:	00078a63          	beqz	a5,1008c <main+0x38>
   1007c:	fec42703          	lw	a4,-20(s0)
   10080:	00100793          	li	a5,1
   10084:	04f70e63          	beq	a4,a5,100e0 <main+0x8c>
   10088:	fedff06f          	j	10074 <main+0x20>
   1008c:	00100793          	li	a5,1
   10090:	fcf42e23          	sw	a5,-36(s0)
   10094:	fdc42783          	lw	a5,-36(s0)
   10098:	00279793          	slli	a5,a5,0x2
   1009c:	fcf42c23          	sw	a5,-40(s0)
   100a0:	fd842783          	lw	a5,-40(s0)
   100a4:	00ff6f33          	or	t5,t5,a5
   100a8:	001f7793          	andi	a5,t5,1
   100ac:	fef42423          	sw	a5,-24(s0)
   100b0:	fe842783          	lw	a5,-24(s0)
   100b4:	04079e63          	bnez	a5,10110 <main+0xbc>
   100b8:	00100793          	li	a5,1
   100bc:	fef42623          	sw	a5,-20(s0)
   100c0:	00100793          	li	a5,1
   100c4:	fef42023          	sw	a5,-32(s0)
   100c8:	fe042783          	lw	a5,-32(s0)
   100cc:	00379793          	slli	a5,a5,0x3
   100d0:	fcf42a23          	sw	a5,-44(s0)
   100d4:	fd442783          	lw	a5,-44(s0)
   100d8:	00ff6f33          	or	t5,t5,a5
   100dc:	0340006f          	j	10110 <main+0xbc>
   100e0:	002f7793          	andi	a5,t5,2
   100e4:	fef42223          	sw	a5,-28(s0)
   100e8:	fe442783          	lw	a5,-28(s0)
   100ec:	02079663          	bnez	a5,10118 <main+0xc4>
   100f0:	fe042623          	sw	zero,-20(s0)
   100f4:	fe042023          	sw	zero,-32(s0)
   100f8:	fe042783          	lw	a5,-32(s0)
   100fc:	00379793          	slli	a5,a5,0x3
   10100:	fcf42a23          	sw	a5,-44(s0)
   10104:	fd442783          	lw	a5,-44(s0)
   10108:	00ff6f33          	or	t5,t5,a5
   1010c:	00c0006f          	j	10118 <main+0xc4>
   10110:	00000013          	nop
   10114:	f61ff06f          	j	10074 <main+0x20>
   10118:	00000013          	nop
   1011c:	f59ff06f          	j	10074 <main+0x20>
```


# Unique Instructions

```
Number of different instructions: 12
List of unique instructions:
beq
or
nop
li
j
and
sll
add
bnez
lw
sw
beqz


```



## Acknowledgements
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Chatgpt
- Emil Jayanth Lal,Colleague,IIIT B
- Shant Rakshit,Colleague,IIIT B
- Mayank Kabra,imtech

 ## Reference 
- https://github.com/SakethGajawada/RISCV-GNU
