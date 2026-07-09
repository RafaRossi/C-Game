import re, sys

component_pattern = re.compile(r'COMPONENT_BODY\((\w+)\)')
property_pattern = re.compile(r'PROPERTY\((.*?)\)\s*([a-zA-Z0-9_:<>]+)\s+([a-zA-Z0-9_]+)\s*(?:=.*?)?;')

TYPE_MAP = {
    "float": "PropertyType::Float",
    "int": "PropertyType::Int",
    "bool": "PropertyType::Bool",
    "std::string": "PropertyType::String",
    "Vector2": "PropertyType::Vector2"
}


def parse_header(header_path):
    with open(header_path, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()

    if '#define COMPONENT_BODY' in content or '#define PROPERTY' in content:
        return "// DO NOT EDIT.\n"

    class_match = component_pattern.search(content)

    if class_match:
        class_name = class_match.group(1)
        if not re.search(rf'\bclass\s+{re.escape(class_name)}\b', content):
            class_match = None

    code = "// DO NOT EDIT. Auto-generated.\n"
    code += f'#include "{header_path}"\n\n'

    if not class_match:
        return code

    class_name = class_match.group(1)
    props = property_pattern.findall(content)

    code += '#include "Engine/Editor/ComponentFactory/ComponentFactory.h"\n\n'

    code += "#ifdef TR_EDITOR\n"

    code += f"void {class_name}::AutoExposeField(FieldCollector& collector) {{\n"
    for options, var_type, var_name in props:
        if var_type in TYPE_MAP:
            code += f'    collector.Expose("{var_name}", &{var_name});\n'
    code += "}\n\n"

    code += f"static bool bReg_{class_name} = []() {{\n"
    code += f'    ComponentFactory::Register("{class_name}", []() {{ return new {class_name}(); }});\n'
    code += "    return true;\n"
    code += "}();\n"

    code += "#endif // TR_EDITOR\n"
    return code


if __name__ == "__main__":
    header_path, output_path = sys.argv[1], sys.argv[2]
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(parse_header(header_path))