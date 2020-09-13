#pragma once

#include <string>
#include <cstdlib>

class FileSystem
{
private:
	typedef std::string(*Builder) (const std::string& path);

public:
	static std::string getPath(const std::string& path) {
		static std::string(*pathBuilder)(std::string const&) = getPathBuilder();
		return (*pathBuilder)(path);
	}

private:
    static std::string const& getRoot()
    {
        //static char const* envRoot = getenv("LOGL_ROOT_PATH");
        //static char const* givenRoot = (envRoot != nullptr ? envRoot : logl_root);
        //static std::string root = (envRoot != nullptr ? envRoot : "");
        return "";
    }

    static Builder getPathBuilder()
    {
        if (getRoot() != "")
            return &FileSystem::getPathRelativeRoot;
        else
            return &FileSystem::getPathRelativeBinary;
    }

    static std::string getPathRelativeRoot(const std::string& path)
    {
        return getRoot() + std::string("/") + path;
    }

    static std::string getPathRelativeBinary(const std::string& path)
    {
        return "../../../" + path;
    }
};