#include <iostream>
#include <memory>
#include "Scene.h"
#include "Shader.h"
#include "Raytracer.h"
#include "YafImport.h"


using namespace PF;
using namespace std;

int main(int argc, char* argv[]){
	YafImport import;
	if(argc != 2){
		cout<<"jako paramter pouzijte nazev souboru s renderovanou scenou"<<endl;
		return 0;
	}
	auto_ptr<Scene> scene( import.import(argv[1]) );

	if(scene.get() == 0){
		cerr<<"error loading scene"<<endl;
		return 0;
	}
	string outputFile(argv[1]);
	outputFile[outputFile.size()-1]='g';	// tohle je jen narychlo :)
	outputFile[outputFile.size()-2]='n';
	outputFile[outputFile.size()-3]='p';
	Raytracer r(scene.get(), outputFile);
	r.render();
	return 0; 
}
