#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Pngexp.h"
#include "Screen.h"

using namespace std;
using namespace PF;

bool Pngexp::exp(const Screen& sc, std::string filename){
	uint width = sc.getX();
	uint height = sc.getY();
	FILE* f;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep p_row = NULL;
	png_text pngtext[1];

	f = fopen(filename.c_str(),"wb");
	if(f == NULL){
		cerr<<"Problem opening png file for writing"<<endl;
		return false;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr == NULL){
		cerr<<"Problem creating png_ptr structure during png write"<<endl;
		fclose(f);
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL){
		cerr<<"Problem creating png info structure during png write"<<endl;
		png_destroy_write_struct(&png_ptr,NULL);
		fclose(f);
		return false;
	}

	if(setjmp(png_jmpbuf(png_ptr))){
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(f);
		cerr<<"problem during png export"<<endl;
		return false;
	}

	png_init_io(png_ptr, f);
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
		 	PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	pngtext[0].key = (char*)"Title:";
	pngtext[0].text = (char*)"GiX's raytracer output";
	pngtext[0].compression = PNG_TEXT_COMPRESSION_NONE;

	png_set_text(png_ptr, info_ptr, pngtext, 1);
	png_write_info(png_ptr, info_ptr);

	p_row = (png_byte*)malloc((size_t) (width*3));

	if(p_row == NULL){
		cerr<<"problem allocating memory for pngrow during png exporting"<<endl;
		fclose(f);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}

	for(uint i=0; i<height; i++){
		for(uint j=0; j<width; j++){
			p_row[3*j]=sc.getColor(j, i).getR_int();
			p_row[3*j+1]=sc.getColor(j, i).getG_int();
			p_row[3*j+2]=sc.getColor(j, i).getB_int();
		}
		png_write_row(png_ptr, p_row);
	}

	png_write_end(png_ptr, info_ptr);

	free(p_row);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(f);

	return true;
}
