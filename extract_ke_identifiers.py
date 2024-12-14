import os
import re
import json

def get_files_with_extension(root_dir, extension=".h"):
    for root, _, files in os.walk(root_dir):
        for file in files:
            if file.endswith(extension):
                yield os.path.join(root, file)

def extract_identifiers(file_path):
    class_struct_pattern = r'\b(class|struct)\s+(\w+)'
    identifiers = []
    
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
        for line in file:
            matches = re.findall(class_struct_pattern, line)
            for match in matches:
                print(f"Identifier: '{match[1]}'")
                identifiers.append(match[1])
    
    return identifiers

def collect_identifiers_from_directory(directory):
    if os.path.exists(directory):
        if not os.path.isdir(directory):
            print(f"Path: '{directory}' exists, but is not a directory")
    else:
        print(f"Path: '{directory}' does not exist")
    
    all_identifiers = []
    for file_path in get_files_with_extension(directory, ".h"):
        print(f"File: '{file_path}'")
        identifiers = extract_identifiers(file_path)
        all_identifiers.extend(identifiers)
    return all_identifiers

def save_identifiers_to_json(identifiers, output_file):
    with open(output_file, 'w', encoding='utf-8') as file:
        json.dump({"identifiers": identifiers}, file, indent=4, ensure_ascii=False)


def main():
    ke_api_dir = "./KingdomEngine/include/KingdomEngine"
    ke_identifiers_json_file = "./resources/ke_identifiers.json"
    
    identifiers = collect_identifiers_from_directory(ke_api_dir)
    save_identifiers_to_json(identifiers, ke_identifiers_json_file)

if __name__ == "__main__":
    main()

