#include <iostream>
#include <Windows.h>

time_t verify_time() {
	time_t t = time(nullptr);
	return t;
}

void print(int music_PLAYED, int music_LENGHT, bool status) {
	system("cls");
	double progress_per = ((music_PLAYED * 100) / music_LENGHT/2.4);
	std::string progress_str;
	std::string stick = "-----------------------------------------";
	for (int i = 0; i < stick.size() - 2; i++) {
		if (i < progress_per) {
			progress_str += '>';
		}
		else progress_str += ' ';
	}
	std::cout << stick << '\n';
	std::cout << "|" << progress_str << "|\n";
	std::cout << stick << '\n';
	if (status) std::cout << "[ PAUSED ] " << music_PLAYED << "/" << music_LENGHT << "sec\n";
	else std::cout << "[ PLAYING ] " << music_PLAYED << "/" << music_LENGHT << "sec\n";
	std::cout << "[ PERCENTAGE ~ ] " << ((progress_per / stick.size())*100)-1 << "%" << "\n";
}

int main(int argc, char* argv[]) {
	int music_LENGHT = 200; // sec
	int music_PLAYED = 0; // sec
	bool pause = false;
	time_t t = 0;
	while (music_PLAYED != music_LENGHT) {
		if (!pause) {
			if (verify_time() != t) {
				music_PLAYED++;
				print(music_PLAYED, music_LENGHT, pause);
				t = verify_time();
			}
		}
		if (GetAsyncKeyState('S') & 0x001) {
			pause = false;
		}
		if (GetAsyncKeyState('P') & 0x001) {
			pause = true;
			print(music_PLAYED, music_LENGHT, pause);
		}
	}

	return 0;
}