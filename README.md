# RISC-V Instruction Format Converter

This project demonstrates a bidirectional conversion pipeline between YAML instruction definitions and C header files for RISC-V instructions. It addresses the challenge of maintaining consistent instruction definitions across different formats.

## Project Overview

The project implements a complete cycle of conversion:
1. Python script reads RISC-V instruction data from YAML files
2. Converts the data to a C header file with a structured representation
3. C program reads the header file and generates a new YAML file
4. The cycle can be repeated to verify consistency

## Files Structure

- `header-cov.py`: Python script that reads YAML instruction definitions and generates C header files
- `emit_yaml.c`: C program that reads the generated header file and emits YAML
- `xnor.yaml`: Sample RISC-V instruction definition (from the RISC-V Unified Database)
- `instruction.h`: Generated C header file containing the instruction data
- `generated.yaml`: YAML file generated from the C program
- `emitted-yaml-check/`: Directory containing verification tools
  - `header-cov-check.py`: Enhanced Python script that handles both nested and flat YAML structures
  - `emit_yaml_check.c`: C program for verification
  - `compare.yaml`: Reference YAML file with correct binary representation

## Requirements

- Python 3.x with PyYAML package (`pip install pyyaml`)
- C compiler (gcc or clang)

## Usage

### Step 1: Generate C header from YAML

```bash
python header-cov.py
```

This reads `xnor.yaml` and generates `instruction.h`.

### Step 2: Generate YAML from C header

```bash
gcc -o emit_yaml emit_yaml.c
./emit_yaml
```

This compiles and runs the C program, which reads `instruction.h` and generates `generated.yaml`.

### Step 3: Verification

```bash
cd emitted-yaml-check
python header-cov-check.py
gcc -o emit_yaml_check emit_yaml_check.c
./emit_yaml_check
```

This verifies the round-trip conversion by:
1. Reading `compare.yaml` (or `generated.yaml`)
2. Generating a new header file
3. Converting back to YAML (`final.yaml`)
4. Comparing the results

## Key Features

- **Robust YAML parsing**: Handles both nested and flat YAML structures
- **Binary value preservation**: Properly maintains binary representations (e.g., `0b0100000`)
- **Format conversion**: Demonstrates bidirectional conversion between different representation formats
- **Error handling**: Includes comprehensive error checking for file operations and parsing

## Technical Details

### YAML Structure

The YAML files represent RISC-V instructions with fields like:
- `name`: Short instruction name
- `long_name`: Full instruction name
- `assembly`: Assembly syntax
- `description`: Detailed description
- `funct7`, `funct3`, `opcode`: Binary encoding fields

### C Representation

The C header defines a struct to hold the instruction data:

```c
typedef struct {
    const char* name;
    const char* long_name;
    const char* assembly;
    const char* description;
    const char* funct7;
    const char* funct3;
    const char* opcode;
} RiscVInstruction;
```

## Challenges Addressed

- **Binary representation**: Preserving binary values (e.g., `0b0100000`) across formats
- **Structure conversion**: Converting between nested YAML and flat C structures
- **Format consistency**: Ensuring the round-trip conversion produces consistent results


