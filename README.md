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

	
 
 int sensorPin;
 int buttonPin;
	
 int laserPin=1;
 int laserPin_reg;
 
 int buzzerPin=0;
 int buzzerPin_reg;

 int alarmState = 0;
 int mask1 = 0xFFFFFFFB;
 int mask2 = 0xFFFFFFF7;
   
    while (1) 
    {
        switch (alarmState) 
        {
            case 0:
                
                    laserPin = 1;
                    laserPin_reg=laserPin*4;
                    
                    asm volatile(
                    	"and x30,x30, %1\n\t"
			"or x30, x30, %0\n\t"
			: 
			:"r"(laserPin_reg),"r"(mask1)//right end
			:"x30"
			);
               
                    asm volatile(
			"andi %0, x30, 0x01\n\t"
			:"=r"(sensorPin)
			:
			:
			);
                    if (sensorPin==0) 
                    {
                        alarmState = 1;
                        buzzerPin=1;
                        buzzerPin_reg=buzzerPin*8;
                       asm volatile(
                       	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    }
                     else
                    {
                    buzzerPin=0;
                        buzzerPin_reg=buzzerPin*8;
                       asm volatile(
                       	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    	
                    }
                            
                
                break;
            
            case 1:
            	
            	

               asm volatile(
			"andi %0, x30, 0x02\n\t"
			: "=r" (buttonPin)
			:
			:
			);
                if (buttonPin) 
                {
                    alarmState = 0;
                    buzzerPin=0;
                    buzzerPin_reg = buzzerPin*8;
                    
                    asm volatile(
                    	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    
                    
                }
                
                 else //buttonpin = 0 in the start
                {
                	
                    alarmState = 1;
                    buzzerPin=1;
                    buzzerPin_reg = buzzerPin*8;
                    
                    asm volatile(
                    	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    	
                    	
                    	
                }
                break;
        }
    }
}
```


# Spike Results

```
x30[3:0] --> GPIO pins 
x30[0] --> sensor pin (detects the object[0 or1])
x30[1] --> button pin (turns the buzzer on or off)
x30[2] --> laser pin (always on)
x30[3] --> buzzer pin (goes on when sensorpin = 0 / goes off when sensorpin = 1)
```



```
input x30[1:0] -->01  output x30[3:2] --> 01 -->masked output -->1000
input x30[1:0] -->00  output x30[3:2] --> 11 -->masked output -->1100
input x30[1:0] -->10  output x30[3:2] --> 11 -->masked output -->1100
```

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out test2.c 
spike pk out
```

Here the alarmstate is initially set to zero and the laser is always turned on.Now the sensor is set to zero(sensorPin=0) which denotes some object is detected.Now the alarmstate is set to 1and the buzzer is turned on.Then it checks for the buttonPin.here the buttonPin is 1 which makes the buzzer go off and the alarmstate is set to zero(alarmstate=0).

![spike1](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/57848571-2f8f-4985-a2ae-e0767a664eef)


Now the sensor is set to one (sensorPin=1) no object is detected the buzzer remains off.Here it does not check for the button pin.

![spike2](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/e13a09d4-6f6b-4328-b32a-a711cabe468d)






# Assembly Code


code conversion:

```
riscv64-unknown-elf -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o out alar1.c
riscv64-unknown-elf-objdump -d -r out > asm.txt
```

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fc010113          	addi	sp,sp,-64
   10058:	02812e23          	sw	s0,60(sp)
   1005c:	04010413          	addi	s0,sp,64
   10060:	00100793          	li	a5,1
   10064:	fef42423          	sw	a5,-24(s0)
   10068:	fe042223          	sw	zero,-28(s0)
   1006c:	fe042623          	sw	zero,-20(s0)
   10070:	ffb00793          	li	a5,-5
   10074:	fef42023          	sw	a5,-32(s0)
   10078:	ff700793          	li	a5,-9
   1007c:	fcf42e23          	sw	a5,-36(s0)
   10080:	fec42783          	lw	a5,-20(s0)
   10084:	00078a63          	beqz	a5,10098 <main+0x44>
   10088:	fec42703          	lw	a4,-20(s0)
   1008c:	00100793          	li	a5,1
   10090:	08f70863          	beq	a4,a5,10120 <main+0xcc>
   10094:	fedff06f          	j	10080 <main+0x2c>
   10098:	00100793          	li	a5,1
   1009c:	fef42423          	sw	a5,-24(s0)
   100a0:	fe842783          	lw	a5,-24(s0)
   100a4:	00279793          	slli	a5,a5,0x2
   100a8:	fcf42c23          	sw	a5,-40(s0)
   100ac:	fd842783          	lw	a5,-40(s0)
   100b0:	fe042703          	lw	a4,-32(s0)
   100b4:	00ef7f33          	and	t5,t5,a4
   100b8:	00ff6f33          	or	t5,t5,a5
   100bc:	001f7793          	andi	a5,t5,1
   100c0:	fcf42a23          	sw	a5,-44(s0)
   100c4:	fd442783          	lw	a5,-44(s0)
   100c8:	02079a63          	bnez	a5,100fc <main+0xa8>
   100cc:	00100793          	li	a5,1
   100d0:	fef42623          	sw	a5,-20(s0)
   100d4:	00100793          	li	a5,1
   100d8:	fef42223          	sw	a5,-28(s0)
   100dc:	fe442783          	lw	a5,-28(s0)
   100e0:	00379793          	slli	a5,a5,0x3
   100e4:	fcf42823          	sw	a5,-48(s0)
   100e8:	fd042783          	lw	a5,-48(s0)
   100ec:	fdc42703          	lw	a4,-36(s0)
   100f0:	00ef7f33          	and	t5,t5,a4
   100f4:	00ff6f33          	or	t5,t5,a5
   100f8:	0900006f          	j	10188 <main+0x134>
   100fc:	fe042223          	sw	zero,-28(s0)
   10100:	fe442783          	lw	a5,-28(s0)
   10104:	00379793          	slli	a5,a5,0x3
   10108:	fcf42823          	sw	a5,-48(s0)
   1010c:	fd042783          	lw	a5,-48(s0)
   10110:	fdc42703          	lw	a4,-36(s0)
   10114:	00ef7f33          	and	t5,t5,a4
   10118:	00ff6f33          	or	t5,t5,a5
   1011c:	06c0006f          	j	10188 <main+0x134>
   10120:	002f7793          	andi	a5,t5,2
   10124:	fcf42623          	sw	a5,-52(s0)
   10128:	fcc42783          	lw	a5,-52(s0)
   1012c:	02078663          	beqz	a5,10158 <main+0x104>
   10130:	fe042623          	sw	zero,-20(s0)
   10134:	fe042223          	sw	zero,-28(s0)
   10138:	fe442783          	lw	a5,-28(s0)
   1013c:	00379793          	slli	a5,a5,0x3
   10140:	fcf42823          	sw	a5,-48(s0)
   10144:	fd042783          	lw	a5,-48(s0)
   10148:	fdc42703          	lw	a4,-36(s0)
   1014c:	00ef7f33          	and	t5,t5,a4
   10150:	00ff6f33          	or	t5,t5,a5
   10154:	0300006f          	j	10184 <main+0x130>
   10158:	00100793          	li	a5,1
   1015c:	fef42623          	sw	a5,-20(s0)
   10160:	00100793          	li	a5,1
   10164:	fef42223          	sw	a5,-28(s0)
   10168:	fe442783          	lw	a5,-28(s0)
   1016c:	00379793          	slli	a5,a5,0x3
   10170:	fcf42823          	sw	a5,-48(s0)
   10174:	fd042783          	lw	a5,-48(s0)
   10178:	fdc42703          	lw	a4,-36(s0)
   1017c:	00ef7f33          	and	t5,t5,a4
   10180:	00ff6f33          	or	t5,t5,a5
   10184:	00000013          	nop
   10188:	ef9ff06f          	j	10080 <main+0x2c>
```



# Unique Instructions

```
Number of different instructions: 13
List of unique instructions:
lw
slli
j
andi
beqz
nop
and
sw
or
addi
beq
bnez
li



```




# Functional Verification on using GTKWave Simulation
Here we  will verify all the outputs with waveform for all the possible input combinations.
```
x30[0] --> sensor pin 
x30[1] --> button pin 
x30[2] --> laser pin 
x30[3] --> buzzer pin
```

In the below image you can see the input_wires[1:0]={buttonPin,sensorPin} and output_wires[1:0]={buzzerPin,laserPin(always high)}.

In the first case the ```input_wires-->00``` As explained earlier buzzer goes on when sensorPin is low, ```output_wires-->11``` .Now only buzzer goes off when button pin goes high.You can clearly see that ```input_wires-->01``` Eventhough sensorPin is high buzzer is still on.

![Fvcase1](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/241695b8-688d-4db0-ade5-e566c8c0166b)


Now in the next case ```input_wires-->10``` .Here the sensorPin is low first and then buttonPin is high. So the buzzer goes on first and once the buttonPin is high it goes off.We can infer from the waveform the output keeps changing ```output_wires-->11-->01-->11--01-->.....```



![FVcase2](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/fd708af4-32aa-48e0-8bfc-a65c8be1fb0f)

Now the case is ```input_wires-->11```.Since the sensorPin and buttonPin is high the buzzer will be off```output_wires-->01```.



![Fvcase3](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/fbef93dc-675d-4d54-9801-230655bb15f5)


# Instruction Verification

Here the instruction in the assembly code is tested and verified by using gtkwave. 

The first instruction is ``` 10054:	fc010113          	addi	sp,sp,-64``` .Previously sp(Signal43) was ```000000FF``` after subtracting by 64 sp is```0000000BF```

![ins_ver](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/56d81b4a-9ca5-4419-977f-4b5517430d4c)

The next instruction with immediate value operation is ```   10060:	00100793          	li	a5,1``` Here the register a5(Signal58) is loaded with 1.

![ins_ver2](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/5149112f-5c91-47bd-bee3-dab514e6284f







# Gate Level Synthesis

It is the process of converting the high-level description into an RTL representation that defines the functional blocks, interconnections, and register transfers within the design. This representation is often in the form of a hardware netlist, which is a list of interconnected logic elements. During synthesis, various optimization techniques are applied to improve the design's performance, power efficiency, and area utilization.
The conversion of RTL in terms of the standard cells gates available in the .lib.



```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog synth_processor_test.v

```
Folllowing are the commands to run the GLS simulation:

```
iverilog -o test synth_processor_test.v testbench.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v

```

## Case1


![Screenshot from 2023-11-02 17-40-56](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/b5afa5a2-ebe3-4299-af07-743e2a4fd48e)

## Case2 
![Screenshot from 2023-11-02 17-40-11](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/36f01394-1544-407f-83c0-88c0095b61bf)

## Case3
![Screenshot from 2023-11-02 17-39-04](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/d8fbf72b-3401-45a5-a97b-f3aeccdf504a)

## Case4
![Screenshot from 2023-11-02 17-38-06](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/4f95f60f-e97d-4609-a1aa-f8c8ab7f8fd3)


# PNR flow

The PNR (Place and Route) flow is a crucial aspect of ASIC (Application-Specific Integrated Circuit) design, encompassing a series of stages that involve placing the electronic components on the chip and establishing the interconnections between them. In the context of Openlane, this flow integrates various open-source tools to facilitate the efficient execution of each step in the Place and Route process.

### Synthesis:
Generation of gate-level netlist: Yosys is employed to produce the gate-level netlist.
Cell mapping: ABC is utilized for the mapping of cells.
Pre-layout Static Timing Analysis (STA): OpenSTA is applied for pre-layout static timing analysis.

### Floorplanning:
Definition of core area, cell sites, and tracks: Init_fp is responsible for establishing the core area for the macro, cell sites, and tracks.
Placement of macro ports: Ioplacer is used to position the input and output ports of the macro.
Power distribution network generation: Pdn is tasked with generating the power distribution network.

### Placement:
Global placement: RePLace is implemented for the initial global placement.
Detailed placement: OpenDP is enlisted for detailed placement to regularize the globally placed components.

### Clock Tree Synthesis (CTS):
Clock tree synthesis: TritonCTS is employed for synthesizing the clock tree.

### Routing:
Global routing: FastRoute is utilized for global routing, generating a guide file for the detailed router.
Detailed routing: TritonRoute is applied for the intricate process of detailed routing.

### GDSII Generation:
Creation of the final GDSII layout file: Magic is used to stream out the conclusive GDSII layout file from the routed DEF file.

# Design Flow
Preparing the design and including the lef files: The commands to prepare the design and overwite in a existing run folder the reports and results along with the command to include the lef files is given below:
 
``` sed -i's/max_transition   :0.04/max_transition   :0.75'*/*.lib ```


```
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project 

```


![flow1](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/d5d6dc57-cec2-491f-9d5c-16699e7688e9)


### Synthesis


![RS](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/c1ded1cc-b68f-466d-bdbf-f8f05ce7942d)



Synthesis Report

![synt_stat](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/906e1793-6a39-42d7-a26a-cd19490c0701)


### Floorplan

![FP](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/d1e847a0-b312-48ab-a56c-3ab10e1bd7df)


### Die Area(post floorplan)

![FP_die_area](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/2b061f33-9031-4f5b-bd5c-9aa1255749bb)



### Core Area(post floorplan)

![FP_core_area](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/ce4d69df-9369-428e-a844-6a51505954cd)



### Placement 

![run_placement](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/4c4c9093-eefc-4a1a-a77d-cf69b19faaae)


### Clock tree synthesis


### Timing report

### Area report 

### Skew report 

### Power report


### Routing


![run_routing](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/525e177f-653a-4801-b836-22f37661f17b)


### Post routing Timing Report
### Post routing Area Report
### Post routing Power Report
### Design Rule Check(DRC)


### Additional steps



## Acknowledgements
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Chatgpt
- Alwin Shaju,Colleague,IIIT B
- Emil Jayanth Lal,Colleague,IIIT B
- Shant Rakshit,Colleague,IIIT B
- Mayank Kabra,imtech

 ## Reference 
- https://github.com/SakethGajawada/RISCV-GNU
