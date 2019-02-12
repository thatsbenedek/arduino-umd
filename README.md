# arduino-umd

Making a broadcast UMD (Under Monitor Display) more useful in everyday life using a WiFi capable microcontroller (NodeMCU 1.0).

The UMD uses RS485 for receiving data, the microcontroller has TTL serial levels. To convert TTL levels to RS485 (as the UMD only receives data) you'll need a level adapter IC (such as the SN75176).

## Harris protocol

UMD-s are capable of displaying a limited set of characters. They use a special protocol to display text data correctly, this is Harris Protocol, which has the following elements:

**%[address of UMD]D** + **string to display** + **%Z**

* opening section: containing the address of the UMD
* middle section: actual text to displaying
* closing section: indicating end of the data sent

For example the string "%0Dtext%Z" will display "text" on the UMD which has the address of 0.
