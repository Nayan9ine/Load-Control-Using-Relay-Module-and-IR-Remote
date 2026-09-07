MADE ARDUINO SHIELD FOR LOAD CONTROL which has relay module IR receiver and LCD display embedded on it with a pot to control brightness.<br><br>
->Learnt how to adjust arduino shield boundary layer to fit in components.<br><br>
->How to use VIAS,Net Labels, Power FLags<br><br>
->power GND symbols act as global labels so symbols with same name so get connected electrically. <br><br>
->re matching pin reference numbers to their footprints<br><br>
->Arduino sheild template was used, the entire boundary was fixed in one place.Was unable to expand the area to put my components in. Learnt about the "locked" feature and disabled it by using Appearance tab and Selection Filter.  <br><br>
->used fillet lines to round up sharp wire edges.<br><br>
->to draw board outline: appearance->layers->Edge.Cuts -> choose drawing line or shape etc.<br><br>
->changing sda/scl pins from digital to analog side in order for better routing<br><br>
->using analog pin as digital for IR receiver for better routing<br><br>
-> can keep signal traces (i2c scl sda) thin but keep them away from high freq signals (buck converter)
or relay module as they create heavy EMI. Never run them parallel to relay lines, cross only at 90 degrees to relay lines)<br><br>
->signal lines: 0.2mm Power lines:0.4mm GND lines: 0.6mm<br><br>
Appropriate Components Found:<br><br>
-> RELAY MODULE DESIGN EXTRACTED from: (https://github.com/ampnics/Relay-Module-HW-Design) when copy-pasted from original schematic the resulting pcb desin was jumbled up so directly copy-pasted PCB design and chenaged the reference name to match the schematic so duplicate relay components won't be created again. <br><br>  
->The LCD I2C component I was able to find (EA T123X-I2C)  was different than what was used in the project. It needed 2 4.7k Ohm pull up resistors for SDA,SCL. Has 2 additional pins for adjusting display contrast (Vo and Vlcd). The contrast was controlled by a potentiometer with Vlcd connected to gnd and 3rd pin of pot. 2nd pin to Vo and 1st to Vdd (5v).
<br><br>
->Added 2 pwr flags on Vo and Vdd as kicad ERC was throwing "input power pins not connected to source" error.<br><br>
->made several connections using NET LABELS to avoid messy wiring.<br><br>
->added no connect flags on pins not being used.<br><br>
-> Mounting holes added to show LCD external 5V supply and AC load connection to relay thorugh a LAMP symbol.<br><br>
->Since GND pins in arduino shield are assumed to be internally connected, KiCad ERC throws "No connection" error and DRC shows unecessary ratnets. So I had to change the name of various GND symbols and some labelled as No Connect.<br><br>
->For smd resistors only traces in front can get connected so used vias to turn back trace into front then connect to smd.
