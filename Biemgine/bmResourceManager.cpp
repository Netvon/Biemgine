#include "stdafx.h"
#include "bmResourceManager.h"
#include <fstream>
#include <sstream>

bmShader bmResourceManager::loadShader(const string & name, const string & vspath, const string & fspath)
{
	string vscode, fscode;

	try {
		ifstream vsfile(vspath);
		ifstream fsfile(fspath);

		stringstream vsstream, fsstream;
		vsstream << vsfile.rdbuf();
		fsstream << fsfile.rdbuf();

		vsfile.close();
		fsfile.close();

		vscode = vsstream.str();
		fscode = fsstream.str();
	}
	catch (exception e) {
		// TODO: some error logging here...
	}
	
	bmShader shader(vscode, fscode);
	shaders[name] = shader;
	return shaders[name];
}

bmShader bmResourceManager::getShader(const string & name) const
{
	return shaders.at(name);
}

void bmResourceManager::clearShaders()
{
	for (auto s : shaders) {
		glDeleteProgram(s.second.getId());
	}

	shaders.clear();
}
