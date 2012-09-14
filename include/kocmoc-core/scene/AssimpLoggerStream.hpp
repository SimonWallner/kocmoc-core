#ifndef KOCMOC_CORE_SCENE_ASSIMP_LOGGER_STREAM_HPP_
#define KOCMOC_CORE_SCENE_ASSIMP_LOGGER_STREAM_HPP_

#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#include <objectif-lune/Singleton.hpp>
#include <sstream>


class AssimpLoggerStream : public Assimp::LogStream
{
public:
	// Write womethink using your own functionality
	void write(const char* message)
	{
		std::stringstream sstr;
		sstr << "assimp logger: " << message;
		objectifLune::Singleton::Get()->trace(sstr.str());
	}
};


#endif
