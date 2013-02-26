env = Environment()
env.Append(CPPPATH=['CException/lib','src/', '/usr/include/libftdi1'])
sources = env.Glob('src/*.c')
sources.extend(env.Glob('CException/lib/*.c'))
env.Program(target='ftdireader', source=sources, LIBS=['libftdi1'])

SConscript('test/SConscript', exports='env')
