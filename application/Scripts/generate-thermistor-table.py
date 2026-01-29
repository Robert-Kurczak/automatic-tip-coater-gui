#!/usr/bin/env python3

import argparse
import numpy as np
import subprocess

FILE_TEMPLATE = """
#pragma once

// Generated with generate-thermistor-table.py
// Reference resistance = |reference_resistance|R
// Reference temperature = |reference_temperature|*C
// Thermistor Beta coefficient = |beta_coefficient|
// Divider resistor = |divider_resistor_value|R
// ADC bits = |adc_bits|

#include <array>

namespace ATC {
inline constexpr std::array<float, |table_size|> |table_name| {
    |table_values|
};
}
"""

class Thermistor:
    def __init__(
            self, reference_resistance: float,
            reference_temperature_celsius: float,
            beta_coefficient: float):
        self.reference_resistance = reference_resistance
        self.reference_temperature_celsius = reference_temperature_celsius
        self.beta_coefficient = beta_coefficient

    def fill_file_content(self, file_content):
        return file_content \
        .replace("|reference_resistance|", str(self.reference_resistance)) \
        .replace("|reference_temperature|", str(self.reference_temperature_celsius)) \
        .replace("|beta_coefficient|", str(self.beta_coefficient))

class Adc:
    def __init__(self, divider_resistor: int, resolution_bits: int):
        self.divider_resistor = divider_resistor
        self.resolution_bits = resolution_bits
        self.max_reading = 2**resolution_bits - 1

    def fill_file_content(self, file_content):
        return file_content \
        .replace("|divider_resistor_value|", str(self.divider_resistor)) \
        .replace("|adc_bits|", str(self.resolution_bits)) \

class TableCalculator:
    def __init__(self, thermistor: Thermistor, adc: Adc):
        self.thermistor = thermistor
        self.adc = adc

    def convert_adc_to_kelvin(self, adc_reading: int):
        resistance_ratio = self.adc.divider_resistor / self.thermistor.reference_resistance

        reference_temperature_kelvin = self.thermistor.reference_temperature_celsius + 273.15
        temperature_ratio = \
            self.thermistor.beta_coefficient / reference_temperature_kelvin

        denominator = np.log(
            resistance_ratio * (self.adc.max_reading / adc_reading) - resistance_ratio
            ) + temperature_ratio

        return self.thermistor.beta_coefficient / denominator

    def create_celsius_table(self):
        table = [0]

        for raw_value in range(1, self.adc.max_reading):
            celsius = self.convert_adc_to_kelvin(raw_value) - 273.15
            table.append(celsius)

        table[0] = table[1]

        return table

class LookupTable:
    def __init__(self, table: list, table_name: str):
        self.table = table
        self.table_name = table_name

    def fill_file_content(self, file_content: str):
        table_size = str(len(self.table))
        values = ",".join(str(x) for x in self.table)

        return file_content \
            .replace("|table_size|", table_size) \
            .replace("|table_name|", self.table_name) \
            .replace("|table_values|", values)

class LookupTableFile:
    def __init__(self, file_path: str):
        self.file_path = file_path

    def write(self, file_content: str):
        with open(self.file_path, "w", encoding="utf-8") as file:
            file.write(file_content)

    def clang_format(self):
        subprocess.run(
            ["clang-format", "-i", self.file_path],
            check=False
        )

def main(args):
    thermistor = Thermistor(
        args.reference_resistance,
        args.reference_temperature,
        args.beta
    )
    adc = Adc(args.divider_resistor, args.adc_bits)
    calculator = TableCalculator(thermistor, adc)

    celsius_values = calculator.create_celsius_table()
    lookup_table = LookupTable(celsius_values, args.table_name)

    file_content = FILE_TEMPLATE
    file_content = thermistor.fill_file_content (file_content)
    file_content = adc.fill_file_content(file_content)
    file_content = lookup_table.fill_file_content(file_content)

    file_manager = LookupTableFile(args.file_path)
    file_manager.write(file_content)
    file_manager.clang_format()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--reference-resistance",
        help="Known thermistor resistance at known temperature",
        required=True,
        type=float
    )
    parser.add_argument(
        "--reference-temperature",
        help="Known temperature in Celsius, at where thermistor achieves known resistance",
        required=True,
        type=float
    )
    parser.add_argument(
        "--beta",
        help="Thermistor beta coefficient",
        required=True,
        type=float
    )
    parser.add_argument(
        "--divider-resistor",
        help="Value of a known voltage divider resistor",
        required=True,
        type=int
    )
    parser.add_argument(
        "--adc-bits",
        help="ADC resolution in bits",
        required=True,
        type=int
    )
    parser.add_argument(
        "--file-path",
        default="thermistor-table.hpp",
        help="Path to the output file",
        type=str,
    )
    parser.add_argument(
        "--table-name",
        default="THERMISTOR_TABLE",
        help="Name of table in code",
        type=str
    )

    main(parser.parse_args())
