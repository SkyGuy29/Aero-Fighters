#pragma once

// Small generic struct for holding the size of the window
struct WindowSize
{
	// Width of the window
	unsigned short width;

	// Height of the window
	unsigned short height;
};
const static WindowSize windowSize = { 224, 320 };