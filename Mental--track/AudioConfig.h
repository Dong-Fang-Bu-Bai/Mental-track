#ifndef AUDIOCONFIG_H
#define AUDIOCONFIG_H

#include <QString>

namespace AudioConfig
{
    // 资源路径
    const QString ClickSound = "qrc:/audio/Debug/music/click.wav";
    const QString BackgroundMusic = "qrc:/audio/Debug/music/music_DeepTheme_Audio_Spring_Hazes_34.mp3";

    //qrc:/audio/Debug/music/Happyday.mp3    Happyday
    //qrc:/audio/Debug/music/Mushroom.mp3    Mushroom
    //qrc:/audio/Debug/music/Running.mp3     Running！

    // 音量设置
    const float DefaultEffectVolume = 0.5f;
    const float DefaultMusicVolume = 0.2f;

    // 音频类型枚举
    enum AudioType
    {
        Effect,  // 音效(短音频)
        Music    // 音乐(长音频)
    };
}

#endif // AUDIOCONFIG_H
