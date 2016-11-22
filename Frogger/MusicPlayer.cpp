#include "MusicPlayer.h"


namespace GEX
{
	MusicPlayer::MusicPlayer():
		_music(),
		_filename(),
		_volume(10.f)
	{
		_filename[MusicID::MenuTheme] = "../Media/music.ogg";
		_filename[MusicID::MissionTheme] = "../Media/Music/MissionTheme.ogg";
	}
	void MusicPlayer::play(MusicID theme)
	{
		std::string filename = _filename[theme];
		if (!_music.openFromFile(filename))
			throw std::runtime_error("music ");

		_music.setVolume(_volume);
		_music.setLoop(true);
		_music.play();
	}
	void MusicPlayer::stop()
	{
		_music.stop();
	}
	void MusicPlayer::setPause(bool paused)
	{
		if (paused)
			_music.pause();
		else
			_music.play();
	}
	void MusicPlayer::setVolume(float volume)
	{
		_volume = volume;
	}
}
