# EX3
This project was written as part of the Advanced Programming 1 Course (89210), BIU.
## Dependencies
- g++
```bash
sudo apt install g++
```
- [Flight Gear](https://www.flightgear.org/)


<b>Optional: </b>
```bash
sudo apt install make
```
## Usage:
Edit fly.txt (default is Project_Data/fly.txt)

## Makefile usage (Recommended for testing)
```bash
make <COMMAND>_<APP> File=<Fly.txt Path>
```
(To use the default fly.txt, you can ignore the File=... part.)

<b>Available Commands:</b>
- compile
- run
- test (run & compile)

<b>Available apps:</b>
- lexer
- parser
- main

### Additional Makefile Commands
<b>run the simulator:</b>

(note, you have you have flightgear installed for this)

Edit your path in the makefile, or use with argument FG_PATH=<PATH>

```bash
make run_simulator <optionally FG_PATH>
```
optionally, you can run a minimalised version of the simulator, with flags specified in flags_mini.txt:

```bash
make run_simulator_mini <optionally FG_PATH>
```
<b>copy generic.xml file to the required flightgear folder.</b>

```bash
make copy_protocol <optionally FG_PATH>
```

<b>compile main (everything), run full gui simulator and run main parallelly:</b>

(note, this is heavy.)

```bash
make run
```
MIT © [Ido Zeira](github.com/idoze2), [Allen Bronshtein](github.com/allenbronshtein)
