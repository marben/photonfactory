list = Split("""main.cc
		Screen.cc
		Pngexp.cc
		Color.cc
		Sphere.cc
		Scene.cc
		Triangle.cc
		Triangle2d.cc
		Raytracer.cc
		Plane.cc
		YafImport.cc
		Camera.cc
		BasicShader.cc
		Matrix4x4.cc
		SurfacePoint.cc
		""")

flags = '-Wall -O3 -pedantic -ansi -ffast-math -Wextra'
libs = ['png', 'xml2']

xml2_config = WhereIs('xml2-config')
png_config = WhereIs('libpng-config')
env=Environment();
env.ParseConfig(xml2_config + ' --cflags --ldflags')
env.ParseConfig(png_config + ' --cflags --ldflags')

env.Program (target = 'ray', source = list, CCFLAGS=flags, LIBS=libs)
