#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <fmod.hpp>
//#include <AL/al.h>
//#include <Al/alc.h>

namespace Core
{
    namespace Systems
    {
        class AudioSystem
        {
        private:
            //ALCdevice* m_pAudioDevice;
            //ALCcontext* m_pContext;

        public:
            AudioSystem();
            ~AudioSystem();

            void Update();
        };
    }
}

#endif //AUDIOSYSTEM_H
