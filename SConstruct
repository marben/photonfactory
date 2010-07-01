list = Split("""src/main.cc
		src/Screen.cc
		src/Pngexp.cc
		src/Color.cc
		src/Sphere.cc
		src/Scene.cc
		src/Triangle.cc
		src/Triangle2d.cc
		src/Raytracer.cc
		src/Plane.cc
		src/YafImport.cc
		src/Camera.cc
		src/BasicShader.cc
		src/Matrix4x4.cc
		src/SurfacePoint.cc
		""")

flags = '-Wall -O3 -pedantic -ansi -ffast-math -Wextra'
libs = ['png', 'xml2']

xml2_config = WhereIs('xml2-config')
png_config = WhereIs('libpng-config')
env=Environment();
env.ParseConfig(xml2_config + ' --cflags --ldflags')
env.ParseConfig(png_config + ' --cflags --ldflags')

env.Program (target = 'ray', source = list, CCFLAGS=flags, LIBS=libs)
