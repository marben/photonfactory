#include <iostream>
#include <memory>

#include "PngWriter.h"

#include "Scene.h"
#include "Shader.h"
#include "Raytracer.h"
#include "YafImport.h"
#include "PngWriter.h"


using namespace PF;
using namespace std;

int main(int argc, char* argv[]){
	YafImport import;
	if(argc != 2){
		cout<<"Usage: ray [input_file]"<<endl;
		return 1;
	}
	auto_ptr<Scene> scene( import.import(argv[1]) );

	if(scene.get() == 0){
		cerr<<"error loading scene"<<endl;
		return 1;
	}
	string outputFile(argv[1]);

	// the file suffix
	outputFile[outputFile.size()-3]='p';
	outputFile[outputFile.size()-2]='n';
	outputFile[outputFile.size()-1]='g';
	
	

	Raytracer r;
	auto_ptr<Screen> screen = r.render(*scene.get());

	ggl::PngWriter pngWriter;
	pngWriter.outputFile(outputFile);
	pngWriter.write(screen->getCanvas());

	return 0; 
}
