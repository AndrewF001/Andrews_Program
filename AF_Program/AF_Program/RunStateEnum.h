#pragma once

enum RunState
{
	Paused,
	Running,
	Closed,
	Restarted
};

enum RunRequest
{
	Pause,
	Run,
	Stop,
	Close,
	Restart
};