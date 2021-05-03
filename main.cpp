#include <opencv2/highgui.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN) {
		int *ptr = (int *) userdata;
		*ptr = x;
    }
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "Add video file name as argument!" << endl;
		return -1;
	}
	string video_file_name = argv[1];
	VideoCapture video(video_file_name);
	if (!video.isOpened()) {
		cout << "Video can't be opened or not found!" << endl;
		return -1;
	}
	double fps = video.get(CV_CAP_PROP_FPS);
	cout << "Playing video: " << video_file_name << endl;
	cout << "Video FPS: " << fps << endl;
	Size video_refs = Size((int) video.get(CAP_PROP_FRAME_WIDTH), (int) video.get(CAP_PROP_FRAME_HEIGHT));
	cout << "Reference frame resolution: Width=" << video_refs.width << "  Height=" << video_refs.height << endl;
	cout << "Frame counts: " << video.get(CAP_PROP_FRAME_COUNT) << endl;

	cout << endl << "COMMAND LIST" << endl;
	cout << "Control with keyboard :" << endl;
	cout << "Press `esc` to quit the window" << endl;
	cout << "Press `s` to skip the video by 5 seconds" << endl;
	cout << "Press `e` to undo the video by 5 seconds" << endl;
	cout << "Press `p` to play or pause the video" << endl << endl;

	cout << "Control with mouse click :" << endl;
	cout << "Click the left part of the video to undo video by 5 seconds" << endl;
	cout << "Click the middle part of the video to play or pause the video" << endl;
	cout << "Click the right part of the video to skip the video by 5 seconds" << endl << endl;
	
	namedWindow("video_player", CV_WINDOW_AUTOSIZE);
	int x_coordinate_click = -1;
	// Controll with mouse click
	setMouseCallback("video_player", CallBackFunc, &x_coordinate_click);
	
	Mat frame;
	bool play_video = true;
	while (true) {
		// cout << "Current Video position (msec): " << video.get(CAP_PROP_POS_MSEC) << endl;
		if (play_video) {
			video.read(frame);
		}
		if (frame.empty()) {
			cout << "Frame is empty or video is finished!" << endl;
			break;
		}
		imshow("video_player", frame);

		// Controll with keyboard
		char key = waitKey(30);
		if (x_coordinate_click != -1) {
			int video_width = (int) video.get(CAP_PROP_FRAME_WIDTH);
			int display_part = video_width / 3;
			if (x_coordinate_click < display_part) {
				key = 'e';
			} else if (x_coordinate_click < display_part*2) {
				key = 'p';
			} else {
				key = 's';
			}
		}
		if (key == 27) {
			cout << "Escape key (esc) was pressed!" << endl;
			break;
		}
		if (key == 's') {
			cout << "Skip key (s) was pressed!" << endl;
			video.set(CAP_PROP_POS_MSEC, video.get(CAP_PROP_POS_MSEC) + 5000);
			imshow("video_player", video.read(frame));
		}
		if (key == 'e') {
			cout << "Prev key (e) was pressed!" << endl;
			double ts = (video.get(CAP_PROP_POS_MSEC) - 5000);
			ts = ts < 0 ? 0 : ts;
			video.set(CAP_PROP_POS_MSEC, ts);
			imshow("video_player", video.read(frame));
		}
		if (key == 'p') {
			cout << "Play or Pause (p) was pressed!" << endl;
			play_video ^= 1;
		}
		x_coordinate_click = -1;
	}

	return 0;
}