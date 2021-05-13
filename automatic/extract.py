#!/usr/bin/env python
import pprint
import sys


def output_function_signature(file, name, rtrn_type, params):
    rtrn_type = rtrn_type.replace('extern ', '')
    file.write(rtrn_type + ' ' + name + '_wrapped(uint64_t id')    
    for param in params:
        file.write(', ')
        if param['pointer']:
            file.write(param['type'] + ' ' + param['name'] + '_client')
            file.write(', ')
            file.write(param['type'] + ' ' + param['name'] + '_library')
        else:
            file.write(param['type'] + ' ' + param['name'])
        #print("param: %s" % param["name"])
    file.write(')')

def output_function_body(file, name, rtrn_type, params):
    rtrn_type = rtrn_type.replace('extern ', '')
    file.write(' {\n')
    file.write('\t//Saved information here:\n')
    file.write('\t\n')
    file.write('\tenable_lib(id);\n')
    file.write('\t\n')
    file.write('\t')
    if not ('void' in rtrn_type and '*' not in rtrn_type):
        file.write(rtrn_type + ' ret = ')
    file.write(name + '(')
    param_pos = 0
    for param in params:
        if param_pos > 0:
            file.write(', ')
        if param['pointer']:
            file.write(param['name'] + '_library')
        else:
            file.write(param['name'])
        param_pos += 1
    file.write(');\n')
    file.write('\tdisable_lib(id);\n')
    file.write('\t//Sanitize data here:\n')
    file.write('\t\n')
    if not ('void' in rtrn_type and '*' not in rtrn_type):
        file.write('\treturn ret;\n')
    file.write('}\n')



sys.path = ["../"] + sys.path
from CppHeaderParser import CppHeader, CppParseError

file_name = sys.argv[1]

try:
    cppHeader = CppHeader(file_name)
except CppParseError as e:
    print(e)
    sys.exit(1)

#print("CppHeaderParser view of %s" % cppHeader)

print("\nFree functions are:")
for func in cppHeader.functions:
    print("name %s" % func["name"])
    print("type  %s" % func["rtnType"])
    #print(" %s" % func["parameters"])
    for param in func["parameters"]:
        print("param name: %s" % param['name'])
        print("param is pointer: %s" % param['pointer']) 
        print("param type: %s" % param['type'])
        #print("param: %s" % param['ctypes_type'])

    #print(func.keys())

original_name_header = file_name[0:file_name.index('.')] + '.h'
new_file_name_header = file_name[0:file_name.index('.')] + '_wrapped.h'
new_file_name_source = file_name[0:file_name.index('.')] + '_wrapped.c'
wrapped_header = open(new_file_name_header, "w")
wrapped_source = open(new_file_name_source, "w")
wrapped_header.write('#include \"' + original_name_header + '\"\n')

wrapped_header.write('#include \"allocator.h\"\n')

for func in cppHeader.functions:
    output_function_signature(wrapped_header, func["name"], func["rtnType"], func["parameters"])
    wrapped_header.write(';\n')
wrapped_header.close()

wrapped_source.write('#include \"' + new_file_name_header + '\"\n')

for func in cppHeader.functions:
    output_function_signature(wrapped_source, func["name"], func["rtnType"], func["parameters"])
    output_function_body(wrapped_source, func["name"], func["rtnType"], func["parameters"])
wrapped_header.close()

#print("\n#includes are:")
#for incl in cppHeader.includes:
#    print(" %s" % incl)

#print("\n#defines are:")
#for define in cppHeader.defines:
#    print(" %s" % define)