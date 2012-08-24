#ifndef KOCMOC_CORE_SCENE_ASSIMP_LOGGER_STREAM_HPP_
#define KOCMOC_CORE_SCENE_ASSIMP_LOGGER_STREAM_HPP_

#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#include <iostream>


class AssimpLoggerStream : public Assimp::LogStream
{
public:
	// Write womethink using your own functionality
	void write(const char* message)
	{
		std::cout << "assimp logger: " << message;
	}
};


#endif
