def options(opt):
    opt.load('compiler_c')

def configure(conf):
    conf.env.CC = 'arm-arago-linux-gnueabi-gcc'
    conf.env.AR = 'arm-arago-linux-gnueabi-ar'
    conf.load('compiler_c')

def build(bld):
    bld.shlib(
        source = ['src/rgb_bitmap.c',
                  'src/filter.c',
                  'src/transform.c',
                  'src/primitives/ops.c',
                  'src/codec/ppm_codec.c'],
        target = 'argon',
        defines = ['ENABLE_NEON_OPTS'],
        includes = ['include'],
        cflags = ['-std=c99', '-mfpu=neon', '-O3', '-Wall', '-Werror']
    )

    bld.program(
        source = ['src/apps/invert.c'],
        target = 'ppminvert',
        defines = ['ENABLE_NEON_OPTS'],
        includes = ['include'],
        use = 'argon',
        cflags = ['-std=c99', '-O3', '-mfpu=neon', '-Wall', '-Werror']
    )

    bld.program(
        source = ['test/test_primitives.c'],
        target = 'argon_test',
        defines = ['ENABLE_NEON_OPTS'],
        includes = ['include', '/usr/local'],
        use = 'argon',
        lib = ['check'],
        libpath = ['/usr/local'],
        cflags = ['-std=c99', '-O3', '-mfpu=neon', '-Wall']
    )
