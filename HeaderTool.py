import os
import re
import sys

pattern = re.compile(r'PROPERTY\((.*?)\)\s*([a-zA-Z0-9_:]+)\s+([a-zA-Z0-9_]+)\s*;')


def parse_header(filepath):
    with open(filepath, 'r') as file:
        content = file.read()

    matches = pattern.findall(content)
    if not matches:
        return None

    generated_code = "//DO NOT EDIT.\n"
    generated_code += "private:\n"
    generated_code += "    void AutoExposeField() {\n"
    generated_code += "#ifdef SDL_ENGINE_EDITOR\n"

    for match in matches:
        options, var_type, var_name = match

        if var_type == "int" or var_type == "float" or var_type == "bool":
            generated_code += f'        ExposeField("{var_name}", &{var_name});\n'

    generated_code += "endif // SDL_ENGINE_EDITOR\n"
    generated_code += "    }\n"

    return generated_code


if __name__ == "__main__":
    header_path = sys.argv[1]
    output_path = sys.argv[2]

    code = parse_header(header_path)
    if code:
        with open(output_path, 'w') as f:
            f.write(code)
