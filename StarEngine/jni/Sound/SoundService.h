#pragma once

#include "../defines.h"

#ifdef _WIN32
#include "SDL.h"
#include "SDL_mixer.h"
#else
#include "android_native_app_glue.h"
#include  <SLES/OpenSLES.h>
#include  <SLES/OpenSLES_Android.h>
#include  <SLES/OpenSLES_AndroidConfiguration.h>
#endif

#include "SoundFile.h"
#include "SoundEffect.h"
#include <map>
#include <vector>

namespace star
{

	class SoundService
	{
	public:
		static SoundService* GetInstance();
		~SoundService(){}
		status Start();
		void Stop();

		status LoadMusic(const tstring& path, const tstring& name);
		status LoadSoundEffect(const tstring& path, const tstring& name);

		//You can load sounds at runtime but for ensuring smooth play preload with LoadMusic
		status PlaySoundFile(const tstring& path, const tstring& name);
		status PlaySoundFile(const tstring& name);

		//You can load sounds at runtime but for ensuring smooth play preload with LoadMusic
		status PlaySoundEffect(const tstring& path, const tstring& name);
		status PlaySoundEffect(const tstring& name);

		status AddToBackgroundQueue(const tstring& name);

		//For looptimes : -1 repeat forever, 0 play once 
		status PlayBackgroundQueue();
		void NextSongInQueue();

		void StopSound(const tstring& name);
		void StopAllSound();
		void PauzeAllSound();
		void ResumeAllSound();
		void DeleteAllSound();
#ifndef _WIN32
		const SLEngineItf& GetEngine(){return mEngine;}
		const SLObjectItf& GetOutputMixObject(){return mOutputMixObj;}
#endif
	private:
		SoundService();

		static SoundService* mSoundService;

		std::map<tstring,SoundFile*> mMusicList;
		std::map<tstring,SoundEffect*> mEffectsList;
		std::vector<SoundFile*> mBackgroundQueue;
		std::vector<SoundFile*>::iterator mQueueIterator;

#ifndef _WIN32
		SLObjectItf mEngineObj;
		SLEngineItf mEngine;
		SLObjectItf mOutputMixObj;
#endif
		SoundService(const SoundService& yRef);
		SoundService(SoundService&& yRef);
		SoundService& operator=(const SoundService& yRef);
	};
}