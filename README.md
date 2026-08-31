# Load-Control-Using-Relay-Module-and-IR-Remote
Created a load control system in which load connected to relay module is turned ON or OFF on entering a password with IR based remote.Built on arduin UNO R3 clone using CH340 chip.
<br><br>
Compo used: IR Receiver; Arduino UNO CH340; Relay Module; Remote with IR transmitter; LCD with I2C ;Load; Jumper cables and 5v cable.
<table>
  <tr>
    <td><img width="380" height="157" alt="image" src="https://github.com/user-attachments/assets/6daa4c7e-3c34-47e4-bfc3-fbfec1d486df" />
    <br>  <div  align="center"><sub><i> Fig1:Setup Box</i></sub></div>
</td>
    <td><img width="326" height="226" alt="image" src="https://github.com/user-attachments/assets/624bda3e-3379-40f3-acac-ce911e6ff2a9" />
    <br>  <div  align="center"><sub><i> Fig2: IR receiver on Setup Box</i></sub></div>
</td>
    <td><img width="426" height="360" alt="image" src="https://github.com/user-attachments/assets/0d36f83f-b765-4129-a4b2-b47a2e7168f5" />
    <br><div align="center"><sub><i> Fig3: IR receiver Desoldered</i></sub></div>
</td>
  </tr>
</table>
IR receiver was salvaged off from old dish tv setup box . Has 3 pins with signal,gnd,power starting from left to right respectively. Required a lot of heat and flux to de-solder, ultimately leading to a pin breaking. I soldered jumper cables hastily to it and used shrink tubes. 
<table>
  <tr>
    <td><img width="399" height="278" alt="image" src="https://github.com/user-attachments/assets/92308cd2-d11e-4533-9dd2-c8667efc700e" />
    <br>  <div  align="center"><sub><i> Fig4: IR Receiver</i></sub></div>
</td>
    <td><img width="291" height="294" alt="image" src="https://github.com/user-attachments/assets/d8c8da43-6dbd-46ed-8a34-da4edca415f8" />
    <br>  <div  align="center"><sub><i> Fig5: LDO on Setup Box</i></sub></div>
</td>
    <td><img width="166" height="165" alt="image" src="https://github.com/user-attachments/assets/8fde33bf-954b-4a46-9d76-c8c9f2a2517a" />
    <br><div align="center"><sub><i> Fig6: LD1117AG ADA TBTQ</i></sub></div>
</td>
  </tr>
</table>
How the polarity was found: Since the setup box wasn’t working, I couldn’t directly measure using multimeter. So I found the component responsible for stepping down which is usually kept near for EMI reduction which is shown in the picture LD1117AG ADA TBTQ. It is a Low Dropout (LDO) linear positive voltage regulator manufactured by UTC (Unisonic Technologies). I compared the connection of IR and LDO with LDO and Barrel jack Input of the circuit. Ground was common to all and the one pin of IR not showing any continuity with LDO was the signal pin hence remains the power pin.<br><br>
USING LIBRARY: Used IRremote library by Shirriff, z3t0, ArminJo (https://github.com/Arduino-IRremote/Arduino-IRremote). The library can detect numerous protocols used for communication by IR. Standard rgb light control Remote was used that uses NEC protocol. The library helped identify signal protocol and command code for each button pressed.<br><br>
<p align="center">
  <img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/85825675-d651-4b33-a61d-652b33c40967" />
   <div align="center"><sub><i> Fig7:Finding Remote Codes</i></sub></div>
</p>   

<img width="1151" height="647" alt="image" src="https://github.com/user-attachments/assets/d9dc2a57-dcf4-4e3b-8da1-3b2cbe381aaf" />
<div align="center"><sub><i> Fig6: LD1117AG ADA TBTQ</i></sub></div>

<br><br>
Used IRremote library by Shirriff,z3t0,ArminJo (https://github.com/Arduino-IRremote/Arduino-IRremote).The library can detect numerous protocols used for communication by IR.Standard rgb light control Remote was used that uses NEC protocol.IR receiver was salvaged off from old dish tv setup box . Has 3 pins with signal,gnd,power starting from left to right respectively. The library helped identify signal protocol and command code for each button pressed. 
<br><br>
<img width="1137" height="639" alt="image" src="https://github.com/user-attachments/assets/e85a53d6-4822-4038-9c3f-eef992fe7c7d" />
<br><br>
2 passwords declared in code one to turn relay on and other to turn off. Delay() of any value was causing timing issue hence leading to frozen response of lcd or ir. Baud rate of 115200 was utilized. Code only uploads when set back to 9600 for some reason and then turned back to 115200(I think it has something to do with CH340 chip). Millis() was used to debounce the buttons. LCD with I2C used to show the status of relay and password entered. Backlight pins connected with 220ohm resistor and also LCD was supplied with separate 5v to reduce current draw.LCD connected with separate source with gnd common for both ext src and Arduino as sda and sdl do require gnd for reference.
<br><br>
Current req: relay: 70-80mA per channel to energize the coil and 2-20mA to power the IR led in optocoupler, LCD backlight: 20-50mA, Arduino can provide : 400-450mA by USB ,500-800 by barrel jack (7v-12v).IR receiver 3.3v: 0.4-1.5ma on standby and 3-5mA at peak. During switching of relay rapid current burst occurs that causes fluctuation in LCD causing dim text appearance (due to voltage drop?). To counter that capacitor can be used to be placed in parallel and delayed activation of LCD relay status indicator or in my case I used a totally separate source. 


