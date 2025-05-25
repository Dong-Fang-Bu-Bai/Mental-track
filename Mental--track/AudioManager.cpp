#include "AudioManager.h"

AudioManager* AudioManager::m_instance = nullptr;

AudioManager::AudioManager(QObject *parent)
    : QObject(parent),
      m_effectsVolume(AudioConfig::DefaultEffectVolume),
      m_musicVolume(AudioConfig::DefaultMusicVolume),
      m_currentMusicPath(AudioConfig::BackgroundMusic)
{
     m_musicPlayer = new QMediaPlayer(this);

    m_musicPlayer->setVolume(static_cast<int>(m_musicVolume * 100));

    // 连接媒体状态改变信号来实现循环
    connect(m_musicPlayer, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status)
    {
        if(status == QMediaPlayer::EndOfMedia)
        {
            m_musicPlayer->play(); // 播放结束时重新开始
        }
    });

    // 预加载常用音效
    preloadCommonEffects();
}


QString AudioManager::currentMusicPath() const
{
    return m_currentMusicPath;
}

void AudioManager::setCurrentMusicPath(const QString& path)
{
    m_currentMusicPath = path;
}

AudioManager* AudioManager::instance()
{
    if(!m_instance) {
        m_instance = new AudioManager();
    }
    return m_instance;
}

void AudioManager::playEffect(const QString& source, float volume)
{
    // 如果未指定volume，使用当前全局音量
        float actualVolume = (volume !=AudioConfig::DefaultEffectVolume) ? volume : m_effectsVolume;

        if(!m_effects.contains(source)) {
            QSoundEffect* effect = new QSoundEffect(this);
            effect->setSource(QUrl(source));
            effect->setVolume(actualVolume); // 设置初始音量
            m_effects[source] = effect;
        }

        QSoundEffect* effect = m_effects.value(source);
        effect->setVolume(actualVolume); // 每次播放前更新音量
        effect->play();
}

void AudioManager::playMusic(const QString& source, bool loop, float volume)
{
    // 停止当前音乐
    stopMusic();

    // 存储当前音乐路径
    setCurrentMusicPath(source);

    // 设置循环标志（通过信号槽实现）
    disconnect(m_musicPlayer, &QMediaPlayer::mediaStatusChanged, nullptr, nullptr);
    if(loop)
    {
        connect(m_musicPlayer, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status) {
            if(status == QMediaPlayer::EndOfMedia) {
                m_musicPlayer->play();
            }
        });
    }

    m_musicPlayer->setMedia(QUrl(source));
    setMusicVolume(volume);
    m_musicPlayer->play();
}

void AudioManager::stopMusic()
{
    m_musicPlayer->stop();
}

void AudioManager::pauseMusic()
{
    m_musicPlayer->pause();
}

void AudioManager::resumeMusic()
{
    m_musicPlayer->play();
}

void AudioManager::setEffectsVolume(float volume)
{
    m_effectsVolume = qBound(0.0f, volume, 1.0f);
    for(QSoundEffect* effect : m_effects.values())
    {
        effect->setVolume(m_effectsVolume);
    }
}

void AudioManager::setMusicVolume(float volume)
{
    m_musicVolume = qBound(0.0f, volume, 1.0f);
    m_musicPlayer->setVolume(static_cast<int>(m_musicVolume * 100));
}

float AudioManager::effectsVolume() const
{
    return m_effectsVolume;
}

float AudioManager::musicVolume() const
{
    return m_musicVolume;
}

void AudioManager::preloadCommonEffects()
{
    // 预加载常用音效
    playEffect(AudioConfig::ClickSound, 0); // 音量0表示预加载但不播放
}
