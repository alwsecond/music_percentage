#include <iostream>
#include <Windows.h>

bool pause = false;
bool debug = false;
int music_LENGHT = 65; // seconds;
int music_PLAYED = 0;

// P - stop/play, D - debug;

time_t verify_time() {
	time_t t = time(nullptr);
	return t;
}

struct Elements {
	std::string filled = ">";
	char empty = ' ';
} e;

void print(int music_PLAYED, int music_LENGHT, bool status, bool debug) {
	system("cls");
	double percentage = (static_cast<double>(music_PLAYED) / music_LENGHT) * 100;
	std::string stick = "-------------------------------------";
	std::string progress;
	int progress_SIZE = (stick.size()*static_cast<int>(percentage))/100;
	for (int i = 0; i < stick.size()-2; i++) {
		if (i < progress_SIZE) progress += e.filled;
		else progress += e.empty;
	}
	std::cout << stick << '\n';
	std::cout << '|' << progress << "|\n";
	std::cout << stick << '\n';
	if (status) std::cout << "\t[ PAUSED ] " << music_PLAYED << "/" << music_LENGHT << "sec\n";
	else std::cout << "\t[ PLAYING ] " << music_PLAYED << "/" << music_LENGHT << "sec\n";
	if (debug) {
		std::cout << "\t[ PERCENTAGE ] " << percentage << "%" << "\n";
		std::cout << "\t[ FILLED ] " << progress_SIZE << "/" << stick.size() << "\n";
	}
}

int main(int argc, char* argv[]) {
	time_t t = 0;
	while (music_PLAYED != music_LENGHT) {
		if (!pause) {
			if (verify_time() != t) {
				music_PLAYED++;
				print(music_PLAYED, music_LENGHT, pause, debug);
				t = verify_time();
			}
		}
		if (GetAsyncKeyState('P') & 0x001) {
			if (!pause) pause = true;
			else pause = false;
			print(music_PLAYED, music_LENGHT, pause, debug);
		}
		if (GetAsyncKeyState('D') & 0x001) {
			if (!debug) debug = true;
			else debug = false;
			print(music_PLAYED, music_LENGHT, pause, debug);
		}
	}

	return 0;
}