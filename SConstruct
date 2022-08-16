import glob
import os
import sys

vars = Variables('settings.py')
vars.AddVariables(
    EnumVariable('mode', 'Build mode', 'debug',
        allowed_values=('debug', 'release', 'profile')),
    BoolVariable('werror', 'Warnings as error', True),
    BoolVariable('yocto', 'Enable yocto renderer', True),
    PathVariable('config_file', 'Config file to use', 'src/config.h'),
)

target_os = str(Platform())

env = Environment(variables = vars, ENV = os.environ)
conf = env.Configure()

if os.environ.get('CC') == 'clang' or target_os == 'darwin':
    env.Replace(CC='clang', CXX='clang++')
else:
    env.Replace(CC='gcc', CXX='g++')

# Asan & Ubsan (need to come first).
if env['mode'] == 'debug' and target_os == 'posix':
    env.Append(CCFLAGS=['-fsanitize=address', '-fsanitize=undefined'],
               LINKFLAGS=['-fsanitize=address', '-fsanitize=undefined'],
               LIBS=['asan', 'ubsan'])


# Global compilation flags.
# CCFLAGS   : C and C++
# CFLAGS    : only C
# CXXFLAGS  : only C++
env.Append(
    CFLAGS=['-std=gnu99'],
    CXXFLAGS=['-std=gnu++17']
)

# Add Some More Flags Only If The OS is not msys (it causes building issues)
if target_os != 'msys':
    env.Append(
        CFLAGS=['-Wall', '-Wno-unknown-pragma', '-Wno-unknown-warning-option', '-Wno-format-truncation'],
        CXXFLAGS=['-Wall', '-Wno-narrowing']
    )

# Use -Werror only in debug/analyze
if env['werror'] and env['mode'] in ['debug', 'analyze']:
    env.Append(CCFLAGS='-Werror')

if env['mode'] not in ['debug', 'analyze']:
    env.Append(CPPDEFINES='NDEBUG', CCFLAGS='-O3')

if env['mode'] == 'debug':
    env.Append(CCFLAGS=['-O0'])

if env['mode'] in ('profile', 'debug'):
    env.Append(CCFLAGS='-g')

env.Append(CPPPATH=['src'])
env.Append(CCFLAGS=['-include', '$config_file'])

def GatherFiles(Directories):
    if type(Directories) is not list:
        Directories = [Directories];

    files = [];
    for directory in Directories:
        for root, dirnames, filenames in os.walk(directory):
            for filename in filenames:
                if filename.endswith('.c') or filename.endswith('.cpp'):
                    files.append(os.path.join(root, filename))

    return files

# Get all the c and c++ files in src, recursively.
sources = []
sources += GatherFiles(['src', 'lib/lua-5.4.4', 'lib/imgui', 'lib/xxhash'])

# Check for libpng.
if conf.CheckLibWithHeader('libpng', 'png.h', 'c'):
    env.Append(CPPDEFINES='HAVE_LIBPNG=1')

# Linux compilation support.
if target_os == 'posix':
    env.Append(LIBS=['GL', 'm'])
    # Note: add '--static' to link with all the libs needed by glfw3.
    env.ParseConfig('pkg-config --libs glfw3')
    env.ParseConfig('pkg-config --cflags --libs gtk+-3.0')

# Windows compilation support.
if target_os == 'msys':
    env.Append(CXXFLAGS=['-Wno-attributes', '-Wno-unused-variable',
                         '-Wno-unused-function'])
    env.Append(LIBS=['glfw3', 'opengl32', 'Imm32', 'gdi32', 'Comdlg32',
                     'z', 'tre', 'intl', 'iconv'],
               LINKFLAGS='--static')
    sources += glob.glob('lib/glew/glew.c')
    env.Append(CPPPATH=['lib/glew'])
    env.Append(CPPDEFINES=['GLEW_STATIC', 'FREE_WINDOWS'])
    env.Append(LINKFLAGS="-mwindows") # Fix Console From Popping-Up

# OSX Compilation support.
if target_os == 'darwin':
    sources += glob.glob('src/*.m')
    env.Append(FRAMEWORKS=['OpenGL', 'Cocoa'])
    env.Append(LIBS=['m', 'glfw', 'objc'])
    # Fix warning in noc_file_dialog (the code should be fixed instead).
    env.Append(CCFLAGS=['-Wno-deprecated-declarations'])

# Add external libs.
env.Append(CPPPATH=['lib/'])
env.Append(CPPPATH=['lib/uthash'])
env.Append(CPPPATH=['lib/stb'])
env.Append(CPPPATH=['lib/noc'])
env.Append(CPPPATH=['lib/xxhash'])
env.Append(CPPPATH=['lib/libvxl'])

if not env['yocto']:
    env.Append(CPPDEFINES='YOCTO=0')

# Append external environment flags
env.Append(
    CFLAGS=os.environ.get("CFLAGS", "").split(),
    CXXFLAGS=os.environ.get("CXXFLAGS", "").split(),
    LINKFLAGS=os.environ.get("LDFLAGS", "").split()
)

env.Program(target='goxel2', source=sorted(sources))
