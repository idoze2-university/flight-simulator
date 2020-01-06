# EX3
This project was written as part of the Advanced Programming 1 Course (89210), BIU.

## Dependencies
- [Flight Gear](https://www.flightgear.org/)
- g++
```bash
sudo apt install g++
```

<b>Optional:</b>
```bash
sudo apt install make
```
## Usage:
Edit fly.txt (default is Project_Data/fly.txt) to run a script, make sure the syntax is as defined in the exercise, 

## Makefile usage (Recommended for testing)
Note: must be used on a unix machine.
```bash
make <APP> (OPTIONAL: File=<Fly.txt Path> )
```
Default file is fly.txt located in this repo.
<b>Available apps:</b>
- lexer
- parser
- main

<b>To compile-only any app:<\b>
 ```bash
 make <APP>.out 
 ```

### Additional Makefile Commands
<b>run the simulator:</b>

(note, you have you have flightgear installed for this)

Edit your path in the make, or use with argument FG_PATH=<PATH>.

```bash
make run_simulator <optionally FG_PATH>
```
optionally, you can run a minimalised version of the simulator, with flags specified in Project_Data/flags_mini.txt:
```bash
make run_simulator_mini <optionally FG_PATH>
```

<b>copy generic.xml file to the required flightgear folder.</b>
```bash
make copy_protocol <optionally FG_PATH>
```

<b>compile main (everything), run full gui simulator and run main parallelly:</b>
```bash
make run
```
BIU © [Ido Zeira](github.com/idoze2), [Allen Bronshtein](github.com/allenbronshtein)
