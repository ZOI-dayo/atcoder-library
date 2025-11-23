#!/usr/bin/env python3

import sys
import os
import re



def process_file(file_path, base_dir, seen_files):
    abs_path = os.path.normpath(os.path.join(base_dir, file_path))

    if abs_path in seen_files:
        return ""

    seen_files.add(abs_path)
    output_lines = []

    with open(abs_path, 'r', encoding='utf-8') as f:
        for line in f:
            if line.strip() == "#pragma once":
                continue
            match = re.match(r'^\s*#include\s*"([^"]+)"', line)
            
            if match:
                include_path = match.group(1)
                output_lines.append(process_file(include_path, os.path.dirname(abs_path), seen_files))
            else:
                output_lines.append(line)
    output_lines.append("\n")

    return "".join(output_lines)

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <root_cpp_file>", file=sys.stderr)
        sys.exit(1)

    root_file = sys.argv[1]
    root_dir = os.path.dirname(os.path.abspath(root_file))
    print(process_file(root_file, root_dir, set()))

if __name__ == "__main__":
    main()