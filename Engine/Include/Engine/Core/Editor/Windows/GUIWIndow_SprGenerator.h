#ifndef GUIWINDOW_SPRGENERATOR_H
#define GUIWINDOW_SPRGENERATOR_H
#include "Engine/Core/Editor/GUIWindow.h"

using String = std::string;

namespace Core
{
    namespace Editor
    {
        class GUIWindow_SprGenerator : public GUIWindow
        {
            const int WINDOW_WIDTH = 480;
            const int WINDOW_HEIGHT = 250;

        private:
            String m_directory;

            String m_jsonFilePath;
            String m_pngFilePath;
            String m_outputPath;
            bool m_fileLoaded;

        public:
            GUIWindow_SprGenerator(EngineGUI& engineGUI);

            void Update(float delta) override;
            void Render() override;

        private:
            String OpenFileDialog();
            bool CreateSpr() const;

            bool LoadNecessaryFiles(const String& jsonFilePath);
        };
    }
}

#endif //GUIWINDOW_SPRGENERATOR_H
