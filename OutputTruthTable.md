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
|3|wash valve|K1 on|connected to spray pomp (tank 1, wash)|
|4|heating (tank 1, wash)|K3 on|connected to heating (tank 2, rinse)|
|5|heating (tank 2, rinse)|K3 on|connected to heating (tank 1, wash)|
|6|hot air|
|7|rinse valve|K2 on|connected to spray pomp (tank 2, rinse)|
|8|*not used*|-|
|9|*not used*|-|
|10|spray pomp (tank 1, wash)|K1 on|connected to wash valve|
|11|spray pomp (tank 2, rinse)|K2 on|connected to rinse valve|
|12|filtration pump (tank 2, rinse)|
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
|27|light tower - red||for error message|

## Pins active (FX2N)

|Mode             | 0| 3| 4| 5| 6| 7|10|11|12|13|14|15|16|17|20|21|22|23|24|25|26|
|-                | -| -| -| -| -| -| -| -| -| -| -| -| -| -| -| -| -| -| -| -| -|
|**After on**     | x|  |  |  |  |  |  |  |  |  |  |  |  |  |  | x| x|  |  | x| x|
|**Stand by**     | x|  |  |  |  |  |  |  | x|  |  |  |  |  |  | x| x|  | x| x| x|
|**Wash**         | x| x| x| x|  |  | x|  | x| p| p|  |  | x| x|  |  |  | x| x| x|
|**Air blast**    | x|  | x| x|  |  |  |  | x|  |  |  | x| x| x|  | x| x| x| x| x|
|**Drip (tank 1)**| x|  | x| x|  |  |  |  | x|  |  |  |  | x| x|  | x|  | x| x| x|
|**Rinse**        | x|  | x| x|  | x|  | x| x| p| p|  |  | x|  | x|  |  | x| x| x|
|**Air blast**    | x|  | x| x|  |  |  |  | x|  |  |  | x| x|  | x| x| x| x| x| x|
|**Drip (tank 2)**| x|  | x| x|  |  |  |  | x|  |  |  |  | x|  | x| x|  | x| x| x|
|**Air blow**     | x|  |  |  | x|  |  |  | x| p| p| x| x| x|  | x| x| x| x| x| x|
|**Drying**       | x|  |  |  | x|  |  |  | x|  |  | x| x| x|  | x| x|  | x| x| x|
