# Truth table for controller outputs

The truth table is based on the controller's LEDs and the machine's electrical circuit.  

The factory installed controller is Mitsubishi FX2N-48MT (block A01).  
Wiring diagram for machine with serial number 525075-38-05.

## List of outputs 

|Pin of FX2N|Use|Pin of Relay module|Comment|
|:-:|-|:-:|-|
|0|"WASH ON" light|-|*disconnected*|
|1|*not used*|-|
|2|*not used*|-|
|3|wash valve|
|4|heating tank 1 (wash)|
|5|heating tank 2 (rinse)|
|6|hot air|
|7|rinse valve|
|8|*not used*|-|
|9|*not used*|-|
|10|spray pomp tank 1 (wash)|
|11|spray pomp tank 2 (rinse)|
|12|filtration pump tank 2 (rinse)|
|13|spray agitation motor down|
|14|spray agitation motor up|
|15|hot air blower|
|16|drayn valve control (tank 2)|
|17|safety door lock open|
|18|*not used*|-|
|19|*not used*|-|
|20|drain valve tank 1 (wash)|
|21|drain valve tank 2 (rinse)|
|22|ventilation open|
|23|air blast for pipes|
|24|filtration pump tank 1 (wash)|
|25|light tower - green|
|26|light tower - white|
|27|light tower - red|

## Modes

*"WASH ON" light is on forever, so I disconnect it and didn't include in following lists.*  

*White light on light tower is on *

### Stand by
Active:
- drain valve tank 2 (rinse)
- ventilation open
- light tower - green
- light tower - white

*FX2N: 21, 22, 25, 26.*
**ARM:**

### Wash
Active:
- wash valve
- heating tank 1 (wash)
- heating tank 2 (rinse)
- spray pomp tank 1 (wash)
- filtration pump tank 2 (rinse)
- spray agitation motor down (pulse mode)
- spray agitation motor up (pulse mode)
- safety door lock open
- drain valve tank 1 (wash)
- filtration pump tank 1 (wash)
- light tower - green
- light tower - white
