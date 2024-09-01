#ifndef SPRMANAGER_H
#define SPRMANAGER_H
#include <cstdint>
#include <fstream>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <SDL2/SDL_stdinc.h>
#include <json/json.h>

using String = std::string;

namespace Core
{
    namespace Utility
    {
        struct Header
        {
            char magic[4]; // SPRF
            uint32_t version;
            uint32_t metadataSize;
            uint32_t imageSize;
        };

        inline std::vector<char> ReadFile(const String& path)
        {
            std::ifstream file(path, std::ios::binary | std::ios::ate);
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (file.read(buffer.data(), size))
            {
                return buffer;
            }
            else
            {
                throw std::runtime_error("Unable to read File: '" + path + "'");
            }
        }

        inline void WriteFile(const String& path, const std::vector<char>& data)
        {
            std::ofstream file(path, std::ios::binary);
            if (!file.is_open())
            {
                throw std::runtime_error("Unable to open file for writing: '" + path + "'");
            }

            file.write(data.data(), data.size());
        }

        inline void CreateSprFile(const String& jsonPath, const String& pngPath, const String& outputPath)
        {
            // Read Data from .png and .json file
            std::vector<char> jsonData = ReadFile(jsonPath);
            std::vector<char> pngData = ReadFile(pngPath);

            Header header;
            memcpy(header.magic, "SPRF", 4);
            header.version = 1;
            header.metadataSize = static_cast<uint32_t>(jsonData.size());
            header.imageSize = static_cast<uint32_t>(pngData.size());

            std::vector<char> buffer(sizeof(Header) + jsonData.size() + pngData.size());

            memcpy(buffer.data(), &header, sizeof(Header));
            memcpy(buffer.data() + sizeof(Header), jsonData.data(), jsonData.size());
            memcpy(buffer.data() + sizeof(Header) + jsonData.size(), pngData.data(), pngData.size());

            WriteFile(outputPath, buffer);
            std::cout << "Created .spr File: '" << outputPath << "'" << std::endl;
        }

        inline void LoadSprFile(const String& path, Json::Value& jsonData, SDL_RWops*& textureData)
        {
            std::vector<char> fileData = ReadFile(path);

            // Parse Header
            Header header;
            std::memcpy(&header, fileData.data(), sizeof(Header));

            if (std::memcmp(header.magic, "SPRF", 4) != 0)
            {
                std::cerr << "Invalid .spr file format" << std::endl;
                textureData = nullptr;
                return;
            }

            // Extract Json Data
            std::vector<char> jsonPart(fileData.begin() + sizeof(Header), fileData.begin() + sizeof(Header) + header.metadataSize);
            String jsonString(jsonPart.begin(), jsonPart.end());

            Json::Reader reader;
            try
            {
                reader.parse(jsonString, jsonData);
            }
            catch (const Json::Exception& e)
            {
                std::cerr << "Failed to Parse Json Data: " << e.what() << std::endl;
                return;
            }

            // Extract PNG Data
            std::vector<char> pngData(fileData.begin() + sizeof(Header) + header.metadataSize, fileData.begin() + sizeof(Header) + header.metadataSize + header.imageSize);

            textureData = SDL_RWFromConstMem(pngData.data(), pngData.size());
            if (!textureData)
            {
                std::cerr << "Failed to create SDL_RWops from PNG data." << std::endl;
                return;
            }
        }
    }
}

#endif //SPRMANAGER_H
