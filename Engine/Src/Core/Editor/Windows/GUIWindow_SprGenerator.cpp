#include "Engine/Core/Editor/Windows/GUIWIndow_SprGenerator.h"
#include <filesystem>
#include "Engine/Utility/SprHandler.h"

namespace fs = std::filesystem;

namespace Core
{
    namespace Editor
    {
        GUIWindow_SprGenerator::GUIWindow_SprGenerator(EngineGUI& engineGUI) : GUIWindow(engineGUI)
        {

        }

        void GUIWindow_SprGenerator::Update(float delta)
        {
        }

        void GUIWindow_SprGenerator::Render()
        {
            ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
            if (ImGui::Begin("Spr Generator", &m_isActive, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
            {
                if (ImGui::Button("Open File"))
                {
                    String filePath = OpenFileDialog();
                    if (!filePath.empty())
                    {
                        if (LoadNecessaryFiles(filePath))
                        {
                            m_fileLoaded = true;
                        }
                    }
                }

                if (m_fileLoaded)
                {
                    if (ImGui::Button("Create Spr File"))
                    {
                        if (CreateSpr())
                        {
                            m_jsonFilePath = "";
                            m_pngFilePath = "";
                            m_directory = "";
                            m_fileLoaded = false;
                        }
                    }
                }

                ImGui::End();
            }
        }

        String GUIWindow_SprGenerator::OpenFileDialog()
        {
            /*
            OPENFILENAME ofn;
            char szFile[260] = { 0 };
            ZeroMemory(&ofn, sizeof(ofn));

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = NULL;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "JSON FILES\0*.json\0";
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            String defaultPath = ASSETS_PATH;

            char initialDirBuffer[MAX_PATH] = { 0 };
            strncpy(initialDirBuffer, defaultPath.c_str(), sizeof(initialDirBuffer) - 1);
            ofn.lpstrInitialDir = initialDirBuffer;

            if (GetOpenFileName(&ofn) == TRUE)
            {
                return ofn.lpstrFile;
            }

            */
            return "";
        }

        bool GUIWindow_SprGenerator::CreateSpr() const
        {
            try
            {
                Utility::CreateSprFile(m_jsonFilePath, m_pngFilePath, m_outputPath);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
                return false;
            }

            return true;
        }

        bool GUIWindow_SprGenerator::LoadNecessaryFiles(const String& jsonFilePath)
        {
            fs::path jsonPath(jsonFilePath);
            fs::path fileDirectory = jsonPath.parent_path();
            fs::path fileBaseName = jsonPath.stem();

            // Check for a corresponding .png file
            fs::path pngPath = fileDirectory / (fileBaseName.string() + ".png");
            if (fs::exists(pngPath))
            {
                m_directory = fileDirectory.string();

                m_jsonFilePath = jsonFilePath;
                m_pngFilePath = pngPath.string();
                m_outputPath = m_directory + "/" + (fileBaseName.string() + ".spr");

                return true;
            }

            return false;
        }
    }
}
