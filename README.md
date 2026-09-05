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
<br>

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
Finding IR Polarity: Since the setup box wasn’t working, I couldn’t directly measure using multimeter. So I found the component responsible for stepping down which is usually kept near for EMI reduction which is shown in the picture LD1117AG ADA TBTQ. It is a Low Dropout (LDO) linear positive voltage regulator manufactured by UTC (Unisonic Technologies). I compared the connection of IR and LDO with LDO and Barrel jack Input of the circuit. Ground was common to all and the one pin of IR not showing any continuity with LDO was the signal pin hence remains the power pin.<br><br>
Using Library: Used IRremote library by Shirriff, z3t0, ArminJo (https://github.com/Arduino-IRremote/Arduino-IRremote). The library can detect numerous protocols used for communication by IR. Standard rgb light control Remote was used that uses NEC protocol. The library helped identify signal protocol and command code for each button pressed.
<br><br>

<p align="center">
  <img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/85825675-d651-4b33-a61d-652b33c40967" />
   <div align="center"><sub><i> Fig7:Finding Remote Codes</i></sub></div>
</p>   

<img width="1151" height="647" alt="image" src="https://github.com/user-attachments/assets/d9dc2a57-dcf4-4e3b-8da1-3b2cbe381aaf" />
<div align="center"><sub><i> Fig8:NEC Protocol Used by Remote</i></sub></div>
<br>
Code was adjusted so that it integrates relay, LCD and assigning buttons values with numbers and letters. Removed or commented various sections of original code that was unnecessary after I found out my remote’s protocol.

<br><br>
<p align="center"><img width="407" height="271" alt="image" src="https://github.com/user-attachments/assets/d4d0b6e5-6636-4797-a04d-b3dd1948f116" /><br><sub><i>Fig9:RGB Remote</i></sub></p>

<br><br>
<img width="1137" height="639" alt="image" src="https://github.com/user-attachments/assets/e85a53d6-4822-4038-9c3f-eef992fe7c7d" />
<p align="center"><sub><i>Fig10:Remote Button Codes</i></sub></p>

<br><br>
2 passwords declared in code one to turn relay on and other to turn off. Delay() of any value was causing timing issue hence leading to frozen response of lcd or ir. Baud rate of 115200 was utilized. Code only uploads when set back to 9600 for some reason and then turned back to 115200(I think it has something to do with CH340 chip). Millis() was used to debounce the buttons. LCD with I2C used to show the status of relay and password entered. Backlight pins connected with 220ohm resistor and also LCD was supplied with separate 5v to reduce current draw.LCD connected with separate source with gnd common for both ext src and Arduino as sda and sdl do require gnd for reference.A USB A plug was stripped and power and gnd wire connected to IR.

<br>
<table>
  <tr>
    <td><img width="484" height="537" alt="image" src="https://github.com/user-attachments/assets/af02a2fb-0a0d-416e-abf9-1060d8a96781" />
    <br>  <div  align="center"><sub><i> Fig11 :5v USB A Plug</i></sub></div>
</td>
    <td><img width="503" height="532" alt="image" src="https://github.com/user-attachments/assets/6fedf8c4-09fb-4063-ada5-4478a8048333" />
    <br>  <div  align="center"><sub><i> Fig12 :5v USB A Plug</i></sub></div>
</td>
  </tr>
</table>

Current req: relay: 70-80mA per channel to energize the coil and 2-20mA to power the IR led in optocoupler, LCD backlight: 20-50mA, Arduino can provide : 400-450mA by USB ,500-800 by barrel jack (7v-12v).IR receiver 3.3v: 0.4-1.5ma on standby and 3-5mA at peak. During switching of relay rapid current burst occurs that causes fluctuation in LCD causing dim text appearance (due to voltage drop?). To counter that capacitor can be used to be placed in parallel and delayed activation of LCD relay status indicator or in my case I used a totally separate source. 

<br><br>
<img width="939" height="473" alt="image" src="https://github.com/user-attachments/assets/cc49dec3-50eb-4cb6-98db-e3d9c6ec0849" />
<br><p align="center"> <sub><i>Fig13: Entire Setup (1)</i></sub>

<br><br>
<img width="899" height="845" alt="image" src="https://github.com/user-attachments/assets/02bcc91e-cb98-40a3-b21e-1404e57df9cc" />
<p align="center"> <sub><i>Fig14: Entire Setup (2)</i></sub></p>

<br>
<table>
  <tr>
    <td><img width="408" height="524" alt="image" src="https://github.com/user-attachments/assets/d18071ac-7596-4367-ba91-6f5cbf3032f2" />
    <br>  <div  align="center"><sub><i> Fig15 :Turning ON</i></sub></div>
</td>
    <td><img width="486" height="524" alt="image" src="https://github.com/user-attachments/assets/2d8cec62-f734-4027-ac7d-35c10ad7c8c9" />
    <br>  <div  align="center"><sub><i> Fig16 :Bulb is ON</i></sub></div>
</td>
  </tr>
</table>

<table>
  <tr>
    <td><img width="436" height="482" alt="image" src="https://github.com/user-attachments/assets/11b49db3-fb7a-4c11-9312-032ed971692e" />
    <br>  <div  align="center"><sub><i> Fig17 :Turning OFF/i></sub></div>
</td>
    <td><img width="314" height="484" alt="image" src="https://github.com/user-attachments/assets/960616f7-4c6e-49a0-8add-09f4bc18276a" />
    <br>  <div  align="center"><sub><i> Fig18 :Bulb OFF</i></sub></div>
</td>
  </tr>
</table>

<table>
  <tr>
    <td><img width="428" height="545" alt="image" src="https://github.com/user-attachments/assets/4a8e0c9b-ae96-4f0e-aa48-247b5f60e078" />
    <br>  <div  align="center"><sub><i> Fig19 :Wrong Pass Used</i></sub></div>
</td>
    <td><img width="422" height="551" alt="image" src="https://github.com/user-attachments/assets/80756c4e-f1ed-467a-874b-79aa3dae5e4d" />
    <br>  <div  align="center"><sub><i> Fig20 :"RE-ENTER" Displayed</i></sub></div>
</td>
  </tr>
</table>
Kicad Document Images:<br>
<img width="1920" height="1080" alt="Screenshot (1045)" src="https://github.com/user-attachments/assets/f31aab91-d490-4d7b-a237-f9b2ae7667f0" /><br>
<img width="1920" height="1080" alt="Screenshot (1042)" src="https://github.com/user-attachments/assets/3e7615be-17b2-481d-a9ab-83c77049d5e4" /><br>
<img width="1920" height="1080" alt="Screenshot (1044)" src="https://github.com/user-attachments/assets/c3f4e769-59ac-4daa-8c42-b0786b51d33f" /><br>
<img width="1920" height="1080" alt="Screenshot (1043)" src="https://github.com/user-attachments/assets/db02544c-3273-42e2-bcac-23bafcb9e4a7" />
<br>
WHAT I LEARNED: Serial.println(F("2")); use of F? F stores memory in Flash instead of using the 2kb SRAM (Save Dynamic Memory) in Arduino UNO and as the code prints a lot of static texts we use flash memory. Variables that change shouldn’t be placed in flash as they need to be in SRAM to be updated.
<br><br>
Flash memory is permanent memory stored in Arduino. It stores the code even when unplugged. Static Variables stored in flash using F() macro.
<br><br>
In SRAM: there is stack and heap in a single memory column. Stack stores function call names and local variables and grows downwards. Heap stores dynamically stored data and grows upward. When memory gets full (called ‘stack overflow’) they both collide into each other and try overwriting each other causing random Arduino reboots and garbage outputs.
<br><br>
Possible Updates: password using cloud/wifi; buzzer integration for audio feedback; circuit need to be made cleaner.

