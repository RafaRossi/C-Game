import re, sys

register_pattern = re.compile(r'REGISTER_BODY\(\s*(\w+)\s*,\s*(\w+)\s*\)')
property_pattern = re.compile(r'PROPERTY\((.*?)\)\s*([a-zA-Z0-9_:<>]+)\s*(\*)?\s*([a-zA-Z0-9_]+)\s*(?:=.*?)?;')

TYPE_MAP = {
    "float": "PropertyType::Float",
    "int": "PropertyType::Int",
    "bool": "PropertyType::Bool",
    "std::string": "PropertyType::String",
    "Vector2": "PropertyType::Vector2",
    "Color": "PropertyType::Color"
}


def parse_header(header_path):
    with open(header_path, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()

    if '#define COMPONENT_BODY' in content or '#define PROPERTY' in content:
        return "// DO NOT EDIT.\n"

    match = register_pattern.search(content)
    if not match:
        return "// No macros found.\n"

    class_name = match.group(1)
    base_class = match.group(2)

    if not re.search(rf'\bclass\s+{re.escape(class_name)}\b', content):
        return "// Class definition not found.\n"

    props = property_pattern.findall(content)

    code = "// DO NOT EDIT. Auto-generated.\n"
    code += f'#include "{header_path}"\n\n'

    code += '#include "Engine/Game/Core/Factory/Factory.h"\n\n'
    code += '#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"\n\n'


    code += f"void {class_name}::AutoExposeField(FieldCollector& collector) {{\n"
    for options, var_type, is_pointer, var_name in props:

        display_name = var_name

        if options.strip():
            match_name = re.search(r'DisplayName\s*=\s*"([^"]+)"', options)
            if match_name:
                display_name = match_name.group(1)

        if is_pointer == "*":
            code += f'    collector.ExposePolymorphic<{var_type}>("{display_name}", &{var_name});\n'
        if var_type in TYPE_MAP:
            code += f'    collector.Expose("{display_name}", &{var_name});\n'
    code += "}\n\n"

    code += f"static bool bReg_{class_name} = []() {{\n"
    code += f'    Factory<{base_class}>::Register("{class_name}", []() {{ return new {class_name}(); }});\n'
    code += "    return true;\n"
    code += "}();\n"

    return code


if __name__ == "__main__":
    header_path, output_path = sys.argv[1], sys.argv[2]
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(parse_header(header_path))
