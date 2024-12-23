#ifndef GL_VERSION_COMBO_H
#define GL_VERSION_COMBO_H

#include <KingdomEngine/Core/Log.h>
#include <KingdomEngine/Events/Event.h>

namespace Editor
{
    static void GLVersionCombo(int& glVersion)
    {
        glVersion = KE::Renderer::GetVersion().glVersion;
        if (ImGui::Combo("OpenGL Version", &glVersion,
				"OpenGL 3\0"
				"OpenGL 2\0"))
        {
            if (glVersion == KE::GLVersion::OpenGL2)
            {
                DISPATCH_EVENT(KE::EventType::LoadGL2);
                LOG_WARN("Switching OpenGL version to OpenGL 2.1!");
            }
            else if (glVersion == KE::GLVersion::OpenGL3)
            {
                DISPATCH_EVENT(KE::EventType::LoadGL3);
                LOG_WARN("Switching OpenGL version to OpenGL 3.3!");
            }
        }
    }
}

#endif
