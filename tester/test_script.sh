#!/bin/bash

# Variables
MAKE_CMD="make"        # Make command
TARGET="../minishell"    # Output binary file
INPUTS_FILE="inputs.txt"
EXPECTED_OUTPUTS_FILE="expected_outputs.txt"
OUTPUTS_FILE="outputs.txt" # Single file for output
DELIMITER="---"
TEST_COUNT=115


# Remove the outputs file if it exists
rm -f $OUTPUTS_FILE

# Change to the parent directory to run the Make command
cd ..

# Compile the C program using Makefile
$MAKE_CMD

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Compilation successful."

# Change back to the test_data directory
cd -

# Execute the program with different inputs and compare the output
for i in $(seq 1 $TEST_COUNT); do
    input=$(awk -v n=$i -v delim="$DELIMITER" 'BEGIN { RS = delim } NR == n { print }' $INPUTS_FILE)
    expected_output=$(awk -v n=$i -v delim="$DELIMITER" 'BEGIN { RS = delim } NR == n { print }' $EXPECTED_OUTPUTS_FILE)

    output=$(echo "$input" | $TARGET)
    echo "$output" >> $OUTPUTS_FILE

    # Add delimiter if not the last test case
    if [ $i -lt $TEST_COUNT ]; then
        echo "$DELIMITER" >> $OUTPUTS_FILE
    fi

    # Compare expected_output and output using diff while ignoring whitespace differences and blank lines
    diff_output=$(diff -Z -B -y --suppress-common-lines <(echo "$expected_output") <(echo "$output"))

    if [ -n "$diff_output" ]; then
        echo "Test ${i} failed."
        echo "Differences:"
        echo "$diff_output"
    else
        echo "Test ${i} passed."
    fi
done