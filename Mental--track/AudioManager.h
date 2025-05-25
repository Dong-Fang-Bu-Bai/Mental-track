#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QHash>
#include "AudioConfig.h"

class AudioManager : public QObject
{
    Q_OBJECT
public:
    // 单例访问
    static AudioManager* instance();

    //背景音乐
    QString currentMusicPath() const;
    void setCurrentMusicPath(const QString& path);

    // 播放控制
    void playEffect(const QString& source=AudioConfig::ClickSound, float volume = AudioConfig::DefaultEffectVolume);
    void playMusic(const QString& source=AudioConfig::BackgroundMusic, bool loop = true, float volume = AudioConfig::DefaultMusicVolume);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    // 音量控制
    void setEffectsVolume(float volume);
    void setMusicVolume(float volume);
    float effectsVolume() const;
    float musicVolume() const;

    // 预加载常用音效
    void preloadCommonEffects();



private:
    explicit AudioManager(QObject *parent = nullptr);
    static AudioManager* m_instance;

    QMediaPlayer* m_musicPlayer;  // 背景音乐播放器
    QHash<QString, QSoundEffect*> m_effects;  // 音效缓存
    float m_effectsVolume;
    float m_musicVolume;
    QString m_currentMusicPath;
};



#endif // AUDIOMANAGER_H
