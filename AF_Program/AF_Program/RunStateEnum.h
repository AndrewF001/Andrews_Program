#pragma once

enum RunState
{
	Paused,		//Started a process but paused
	Running,	//Running
	Closed,		//Everything is deleted off heap and ready for thread deletion
	Restarted	//brand new or fresh start that hasn't been run
};

enum RunRequest
{
	Pause,		//pauses mid way thread
	Run,		//starts thread from any posistion
	Close,		//request to delete heap so thread is ready for closing
	Restart		//resets the thread, can be called anytime
};

enum TabState
{
	start,
	running,
	paused,
	ended
};